src=$(wildcard *.c)
obj=$(src:.c=.o)
target=output
CC=gcc

CFLAGS=-Wall -g -I.
LDFLAGS=

$(target):$(obj)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -rf *.o $(target)
