#analysing lengths of paths for bfs and dfs

library(tidyverse)
#clean data
head(AdjListBFSOutput$V1) #need to filter for -1's
bfs<-data.frame(AdjListBFSOutput)
dfs<-data.frame(AdjListDFSOutput)
bfs[bfs==-1]<-0
dfs[dfs==-1]<-0

bnew<-bfs %>% filter(V1>0) #filtered dataset
dnew<-dfs %>% filter(V1>0)

head(bnew)

bseg<-bfs
bseg[bseg>0]<-1
dseg<-dfs
dseg[dseg>0]<-1
summary(bseg) #summary stats
summary(dseg)

#bar plot
bp <- ggplot(bseg, aes(V1))
bp + geom_bar(fill = "pink") +
  ggtitle("Whether or Not There is a Path Between Two Articles") +
  xlab("True or False") + ylab("Number of Tests")

#t-tests
#two-sided
t.test(bnew, mu = 6)
t.test(dnew, mu = 6)

#one-sided, greater
t.test(bnew, mu = 6, alternative = "greater")
t.test(dnew, mu = 6, alternative = "greater")

#checking assumptions
d <- density(bnew$V1)
plot(d, main="Kernel Density of Length of Path Using BFS")
polygon(d, col="pink1", border="mediumpurple1")
abline(v = mean(bnew$V1), col="blue")

dd <- density(dnew$V1)
plot(dd, main="Kernel Density of Length of Path Using DFS")
polygon(dd, col="pink3", border="mediumpurple2")
abline(v = mean(dnew$V1), col="blue")

qqnorm(bnew$V1)
qqline(bnew$V1)

#standard deviations
sdb <- sd(bnew$V1)
sdd <- sd(dnew$V1)
