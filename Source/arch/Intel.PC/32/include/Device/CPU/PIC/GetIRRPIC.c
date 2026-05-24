#include <Device/CPU/PIC.h>
#include <stdint.h>
#include <Device/IO.h>

uint16_t GetIRRPIC() {
	return GetIRQRegisterPIC(ReadIRRPIC);
}