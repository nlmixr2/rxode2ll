# rxode2ll (development version)

* `llikNorm()`, `llikT()`, and `llikCauchy()` no longer silently replace a
  scale parameter (`sigma`/`sd`/`scale`) smaller than
  `sqrt(.Machine$double.eps)` with `1`. That guard (`_smallIsOne`) was meant
  to avoid a divide-by-zero, but replacing a genuinely tiny scale with `1`
  turned a catastrophically bad fit -- a large residual over a near-zero
  scale, which should read as an enormous negative log-likelihood -- into one
  that merely looked moderately bad. A maximum-likelihood search or an MCMC
  sampler reading this log-likelihood (e.g. `nlmixr2est`'s SAEM
  general-likelihood `do_mcmc`/direct theta optimization) could wander into
  and get trapped in that degenerate region, since nothing in the objective
  correctly punished it -- observed as `saem` diverging to nonsensical
  parameter estimates on a `dnorm()`/`dt()`/`cauchy()` general-likelihood
  endpoint whose structural model can drive its prediction toward zero (e.g.
  a Michaelis-Menten elimination model with proportional error). The scale
  is now floored at `sqrt(.Machine$double.eps)` instead (`_smallIsNotZero`,
  matching the guard `llikT()`'s own `df` parameter already used), so it
  still avoids the divide-by-zero but the resulting log-likelihood stays
  correctly, severely negative rather than flipping to a false local optimum.

* `llikNbinom()` and `llikNbinomMu()` now accept a continuous (non-integer)
  `size`.  In the negative binomial's mean/dispersion parameterisation `size`
  is a real dispersion parameter, not a count, and `stats::dnbinom()` has
  always allowed it.  Previously `size` was stored in an integer vector and
  silently truncated, so a `size` above 1 returned the log-likelihood at
  `trunc(size)` and a `size` between 0 and 1 truncated to 0 and aborted; the
  R-level `assertIntegerish(size)` rejected such values outright.  Truncation
  also made the log-likelihood a step function of `size`, so the dispersion
  could not be estimated even when its true value was an integer.  This
  blocked `nbinomMu()` models with continuous overdispersion in `nlmixr2`.
  `size` must now be strictly positive; non-positive values return `NA`.  The
  `INT_MAX` bound added in 2.0.15 still applies to `x` everywhere, and to
  `size` for `rxLlikBinom` where `size` is a number of trials.

* `llikNbinom()` and `llikNbinomMu()` now return `NA` instead of aborting the R
  process when the mean handed to the underlying likelihood is out of domain.
  This covers a `prob` of 0 (and, through the C API, a `prob` outside `[0, 1]`
  or a negative `mu`), and -- because `size` is no longer bounded by `INT_MAX`
  -- a large `size` with a small `prob` whose product overflows.  Previously
  these threw a C++ exception that escaped the `rxLlikNbinom()` /
  `rxLlikNbinomMu()` entry points used by `rxode2` solves and `focei`, killing
  the session.

* `llikNbinom()` at `prob == 1` and `llikNbinomMu()` at `mu == 0` now match
  `stats::dnbinom()`.  The distribution is degenerate at zero there, so `fx` is
  `0` (a likelihood of 1) at `x == 0` and `-Inf` otherwise.  These are the only
  points where `stats::dnbinom()` defines a value that the underlying Stan
  likelihood cannot compute -- it requires a strictly positive mean.  No
  derivative exists at a point mass, so `dProb` / `dMu` are `NA`; an unusable
  gradient beats a `NA` log-likelihood, and beats the abort these used to
  cause.  `prob == 0` remains `NA`, matching the `NaN` R returns there.


# rxode2ll 2.0.16

* Fix ABI issues in rxode2 and the nlmixr2 ecosystem by requiring
  RcppParallel 6.0.0

# rxode2ll 2.0.15

* Fix signed integer overflow: loop indices in `llikXxxInternal()` Rcpp
  functions changed from `int` to `R_xlen_t`; previously vectors longer
  than ~500 million elements (>4 GB) could cause undefined behavior due
  to `int` overflow when assigned from `x.size()`.
* Fix undefined behavior from unchecked `double`-to-`int` casts for discrete
  distribution count arguments (`x`, `size`) exceeding `INT_MAX`
  (2147483647); the five affected C-API functions (`rxLlikPois`,
  `rxLlikBinom`, `rxLlikGeom`, `rxLlikNbinom`, `rxLlikNbinomMu`) now return
  `NA` instead of invoking undefined behavior for out-of-range inputs.
* Fix type correctness for loop indices in Stan autodiff functor
  `operator()` methods across all 15 distributions: changed from `int` to
  `Eigen::Index` to match the return type of `Eigen::VectorXd::size()`.
* Add comprehensive derivative validation tests using central finite
  differences for all 14 differentiable distributions.
* Add integer overflow bounds-checking tests for all 5 discrete
  distributions, calling the `*Internal()` C++ functions directly to
  bypass R-level input validation.
* Add a `skip()`-guarded large-vector test that documents the `R_xlen_t`
  fix and can be run manually on systems with >4 GB free RAM.
* Changed _log() to _lpmf()/_lpdf() because these functions changed
  in StanHeaders

# rxode2ll 2.0.14

* Make all distribution calculations thread safe

# rxode2ll 2.0.13

* Update compile flags in anticipation of BH 1.87.0 (#10)

# rxode2ll 2.0.12

* Update compile flags for alpine linux (#7)

# rxode2ll 2.0.11

* Update compile flags based on CRAN C++17 requirement (Issue #5)

# rxode2ll 2.0.10

* Update compile flags based on StanHeaders change.

# rxode2ll 2.0.9

* Initial release, exports log-likelihood functions from 'stan' and
  their derivatives to R and C.  This allows linkage in 'rxode2' to
  allow generalized log-likelihood in 'nlmixr2'.
* This is a data like package and is likely not to change very much
  over time.
* Added a `NEWS.md` file to track changes to the package.
