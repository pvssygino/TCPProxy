#include "proxy.h"
#include "config.h"

int main() {
	Config *config= new Config("config.ini");
	ConfigData data = config->getData();

	std::cout << "         _____         _____                 \n";
	std::cout << "        |_   _|___ ___|  _  |___ ___ _ _ _ _ \n";
	std::cout << "          | | |  _| . |   __|  _| . |_'_| | |\n";
	std::cout << "          |_| |___|  _|__|  |_| |___|_,_|_  |\n";
	std::cout << "                  |_|                   |___|\n";

	Proxy* TCPPROXY_SERVER = new Proxy(data.proxy_ip,data.proxy_port,data.remote_ip,data.remote_port);
	
	std::cout << "     PROXY IP: " << data.proxy_ip << "    PROXY PORT:" <<data.proxy_port<< "     [STATE]=ON\n";
	std::cout << "Waiting for connection..\n";


		while (true) {
			std::cout << "                                                       ONLINE:" << TCPPROXY_SERVER->n_client << std::endl;
			TCPPROXY_SERVER->accept_connection();
		}
	return 0;
}
