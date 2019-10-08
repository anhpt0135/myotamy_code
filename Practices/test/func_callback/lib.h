#ifndef _lib_h_
#define _lib_h_

typedef void(*func_callback_t)(void);//nen dat ten khac

typedef struct{
	char *name;
	func_callback_t func;
}camdb_t;

typedef void (*cam_func_callback_t)(camdb_t *camdbb,int *size );

void lib_register(cam_func_callback_t func);
void run(char *string);

#endif