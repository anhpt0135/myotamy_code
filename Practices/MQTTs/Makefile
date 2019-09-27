CC=gcc
src=$(wildcard *.c)
src+=$(wildcard ./paho.mqtt.embedded-c/MQTTClient-C/src/*.c)
src+=$(wildcard ./paho.mqtt.embedded-c/MQTTPacket/src/*.c)
src+=$(wildcard ./paho.mqtt.embedded-c/MQTTClient-C/src/linux/*.c)

obj=$(src:.c=.o)

target=ouput

CFLAGS=-g -v -Wall -Werror -I. -I./paho.mqtt.embedded-c/MQTTClient-C/src/ -I./paho.mqtt.embedded-c/MQTTPacket/src/ 
CFLAGS+=-I./paho.mqtt.embedded-c/MQTTClient-C/src/linux/

LDFLAGS=-L/mbedtls-2.16.3/library -lmbedcrypto -lmbedtls -lmbedx509

$(target):$(obj)$(mbedtls)
	$(CC) $(CFLAGS) $(obj) -o $(target) $(LDFLAGS)
	
mbedtls:
	CC=arm-linux-gcc SHARED=yes $(MAKE) -C mbedtls-2.16.3/library

clean:
	rm -rf *.o $(target) ./paho.mqtt.embedded-c/MQTTClient-C/src/*.o
	$(MAKE) -C mbedtls-2.16.3/ clean