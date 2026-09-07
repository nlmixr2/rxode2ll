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
extern rxLlik3_t _p_rxLlikT;
extern rxLlik3_t _p_rxLlikTDdf;
extern rxLlik3_t _p_rxLlikTDmean;
extern rxLlik3_t _p_rxLlikTDsd;
extern rxLlik1_t _p_rxLlikChisq;
extern rxLlik1_t _p_rxLlikChisqDdf;
extern rxLlik1_t _p_rxLlikExp;
extern rxLlik1_t _p_rxLlikExpDrate;
extern rxLlik2_t _p_rxLlikF;
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

/* Fixed list order.  APPEND ONLY -- never reorder or remove. */
static inline SEXP iniRxode2llPtrs0(SEXP p) {
  int n = (int)Rf_length(p);
  if (n > 0) _p_rxLlikNorm = (rxLlik2_t) R_ExternalPtrAddrFn(VECTOR_ELT(p, 0));
  if (n > 1) _p_rxLlikNormDmean = (rxLlik2_t) R_ExternalPtrAddrFn(VECTOR_ELT(p, 1));
  if (n > 2) _p_rxLlikNormDsd = (rxLlik2_t) R_ExternalPtrAddrFn(VECTOR_ELT(p, 2));
  if (n > 3) _p_rxLlikPois = (rxLlik1_t) R_ExternalPtrAddrFn(VECTOR_ELT(p, 3));
  if (n > 4) _p_rxLlikPoisDlambda = (rxLlik1_t) R_ExternalPtrAddrFn(VECTOR_ELT(p, 4));
  if (n > 5) _p_rxLlikBinom = (rxLlik2_t) R_ExternalPtrAddrFn(VECTOR_ELT(p, 5));
  if (n > 6) _p_rxLlikBinomDprob = (rxLlik2_t) R_ExternalPtrAddrFn(VECTOR_ELT(p, 6));
  if (n > 7) _p_rxLlikNbinomMu = (rxLlik2_t) R_ExternalPtrAddrFn(VECTOR_ELT(p, 7));
  if (n > 8) _p_rxLlikNbinomMuDmu = (rxLlik2_t) R_ExternalPtrAddrFn(VECTOR_ELT(p, 8));
  if (n > 9) _p_rxLlikNbinom = (rxLlik2_t) R_ExternalPtrAddrFn(VECTOR_ELT(p, 9));
  if (n > 10) _p_rxLlikNbinomDprob = (rxLlik2_t) R_ExternalPtrAddrFn(VECTOR_ELT(p, 10));
  if (n > 11) _p_rxLlikBeta = (rxLlik2_t) R_ExternalPtrAddrFn(VECTOR_ELT(p, 11));
  if (n > 12) _p_rxLlikT = (rxLlik3_t) R_ExternalPtrAddrFn(VECTOR_ELT(p, 12));
  if (n > 13) _p_rxLlikTDdf = (rxLlik3_t) R_ExternalPtrAddrFn(VECTOR_ELT(p, 13));
  if (n > 14) _p_rxLlikTDmean = (rxLlik3_t) R_ExternalPtrAddrFn(VECTOR_ELT(p, 14));
  if (n > 15) _p_rxLlikTDsd = (rxLlik3_t) R_ExternalPtrAddrFn(VECTOR_ELT(p, 15));
  if (n > 16) _p_rxLlikChisq = (rxLlik1_t) R_ExternalPtrAddrFn(VECTOR_ELT(p, 16));
  if (n > 17) _p_rxLlikChisqDdf = (rxLlik1_t) R_ExternalPtrAddrFn(VECTOR_ELT(p, 17));
  if (n > 18) _p_rxLlikExp = (rxLlik1_t) R_ExternalPtrAddrFn(VECTOR_ELT(p, 18));
  if (n > 19) _p_rxLlikExpDrate = (rxLlik1_t) R_ExternalPtrAddrFn(VECTOR_ELT(p, 19));
  if (n > 20) _p_rxLlikF = (rxLlik2_t) R_ExternalPtrAddrFn(VECTOR_ELT(p, 20));
  if (n > 21) _p_rxLlikGeom = (rxLlik1_t) R_ExternalPtrAddrFn(VECTOR_ELT(p, 21));
  if (n > 22) _p_rxLlikGeomDp = (rxLlik1_t) R_ExternalPtrAddrFn(VECTOR_ELT(p, 22));
  if (n > 23) _p_rxLlikUnif = (rxLlik2_t) R_ExternalPtrAddrFn(VECTOR_ELT(p, 23));
  if (n > 24) _p_rxLlikUnifDalpha = (rxLlik2_t) R_ExternalPtrAddrFn(VECTOR_ELT(p, 24));
  if (n > 25) _p_rxLlikUnifDbeta = (rxLlik2_t) R_ExternalPtrAddrFn(VECTOR_ELT(p, 25));
  if (n > 26) _p_rxLlikWeibull = (rxLlik2_t) R_ExternalPtrAddrFn(VECTOR_ELT(p, 26));
  if (n > 27) _p_rxLlikWeibullDshape = (rxLlik2_t) R_ExternalPtrAddrFn(VECTOR_ELT(p, 27));
  if (n > 28) _p_rxLlikWeibullDscale = (rxLlik2_t) R_ExternalPtrAddrFn(VECTOR_ELT(p, 28));
  if (n > 29) _p_rxLlikGamma = (rxLlik2_t) R_ExternalPtrAddrFn(VECTOR_ELT(p, 29));
  if (n > 30) _p_rxLlikGammaDshape = (rxLlik2_t) R_ExternalPtrAddrFn(VECTOR_ELT(p, 30));
  if (n > 31) _p_rxLlikGammaDrate = (rxLlik2_t) R_ExternalPtrAddrFn(VECTOR_ELT(p, 31));
  if (n > 32) _p_rxLlikCauchy = (rxLlik2_t) R_ExternalPtrAddrFn(VECTOR_ELT(p, 32));
  if (n > 33) _p_rxLlikCauchyDlocation = (rxLlik2_t) R_ExternalPtrAddrFn(VECTOR_ELT(p, 33));
  if (n > 34) _p_rxLlikCauchyDscale = (rxLlik2_t) R_ExternalPtrAddrFn(VECTOR_ELT(p, 34));
  return R_NilValue;
}

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
  rxLlik3_t _p_rxLlikT = NULL; \
  rxLlik3_t _p_rxLlikTDdf = NULL; \
  rxLlik3_t _p_rxLlikTDmean = NULL; \
  rxLlik3_t _p_rxLlikTDsd = NULL; \
  rxLlik1_t _p_rxLlikChisq = NULL; \
  rxLlik1_t _p_rxLlikChisqDdf = NULL; \
  rxLlik1_t _p_rxLlikExp = NULL; \
  rxLlik1_t _p_rxLlikExpDrate = NULL; \
  rxLlik2_t _p_rxLlikF = NULL; \
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
  SEXP iniRxode2llPtrs(SEXP p) { \
    iniRxode2llPtrs0(p); \
    return R_NilValue; \
  }

#if defined(__cplusplus)
}
#endif

#endif /* __RXODE2LLPTRS_H__ */
