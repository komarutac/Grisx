#include "StringConvert.h"
#include <stdint.h>
#include <string.h>

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