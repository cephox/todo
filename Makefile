CC = gcc
src = $(wildcard src/*.c)

bindir = /usr/bin
name = todo

build: clean
	$(CC) -o $(name) $(src)

clean:
	rm -f $(name)

install:
	install --mode=755 $(name) $(bindir)/

uninstall:
	rm -f $(bindir)/$(name)

