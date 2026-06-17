#pragma once
#include <Abstraction/DAL.h>
#include <stdint.h>
#include <macro.h>

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

extern independent DALDevice* CheckPCIBus(uint8_t Bus, DALDevice* BusDevice);
extern independent DALDevice* CheckPCIDevice(uint8_t Bus, uint8_t Device, DALDevice* BusDevice);
extern independent void CheckPCIFunction(uint8_t Bus, uint8_t Device, uint8_t Function, DALDevice* ParentDevice);
extern independent void PCIApplyName(uint8_t BaseClass, uint8_t SubClass, uint8_t ProgIF, DALDevice* Device);
extern dependent uint16_t PCIReadWord(uint8_t Bus, uint8_t Slot, uint8_t Function, uint8_t Offset);
extern dependent uint8_t PCIReadByte(uint8_t Bus, uint8_t Slot, uint8_t Function, uint8_t Offset);
extern independent void PCIUninit();
extern independent void PCIInit();
extern independent void* PCICommand(char Function, void* Arguments, DALDevice*);
extern independent bool PCITest(DALDevice* Device);
extern DALDevice* PCIDevice;