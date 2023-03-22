#include <stdio.h>
#include <Windows.h>
#include <string.h>
#include <time.h>

#define RED 12
#define GREEN 10
#define YELLOW 14
#define WHITE 15

#ifndef utility_h
#define utility_h

void set_textColor(HANDLE hConsole,char* text,char *msg);
char* get_time();



#endif
