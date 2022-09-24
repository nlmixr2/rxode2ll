#define USE_FC_LEN_T
#define STRICT_R_HEADERS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <R.h>
#include <Rinternals.h>
#include <stdlib.h> // for NULL
#include <R_ext/Rdynload.h>
#define __DOINIT__
#include "llik.h"

SEXP _rxode2ll_llikNormInternal(SEXP xSEXP, SEXP muSEXP, SEXP sigmaSEXP);
SEXP _rxode2ll_llikPoisInternal(SEXP xSEXP, SEXP lambdaSEXP);
SEXP _rxode2ll_llikBinomInternal(SEXP xSEXP, SEXP sizeSEXP, SEXP probSEXP);
SEXP _rxode2ll_llikNbinomMuInternal(SEXP xSEXP, SEXP sizeSEXP, SEXP muSEXP);
SEXP _rxode2ll_llikNbinomInternal(SEXP xSEXP, SEXP sizeSEXP, SEXP probSEXP);
SEXP _rxode2ll_llikBetaInternal(SEXP xSEXP, SEXP shape1SEXP, SEXP shape2SEXP);
SEXP _rxode2ll_llikTInternal(SEXP xSEXP, SEXP df1SEXP, SEXP meanSEXP, SEXP sdSEXP);
SEXP _rxode2ll_llikChisqInternal(SEXP xSEXP, SEXP dfSEXP);
SEXP _rxode2ll_llikExpInternal(SEXP xSEXP, SEXP rateSEXP);
SEXP _rxode2ll_llikFInternal(SEXP xSEXP, SEXP df1SEXP, SEXP df2SEXP);
SEXP _rxode2ll_llikGeomInternal(SEXP xSEXP, SEXP pSEXP);
SEXP _rxode2ll_llikUnifInternal(SEXP xSEXP, SEXP alphaSEXP, SEXP betaSEXP);
SEXP _rxode2ll_llikWeibullInternal(SEXP xSEXP, SEXP shapeSEXP, SEXP sizeSEXP);
SEXP _rxode2ll_llikGammaInternal(SEXP xSEXP, SEXP shapeSEXP, SEXP rateSEXP);
SEXP _rxode2ll_llikCauchyInternal(SEXP xSEXP, SEXP locationSEXP, SEXP scaleSEXP);

void R_init_rxode2ll(DllInfo *info){
  R_CallMethodDef callMethods[]  = {
    {"_rxode2ll_llikNormInternal", (DL_FUNC) &_rxode2ll_llikNormInternal, 3},
    {"_rxode2ll_llikPoisInternal", (DL_FUNC) &_rxode2ll_llikPoisInternal, 2},
    {"_rxode2ll_llikBinomInternal",(DL_FUNC) &_rxode2ll_llikBinomInternal, 3},
    {"_rxode2ll_llikNbinomMuInternal",(DL_FUNC) &_rxode2ll_llikNbinomMuInternal, 3},
    {"_rxode2ll_llikNbinomInternal",(DL_FUNC) &_rxode2ll_llikNbinomInternal, 3},
    {"_rxode2ll_llikBetaInternal", (DL_FUNC) &_rxode2ll_llikBetaInternal, 3},
    {"_rxode2ll_llikTInternal", (DL_FUNC) &_rxode2ll_llikTInternal, 4},
    {"_rxode2ll_llikChisqInternal", (DL_FUNC) &_rxode2ll_llikChisqInternal, 2},
    {"_rxode2ll_llikExpInternal", (DL_FUNC) &_rxode2ll_llikExpInternal, 2},
    {"_rxode2ll_llikFInternal", (DL_FUNC) &_rxode2ll_llikFInternal, 3},
    {"_rxode2ll_llikGeomInternal", (DL_FUNC) &_rxode2ll_llikGeomInternal, 2},
    {"_rxode2ll_llikUnifInternal", (DL_FUNC) &_rxode2ll_llikUnifInternal, 3},
    {"_rxode2ll_llikWeibullInternal", (DL_FUNC) &_rxode2ll_llikWeibullInternal, 3},
    {"_rxode2ll_llikGammaInternal", (DL_FUNC) &_rxode2ll_llikGammaInternal, 3},
    {"_rxode2ll_llikCauchyInternal", (DL_FUNC) &_rxode2ll_llikCauchyInternal, 3},
    {NULL, NULL, 0} 
  };
    // log likelihoods used in calculations
  R_RegisterCCallable("rxode2ll", "rxLlikNorm", (DL_FUNC) &rxLlikNorm);
  R_RegisterCCallable("rxode2ll", "rxLlikNormDmean", (DL_FUNC) &rxLlikNormDmean);
  R_RegisterCCallable("rxode2ll", "rxLlikNormDsd", (DL_FUNC) &rxLlikNormDsd);
  R_RegisterCCallable("rxode2ll", "rxLlikPois", (DL_FUNC) &rxLlikPois);
  R_RegisterCCallable("rxode2ll", "rxLlikPoisDlambda", (DL_FUNC) &rxLlikPoisDlambda);
  R_RegisterCCallable("rxode2ll", "rxLlikBinom", (DL_FUNC) &rxLlikBinom);
  R_RegisterCCallable("rxode2ll", "rxLlikBinomDprob", (DL_FUNC) &rxLlikBinomDprob);
  R_RegisterCCallable("rxode2ll", "rxLlikNbinomMu", (DL_FUNC) &rxLlikNbinomMu);
  R_RegisterCCallable("rxode2ll", "rxLlikNbinomMuDmu", (DL_FUNC) &rxLlikNbinomMuDmu);
  R_RegisterCCallable("rxode2ll", "rxLlikNbinom", (DL_FUNC) &rxLlikNbinom);
  R_RegisterCCallable("rxode2ll", "rxLlikNbinomDprob", (DL_FUNC) &rxLlikNbinomDprob);

  R_RegisterCCallable("rxode2ll", "rxLlikBeta", (DL_FUNC) &rxLlikBeta);
  R_RegisterCCallable("rxode2ll", "rxLlikBetaDshape1", (DL_FUNC) &rxLlikBetaDshape1);
  R_RegisterCCallable("rxode2ll", "rxLlikBetaDshape2", (DL_FUNC) &rxLlikBetaDshape2);
  R_RegisterCCallable("rxode2ll", "rxLlikT", (DL_FUNC) &rxLlikT);
  R_RegisterCCallable("rxode2ll", "rxLlikTDdf", (DL_FUNC) &rxLlikTDdf);
  R_RegisterCCallable("rxode2ll", "rxLlikTDmean", (DL_FUNC) &rxLlikTDmean);
  R_RegisterCCallable("rxode2ll", "rxLlikTDsd", (DL_FUNC) &rxLlikTDsd);
  R_RegisterCCallable("rxode2ll", "rxLlikChisq", (DL_FUNC) &rxLlikChisq);
  R_RegisterCCallable("rxode2ll", "rxLlikChisqDdf", (DL_FUNC) &rxLlikChisqDdf);
  R_RegisterCCallable("rxode2ll", "rxLlikExp", (DL_FUNC) &rxLlikExp);
  R_RegisterCCallable("rxode2ll", "rxLlikExpDrate", (DL_FUNC) &rxLlikExpDrate);
  R_RegisterCCallable("rxode2ll", "rxLlikF", (DL_FUNC) &rxLlikF);
  R_RegisterCCallable("rxode2ll", "rxLlikFDdf1", (DL_FUNC) &rxLlikFDdf1);
  R_RegisterCCallable("rxode2ll", "rxLlikFDdf2", (DL_FUNC) &rxLlikFDdf2);
  R_RegisterCCallable("rxode2ll", "rxLlikGeom", (DL_FUNC) &rxLlikGeom);
  R_RegisterCCallable("rxode2ll", "rxLlikGeomDp", (DL_FUNC) &rxLlikGeomDp);
  R_RegisterCCallable("rxode2ll", "rxLlikUnif", (DL_FUNC) &rxLlikUnif);
  R_RegisterCCallable("rxode2ll", "rxLlikUnifDalpha", (DL_FUNC) &rxLlikUnifDalpha);
  R_RegisterCCallable("rxode2ll", "rxLlikUnifDbeta", (DL_FUNC) &rxLlikUnifDbeta);
  R_RegisterCCallable("rxode2ll", "rxLlikWeibull", (DL_FUNC) &rxLlikWeibull);
  R_RegisterCCallable("rxode2ll", "rxLlikWeibullDshape", (DL_FUNC) &rxLlikWeibullDshape);
  R_RegisterCCallable("rxode2ll", "rxLlikWeibullDscale", (DL_FUNC) &rxLlikWeibullDscale);
  R_RegisterCCallable("rxode2ll", "rxLlikGamma", (DL_FUNC) &rxLlikGamma);
  R_RegisterCCallable("rxode2ll", "rxLlikGammaDshape", (DL_FUNC) &rxLlikGammaDshape);
  R_RegisterCCallable("rxode2ll", "rxLlikGammaDrate", (DL_FUNC) &rxLlikGammaDrate);
  R_RegisterCCallable("rxode2ll", "rxLlikCauchy", (DL_FUNC) &rxLlikCauchy);
  R_RegisterCCallable("rxode2ll", "rxLlikCauchyDlocation", (DL_FUNC) &rxLlikCauchyDlocation);
  R_RegisterCCallable("rxode2ll", "rxLlikCauchyDscale", (DL_FUNC) &rxLlikCauchyDscale);
  
  static const R_CMethodDef cMethods[] = {
    {NULL, NULL, 0, NULL}
  };
  R_registerRoutines(info, cMethods, callMethods, NULL, NULL);
  R_useDynamicSymbols(info, FALSE);
}
