/* External-pointer export of rxode2ll's llik functions and derivatives.
 *
 * See inst/include/rxode2llPtrs.h for why R_GetCCallable() is not enough and
 * what the consumer contract is.  The order here IS that contract: append only.
 */
#include <R.h>
#include <Rinternals.h>
#include "llik.h"

SEXP _rxode2ll_ptr(void) {
  SEXP ret = PROTECT(Rf_allocVector(VECSXP, 74));
  SET_VECTOR_ELT(ret, 0, R_MakeExternalPtrFn((DL_FUNC)&rxLlikNorm, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 1, R_MakeExternalPtrFn((DL_FUNC)&rxLlikNormDmean, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 2, R_MakeExternalPtrFn((DL_FUNC)&rxLlikNormDsd, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 3, R_MakeExternalPtrFn((DL_FUNC)&rxLlikPois, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 4, R_MakeExternalPtrFn((DL_FUNC)&rxLlikPoisDlambda, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 5, R_MakeExternalPtrFn((DL_FUNC)&rxLlikBinom, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 6, R_MakeExternalPtrFn((DL_FUNC)&rxLlikBinomDprob, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 7, R_MakeExternalPtrFn((DL_FUNC)&rxLlikNbinomMu, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 8, R_MakeExternalPtrFn((DL_FUNC)&rxLlikNbinomMuDmu, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 9, R_MakeExternalPtrFn((DL_FUNC)&rxLlikNbinom, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 10, R_MakeExternalPtrFn((DL_FUNC)&rxLlikNbinomDprob, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 11, R_MakeExternalPtrFn((DL_FUNC)&rxLlikBeta, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 12, R_MakeExternalPtrFn((DL_FUNC)&rxLlikBetaDshape1, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 13, R_MakeExternalPtrFn((DL_FUNC)&rxLlikBetaDshape2, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 14, R_MakeExternalPtrFn((DL_FUNC)&rxLlikT, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 15, R_MakeExternalPtrFn((DL_FUNC)&rxLlikTDdf, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 16, R_MakeExternalPtrFn((DL_FUNC)&rxLlikTDmean, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 17, R_MakeExternalPtrFn((DL_FUNC)&rxLlikTDsd, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 18, R_MakeExternalPtrFn((DL_FUNC)&rxLlikChisq, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 19, R_MakeExternalPtrFn((DL_FUNC)&rxLlikChisqDdf, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 20, R_MakeExternalPtrFn((DL_FUNC)&rxLlikExp, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 21, R_MakeExternalPtrFn((DL_FUNC)&rxLlikExpDrate, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 22, R_MakeExternalPtrFn((DL_FUNC)&rxLlikF, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 23, R_MakeExternalPtrFn((DL_FUNC)&rxLlikFDdf1, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 24, R_MakeExternalPtrFn((DL_FUNC)&rxLlikFDdf2, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 25, R_MakeExternalPtrFn((DL_FUNC)&rxLlikGeom, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 26, R_MakeExternalPtrFn((DL_FUNC)&rxLlikGeomDp, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 27, R_MakeExternalPtrFn((DL_FUNC)&rxLlikUnif, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 28, R_MakeExternalPtrFn((DL_FUNC)&rxLlikUnifDalpha, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 29, R_MakeExternalPtrFn((DL_FUNC)&rxLlikUnifDbeta, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 30, R_MakeExternalPtrFn((DL_FUNC)&rxLlikWeibull, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 31, R_MakeExternalPtrFn((DL_FUNC)&rxLlikWeibullDshape, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 32, R_MakeExternalPtrFn((DL_FUNC)&rxLlikWeibullDscale, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 33, R_MakeExternalPtrFn((DL_FUNC)&rxLlikGamma, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 34, R_MakeExternalPtrFn((DL_FUNC)&rxLlikGammaDshape, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 35, R_MakeExternalPtrFn((DL_FUNC)&rxLlikGammaDrate, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 36, R_MakeExternalPtrFn((DL_FUNC)&rxLlikCauchy, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 37, R_MakeExternalPtrFn((DL_FUNC)&rxLlikCauchyDlocation, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 38, R_MakeExternalPtrFn((DL_FUNC)&rxLlikCauchyDscale, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 39, R_MakeExternalPtrFn((DL_FUNC)&rxLlikLnorm, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 40, R_MakeExternalPtrFn((DL_FUNC)&rxLlikLnormDMeanlog, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 41, R_MakeExternalPtrFn((DL_FUNC)&rxLlikLnormDSdlog, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 42, R_MakeExternalPtrFn((DL_FUNC)&rxLlikLogis, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 43, R_MakeExternalPtrFn((DL_FUNC)&rxLlikLogisDLocation, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 44, R_MakeExternalPtrFn((DL_FUNC)&rxLlikLogisDScale, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 45, R_MakeExternalPtrFn((DL_FUNC)&rxLlikGumbel, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 46, R_MakeExternalPtrFn((DL_FUNC)&rxLlikGumbelDMu, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 47, R_MakeExternalPtrFn((DL_FUNC)&rxLlikGumbelDBeta, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 48, R_MakeExternalPtrFn((DL_FUNC)&rxLlikDblExp, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 49, R_MakeExternalPtrFn((DL_FUNC)&rxLlikDblExpDMu, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 50, R_MakeExternalPtrFn((DL_FUNC)&rxLlikDblExpDSigma, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 51, R_MakeExternalPtrFn((DL_FUNC)&rxLlikInvGamma, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 52, R_MakeExternalPtrFn((DL_FUNC)&rxLlikInvGammaDAlpha, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 53, R_MakeExternalPtrFn((DL_FUNC)&rxLlikInvGammaDBeta, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 54, R_MakeExternalPtrFn((DL_FUNC)&rxLlikInvChisq, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 55, R_MakeExternalPtrFn((DL_FUNC)&rxLlikInvChisqDNu, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 56, R_MakeExternalPtrFn((DL_FUNC)&rxLlikScaledInvChisq, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 57, R_MakeExternalPtrFn((DL_FUNC)&rxLlikScaledInvChisqDNu, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 58, R_MakeExternalPtrFn((DL_FUNC)&rxLlikScaledInvChisqDSigma, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 59, R_MakeExternalPtrFn((DL_FUNC)&rxLlikFrechet, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 60, R_MakeExternalPtrFn((DL_FUNC)&rxLlikFrechetDAlpha, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 61, R_MakeExternalPtrFn((DL_FUNC)&rxLlikFrechetDSigma, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 62, R_MakeExternalPtrFn((DL_FUNC)&rxLlikRayleigh, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 63, R_MakeExternalPtrFn((DL_FUNC)&rxLlikRayleighDSigma, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 64, R_MakeExternalPtrFn((DL_FUNC)&rxLlikPareto, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 65, R_MakeExternalPtrFn((DL_FUNC)&rxLlikParetoDYMin, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 66, R_MakeExternalPtrFn((DL_FUNC)&rxLlikParetoDAlpha, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 67, R_MakeExternalPtrFn((DL_FUNC)&rxLlikParetoType2, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 68, R_MakeExternalPtrFn((DL_FUNC)&rxLlikParetoType2DMu, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 69, R_MakeExternalPtrFn((DL_FUNC)&rxLlikParetoType2DLambda, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 70, R_MakeExternalPtrFn((DL_FUNC)&rxLlikParetoType2DAlpha, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 71, R_MakeExternalPtrFn((DL_FUNC)&rxLlikBetaProportion, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 72, R_MakeExternalPtrFn((DL_FUNC)&rxLlikBetaProportionDMu, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 73, R_MakeExternalPtrFn((DL_FUNC)&rxLlikBetaProportionDKappa, R_NilValue, R_NilValue));
  UNPROTECT(1);
  return ret;
}
