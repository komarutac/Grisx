#include <Device/CPU/PIT.h>
#include <Device/CPU/Interrupt.h>

void TimerHandler(Registers* Regs) {
	(void)Regs;
	TimerTicks++;

	if (TimerCountDown != 0)
	{
		TimerCountDown--;
	}
}