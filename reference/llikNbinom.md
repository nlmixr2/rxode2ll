# Calculate the log likelihood of the negative binomial function (and its derivatives)

Calculate the log likelihood of the negative binomial function (and its
derivatives)

## Usage

``` r
llikNbinom(x, size, prob, full = FALSE)
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
llikNbinom(46:54, 100, 0.5)
#>          fx dProb
#> 1 -13.25200   108
#> 2 -12.81168   106
#> 3 -12.38560   104
#> 4 -11.97335   102
#> 5 -11.57458   100
#> 6 -11.18892    98
#> 7 -10.81603    96
#> 8 -10.45559    94
#> 9 -10.10728    92

llikNbinom(46:54, 100, 0.5, TRUE)
#>    x size prob        fx dProb
#> 1 46  100  0.5 -13.25200   108
#> 2 47  100  0.5 -12.81168   106
#> 3 48  100  0.5 -12.38560   104
#> 4 49  100  0.5 -11.97335   102
#> 5 50  100  0.5 -11.57458   100
#> 6 51  100  0.5 -11.18892    98
#> 7 52  100  0.5 -10.81603    96
#> 8 53  100  0.5 -10.45559    94
#> 9 54  100  0.5 -10.10728    92
```
