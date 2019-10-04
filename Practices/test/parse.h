#ifndef _PARSE_H_
#define _PARSE_H_

typedef struct{
	char *name;
	void (*func)(void);
}cmd_t;

void user_fn(void);

void pass_fn(void);

//void command_register(cmd_t *user_func);

void fn_lookup(char *name);


#endif