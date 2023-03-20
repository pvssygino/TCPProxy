
#include "proxy.h"
#pragma warning(disable:4996)
void error(char* msg) {
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(1);
}

int create_socket() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        error((char*)"Error creating socket");
    }
    return sockfd;
}

int bind_socket(int sockfd, int port) {
    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(port);

    if (bind(sockfd, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        error((char*)"Error binding socket");
    }

    if (listen(sockfd, 5) < 0) {
        error((char*)"Error listening on socket");
    }

    return sockfd;
}

int connect_to_server(char* hostname, int port) {

    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);

    struct hostent* server = gethostbyname(hostname);
    if (server == NULL) {
        error((char*)"Error resolving hostname");
    }

    memcpy(&server_address.sin_addr.s_addr, server->h_addr, server->h_length);

    int sockfd = create_socket();
    if (connect(sockfd, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        error((char*)"Error connecting to server");
    }

    return sockfd;
}

void handle_client(int client_sockfd, int server_sockfd) {
    char buffer[BUFFER_SIZE];
    int bytes_read;

    while ((bytes_read = recv(client_sockfd, buffer, BUFFER_SIZE, 0)) > 0) {
        if (send(server_sockfd, buffer, bytes_read, 0) < 0) {
            error((char*)"Error sending data to server");
        }
        memset(buffer, 0, BUFFER_SIZE);

        bytes_read = recv(server_sockfd, buffer, BUFFER_SIZE, 0);
        if (bytes_read < 0) {
            error((char*)"Error receiving data from server");
        }

        if (send(client_sockfd, buffer, bytes_read, 0) < 0) {
            error((char*)"Error sending data to client");
        }
        memset(buffer, 0, BUFFER_SIZE);
    }
}
