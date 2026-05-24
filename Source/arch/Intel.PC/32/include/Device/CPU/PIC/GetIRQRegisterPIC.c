#include <Device/CPU/PIC.h>
#include <stdint.h>
#include <Device/IO.h>

uint16_t GetIRQRegisterPIC(int OCW3) {
	uint8_t Temp;
	uint8_t Temp2;
	outb(PICMaster, OCW3);
	outb(PICSlave, OCW3);
	Temp = inb(PICSlave + 1);
	Temp2 = inb(PICMaster + 1);
	return (Temp << 8) |  Temp2;
}