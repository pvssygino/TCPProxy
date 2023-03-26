#pragma once
#include <iostream>
#include <string>
#include <winsock.h>

#define ON 1
#define OFF 0
class Client {
public:
	Client();
	~Client();
	std::string get_client_ip();
	void set_ip(std::string ip);
	void set_state(bool state);
	bool get_state();

	int sock_fd;
	struct sockaddr_in client_struct;
private:
	bool client_status;
	std::string ip;
	
};
