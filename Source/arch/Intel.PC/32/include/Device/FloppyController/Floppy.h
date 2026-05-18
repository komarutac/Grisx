#pragma once
#include <stdint.h>
#include <Abstraction/DAL.h>
#define FDCStatusARegister 0x3F0
#define FDCStatusBRegister 0x3F1
#define FDCDigitalOutputRegister 0x3F2
#define FDCTapeDriveRegister 0x3F3
#define FDCMainStatusRegister 0x3F4
#define FDCDataRateSelectRegister 0x3F4
#define FDCDataFIFO 0x3F5
#define FDCDigitalInputRegister 0x3F7
#define FDCConfigControlRegister 0x3F7

struct _FloppyDrives {
    uint8_t Slave;
    uint8_t Master;
}; StructType(_FloppyDrives, FloppyDrives);
