CC=g++ -march=native
CFLAGS=-c -I. -std=c++11 -Wfatal-errors

all: core

core: main.o heap.o treap.o glist.o ex.o stream.o
	$(CC) main.o heap.o treap.o glist.o ex.o stream.o -o core -g
	rm *.o

main.o: main.cc
	$(CC) $(CFLAGS) main.cc -o main.o -g

heap.o: heap.cc
	$(CC) $(CFLAGS) heap.cc -o heap.o -g

treap.o: treap.cc
	$(CC) $(CFLAGS) treap.cc -o treap.o -g

glist.o: glist.cc
	$(CC) $(CFLAGS) glist.cc -o glist.o -g

ex.o:Experiment.cc
	$(CC) $(CFLAGS) Experiment.cc -o ex.o -g

stream.o:Stream.cc
	$(CC) $(CFLAGS) Stream.cc -o stream.o -g


.PHONY:clean
clean:
	rm *.o
