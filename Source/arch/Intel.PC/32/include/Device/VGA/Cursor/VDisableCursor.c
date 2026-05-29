#include <Device/IO.h>
#include <Device/VGA/Cursor.h>
#include <vgatext.h>

void VDisableCursor()
{
    VCWriteRegister(VCRTCommand, 0x0A, 0x20);
}