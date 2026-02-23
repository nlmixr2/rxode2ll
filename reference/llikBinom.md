# Calculate the log likelihood of the binomial function (and its derivatives)

Calculate the log likelihood of the binomial function (and its
derivatives)

## Usage

``` r
llikBinom(x, size, prob, full = FALSE)
```

## Arguments

- x:

  Number of successes

- size:

  Size of trial

- prob:

  probability of success

- full:

  Add the data frame showing x, mean, sd as well as the fx and
  derivatives

## Value

data frame with `fx` for the pdf value of with `dProb` that has the
derivatives with respect to the parameters at the observation time-point

## Author

Matthew L. Fidler

## Examples

``` r
llikBinom(46:54, 100, 0.5)
#>          fx dProb
#> 1 -2.848030   -16
#> 2 -2.709193   -12
#> 3 -2.610102    -8
#> 4 -2.550679    -4
#> 5 -2.530876     0
#> 6 -2.550679     4
#> 7 -2.610102     8
#> 8 -2.709193    12
#> 9 -2.848030    16

llikBinom(46:54, 100, 0.5, TRUE)
#>    x size prob        fx dProb
#> 1 46  100  0.5 -2.848030   -16
#> 2 47  100  0.5 -2.709193   -12
#> 3 48  100  0.5 -2.610102    -8
#> 4 49  100  0.5 -2.550679    -4
#> 5 50  100  0.5 -2.530876     0
#> 6 51  100  0.5 -2.550679     4
#> 7 52  100  0.5 -2.610102     8
#> 8 53  100  0.5 -2.709193    12
#> 9 54  100  0.5 -2.848030    16
```
