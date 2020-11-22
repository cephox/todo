CC = gcc
src = $(wildcard src/*.c)

build: clean
	$(CC) -o todo $(src)

clean:
	rm -f todo
