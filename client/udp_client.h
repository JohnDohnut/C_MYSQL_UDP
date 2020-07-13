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

#define SERVER_PORT 4000 /// server port 
/**
*@struct udp_client_s
*@brief struct to contain FD of SOCKET and sockaddr_in* of server_addr
*/
typedef struct udp_client_s udp_client_t;
struct udp_client_s{
	int SOCK;///SOCKET for client
	struct sockaddr_in* server_addr;///struct for server address
};
udp_client_t* udp_client_init();
void udp_client_connect(udp_client_t* client);
void udp_client_destroy(udp_client_t* client);

#endif
