#

CXX = g++
# for debugging
# CXXFLAGS = -Wall -g -std=c++0x -pthread
CXXFLAGS = -std=c++0x -pthread

OBJS = main.o Helper.o Profile.o Probability.o init.o

all: motif-finder

motif-finder: $(OBJS)
	$(CXX) $(CXXFLAGS) -o motif-finder $(OBJS)


main.o: main.cpp Helper.h init.h Queue.h
Helper.o: Helper.cpp Helper.h Profile.h Probability.h
Profile.o: Profile.h Matrix.h
Probability.o: Probability.h Probability.cpp Matrix.h
init.o: init.h init.cpp

clean:
	rm -f *~ *.o motif-finder
