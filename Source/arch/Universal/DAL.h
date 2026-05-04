#pragma once
#include <stdbool.h>
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

#define DeviceStatusUninit 0x01
#define DeviceStatusNotAvailable 0x02
#define DeviceStatusError 0x03
#define DeviceStatusOK 0x04

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

#define MsgDevReady 0x01
#define MsgDevError 0x02
#define MsgDevUnloaded 0x03
#define MsgDevUnplug 0x04
#define MsgDevPlug 0x05
#define MsgDevPollNeeded 0x06
#define MsgKrnShutdown 0x07

struct _DALProperties {
    int Bus;
    int IRQ;
    int Vendor;
    int Function;
    int Class;
    int SubClass;
    int Type;
    int Status;
}; typedef struct _DALProperties DALProperties;

struct _DALDevice {
    char* Name;
    DALProperties* Properties;
	int ChildrenCount;
	int Bar0;
	int Bar1;
	int Bar2;
	int Bar3;
	int Bar4;
    bool (*Test)(struct _DALDevice*);
    void (*Initialize)(struct _DALDevice*);
    void (*Uninitialize)(struct _DALDevice*);
    int (*GetStatus)(struct _DALDevice*);
	int (*SendKrnMessage)(int Message, struct _DALDevice*);
    void* (*Command)(int Function, void* Arguments, struct _DALDevice*);
	struct _DALDevice* Children[255];
}; typedef struct _DALDevice DALDevice;

extern DALDevice* DALDevices[255];
extern void RegisterDALDevice(DALDevice* Device, void* MessageHandler);
extern void RegisterDALDeviceChild(DALDevice* Parent, DALDevice* Child, void* MessageHandler);
extern void PlaceholderInit(DALDevice* Device);
extern void PlaceholderUninit(DALDevice* Device);
extern void* PlaceholderCommand(int Function, void* Arguments, DALDevice* Device);
extern int MessageCallback(int Message, DALDevice* Device);
extern void UninitializeDevices(DALDevice* Devices[]);
extern DALDevice* DALFindFirst(DALProperties Properties, DALDevice** List, bool TypeOnly);
extern bool DALPropertiesCompareType(DALProperties A, DALProperties B);
extern bool DALPropertiesCompare(DALProperties A, DALProperties B);