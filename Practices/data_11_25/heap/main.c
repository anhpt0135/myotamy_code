#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include "dbg.h"
#include <stdint.h>

#define MAX_DATA 100

typedef struct{
	int id;
	int set;
	char name[MAX_DATA];
	char email[MAX_DATA];

}address_t;

typedef struct{
	address_t data[MAX_DATA];
}database_t;

typedef struct{
	FILE *file;
	database_t *db;
}connection_t;

connection_t *conn = NULL;

int initialize_database(void);
int deinitalize_database(connection_t *con);
void set_database(connection_t *con, int id, char *name, char *email);
void list_database(connection_t *con);

int main(int argc, char *argv[]){
	printf("Hello world !\n");
	log_info("This is a test line: %d\n", 10);
	int ret = 0;
	ret = initialize_database();
	char chr;
	char str[20];
	while(1){
		printf("Nhap vao cac ky tu lua chon sau: \
			\n\t s <id> <name> <address>: set into database \
			\n\t l: list out the database \
			\n\t a: add into the database\n\r");
		chr = getchar();
		putchar(chr);
		fgets(str, 10, stdin);
		printf("\n %s \n", str);
		switch (chr)
		{
			case 's':
			set_database(conn, 1, "anhpt", "phamanh@gmail.com");
			set_database(conn, 2, "hanhnt", "hanhnt@gmail.com");
			case 'l':
			list_database(conn);
		}
		deinitalize_database(conn);
		return 0;
	}
	return ret;
}

int initialize_database(void){
	int ret = 0;

	conn = malloc(sizeof(connection_t));
	conn->file=fopen("database.dat","w");
	conn->db = malloc(sizeof(database_t));

	if(conn == NULL)
		ret = -1;
	int i = 0;
	for(i = 0; i < MAX_DATA; i++){
		conn->db->data[i].id = i;
		conn->db->data[i].set = 0;
	}
	fwrite(conn->db, sizeof(database_t), 1, conn->file);
	fclose(conn->file);
	conn->file=fopen("database.dat","r+");
	return ret;
}

int deinitalize_database(connection_t *con){
	if(con != NULL){
		if(con->file)
			fclose(con->file);
		free(con->db);
		free(con);
	}
	return 0;
}

void set_database(connection_t *con,int id, char *name, char *email){
	database_t *idata = malloc(sizeof(database_t));
	fread(idata, sizeof(database_t), 1, con->file);
	if(idata->data[id].set == 0){
		idata->data[id].set = 1;
		idata->data[id].id = id;
		strcpy(idata->data[id].name, name);
		strcpy(idata->data[id].email, email);
	}
	memcpy(con->db, idata, sizeof(database_t));
	fwrite(con->db, sizeof(database_t), 1, con->file);
	fflush(con->file);
	free(idata);
}

void list_database(connection_t *con){
	database_t *idata = malloc(sizeof(database_t));
	fread(idata, sizeof(database_t), 1, con->file);
	int i;
	for(i = 0; i < MAX_DATA; i ++){
		if(idata->data[i].set == 1)
			printf("%d %s %s\n", idata->data[i].id, idata->data[i].name, idata->data[i].email);
	}
	free(idata);

}