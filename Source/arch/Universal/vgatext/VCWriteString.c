#include <vgatext.h>

void VCWriteString(char* Text)
{
	while (*Text != '\0')
	{
		VCWriteChar(*Text);
		Text++;
	}
}