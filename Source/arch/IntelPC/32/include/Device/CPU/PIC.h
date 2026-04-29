#ifndef C_DEVICE_8259_PIC_HEADER
#define C_DEVICE_8259_PIC_HEADER
#include <stdint.h>
#include <Device/IO.h>
#include <DAL.h>

#define PICMaster 0x20
#define PICSlave 0xA0
#define PICEOI 0x20
#define ICW14 0x01
#define ICW1Single 0x02
#define ICW1Interval4 0x04
#define ICW1Level 0x08
#define ICW1Init 0x10

#define ICW48086 0x01
#define ICW4Auto 0x02
#define ICW4BufferSlave 0x08
#define ICW4BufferMaster 0x0C
#define ICW4SFNM 0x10

#define IRQCascade 0x02

#define ReadIRRPIC 0x0A
#define ReadISRPIC 0x0B

extern DALDevice* PICDevice;

void SendPICEOI(uint8_t IRQ);
void RemapPIC(int Offset, int Offset1);
void SetIRQMask(uint8_t IRQLine);
void ClearIRQMask(uint8_t IRQLine);
uint16_t GetIRQRegisterPIC(int OCW3);
uint16_t GetIRRPIC();
uint16_t GetISRPIC();
void DisablePIC();
void PICUninit(DALDevice* Device);
void PICInit(DALDevice* Device);
#endif