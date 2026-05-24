#include <StringConvert.h>

void IntegerToASCII(unsigned long Integer, char* Destination, char* Array, int Division) {
	unsigned long i = 0;

	if (Integer == 0)
	{
		Destination[i++] = Array[Integer]; 
	}

	while (Integer > 0)
	{
		Destination[i++] = Array[Integer % Division];
		Integer /= Division;
	}

	strrev(i, Destination);
}