#include <Device/IO.h>
#include <Device/VGA/Cursor.h>
#include <Device/VGA/ColorTextMode.h>
#include <stdint.h>

void VEnableCursor(const uint8_t Start, const uint8_t End)
{
    uint8_t Temp;
    Temp = VCReadRegister(VCRTCommand, 0x0A);
    outb(VCRTValue, (Temp & 0xC0) | Start);
    Temp = VCReadRegister(VCRTCommand, 0x0B);
    outb(VCRTValue, (Temp & 0xE0) | End);
}