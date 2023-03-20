
#ifndef FIREWALL_H
#define FIREWALL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <iphlpapi.h>
#include "utility.h"
#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"iphlpapi.lib")
#pragma warning(disable:4996)


#define RULES_FILE "firewall.rules"

// Struttura dati per le regole del firewall
typedef struct {
    char local_subnet[20];
    char remote_subnet[20];
    int remote_port;
} firewall_rule;

// Array di regole del firewall

int init_firewall();
void shutdown_firewall();
int is_allowed(SOCKET client_socket, const char* remote_host, int remote_port);
DWORD get_subnet_mask(DWORD interface_index);

#endif /* FIREWALL_H */
