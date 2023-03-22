#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LOG_MESSAGE_MAX_SIZE 50

typedef enum {
    INFO,
    ERR
} LogType;

typedef struct {
    time_t timestamp;
    LogType type;
    char message[LOG_MESSAGE_MAX_SIZE];
} LogMessage;

void logToFile(LogType type, char* message);

#endif
