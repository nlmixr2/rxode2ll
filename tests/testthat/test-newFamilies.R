## The families added alongside the external-pointer export, checked against
## hand-written reference densities rather than against themselves.
##
## This is the check that matters for these: the log-density is a one-line Stan
## call, so the thing that can silently go wrong is the ORDER the parameters are
## passed in.  A transposed pair still returns a finite number and still
## differentiates cleanly -- it is simply the wrong distribution.  Comparing fx
## against an independently written density catches that; comparing the
## derivatives against central differences of the SAME reference catches a
## mis-indexed ret[] slot.

.gradCheck <- function(got, par, rf, tol = 1e-5) {
  .an <- as.numeric(got[-1])
  .h <- 1e-6
  .nu <- vapply(seq_along(par), function(.i) {
    .pp <- par; .pm <- par
    .pp[.i] <- .pp[.i] + .h; .pm[.i] <- .pm[.i] - .h
    (rf(.pp) - rf(.pm)) / (2 * .h)
  }, numeric(1))
  expect_equal(.an, .nu, tolerance = tol)
}

test_that("lognormal matches dlnorm and its derivatives", {
  .x <- 1.3; .p <- c(0.2, 0.7)
  .rf <- function(q) stats::dlnorm(.x, q[1], q[2], log = TRUE)
  .g <- unlist(llikLnorm(.x, .p[1], .p[2]))
  expect_equal(.g[[1]], .rf(.p))
  .gradCheck(.g, .p, .rf)
})

test_that("logistic matches dlogis and its derivatives", {
  .x <- 1.3; .p <- c(0.1, 1.2)
  .rf <- function(q) stats::dlogis(.x, q[1], q[2], log = TRUE)
  .g <- unlist(llikLogis(.x, .p[1], .p[2]))
  expect_equal(.g[[1]], .rf(.p))
  .gradCheck(.g, .p, .rf)
})

test_that("gumbel, double exponential and rayleigh match closed forms", {
  .x <- 1.3
  .p <- c(0.3, 0.9)
  .rf <- function(q) { .z <- (.x - q[1]) / q[2]; -log(q[2]) - (.z + exp(-.z)) }
  .g <- unlist(llikGumbel(.x, .p[1], .p[2]))
  expect_equal(.g[[1]], .rf(.p)); .gradCheck(.g, .p, .rf)

  .p <- c(0.2, 0.8)
  .rf <- function(q) -log(2 * q[2]) - abs(.x - q[1]) / q[2]
  .g <- unlist(llikDblExp(.x, .p[1], .p[2]))
  expect_equal(.g[[1]], .rf(.p)); .gradCheck(.g, .p, .rf)

  .p <- 0.9
  .rf <- function(q) log(.x) - 2 * log(q[1]) - .x^2 / (2 * q[1]^2)
  .g <- unlist(llikRayleigh(.x, .p[1]))
  expect_equal(.g[[1]], .rf(.p)); .gradCheck(.g, .p, .rf)
})

test_that("the inverse-gamma family matches closed forms", {
  .x <- 1.3
  .p <- c(2.5, 1.4)
  .rf <- function(q) q[1] * log(q[2]) - lgamma(q[1]) - (q[1] + 1) * log(.x) - q[2] / .x
  .g <- unlist(llikInvGamma(.x, .p[1], .p[2]))
  expect_equal(.g[[1]], .rf(.p)); .gradCheck(.g, .p, .rf)

  .p <- 3.2
  .rf <- function(q) -lgamma(q[1] / 2) - (q[1] / 2) * log(2) -
    (q[1] / 2 + 1) * log(.x) - 1 / (2 * .x)
  .g <- unlist(llikInvChisq(.x, .p[1]))
  expect_equal(.g[[1]], .rf(.p)); .gradCheck(.g, .p, .rf)

  .p <- c(3.0, 0.8)
  .rf <- function(q) (q[1] / 2) * log(q[1] / 2) + q[1] * log(q[2]) -
    lgamma(q[1] / 2) - (q[1] / 2 + 1) * log(.x) - q[1] * q[2]^2 / (2 * .x)
  .g <- unlist(llikScaledInvChisq(.x, .p[1], .p[2]))
  expect_equal(.g[[1]], .rf(.p)); .gradCheck(.g, .p, .rf)
})

test_that("frechet and the pareto family match closed forms", {
  .x <- 1.3
  .p <- c(2.2, 1.1)
  .rf <- function(q) log(q[1]) - log(q[2]) + (-q[1] - 1) * log(.x / q[2]) -
    (.x / q[2])^(-q[1])
  .g <- unlist(llikFrechet(.x, .p[1], .p[2]))
  expect_equal(.g[[1]], .rf(.p)); .gradCheck(.g, .p, .rf)

  # pareto is defined for x >= y_min
  .p <- c(0.8, 2.3)
  .rf <- function(q) log(q[2]) + q[2] * log(q[1]) - (q[2] + 1) * log(.x)
  .g <- unlist(llikPareto(.x, .p[1], .p[2]))
  expect_equal(.g[[1]], .rf(.p)); .gradCheck(.g, .p, .rf)

  .p <- c(0.0, 1.2, 2.0)
  .rf <- function(q) log(q[3]) - log(q[2]) - (q[3] + 1) * log1p((.x - q[1]) / q[2])
  .g <- unlist(llikParetoType2(.x, .p[1], .p[2], .p[3]))
  expect_equal(.g[[1]], .rf(.p)); .gradCheck(.g, .p, .rf)
})

test_that("beta proportion matches its closed form", {
  .x <- 0.4; .p <- c(0.5, 6)
  .rf <- function(q) lgamma(q[2]) - lgamma(q[1] * q[2]) - lgamma((1 - q[1]) * q[2]) +
    (q[1] * q[2] - 1) * log(.x) + ((1 - q[1]) * q[2] - 1) * log(1 - .x)
  .g <- unlist(llikBetaProportion(.x, .p[1], .p[2]))
  expect_equal(.g[[1]], .rf(.p))
  .gradCheck(.g, .p, .rf, tol = 1e-4)
})

test_that("the external pointer list is complete and append-only", {
  .p <- .rxode2llPtr()
  expect_true(is.list(.p))
  # one entry per declaration in src/llik.h; the header reads by fixed index, so
  # a shrink or a reorder would silently hand a consumer the wrong function
  expect_gte(length(.p), 74L)
  expect_true(all(vapply(.p, function(.z) class(.z) == "externalptr", logical(1))))
})
