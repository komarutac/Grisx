#include <Console.h>
#include <stdarg.h>
#include <string.h>
#include <StringConvert.h>
ConsoleStruct* DefaultConsole = &(ConsoleStruct){};
ConsoleStruct* DebugConsole = &(ConsoleStruct){};
ConsoleStruct* NullConsole = 0;

void ConWriteTo(ConsoleStruct* Console, char* Source, int Length)
{
	for (int i = 0; i < Length; i++)
	{
		Console->WriteChar(Source[i]);
	}
}

int ConFormatTo(ConsoleStruct* Console, char* restrict Format, ...)
{
    va_list Parameters;
    va_start(Parameters, Format);

    int Written = 0;
	if (Console == 0)
    {
		return 0;
	}

    while (*Format != '\0')
    {
        if (*Format != '%')
        {
            int Amount = 1;

            while (Format[Amount] != 0 && Format[Amount] != '%')
            {
                Amount++;
            }

            ConWriteTo(Console, Format, Amount);

            Format += Amount;
            Written += Amount;
        }


        char* FormatBegin = Format++;

        if (*Format == 'c')
        {
            Format++;
            char C = (char)va_arg(Parameters, int);

            Console->WriteChar(C);
            Written++;
        }
        else if (*Format == 'd')
        {
            Format++;
            int Number = va_arg(Parameters, int);

            char NumberString[SBaseGetSafeSize(Number, 10)];

            SBaseToString(Number, NumberString, SBase10, 10);
            Console->WriteString(NumberString);
            Written += strlen(NumberString);
        }
        else if (*Format == 'X')
        {
            Format++;
            const int Number = va_arg(Parameters, int);

            char NumberString[SBaseGetSafeSize(Number, 16)];
            SBaseToString(Number, NumberString, SBase16, 16);

            Console->WriteString(NumberString);
            Written += strlen(NumberString);
        }
        else if (*Format == 's')
        {
            Format++;
            char* Text = va_arg(Parameters, char*);

            Console->WriteString(Text);
            Written += strlen(Text);
        }
        else
        {
            Format = FormatBegin;
            int Length = strlen(Format);

            Console->WriteString(Format);
            Written += Length;
            Format += Length;
        }
    }

    va_end(Parameters);
    return Written;
}