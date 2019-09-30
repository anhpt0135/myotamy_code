#include "mqtts.h"
#include "MQTTClient.h"

#define SERVER_PORT "443"
#define SERVER_NAME "mqtt.thingspeak.com"
#define MQTT_BUF_SIZE 1000
#define MQTT_WEBSOCKET 1  // 0=no 1=yes

static unsigned char mqtt_sendBuf[MQTT_BUF_SIZE];
static unsigned char mqtt_readBuf[MQTT_BUF_SIZE];

Network n;
MQTTClient c;

void mqtts_task(void){
	//MQTTs init
	 /*
     * 0. Initialize the RNG and the session data
     */

	Tls_sessionInit(&n);
	//Network connect 
	NetworkConnect(&n, SERVER_NAME, SERVER_PORT);
	//MQTTClientInit
	MQTTClientInit(&c, &n, 
		2000,//unsigned int command_timeout_ms,
		mqtt_sendBuf, //unsigned char* sendbuf, 
		sizeof(mqtt_sendBuf), //size_t sendbuf_size, 
		mqtt_readBuf, //unsigned char* readbuf, 
		sizeof(mqtt_readBuf));//size_t readbuf_size)
	//MQTTConnect
	MQTTString clientId = MQTTString_initializer;
	clientId.cstring = "ESP32MQTT";

	MQTTPacket_connectData data = MQTTPacket_connectData_initializer;
	data.clientID          = clientId;
	data.willFlag          = 0;
	data.MQTTVersion       = 4; // 3 = 3.1 4 = 3.1.1
	data.keepAliveInterval = 60;
	data.cleansession      = 1;
	MQTTConnect(&c, &data);

}

int main(void){
	mqtts_task();
	return 0;
}