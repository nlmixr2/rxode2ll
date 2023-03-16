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

if (.Platform$OS.type == "windows" && !file.exists("src/Makevars.win")) {
  file.out <- file("src/Makevars.win", "wb")
  writeLines(gsub("@ISYSTEM@", "I", .in),
             file.out)
  close(file.out)
} else {
  file.out <- file("src/Makevars", "wb")
  writeLines(gsub("@ISYSTEM@", "isystem", .in),
             file.out)
  close(file.out)
}

