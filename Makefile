#

CC = g++
# CFLAGS = -Wall -O3 -Werror
# for debugging
CFLAGS = -Wall -g -Werror

OBJS = Source.o helpers.o

motif-finder: $(OBJS)
	$(CC) $(CFLAGS) -o motif-finder $(OBJS)


Source.o: Source.cpp
helpers.o: helpers.cpp

clean:
	rm -f *~ *.o motif-finder
