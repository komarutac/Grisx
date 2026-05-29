#include <Device/IO.h>
#include <Device/VGA/Cursor.h>
#include <Device/VGA/ColorTextMode.h>

void VDisableCursor()
{
    VCWriteRegister(VCRTCommand, 0x0A, 0x20);
}