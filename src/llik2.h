//#undef NDEBUG
#ifndef NDEBUG
#define NDEBUG // just in case
#endif
#define USE_FC_LEN_T
#define STRICT_R_HEADERS
#include <stan/math.hpp>

#include <stan/math/rev/core/chainablestack.hpp>
// -----------------------------------------------------------------------------
// Stan Math reverse-mode autodiff is thread-local. When called from OpenMP worker
// threads (e.g., rxode2 parallel solves), each thread must initialize its AD tape
// before using reverse-mode functions like jacobian()/gradient().
// -----------------------------------------------------------------------------
static inline void rx_stan_math_thread_init_rev_autodiff() {
#if defined(STAN_THREADS) || defined(_OPENMP)
  // A per-thread ChainableStack ensures Stan reverse-mode autodiff is initialized
  // for OpenMP worker threads before calling jacobian()/gradient(), etc.
  static thread_local stan::math::ChainableStack tls_ad_stack;
  (void)tls_ad_stack;
#endif
}

#ifndef NDEBUG
#define NDEBUG // just in case
#endif
#include <Rcpp.h>
#include <RcppEigen.h>
#include "llik.h"
// [[Rcpp::depends(RcppEigen)]]
using namespace Rcpp;

#define isNorm 8.0
#define isPois 1.0
#define isBinom 2.0
#define isBeta 3.0
#define isT 4.0
#define isChisq 5.0
#define isExp 6.0
#define isF 7.0
#define isGeom 9.0
#define isUnif 10.0
#define isWeibull 11.0
#define isGamma 12.0
#define isCauchy 13.0
#define isNbinomMu 14.0
#define isNbinom 15.0

typedef struct stanLl {
  Eigen::VectorXd fx;
  Eigen::Matrix<double, -1, -1> J;
} stanLl;

#define _smallIsOne(x) ((x) < sqrt(DBL_EPSILON) ? 1 : (x))
#define _smallIsNotZero(x) (fabs(x) < sqrt(DBL_EPSILON) ? sqrt(DBL_EPSILON) : (x))
#define _parIsProb(x) ((x) < sqrt(DBL_EPSILON) ? sqrt(DBL_EPSILON): ((x) > 0.999999999999999 ? 0.999999999999999 :(x)))
