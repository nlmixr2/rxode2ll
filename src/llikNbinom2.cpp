#include "llik2.h"

#ifdef _OPENMP
#include <omp.h>
#endif

////////////////////////////////////////////////////////////////////////////////
// Negative Binomial 2
// R , sigma=scale

struct nbinomMu_llik {
  const Eigen::VectorXi y_;
  const Eigen::VectorXd N_; // dispersion; real-valued, not a count
  nbinomMu_llik(const Eigen::VectorXi& y, Eigen::VectorXd& N) : y_(y), N_(N) { }

  template <typename T>
  Eigen::Matrix<T, -1, 1> operator()(const Eigen::Matrix<T, -1, 1>& theta) const {
    T mu = theta[0];
    Eigen::Matrix<T, -1, 1> lp(y_.size());
    for (Eigen::Index i = 0; i < y_.size(); ++i) {
      lp[i] = stan::math::neg_binomial_2_lpmf(y_[i], mu, N_[i]);
    }
    return lp;
  }
};

stanLl llik_nbinomMu(Eigen::VectorXi& y, Eigen::VectorXd& N, Eigen::VectorXd& params) {
  rx_stan_math_thread_init_rev_autodiff();
  nbinomMu_llik f(y, N);
  Eigen::VectorXd fx;
  Eigen::Matrix<double, -1, -1> J;
  stan::math::jacobian(f, params, fx, J);
  stanLl ret;
  ret.fx = fx;
  ret.J  = J;
  return ret;
}


static inline void llikNbinomMuFull(double* ret, double x, double size, double mu) {
#ifdef _OPENMP
  if (!omp_in_parallel()) {
    if (ret[0] == isNbinomMu &&
        ret[1] == x &&
        ret[2] == size &&
        ret[3] == mu) {
      // Assume this is the same
      return;
    }
  }
#else
  if (ret[0] == isNbinomMu &&
      ret[1] == x &&
      ret[2] == size &&
      ret[3] == mu) {
    // Assume this is the same
    return;
  }
#endif

  if (!R_finite(x) || !R_finite(size) || !R_finite(mu)) {
    ret[0] = isNbinomMu;
    ret[1] = x;
    ret[2] = size;
    ret[3] = mu;
    ret[4] = NA_REAL;
    ret[5] = NA_REAL;
    return;
  }
  // neg_binomial_2_lpmf() needs a positive finite mean; a negative mu (reachable
  // through the C API, which bypasses the R-level assertions) makes it throw,
  // and that exception would escape the extern "C" entry points below and abort
  // the R process, so return NA here instead.  mu == 0 is degenerate rather than
  // out of domain and is handled just below.
  if (x < 0.0 || x > static_cast<double>(INT_MAX) ||
      size <= 0.0 || mu < 0.0) {
    ret[0] = isNbinomMu;
    ret[1] = x;
    ret[2] = size;
    ret[3] = mu;
    ret[4] = NA_REAL;
    ret[5] = NA_REAL;
    return;
  }
  if (mu == 0.0) {
    // mu == 0 makes the distribution degenerate at zero, so the likelihood is 1
    // at x == 0 and 0 elsewhere, matching stats::dnbinom().  Stan cannot
    // evaluate this point at all (it needs a strictly positive mean) and there
    // is no usable derivative here, so report the value R would and leave the
    // gradient NA rather than returning NA for both.
    ret[0] = isNbinomMu;
    ret[1] = x;
    ret[2] = size;
    ret[3] = mu;
    ret[4] = (x == 0.0) ? 0.0 : R_NegInf;
    ret[5] = NA_REAL;
    return;
  }
  Eigen::VectorXi y(1);
  Eigen::VectorXd N(1);
  Eigen::VectorXd params(1);
  y(0) = (int)(x);
  N(0) = size;
  params(0) = mu;
  stanLl ll = llik_nbinomMu(y, N, params);
  ret[0] = isNbinomMu;
  ret[1] = x;
  ret[2] = size;
  ret[3] = mu;
  ret[4] = ll.fx(0);
  ret[5] = ll.J(0, 0);
  return;
}

//[[Rcpp::export]]
Rcpp::DataFrame llikNbinomMuInternal(Rcpp::NumericVector x, Rcpp::NumericVector size, Rcpp::NumericVector mu) {
  NumericVector fx(x.size());
  NumericVector dMu(x.size());
  double cur[6];
  std::fill_n(cur, 6, 0.0);
  for (R_xlen_t j = x.size(); j--;) {
    llikNbinomMuFull(cur, x[j], size[j], mu[j]);
    fx[j]      = cur[4];
    dMu[j]     = cur[5];
  }
  return Rcpp::DataFrame::create(_["fx"]=fx,
                                 _["dMu"]=dMu);
}

extern "C" double rxLlikNbinomMu(double* ret, double x, double size, double mu) {
  llikNbinomMuFull(ret, x, size, mu);
  return ret[4];
}

extern "C" double rxLlikNbinomMuDmu(double* ret, double x, double size, double mu) {
  llikNbinomMuFull(ret, x, size, mu);
  return ret[5];
}
