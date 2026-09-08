
## Generated wrappers for the Stan-backed families added alongside the
## external-pointer export.  Same shape as llikGamma() above: validate,
## recycle into a data.frame, call the compiled Internal, optionally bind.

#' log likelihood of the Lnorm distribution and its derivatives (from stan)
#'
#' @param x Observation
#' @param meanlog distribution parameter
#' @param sdlog distribution parameter
#' @param full return the input parameters alongside the result
#' @return data frame with `fx` and the derivative of each parameter
#' @export
llikLnorm <- function(x, meanlog, sdlog, full=FALSE) {
  checkmate::assertNumeric(x, min.len=0, any.missing=FALSE, finite=TRUE)
  checkmate::assertNumeric(meanlog, min.len=0, any.missing=FALSE, finite=TRUE)
  checkmate::assertNumeric(sdlog, min.len=0, lower=0, any.missing=FALSE, finite=TRUE)
  .d <- try(data.frame(x=x, meanlog=meanlog, sdlog=sdlog), silent=TRUE)
  if (inherits(.d, "try-error")) {
    stop("incompatible dimensions for x, meanlog, sdlog", call.=FALSE)
  }
  .ret <- llikLnormInternal(.d$x, .d$meanlog, .d$sdlog)
  if (full) .ret <- cbind(.d, .ret)
  .ret
}

#' log likelihood of the Logis distribution and its derivatives (from stan)
#'
#' @param x Observation
#' @param location distribution parameter
#' @param scale distribution parameter
#' @param full return the input parameters alongside the result
#' @return data frame with `fx` and the derivative of each parameter
#' @export
llikLogis <- function(x, location, scale, full=FALSE) {
  checkmate::assertNumeric(x, min.len=0, any.missing=FALSE, finite=TRUE)
  checkmate::assertNumeric(location, min.len=0, any.missing=FALSE, finite=TRUE)
  checkmate::assertNumeric(scale, min.len=0, lower=0, any.missing=FALSE, finite=TRUE)
  .d <- try(data.frame(x=x, location=location, scale=scale), silent=TRUE)
  if (inherits(.d, "try-error")) {
    stop("incompatible dimensions for x, location, scale", call.=FALSE)
  }
  .ret <- llikLogisInternal(.d$x, .d$location, .d$scale)
  if (full) .ret <- cbind(.d, .ret)
  .ret
}

#' log likelihood of the Gumbel distribution and its derivatives (from stan)
#'
#' @param x Observation
#' @param mu distribution parameter
#' @param beta distribution parameter
#' @param full return the input parameters alongside the result
#' @return data frame with `fx` and the derivative of each parameter
#' @export
llikGumbel <- function(x, mu, beta, full=FALSE) {
  checkmate::assertNumeric(x, min.len=0, any.missing=FALSE, finite=TRUE)
  checkmate::assertNumeric(mu, min.len=0, any.missing=FALSE, finite=TRUE)
  checkmate::assertNumeric(beta, min.len=0, lower=0, any.missing=FALSE, finite=TRUE)
  .d <- try(data.frame(x=x, mu=mu, beta=beta), silent=TRUE)
  if (inherits(.d, "try-error")) {
    stop("incompatible dimensions for x, mu, beta", call.=FALSE)
  }
  .ret <- llikGumbelInternal(.d$x, .d$mu, .d$beta)
  if (full) .ret <- cbind(.d, .ret)
  .ret
}

#' log likelihood of the DblExp distribution and its derivatives (from stan)
#'
#' @param x Observation
#' @param mu distribution parameter
#' @param sigma distribution parameter
#' @param full return the input parameters alongside the result
#' @return data frame with `fx` and the derivative of each parameter
#' @export
llikDblExp <- function(x, mu, sigma, full=FALSE) {
  checkmate::assertNumeric(x, min.len=0, any.missing=FALSE, finite=TRUE)
  checkmate::assertNumeric(mu, min.len=0, any.missing=FALSE, finite=TRUE)
  checkmate::assertNumeric(sigma, min.len=0, lower=0, any.missing=FALSE, finite=TRUE)
  .d <- try(data.frame(x=x, mu=mu, sigma=sigma), silent=TRUE)
  if (inherits(.d, "try-error")) {
    stop("incompatible dimensions for x, mu, sigma", call.=FALSE)
  }
  .ret <- llikDblExpInternal(.d$x, .d$mu, .d$sigma)
  if (full) .ret <- cbind(.d, .ret)
  .ret
}

#' log likelihood of the InvGamma distribution and its derivatives (from stan)
#'
#' @param x Observation
#' @param alpha distribution parameter
#' @param beta distribution parameter
#' @param full return the input parameters alongside the result
#' @return data frame with `fx` and the derivative of each parameter
#' @export
llikInvGamma <- function(x, alpha, beta, full=FALSE) {
  checkmate::assertNumeric(x, min.len=0, any.missing=FALSE, finite=TRUE)
  checkmate::assertNumeric(alpha, min.len=0, lower=0, any.missing=FALSE, finite=TRUE)
  checkmate::assertNumeric(beta, min.len=0, lower=0, any.missing=FALSE, finite=TRUE)
  .d <- try(data.frame(x=x, alpha=alpha, beta=beta), silent=TRUE)
  if (inherits(.d, "try-error")) {
    stop("incompatible dimensions for x, alpha, beta", call.=FALSE)
  }
  .ret <- llikInvGammaInternal(.d$x, .d$alpha, .d$beta)
  if (full) .ret <- cbind(.d, .ret)
  .ret
}

#' log likelihood of the InvChisq distribution and its derivatives (from stan)
#'
#' @param x Observation
#' @param nu distribution parameter
#' @param full return the input parameters alongside the result
#' @return data frame with `fx` and the derivative of each parameter
#' @export
llikInvChisq <- function(x, nu, full=FALSE) {
  checkmate::assertNumeric(x, min.len=0, any.missing=FALSE, finite=TRUE)
  checkmate::assertNumeric(nu, min.len=0, lower=0, any.missing=FALSE, finite=TRUE)
  .d <- try(data.frame(x=x, nu=nu), silent=TRUE)
  if (inherits(.d, "try-error")) {
    stop("incompatible dimensions for x, nu", call.=FALSE)
  }
  .ret <- llikInvChisqInternal(.d$x, .d$nu)
  if (full) .ret <- cbind(.d, .ret)
  .ret
}

#' log likelihood of the ScaledInvChisq distribution and its derivatives (from stan)
#'
#' @param x Observation
#' @param nu distribution parameter
#' @param sigma distribution parameter
#' @param full return the input parameters alongside the result
#' @return data frame with `fx` and the derivative of each parameter
#' @export
llikScaledInvChisq <- function(x, nu, sigma, full=FALSE) {
  checkmate::assertNumeric(x, min.len=0, any.missing=FALSE, finite=TRUE)
  checkmate::assertNumeric(nu, min.len=0, lower=0, any.missing=FALSE, finite=TRUE)
  checkmate::assertNumeric(sigma, min.len=0, lower=0, any.missing=FALSE, finite=TRUE)
  .d <- try(data.frame(x=x, nu=nu, sigma=sigma), silent=TRUE)
  if (inherits(.d, "try-error")) {
    stop("incompatible dimensions for x, nu, sigma", call.=FALSE)
  }
  .ret <- llikScaledInvChisqInternal(.d$x, .d$nu, .d$sigma)
  if (full) .ret <- cbind(.d, .ret)
  .ret
}

#' log likelihood of the Frechet distribution and its derivatives (from stan)
#'
#' @param x Observation
#' @param alpha distribution parameter
#' @param sigma distribution parameter
#' @param full return the input parameters alongside the result
#' @return data frame with `fx` and the derivative of each parameter
#' @export
llikFrechet <- function(x, alpha, sigma, full=FALSE) {
  checkmate::assertNumeric(x, min.len=0, any.missing=FALSE, finite=TRUE)
  checkmate::assertNumeric(alpha, min.len=0, lower=0, any.missing=FALSE, finite=TRUE)
  checkmate::assertNumeric(sigma, min.len=0, lower=0, any.missing=FALSE, finite=TRUE)
  .d <- try(data.frame(x=x, alpha=alpha, sigma=sigma), silent=TRUE)
  if (inherits(.d, "try-error")) {
    stop("incompatible dimensions for x, alpha, sigma", call.=FALSE)
  }
  .ret <- llikFrechetInternal(.d$x, .d$alpha, .d$sigma)
  if (full) .ret <- cbind(.d, .ret)
  .ret
}

#' log likelihood of the Rayleigh distribution and its derivatives (from stan)
#'
#' @param x Observation
#' @param sigma distribution parameter
#' @param full return the input parameters alongside the result
#' @return data frame with `fx` and the derivative of each parameter
#' @export
llikRayleigh <- function(x, sigma, full=FALSE) {
  checkmate::assertNumeric(x, min.len=0, any.missing=FALSE, finite=TRUE)
  checkmate::assertNumeric(sigma, min.len=0, lower=0, any.missing=FALSE, finite=TRUE)
  .d <- try(data.frame(x=x, sigma=sigma), silent=TRUE)
  if (inherits(.d, "try-error")) {
    stop("incompatible dimensions for x, sigma", call.=FALSE)
  }
  .ret <- llikRayleighInternal(.d$x, .d$sigma)
  if (full) .ret <- cbind(.d, .ret)
  .ret
}

#' log likelihood of the Pareto distribution and its derivatives (from stan)
#'
#' @param x Observation
#' @param yMin distribution parameter
#' @param alpha distribution parameter
#' @param full return the input parameters alongside the result
#' @return data frame with `fx` and the derivative of each parameter
#' @export
llikPareto <- function(x, yMin, alpha, full=FALSE) {
  checkmate::assertNumeric(x, min.len=0, any.missing=FALSE, finite=TRUE)
  checkmate::assertNumeric(yMin, min.len=0, lower=0, any.missing=FALSE, finite=TRUE)
  checkmate::assertNumeric(alpha, min.len=0, lower=0, any.missing=FALSE, finite=TRUE)
  .d <- try(data.frame(x=x, yMin=yMin, alpha=alpha), silent=TRUE)
  if (inherits(.d, "try-error")) {
    stop("incompatible dimensions for x, yMin, alpha", call.=FALSE)
  }
  .ret <- llikParetoInternal(.d$x, .d$yMin, .d$alpha)
  if (full) .ret <- cbind(.d, .ret)
  .ret
}

#' log likelihood of the ParetoType2 distribution and its derivatives (from stan)
#'
#' @param x Observation
#' @param mu distribution parameter
#' @param lambda distribution parameter
#' @param alpha distribution parameter
#' @param full return the input parameters alongside the result
#' @return data frame with `fx` and the derivative of each parameter
#' @export
llikParetoType2 <- function(x, mu, lambda, alpha, full=FALSE) {
  checkmate::assertNumeric(x, min.len=0, any.missing=FALSE, finite=TRUE)
  checkmate::assertNumeric(mu, min.len=0, any.missing=FALSE, finite=TRUE)
  checkmate::assertNumeric(lambda, min.len=0, lower=0, any.missing=FALSE, finite=TRUE)
  checkmate::assertNumeric(alpha, min.len=0, lower=0, any.missing=FALSE, finite=TRUE)
  .d <- try(data.frame(x=x, mu=mu, lambda=lambda, alpha=alpha), silent=TRUE)
  if (inherits(.d, "try-error")) {
    stop("incompatible dimensions for x, mu, lambda, alpha", call.=FALSE)
  }
  .ret <- llikParetoType2Internal(.d$x, .d$mu, .d$lambda, .d$alpha)
  if (full) .ret <- cbind(.d, .ret)
  .ret
}

#' log likelihood of the BetaProportion distribution and its derivatives (from stan)
#'
#' @param x Observation
#' @param mu distribution parameter
#' @param kappa distribution parameter
#' @param full return the input parameters alongside the result
#' @return data frame with `fx` and the derivative of each parameter
#' @export
llikBetaProportion <- function(x, mu, kappa, full=FALSE) {
  checkmate::assertNumeric(x, min.len=0, any.missing=FALSE, finite=TRUE)
  checkmate::assertNumeric(mu, min.len=0, lower=0, any.missing=FALSE, finite=TRUE)
  checkmate::assertNumeric(kappa, min.len=0, lower=0, any.missing=FALSE, finite=TRUE)
  .d <- try(data.frame(x=x, mu=mu, kappa=kappa), silent=TRUE)
  if (inherits(.d, "try-error")) {
    stop("incompatible dimensions for x, mu, kappa", call.=FALSE)
  }
  .ret <- llikBetaProportionInternal(.d$x, .d$mu, .d$kappa)
  if (full) .ret <- cbind(.d, .ret)
  .ret
}
