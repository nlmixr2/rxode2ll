# rxode2ll

The goal of rxode2ll is to create log-likelihood functions for use in
‘rxode2’ and ‘nlmixr2’

## Installation

You can install the development version of rxode2ll from
[GitHub](https://github.com/) with:

``` r

# install.packages("devtools")
devtools::install_github("nlmixr2/rxode2ll")
```

## Examples

Each of the C++ interface to the `stan` log-likelihood equations can be
used in a stand-alone manner. For example:

``` r

llikNorm(seq(-2,2,length.out=10), full=TRUE)
```

The following log-likelihood distributions are supported:

- [`llikNorm()`](https://nlmixr2.github.io/rxode2ll/reference/llikNorm.md)
- [`llikPois()`](https://nlmixr2.github.io/rxode2ll/reference/llikPois.md)
- [`llikBinom()`](https://nlmixr2.github.io/rxode2ll/reference/llikBinom.md)
- [`llikNbinom()`](https://nlmixr2.github.io/rxode2ll/reference/llikNbinom.md)
- [`llikNbinomMu()`](https://nlmixr2.github.io/rxode2ll/reference/llikNbinomMu.md)
- [`llikBeta()`](https://nlmixr2.github.io/rxode2ll/reference/llikBeta.md)
- [`llikT()`](https://nlmixr2.github.io/rxode2ll/reference/llikT.md)
- [`llikChisq()`](https://nlmixr2.github.io/rxode2ll/reference/llikChisq.md)
- [`llikExp()`](https://nlmixr2.github.io/rxode2ll/reference/llikExp.md)
- [`llikF()`](https://nlmixr2.github.io/rxode2ll/reference/llikF.md)
- [`llikGeom()`](https://nlmixr2.github.io/rxode2ll/reference/llikGeom.md)
- [`llikUnif()`](https://nlmixr2.github.io/rxode2ll/reference/llikUnif.md)
- [`llikWeibull()`](https://nlmixr2.github.io/rxode2ll/reference/llikWeibull.md)
- [`llikGamma()`](https://nlmixr2.github.io/rxode2ll/reference/llikGamma.md)
- [`llikCauchy()`](https://nlmixr2.github.io/rxode2ll/reference/llikCauchy.md)
