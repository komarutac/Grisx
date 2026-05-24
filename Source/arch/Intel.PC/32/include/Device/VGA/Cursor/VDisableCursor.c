#include <Device/IO.h>
#include <Device/VGA/Cursor.h>
#include <Device/VGA/ColorTextMode.h>

void VDisableCursor()
{
    outb(VCRTCommand, 0x0A);
    outb(VCRTValue, 0x20);
}