#include <stdio.h>
#include <string.h>
#include "lib.h"
void pass_func(void){
	printf("This is pass func\n");
}

void user_func(void){
	printf("This is user func\n");
}

camdb_t gcamdb[]={{"user", user_func},{"pass", pass_func}};

void callback(camdb_t *ptrcamdb, int *size){
	*size = sizeof(gcamdb)/sizeof(gcamdb[0]);
	memcpy(ptrcamdb, gcamdb, *size);
}

int main(void){
	printf("Hello world!\n");
	lib_register(&callback);
	run("user");
	return 0;
}