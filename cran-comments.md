This update stops 'rxode2ll' from linking and loading the TBB library bundled
in 'RcppParallel', which it now uses for headers only (LinkingTo).  The
gcc-UBSAN check reports runtime errors inside that TBB library whenever it is
loaded, currently for 'rxode2', which imports this package.  Log-likelihoods
and gradients are unchanged.
