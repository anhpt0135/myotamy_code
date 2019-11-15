#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*static void getline_func(char *sendbuff, char *tmpbuf, int lineID){
  int ilineID = lineID;
  char *tmppiece;
  char *piece = strtok(tmpbuf, "\n");
  if(ilineID <= 0){
	  printf("lineID is wrong!!!");
	  return;
  }
  while(--ilineID){
      piece = strtok(NULL, "\n");
  }
  tmppiece = strtok(piece, ":");
  tmppiece = strtok(NULL, "\n");
  strcpy(sendbuff, tmppiece);
  printf("%s", tmppiece);
}*/

static void get_from_line_to_line(char *sendbuff, char *tmpbuf, int lineID){
	char buff[2][100];
	int ilineID = lineID;
  	char *piece = strtok(tmpbuf, "\n");
	//int i=0, j = 0;
	if(ilineID <= 0){
		printf("input line is wrong!!!");
		return;
  	} else {
  		/*for(i=ibegin_line; i <= idest_line; i++){
  			getline_func(buff[j],tmpbuf, i);
  			printf("%s", buff[j]);
  			j++;
  		}*/
  		strcpy(buff[0], piece);

  		//printf("%s", buff[0]);
  		piece = strtok(NULL, "\n");
  		strcpy(buff[1], piece);
  		strcat(buff[0], "\n");
  		strcat(buff[0], buff[1]);
  		strcpy(sendbuff, buff[0]);
  		printf("%s", sendbuff);

  	}

  	//strcpy(sendbuff, buff[0]);
  	//strcpy(sendbuff + 100, buff[1]);
  	//getline_func(buff[0], tmpbuf, 1);
  	//getline_func(buff[1], tmpbuf, 2);

}

int main(void){
	FILE *ptrfile;
	ptrfile = fopen("/home/anhpt/Desktop/top.txt", "r");
	char str[500];
	fread(str, sizeof(char), 500, ptrfile);
	//string token
/*	char *piece = strtok(str, "\n");
	printf("%s\n", piece);
	piece = strtok(NULL, "\n");
	printf("%s\n", piece);
	piece = strtok(NULL, "\n");
	printf("%s\n", piece);*/
	char buf[1000];
	//getline_func(buf, str, 1);
	//getline_func(buf, str, 2);
	get_from_line_to_line(buf, str, 2);
	//strcpy(buf, piece);
	//printf("buf = %s\n", buf);

	return 0;
}