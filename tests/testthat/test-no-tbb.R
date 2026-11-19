# Loading TBB (RcppParallel's library) is what CRAN's gcc-UBSAN check reports,
# so neither loading this package nor its gradients may load it.
test_that("gradients do not load the TBB library", {
  skip_if_not(file.exists("/proc/self/maps"))
  .r <- llikNorm(c(-1, 0.5, 2), mean = 1, sd = 2, full = TRUE)
  expect_true(all(is.finite(.r$dMean)))
  expect_false("RcppParallel" %in% loadedNamespaces())
  expect_false(any(grepl("libtbb", readLines("/proc/self/maps"), fixed = TRUE)))
})
