# A makefile for compiling the RBM project WIP

obj = BoltzmannDistribution.o Layer.o Machine.o main.o \
	Network.o SimilarityTester.o Unit.o
searchPaths = /usr/local/include/
libPaths = /usr/local/lib/
librariesToLink = armadillo.6.50.4

LLIBS = -L$(libPaths) -l$(librariesToLink)
SPTHS = -I$(searchPaths)

rbm : $(obj)
	mkdir ./executable
	clang++ $(obj) $(LLIBS) $(SPTHS) -o ./executable/rbm 
	
main.o : main.cpp Network.h SimilarityTester.h
BoltzmannDistribution.o : BoltzmannDistribution.h BoltzmannDistribution.cpp
Layer.o : Layer.h Layer.cpp
Machine.o : Machine.h Machine.cpp
Network.o : Network.cpp Network.h
SimilarityTester.o : SimilarityTester.cpp SimilarityTester.h
Unit.o : Unit.cpp Unit.h

.PHONY : clean
	clean

clean :
	rm *.o ./executable/rbm
