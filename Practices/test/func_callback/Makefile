src=$(wildcard *.c)
obj=$(src:.c=.o)
target=output


CFLAGS=-Wall -Werror -g

$(target):$(obj)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf *.o $(target)


