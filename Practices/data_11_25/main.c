#include <stdio.h>
#include <stdlib.h>
#include "dbg.h"
#include "heap_stack_allocation.h"

int main(int argc, char *argv[]){
	FILE *fp;
	fp = fopen("prog.log", "a");
	log_info("This is the log infor");
	log_err("This is the log error = %d", 10);
	fclose(fp);

	if(argc < 3){
		printf("wrong syntax, follow this: output <database> <option> [<parameters>]\n");
		return 1;
	}
	char option = argv[2][0];
	struct Connection *conn = Database_open(argv[1],option);
	int ret = 0;

	switch(option){
		case 'c':
		ret = create_database(conn);
		break;
		case 's':
		ret = set_to_database(conn,argv[3], argv[4], argv[5]);
		break;
		case 'g':
		ret = get_from_database(conn, argv[3]);
		break;
		case 'l':
		ret = list_out_from_database(conn);
		break;
		case 'd':
		ret = delete_id_in_database(conn, argv[3]);
		break;

		default:
		printf("Invalid option\n");
		break;
	}

	Database_close(conn);
	return ret;
}

