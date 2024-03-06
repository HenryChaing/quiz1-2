CC = gcc
CFLAGS = -O1 -g -Wall
OBJS = quicksort.o binarytree.o LRUcache.o

all: quicksort

%.o: %.c 
	$(CC) $(CFLAGS) -c -o $@ $<

quicksort: quicksort.o
	$(CC) $(CFLAGS) -o $@ $^

binarytree: binarytree.o
	$(CC) $(CFLAGS) -o $@ $^

LRUcache: LRUcache.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm $(OBJS) quicksort binarytree LRUcache