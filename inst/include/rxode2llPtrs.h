#ifndef __RXODE2LLPTRS_H__
#define __RXODE2LLPTRS_H__
/*
  ABI-free access to rxode2ll's log-likelihood functions and their exact
  derivatives.

  R_GetCCallable() is NOT sufficient for this.  It removes the LINK-time
  dependency, but the consumer still compiles in a typedef'd signature and
  caches a raw address, so a rxode2ll update needs the consumer recompiled and
  a reload of rxode2ll leaves the cached pointers dangling.  That is the
  coupling the CRAN work-arounds in this ecosystem exist to avoid.

  This header follows the pattern rxode2, nlmixr2est, RcppTrust and n1qn1
  already use (see n1qn1/inst/include/n1qn1c.h): the provider hands out a list
  of external pointers from an R function, and the consumer re-reads that list
  in its own .onLoad.  A rxode2ll update is then picked up on the next load
  rather than baked into the consumer's object code.

  Consumer usage:

      #include <rxode2llPtrs.h>
      iniRxode2ll        // once, in one translation unit: defines the pointers
                         // and the .Call entry that fills them
      // and from R's .onLoad():
      //   .Call(`_yourpkg_iniRxode2llPtrs`, rxode2ll::.rxode2llPtr())

  The list is APPEND-ONLY and its order is fixed, so a consumer built against an
  older rxode2ll keeps working against a newer one.  Any pointer the provider
  did not supply is left NULL -- check before calling.
*/

#include <Rinternals.h>

#if defined(__cplusplus)
extern "C" {
#endif

/* one typedef per arity; ret is written by the callee, x is the datum */
typedef double (*rxLlik1_t)(double* ret, double x, double a);
typedef double (*rxLlik2_t)(double* ret, double x, double a, double b);
typedef double (*rxLlik3_t)(double* ret, double x, double a, double b, double c);

extern rxLlik2_t _p_rxLlikNorm;
extern rxLlik2_t _p_rxLlikNormDmean;
extern rxLlik2_t _p_rxLlikNormDsd;
extern rxLlik1_t _p_rxLlikPois;
extern rxLlik1_t _p_rxLlikPoisDlambda;
extern rxLlik2_t _p_rxLlikBinom;
extern rxLlik2_t _p_rxLlikBinomDprob;
extern rxLlik2_t _p_rxLlikNbinomMu;
extern rxLlik2_t _p_rxLlikNbinomMuDmu;
extern rxLlik2_t _p_rxLlikNbinom;
extern rxLlik2_t _p_rxLlikNbinomDprob;
extern rxLlik2_t _p_rxLlikBeta;
extern rxLlik2_t _p_rxLlikBetaDshape1;
extern rxLlik2_t _p_rxLlikBetaDshape2;
extern rxLlik3_t _p_rxLlikT;
extern rxLlik3_t _p_rxLlikTDdf;
extern rxLlik3_t _p_rxLlikTDmean;
extern rxLlik3_t _p_rxLlikTDsd;
extern rxLlik1_t _p_rxLlikChisq;
extern rxLlik1_t _p_rxLlikChisqDdf;
extern rxLlik1_t _p_rxLlikExp;
extern rxLlik1_t _p_rxLlikExpDrate;
extern rxLlik2_t _p_rxLlikF;
extern rxLlik2_t _p_rxLlikFDdf1;
extern rxLlik2_t _p_rxLlikFDdf2;
extern rxLlik1_t _p_rxLlikGeom;
extern rxLlik1_t _p_rxLlikGeomDp;
extern rxLlik2_t _p_rxLlikUnif;
extern rxLlik2_t _p_rxLlikUnifDalpha;
extern rxLlik2_t _p_rxLlikUnifDbeta;
extern rxLlik2_t _p_rxLlikWeibull;
extern rxLlik2_t _p_rxLlikWeibullDshape;
extern rxLlik2_t _p_rxLlikWeibullDscale;
extern rxLlik2_t _p_rxLlikGamma;
extern rxLlik2_t _p_rxLlikGammaDshape;
extern rxLlik2_t _p_rxLlikGammaDrate;
extern rxLlik2_t _p_rxLlikCauchy;
extern rxLlik2_t _p_rxLlikCauchyDlocation;
extern rxLlik2_t _p_rxLlikCauchyDscale;
extern rxLlik2_t _p_rxLlikLnorm;
extern rxLlik2_t _p_rxLlikLnormDMeanlog;
extern rxLlik2_t _p_rxLlikLnormDSdlog;
extern rxLlik2_t _p_rxLlikLogis;
extern rxLlik2_t _p_rxLlikLogisDLocation;
extern rxLlik2_t _p_rxLlikLogisDScale;
extern rxLlik2_t _p_rxLlikGumbel;
extern rxLlik2_t _p_rxLlikGumbelDMu;
extern rxLlik2_t _p_rxLlikGumbelDBeta;
extern rxLlik2_t _p_rxLlikDblExp;
extern rxLlik2_t _p_rxLlikDblExpDMu;
extern rxLlik2_t _p_rxLlikDblExpDSigma;
extern rxLlik2_t _p_rxLlikInvGamma;
extern rxLlik2_t _p_rxLlikInvGammaDAlpha;
extern rxLlik2_t _p_rxLlikInvGammaDBeta;
extern rxLlik1_t _p_rxLlikInvChisq;
extern rxLlik1_t _p_rxLlikInvChisqDNu;
extern rxLlik2_t _p_rxLlikScaledInvChisq;
extern rxLlik2_t _p_rxLlikScaledInvChisqDNu;
extern rxLlik2_t _p_rxLlikScaledInvChisqDSigma;
extern rxLlik2_t _p_rxLlikFrechet;
extern rxLlik2_t _p_rxLlikFrechetDAlpha;
extern rxLlik2_t _p_rxLlikFrechetDSigma;
extern rxLlik1_t _p_rxLlikRayleigh;
extern rxLlik1_t _p_rxLlikRayleighDSigma;
extern rxLlik2_t _p_rxLlikPareto;
extern rxLlik2_t _p_rxLlikParetoDYMin;
extern rxLlik2_t _p_rxLlikParetoDAlpha;
extern rxLlik3_t _p_rxLlikParetoType2;
extern rxLlik3_t _p_rxLlikParetoType2DMu;
extern rxLlik3_t _p_rxLlikParetoType2DLambda;
extern rxLlik3_t _p_rxLlikParetoType2DAlpha;
extern rxLlik2_t _p_rxLlikBetaProportion;
extern rxLlik2_t _p_rxLlikBetaProportionDMu;
extern rxLlik2_t _p_rxLlikBetaProportionDKappa;

/* Fixed list order.  APPEND ONLY -- never reorder or remove.
 *
 * The index into `p` is advanced by the macro rather than written out per
 * entry.  It used to be a literal on every line, which made the ONE invariant
 * this list has -- position k in the R-side list is position k here -- depend
 * on 74 hand-typed numbers staying in step.  An off-by-one there binds a
 * DIFFERENT likelihood's function pointer, silently and with the right
 * signature, which is about the worst failure this header could have.  Now the
 * order is the only thing written down, and appending an entry cannot
 * renumber the ones above it.
 */
#define _RXLL_NEXT(var, type)                                           \
  do {                                                                  \
    if (_i < _n) var = (type) R_ExternalPtrAddrFn(VECTOR_ELT(p, _i));    \
    _i++;                                                               \
  } while (0)

static inline SEXP iniRxode2llPtrs0(SEXP p) {
  int _n = (int)Rf_length(p);
  int _i = 0;
  _RXLL_NEXT(_p_rxLlikNorm, rxLlik2_t);
  _RXLL_NEXT(_p_rxLlikNormDmean, rxLlik2_t);
  _RXLL_NEXT(_p_rxLlikNormDsd, rxLlik2_t);
  _RXLL_NEXT(_p_rxLlikPois, rxLlik1_t);
  _RXLL_NEXT(_p_rxLlikPoisDlambda, rxLlik1_t);
  _RXLL_NEXT(_p_rxLlikBinom, rxLlik2_t);
  _RXLL_NEXT(_p_rxLlikBinomDprob, rxLlik2_t);
  _RXLL_NEXT(_p_rxLlikNbinomMu, rxLlik2_t);
  _RXLL_NEXT(_p_rxLlikNbinomMuDmu, rxLlik2_t);
  _RXLL_NEXT(_p_rxLlikNbinom, rxLlik2_t);
  _RXLL_NEXT(_p_rxLlikNbinomDprob, rxLlik2_t);
  _RXLL_NEXT(_p_rxLlikBeta, rxLlik2_t);
  _RXLL_NEXT(_p_rxLlikBetaDshape1, rxLlik2_t);
  _RXLL_NEXT(_p_rxLlikBetaDshape2, rxLlik2_t);
  _RXLL_NEXT(_p_rxLlikT, rxLlik3_t);
  _RXLL_NEXT(_p_rxLlikTDdf, rxLlik3_t);
  _RXLL_NEXT(_p_rxLlikTDmean, rxLlik3_t);
  _RXLL_NEXT(_p_rxLlikTDsd, rxLlik3_t);
  _RXLL_NEXT(_p_rxLlikChisq, rxLlik1_t);
  _RXLL_NEXT(_p_rxLlikChisqDdf, rxLlik1_t);
  _RXLL_NEXT(_p_rxLlikExp, rxLlik1_t);
  _RXLL_NEXT(_p_rxLlikExpDrate, rxLlik1_t);
  _RXLL_NEXT(_p_rxLlikF, rxLlik2_t);
  _RXLL_NEXT(_p_rxLlikFDdf1, rxLlik2_t);
  _RXLL_NEXT(_p_rxLlikFDdf2, rxLlik2_t);
  _RXLL_NEXT(_p_rxLlikGeom, rxLlik1_t);
  _RXLL_NEXT(_p_rxLlikGeomDp, rxLlik1_t);
  _RXLL_NEXT(_p_rxLlikUnif, rxLlik2_t);
  _RXLL_NEXT(_p_rxLlikUnifDalpha, rxLlik2_t);
  _RXLL_NEXT(_p_rxLlikUnifDbeta, rxLlik2_t);
  _RXLL_NEXT(_p_rxLlikWeibull, rxLlik2_t);
  _RXLL_NEXT(_p_rxLlikWeibullDshape, rxLlik2_t);
  _RXLL_NEXT(_p_rxLlikWeibullDscale, rxLlik2_t);
  _RXLL_NEXT(_p_rxLlikGamma, rxLlik2_t);
  _RXLL_NEXT(_p_rxLlikGammaDshape, rxLlik2_t);
  _RXLL_NEXT(_p_rxLlikGammaDrate, rxLlik2_t);
  _RXLL_NEXT(_p_rxLlikCauchy, rxLlik2_t);
  _RXLL_NEXT(_p_rxLlikCauchyDlocation, rxLlik2_t);
  _RXLL_NEXT(_p_rxLlikCauchyDscale, rxLlik2_t);
  _RXLL_NEXT(_p_rxLlikLnorm, rxLlik2_t);
  _RXLL_NEXT(_p_rxLlikLnormDMeanlog, rxLlik2_t);
  _RXLL_NEXT(_p_rxLlikLnormDSdlog, rxLlik2_t);
  _RXLL_NEXT(_p_rxLlikLogis, rxLlik2_t);
  _RXLL_NEXT(_p_rxLlikLogisDLocation, rxLlik2_t);
  _RXLL_NEXT(_p_rxLlikLogisDScale, rxLlik2_t);
  _RXLL_NEXT(_p_rxLlikGumbel, rxLlik2_t);
  _RXLL_NEXT(_p_rxLlikGumbelDMu, rxLlik2_t);
  _RXLL_NEXT(_p_rxLlikGumbelDBeta, rxLlik2_t);
  _RXLL_NEXT(_p_rxLlikDblExp, rxLlik2_t);
  _RXLL_NEXT(_p_rxLlikDblExpDMu, rxLlik2_t);
  _RXLL_NEXT(_p_rxLlikDblExpDSigma, rxLlik2_t);
  _RXLL_NEXT(_p_rxLlikInvGamma, rxLlik2_t);
  _RXLL_NEXT(_p_rxLlikInvGammaDAlpha, rxLlik2_t);
  _RXLL_NEXT(_p_rxLlikInvGammaDBeta, rxLlik2_t);
  _RXLL_NEXT(_p_rxLlikInvChisq, rxLlik1_t);
  _RXLL_NEXT(_p_rxLlikInvChisqDNu, rxLlik1_t);
  _RXLL_NEXT(_p_rxLlikScaledInvChisq, rxLlik2_t);
  _RXLL_NEXT(_p_rxLlikScaledInvChisqDNu, rxLlik2_t);
  _RXLL_NEXT(_p_rxLlikScaledInvChisqDSigma, rxLlik2_t);
  _RXLL_NEXT(_p_rxLlikFrechet, rxLlik2_t);
  _RXLL_NEXT(_p_rxLlikFrechetDAlpha, rxLlik2_t);
  _RXLL_NEXT(_p_rxLlikFrechetDSigma, rxLlik2_t);
  _RXLL_NEXT(_p_rxLlikRayleigh, rxLlik1_t);
  _RXLL_NEXT(_p_rxLlikRayleighDSigma, rxLlik1_t);
  _RXLL_NEXT(_p_rxLlikPareto, rxLlik2_t);
  _RXLL_NEXT(_p_rxLlikParetoDYMin, rxLlik2_t);
  _RXLL_NEXT(_p_rxLlikParetoDAlpha, rxLlik2_t);
  _RXLL_NEXT(_p_rxLlikParetoType2, rxLlik3_t);
  _RXLL_NEXT(_p_rxLlikParetoType2DMu, rxLlik3_t);
  _RXLL_NEXT(_p_rxLlikParetoType2DLambda, rxLlik3_t);
  _RXLL_NEXT(_p_rxLlikParetoType2DAlpha, rxLlik3_t);
  _RXLL_NEXT(_p_rxLlikBetaProportion, rxLlik2_t);
  _RXLL_NEXT(_p_rxLlikBetaProportionDMu, rxLlik2_t);
  _RXLL_NEXT(_p_rxLlikBetaProportionDKappa, rxLlik2_t);
  return R_NilValue;
}
#undef _RXLL_NEXT

#define iniRxode2ll \
  rxLlik2_t _p_rxLlikNorm = NULL; \
  rxLlik2_t _p_rxLlikNormDmean = NULL; \
  rxLlik2_t _p_rxLlikNormDsd = NULL; \
  rxLlik1_t _p_rxLlikPois = NULL; \
  rxLlik1_t _p_rxLlikPoisDlambda = NULL; \
  rxLlik2_t _p_rxLlikBinom = NULL; \
  rxLlik2_t _p_rxLlikBinomDprob = NULL; \
  rxLlik2_t _p_rxLlikNbinomMu = NULL; \
  rxLlik2_t _p_rxLlikNbinomMuDmu = NULL; \
  rxLlik2_t _p_rxLlikNbinom = NULL; \
  rxLlik2_t _p_rxLlikNbinomDprob = NULL; \
  rxLlik2_t _p_rxLlikBeta = NULL; \
  rxLlik2_t _p_rxLlikBetaDshape1 = NULL; \
  rxLlik2_t _p_rxLlikBetaDshape2 = NULL; \
  rxLlik3_t _p_rxLlikT = NULL; \
  rxLlik3_t _p_rxLlikTDdf = NULL; \
  rxLlik3_t _p_rxLlikTDmean = NULL; \
  rxLlik3_t _p_rxLlikTDsd = NULL; \
  rxLlik1_t _p_rxLlikChisq = NULL; \
  rxLlik1_t _p_rxLlikChisqDdf = NULL; \
  rxLlik1_t _p_rxLlikExp = NULL; \
  rxLlik1_t _p_rxLlikExpDrate = NULL; \
  rxLlik2_t _p_rxLlikF = NULL; \
  rxLlik2_t _p_rxLlikFDdf1 = NULL; \
  rxLlik2_t _p_rxLlikFDdf2 = NULL; \
  rxLlik1_t _p_rxLlikGeom = NULL; \
  rxLlik1_t _p_rxLlikGeomDp = NULL; \
  rxLlik2_t _p_rxLlikUnif = NULL; \
  rxLlik2_t _p_rxLlikUnifDalpha = NULL; \
  rxLlik2_t _p_rxLlikUnifDbeta = NULL; \
  rxLlik2_t _p_rxLlikWeibull = NULL; \
  rxLlik2_t _p_rxLlikWeibullDshape = NULL; \
  rxLlik2_t _p_rxLlikWeibullDscale = NULL; \
  rxLlik2_t _p_rxLlikGamma = NULL; \
  rxLlik2_t _p_rxLlikGammaDshape = NULL; \
  rxLlik2_t _p_rxLlikGammaDrate = NULL; \
  rxLlik2_t _p_rxLlikCauchy = NULL; \
  rxLlik2_t _p_rxLlikCauchyDlocation = NULL; \
  rxLlik2_t _p_rxLlikCauchyDscale = NULL; \
  rxLlik2_t _p_rxLlikLnorm = NULL; \
  rxLlik2_t _p_rxLlikLnormDMeanlog = NULL; \
  rxLlik2_t _p_rxLlikLnormDSdlog = NULL; \
  rxLlik2_t _p_rxLlikLogis = NULL; \
  rxLlik2_t _p_rxLlikLogisDLocation = NULL; \
  rxLlik2_t _p_rxLlikLogisDScale = NULL; \
  rxLlik2_t _p_rxLlikGumbel = NULL; \
  rxLlik2_t _p_rxLlikGumbelDMu = NULL; \
  rxLlik2_t _p_rxLlikGumbelDBeta = NULL; \
  rxLlik2_t _p_rxLlikDblExp = NULL; \
  rxLlik2_t _p_rxLlikDblExpDMu = NULL; \
  rxLlik2_t _p_rxLlikDblExpDSigma = NULL; \
  rxLlik2_t _p_rxLlikInvGamma = NULL; \
  rxLlik2_t _p_rxLlikInvGammaDAlpha = NULL; \
  rxLlik2_t _p_rxLlikInvGammaDBeta = NULL; \
  rxLlik1_t _p_rxLlikInvChisq = NULL; \
  rxLlik1_t _p_rxLlikInvChisqDNu = NULL; \
  rxLlik2_t _p_rxLlikScaledInvChisq = NULL; \
  rxLlik2_t _p_rxLlikScaledInvChisqDNu = NULL; \
  rxLlik2_t _p_rxLlikScaledInvChisqDSigma = NULL; \
  rxLlik2_t _p_rxLlikFrechet = NULL; \
  rxLlik2_t _p_rxLlikFrechetDAlpha = NULL; \
  rxLlik2_t _p_rxLlikFrechetDSigma = NULL; \
  rxLlik1_t _p_rxLlikRayleigh = NULL; \
  rxLlik1_t _p_rxLlikRayleighDSigma = NULL; \
  rxLlik2_t _p_rxLlikPareto = NULL; \
  rxLlik2_t _p_rxLlikParetoDYMin = NULL; \
  rxLlik2_t _p_rxLlikParetoDAlpha = NULL; \
  rxLlik3_t _p_rxLlikParetoType2 = NULL; \
  rxLlik3_t _p_rxLlikParetoType2DMu = NULL; \
  rxLlik3_t _p_rxLlikParetoType2DLambda = NULL; \
  rxLlik3_t _p_rxLlikParetoType2DAlpha = NULL; \
  rxLlik2_t _p_rxLlikBetaProportion = NULL; \
  rxLlik2_t _p_rxLlikBetaProportionDMu = NULL; \
  rxLlik2_t _p_rxLlikBetaProportionDKappa = NULL; \
  SEXP iniRxode2llPtrs(SEXP p) { \
    iniRxode2llPtrs0(p); \
    return R_NilValue; \
  }

#if defined(__cplusplus)
}
#endif

#endif /* __RXODE2LLPTRS_H__ */
