#include "client.h"

Client::Client() { this->client_status = OFF; this->ip = ""; }
Client::~Client() {}

void Client::set_state(bool state) {
	this->client_status = state;
}
bool Client::get_state() {
	return this->client_status;
}
std::string Client::get_client_ip() {
	return this->ip;
}
void Client::set_ip(std::string ip) {
	this->ip = ip;
}
