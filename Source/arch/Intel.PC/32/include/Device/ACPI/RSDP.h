#pragma once
#include <stdint.h>
#include <stdbool.h>

struct _RSDP {
	char Magic[8];
	uint8_t Checksum;
	char OEM[6];
	uint8_t Version;
	uint32_t RSDTAddress;
}; typedef struct _RSDP RSDP;

struct _SDT {
	char Magic[4];
	uint32_t Size;
	uint8_t Version;
	uint8_t Checksum;
	char OEM[6];
	char OEMTable[8];
	uint32_t OEMVersion;
	uint32_t Creator;
	uint32_t CreatorVersion;
}; typedef struct _SDT SDT;

struct _Address
{
	uint8_t AddressSpace;
	uint8_t BitWidth;
	uint8_t BitOffset;
	uint8_t AccessSize;
	size_t Address;
}; typedef struct _Address Address;

struct _FADT {
	char Magic[4];
	uint32_t Size;
	uint8_t Version;
	uint8_t Checksum;
	char OEMID[6];
	char OEMTable[8];
	uint32_t OEMVersion;
	uint32_t Creator;
	uint32_t CreatorVersion;
	
	uint32_t FirmwareControl;
    uint32_t DSDT;
	uint8_t Reserved;
	uint8_t PowerMgmtProfile;
	uint16_t SCI;
	uint32_t SMICmdPort;
	uint8_t ACPIEnable;
	uint8_t ACPIDisable;
	uint8_t S4BIOSReq;
	uint8_t PSTATEControl;
	uint32_t PM1aEventBlock;
	uint32_t PM1bEventBlock;
	uint32_t PM1aControlBlock;
	uint32_t PM1bControlBlock;
	uint32_t PM2ControlBlock;
	uint32_t PMTimerBlock;
	uint32_t GPE0Block;
	uint32_t GPE1Block;
	uint8_t PM1EventLength;
	uint8_t PM1ControlLength;
	uint8_t PM2ControlLength;
	uint8_t PMTimerLength;
	uint8_t GPE0Length;
	uint8_t GPE1Length;
	uint8_t GPE1Base;
	uint8_t CStateControl;
	uint16_t WorstC2Latency;
	uint16_t WorstC3Latency;
	uint16_t FlushSize;
	uint16_t FlushStride;
	uint8_t DutyOffset;
	uint8_t DutyWidth;
	uint8_t DayAlarm;
	uint8_t MonthAlarm;
	uint8_t Century;
	uint16_t Reserved2;
	uint8_t Reserved3;
	uint32_t Flags;
	Address ResetReg;
	uint8_t ResetValue;
	uint8_t Reserved4[3];
}; typedef struct _FADT FADT;

struct _RSDT {
	char Magic[4];
	uint32_t Size;
	uint8_t Version;
	uint8_t Checksum;
	char OEM[6];
	char OEMTable[8];
	uint32_t OEMVersion;
	uint32_t Creator;
	uint32_t CreatorVersion;
	uint32_t OtherSDT[((4 + 8 + 2 + 6 + 8 + 8 + 8) - sizeof(SDT)) / 4];
}; typedef struct _RSDT RSDT;

size_t SearchForRSDP();