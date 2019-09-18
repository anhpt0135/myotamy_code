src=$(wildcard *.c)
obj=$(src: .c=.o)
target=output

CFLAGS=-Wall -g -I.
LDFLAGS=
CC=gcc

$(target):$(obj)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -rf *.o $(target)
