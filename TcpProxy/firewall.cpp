#include "firewall.h"

// Ottiene l'indirizzo IP della rete locale
firewall_rule* rules;
int num_rules = 0;

DWORD get_local_ip() {
    DWORD local_ip = 0;
    ULONG buflen = 0;
    PIP_ADAPTER_INFO pAdapterInfo = NULL;
    PIP_ADAPTER_INFO pAdapter = NULL;

    GetAdaptersInfo(NULL, &buflen);
    pAdapterInfo = (PIP_ADAPTER_INFO)malloc(buflen);
    if (pAdapterInfo == NULL) {
        return local_ip;
    }

    if (GetAdaptersInfo(pAdapterInfo, &buflen) == NO_ERROR) {
        pAdapter = pAdapterInfo;
        while (pAdapter) {
            if (pAdapter->Type == MIB_IF_TYPE_ETHERNET) {
                local_ip = inet_addr(pAdapter->IpAddressList.IpAddress.String);
                break;
            }
            pAdapter = pAdapter->Next;
        }
    }

    free(pAdapterInfo);
    return local_ip;
}


DWORD get_subnet_mask(DWORD interface_index) {
    DWORD subnet_mask = 0;

    MIB_IPADDRTABLE* ip_table = NULL;
    DWORD table_size = 0;
    DWORD result = GetIpAddrTable(ip_table, &table_size, FALSE);

    if (result == ERROR_INSUFFICIENT_BUFFER) {
        ip_table = (MIB_IPADDRTABLE*)malloc(table_size);
        result = GetIpAddrTable(ip_table, &table_size, FALSE);
    }

    if (result == NO_ERROR) {
        for (DWORD i = 0; i < ip_table->dwNumEntries; i++) {
            if (ip_table->table[i].dwIndex == interface_index) {
                subnet_mask = ip_table->table[i].dwMask;
                break;
            }
        }
    }

    if (ip_table != NULL) {
        free(ip_table);
    }

    return subnet_mask;
}

// Verifica se l'indirizzo IP è nella stessa subnet dell'indirizzo IP locale
int is_same_subnet(DWORD ip_addr) {
    DWORD local_ip = get_local_ip();
    DWORD subnet_mask = 0;
    get_subnet_mask(subnet_mask);

    DWORD local_subnet = local_ip & subnet_mask;
    DWORD ip_subnet = ip_addr & subnet_mask;

    return (local_subnet == ip_subnet);
}

// Legge le regole del firewall dal file di configurazione
int read_firewall_rules() {
    FILE* fp;
    char line[100];
    int line_num = 0;

    fp = fopen(RULES_FILE, "r");
    if (fp == NULL) {
        printf("[ERRORE]: impossibile trovare il file: %s\n", RULES_FILE);
        return -1;
    }

    while (fgets(line, sizeof(line), fp) != NULL) {
        line_num++;
        char* token = strtok(line, ",");
        char local_subnet[20];
        char remote_subnet[20];
        int remote_port;

        if (token == NULL) {
            printf("Errore nella riga %d del file delle regole del firewall: indirizzo IP locale mancante\n", line_num);
            fclose(fp);
            return -1;
        }
        strncpy(local_subnet, token, sizeof(local_subnet));

        token = strtok(NULL, ",");
        if (token == NULL) {
            printf("Errore nella riga %d del file delle regole del firewall: indirizzo IP remoto mancante\n", line_num);
            fclose(fp);
            return -1;
        }
        strncpy(remote_subnet, token, sizeof(remote_subnet));

        token = strtok(NULL, ",");
        if (token == NULL) {
            printf("Errore nella riga %d del file delle regole del firewall: porta remota mancante\n", line_num);
            fclose(fp);
            return -1;
        }
        remote_port = atoi(token);

        if (num_rules == 0) {
            rules = (firewall_rule*)malloc(sizeof(firewall_rule));
        }
        else {
            rules = (firewall_rule*)realloc(rules, sizeof(firewall_rule) * (num_rules + 1));
        }

        strncpy(rules[num_rules].local_subnet, local_subnet, sizeof(rules[num_rules].local_subnet));
        strncpy(rules[num_rules].remote_subnet, remote_subnet, sizeof(rules[num_rules].remote_subnet));
        rules[num_rules].remote_port = remote_port;
        num_rules++;
    }

    fclose(fp);
    return 0;
}

// Inizializza il firewall
int init_firewall() {
    if (read_firewall_rules() != 0) {
        return -1;
    }
    return 0;
}

// Termina il firewall
void shutdown_firewall() {
    if (rules != NULL) {
        free(rules);
    }
}

// Verifica se il socket del client è consentito a connettersi all'host remoto sulla porta remota
int is_allowed(SOCKET client_socket, const char* remote_host, int remote_port) {
    struct sockaddr_in client_addr;
    int addr_len = sizeof(client_addr);

    getpeername(client_socket, (struct sockaddr*)&client_addr, &addr_len);
    if (!is_same_subnet(client_addr.sin_addr.S_un.S_addr)) {
        return 0;
    }

    struct hostent* host = gethostbyname(remote_host);
    if (host == NULL) {
        return 0;
    }

    for (int i = 0; i < num_rules; i++) {
        if (strcmp(inet_ntoa(*(struct in_addr*)host->h_addr_list[0]), rules[i].remote_subnet) == 0
            && remote_port == rules[i].remote_port) {
            return 1;
        }
    }

    return 0;
}


