#include "llik2.h"
#ifdef _OPENMP
#include <omp.h>
#endif

////////////////////////////////////////////////////////////////////////////////
// Pareto distribution -- gradients by Stan reverse-mode autodiff, exactly as
// the other families in this package are done.
struct llikPareto_ll {
  const Eigen::VectorXd y_;
  llikPareto_ll(const Eigen::VectorXd& y) : y_(y) { }
  template <typename T>
  Eigen::Matrix<T, -1, 1> operator()(const Eigen::Matrix<T, -1, 1>& theta) const {
    T yMin = theta[0];
    T alpha = theta[1];
    Eigen::Matrix<T, -1, 1> lp(y_.size());
    for (Eigen::Index n = 0; n < y_.size(); ++n) {
      lp[n] = pareto_lpdf(y_[n], yMin, alpha);
    }
    return lp;
  }
};

stanLl llik_llikPareto(Eigen::VectorXd& y, Eigen::VectorXd& params) {
  rx_stan_math_thread_init_rev_autodiff();
  llikPareto_ll f(y);
  Eigen::VectorXd fx;
  Eigen::Matrix<double, -1, -1> J;
  stan::math::jacobian(f, params, fx, J);
  stanLl ret;
  ret.fx = fx;
  ret.J  = J;
  return ret;
}

static inline void llikParetoFull(double* ret, double x, double yMin, double alpha) {
#ifdef _OPENMP
  if (!omp_in_parallel()) {
    if (ret[0] == isPareto &&
        ret[1] == x &&
        ret[2] == yMin &&
        ret[3] == alpha) return;
  }
#else
  if (ret[0] == isPareto &&
        ret[1] == x &&
        ret[2] == yMin &&
        ret[3] == alpha) return;
#endif
  if (!R_finite(x) || !R_finite(yMin) || !R_finite(alpha)) {
    ret[0] = isPareto;
    ret[1] = x;
    ret[2] = yMin;
    ret[3] = alpha;
    ret[4] = NA_REAL;
    ret[5] = NA_REAL;
    ret[6] = NA_REAL;
    return;
  }
  Eigen::VectorXd y(1);
  Eigen::VectorXd params(2);
  y(0) = x;
  params(0) = _smallIsNotZero(yMin);
  params(1) = _smallIsNotZero(alpha);
  stanLl ll = llik_llikPareto(y, params);
  ret[0] = isPareto;
  ret[1] = x;
  ret[2] = yMin;
  ret[3] = alpha;
  ret[4] = ll.fx(0);
  ret[5] = ll.J(0, 0);
  ret[6] = ll.J(0, 1);
  return;
}

//[[Rcpp::export]]
Rcpp::DataFrame llikParetoInternal(Rcpp::NumericVector x, Rcpp::NumericVector yMin, Rcpp::NumericVector alpha) {
  NumericVector fx(x.size());
  NumericVector dYMin(x.size());
  NumericVector dAlpha(x.size());
  double cur[7];
  std::fill_n(cur, 7, 0.0);
  for (R_xlen_t j = x.size(); j--;) {
    llikParetoFull(cur, x[j], yMin[j], alpha[j]);
    fx[j] = cur[4];
    dYMin[j] = cur[5];
    dAlpha[j] = cur[6];
  }
  return Rcpp::DataFrame::create(_["fx"]=fx,
                                 _["dYMin"]=dYMin,
                                 _["dAlpha"]=dAlpha);
}

extern "C" double rxLlikPareto(double* ret, double x, double yMin, double alpha) {
  llikParetoFull(ret, x, yMin, alpha);
  return ret[4];
}

extern "C" double rxLlikParetoDYMin(double* ret, double x, double yMin, double alpha) {
  llikParetoFull(ret, x, yMin, alpha);
  return ret[5];
}

extern "C" double rxLlikParetoDAlpha(double* ret, double x, double yMin, double alpha) {
  llikParetoFull(ret, x, yMin, alpha);
  return ret[6];
}
