# log-likelihood for the Poisson distribution

log-likelihood for the Poisson distribution

## Usage

``` r
llikPois(x, lambda, full = FALSE)
```

## Arguments

- x:

  non negative integers

- lambda:

  non-negative means

- full:

  Add the data frame showing x, mean, sd as well as the fx and
  derivatives

## Value

data frame with `fx` for the pdf value of with `dLambda` that has the
derivatives with respect to the parameters at the observation time-point

## Author

Matthew L. Fidler
