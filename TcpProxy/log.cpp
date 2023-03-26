#include "log.h"
#include <iostream>
#include <chrono>
#include <ctime>
#pragma warning(disable:4996)

Logger::Logger(const std::string& filename) {
    
    m_outfile.open(filename, std::ios::app);
    if (!m_outfile.is_open()) {
        std::cerr << "Failed to open log file" << std::endl;
    }
}

Logger::~Logger() {
    if (m_outfile.is_open()) {
        m_outfile.close();
    }
}

void Logger::log(const std::string& message) {
    if (m_outfile.is_open()) {
        auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        m_outfile <<"["<< std::ctime(&now) <<"]:" << message << std::endl;
    }
}
