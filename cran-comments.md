* This is a new package to split off the log-likelihoods (with
  derivatives) from 'stan' to allow nonlinear mixed effects models
  using generalized likelihood link functions in 'nlmixr2'
  
* The goal of this package is to reduce the compilation time, of
  'rxode2' as requested by Prof Brian Ripley.
  
* These functions, while taking most of the compile time in 'rxode2'
  are not likely to change. Therefore this is like a data-only package that
  will only need to be compiled infrequently to save CRAN maintainers' 
  (and my) time.

## R CMD check results

0 errors | 0 warnings | 1 note

* This is a new release.
