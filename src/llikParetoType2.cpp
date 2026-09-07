#include "llik2.h"
#ifdef _OPENMP
#include <omp.h>
#endif

////////////////////////////////////////////////////////////////////////////////
// ParetoType2 distribution -- gradients by Stan reverse-mode autodiff, exactly as
// the other families in this package are done.
struct llikParetoType2_ll {
  const Eigen::VectorXd y_;
  llikParetoType2_ll(const Eigen::VectorXd& y) : y_(y) { }
  template <typename T>
  Eigen::Matrix<T, -1, 1> operator()(const Eigen::Matrix<T, -1, 1>& theta) const {
    T mu = theta[0];
    T lambda = theta[1];
    T alpha = theta[2];
    Eigen::Matrix<T, -1, 1> lp(y_.size());
    for (Eigen::Index n = 0; n < y_.size(); ++n) {
      lp[n] = pareto_type_2_lpdf(y_[n], mu, lambda, alpha);
    }
    return lp;
  }
};

stanLl llik_llikParetoType2(Eigen::VectorXd& y, Eigen::VectorXd& params) {
  rx_stan_math_thread_init_rev_autodiff();
  llikParetoType2_ll f(y);
  Eigen::VectorXd fx;
  Eigen::Matrix<double, -1, -1> J;
  stan::math::jacobian(f, params, fx, J);
  stanLl ret;
  ret.fx = fx;
  ret.J  = J;
  return ret;
}

static inline void llikParetoType2Full(double* ret, double x, double mu, double lambda, double alpha) {
#ifdef _OPENMP
  if (!omp_in_parallel()) {
    if (ret[0] == isParetoType2 &&
        ret[1] == x &&
        ret[2] == mu &&
        ret[3] == lambda &&
        ret[4] == alpha) return;
  }
#else
  if (ret[0] == isParetoType2 &&
        ret[1] == x &&
        ret[2] == mu &&
        ret[3] == lambda &&
        ret[4] == alpha) return;
#endif
  if (!R_finite(x) || !R_finite(mu) || !R_finite(lambda) || !R_finite(alpha)) {
    ret[0] = isParetoType2;
    ret[1] = x;
    ret[2] = mu;
    ret[3] = lambda;
    ret[4] = alpha;
    ret[5] = NA_REAL;
    ret[6] = NA_REAL;
    ret[7] = NA_REAL;
    ret[8] = NA_REAL;
    return;
  }
  Eigen::VectorXd y(1);
  Eigen::VectorXd params(3);
  y(0) = x;
  params(0) = mu;
  params(1) = _smallIsNotZero(lambda);
  params(2) = _smallIsNotZero(alpha);
  stanLl ll = llik_llikParetoType2(y, params);
  ret[0] = isParetoType2;
  ret[1] = x;
  ret[2] = mu;
  ret[3] = lambda;
  ret[4] = alpha;
  ret[5] = ll.fx(0);
  ret[6] = ll.J(0, 0);
  ret[7] = ll.J(0, 1);
  ret[8] = ll.J(0, 2);
  return;
}

//[[Rcpp::export]]
Rcpp::DataFrame llikParetoType2Internal(Rcpp::NumericVector x, Rcpp::NumericVector mu, Rcpp::NumericVector lambda, Rcpp::NumericVector alpha) {
  NumericVector fx(x.size());
  NumericVector dMu(x.size());
  NumericVector dLambda(x.size());
  NumericVector dAlpha(x.size());
  double cur[9];
  std::fill_n(cur, 9, 0.0);
  for (R_xlen_t j = x.size(); j--;) {
    llikParetoType2Full(cur, x[j], mu[j], lambda[j], alpha[j]);
    fx[j] = cur[5];
    dMu[j] = cur[6];
    dLambda[j] = cur[7];
    dAlpha[j] = cur[8];
  }
  return Rcpp::DataFrame::create(_["fx"]=fx,
                                 _["dMu"]=dMu,
                                 _["dLambda"]=dLambda,
                                 _["dAlpha"]=dAlpha);
}

extern "C" double rxLlikParetoType2(double* ret, double x, double mu, double lambda, double alpha) {
  llikParetoType2Full(ret, x, mu, lambda, alpha);
  return ret[5];
}

extern "C" double rxLlikParetoType2DMu(double* ret, double x, double mu, double lambda, double alpha) {
  llikParetoType2Full(ret, x, mu, lambda, alpha);
  return ret[6];
}

extern "C" double rxLlikParetoType2DLambda(double* ret, double x, double mu, double lambda, double alpha) {
  llikParetoType2Full(ret, x, mu, lambda, alpha);
  return ret[7];
}

extern "C" double rxLlikParetoType2DAlpha(double* ret, double x, double mu, double lambda, double alpha) {
  llikParetoType2Full(ret, x, mu, lambda, alpha);
  return ret[8];
}
