#include "utility.h"

void set_textColor(HANDLE hConsole, char* text, char* msg) {

    int text_color = 0;

    if (strcmp(msg, "err") == 0)
        text_color = RED;
    else if (strcmp(msg, "ok") == 0)
        text_color = GREEN;
    else if (strcmp(msg, "warn") == 0)
        text_color = YELLOW;

    SetConsoleTextAttribute(hConsole, text_color);
    printf("%s", text);
    SetConsoleTextAttribute(hConsole, WHITE);
    printf("\n");

}

