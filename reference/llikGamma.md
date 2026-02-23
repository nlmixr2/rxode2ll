# log likelihood and derivatives for Gamma distribution

log likelihood and derivatives for Gamma distribution

## Usage

``` r
llikGamma(x, shape, rate, full = FALSE)
```

## Arguments

- x:

  variable that is distributed by gamma distribution

- shape:

  this is the distribution's shape parameter. Must be positive.

- rate:

  this is the distribution's rate parameters. Must be positive.

- full:

  Add the data frame showing x, mean, sd as well as the fx and
  derivatives

## Value

data frame with `fx` for the log pdf value of with `dProb` that has the
derivatives with respect to the `prob` parameters at the observation
time-point

## Author

Matthew L. Fidler

## Examples

``` r
llikGamma(1, 1, 10)
#>          fx   dShape dRate
#> 1 -7.697415 2.879801  -0.9
```
