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
    time_ = get_time();
    printf("\n\n[%s]Creazione del file log() ...    ",time_);
    
    set_textColor(hConsole, (char*)"OK!", (char*)"ok");
    time_ = get_time();
    printf("[%s]Inizializzazione della librearia winsock() ...    ",time_);
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        error((char*)"Errore nell'inizializzazione della libreria winsock!");
    }

    set_textColor(hConsole, (char*)"OK!",(char*)"ok");
    
    time_ = get_time();
    // Inizializzazione del FIREWALL
    printf("[%s]Inizializzazione del firewall() ... \n",time_);
    printf("\nIP_BAN (LIST): \n");
    init_firewall();
    // 
    int local_port = atoi(argv[1]);
    char* remote_host = argv[2];
    int remote_port = atoi(argv[3]);

    int sockfd = create_socket();
    time_ = get_time();
    printf("[%s]Inizializzazione del Proxy ...   ",time_);
    set_textColor(hConsole, (char*)"OK!", (char*)"ok");

    printf("\n                   PROXY [ON] | LOCAL_PORT: %d  REMOTE_SERVER %s:%d  ...\n", local_port, remote_host, remote_port);

    bind_socket(sockfd, local_port); 

    struct sockaddr_in client_address;
    int client_len = sizeof(client_address);
    int server_sockfd = NULL;
    char* ip_client;

    while (1) {
        time_ = get_time();
        int client_sockfd = accept(sockfd, (struct sockaddr*)&client_address, &client_len);
        ip_client = get_client_ip(client_sockfd);
        
        if (client_sockfd < 0) {
            error((char*)"Error accepting connection from client");
        }

        //FIREWALL CONTROLLA LE CONNESSIONI IN ENTRATA
        if (!is_allowed(client_sockfd, remote_host, remote_port)) {
            
            SetConsoleTextAttribute(hConsole, YELLOW);
            printf("[%s][FIREWALL]: Accesso negato al client: %s \n",time_, ip_client);
            SetConsoleTextAttribute(hConsole, WHITE);

            logToFile(ERR, (char*)"Acceso Negato");
            closesocket(client_sockfd);
        }
        //
        else {
            
            printf("\n[%s][IN]: Connessione stabilita con %s\n", time_,ip_client);
            server_sockfd = connect_to_server(remote_host, remote_port);
            handle_client(client_sockfd, server_sockfd);
        }

       // closesocket(client_sockfd);
    }

    closesocket(sockfd);
    closesocket(server_sockfd);
    WSACleanup();

    return 0;
}
