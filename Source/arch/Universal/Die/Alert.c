#include <Abstraction/Console.h>
#include <Die.h>

void Alert(char* Reason, char* What)
{
	(void)What;
	printf("Alert, %s!\r\n", Reason);
}