CC = gcc
CFLAGS = -c
DATA_FILE = data.txt

all: hello clean

hello: problem_TT.c
	$(CC) problem_TT.c -o start

clean:
	rm -rf *.o hello

leaks:
	leaks -atExit -- ./start < $(DATA_FILE)

run:
	./start < $(DATA_FILE)
