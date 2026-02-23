
<!-- README.md is generated from README.Rmd. Please edit that file -->

# rxode2ll

<!-- badges: start -->

[![R-CMD-check](https://github.com/nlmixr2/rxode2ll/actions/workflows/R-CMD-check.yaml/badge.svg)](https://github.com/nlmixr2/rxode2ll/actions/workflows/R-CMD-check.yaml)
[![Codecov test
coverage](https://codecov.io/gh/nlmixr2/rxode2ll/graph/badge.svg)](https://app.codecov.io/gh/nlmixr2/rxode2ll)
[![CRAN
version](http://www.r-pkg.org/badges/version/rxode2ll)](https://cran.r-project.org/package=rxode2ll)
[![CRAN total
downloads](https://cranlogs.r-pkg.org/badges/grand-total/rxode2ll)](https://cran.r-project.org/package=rxode2ll)
[![CRAN total
downloads](https://cranlogs.r-pkg.org/badges/rxode2ll)](https://cran.r-project.org/package=rxode2ll)
[![CodeFactor](https://www.codefactor.io/repository/github/nlmixr2/rxode2ll/badge)](https://www.codefactor.io/repository/github/nlmixr2/rxode2ll)
![r-universe](https://nlmixr2.r-universe.dev/badges/rxode2ll)
<!-- badges: end -->

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

- `llikNorm()`
- `llikPois()`
- `llikBinom()`
- `llikNbinom()`
- `llikNbinomMu()`
- `llikBeta()`
- `llikT()`
- `llikChisq()`
- `llikExp()`
- `llikF()`
- `llikGeom()`
- `llikUnif()`
- `llikWeibull()`
- `llikGamma()`
- `llikCauchy()`
