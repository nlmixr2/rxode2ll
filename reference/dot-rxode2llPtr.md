# External pointers to rxode2ll's log-likelihood functions

Hands a consumer package the addresses of every `rxLlik*` function and
its exact derivatives, so it can call them from C/C++ without an ABI
dependency on this package.

## Usage

``` r
.rxode2llPtr()
```

## Value

list of external pointers, in the order documented in `rxode2llPtrs.h`

## Details

`R_GetCCallable()` is not sufficient for that. It drops the link-time
dependency, but the consumer still compiles in a typedef'd signature and
caches a raw address: updating rxode2ll then requires the consumer to be
rebuilt, and reloading rxode2ll leaves the cached pointers dangling.
This is the same external-pointer handshake rxode2, nlmixr2est,
RcppTrust and n1qn1 already use, where the consumer re-reads the list in
its own `.onLoad()` and therefore picks up an updated rxode2ll instead
of baking one in.

The returned list is APPEND-ONLY and its order is fixed; see
`inst/include/rxode2llPtrs.h`, which is the matching consumer header.

## Examples

``` r
length(.rxode2llPtr())
#> [1] 74
```
