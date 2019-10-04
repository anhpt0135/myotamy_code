CC=gcc
src=$(wildcard *.c)
obj=$(src:.c=.o)
target=output

CFLAGS=-Wall -Werror -g -I.

$(target):$(obj)
	$(CC) $(CFLAGS) -o $(target) $^

clean:
	rm -rf *.o $(target)