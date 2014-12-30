library(ggplot2)

name <- c("v2", "v3")
time <- c(1304, 1321)
qplot(factor(name), y=time, geom="bar", fill=factor(name), stat="identity") + xlab("protobuf's version")

name <- c("v2", "v3", "v3 (with arena)")
time <- c(2588, 3059, 2618)
qplot(factor(name), y=time, geom="bar", fill=factor(name), stat="identity") + xlab("protobuf's version")
