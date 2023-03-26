#include "proxy.h"
#include "firewall.h"
#include "log.h"

#pragma comment(lib,"ws2_32.lib")

firewall* FIREWALL = new firewall("firewall.rules");
Logger log_("TCPPROXY_LOG.log");
int record_client = 0;

Proxy::Proxy(std::string ip,int port,std::string remote_host,int remote_port) {
	
	this->remote_host = new remote_server(remote_host, remote_port);

	if (WSAStartup(MAKEWORD(2, 2), &this->wsa) != 0) {
		std::cout << "Errore nella librearia winsock!" << std::endl;
	}
	this->n_client = NULL;
	this->ip = ip;
	this->port = port;
	this->proxy_address.sin_family = AF_INET;
	this->proxy_address.sin_addr.s_addr = inet_addr(this->ip.c_str());
	this->proxy_address.sin_port = htons(this->port);
	
	this->listener = socket(AF_INET, SOCK_STREAM, 0);
	
	bind_();
	
	if (listen(this->listener, 5) < 0) {
		std::cout << "Impossibile ascoltare il socket dell'ascoltatore!" << std::endl;
	}
}
int Proxy::bind_() {
	
	if (bind(this->listener, (struct sockaddr*)&this->proxy_address, sizeof(this->proxy_address)) < 0) {
		std::cout << "Errore bind" << std::endl;
		return -1;
	}
	return this->listener;
}
void Proxy::packet_handle() {

	char buffer[PACKET_BUFFER_MAX_SIZE];
	int bytes_read = 0;
	int buffer_size = 0;

	int sockfd_server = remote_host->connect_to_remotehost();
	while ((bytes_read = recv(this->client_[this->n_client].sock_fd, buffer, PACKET_BUFFER_MAX_SIZE, 0)) > 0) {

		if (send(sockfd_server, buffer, bytes_read, 0) < 0) {
			std::cout << "Impossibile inviare dati al server!" << std::endl;
			break;
		}
		memset(buffer, 0, PACKET_BUFFER_MAX_SIZE);

		bytes_read = recv(sockfd_server, buffer, PACKET_BUFFER_MAX_SIZE, 0);
		if (bytes_read < 0) {
			std::cout << "Impossibile ricevere dati dal server!" << std::endl;
			break;
		}

		if (send(this->client_[this->n_client].sock_fd, buffer, bytes_read, 0) < 0) {
			std::cout << "Impossibile inviare dati al client:"<<this-n_client << std::endl;
			break;
		}
		memset(buffer, 0, PACKET_BUFFER_MAX_SIZE);
	}

	std::cout<<"[OUT] [ "<<this->client_[this->n_client].get_client_ip()<<" ]\n";
	log_.log("CONNESSIONE IN USCITA: " + this->client_[n_client].get_client_ip());
	closesocket(this->client_[this->n_client].sock_fd);
	this->client_[this->n_client].set_state(OFF);
	this->n_client--;		
}
int Proxy::accept_connection() {

	int client_len = sizeof(this->client_[this->n_client].client_struct);
	this->client_[this->n_client].sock_fd = accept(this->listener, (struct sockaddr*)&this->client_[this->n_client].client_struct, &client_len);

	this->client_[n_client].set_ip(inet_ntoa(this->client_[this->n_client].client_struct.sin_addr));

	if (FIREWALL->check_connection(this->client_[n_client].get_client_ip()) == TRUE) {

		if (this->client_[this->n_client].sock_fd < 0) {
			std::cout << "Errore nell'accettazione della connessione dal client" << std::endl;
			return -1;
		}
		else if (this->n_client == MAX_CONNECTION) {
			std::cout << "Il Proxy ha raggiunto il numero massimo di connessioni!" << std::endl;
			log_.log("NUMERO MASSIMO DI CLIENT RAGGIUNTO!");
			return -1;
			if (this->client_[this->n_client].sock_fd >= 0) {
				std::cout << "Connessione in entrata riufiutata!" << std::endl;
				log_.log("CONNESSIONE RIFIUTATA : " + this->client_[n_client].get_client_ip());
				return -1;
			}
		}
		else {
			std::cout << "[IN] : [" << this->n_client << "]" << "[ " << this->client_[n_client].get_client_ip() << " ]" << std::endl;
			this->client_[this->n_client].set_state(ON);
			log_.log("CONNESSIONE STABILITA CON: " + this->client_[n_client].get_client_ip());

			t = std::thread([this]() {
				this->packet_handle();
				});
			t.join();
			this->n_client++;
			
		}
	}
	else {
		std::cout << "[FIREWALL] ip_block: " << this->client_[n_client].get_client_ip() << std::endl;
		log_.log("FIREWALL [ip_block]: " + this->client_[n_client].get_client_ip());
		closesocket(this->client_[n_client].sock_fd);
		return -1;
	}
	record_client++;
	return this->client_[this->n_client].sock_fd;
}
bool Proxy::try_server_connection() {
	bool status = this->remote_host->get_server_status();
	return status;
}
Proxy::~Proxy() {
	free(remote_host);
	delete[] this->client_;
}
