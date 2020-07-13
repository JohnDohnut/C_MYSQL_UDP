#ifndef __SERVER_H__
#define __SERVER_H__

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "../protocol/protocol.h"
#include "../Library_DB/Library_DB.h"
#define SERVER_PORT 4000


typedef struct udp_server_s udp_server_t;
struct udp_server_s{
	int SOCK;	///fd for socket
	struct sockaddr_in* server_addr;///srtucture manage server address
	library_db_t* DB_CONN;

};
udp_server_t* udp_server_init();/// Initialize and return udp_server_t*, socket() and bind(),
void udp_server_connect(udp_server_t* server);/// Server listen.
void udp_server_destroy(udp_server_t* server);/// Destroy udp_server_t* server and terminate the server. (Currently SIGINT is only way to terminate the program.)
#endif
