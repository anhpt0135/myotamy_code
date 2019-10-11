src=$(wildcard *.c)
obj=$(src:.c=.o)
target=output

CFLAGS=-Wall -Werror -g

$(target):$(obj)
	$(CC) -o $@ $(CFLAGS) $^

clean:
	rm -rf *.o $(target)