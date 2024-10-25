library(jsonlite)
# Create the matrix
M <- 5000
N <- M*M
a <- matrix(c(1:N), nrow = M, ncol = M, byrow=TRUE)
a[M, M]
starttime <- Sys.time()
# Serialize
s_out <- toJSON(a, matrix = c("rowmajor"))
# Save to disk
write(s_out, file = "a.json")
end1time <- Sys.time()
# Load from disk
s_in <- fromJSON("a.json")
m <- matrix(unlist(s_in), ncol=M, byrow=TRUE)
m[M, M]
end2time <- Sys.time()
time1 <- end1time - starttime
time2 <- end2time - end1time
time1
time2
