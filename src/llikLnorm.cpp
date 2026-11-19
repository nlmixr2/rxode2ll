#include "llik2.h"
#ifdef _OPENMP
#include <omp.h>
#endif

////////////////////////////////////////////////////////////////////////////////
// Lnorm distribution -- gradients by Stan reverse-mode autodiff, exactly as
// the other families in this package are done.
struct llikLnorm_ll {
  const Eigen::VectorXd y_;
  llikLnorm_ll(const Eigen::VectorXd& y) : y_(y) { }
  template <typename T>
  Eigen::Matrix<T, -1, 1> operator()(const Eigen::Matrix<T, -1, 1>& theta) const {
    T meanlog = theta[0];
    T sdlog = theta[1];
    Eigen::Matrix<T, -1, 1> lp(y_.size());
    for (Eigen::Index n = 0; n < y_.size(); ++n) {
      lp[n] = lognormal_lpdf(y_[n], meanlog, sdlog);
    }
    return lp;
  }
};

stanLl llik_llikLnorm(Eigen::VectorXd& y, Eigen::VectorXd& params) {
  rx_stan_math_thread_init_rev_autodiff();
  llikLnorm_ll f(y);
  Eigen::VectorXd fx;
  Eigen::Matrix<double, -1, -1> J;
  stan::math::jacobian(f, params, fx, J);
  stanLl ret;
  ret.fx = fx;
  ret.J  = J;
  return ret;
}

static inline void llikLnormFull(double* ret, double x, double meanlog, double sdlog) {
#ifdef _OPENMP
  if (!omp_in_parallel()) {
    if (ret[0] == isLnorm &&
        ret[1] == x &&
        ret[2] == meanlog &&
        ret[3] == sdlog) return;
  }
#else
  if (ret[0] == isLnorm &&
        ret[1] == x &&
        ret[2] == meanlog &&
        ret[3] == sdlog) return;
#endif
  if (!R_finite(x) || !R_finite(meanlog) || !R_finite(sdlog)) {
    ret[0] = isLnorm;
    ret[1] = x;
    ret[2] = meanlog;
    ret[3] = sdlog;
    ret[4] = NA_REAL;
    ret[5] = NA_REAL;
    ret[6] = NA_REAL;
    return;
  }
  Eigen::VectorXd y(1);
  Eigen::VectorXd params(2);
  y(0) = x;
  params(0) = meanlog;
  params(1) = _smallIsNotZero(sdlog);
  stanLl ll = llik_llikLnorm(y, params);
  ret[0] = isLnorm;
  ret[1] = x;
  ret[2] = meanlog;
  ret[3] = sdlog;
  ret[4] = ll.fx(0);
  ret[5] = ll.J(0, 0);
  ret[6] = ll.J(0, 1);
  return;
}

//[[Rcpp::export]]
Rcpp::DataFrame llikLnormInternal(Rcpp::NumericVector x, Rcpp::NumericVector meanlog, Rcpp::NumericVector sdlog) {
  NumericVector fx(x.size());
  NumericVector dMeanlog(x.size());
  NumericVector dSdlog(x.size());
  double cur[7];
  std::fill_n(cur, 7, 0.0);
  for (R_xlen_t j = x.size(); j--;) {
    llikLnormFull(cur, x[j], meanlog[j], sdlog[j]);
    fx[j] = cur[4];
    dMeanlog[j] = cur[5];
    dSdlog[j] = cur[6];
  }
  return Rcpp::DataFrame::create(_["fx"]=fx,
                                 _["dMeanlog"]=dMeanlog,
                                 _["dSdlog"]=dSdlog);
}

extern "C" double rxLlikLnorm(double* ret, double x, double meanlog, double sdlog) {
  llikLnormFull(ret, x, meanlog, sdlog);
  return ret[4];
}

extern "C" double rxLlikLnormDMeanlog(double* ret, double x, double meanlog, double sdlog) {
  llikLnormFull(ret, x, meanlog, sdlog);
  return ret[5];
}

extern "C" double rxLlikLnormDSdlog(double* ret, double x, double meanlog, double sdlog) {
  llikLnormFull(ret, x, meanlog, sdlog);
  return ret[6];
}
