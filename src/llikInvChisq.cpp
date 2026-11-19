#include "llik2.h"
#ifdef _OPENMP
#include <omp.h>
#endif

////////////////////////////////////////////////////////////////////////////////
// InvChisq distribution -- gradients by Stan reverse-mode autodiff, exactly as
// the other families in this package are done.
struct llikInvChisq_ll {
  const Eigen::VectorXd y_;
  llikInvChisq_ll(const Eigen::VectorXd& y) : y_(y) { }
  template <typename T>
  Eigen::Matrix<T, -1, 1> operator()(const Eigen::Matrix<T, -1, 1>& theta) const {
    T nu = theta[0];
    Eigen::Matrix<T, -1, 1> lp(y_.size());
    for (Eigen::Index n = 0; n < y_.size(); ++n) {
      lp[n] = inv_chi_square_lpdf(y_[n], nu);
    }
    return lp;
  }
};

stanLl llik_llikInvChisq(Eigen::VectorXd& y, Eigen::VectorXd& params) {
  rx_stan_math_thread_init_rev_autodiff();
  llikInvChisq_ll f(y);
  Eigen::VectorXd fx;
  Eigen::Matrix<double, -1, -1> J;
  stan::math::jacobian(f, params, fx, J);
  stanLl ret;
  ret.fx = fx;
  ret.J  = J;
  return ret;
}

static inline void llikInvChisqFull(double* ret, double x, double nu) {
#ifdef _OPENMP
  if (!omp_in_parallel()) {
    if (ret[0] == isInvChisq &&
        ret[1] == x &&
        ret[2] == nu) return;
  }
#else
  if (ret[0] == isInvChisq &&
        ret[1] == x &&
        ret[2] == nu) return;
#endif
  if (!R_finite(x) || !R_finite(nu)) {
    ret[0] = isInvChisq;
    ret[1] = x;
    ret[2] = nu;
    ret[3] = NA_REAL;
    ret[4] = NA_REAL;
    return;
  }
  Eigen::VectorXd y(1);
  Eigen::VectorXd params(1);
  y(0) = x;
  params(0) = _smallIsNotZero(nu);
  stanLl ll = llik_llikInvChisq(y, params);
  ret[0] = isInvChisq;
  ret[1] = x;
  ret[2] = nu;
  ret[3] = ll.fx(0);
  ret[4] = ll.J(0, 0);
  return;
}

//[[Rcpp::export]]
Rcpp::DataFrame llikInvChisqInternal(Rcpp::NumericVector x, Rcpp::NumericVector nu) {
  NumericVector fx(x.size());
  NumericVector dNu(x.size());
  double cur[5];
  std::fill_n(cur, 5, 0.0);
  for (R_xlen_t j = x.size(); j--;) {
    llikInvChisqFull(cur, x[j], nu[j]);
    fx[j] = cur[3];
    dNu[j] = cur[4];
  }
  return Rcpp::DataFrame::create(_["fx"]=fx,
                                 _["dNu"]=dNu);
}

extern "C" double rxLlikInvChisq(double* ret, double x, double nu) {
  llikInvChisqFull(ret, x, nu);
  return ret[3];
}

extern "C" double rxLlikInvChisqDNu(double* ret, double x, double nu) {
  llikInvChisqFull(ret, x, nu);
  return ret[4];
}
