#pragma once
#include <iostream>
#include <string>
#include <winsock.h>
#include <thread>
#include <functional>
#include "Client.h"
#include "firewall.h"
#include "remote_server.h"

#define PACKET_BUFFER_MAX_SIZE 4096
#define MAX_CONNECTION 50

class Proxy {
public:
	Proxy(std::string ip, int port,std::string remote_host, int remote_port);
	~Proxy();
	
	int bind_();
	void packet_handle();
	int accept_connection();
	bool try_server_connection();
	time_t get_proxy_time();
	std::thread t;
	int n_client;

private:
	
	WSADATA wsa;
	time_t proxy_time;

	int listener;
	int client_sockfd;
	int server_sockfd;
	int port;
	std::string ip;

	Client client_[MAX_CONNECTION];
	remote_server *remote_host;
	struct sockaddr_in proxy_address;
		
};
