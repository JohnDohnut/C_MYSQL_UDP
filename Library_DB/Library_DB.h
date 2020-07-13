#ifndef __LIBRARY_DB_H__
#define __LIBRARY_DB_H__
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include <mysql.h>

#define ADDRESS "127.0.0.1"
#define GUEST_ID "guest"
#define GUEST_PW "1234"
#define DB_NAME "LibraryDB"
#define PORT 3306

typedef struct library_db_s library_db_t;
struct library_db_s{
	MYSQL mysql;
	char query[1024];
	MYSQL_RES* result;
	int num_fields;
	MYSQL_ROW num_row;
};

int Library_DB_t_init(library_db_t* DB_CONN);
int Library_DB_close_connection(library_db_t* DB_CONN);
int Library_DB_send_query(library_db_t* DB_CONN);
int Library_DB_recv_result(library_db_t* DB_CONN);
int Library_DB_print_result(library_db_t* DB_CONN);

#endif
