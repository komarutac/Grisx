#include <Device/CPU/PIC.h>
#include <Device/IO.h>

void RemapPIC(int Offset, int Offset1) {
	outb(PICMaster, ICW1Init | ICW14);
	IOWait();

	outb(PICSlave, ICW1Init | ICW14);
	IOWait();

	outb(PICMaster + 1, Offset);
	IOWait();

	outb(PICSlave + 1, Offset1);
	IOWait();

	outb(PICMaster + 1, 1 << IRQCascade);
	IOWait();

	outb(PICSlave + 1, 2);
	IOWait();

	outb(PICMaster + 1, ICW48086);
	IOWait();

	outb(PICSlave + 1, ICW48086);
	IOWait();

	outb(PICMaster + 1, 0x00);
	outb(PICSlave + 1, 0x00);
}