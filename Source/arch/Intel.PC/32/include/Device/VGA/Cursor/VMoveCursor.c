#include <Device/IO.h>
#include <Device/VGA/Cursor.h>
#include <Device/VGA/ColorTextMode.h>
#include <stdint.h>

void VMoveCursor(const uint8_t Top, const uint8_t Left)
{
    const uint16_t Position = Top * VCResWidth + Left;
    outb(VCRTCommand, 0x0F);
    outb(VCRTValue, Position & 0xFF);
    outb(VCRTCommand, 0x0E);
    outb(VCRTValue, (Position >> 8) & 0xFF);
}