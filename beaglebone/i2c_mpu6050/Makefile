target=mpu6050
src=$(wildcard *.c)
obj=$(src:.c=.o)

CFLAGS=-Wall -Werror -g

all:$(target)

$(target):$(obj)
	$(CC) $(CFLAGS) -o $@ $^
clear:
	rm -rf *.o $(target)

.PHONY: all $(target) clear
