#pragma once
#include <string>
#include <winsock.h>

class remote_server {
public:
	remote_server(std::string ip, int port);
	~remote_server();

	int get_server_port();
	bool get_server_status();
	void set_server_status(bool state);
	int connect_to_remotehost();
private:
	struct sockaddr_in remote_server_address;
	std::string ip;
	int port;
	bool server_status;	
};
