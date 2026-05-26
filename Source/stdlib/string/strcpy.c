#include <string.h>
#include <stddef.h>

char* strcpy(char* A, char* B)
{
	if (A == NULL || B == NULL)
	{
		return NULL;
	}

	int i;

	for (i = 0; i < strlen(B); i++)
	{
		A[i] = B[i];
	}

	A[i + 1] = '\0';

	return A;
}