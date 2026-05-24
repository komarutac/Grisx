#include <Device/IO.h>
#include <Device/VGA/Cursor.h>
#include <Device/VGA/ColorTextMode.h>
#include <stdint.h>

void VEnableCursor(const uint8_t Start, const uint8_t End)
{
    uint8_t Temp;
    outb(VCRTCommand, 0x0A);
    Temp = inb(0x3D5);
    outb(VCRTValue, (Temp & 0xC0) | Start);
    outb(VCRTCommand, 0x0B);
    Temp = inb(0x3D5);
    outb(VCRTValue, (Temp & 0xE0) | End);
}