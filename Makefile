#

CC = gcc
# CFLAGS = -Wall -O3 -Werror
# for debugging
CFLAGS = -Wall -g -Werror

OBJS = Source.o

motif-finder: $(OBJS)
	$(CC) $(CFLAGS) -o motif-finder $(OBJS)


Source.o: Source.cpp

clean:
	rm -f *~ *.o motif-finder
