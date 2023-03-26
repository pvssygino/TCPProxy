#include "config.h"
#include <Windows.h>
#include <sstream>
#include <fstream>
#include <iostream>
Config::Config(std::string filename) {

    this->filename = filename;
    std::ifstream file_(this->filename);

    std::string line;
    while (std::getline(file_,line)) {

        std::stringstream lineStream(line);
        std::string key, value;
        std::getline(lineStream, key, '=');
        std::getline(lineStream, value);
        
        if (key == "IP") 
            data.proxy_ip = value;
        else if (key == "PORT") 
            data.proxy_port = stoi(value);       
        else if (key == "REMOTE_HOST") 
            data.remote_ip = value;
        else if (key == "REMOTE_PORT") 
            data.remote_port = stoi(value);
    }   
}

ConfigData Config::getData() {
    return data;
}
