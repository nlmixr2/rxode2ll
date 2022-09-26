## Cran comments

* Fixed `Conditional jump or move depends on uninitialised value(s)` in code

> Thanks we see:
>   The Title field should be in title case. Current version is:
>   'Log-likelihood Functions for 'rxode2''
>   In title case that is:
>   'Log-Likelihood Functions for 'rxode2''

* Fixed

>
>   The Description field should start with a capital letter and not with
>   the package name. Ideally omit the redudnant (and non grammatical)
> "'rxode2' is a tool for for "

* Rewrote the description as requested


> Is there some reference about the method you can add in the Description
> field in the form Authors (year) <doi:10.....> or <arXiv:.....>?

* Added 3 references in the description


## First attempt comments

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
