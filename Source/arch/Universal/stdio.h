#pragma once
#include <stdint.h>
#define putchar(Char) ConFormatTo(DefaultConsole, "%c", Char)
#define puts(String) ConFormatTo(DefaultConsole, "%s", String)
#ifndef NULL
#define NULL 0
#endif
extern int ConFormatTo(DefaultConsole, char* restrict, ...);