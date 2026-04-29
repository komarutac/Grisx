#include <Die.h>
#include <Device/Terminal/Console.h>

void Oops(char* Reason, char* What)
{
	(void)What;
	printf(" Oops, %s.\r\n", Reason);
}

void Alert(char* Reason, char* What)
{
	(void)What;
	printf("Alert, %s!\r\n", Reason);
}