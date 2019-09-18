#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "heap_stack_allocation.h"

static void Database_load(struct Connection *conn){
	fread(conn->db, sizeof(struct Database),1, conn->file);
}

struct Connection *Database_open(char *name, char mode){
	struct Connection *conn;
	conn = malloc(sizeof(struct Connection));
	conn->db = malloc(sizeof(struct Database));
	if(mode == 'c'){
		conn->file = fopen(name, "w");
	}else{
		conn->file = fopen(name, "r+");
		Database_load(conn);
	}

	return conn;
}

static int Database_write(struct Connection *conn){
	printf("In function Database_write\n");
	rewind(conn->file);
	fwrite(conn->db, sizeof(struct Database),1, conn->file);
	fflush(conn->file);
	return 0;
}

int Database_close(struct Connection *conn){
	if(conn != NULL){
		fclose(conn->file);
		free(conn->db);
		free(conn);
	}
	return 0;	
}

int create_database(struct Connection *conn){
	int i=0;
	int ret =0;
	for(i=0; i < MAX_ROWS; i++){
		struct Address addr = {.id=i, .set=0};
		conn->db->rows[i] = addr;
	}
	ret = Database_write(conn); 
	if(ret == 0)
		return -1;
	return 0;
}

int set_to_database(struct Connection *conn, char *id, char * name, char *email){

	int i;
	i = atoi(id);
	printf("In function set_to_database\n");
	conn->db->rows[i].id = i;
	conn->db->rows[i].set = 1;
	strncpy(conn->db->rows[i].name, name, MAX_DATA);
	strncpy(conn->db->rows[i].email, email, MAX_DATA);
	Database_write(conn);
	return 0;
}

int get_from_database(struct Connection *conn, char *id){


	return 0;
}

int list_out_from_database(struct Connection *conn){
	int i;
	printf("In function list_out_from_database\n");
	for(i = 0; i < MAX_ROWS; i++){
		if(conn->db->rows[i].set == 1){
			printf("%d  %s   %s\n", conn->db->rows[i].id,
				conn->db->rows[i].name,
				conn->db->rows[i].email);
		}
	}
	return 0;
}

int delete_id_in_database(struct Connection *conn, char *id){
	return 0;
}

