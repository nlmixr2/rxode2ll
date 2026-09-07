#ifndef __LLIK_H__
#define __LLIK_H__

#if defined(__cplusplus)
extern "C" {
#endif

  double rxLlikNorm(double* ret, double x, double mu, double sigma);
  double rxLlikNormDmean(double* ret, double x, double mu, double sigma);
  double rxLlikNormDsd(double* ret, double x, double mu, double sigma);

  double rxLlikPois(double* ret, double x, double lambda);
  double rxLlikPoisDlambda(double* ret, double x, double lambda);

  double rxLlikBinom(double* ret, double x, double size, double prob);
  double rxLlikBinomDprob(double* ret, double x, double size, double prob);

  double rxLlikNbinomMu(double* ret, double x, double size, double mu);
  double rxLlikNbinomMuDmu(double* ret, double x, double size, double mu);

  double rxLlikNbinom(double* ret, double x, double size, double prob);
  double rxLlikNbinomDprob(double* ret, double x, double size, double prob);

  double rxLlikBeta(double* ret, double x, double shape1, double shape2);
  double rxLlikBetaDshape1(double* ret, double x, double shape1, double shape2);
  double rxLlikBetaDshape2(double* ret, double x, double shape1, double shape2);

  double rxLlikT(double* ret, double x, double df, double mean, double sd);
  double rxLlikTDdf(double* ret, double x, double df, double mean, double sd);
  double rxLlikTDmean(double* ret, double x, double df, double mean, double sd);
  double rxLlikTDsd(double* ret, double x, double df, double mean, double sd);

  double rxLlikChisq(double* ret, double x, double df);
  double rxLlikChisqDdf(double* ret, double x, double df);

  double rxLlikExp(double* ret, double x, double rate);
  double rxLlikExpDrate(double* ret, double x, double rate);

  double rxLlikF(double* ret, double x,  double df1, double df2);
  double rxLlikFDdf1(double* ret, double x, double df1, double df2);
  double rxLlikFDdf2(double* ret, double x, double df1, double df2);

  double rxLlikGeom(double* ret, double x, double p);
  double rxLlikGeomDp(double* ret, double x, double p);

  double rxLlikUnif(double* ret, double x, double alpha, double beta);
  double rxLlikUnifDalpha(double* ret, double x, double alpha, double beta);
  double rxLlikUnifDbeta(double* ret, double x, double alpha, double beta);

  double rxLlikWeibull(double* ret, double x, double shape, double scale);
  double rxLlikWeibullDshape(double* ret, double x, double shape, double scale);
  double rxLlikWeibullDscale(double* ret, double x, double shape, double scale);

  double rxLlikGamma(double* ret, double x, double shape, double rate);
  double rxLlikGammaDshape(double* ret, double x, double shape, double rate);
  double rxLlikGammaDrate(double* ret, double x, double shape, double rate);

  double rxLlikCauchy(double* ret, double x, double location, double scale);
  double rxLlikCauchyDlocation(double* ret, double x, double location, double scale);
  double rxLlikCauchyDscale(double* ret, double x, double location, double scale);

  double rxLlikLnorm(double* ret, double x, double meanlog, double sdlog);
  double rxLlikLnormDMeanlog(double* ret, double x, double meanlog, double sdlog);
  double rxLlikLnormDSdlog(double* ret, double x, double meanlog, double sdlog);
  double rxLlikLogis(double* ret, double x, double location, double scale);
  double rxLlikLogisDLocation(double* ret, double x, double location, double scale);
  double rxLlikLogisDScale(double* ret, double x, double location, double scale);
  double rxLlikGumbel(double* ret, double x, double mu, double beta);
  double rxLlikGumbelDMu(double* ret, double x, double mu, double beta);
  double rxLlikGumbelDBeta(double* ret, double x, double mu, double beta);
  double rxLlikDblExp(double* ret, double x, double mu, double sigma);
  double rxLlikDblExpDMu(double* ret, double x, double mu, double sigma);
  double rxLlikDblExpDSigma(double* ret, double x, double mu, double sigma);
  double rxLlikInvGamma(double* ret, double x, double alpha, double beta);
  double rxLlikInvGammaDAlpha(double* ret, double x, double alpha, double beta);
  double rxLlikInvGammaDBeta(double* ret, double x, double alpha, double beta);
  double rxLlikInvChisq(double* ret, double x, double nu);
  double rxLlikInvChisqDNu(double* ret, double x, double nu);
  double rxLlikScaledInvChisq(double* ret, double x, double nu, double sigma);
  double rxLlikScaledInvChisqDNu(double* ret, double x, double nu, double sigma);
  double rxLlikScaledInvChisqDSigma(double* ret, double x, double nu, double sigma);
  double rxLlikFrechet(double* ret, double x, double alpha, double sigma);
  double rxLlikFrechetDAlpha(double* ret, double x, double alpha, double sigma);
  double rxLlikFrechetDSigma(double* ret, double x, double alpha, double sigma);
  double rxLlikRayleigh(double* ret, double x, double sigma);
  double rxLlikRayleighDSigma(double* ret, double x, double sigma);
  double rxLlikPareto(double* ret, double x, double yMin, double alpha);
  double rxLlikParetoDYMin(double* ret, double x, double yMin, double alpha);
  double rxLlikParetoDAlpha(double* ret, double x, double yMin, double alpha);
  double rxLlikParetoType2(double* ret, double x, double mu, double lambda, double alpha);
  double rxLlikParetoType2DMu(double* ret, double x, double mu, double lambda, double alpha);
  double rxLlikParetoType2DLambda(double* ret, double x, double mu, double lambda, double alpha);
  double rxLlikParetoType2DAlpha(double* ret, double x, double mu, double lambda, double alpha);
  double rxLlikBetaProportion(double* ret, double x, double mu, double kappa);
  double rxLlikBetaProportionDMu(double* ret, double x, double mu, double kappa);
  double rxLlikBetaProportionDKappa(double* ret, double x, double mu, double kappa);

#if defined(__cplusplus)
}
#endif

#endif // __LLIK_H__
