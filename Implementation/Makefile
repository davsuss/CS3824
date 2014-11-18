#

CC = g++
# for debugging
CFLAGS = -Wall -g -Werror

OBJS = main.o Helper.o Profile.o Probability.o init.o

motif-finder: $(OBJS)
	$(CC) $(CFLAGS) -o motif-finder $(OBJS)


main.o: main.cpp Helper.h init.h
Helper.o: Helper.cpp Helper.h Profile.h Probability.h
Profile.o: Profile.h Matrix.h
Probability.o: Probability.h Probability.cpp Matrix.h
init.o: init.h init.cpp

clean:
	rm -f *~ *.o motif-finder
