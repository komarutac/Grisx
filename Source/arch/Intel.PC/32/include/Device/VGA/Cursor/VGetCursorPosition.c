#include <Device/IO.h>
#include <Device/VGA/Cursor.h>
#include <Device/VGA/ColorTextMode.h>
#include <stdint.h>

uint16_t VGetCursorPosition()
{
    uint8_t Temp;
    uint16_t Position = 0;
    outb(VCRTCommand, 0x0F);
    Temp = inb(VCRTValue);
    Position |= Temp;
    outb(VCRTCommand, 0x0E);
    Temp = inb(VCRTValue);
    Position |= Temp << 8;
    return Position;
}