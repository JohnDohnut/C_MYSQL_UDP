#include "Library_DB.h"

int main(int argc, char* argv[])
{	char buffer[4096];
	library_db_t DB_CONN[1];
	Library_DB_t_init(DB_CONN);
	Library_DB_connect(DB_CONN);
	memcpy(DB_CONN->query,"select * from book",sizeof(DB_CONN->query));
	Library_DB_send_query(DB_CONN);
	Library_DB_recv_result(DB_CONN);
	//Library_DB_print_result(DB_CONN);
	Library_DB_print_result_to_buffer(DB_CONN,buffer);
	Library_DB_close_connection(DB_CONN);
	
	return 0;	
}
