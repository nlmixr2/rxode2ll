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
