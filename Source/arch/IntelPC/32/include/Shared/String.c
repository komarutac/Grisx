#include "String.h"
#include <stdint.h>
#include <Device/Terminal/Console.h>

char SBase20[] = {
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'J', 'K'
};

char SBase16[] = {
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
};

char SBase10[] = {
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
};

char SBase2[] = {
	'0', '1'
};

int strlen(char* String)
{
	int ReturnLength = 0;
	while (*String != '\0')
	{
		ReturnLength++;
		String++;
	}
	return ReturnLength;
}

unsigned long SBaseGetSafeSize(unsigned long Integer, int Division) {
	unsigned long SafeSize = 0;
	while (Integer > 0) {
		SafeSize++;
		Integer /= Division;
	}
	return SafeSize;
}

void strrev(int i, char* Destination) {
	for (int j = 0, k = i - 1; j < k; j++, k--) {
		char Temp = Destination[j];
		Destination[j] = Destination[k];
		Destination[k] = Temp;
	}
	Destination[i] = '\0';
}

void SBaseToString(unsigned long Integer, char* Destination, char* Array, int Division) {
	unsigned long i = 0;
	if (Integer == 0) {
		Destination[i++] = Array[Integer];
	}
	
	while (Integer > 0) {
		Destination[i++] = Array[Integer % Division];
		Integer /= Division;
	}

	strrev(i, Destination);
}

int strsum(char* Source) {
	int Sum = 0;
	while (*Source != '\0')
		Sum += *Source++;
	return Sum;
}

void strcat(char* Source0, char* Source1, char* Destination) {
	while (*Source0 != '\0') 
		*Destination++ = *Source0++;
	while (*Source1 != '\0') 
		*Destination++ = *Source1++;
	*Destination = '\0';
}

int strcmp(char* Source0, char* Source1) {
	while (*Source0 != '\0') 
		if (*Source0++ != *Source1++) 
			return -1;
	return 0;
}

void CharArrayToString(char* Array, char* Output, int Size) {
	for (int i = 0; i < Size + 1; i++) {
		Output[i] = '\0';
	}
	for (int i = 0; i < Size; i++) {
		Output[i] = Array[i];
	}
}