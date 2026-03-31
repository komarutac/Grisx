#pragma once
#include <limits.h>
#include <stdarg.h>
#include <Shared/String.h>
#include <Shared/Error.h>
#include <Color.h>
#define DebugPrint(Message) ConFormatTo(DebugConsole, "\r\n%s,%d,%s: %s\r\n", __FILE__, __LINE__, __FUNCTION__, Message)

struct _TableColumn {
    int ID;
    char* Name;
}; typedef struct _TableColumn TableColumn;

struct _TableRow {
    int ID;
    int ColumnID;
    char* Value;
}; typedef struct _TableRow TableRow;

struct _TableStruct {
    TableColumn Columns[32];
    TableRow Rows[96];
}; typedef struct _TableStruct TableStruct;

struct _ConsoleStruct
{
    int Width;
    int Height;
    int X;
    int Y;
    int Busy;
    void (*WriteChar)(uint8_t Char);
    void (*WriteCharAt)(uint8_t Char, int X, int Y);
    void (*WriteString)(char* Text);
    void (*WriteLine)(char* Text);
    void (*EraseLine)();
    void (*NewLine)();
    void (*Clear)();
    void (*SetForegroundColor)(ARGB Color);
    void (*SetBackgroundColor)(ARGB Color);
    uint16_t* TextBuffer;
}; typedef struct _ConsoleStruct ConsoleStruct;

extern ConsoleStruct* DefaultConsole;
extern ConsoleStruct* DebugConsole;
extern ConsoleStruct* NullConsole;
extern void ConWriteTo(ConsoleStruct* Console, char* Source, int Length);
extern int ConFormatTo(ConsoleStruct* Console, char* restrict Format, ...);
extern int (*printf)(char* restrict, ...);