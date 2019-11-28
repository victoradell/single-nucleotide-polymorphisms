library(kernlab)

## Load the kernel matrix
K <- as.matrix(read.csv("../kernel_matrices/dirac.txt", header=F, sep=" "))
K <- as.kernelMatrix(K)
N <- dim(K)[1]
population <- as.factor(as.matrix(read.csv("../data/population.csv", header=F)))

## First we should split the data into learning (2/3) and test (1/3) parts
ntrain <- round(N*2/3)      # number of training examples
tindex <- sample(N, ntrain) # indices of training examples

## The fit a SVM in the train part
svm1.train <- ksvm(K[tindex,tindex], population[tindex], type="C-svc", kernel='matrix')

## and make it predict the test part

## Let's call SV the set of obtained support vectors

## Then it becomes tricky. We must compute the test-vs-SV kernel matrix
## which we do in two phases:

# First the test-vs-train matrix
testK <- K[-tindex, tindex]
# then we extract the SV from the train
testK <- testK[, SVindex(svm1.train), drop=FALSE]

# Now we can predict the test data
# Warning: here we MUST convert the matrix testK to a 'kernelMatrix'
y1 <- predict(svm1.train, as.kernelMatrix(testK))

table (pred=y1, truth=population[-tindex])

cat('Error rate = ', 100*sum(y1 != population[-tindex])/length(y1), '%')


#############################################


