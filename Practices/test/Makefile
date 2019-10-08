CC=gcc
src=$(wildcard *.c)
obj=$(src:.c=.o)
target=output

CFLAGS=-Wall -Werror -g -I.

$(target):$(obj)
	$(CC) $(CFLAGS) -o $(target) $^

callback:
	$(MAKE) -C func_callback/

splitstring:
	$(MAKE) -C split_string/

clean:
	rm -rf *.o $(target)
	$(MAKE) -C func_callback/ clean
	$(MAKE) -C split_string/ clean
