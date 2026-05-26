#include <string.h>
#include <stddef.h>

char* strncpy(char* A, char* B, size_t Length)
{
	if (A == NULL || B == NULL)
	{
		return NULL;
	}

	int i;

	for (i = 0; i < strlen(B); i++)
	{
		if (i < Length)
		{
			A[i] = B[i];
		}
	}

	A[i + 1] = '\0';

	return A;
}