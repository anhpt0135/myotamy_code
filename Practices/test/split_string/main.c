#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static void getline_func(char *sendbuff, char *tmpbuf, int lineID){
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
}



int main(void){
	FILE *ptrfile;
	ptrfile = fopen("/home/anhpt/Desktop/top.txt", "r");
	char str[1000];
	fread(str, sizeof(char), 1000, ptrfile);
	//string token
/*	char *piece = strtok(str, "\n");
	printf("%s\n", piece);
	piece = strtok(NULL, "\n");
	printf("%s\n", piece);
	piece = strtok(NULL, "\n");
	printf("%s\n", piece);*/
	char buf[2000];
	getline_func(buf, str, 0);
	//strcpy(buf, piece);
	printf("buf = %s\n", buf);

	return 0;
}