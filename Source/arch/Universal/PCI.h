#pragma once
#include <Abstraction/DAL.h>
#include <stdint.h>
#define PCIInterruptAck 		0b0000
#define PCISpecialCycle 		0b0001
#define PCIIORead 				0b0010
#define PCIIOWrite 				0b0011
#define PCIMemRead 				0b0110
#define PCIMemWrite 			0b0111
#define PCIConfigRead 			0b1010
#define PCIConfigWrite 			0b1011
#define PCIMemReadMulti 		0b1100
#define PCIDualAddrCycle 		0b1101
#define PCIMemReadLine 			0b1110
#define PCIMemWriteAndInvalid 	0b1111

extern DALDevice* CheckPCIBus(uint8_t Bus, DALDevice* BusDevice);
extern DALDevice* CheckPCIDevice(uint8_t Bus, uint8_t Device, DALDevice* BusDevice);
extern uint16_t PCIReadConfig(uint8_t Bus, uint8_t Slot, uint8_t Function, uint8_t Offset);
extern uint8_t PCIReadByte(uint8_t Bus, uint8_t Slot, uint8_t Function, uint8_t Offset);
extern void PCIUninit();
extern void PCIInit();
extern void* PCICommand(int Function, void* Arguments, DALDevice*);
extern DALDevice* PCIDevice;
extern bool PCITest(DALDevice* Device);