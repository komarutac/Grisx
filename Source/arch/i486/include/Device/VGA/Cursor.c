#include <Device/IO.h>
#include "ColorTextMode.h"
#include "Cursor.h"

void VDisableCursor()
{
    outb(VCRTCommand, 0x0A);
    outb(VCRTValue, 0x20);
}

uint16_t VGetCursorPosition()
{
    uint16_t Position = 0;
    outb(VCRTCommand, 0x0F);
    Position |= inb(VCRTValue);
    outb(VCRTCommand, 0x0E);
    Position |= inb(VCRTValue) << 8;
    return Position;
}

void VEnableCursor(const uint8_t Start, const uint8_t End)
{
    outb(VCRTCommand, 0x0A);
    outb(VCRTValue, (inb(0x3D5) & 0xC0) | Start);
    outb(VCRTCommand, 0x0B);
    outb(VCRTValue, (inb(0x3D5) & 0xE0) | End);
}

void VMoveCursor(const uint8_t Top, const uint8_t Left)
{
    const uint16_t Position = Top * VCResWidth + Left;
    outb(VCRTCommand, 0x0F);
    outb(VCRTValue, Position & 0xFF);
    outb(VCRTCommand, 0x0E);
    outb(VCRTValue, (Position >> 8) & 0xFF);
}