CC=gcc
src=$(wildcard *.c ./paho.mqtt.embedded-c/MQTTClient-C/src/*.c ./paho.mqtt.embedded-c/MQTTPacket/src/*.c)

obj=$(src:.c=.o)

target=ouput

CFLAGS=-g -v -Wall -Werror

all:
	$(CC) $(CFLAGS) $(obj) -o $(target) 
	$(MAKE) -C mbedtls-2.16.3/

clean:
	rm -rf *.o $(target) ./paho.mqtt.embedded-c/MQTTClient-C/src/*.o ./paho.mqtt.embedded-c/MQTTPacket/src/*.o