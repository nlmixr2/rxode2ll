# Log likelihood for normal distribution

Log likelihood for normal distribution

## Usage

``` r
llikNorm(x, mean = 0, sd = 1, full = FALSE)
```

## Arguments

- x:

  Observation

- mean:

  Mean for the likelihood

- sd:

  Standard deviation for the likelihood

- full:

  Add the data frame showing x, mean, sd as well as the fx and
  derivatives

## Value

data frame with `fx` for the pdf value of with `dMean` and `dSd` that
has the derivatives with respect to the parameters at the observation
time-point

## Author

Matthew L. Fidler

## Examples

``` r

llikNorm(0)
#>           fx dMean dSd
#> 1 -0.9189385     0  -1

llikNorm(seq(-2,2,length.out=10), full=TRUE)
#>             x mean sd         fx      dMean        dSd
#> 1  -2.0000000    0  1 -2.9189385 -2.0000000  3.0000000
#> 2  -1.5555556    0  1 -2.1288151 -1.5555556  1.4197531
#> 3  -1.1111111    0  1 -1.5362225 -1.1111111  0.2345679
#> 4  -0.6666667    0  1 -1.1411608 -0.6666667 -0.5555556
#> 5  -0.2222222    0  1 -0.9436299 -0.2222222 -0.9506173
#> 6   0.2222222    0  1 -0.9436299  0.2222222 -0.9506173
#> 7   0.6666667    0  1 -1.1411608  0.6666667 -0.5555556
#> 8   1.1111111    0  1 -1.5362225  1.1111111  0.2345679
#> 9   1.5555556    0  1 -2.1288151  1.5555556  1.4197531
#> 10  2.0000000    0  1 -2.9189385  2.0000000  3.0000000
```
