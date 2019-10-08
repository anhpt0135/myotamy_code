/*	@file:HBhttp_server.c
	@author: Tuan Anh
	@date: Oct 3rd, 2019
	@brief:
	Receive the following http commands:
	-get_memory:http://127.0.0.1:12121/?action=command&command=get_memory
	-get_cpu:http://127.0.0.1:12121/?action=command&command=get_cpu
	-get_disk:http://127.0.0.1:12121/?action=command&command=get_disk
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
#define FILE_MEM_INFO "/proc/meminfo"
#define FILE_CPU_STATE "/proc/stat"

typedef struct{
	char *name;
	void (*func)(char *output_buf);
}cmddb_t;

void get_mem_info_func(char *output_buf);
void get_cpu_info_func(char *output_buf);

cmddb_t gcmd[]=	{{"get_memory", get_mem_info_func},
		 		{"get_cpu", get_cpu_info_func}};

void format_time(char *output){
    time_t rawtime;
    struct tm * timeinfo;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );

    sprintf(output, "[%d %d %d %d:%d:%d]",timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
}

void cmd_parse(char *input_buffer,char *parse_buff){
	char *piece;
	piece=strtok(input_buffer, "=");
	piece=strtok(NULL, "=");
	piece=strtok(NULL, " ");
	strcpy(parse_buff, piece);
	//printf("%s\n", parse_buff);
}

int vtable(char *input_buf,char *result){
	int i;
	int size = sizeof(gcmd)/sizeof(gcmd[0]);
	for(i = 0; i < size; i ++){
		if(strcmp(input_buf, gcmd[i].name) == 0){
			if(gcmd[i].func!= NULL){
				gcmd[i].func(result);
				return 0;
			}
		}
	}
	return -1;
}

int main(int argc, char const *argv[])
{
    int server_fd, new_socket; ;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    
    // Only this line has been changed. Everything is same.
    char *header = "HTTP/1.1 200 OK\n"				\
    			  "Content-Type: text/plain\n"		\
    			  "Content-Length: %d\n\n"			\
    			  "%s\n%s";
    

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
    
    char sent_buff[1500];
    char recv_buff[500] = {0};
    char parse_buff[50];
    char buftime[50];
    char content[450];
    int len = 0;

    while(1)
    {	
    	//char content[1000]; //= "Welcome to the server page! \n\n HAVE A NICE DAY!!!!";
        printf("\n+++++++ Waiting for new connection ++++++++\n\n");
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
        {
            perror("In accept");
            exit(EXIT_FAILURE);
        }

        format_time(buftime);
        read( new_socket , recv_buff, sizeof(recv_buff)/sizeof(recv_buff[0]));
        printf("%s\n",recv_buff );
        cmd_parse(recv_buff,parse_buff);
        if(vtable(parse_buff,content)< 0){
        	strcpy(content, "Unsupported Command ");
        }
        len = strlen(buftime) + strlen(content);
        sprintf(sent_buff, header, len, buftime, content);
        write(new_socket , sent_buff , strlen(sent_buff));
        printf("------------------reply message sent-------------------");
        close(new_socket);
    }
    return 0;
}

void get_mem_info_func(char *output_buf){
	char icontent[800];
	FILE *ptrfile = NULL;
	ptrfile = fopen(FILE_MEM_INFO, "r");
    fread(icontent, sizeof(char), sizeof(icontent), ptrfile);
    strcpy(output_buf, icontent);
    fclose(ptrfile);
}

void get_cpu_info_func(char *output_buf){
	char icontent[800];
	FILE *ptrfile = NULL;
	ptrfile = fopen(FILE_CPU_STATE, "r");
    fread(icontent, sizeof(char), sizeof(icontent), ptrfile);
    strcpy(output_buf, icontent);
    fclose(ptrfile);
}