#include <Device/CPU/PIC.h>
#include <stdint.h>
#include <Device/IO.h>

void ClearIRQMask(uint8_t IRQLine) {
	uint16_t Port;
	uint8_t Value;
	uint8_t Temp;

	if (IRQLine < 8) {
		Port = PICMaster;
	} else {
		Port = PICSlave;
		IRQLine -= 8;
	}

	Temp = inb(Port);
	Value = Temp & ~(1 << IRQLine);
	outb(Port, Value);
}