#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <winsock2.h>

#ifndef PROXY_H
#define PROXY_H

#define BUFFER_SIZE 4096

void error(char* msg);
int create_socket();
int bind_socket(int sockfd, int port);
int connect_to_server(char* hostname, int port);
void handle_client(int client_sockfd, int server_sockfd);

#endif
