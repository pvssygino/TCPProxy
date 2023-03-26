#include "firewall.h"
#pragma warning(disable:4996)

firewall::firewall(std::string firewall_rules_file) {

	this->n_ip = 0;
	char line[100];
	FILE *firewall_file = fopen(firewall_rules_file.c_str(), "r");
	if (firewall_file==NULL) std::cout << "Impossibile trovare il file :" << firewall_rules_file;
	else {
		while (fgets(line, sizeof(line), firewall_file) != NULL) {				
			this->ip_ban[this->n_ip] = line;
			this->n_ip++;
		}		
	}
}
bool firewall::check_connection(std::string ip) {

	bool trusted = true;
	if (this->n_ip >= 0) {
		for (int i = 0; i < this->n_ip; i++) {
			if (ip == this->ip_ban[i]) {
				trusted = false;
			}
		}
	}
	else trusted = true;
	return trusted;
}
void firewall::shutdown_firewall() {
	if (this->n_ip >= 0) {
		for (int i = 0; i < MAX_IP; i++) {
			this->ip_ban[i] = "";
		}
	}
}
firewall::~firewall() { delete[] this->ip_ban; }
