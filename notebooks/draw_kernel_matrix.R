K <- read.csv("../kernel_matrices/dirac.txt", header=F, sep=" ")
K <- as.matrix(K)
rownames(K) <- NULL
colnames(K) <- NULL

library(lattice)
levelplot(K, col.regions=colorRampPalette(c("blue", "green", "yellow", "orange", "red")), cuts=11, 
          main="Allele-sharing distances", xlab="", ylab="")

