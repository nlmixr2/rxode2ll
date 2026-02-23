# Changelog

## rxode2ll 2.0.14

- Make all distribution calculations thread safe

## rxode2ll 2.0.13

CRAN release: 2024-12-15

- Update compile flags in anticipation of BH 1.87.0
  ([\#10](https://github.com/nlmixr2/rxode2ll/issues/10))

## rxode2ll 2.0.12

CRAN release: 2024-11-21

- Update compile flags for alpine linux
  ([\#7](https://github.com/nlmixr2/rxode2ll/issues/7))

## rxode2ll 2.0.11

CRAN release: 2023-03-17

- Update compile flags based on CRAN C++17 requirement (Issue
  [\#5](https://github.com/nlmixr2/rxode2ll/issues/5))

## rxode2ll 2.0.10

CRAN release: 2023-03-16

- Update compile flags based on StanHeaders change.

## rxode2ll 2.0.9

CRAN release: 2022-09-29

- Initial release, exports log-likelihood functions from ‘stan’ and
  their derivatives to R and C. This allows linkage in ‘rxode2’ to allow
  generalized log-likelihood in ‘nlmixr2’.
- This is a data like package and is likely not to change very much over
  time.
- Added a `NEWS.md` file to track changes to the package.
