CC=gcc
src=$(wildcard *.c)
src+=$(wildcard ./paho.mqtt.embedded-c/MQTTClient-C/src/*.c)
src+=$(wildcard ./paho.mqtt.embedded-c/MQTTPacket/src/*.c)
#src+=$(wildcard ./paho.mqtt.embedded-c/MQTTClient-C/src/linux/*.c)

obj=$(src:.c=.o)

target=ouput

CFLAGS=-g -Wall -Werror -I. -I./paho.mqtt.embedded-c/MQTTClient-C/src/ -I./paho.mqtt.embedded-c/MQTTPacket/src/ 
#CFLAGS+=-I./paho.mqtt.embedded-c/MQTTClient-C/src/linux/ 
CFLAGS+=-I./mbedtls-2.16.3/include

LDFLAGS=-L./mbedtls-2.16.3/library -lmbedtls -lmbedcrypto -lmbedx509

$(target):$(obj)
	$(CC) $(CFLAGS) $(obj) -o $(target) $(LDFLAGS)
	
mbedtls:
	CC=gcc $(MAKE) -C mbedtls-2.16.3/library

clean:
	rm -rf *.o $(target) ./paho.mqtt.embedded-c/MQTTClient-C/src/*.o
	$(MAKE) -C mbedtls-2.16.3/ clean