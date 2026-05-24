#include <StringConvert.h>

void strrev(int i, char* Destination) {
	for (int j = 0, k = i - 1; j < k; j++, k--) {
		char Temp = Destination[j];
		Destination[j] = Destination[k];
		Destination[k] = Temp;
	}
	Destination[i] = '\0';
}