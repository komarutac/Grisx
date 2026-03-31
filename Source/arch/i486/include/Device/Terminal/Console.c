#include "Console.h"
#include <stdarg.h>
#include <Shared/String.h>
ConsoleStruct* DefaultConsole = &(ConsoleStruct){};
ConsoleStruct* DebugConsole = &(ConsoleStruct){};
ConsoleStruct* NullConsole = 0;

void ConWriteTo(ConsoleStruct* Console, char* Source, int Length) {
    for (int i = 0; i < Length; i++) {
        Console->WriteChar(Source[i]);
    }
}

int ConFormatTo(ConsoleStruct* Console, char* restrict Format, ...) {
    va_list Parameters;
    va_start(Parameters, Format);

    int Written = 0;
	if (Console == 0) {
		return 0;
	}

    while (*Format != '\0') {
        int MaxRem = INT_MAX - Written;

        if (Format[0] != '%' || Format[1] == '%') {
            if (Format[0] == '%')
                Format++;

            int Amount = 1;

            while (Format[Amount] && Format[Amount] != '%')
                Amount++;

            if (MaxRem < Amount) {
                return -1;
            }

            ConWriteTo(Console, Format, Amount);

            Format += Amount;
            Written += Amount;
        }


        char* FormatBegin = Format++;

        if (*Format == 'c') {
            Format++;
            char C = (char)va_arg(Parameters, int);

            if (!MaxRem) {
                
                return -1;
            }

            Console->WriteChar(C);
            Written++;
        } else if (*Format == 'd') {
            Format++;
            int Number = va_arg(Parameters, int);

            if (!MaxRem) {
                
                return -1;
            }

            char NumberString[SBaseGetSafeSize(Number, 10)];

            SBaseToString(Number, NumberString, SBase10, 10);
            Console->WriteString(NumberString);
            Written += strlen(NumberString);
        } else if (*Format == 'h') {
            Format++;
            const int Number = va_arg(Parameters, int);

            if (!MaxRem) {
                
                return -1;
            }

            char NumberString[SBaseGetSafeSize(Number, 16)];

            SBaseToString(Number, NumberString, SBase16, 16);
            Console->WriteString(NumberString);
            Written += strlen(NumberString);
        } else if (*Format == 'b') {
            Format++;
            const int Number = va_arg(Parameters, int);

            if (!MaxRem) {
                
                return -1;
            }

            char NumberString[SBaseGetSafeSize(Number, 2)];

            SBaseToString(Number, NumberString, SBase2, 2);
            Console->WriteString(NumberString);
            Written += strlen(NumberString);
        } else if (*Format == 'v') {
            Format++;
            const int Number = va_arg(Parameters, int);

            if (!MaxRem) {
                
                return -1;
            }

            char NumberString[SBaseGetSafeSize(Number, 20)];

            SBaseToString(Number, NumberString, SBase20, 20);
            Console->WriteString(NumberString);
            Written += strlen(NumberString);
        } else if (*Format == 's') {
            Format++;
            char* Text = va_arg(Parameters, char*);

            if (!MaxRem) {
                
                return -1;
            }

            Console->WriteString(Text);
            Written += strlen(Text);
        } else {
            Format = (char*)FormatBegin;
            int Length = strlen(Format);
            if (MaxRem < Length) {
                
                return -1;
            }

            Console->WriteString(Format);
            Written += Length;
            Format += Length;
        }
    }

    va_end(Parameters);
    return Written;
}