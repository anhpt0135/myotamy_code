CC=gcc
src=$(wildcard *.c)
obj=$(src:.c=.o)
target=output

CFLAGS=-Wall -Werror -g -I.

$(target):$(obj)
	$(CC) $(CFLAGS) -o $(target) $^

callback:
	$(MAKE) -C func_callback/

clean:
	rm -rf *.o $(target)
	$(MAKE) -C func_callback/ clean
