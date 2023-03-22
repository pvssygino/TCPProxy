#include "log.h"
#pragma warning(disable:4996)
void logToFile(LogType type, char* message) {
    time_t t = time(NULL);

    LogMessage logMessage;
    logMessage.timestamp = t;
    logMessage.type = type;
    snprintf(logMessage.message, sizeof(logMessage.message), "%s", message);

    struct tm tm = *localtime(&t);

    char filename[100];
    
        snprintf(filename, sizeof(filename), "%d-%02d-%02d.log", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
    

    FILE* file = fopen(filename, "a");
    if (file == NULL) {
        printf("Errore durante l'apertura del file di log.");
        return;
    }

    fprintf(file, "[%d-%02d-%02d %02d:%02d:%02d] [%s] %s\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, (type == INFO) ? "INFO" : "ERROR", logMessage.message);
    fclose(file);
}
