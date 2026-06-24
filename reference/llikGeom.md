# log likelihood and derivatives for Geom distribution

log likelihood and derivatives for Geom distribution

## Usage

``` r
llikGeom(x, prob, full = FALSE)
```

## Arguments

- x:

  variable distributed by a geom distribution

- prob:

  probability of success in each trial. `0 < prob <= 1`.

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

llikGeom(1:10, 0.2)
#>           fx dProb
#> 1  -1.832581  3.75
#> 2  -2.055725  2.50
#> 3  -2.278869  1.25
#> 4  -2.502012  0.00
#> 5  -2.725156 -1.25
#> 6  -2.948299 -2.50
#> 7  -3.171443 -3.75
#> 8  -3.394586 -5.00
#> 9  -3.617730 -6.25
#> 10 -3.840873 -7.50
```
