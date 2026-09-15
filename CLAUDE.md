# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when
working with code in this repository.

## Overview

**rxode2ll** provides log-likelihoods and their exact gradients (via Stan
Math reverse-mode autodiff) for the distributions `rxode2` models can use in
`llik*()` calls and `nlmixr2` estimates with generalized likelihoods. It is
split out of `rxode2` so the heavy Stan headers are not recompiled with every
`rxode2` build. Every compiled `rxode2` model loads this package, so it is
effectively on the load path of the whole nlmixr2 ecosystem.

## Build and Development Commands

### Install/Build
```r
# Install development version (from within R)
devtools::install()

# Or from the shell
R CMD INSTALL .
```

### Document
```r
devtools::document()
```

### Run All Tests
```sh
find src -name "*.so" -o -name "*.o" | xargs rm -f 2>/dev/null; NOT_CRAN=true Rscript -e "devtools::test()"
```

### Run a Single Test File
```sh
# Filter by test file name (without "test-" prefix and ".R" suffix)
NOT_CRAN=true Rscript -e "devtools::test(filter='llik')"
NOT_CRAN=true Rscript -e "devtools::test(filter='newFamilies')"
NOT_CRAN=true Rscript -e "devtools::test(filter='no-tbb')"
```

### R CMD Check
```r
invisible(lapply(list.files("src", "\\.s?o$", full.names = TRUE), unlink));devtools::check()
# Or: R CMD check .
```

`configure`/`configure.win` run `inst/tools/workaround.R` to generate
`src/Makevars`(`.win`) from `src/Makevars.in`; `cleanup` removes them. Edit
`src/Makevars.in`, never the generated `src/Makevars`.

### Formatting and Linting
- R code is formatted with [air](https://posit-dev.github.io/air/) using
  `air.toml`; the `format-check` CI job runs `air format --check`. Run
  `air format .` (or on the files you touched) before committing. Install the
  pinned version with
  `curl -LsSf https://github.com/posit-dev/air/releases/download/0.11.0/air-installer.sh | sh`.
- `.lintr` is based on rxode2's rules; the `lint` CI job fails on any lint, so
  `lintr::lint_package()` must return nothing. `infix_spaces_linter` and
  `commas_linter` are on (air keeps them clean) and `indentation_linter` is off
  (air owns indentation).
- `R/RcppExports.R` is generated: air skips it by default and `.lintr`
  excludes it.

## Architecture

### One family, one file

Each distribution lives in `src/llik<Family>.cpp` and has the same shape
(copy `src/llikNorm.cpp` as a template):

1. A Stan functor (`normal_llik`) returning the per-observation `*_lpdf`, and a
   `llik_<family>()` that calls `rx_stan_math_thread_init_rev_autodiff()` and
   then `stan::math::jacobian()`.
2. A static `llik<Family>Full(double* ret, x, params...)` that fills a
   caller-owned cache: `ret[0]` is the family tag (`is<Family>` in
   `src/llik2.h`), then `x` and the parameters, then `fx` and one derivative per
   parameter. A call with the same tag and inputs returns the cache (skipped
   inside OpenMP parallel regions). Non-finite or out-of-domain input returns
   `NA`, never throws.
3. `//[[Rcpp::export]] llik<Family>Internal()` for the R wrapper.
4. `extern "C" double rxLlik<Family>(...)` and `rxLlik<Family>D<Param>(...)`
   entry points that return the `fx`/derivative slot.

The R wrappers (`R/llik.R`, `R/llikNew.R`) validate with `checkmate`, recycle
the inputs through `data.frame()`, call the `*Internal()` function, and
optionally `cbind()` the inputs (`full = TRUE`).

### Adding a family

1. `src/llik<Family>.cpp` as above; a new `is<Family>` tag in `src/llik2.h`.
2. Declarations in `src/llik.h`.
3. `Rcpp::compileAttributes(".")`, then hand-edit `src/init.c`: the forward
   prototype and the `callMethods[]` entry with its HARDCODED argument count
   (`R_init_rxode2ll` lives in `init.c`, not `RcppExports.cpp`). A stale count
   surfaces only at runtime as `Incorrect number of arguments (N), expecting M`.
4. Append the entry points to the pointer table (below).
5. R wrapper, roxygen docs, `devtools::document()`, and a test comparing `fx`
   against an independent reference density and the derivatives against
   central differences of that reference (see `tests/testthat/test-newFamilies.R`
   -- a transposed parameter pair still returns a finite, differentiable,
   wrong answer).

### Exposing entry points to downstream packages

`rxode2`/`nlmixr2est` reach the `rxLlik*` functions through the
**external-pointer table** returned by `.rxode2llPtr()` (`_rxode2ll_ptr()` in
`src/ptr.c`), read by the consumer header `inst/include/rxode2llPtrs.h` in the
consumer's own `.onLoad()`. This avoids the ABI coupling of
`R_GetCCallable()`. The `R_RegisterCCallable()` calls in `src/init.c` are kept
for already-released consumers.

To add an entry point, append in all of these, in the same order:

1. `src/ptr.c`: bump the `Rf_allocVector(VECSXP, N)` length and add
   `SET_VECTOR_ELT(ret, N, ...)` at the new last index.
2. `inst/include/rxode2llPtrs.h`: the `extern rxLlik<k>_t _p_rxLlik...`
   declaration (`<k>` = number of distribution parameters; add a typedef if no
   arity fits), a `_RXLL_NEXT(...)` line at the end of `iniRxode2llPtrs0()`
   (position in that list IS the slot index), and the `= NULL` definition at
   the end of the `iniRxode2ll` macro.
3. `src/init.c`: the matching `R_RegisterCCallable()`.

> [!IMPORTANT]
> **The pointer table is APPEND-ONLY, and nothing on the load path validates
> anything.** Released `rxode2`/`nlmixr2est` builds read slots by position and
> cannot be patched retroactively.
>
> 1. **Never rename, reorder, remove, or repurpose an existing slot**, and never
>    change the signature or semantics of a released `rxLlik*` entry point or
>    `R_RegisterCCallable()` name. Add a new entry point instead -- and ask first.
> 2. **Never add an unrequested check, assertion, or validation to package load,
>    `.rxode2llPtr()`, or the `rxLlik*` C entry points.** CRAN runs every
>    reverse dependency against a submission, and since every `rxode2` model
>    loads rxode2ll, one check that fires takes them all down. Assert in
>    rxode2ll's own tests instead.
>
> **Reverse-dependency compatibility is fixed here, in rxode2ll**, not in the
> released reverse dependency.

### No TBB

rxode2ll must neither link nor load TBB (RcppParallel's library); loading it is
what CRAN's gcc-UBSAN check reports for every package that loads rxode2ll.
`RXLL_NO_TBB` in `src/Makevars.in` keeps Stan's TBB tape observer and
`reduce_sum`/`map_rect` headers out of the build, and
`rx_stan_math_thread_init_rev_autodiff()` in `src/llik2.h` creates each
thread's AD tape instead. Do not add `RcppParallel` to `Imports`, link TBB, or
include Stan headers that pull it in. `tests/testthat/test-no-tbb.R` guards
this.

### Important Files

| File | Purpose |
|------|---------|
| `src/llik2.h` | Stan includes, per-thread AD tape init, family tags, shared helpers |
| `src/llik.h` | C declarations of every `rxLlik*` entry point |
| `src/llik<Family>.cpp` | One distribution: Stan functor, cache, Rcpp and C entry points |
| `src/init.c` | Manual `.Call` registration table and `R_RegisterCCallable()`s |
| `src/ptr.c` | Append-only external-pointer table (`.rxode2llPtr()`) |
| `inst/include/rxode2llPtrs.h` | Consumer header for the pointer table |
| `src/Makevars.in` | Build flags, including `RXLL_NO_TBB` |
| `R/llik.R`, `R/llikNew.R` | Exported `llik*()` R wrappers |

## R Code Style

- **Exported functions**: `camelCase` (e.g., `llikNorm`, `llikBetaProportion`)
- **Internal/non-exported functions**: `.camelCase` with a leading dot (e.g., `.rxode2llPtr`, `.gradCheck`)
- **Local variables inside functions**: `.camelCase` with a leading dot (e.g., `.df`, `.ret`)
- Avoid `snake_case` for new names.
- Use American English spelling for consistency and do not use unicode characters
- **Never write `rxode2ll:::foo` (or any `pkg:::`)** in tests or package code;
  CodeFactor flags every `:::`. Tests run in the package namespace, so call
  internals (e.g. `llikNormInternal()`) by their bare name.

### C/C++ Conventions

- C files use `#define STRICT_R_HEADERS` and `#define USE_FC_LEN_T`
- A C++ exception must never escape an `extern "C"` `rxLlik*` entry point: it
  aborts the R session inside `rxode2` solves. Return `NA` for out-of-domain
  input instead.

## Documentation and Comment Style

- Keep comments and documentation terse. State the fact, not the story behind
  it.
- Shorten multi-paragraph roxygen descriptions to a single compact paragraph,
  but keep every `@param`, `@return`, `@author`, `@export`, and `@keywords` tag.
- Organize `NEWS.md` per version (`# rxode2ll X.Y.Z`) as past-tense bullets, a
  sentence or two each, stating the change and its user-visible effect.
- ASCII only. No Unicode anywhere in the repo (CRAN requirement): use `--` for
  em-dashes, `->` for arrows, straight quotes, `...` for ellipses, etc.
