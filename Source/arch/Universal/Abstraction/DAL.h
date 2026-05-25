#pragma once
#include <stdbool.h>
#include <stdint.h>
#define DeviceType(A) (DALProperties){.Type=A}
#define DeviceBusCPU 0x01
#define DeviceBusISA 0x02
#define DeviceBusPCI 0x03
#define DeviceBusPCIe 0x04
#define DeviceBusUSB 0x05
#define DeviceBusSMBus 0x06
#define DeviceBusMCABus 0x07

#define DeviceTypeKeyboard 0x01
#define DeviceTypeVideo 0x02
#define DeviceTypeCom 0x03
#define DeviceTypeBattery 0x04
#define DeviceTypeDisplay 0x05
#define DeviceTypeDiskController 0x06
#define DeviceTypeDisk 0x07
#define DeviceTypeNetwork 0x08
#define DeviceTypeBus 0x09
#define DeviceTypeMouse 0x0A
#define DeviceTypeJoystick 0x0B
#define DeviceTypePIC 0x0C
#define DeviceTypeTimer 0x0D
#define DeviceTypeACPI 0x0E
#define DeviceTypePowerManagement 0x0F
#define DeviceTypeArch 0x10
#define DeviceTypePlatform 0x11
#define DeviceTypeMultimediaController 0x12
#define DeviceTypeNetworkController 0x13
#define DeviceTypeVideoController 0x14
#define DeviceTypeMemoryController 0x15
#define DeviceTypeBridge 0x16
#define DeviceTypeCryptoController 0x17
#define DeviceTypeCommController 0x18
#define DeviceTypeInputController 0x19
#define DeviceTypeSerialBusController 0x1A
#define DeviceTypeWirelessController 0x1B

#define DeviceStatusNotAvailable 0x00
#define DeviceStatusUninit 0x01
#define DeviceStatusError 0x02
#define DeviceStatusOK 0x04
#define DeviceStatusBusy 0x08

#define DeviceVideoBPP4 0x04
#define DeviceVideoBPP8 0x08
#define DeviceVideoBPP15 0x0F
#define DeviceVideoBPP16 0x10
#define DeviceVideoBPP24 0x18
#define DeviceVideoBPP32 0x20

#define DeviceCommandDisplaySetBank 0x00
#define DeviceCommandDisplaySetMode 0x01
#define DeviceCommandDisplayGetModes 0x02
#define DeviceCommandDisplayDisable 0x03
#define DeviceCommandDisplayEnable 0x04


#define DevCMDSetCursor 0x05
#define DevCMDDrawLine 0x06
#define DevCMDDrawRect 0x07
#define DevCMDDrawBitmap 0x08

#define DevCMDAudioSetHz 0x09
#define DevCMDAudioPlayStop 0x0A
#define DevCMDAudioSetVolume 0x0B
#define DevCMDPowerShutdown 0x0C
#define DevCMDHasFunction 0x0D
#define DevCMDPowerRestart 0x0E
#define DevCMDGetDeviceInformation 0x0F
#define DevCMDSwitchToFallback 0x10

#define MsgDevReady 0x01
#define MsgDevError 0x02
#define MsgDevUnloaded 0x03
#define MsgDevUnplug 0x04
#define MsgDevPlug 0x05
#define MsgDevPollNeeded 0x06
#define MsgKrnShutdown 0x07

extern char* Storage;
extern char* Network;
extern char* Display;
extern char* Multimedia;
extern char* Memory;
extern char* Bridge;
extern char* Comm;
extern char* Input;
extern char* SerialBus;
extern char* Wireless;
extern char* Crypto;
extern char* BusHost;
extern char* Generic;

struct _DALProperties {
    char Bus;
    uint16_t IRQ;
    uint16_t Vendor;
    uint16_t Function;
    uint16_t Class;
    uint16_t SubClass;
    uint16_t Type;
    uint16_t Status;
    uint16_t HeaderType;
    uint16_t ProgIF;
    uint16_t DeviceID;
    bool Virtual;
}; typedef struct _DALProperties DALProperties;

struct _DALDevice {
    char* Name;
    DALProperties* Properties;
	char ChildrenCount;
	uint16_t Bar0;
	uint16_t Bar1;
	uint16_t Bar2;
	uint16_t Bar3;
	uint16_t Bar4;
    bool (*Test)(struct _DALDevice*);
    void (*Initialize)(struct _DALDevice*);
    void (*Uninitialize)(struct _DALDevice*);
    char (*GetStatus)(struct _DALDevice*);
	char (*SendKrnMessage)(char Message, struct _DALDevice*);
    void* (*Command)(char Function, void* Arguments, struct _DALDevice*);
	struct _DALDevice* Children[32];
}; typedef struct _DALDevice DALDevice;

extern DALDevice* DALDevices[32];
extern void RegisterDALDevice(DALDevice* Device, void* MessageHandler);
extern void RegisterDALDeviceChild(DALDevice* Parent, DALDevice* Child, void* MessageHandler);
extern void PlaceholderInit(DALDevice* Device);
extern void PlaceholderUninit(DALDevice* Device);
extern void* PlaceholderCommand(int Function, void* Arguments, DALDevice* Device);
extern int MessageCallback(int Message, DALDevice* Device);
extern void UninitializeDevices(DALDevice* Devices[]);
extern DALDevice* DALFindFirst(DALProperties Properties, DALDevice** List, bool TypeOnly);
extern bool DALPropertiesCompare(DALProperties A, DALProperties B);