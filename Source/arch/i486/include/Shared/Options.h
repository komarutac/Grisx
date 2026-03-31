#ifndef C_SHARED_OPTIONS_HEADER
#define C_SHARED_OPTIONS_HEADER
#include <Shared/int.h>
#include <Shared/Def.h>

// Required
#define OptionSign 0x7C02; // Must be 0xFF
#define OptionTextMode 0x7C03; // 0x00: 80x25 Color, 0x01: 80x25 Mono
#define OptionRootDriveController 0x7C04; // 0x00: Floppy, 0x01 ATA, 0x02 SCSI
#define OptionRootDriveNumber 0x7C05; // 0x00: A, 0x01: B, 0x02: C, 0x03: D, 0x04: E, 0x05: F, 0x06: G
#define OptionDebugMode 0x7C06; // 0x00: False, 0x01: True
#define OptionTextBufferAddress 0x7C07; // Not used.
#define OptionMainSerialAddress 0x7C08; // Not used.
#define OptionUseCPUID 0x7C09; // 0x00: False, 0x01: True

Byte* OPSign = (uint8_t*)OptionSign;
Byte* OPTextMode = (uint8_t*)OptionTextMode;
Byte* OPRootDC = (uint8_t*)OptionRootDriveController;
Byte* OPRootDN = (uint8_t*)OptionRootDriveNumber;
Byte* OPDebugMode = (uint8_t*)OptionDebugMode;
Byte* OPTextBuffer = (uint8_t*)OptionTextBufferAddress;
Byte* OPSerialAddr = (uint8_t*)OptionMainSerialAddress;
Byte* OPUseCPUID = (uint8_t*)OptionUseCPUID;
#endif