#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib.h"

camdb_t *gcamdb = NULL;
cam_func_callback_t gfunc_callback;
int gsize;

void lib_register(cam_func_callback_t func){
	gfunc_callback = func;

}
void run(char *string){
	gfunc_callback(gcamdb, &gsize);
	int i;
	for(i = 0; i < gsize; i++){
		if((gcamdb != NULL) && (strcmp(gcamdb[i].name, string) == 0)){
			gcamdb[i].func();
		}
	}
}
