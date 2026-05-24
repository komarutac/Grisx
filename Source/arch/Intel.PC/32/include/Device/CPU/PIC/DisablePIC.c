#include <Device/CPU/PIC.h>
#include <Device/IO.h>

void DisablePIC() {
	outb(PICMaster + 1, 0xFF);
	outb(PICSlave + 1, 0xFF);
}