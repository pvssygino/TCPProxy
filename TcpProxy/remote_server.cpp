#include "remote_server.h"

remote_server::remote_server(std::string ip, int port) {
	this->ip = ip;
	this->port = port;
	this->remote_server_address.sin_family = AF_INET;
	this->remote_server_address.sin_addr.s_addr = inet_addr(ip.c_str());
	this->remote_server_address.sin_port = htons(this->port);
}
bool remote_server::get_server_status() {
	bool status = true;
	int sockfd = NULL;
	connect(sockfd, (struct sockaddr*)&this->remote_server_address, sizeof(this->remote_server_address)) < 0 ? status = 0 : status = 1;

	return status;
}
void remote_server::set_server_status(bool state) {
	this->server_status = state;
}
int remote_server::get_server_port() {
	return this->port;
}
int remote_server::connect_to_remotehost() {
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (connect(sockfd, (struct sockaddr*)&this->remote_server_address, sizeof(this->remote_server_address)) < 0) {
		printf("Impossibile connettersi col server!");
	}
	return sockfd;
}
remote_server::~remote_server() {}