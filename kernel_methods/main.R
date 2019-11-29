#################### Load the kernel matrix and libraries #################### 



library(kernlab)
library(ggplot2)

K <- as.matrix(read.csv("../kernel_matrices/11_gram.txt", header=F, sep=" "))
# K <- K / (max(K) / 2)
K <- as.kernelMatrix(K)
N <- dim(K)[1]
population <- as.factor(as.matrix(read.csv("../data/population.csv", header=F)))



#################### kSVM #################### 



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



#################### kPCA #################### 



kpc.snp <- kpca (K, features=2, kernel="matrix")
data <- as.data.frame(kpc.snp@rotated[,1:2])
colnames(data) <- c("x", "y")
data$population <- population

MyPalette <- c(EthA = "black", EthE = "blue", EthK = "green", EthP = "red")

g2 <- ggplot(data, aes(x=x, y=y, color=population)) + geom_point(alpha=.4)
g2 + geom_vline(xintercept=0, linetype="dotted") + geom_hline(yintercept=0, linetype="dotted") + 
  labs(title="2-dimensional kPCA with 11-gram Kernel") +
  theme(plot.title = element_text(hjust = 0.5)) + theme(text=element_text(family="Ubuntu")) +
  scale_colour_manual(values = MyPalette)

