#/bin/sh
CC=gcc
PROG=outputstr unpitest mytest printtest
LIBS=-lunpipc
LIBS+=-lpthread
LIBS+=-lrt
FLAGS= -g -std=c11 
all:${PROG}
outputstr:outputstr.o
	gcc -g -o outputstr outputstr.c

unpitest:unpitest.o
	$(CC) $(FLAGS) -o unpitest unpitest.c $(LIBS)
mytest:mytest.o
	$(CC) $(FLAGS) -o mytest mytest.c

printtest:printtest.o
	$(CC) $(FLAGS) -o printtest printtest.c

clean:
	rm *.o $(PROG)