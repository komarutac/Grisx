#include "PIC.h"
#include <stdint.h>
#include <Device/IO.h>
#include <Abstraction/DAL.h>
#include <stdbool.h>
#include <PPI.h>

DALDevice* PICDevice = &(DALDevice){
	.Name = "interruptctrl",
	.Properties = &(DALProperties) {
		.Bus = DeviceBusISA,
		.Type = DeviceTypePIC,
	},
	.Uninitialize = PICUninit,
	.Initialize = PICInit
};

void SendPICEOI(uint8_t IRQ) {
    PPITrace(__FUNCTION__);
	if (IRQ >= 8) {
		outb(PICSlave, PICEOI);
	}

	outb(PICMaster, PICEOI);
}

void RemapPIC(int Offset, int Offset1) { 
    PPITrace(__FUNCTION__);
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

void SetIRQMask(uint8_t IRQLine) {
    PPITrace(__FUNCTION__);
	uint16_t Port;
	uint8_t Temp;

	if (IRQLine < 8) {
		Port = PICMaster;
	} else {
		Port = PICSlave;
		IRQLine -= 8;
	}

	inb(Port, Temp);
	outb(Port, Temp | (1 << IRQLine));
}

void ClearIRQMask(uint8_t IRQLine) {
    PPITrace(__FUNCTION__);
	uint16_t Port;
	uint8_t Value;
	uint8_t Temp;

	if (IRQLine < 8) {
		Port = PICMaster;
	} else {
		Port = PICSlave;
		IRQLine -= 8;
	}

	inb(Port, Temp);
	Value = Temp & ~(1 << IRQLine);
	outb(Port, Value);
}

uint16_t GetIRQRegisterPIC(int OCW3) {
    PPITrace(__FUNCTION__);
	uint8_t Temp;
	uint8_t Temp2;
	outb(PICMaster, OCW3);
	outb(PICSlave, OCW3);
	inb(PICSlave + 1, Temp);
	inb(PICMaster + 1, Temp2);
	return (Temp << 8) |  Temp2;
}

uint16_t GetIRRPIC() {
	return GetIRQRegisterPIC(ReadIRRPIC);
}

uint16_t GetISRPIC() {
	return GetIRQRegisterPIC(ReadISRPIC);
}

void DisablePIC() {
    PPITrace(__FUNCTION__);
	outb(PICMaster + 1, 0xFF);
	outb(PICSlave + 1, 0xFF);
}

void PICUninit(DALDevice* Device) {
    PPITrace(__FUNCTION__);
	DisablePIC();
	Device->SendKrnMessage(MsgDevUnloaded, PICDevice);
}

void PICInit(DALDevice* Device) {
    PPITrace(__FUNCTION__);
	RemapPIC(0x20, 0x28);
	Device->SendKrnMessage(MsgDevReady, PICDevice);
}
