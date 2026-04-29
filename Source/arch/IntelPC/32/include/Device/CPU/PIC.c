#include "PIC.h"
#include <stdint.h>
#include <Device/IO.h>
#include <DAL.h>
#include <stdbool.h>

DALDevice* PICDevice = &(DALDevice){
	.Name = "interruptctrl",
	.Bus = DeviceBusISA,
	.Type = DeviceTypePIC,
	.Uninitialize = PICUninit,
	.Initialize = PICInit
};

void SendPICEOI(uint8_t IRQ) {
    if (IRQ >= 8) {
        outb(PICSlave, PICEOI);
    }

    outb(PICMaster, PICEOI);
}

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

void SetIRQMask(uint8_t IRQLine) {
    uint16_t Port;

    if (IRQLine < 8) {
        Port = PICMaster;
    } else {
        Port = PICSlave;
        IRQLine -= 8;
    }

    outb(Port, inb(Port) | (1 << IRQLine));
}

void ClearIRQMask(uint8_t IRQLine) {
    uint16_t Port;
    uint8_t Value;

    if (IRQLine < 8) {
        Port = PICMaster;
    } else {
        Port = PICSlave;
        IRQLine -= 8;
    }

    Value = inb(Port) & ~(1 << IRQLine);
    outb(Port, Value);
}

uint16_t GetIRQRegisterPIC(int OCW3) {
    outb(PICMaster, OCW3);
    outb(PICSlave, OCW3);
    return (inb(PICSlave + 1) << 8) | inb(PICMaster + 1);
}

uint16_t GetIRRPIC() {
    return GetIRQRegisterPIC(ReadIRRPIC);
}

uint16_t GetISRPIC() {
    return GetIRQRegisterPIC(ReadISRPIC);
}

void DisablePIC() {
    outb(PICMaster + 1, 0xFF);
    outb(PICSlave + 1, 0xFF);
}

void PICUninit(DALDevice* Device) {
	DisablePIC();
	Device->SendKrnMessage(MsgDevUnloaded, PICDevice);
}

void PICInit(DALDevice* Device) {
	RemapPIC(0x20, 0x28);
	Device->SendKrnMessage(MsgDevReady, PICDevice);
}
