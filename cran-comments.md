## Third Attempt CRAN comments

> Please write references in the description of the DESCRIPTION file in
> the form
> authors (year) <doi:...>
> authors (year) <arXiv:...>
> authors (year, ISBN:...)
> or if those are not available: authors (year) <https:...>
> with no space after 'doi:', 'arXiv:', 'https:' and angle brackets for
> auto-linking. (If you want to add a title as well please put it in
> quotes: "Title")

Added parentheses in the year, as requested.

> Some code lines in examples are commented out. Please never do that.
> Ideally find toy examples that can be regularly executed and checked.
> Lengthy examples (> 5 sec), can be wrapped in \donttest{}.
> Since you want to show how it is done in 'rxode2', maybe list 'rxode2'
> in ‘Suggests’, and wrap the examples in
> if(requireNamespace("rxode2")){}. That way, users who have 'rxode2'
> installed can run the examples and those who have not don't get an error.

This was commented out to avoid a cyclic dependency (that is rxode2ll needs
rxode2 to test, but rxode2 needs rxode2ll to compile).

Instead of commenting out all references to the 'rxode2' examples,
they are removed in this package (and all references in the
documentation to 'rxode2' are removed too).

In the next release of the 'rxode2' package, the same examples and
documentation will be moved to 'rxode2' when the binary linkage is
available.

## Second Attempt Cran comments

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
