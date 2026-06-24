# log likelihood and derivatives for Weibull distribution

log likelihood and derivatives for Weibull distribution

## Usage

``` r
llikWeibull(x, shape, scale, full = FALSE)
```

## Arguments

- x:

  variable distributed by a Weibull distribution

- shape, scale:

  shape and scale parameters, the latter defaulting to 1.

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

llikWeibull(1, 1, 10)
#>          fx    dShape dScale
#> 1 -2.402585 -1.072327  -0.09
```
