src=$(wildcard *.c)
obj=$(src:.c=.o)
target=hb_httpserver

CFLAGS=-g -Wall -Werror -I.
LDFLAGS=

$(target):$(obj)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm -rf *.o $(target)  