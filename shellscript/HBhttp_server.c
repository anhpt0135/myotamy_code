/*	@file:HBhttp_server.c
	@author: Tuan Anh
	@date: Oct 3rd, 2019
	@brief:
	Receive the following http commands:
	-get_memory:http://127.0.0.1:12121/?action=command=get_memory
	-get_cpu:http://127.0.0.1:12121/?action=command=get_cpu
	-get_disk:http://127.0.0.1:12121/?action=command=get_disk
	and response with the required information
*/
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#define SERVER_PORT 12121

int main(void){
	int ret = 0;
	int opt = 1;
	int sockfd, newsocket, valread;
	struct sockaddr_in address;
	int addrlen = sizeof(address); 
	char buf[]= "Doi nguoi chi song mot lan";
	char header[] = "HTTP/1.1 200 OK\r\n"				\
					"Connection: close\r\n"				\
					"Content-Type: text/plain\r\n"		\
					"Content-Length: %d\r\n\r\n";		
	char hello[120];

	while(1){
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == 0){
		printf("cannot create a socket! \n");
		return -1;
	}
	// setsockopt helps in reuse of address and port, prevent error such as: "address
	// already in use"
	ret = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
	if(ret != 0){
		printf("error when using setsockopt\n");
		return -1;
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(SERVER_PORT);

	if(bind(sockfd, (struct sockaddr *)&address, sizeof(address)) < 0){
		printf("cannot bind the address with port");
		return -1;
	}

	if(listen(sockfd, 3) < 0){
		printf("listen failed\n");
		return -1;
	}

		char buffer[1024] = {0};
		printf("Waiting new connection new connection\n");
		newsocket = accept(sockfd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
		if(newsocket == 0){
			printf("cannot create a new socket for the new connection\n");
			return -1;
		}

		valread = read(newsocket, buffer, sizeof(buffer));
		if(valread < 0){
			printf("cannot read the buffer");
			return -1;
		}

		printf("%s \n", buffer);
		sprintf(hello, header,sizeof(buf));
		printf("%s\n",hello);
		write(newsocket, hello, sizeof(buf));
		sprintf(hello, "%s\r\n", buf);
		write(newsocket, buf, sizeof(buf));
		printf("%s\n",hello);
		close(newsocket);
		close(sockfd);

	}
	return 0;
}