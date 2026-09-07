/* External-pointer export of rxode2ll's llik functions and derivatives.
 *
 * See inst/include/rxode2llPtrs.h for why R_GetCCallable() is not enough and
 * what the consumer contract is.  The order here IS that contract: append only.
 */
#include <R.h>
#include <Rinternals.h>
#include "llik.h"

SEXP _rxode2ll_ptr(void) {
  SEXP ret = PROTECT(Rf_allocVector(VECSXP, 35));
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
  SET_VECTOR_ELT(ret, 12, R_MakeExternalPtrFn((DL_FUNC)&rxLlikT, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 13, R_MakeExternalPtrFn((DL_FUNC)&rxLlikTDdf, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 14, R_MakeExternalPtrFn((DL_FUNC)&rxLlikTDmean, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 15, R_MakeExternalPtrFn((DL_FUNC)&rxLlikTDsd, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 16, R_MakeExternalPtrFn((DL_FUNC)&rxLlikChisq, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 17, R_MakeExternalPtrFn((DL_FUNC)&rxLlikChisqDdf, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 18, R_MakeExternalPtrFn((DL_FUNC)&rxLlikExp, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 19, R_MakeExternalPtrFn((DL_FUNC)&rxLlikExpDrate, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 20, R_MakeExternalPtrFn((DL_FUNC)&rxLlikF, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 21, R_MakeExternalPtrFn((DL_FUNC)&rxLlikGeom, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 22, R_MakeExternalPtrFn((DL_FUNC)&rxLlikGeomDp, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 23, R_MakeExternalPtrFn((DL_FUNC)&rxLlikUnif, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 24, R_MakeExternalPtrFn((DL_FUNC)&rxLlikUnifDalpha, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 25, R_MakeExternalPtrFn((DL_FUNC)&rxLlikUnifDbeta, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 26, R_MakeExternalPtrFn((DL_FUNC)&rxLlikWeibull, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 27, R_MakeExternalPtrFn((DL_FUNC)&rxLlikWeibullDshape, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 28, R_MakeExternalPtrFn((DL_FUNC)&rxLlikWeibullDscale, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 29, R_MakeExternalPtrFn((DL_FUNC)&rxLlikGamma, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 30, R_MakeExternalPtrFn((DL_FUNC)&rxLlikGammaDshape, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 31, R_MakeExternalPtrFn((DL_FUNC)&rxLlikGammaDrate, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 32, R_MakeExternalPtrFn((DL_FUNC)&rxLlikCauchy, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 33, R_MakeExternalPtrFn((DL_FUNC)&rxLlikCauchyDlocation, R_NilValue, R_NilValue));
  SET_VECTOR_ELT(ret, 34, R_MakeExternalPtrFn((DL_FUNC)&rxLlikCauchyDscale, R_NilValue, R_NilValue));
  UNPROTECT(1);
  return ret;
}
