#pragma once
#include <stdint.h>
extern char SBase20[];
extern char SBase16[];
extern char SBase10[];
extern char SBase2[];

int strlen(char* String);
unsigned long SBaseGetSafeSize(unsigned long Integer, int Division);
void strrev(int i, char* Destination);
void SBaseToString(unsigned long Integer, char* Destination, char* Array, int Division);
void CharArrayToString(char* Array, char* Output, int Size);
int strsum(char* Source);
void strcat(char* Source0, char* Source1, char* Destination);
int strcmp(char* Source0, char* Source1);