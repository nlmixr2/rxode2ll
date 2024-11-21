.in <- suppressWarnings(readLines("src/Makevars.in"))
.in <- gsub("@BH@", file.path(find.package("BH"),"include"), .in)
.in <- gsub("@RCPP@", file.path(find.package("Rcpp"),"include"), .in)
.in <- gsub("@EG@", file.path(find.package("RcppEigen"),"include"), .in)

.badStan <- ""
.in <- gsub("@SH@", gsub("-I", "-@ISYSTEM@",
                         paste(capture.output(StanHeaders:::CxxFlags()), # nolint
                               capture.output(RcppParallel:::CxxFlags()), # nolint
                               paste0("-@ISYSTEM@'", system.file('include', 'src', package = 'StanHeaders', mustWork = TRUE), "'"),
                               .badStan)),
            .in)

.in <- gsub("@SL@", paste(capture.output(StanHeaders:::LdFlags()), capture.output(RcppParallel:::RcppParallelLibs())), #nolint
            .in)

.makevars <- "src/Makevars"
if ((.Platform$OS.type == "windows" && !file.exists("src/Makevars.win"))) {
  .makevars <- "src/Makevars.win"
}

if (.Platform$OS.type == "windows" || R.version$os == "linux-musl") {
  .i <- "I"
} else {
  if (any(grepl("Pop!_OS", utils::osVersion, fixed=TRUE))) {
    .i <- "isystem"
  } else {
    .i <- "I"
  }
}
file.out <- file(.makevars, "wb")
writeLines(gsub("@ISYSTEM@", .i, .in),
           file.out)
close(file.out)
