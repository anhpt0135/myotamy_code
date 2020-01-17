#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib.h"

CALLBACKFUNC g_function = NULL;
BUTTON_T g_button;

void fakeEventFunc(BUTTON_T *button){
	button->pressTime = 3;
}

void hw_register_function_callback(CALLBACKFUNC func){
	g_function = func;
	fakeEventFunc(&g_button);
	if(g_function != NULL)
		g_function(g_button);
}