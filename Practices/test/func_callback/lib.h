#ifndef _lib_h_
#define _lib_h_

typedef struct{
	char *name;
	int pressTime;
}BUTTON_T;

typedef void(*CALLBACKFUNC)(BUTTON_T button);

void hw_register_function_callback(CALLBACKFUNC func);

#endif