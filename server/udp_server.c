#include "udp_server.h"

/**
*@brief initialize and return udp_server_t*
*@return udp_server_t*
*@detail
*initializing process includes socket() and bind()
*using port 4000.
*if fail to socket() or bind(), exit program.
*/
udp_server_t* udp_server_init(){
	udp_server_t* server = malloc(sizeof(udp_server_t));	
	server->server_addr = malloc(sizeof(struct sockaddr_in));
	memset(server->server_addr,0,sizeof(struct sockaddr_in));
	server->server_addr->sin_family = AF_INET;
	server->server_addr->sin_port = htons(SERVER_PORT);
	server->server_addr->sin_addr.s_addr=htonl(INADDR_ANY);
	server->SOCK = socket(PF_INET,SOCK_DGRAM,0);
	if(server->SOCK <0){
		printf("socket() failed\n");
		free(server);
		exit(0);	
	}
	if(bind(server->SOCK, (struct sockaddr*)server->server_addr, sizeof(struct sockaddr))<0){
		printf("bind() faild\n");
		close(server->SOCK);
		free(server);
		exit(1);
	}
	///mysql init	
	library_db_t* DB_CONN = malloc(sizeof(library_db_t));
	Library_DB_t_init(DB_CONN);
	Library_DB_connect(DB_CONN);
	server->DB_CONN = DB_CONN;
	return server;
}
/**
*@brief echo server listen and send message back to client.
*@param udp_server_t*
*@detail
*If message == "/quit", then don't send back.
*/
void udp_server_connect(udp_server_t* server){
	int i;
	protocol_packet_t* send_packet = protocol_packet_init();
	protocol_packet_t* recv_packet = protocol_packet_init();
	printf("connecting...\n");
	printf("SOCK no : %d\n",server->SOCK);
	if(server->SOCK <=0){
		free(server);
		printf("socket fd error while connection\n");
		exit(1);
	}
	struct sockaddr_in client_addr;
	int addr_len = sizeof(struct sockaddr);
	ssize_t recv_bytes;
	memset(&client_addr,0,addr_len);
	printf("client addr struct init done...\n");
	char cmd[4];
	memset(cmd,0,sizeof(cmd));
	int QUERY_RES;
	while(1){
		if(QUERY_RES ==0){
			library_db_t* DB_CONN = malloc(sizeof(library_db_t));
			Library_DB_t_init(DB_CONN);
			Library_DB_connect(DB_CONN);
			server->DB_CONN = DB_CONN;
		}
		printf("waiting for msg\n");
		recv_bytes = recvfrom(server->SOCK, recv_packet,sizeof(*recv_packet),0,(struct sockaddr*)(&client_addr),&addr_len);
		if(recv_bytes<=0){
			printf("failed to receive data\n");
			break;
		}
		else{	
			if(recv_packet->header.data_type== 2) // seq_id == 2 : client sent /quit
				continue;
			else{			
				protocol_print_message(recv_packet);
				recv_packet->data[DATA_MAX_LENGTH-1] = '\0';
				memcpy(cmd,recv_packet->data,sizeof("/q"));
				if(memcmp(cmd, "/q ",3)==0){

					memcpy(server->DB_CONN->query,recv_packet->data+3,sizeof(server->DB_CONN->query));
					QUERY_RES = Library_DB_send_query(server->DB_CONN)
					if(QUERY_RES !=0){
						memcpy(send_packet,recv_packet,sizeof(*send_packet));
						memcpy(send_packet->data,"query failed.",sizeof(send_packet->data));
						sendto(server->SOCK,send_packet,sizeof(*send_packet), 0, (struct sockaddr*)(&client_addr), sizeof(client_addr));
						protocol_clean_packet(send_packet);
						protocol_clean_packet(recv_packet);
						protocol_increase_seq_id(send_packet);
						continue;
					}
					QUERY_RES = Library_DB_recv_result(server->DB_CONN);
					if(QUERY_RES !=0){
						memcpy(send_packet,recv_packet,sizeof(*send_packet));
						memcpy(send_packet->data,"query failed.",sizeof(send_packet->data));
						
						sendto(server->SOCK,send_packet,sizeof(*send_packet), 0, (struct sockaddr*)(&client_addr), sizeof(client_addr));
						protocol_clean_packet(send_packet);
						protocol_clean_packet(recv_packet);
						protocol_increase_seq_id(send_packet);
						continue;
					}
					QUERY_RES = Library_DB_print_result_to_buffer(server->DB_CONN,send_packet->data);
					if(QUERY_RES !=0){
						memcpy(send_packet,recv_packet,sizeof(*send_packet));
						memcpy(send_packet->data,"query failed.",sizeof(send_packet->data));			
						sendto(server->SOCK,send_packet,sizeof(*send_packet), 0, (struct sockaddr*)(&client_addr), sizeof(client_addr));
						protocol_clean_packet(send_packet);
						protocol_clean_packet(recv_packet);
						protocol_increase_seq_id(send_packet);
						continue;
					}
					sendto(server->SOCK,send_packet,sizeof(*send_packet), 0, (struct sockaddr*)(&client_addr), sizeof(client_addr));
					continue;
					
				}
				memcpy(send_packet,recv_packet,sizeof(*send_packet));
				sendto(server->SOCK,send_packet,sizeof(*send_packet), 0, (struct sockaddr*)(&client_addr), sizeof(client_addr));
			}
		}
		protocol_clean_packet(send_packet);
		protocol_clean_packet(recv_packet);
		protocol_increase_seq_id(send_packet);

		
	}
		
}

/**
*@brief release udp_server_t*
*@param udp_server_t*
*/
void udp_server_destroy(udp_server_t* server){
	printf("Shutdown server...");
	close(server->SOCK);		
	free(server);
}

/**
*@fn int main(int argc, char* argv[])
*
*
*
*/

int main(int argc, char* argv[]){
	printf("openning udp server. Hail our lord James Jeong\n");
	udp_server_t* server = udp_server_init();
	udp_server_connect(server);
	udp_server_destroy(server);
	return 0;
	
}
