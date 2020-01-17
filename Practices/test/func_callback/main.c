#include <stdio.h>
#include <string.h>
#include "lib.h"

void callback(BUTTON_T button){
	if(button.pressTime == 1){
		printf("Function callback !!!!!!!!!\n");
	}
}

int main(void){
	printf("Hello world!\n");
	hw_register_function_callback(callback);
	return 0;
}