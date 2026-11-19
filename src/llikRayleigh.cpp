#include "llik2.h"
#ifdef _OPENMP
#include <omp.h>
#endif

////////////////////////////////////////////////////////////////////////////////
// Rayleigh distribution -- gradients by Stan reverse-mode autodiff, exactly as
// the other families in this package are done.
struct llikRayleigh_ll {
  const Eigen::VectorXd y_;
  llikRayleigh_ll(const Eigen::VectorXd& y) : y_(y) { }
  template <typename T>
  Eigen::Matrix<T, -1, 1> operator()(const Eigen::Matrix<T, -1, 1>& theta) const {
    T sigma = theta[0];
    Eigen::Matrix<T, -1, 1> lp(y_.size());
    for (Eigen::Index n = 0; n < y_.size(); ++n) {
      lp[n] = rayleigh_lpdf(y_[n], sigma);
    }
    return lp;
  }
};

stanLl llik_llikRayleigh(Eigen::VectorXd& y, Eigen::VectorXd& params) {
  rx_stan_math_thread_init_rev_autodiff();
  llikRayleigh_ll f(y);
  Eigen::VectorXd fx;
  Eigen::Matrix<double, -1, -1> J;
  stan::math::jacobian(f, params, fx, J);
  stanLl ret;
  ret.fx = fx;
  ret.J  = J;
  return ret;
}

static inline void llikRayleighFull(double* ret, double x, double sigma) {
#ifdef _OPENMP
  if (!omp_in_parallel()) {
    if (ret[0] == isRayleigh &&
        ret[1] == x &&
        ret[2] == sigma) return;
  }
#else
  if (ret[0] == isRayleigh &&
        ret[1] == x &&
        ret[2] == sigma) return;
#endif
  if (!R_finite(x) || !R_finite(sigma)) {
    ret[0] = isRayleigh;
    ret[1] = x;
    ret[2] = sigma;
    ret[3] = NA_REAL;
    ret[4] = NA_REAL;
    return;
  }
  Eigen::VectorXd y(1);
  Eigen::VectorXd params(1);
  y(0) = x;
  params(0) = _smallIsNotZero(sigma);
  stanLl ll = llik_llikRayleigh(y, params);
  ret[0] = isRayleigh;
  ret[1] = x;
  ret[2] = sigma;
  ret[3] = ll.fx(0);
  ret[4] = ll.J(0, 0);
  return;
}

//[[Rcpp::export]]
Rcpp::DataFrame llikRayleighInternal(Rcpp::NumericVector x, Rcpp::NumericVector sigma) {
  NumericVector fx(x.size());
  NumericVector dSigma(x.size());
  double cur[5];
  std::fill_n(cur, 5, 0.0);
  for (R_xlen_t j = x.size(); j--;) {
    llikRayleighFull(cur, x[j], sigma[j]);
    fx[j] = cur[3];
    dSigma[j] = cur[4];
  }
  return Rcpp::DataFrame::create(_["fx"]=fx,
                                 _["dSigma"]=dSigma);
}

extern "C" double rxLlikRayleigh(double* ret, double x, double sigma) {
  llikRayleighFull(ret, x, sigma);
  return ret[3];
}

extern "C" double rxLlikRayleighDSigma(double* ret, double x, double sigma) {
  llikRayleighFull(ret, x, sigma);
  return ret[4];
}
