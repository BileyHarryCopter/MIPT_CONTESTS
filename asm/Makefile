CC = gcc
CFLAGS = -c -Wall
CPROBLEM = AS2

all: start clean

start: problem_$(CPROBLEM).o
	$(CC) problem_$(CPROBLEM).o -o start

problem_$(CPROBLEM).o:
	$(CC) $(CFLAGS) problem_$(CPROBLEM).c

clean:
	rm -rf *.o

leaks:
	leaks -atExit -- ./start
