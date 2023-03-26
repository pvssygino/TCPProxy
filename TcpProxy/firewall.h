#pragma once
#include <iostream>
#include <string>

#define MAX_IP 20

class firewall {
public:
	firewall(std::string firewall_rules_file);
	~firewall();
	bool check_connection(std::string ip);
	void shutdown_firewall();

private:
	int n_ip;
	std::string ip_ban[MAX_IP];
};
