CC=gcc
CFLAGS=-Wall -std=c99

all: stack_from_queue

stack_from_queue: stack_from_queue.o
	gcc -g -Wall -std=c99 -o stack_from_queue stack_from_queue.o

stack_from_queue.o: stack_from_queue.c
	gcc -g -Wall -std=c99 -c stack_from_queue.c

clean:
	-rm *.o

cleanall: clean
	-rm stack_from_queue
