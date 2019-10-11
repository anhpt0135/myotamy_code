src=$(wildcard *.c)
#obj=$(src:.c=.o)  <==> obj=$(patsubst <cac file c>, <cac file o>, $(src))
obj=$(patsubst %.c, %.o, $(src))
target=output

CFLAGS=-Wall -Werror -g $(OPTFLAGS)

$(target):$(obj)
	$(CC) -o $@ $(CFLAGS) $^

clean:
	rm -rf *.o $(target)