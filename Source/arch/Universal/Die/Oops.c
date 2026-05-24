#include <Abstraction/Console.h>
#include <Die.h>

void Oops(char* Reason, char* What)
{
	(void)What;
	printf(" Oops, %s.\r\n", Reason);
}