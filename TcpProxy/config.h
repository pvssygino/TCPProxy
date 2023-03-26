#pragma once
#include <string>

struct ConfigData {
    std::string proxy_ip;
    int proxy_port;
    int max_connection;
    bool firewall;
    std::string remote_ip;
    int remote_port;
};

class Config {
public:
    Config(std::string filename);

    ConfigData getData();

private:
    std::string filename;
    ConfigData data;
};
