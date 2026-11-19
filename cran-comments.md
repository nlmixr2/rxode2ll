## Resubmission shortly after 2.0.17

'rxode2ll' 2.0.17 was accepted on 2026-09-09.  This quick update is needed so
that 'rxode2', which imports this package, stops being flagged by the gcc-UBSAN
additional check.  We apologize for the short interval.

## Why this is needed

'rxode2' 5.1.7 shows "gcc-UBSAN" under additional issues.  Every report in that
log is a runtime error inside the TBB library bundled with 'RcppParallel'
(`tbbmalloc/backref.cpp` and `tbb/arena.cpp`), and they fire whenever that
library is loaded, not from code in 'rxode2'.

Every compiled 'rxode2' model loads 'rxode2ll', and 'rxode2ll' linked and
loaded TBB.  It only needed TBB for the 'stan' autodiff tape observer, which it
does not rely on: each log-likelihood already creates the autodiff tape for its
own thread.

Version 2.0.18 keeps that observer (and the unused 'stan' 'reduce_sum' and
'map_rect' code) out of the build, so 'rxode2ll' neither links nor loads TBB and
uses 'RcppParallel' for headers only (LinkingTo).  The log-likelihoods and their
gradients are unchanged: all 27 functions, and 'rxode2' solves that call them
on 1, 2 and 4 threads, give identical results to 2.0.17.

The next 'rxode2' release (5.1.8) will require 'rxode2ll' (>= 2.0.18).

## Test environments

* local Ubuntu 24.04, R 4.6.1
* GitHub Actions: ubuntu-latest (devel, release, oldrel-1), macos-latest
  (release), windows-latest (release)

## R CMD check results

0 errors | 0 warnings | 2 notes

* "Days since last update: 5", explained above.
* "Compilation used the following non-portable flag(s):
  -mno-omit-leaf-frame-pointer" comes from the local R installation's compiler
  flags, not from this package.
