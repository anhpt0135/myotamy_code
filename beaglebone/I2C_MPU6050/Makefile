target=mpu6050
src=$(wildcard *.c)
obj=$(src:.c=.o)

CFLAGS=-Wall -Werror -g

.PHONY: mpu6050 clean all

all:$(target)

$(target):$(obj)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf *.o $(target)

