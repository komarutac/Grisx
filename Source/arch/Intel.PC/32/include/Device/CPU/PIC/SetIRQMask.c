#include <Device/CPU/PIC.h>
#include <stdint.h>
#include <Device/IO.h>

void SetIRQMask(uint8_t IRQLine) {
	uint16_t Port;
	uint8_t Temp;

	if (IRQLine < 8) {
		Port = PICMaster;
	} else {
		Port = PICSlave;
		IRQLine -= 8;
	}

	Temp = inb(Port);
	outb(Port, Temp | (1 << IRQLine));
}