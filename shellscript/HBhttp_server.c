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
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <time.h>

#define PORT 12121
int main(int argc, char const *argv[])
{
    int server_fd, new_socket; ;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    time_t timer;
    
    // Only this line has been changed. Everything is same.
    char *header = "HTTP/1.1 200 OK\n"				\
    			  "Content-Type: text/plain\n"		\
    			  "Content-Length: %d\n\n"			\
    			  "%s\n%s";
    
    char *content = "Welcome to the server page! \n\n HAVE A NICE DAY!!!!";

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("In socket");
        exit(EXIT_FAILURE);
    }
    
    int enable = 1;
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0){
    	printf("setsockopt(SO_REUSEADDR) failed");
    	return -1;
	}

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
    
   // memset(address.sin_zero, '\0', sizeof address.sin_zero);
    
    
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0)
    {
        perror("In bind");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("In listen");
        exit(EXIT_FAILURE);
    }
    
    while(1)
    {
        printf("\n+++++++ Waiting for new connection ++++++++\n\n");
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
        {
            perror("In accept");
            exit(EXIT_FAILURE);
        }
        
        char buffer[30000] = {0};
        time(&timer);
        char buftime[200];
        sprintf(buftime, "%s", ctime(&timer));
        int len = strlen(content) + strlen(buftime);
   		char buf[500];
   		sprintf(buf, header, len, ctime(&timer), content);
        read( new_socket , buffer, 30000);
        //if(cmd_parse(buffer, buf) != 0){
        //	printf("Unsupported command");
        //	return -1;
        //}
        printf("%s\n",buffer );
        write(new_socket , buf , strlen(buf));
        printf("------------------Hello message sent-------------------");
        close(new_socket);
    }
    return 0;
}