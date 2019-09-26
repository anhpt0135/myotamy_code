/*
 * main.c
 *
 *  Created on: Aug 2, 2019
 *      Author: anhpt
 */
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define WEB_SERVER "google.com"
#define WEB_PORT 80
#define WEB_URL "http://google.com"


static const char *REQUEST = "GET / HTTP/1.1\r\n"
    "Host: "WEB_SERVER"\r\n"
    "User-Agent: esp-idf/1.0 esp32\r\n"
    "\r\n";

const struct addrinfo hints = { .ai_family = AF_INET, .ai_socktype = SOCK_STREAM, };

int main(void) {

	struct addrinfo *res;
	struct in_addr *addr;
	int s, r;
	char recv_buf[200];

	while(1){
	int er = getaddrinfo(WEB_SERVER, "80", &hints, &res);

	while (er != 0 || res == NULL) {
		printf("DNS lookup.....\n");
		sleep(1);
		continue;
	}

	addr = &((struct sockaddr_in *) res->ai_addr)->sin_addr;

	printf("DNS lookup succeeded. IP=%s\n", inet_ntoa(*addr));

	s = socket(res->ai_family, res->ai_socktype, 0);

	while (s < 0) {
		freeaddrinfo(res);
		sleep(1);
		continue;
	}

	while (connect(s, res->ai_addr, res->ai_addrlen) != 0) {
		close(s);
		freeaddrinfo(res);
		sleep(1);
		continue;
	}

	printf("connected....\n");

	freeaddrinfo(res);

	while (write(s, REQUEST, strlen(REQUEST)) < 0) {
		close(s);
		sleep(4);
		continue;
	}

    struct timeval receiving_timeout;
    receiving_timeout.tv_sec = 5;
    receiving_timeout.tv_usec = 0;
    if (setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, &receiving_timeout,
                    sizeof(receiving_timeout)) < 0) {
                printf( "... failed to set socket receiving timeout\n");
                close(s);
                sleep(4);
                continue;
            }
	printf("Set socket receiving timeout success\n");
    do {
        bzero(recv_buf, sizeof(recv_buf));
        printf("reading the buffer \n");
        r = read(s, recv_buf, sizeof(recv_buf)-1);
        printf("finished readding the buffer\n");
        printf("\n %s", recv_buf);
        int i;
        for(i = 0; i < r; i++) {
            putchar(recv_buf[i]);
        }
    } while(r > 0);;
	printf("\n %s", recv_buf);
	close(s);
	sleep(5);

}

}
