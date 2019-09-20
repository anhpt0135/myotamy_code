#include <stdio.h>
#include <string.h>

int read_file_by_line(char *path, char *buff, int line_num, int size){
	int ret = 0;
	FILE *fp;
	fp = fopen(path, "r");
	char ch;
	int i=0;
	int line = 0;
	if(fp == NULL){
		printf("Cannot load file %s\n", path);
		return -1;
	}

	while(1){
		ch = fgetc(fp);
		if(ch == EOF){
			printf("end of file\n");
			break;
		}
		if(line == (line_num -1)){
			if(ch != '\n'){
				buff[i] = ch;
				i++;
				if(i >= size){
					printf("out of buffer\n");
					return 0;
				}
			}
		}
		if(ch == '\n')
			line++;
	}
	return ret;
}

int main()
{
    char buff[12];
    printf("Hello World\n");
    read_file_by_line("/home/anhpt/Desktop/string.txt", buff, 1, sizeof(buff));
    printf("%s", buff);

    return 0;
}