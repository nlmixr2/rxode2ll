# Calculate the log likelihood of the negative binomial function (and its derivatives)

Calculate the log likelihood of the negative binomial function (and its
derivatives)

## Usage

``` r
llikNbinomMu(x, size, mu, full = FALSE)
```

## Arguments

- x:

  Number of successes

- size:

  Size of trial

- mu:

  mu parameter for negative binomial

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

llikNbinomMu(46:54, 100, 40)
#>          fx       dMu
#> 1 -3.326828 0.1071429
#> 2 -3.446132 0.1250000
#> 3 -3.579663 0.1428571
#> 4 -3.727034 0.1607143
#> 5 -3.887874 0.1785714
#> 6 -4.061827 0.1964286
#> 7 -4.248554 0.2142857
#> 8 -4.447728 0.2321429
#> 9 -4.659037 0.2500000

llikNbinomMu(46:54, 100, 40, TRUE)
#>    x size mu        fx       dMu
#> 1 46  100 40 -3.326828 0.1071429
#> 2 47  100 40 -3.446132 0.1250000
#> 3 48  100 40 -3.579663 0.1428571
#> 4 49  100 40 -3.727034 0.1607143
#> 5 50  100 40 -3.887874 0.1785714
#> 6 51  100 40 -4.061827 0.1964286
#> 7 52  100 40 -4.248554 0.2142857
#> 8 53  100 40 -4.447728 0.2321429
#> 9 54  100 40 -4.659037 0.2500000
```
