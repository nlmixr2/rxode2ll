#include "llik2.h"
#ifdef _OPENMP
#include <omp.h>
#endif

////////////////////////////////////////////////////////////////////////////////
// BetaProportion distribution -- gradients by Stan reverse-mode autodiff, exactly as
// the other families in this package are done.
struct llikBetaProportion_ll {
  const Eigen::VectorXd y_;
  llikBetaProportion_ll(const Eigen::VectorXd& y) : y_(y) { }
  template <typename T>
  Eigen::Matrix<T, -1, 1> operator()(const Eigen::Matrix<T, -1, 1>& theta) const {
    T mu = theta[0];
    T kappa = theta[1];
    Eigen::Matrix<T, -1, 1> lp(y_.size());
    for (Eigen::Index n = 0; n < y_.size(); ++n) {
      lp[n] = beta_proportion_lpdf(y_[n], mu, kappa);
    }
    return lp;
  }
};

stanLl llik_llikBetaProportion(Eigen::VectorXd& y, Eigen::VectorXd& params) {
  rx_stan_math_thread_init_rev_autodiff();
  llikBetaProportion_ll f(y);
  Eigen::VectorXd fx;
  Eigen::Matrix<double, -1, -1> J;
  stan::math::jacobian(f, params, fx, J);
  stanLl ret;
  ret.fx = fx;
  ret.J  = J;
  return ret;
}

static inline void llikBetaProportionFull(double* ret, double x, double mu, double kappa) {
#ifdef _OPENMP
  if (!omp_in_parallel()) {
    if (ret[0] == isBetaProportion &&
        ret[1] == x &&
        ret[2] == mu &&
        ret[3] == kappa) return;
  }
#else
  if (ret[0] == isBetaProportion &&
        ret[1] == x &&
        ret[2] == mu &&
        ret[3] == kappa) return;
#endif
  if (!R_finite(x) || !R_finite(mu) || !R_finite(kappa)) {
    ret[0] = isBetaProportion;
    ret[1] = x;
    ret[2] = mu;
    ret[3] = kappa;
    ret[4] = NA_REAL;
    ret[5] = NA_REAL;
    ret[6] = NA_REAL;
    return;
  }
  Eigen::VectorXd y(1);
  Eigen::VectorXd params(2);
  y(0) = x;
  params(0) = _smallIsNotZero(mu);
  params(1) = _smallIsNotZero(kappa);
  stanLl ll = llik_llikBetaProportion(y, params);
  ret[0] = isBetaProportion;
  ret[1] = x;
  ret[2] = mu;
  ret[3] = kappa;
  ret[4] = ll.fx(0);
  ret[5] = ll.J(0, 0);
  ret[6] = ll.J(0, 1);
  return;
}

//[[Rcpp::export]]
Rcpp::DataFrame llikBetaProportionInternal(Rcpp::NumericVector x, Rcpp::NumericVector mu, Rcpp::NumericVector kappa) {
  NumericVector fx(x.size());
  NumericVector dMu(x.size());
  NumericVector dKappa(x.size());
  double cur[7];
  std::fill_n(cur, 7, 0.0);
  for (R_xlen_t j = x.size(); j--;) {
    llikBetaProportionFull(cur, x[j], mu[j], kappa[j]);
    fx[j] = cur[4];
    dMu[j] = cur[5];
    dKappa[j] = cur[6];
  }
  return Rcpp::DataFrame::create(_["fx"]=fx,
                                 _["dMu"]=dMu,
                                 _["dKappa"]=dKappa);
}

extern "C" double rxLlikBetaProportion(double* ret, double x, double mu, double kappa) {
  llikBetaProportionFull(ret, x, mu, kappa);
  return ret[4];
}

extern "C" double rxLlikBetaProportionDMu(double* ret, double x, double mu, double kappa) {
  llikBetaProportionFull(ret, x, mu, kappa);
  return ret[5];
}

extern "C" double rxLlikBetaProportionDKappa(double* ret, double x, double mu, double kappa) {
  llikBetaProportionFull(ret, x, mu, kappa);
  return ret[6];
}
