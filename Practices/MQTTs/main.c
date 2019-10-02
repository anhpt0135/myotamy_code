#include "mqtts.h"
#include "MQTTClient.h"

#define MQTT_SERVER "mqtt.thingspeak.com"
#define MQTT_PORT 443
//#define MQTT_PORT 1883
#define MQTT_BUF_SIZE 1000
#define MQTT_WEBSOCKET 1  // 0=no 1=yes

static unsigned char mqtt_sendBuf[MQTT_BUF_SIZE];
static unsigned char mqtt_readBuf[MQTT_BUF_SIZE];

Network network;
MQTTClient client;

void mqtts_task(void){
	//MQTTs init
	 /*
     * 0. Initialize the RNG and the session data
     */
		int ret = 0;
		printf( "Connected to AP");

		printf( "Start MQTT Task ...");

		MQTTClient client;
		NetworkInit(&network);
		network.websocket = MQTT_WEBSOCKET;

		printf("NetworkConnect %s:%d ...",MQTT_SERVER,MQTT_PORT);
		NetworkConnect(&network, MQTT_SERVER, MQTT_PORT);
		printf("MQTTClientInit  ...");
		MQTTClientInit(&client, &network,
			2000,            // command_timeout_ms
			mqtt_sendBuf,         //sendbuf,
			MQTT_BUF_SIZE, //sendbuf_size,
			mqtt_readBuf,         //readbuf,
			MQTT_BUF_SIZE  //readbuf_size
		);

		MQTTString clientId = MQTTString_initializer;
		clientId.cstring = "ESP32MQTT";

		MQTTPacket_connectData data = MQTTPacket_connectData_initializer;
		data.clientID          = clientId;
		data.willFlag          = 0;
		data.MQTTVersion       = 4; // 3 = 3.1 4 = 3.1.1
		data.keepAliveInterval = 60;
		data.cleansession      = 1;

		printf("MQTTConnect  ...");
		ret = MQTTConnect(&client, &data);
		if (ret != SUCCESS) {
			printf( "MQTTConnect not SUCCESS: %d", ret);
			goto exit;
		}

		char msgbuf[100];
		for (int i=0;i<5;i++) {

			MQTTMessage message;
			sprintf(msgbuf, "field1=%d&field2=%lf",(uint8_t)(rand()&0xFF),(double)((rand()&0xFFFF)/10));

			printf( "MQTTPublish  ... %s",msgbuf);
			message.qos = QOS0;
			message.retained = 0;
			message.dup = 0;
			message.payload = (void*)msgbuf;
			message.payloadlen = strlen(msgbuf)+1;

			ret = MQTTPublish(&client, "channels/875984/publish/3FI3H6MY2RBPYC7R", &message);
			if (ret != SUCCESS) {
				printf( "MQTTPublish not SUCCESS: %d", ret);
				goto exit;
			}
			for(int countdown = 30; countdown >= 0; countdown--) {
				if(countdown%10==0) {
					printf( "%d...", countdown);
				}
				sleep(1);
			}
		}
		exit:
			MQTTDisconnect(&client);
			NetworkDisconnect(&network);
			for(int countdown = 60; countdown >= 0; countdown--) {
				if(countdown%10==0) {
					printf( "%d...", countdown);
				}
				sleep(1);
			}
			printf( "Starting again!");
    }
	

int main(void){
	mqtts_task();
	return 0;
}