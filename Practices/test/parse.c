#include <stdio.h>
#include <string.h>
#include "parse.h"

void user_fn(){
	printf("USER fn\n");
} 

void pass_fn(){
	printf("PASS fn\n");
}

cmd_t cmd_table[]={{"USER", user_fn},
				   {"PASS", pass_fn}};

void fn_lookup(char *name){
	int i;
	for(i=0 ; i < 2; i ++){
		if(strcmp(cmd_table[i].name, name) == 0){
			cmd_table[i].func();
		}
	}
}
