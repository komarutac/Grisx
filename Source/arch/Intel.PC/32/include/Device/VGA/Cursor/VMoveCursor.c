#include <Device/IO.h>
#include <Device/VGA/Cursor.h>
#include <Device/VGA/ColorTextMode.h>
#include <stdint.h>

void VMoveCursor(const uint8_t Top, const uint8_t Left)
{
    const uint16_t Position = Top * VCResWidth + Left;
    VCWriteRegister(VCRTCommand, 0x0F, Position & 0xFF);
    VCWriteRegister(VCRTCommand, 0x0E, (Position >> 8) & 0xFF);
}