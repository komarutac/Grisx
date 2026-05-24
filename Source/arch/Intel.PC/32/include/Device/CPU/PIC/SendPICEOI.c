#include <Device/CPU/PIC.h>
#include <stdint.h>
#include <Device/IO.h>

void SendPICEOI(uint8_t IRQ) {
	if (IRQ >= 8) {
		outb(PICSlave, PICEOI);
	}

	outb(PICMaster, PICEOI);
}