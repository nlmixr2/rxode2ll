# log likelihood and derivatives for exponential distribution

log likelihood and derivatives for exponential distribution

## Usage

``` r
llikExp(x, rate, full = FALSE)
```

## Arguments

- x:

  variable that is distributed by exponential distribution

- rate:

  vector of rates.

- full:

  Add the data frame showing x, mean, sd as well as the fx and
  derivatives

## Value

data frame with `fx` for the log pdf value of with `dRate` that has the
derivatives with respect to the `rate` parameter the observation
time-point

## Author

Matthew L. Fidler

## Examples

``` r

llikExp(1, 1:3)
#>          fx      dRate
#> 1 -1.000000  0.0000000
#> 2 -1.306853 -0.5000000
#> 3 -1.901388 -0.6666667

llikExp(1, 1:3, full=TRUE)
#>   x rate        fx      dRate
#> 1 1    1 -1.000000  0.0000000
#> 2 1    2 -1.306853 -0.5000000
#> 3 1    3 -1.901388 -0.6666667
```
