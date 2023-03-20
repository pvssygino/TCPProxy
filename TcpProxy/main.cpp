#include "proxy.h"
#include "firewall.h"
#include "utility.h"
#pragma warning(disable:4996)
#pragma comment(lib,"ws2_32.lib")

int main(int argc, char* argv[]) {

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    printf("      _____         _____                 \n");
    printf("     |_   _|___ ___|  _  |___ ___ _ _ _ _ \n");
    printf("       | | |  _| . |   __|  _| . |_'_| | |\n");
    printf("       |_| |___|  _|__|  |_| |___|_,_|_  |\n");
    printf("               |_|                   |___|\n");

    if (argc != 4) {
        fprintf(stderr, "Utilizzo: %s <local_port> <remote_host> <remote_port>\n", argv[0]);
        exit(1);
    }
    printf("\n\n------------> Inizializzazione della librearia winsock() \n");
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        error((char*)"Errore nell'inizializzazione della libreria winsock!");
    }

    set_textColor(hConsole, (char*)"OK!", (char*)"ok");

    // Inizializzazione del FIREWALL
    printf("------------> Inizializzazione del firewall() \n");
    init_firewall();
    // 
    int local_port = atoi(argv[1]);
    char* remote_host = argv[2];
    int remote_port = atoi(argv[3]);

    //Inizializzazione del PROXY
    printf("------------> Inizializzazione del Proxy\n");
    int sockfd = create_socket();
    printf("\n                   PROXY [ON] | LOCAL_PORT: %d  REMOTE_SERVER %s:%d...\n", local_port, remote_host, remote_port);
    bind_socket(sockfd, local_port);
    //

    struct sockaddr_in client_address;
    int client_len = sizeof(client_address);
    int server_sockfd = NULL;


    while (1) {

        int client_sockfd = accept(sockfd, (struct sockaddr*)&client_address, &client_len);

        //FIREWALL CONTROLLA LE CONNESSIONI IN ENTRATA
        if (!is_allowed(client_sockfd, remote_host, remote_port)) {
            printf("[FIREWALL]: Accesso negato al client: %s \n", client_address.sin_addr);
            closesocket(client_sockfd);
        }
        //

        if (client_sockfd < 0) {
            error((char*)"Error accepting connection from client");
        }
        server_sockfd = connect_to_server(remote_host, remote_port);
        handle_client(client_sockfd, server_sockfd);

        closesocket(client_sockfd);
    }

    closesocket(sockfd);
    closesocket(server_sockfd);
    WSACleanup();

    return 0;
}
