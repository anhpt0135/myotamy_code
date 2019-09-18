#ifndef _heap_stack_allocation_h_
#define _heap_stack_allocation_h_

#define MAX_DATA 512
#define MAX_ROWS 100

struct Address{
	int id;
	int set;
	char name[MAX_DATA];
	char email[MAX_DATA];
};


struct Database{
	struct Address rows[MAX_ROWS];
};

struct Connection{
	FILE *file;
	struct Database *db;
};

struct Connection *Database_open(char *name, char mode);
int create_database(struct Connection *conn);
int set_to_database(struct Connection *conn, char *id, char * name, char *email);
int get_from_database(struct Connection *conn, char *id);
int list_out_from_database(struct Connection *conn);
int delete_id_in_database(struct Connection *conn, char*id);
int Database_close(struct Connection *conn);

#endif