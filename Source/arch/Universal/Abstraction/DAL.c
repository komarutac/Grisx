#include <Abstraction/DAL.h>
#include <stddef.h>
#include <Abstraction/Console.h>
#include <Abstraction/VFS.h>
#include <Die.h>
#include <string.h>

char* Storage = "storagectrl";
char* Network = "networkctrl";
char* Display = "displayctrl";
char* Multimedia = "multimediactrl";
char* Memory = "memoryctrl";
char* Bridge = "bridge";
char* Comm = "commctrl";
char* Input = "inputctrl";
char* SerialBus = "serialctrl";
char* Wireless = "wirelessctrl";
char* Crypto = "cryptoctrl";
char* BusHost = "bushost";
char* Generic = "generic";

DALDevice* DALDevices[255];
int DALDevicesIndex = 0;

int MessageCallback(int Message, DALDevice* Device)
{		
	if (Message == MsgDevReady)
	{
		if (Device->Test != NULL)
		{
			printf("Testing %s\r\n", Device->Name);
			Device->Test(Device);
		}
		printf("Initialized %s\r\n", Device->Name);
	}
	
	if (Message == MsgDevUnloaded)
	{ 
		printf("Stopping %s\r\n", Device->Name);
	}

	if (Message == MsgDevError)
	{
		Oops("a device reported an error", Device->Name);
	}
	
	if (Message == MsgKrnShutdown)
	{
		printf("%s is requesting system shutdown\r\n", Device->Name);
		UninitializeDevices(DALDevices);
	}
	
	return 0;
}
void UninitializeDevices(DALDevice* Devices[])
{
	for (size_t i = 1; i < sizeof(DALDevice) / sizeof(Devices[0]); i++)
	{
		if (Devices[i] == NULL)
		{
			break;
		}
		DALDevice* Device = Devices[i];
		if (Device->ChildrenCount != 0)
		{
			UninitializeDevices(Device->Children);
		}
		if (Device->Uninitialize)
		{
			Device->Uninitialize(Device);
		}
		else
		{
			Oops("No uninitialize function for device\r\n", Device->Name);
		}
		Devices[i] = NULL;
	}  
}

bool DALPropertiesCompare(DALProperties A, DALProperties B)
{
	if (A.Bus == B.Bus && A.Class == B.Class && A.Function == B.Function && A.IRQ == B.IRQ &&
		A.Status == B.Status && A.SubClass == B.SubClass && A.Type == B.Type && A.Vendor == B.Vendor)
	{
		return true;
	}
	return false;
}

DALDevice* DALFindFirst(DALProperties Properties, DALDevice** List, bool TypeOnly)
{
	int i = 1;
	for (;;) {
		if (List[i] == NULL)
		{
			break;
		}
		
		DALDevice* Device = List[i];
		if (Device->Properties->Type == Properties.Type)
		{
			printf("OREO\r\n");
			return Device;
		}
		
		if (Device->ChildrenCount > 0)
		{
			DALDevice* Child = DALFindFirst(Properties, Device->Children, TypeOnly);
			if (Child != 0)
			{
				return Child;
			}
		}
		
		i++;
	}
	return NULL;
}
void RegisterDALDevice(DALDevice* Device, void* MessageHandler)
{
	if (DALDevicesIndex++ < 255) {
		if (Device->Name == NULL) {
			Oops("invalid device name", "device");
			return;
		}
		/* VFSEntry* DeviceFile = &(VFSEntry) {};
		DeviceFile->Name = Device->Name;
		if (VirtualDev->Next != 0) {
			DeviceFile->Next = VirtualDev->Next;
			VirtualDev->Next->Previous = DeviceFile;
		}
		DeviceFile->Previous = VirtualDev;
		VirtualDev->Next = DeviceFile; */
		ConFormatTo(DefaultConsole, "Registering %s, Class 0x%X/0x%X, ID 0x%X/0x%X as a parent\r\n", Device->Name, Device->Properties->Class, Device->Properties->SubClass, Device->Properties->DeviceID, Device->Properties->Vendor);
		DALDevices[DALDevicesIndex] = Device;
		DALDevices[DALDevicesIndex]->SendKrnMessage = MessageHandler;
		if (DALDevices[DALDevicesIndex]->Initialize) {
			DALDevices[DALDevicesIndex]->Initialize(Device);
		}
	}
}
void RegisterDALDeviceChild(DALDevice* Parent, DALDevice* Child, void* MessageHandler) {
	if (Parent->ChildrenCount++ < 255) {
		if (Child->Name == NULL) {
			Oops("invalid device name", "device");
			return;
		}
		/* VFSEntry* DeviceFile = &(VFSEntry) {};
		DeviceFile->Name = Child->Name;
		if (VirtualDev->Next != 0) {
			DeviceFile->Next = VirtualDev->Next;
			VirtualDev->Next->Previous = DeviceFile;
		}
		DeviceFile->Previous = VirtualDev;
		VirtualDev->Next = DeviceFile; */
		ConFormatTo(DefaultConsole, "Registering %s, Class 0x%X/0x%X, ID 0x%X/0x%X as a child\r\n", Child->Name, Child->Properties->Class, Child->Properties->SubClass, Child->Properties->DeviceID, Child->Properties->Vendor);
		Parent->Children[Parent->ChildrenCount] = Child;
		Parent->Children[Parent->ChildrenCount]->SendKrnMessage = MessageHandler;
		if (Parent->Children[Parent->ChildrenCount]->Initialize) {
			Parent->Children[Parent->ChildrenCount]->Initialize(Child);
		}
	}
}