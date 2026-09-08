#include "llik2.h"
#ifdef _OPENMP
#include <omp.h>
#endif

////////////////////////////////////////////////////////////////////////////////
// Frechet distribution -- gradients by Stan reverse-mode autodiff, exactly as
// the other families in this package are done.
struct llikFrechet_ll {
  const Eigen::VectorXd y_;
  llikFrechet_ll(const Eigen::VectorXd& y) : y_(y) { }
  template <typename T>
  Eigen::Matrix<T, -1, 1> operator()(const Eigen::Matrix<T, -1, 1>& theta) const {
    T alpha = theta[0];
    T sigma = theta[1];
    Eigen::Matrix<T, -1, 1> lp(y_.size());
    for (Eigen::Index n = 0; n < y_.size(); ++n) {
      lp[n] = frechet_lpdf(y_[n], alpha, sigma);
    }
    return lp;
  }
};

stanLl llik_llikFrechet(Eigen::VectorXd& y, Eigen::VectorXd& params) {
  rx_stan_math_thread_init_rev_autodiff();
  llikFrechet_ll f(y);
  Eigen::VectorXd fx;
  Eigen::Matrix<double, -1, -1> J;
  stan::math::jacobian(f, params, fx, J);
  stanLl ret;
  ret.fx = fx;
  ret.J  = J;
  return ret;
}

static inline void llikFrechetFull(double* ret, double x, double alpha, double sigma) {
#ifdef _OPENMP
  if (!omp_in_parallel()) {
    if (ret[0] == isFrechet &&
        ret[1] == x &&
        ret[2] == alpha &&
        ret[3] == sigma) return;
  }
#else
  if (ret[0] == isFrechet &&
        ret[1] == x &&
        ret[2] == alpha &&
        ret[3] == sigma) return;
#endif
  if (!R_finite(x) || !R_finite(alpha) || !R_finite(sigma)) {
    ret[0] = isFrechet;
    ret[1] = x;
    ret[2] = alpha;
    ret[3] = sigma;
    ret[4] = NA_REAL;
    ret[5] = NA_REAL;
    ret[6] = NA_REAL;
    return;
  }
  Eigen::VectorXd y(1);
  Eigen::VectorXd params(2);
  y(0) = x;
  params(0) = _smallIsNotZero(alpha);
  params(1) = _smallIsNotZero(sigma);
  stanLl ll = llik_llikFrechet(y, params);
  ret[0] = isFrechet;
  ret[1] = x;
  ret[2] = alpha;
  ret[3] = sigma;
  ret[4] = ll.fx(0);
  ret[5] = ll.J(0, 0);
  ret[6] = ll.J(0, 1);
  return;
}

//[[Rcpp::export]]
Rcpp::DataFrame llikFrechetInternal(Rcpp::NumericVector x, Rcpp::NumericVector alpha, Rcpp::NumericVector sigma) {
  NumericVector fx(x.size());
  NumericVector dAlpha(x.size());
  NumericVector dSigma(x.size());
  double cur[7];
  std::fill_n(cur, 7, 0.0);
  for (R_xlen_t j = x.size(); j--;) {
    llikFrechetFull(cur, x[j], alpha[j], sigma[j]);
    fx[j] = cur[4];
    dAlpha[j] = cur[5];
    dSigma[j] = cur[6];
  }
  return Rcpp::DataFrame::create(_["fx"]=fx,
                                 _["dAlpha"]=dAlpha,
                                 _["dSigma"]=dSigma);
}

extern "C" double rxLlikFrechet(double* ret, double x, double alpha, double sigma) {
  llikFrechetFull(ret, x, alpha, sigma);
  return ret[4];
}

extern "C" double rxLlikFrechetDAlpha(double* ret, double x, double alpha, double sigma) {
  llikFrechetFull(ret, x, alpha, sigma);
  return ret[5];
}

extern "C" double rxLlikFrechetDSigma(double* ret, double x, double alpha, double sigma) {
  llikFrechetFull(ret, x, alpha, sigma);
  return ret[6];
}
