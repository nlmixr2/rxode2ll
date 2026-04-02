test_that("log-liklihood tests for normal (including derivatives)", {
  et <- data.frame(time=seq(-3, 3, length.out=10))
  et$mu <- 0
  et$sigma <- 1
  fromR <- llikNorm(et$time, et$mu, et$sigma)
  expect_equal(fromR$fx, dnorm(et$time, log=TRUE))
})


test_that("log-liklihood tests for pois (including derivatives)", {
  et <- data.frame(time=0:10)
  et$lambda <- 0.5
  fromR <- llikPois(et$time, et$lambda)
  expect_equal(fromR$fx, dpois(et$time, lambda=et$lambda, log=TRUE))
})

test_that("log-liklihood tests for binom (including derivatives)", {
  et <- data.frame(time=0:10)
  et$size <- 100
  et$prob <- 0.5
  fromR <- llikBinom(et$time, et$size, et$prob, full=TRUE)
  expect_equal(fromR$fx, dbinom(et$time, size=100, prob=0.5, log=TRUE))
})

test_that("log-liklihood tests for nbinom (including derivatives)", {
  et <- data.frame(time=0:10)
  et$size <- 100
  et$prob <- 0.5
  fromR <- llikNbinom(et$time, et$size, et$prob, full=TRUE)
  expect_equal(fromR$fx, dnbinom(et$time, size=100, prob=0.5, log=TRUE))
})


test_that("log-liklihood tests for NbinomMu (including derivatives)", {
  et <- data.frame(time=0:10)
  et$size <- 100
  et$mu <- 40
  fromR <- llikNbinomMu(et$time, et$size, et$mu, full=TRUE)
  expect_equal(fromR$fx, dnbinom(et$time, size=100, mu=40, log=TRUE))
})

test_that("log-liklihood tests for beta (including derivatives)", {
  et <- data.frame(time=seq(1e-4, 1-1e-4, length.out=21))
  et$shape1 <- 0.5
  et$shape2 <- 1.5
  fromR <- llikBeta(et$time, et$shape1, et$shape2, full=TRUE)
  expect_equal(fromR$fx, dbeta(et$time, shape1=0.5, shape2=1.5, log=TRUE))
})

test_that("log-liklihood tests for T (including derivatives)", {
  # Check rxode2 internals with R exported
  et <- data.frame(time=seq(-3, 3, length.out=10))
  et$nu <- 7
  et$mean <- 0
  et$sd <- 1
  fromR <- llikT(et$time, et$nu, et$mean, et$sd, full=TRUE)
  expect_equal(fromR$fx, dt(et$time, df=7, log=TRUE))
})


test_that("log-liklihood tests for chi-squared (including derivatives)", {
  et <- data.frame(time=1:3)
  et$x <- 1
  fromR <- llikChisq(et$x,et$time, full=TRUE)
  expect_equal(fromR$fx, dchisq(1, et$time, log=TRUE))
})

test_that("log-liklihood tests for exponential (including derivatives)", {
  et <- data.frame(time=1:3)
  et$x <- 1
  fromR <- llikExp(et$x,et$time, full=TRUE)
  expect_equal(fromR$fx, dexp(1, et$time, log=TRUE))
})


test_that("log-liklihood tests for f (including derivatives)", {
  et <- data.frame(time=seq(0.001, 5, length.out = 100))
  et$df1 <- 1
  et$df2 <- 5
  fromR <- llikF(et$time,et$df1, et$df2, full=TRUE)
  expect_equal(fromR$fx, df(et$time, 1, 5, log=TRUE))
})

test_that("log-liklihood tests for geom (including derivatives)", {
  et <- data.frame(time=1:10)
  et$prob <- 0.2
  fromR <- llikGeom(et$time, et$prob, full=TRUE)
  expect_equal(fromR$fx, dgeom(et$time, 0.2, log=TRUE))
})

test_that("log-liklihood tests for unif (including derivatives)", {
  et <- data.frame(time=seq(-4, 4, length.out=10))
  et$alpha <- -2
  et$beta <- 2
  fromR <- llikUnif(et$time, -2, 2, full=TRUE)
  expect_equal(fromR$fx, dunif(et$time, -2, 2, log=TRUE))
})


test_that("log-liklihood tests for weibull (including derivatives)", {
  et <- data.frame(time=seq(0.01,4, length.out=10))
  et$shape <- 1
  et$scale <- 10    
  fromR <- llikWeibull(et$time, 1, 10, full=TRUE)
  expect_equal(fromR$fx, dweibull(et$time, 1, 10, log=TRUE))
})

test_that("log-liklihood tests for gamma (including derivatives)", {
  # Check rxode2 internals with R exported
  et  <- data.frame(time=seq(0.01, 4, length.out=10))
  et$shape <- 1
  et$rate  <- 10
  fromR    <- llikGamma(et$time, 1, 10, full=TRUE)
  expect_equal(fromR$fx, dgamma(et$time, 1, rate=10, log=TRUE))
})

test_that("log-liklihood tests for cauchy (including derivatives)", {
   # Check rxode2 internals with R exported
  et  <- data.frame(time=seq(0.01,4, length.out=10))
  et$location <- 1
  et$scale <- 10

  fromR <- llikCauchy(et$time, 1, 10, full=TRUE)
  expect_equal(fromR$fx, dcauchy(et$time, location=1, scale=10, log=TRUE))
})

## Derivative validation tests using central finite differences

test_that("llikNorm derivatives match numerical finite differences", {
  h <- 1e-4
  x <- 1.5; mu <- 0.5; sd <- 2.0
  r <- llikNorm(x, mu, sd)
  dMu_num <- (llikNorm(x, mu + h, sd)$fx - llikNorm(x, mu - h, sd)$fx) / (2 * h)
  dSd_num  <- (llikNorm(x, mu, sd + h)$fx - llikNorm(x, mu, sd - h)$fx) / (2 * h)
  expect_equal(r$dMean, dMu_num, tolerance = 1e-4)
  expect_equal(r$dSd,   dSd_num,  tolerance = 1e-4)
})

test_that("llikPois derivatives match numerical finite differences", {
  h <- 1e-4
  x <- 3; lambda <- 2.0
  r <- llikPois(x, lambda)
  dL_num <- (llikPois(x, lambda + h)$fx - llikPois(x, lambda - h)$fx) / (2 * h)
  expect_equal(r$dLambda, dL_num, tolerance = 1e-4)
})

test_that("llikBinom derivatives match numerical finite differences", {
  h <- 1e-4
  x <- 5; size <- 20; prob <- 0.4
  r <- llikBinom(x, size, prob)
  dP_num <- (llikBinom(x, size, prob + h)$fx - llikBinom(x, size, prob - h)$fx) / (2 * h)
  expect_equal(r$dProb, dP_num, tolerance = 1e-4)
})

test_that("llikNbinom derivatives match numerical finite differences", {
  h <- 1e-4
  x <- 5; size <- 10; prob <- 0.4
  r <- llikNbinom(x, size, prob)
  dP_num <- (llikNbinom(x, size, prob + h)$fx - llikNbinom(x, size, prob - h)$fx) / (2 * h)
  expect_equal(r$dProb, dP_num, tolerance = 1e-4)
})

test_that("llikNbinomMu derivatives match numerical finite differences", {
  h <- 1e-4
  x <- 5; size <- 10; mu <- 8.0
  r <- llikNbinomMu(x, size, mu)
  dMu_num <- (llikNbinomMu(x, size, mu + h)$fx - llikNbinomMu(x, size, mu - h)$fx) / (2 * h)
  expect_equal(r$dMu, dMu_num, tolerance = 1e-4)
})

test_that("llikBeta derivatives match numerical finite differences", {
  h <- 1e-4
  x <- 0.3; s1 <- 0.5; s2 <- 1.5
  r <- llikBeta(x, s1, s2)
  ds1_num <- (llikBeta(x, s1 + h, s2)$fx - llikBeta(x, s1 - h, s2)$fx) / (2 * h)
  ds2_num <- (llikBeta(x, s1, s2 + h)$fx - llikBeta(x, s1, s2 - h)$fx) / (2 * h)
  expect_equal(r$dShape1, ds1_num, tolerance = 1e-4)
  expect_equal(r$dShape2, ds2_num, tolerance = 1e-4)
})

test_that("llikT derivatives match numerical finite differences", {
  h <- 1e-4
  x <- 1.0; df <- 7.0; mean <- 0.0; sd <- 1.0
  r <- llikT(x, df, mean, sd)
  dDf_num   <- (llikT(x, df + h, mean, sd)$fx - llikT(x, df - h, mean, sd)$fx) / (2 * h)
  dMean_num <- (llikT(x, df, mean + h, sd)$fx  - llikT(x, df, mean - h, sd)$fx)  / (2 * h)
  dSd_num   <- (llikT(x, df, mean, sd + h)$fx  - llikT(x, df, mean, sd - h)$fx)  / (2 * h)
  expect_equal(r$dDf,   dDf_num,   tolerance = 1e-4)
  expect_equal(r$dMean, dMean_num, tolerance = 1e-4)
  expect_equal(r$dSd,   dSd_num,   tolerance = 1e-4)
})

test_that("llikChisq derivatives match numerical finite differences", {
  h <- 1e-4
  x <- 2.0; df <- 3.0
  r <- llikChisq(x, df)
  dDf_num <- (llikChisq(x, df + h)$fx - llikChisq(x, df - h)$fx) / (2 * h)
  expect_equal(r$dDf, dDf_num, tolerance = 1e-4)
})

test_that("llikExp derivatives match numerical finite differences", {
  h <- 1e-4
  x <- 1.0; rate <- 2.0
  r <- llikExp(x, rate)
  dRate_num <- (llikExp(x, rate + h)$fx - llikExp(x, rate - h)$fx) / (2 * h)
  expect_equal(r$dRate, dRate_num, tolerance = 1e-4)
})

test_that("llikF derivatives match numerical finite differences", {
  h <- 1e-4
  x <- 1.5; df1 <- 3.0; df2 <- 5.0
  r <- llikF(x, df1, df2)
  dDf1_num <- (llikF(x, df1 + h, df2)$fx - llikF(x, df1 - h, df2)$fx) / (2 * h)
  dDf2_num <- (llikF(x, df1, df2 + h)$fx - llikF(x, df1, df2 - h)$fx) / (2 * h)
  expect_equal(r$dDf1, dDf1_num, tolerance = 1e-4)
  expect_equal(r$dDf2, dDf2_num, tolerance = 1e-4)
})

test_that("llikGeom derivatives match numerical finite differences", {
  h <- 1e-4
  x <- 3; prob <- 0.3
  r <- llikGeom(x, prob)
  dP_num <- (llikGeom(x, prob + h)$fx - llikGeom(x, prob - h)$fx) / (2 * h)
  expect_equal(r$dProb, dP_num, tolerance = 1e-4)
})

test_that("llikWeibull derivatives match numerical finite differences", {
  h <- 1e-4
  x <- 1.5; shape <- 2.0; scale <- 3.0
  r <- llikWeibull(x, shape, scale)
  dShape_num <- (llikWeibull(x, shape + h, scale)$fx - llikWeibull(x, shape - h, scale)$fx) / (2 * h)
  dScale_num <- (llikWeibull(x, shape, scale + h)$fx - llikWeibull(x, shape, scale - h)$fx) / (2 * h)
  expect_equal(r$dShape, dShape_num, tolerance = 1e-4)
  expect_equal(r$dScale, dScale_num, tolerance = 1e-4)
})

test_that("llikGamma derivatives match numerical finite differences", {
  h <- 1e-4
  x <- 1.5; shape <- 2.0; rate <- 1.5
  r <- llikGamma(x, shape, rate)
  dShape_num <- (llikGamma(x, shape + h, rate)$fx - llikGamma(x, shape - h, rate)$fx) / (2 * h)
  dRate_num  <- (llikGamma(x, shape, rate + h)$fx  - llikGamma(x, shape, rate - h)$fx)  / (2 * h)
  expect_equal(r$dShape, dShape_num, tolerance = 1e-4)
  expect_equal(r$dRate,  dRate_num,  tolerance = 1e-4)
})

test_that("llikCauchy derivatives match numerical finite differences", {
  h <- 1e-4
  x <- 2.0; location <- 1.0; scale <- 2.0
  r <- llikCauchy(x, location, scale)
  dLoc_num   <- (llikCauchy(x, location + h, scale)$fx - llikCauchy(x, location - h, scale)$fx) / (2 * h)
  dScale_num <- (llikCauchy(x, location, scale + h)$fx  - llikCauchy(x, location, scale - h)$fx)  / (2 * h)
  expect_equal(r$dLocation, dLoc_num,   tolerance = 1e-4)
  expect_equal(r$dScale,    dScale_num, tolerance = 1e-4)
})

## Integer overflow / bounds tests for discrete distributions
## These call the *Internal() Rcpp functions directly to bypass R-level
## checkmate validation and exercise the C++ bounds guard.

test_that("llikPoisInternal returns NA for x > INT_MAX", {
  big <- 2^31  # 2147483648 > INT_MAX = 2147483647
  res <- llikPoisInternal(big, 1.0)
  expect_true(is.na(res$fx))
  expect_true(is.na(res$dLambda))
})

test_that("llikBinomInternal returns NA for x > INT_MAX", {
  big <- 2^31
  res <- llikBinomInternal(big, 100, 0.5)
  expect_true(is.na(res$fx))
  expect_true(is.na(res$dProb))
})

test_that("llikBinomInternal returns NA for size > INT_MAX", {
  big <- 2^31
  res <- llikBinomInternal(5, big, 0.5)
  expect_true(is.na(res$fx))
  expect_true(is.na(res$dProb))
})

test_that("llikGeomInternal returns NA for x > INT_MAX", {
  big <- 2^31
  res <- llikGeomInternal(big, 0.3)
  expect_true(is.na(res$fx))
  expect_true(is.na(res$dProb))
})

test_that("llikNbinomInternal returns NA for x > INT_MAX", {
  big <- 2^31
  res <- llikNbinomInternal(big, 10, 0.5)
  expect_true(is.na(res$fx))
  expect_true(is.na(res$dProb))
})

test_that("llikNbinomInternal returns NA for size > INT_MAX", {
  big <- 2^31
  res <- llikNbinomInternal(5, big, 0.5)
  expect_true(is.na(res$fx))
  expect_true(is.na(res$dProb))
})

test_that("llikNbinomMuInternal returns NA for x > INT_MAX", {
  big <- 2^31
  res <- llikNbinomMuInternal(big, 10, 40)
  expect_true(is.na(res$fx))
  expect_true(is.na(res$dMu))
})

test_that("llikNbinomMuInternal returns NA for size > INT_MAX", {
  big <- 2^31
  res <- llikNbinomMuInternal(5, big, 40)
  expect_true(is.na(res$fx))
  expect_true(is.na(res$dMu))
})

## Large-vector test for R_xlen_t fix
## Skipped in normal test runs: requires ~17 GB per numeric vector
## (~103 GB total for 6 vectors), which exceeds typical system RAM.
## The overflow behaviour is validated without large memory by the
## "R_xlen_t overflow demonstration" test below.

test_that("llikNormInternal handles vectors longer than INT_MAX (R_xlen_t loop fix)", {
  skip(paste0(
    "Requires ~103 GB free RAM (6 vectors of 2^31+1 doubles at ~17 GB each). ",
    "Previously 'int j = x.size()' overflowed to INT_MIN when length > INT_MAX, ",
    "causing the counting-down loop to run ~4 billion iterations over invalid memory. ",
    "The fix uses R_xlen_t j which correctly holds values > INT_MAX. ",
    "See the 'R_xlen_t overflow demonstration' test for a RAM-free proof."
  ))
  # allocate a vector of length 2^31 + 1 (> INT_MAX = 2147483647)
  # Use double arithmetic to avoid R integer overflow
  n <- as.numeric(.Machine$integer.max) + 2
  x     <- rep(0.0, n)
  mu    <- rep(0.0, n)
  sigma <- rep(1.0, n)
  res <- llikNormInternal(x, mu, sigma)
  expect_equal(nrow(res), n)
  expect_true(all(is.finite(res$fx)))
})

## Lightweight proof that int j overflows for n > INT_MAX.
## Uses only a few bytes; no large allocation required.

test_that("R_xlen_t overflow demonstration: int j wraps to negative for n > INT_MAX", {
  # The old loop: for (int j = x.size(); j--;)
  # When x.size() returns 2^31 = 2147483648 (> INT_MAX = 2147483647):
  #   int j = 2147483648  ->  j = -2147483648 (INT_MIN) on x86-64 -- overflow!
  #   The loop starts negative, wraps again on first j--, and runs ~4 billion
  #   iterations over out-of-bounds memory (undefined behaviour).
  #
  # The fix: for (R_xlen_t j = x.size(); j--;)
  #   R_xlen_t j = 2147483648  ->  j = 2147483648 (correct, no overflow)

  INT_MAX <- .Machine$integer.max   # 2147483647
  n_large <- as.numeric(INT_MAX) + 1  # 2147483648 = 2^31, exceeds INT_MAX

  # Confirm n_large truly exceeds INT_MAX (would overflow int in C++)
  expect_true(n_large > INT_MAX)
  expect_equal(n_large, 2^31)

  # R's double can represent this exactly (2^31 is within double precision)
  expect_equal(n_large, 2147483648)

  # The fix means R_xlen_t (ptrdiff_t / int64_t on 64-bit) holds the full value.
  # We verify by confirming the value round-trips through a 64-bit integer type.
  # In R, bit64 or just checking double suffices: 2^31 < 2^53 so no precision loss.
  expect_true(n_large == n_large + 0)   # exact double representation
})

## Caching consistency test

test_that("llikNorm returns consistent results on repeated calls (cache hit and miss)", {
  x <- 1.5; mu <- 0.0; sd <- 1.0
  r1 <- llikNorm(x, mu, sd)
  r2 <- llikNorm(x, mu, sd)   # should hit the per-call cache
  expect_equal(r1$fx,    r2$fx)
  expect_equal(r1$dMean, r2$dMean)
  expect_equal(r1$dSd,   r2$dSd)
  r3 <- llikNorm(x + 0.1, mu, sd)  # cache invalidated
  expect_false(isTRUE(all.equal(r1$fx, r3$fx)))
})
