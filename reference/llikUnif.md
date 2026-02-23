# log likelihood and derivatives for Unif distribution

log likelihood and derivatives for Unif distribution

## Usage

``` r
llikUnif(x, alpha, beta, full = FALSE)
```

## Arguments

- x:

  variable distributed by a uniform distribution

- alpha:

  is the lower limit of the uniform distribution

- beta:

  is the upper limit of the distribution

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
llikUnif(1, -2, 2)
#>          fx dAlpha dBeta
#> 1 -1.386294   0.25 -0.25
```
