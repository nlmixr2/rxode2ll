.in <- suppressWarnings(readLines("src/Makevars.in"))
.in <- gsub("@BH@", file.path(find.package("BH"),"include"), .in)
.in <- gsub("@RCPP@", file.path(find.package("Rcpp"),"include"), .in)
.in <- gsub("@EG@", file.path(find.package("RcppEigen"),"include"), .in)

# Stan and TBB headers only; nothing links TBB (see src/Makevars.in).  These
# are the flags StanHeaders:::CxxFlags() emits, built with system.file()
# because calling it loads 'StanHeaders' and so 'RcppParallel', which loads
# the TBB library.
.tbbInc <- Sys.getenv("TBB_INC")
if (dir.exists(.tbbInc)) {
  .tbbInc <- normalizePath(.tbbInc)
} else {
  .tbbInc <- system.file("include", package = "RcppParallel", mustWork = TRUE)
}
.sh <- paste0("-I", shQuote(.tbbInc), " -D_REENTRANT -DSTAN_THREADS",
              if (file.exists(file.path(.tbbInc, "tbb", "version.h"))) " -DTBB_INTERFACE_NEW",
              " -@ISYSTEM@'", system.file("include", "src", package = "StanHeaders", mustWork = TRUE), "'")
.in <- gsub("@SH@", gsub("-I", "-@ISYSTEM@", .sh), .in)

.makevars <- "src/Makevars"
if ((.Platform$OS.type == "windows" && !file.exists("src/Makevars.win"))) {
  .makevars <- "src/Makevars.win"
}

if (.Platform$OS.type == "windows" || R.version$os == "linux-musl") {
  .i <- "I"
} else {
  if (any(grepl("Pop!_OS", utils::osVersion, fixed=TRUE)) ||
        any(grepl("Ubuntu", utils::osVersion, fixed=TRUE))) {
    .i <- "isystem"
  } else {
    .i <- "I"
  }
}
file.out <- file(.makevars, "wb")
writeLines(gsub("@ISYSTEM@", .i, .in),
           file.out)
close(file.out)
