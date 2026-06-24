# log likelihood and derivatives for chi-squared distribution

log likelihood and derivatives for chi-squared distribution

## Usage

``` r
llikChisq(x, df, full = FALSE)
```

## Arguments

- x:

  variable that is distributed by chi-squared distribution

- df:

  degrees of freedom (non-negative, but can be non-integer).

- full:

  Add the data frame showing x, mean, sd as well as the fx and
  derivatives

## Value

data frame with `fx` for the log pdf value of with `dDf` that has the
derivatives with respect to the `df` parameter the observation
time-point

## Author

Matthew L. Fidler

## Examples

``` r

llikChisq(1, df = 1:3, full=TRUE)
#>   x df        fx         dDf
#> 1 1  1 -1.418939  0.63518142
#> 2 1  2 -1.193147 -0.05796576
#> 3 1  3 -1.418939 -0.36481858

llikChisq(1, df = 6:9)
#>          fx        dDf
#> 1 -3.272589 -0.8079658
#> 2 -4.126989 -0.8981519
#> 3 -5.064348 -0.9746324
#> 4 -6.072899 -1.0410091
```
