CC=gcc
src=$(wildcard *.c)
src+=$(wildcard ./paho.mqtt.embedded-c/MQTTClient-C/src/*.c)
src+=$(wildcard ./paho.mqtt.embedded-c/MQTTPacket/src/*.c)
src+=$(wildcard ./paho.mqtt.embedded-c/MQTTClient-C/src/linux/*.c)

obj=$(src:.c=.o)

target=ouput

CFLAGS=-g -v -Wall -Werror -I. -I./paho.mqtt.embedded-c/MQTTClient-C/src/ -I./paho.mqtt.embedded-c/MQTTPacket/src/ 
CFLAGS+=-I./paho.mqtt.embedded-c/MQTTClient-C/src/linux/

$(target):$(obj)
	$(CC) $(CFLAGS) $(obj) -o $(target) 
	$(MAKE) -C mbedtls-2.16.3/

clean:
	rm -rf *.o $(target) ./paho.mqtt.embedded-c/MQTTClient-C/src/*.o ./paho.mqtt.embedded-c/MQTTPacket/src/*.o