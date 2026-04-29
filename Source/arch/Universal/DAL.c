#include <DAL.h>
#include <stddef.h>
#include <Device/Terminal/Console.h>
#include <VFS.h>
#include <Die.h>

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

DALDevice* DALGet(char* Name, DALDevice** List) {
	int i = 1;
	for (;;) {
		if (List[i] == NULL) {
			break;
		}
		
		DALDevice* Device = List[i];
		
		if (strcmp(Device->Name, Name) == 0) {
			return Device;
		}
		
		if (Device->ChildrenCount > 0) {
			DALDevice* Child = DALGet(Name, Device->Children);
			if (Child != 0) {
				return Child;
			}
		}
		
		i++;
	}
	return NULL;
}

void RegisterDALDevice(DALDevice* Device, void* MessageHandler) {
	if (DALDevicesIndex++ < 255) {
		if (Device->Name == NULL) {
			Oops("invalid device name", "device");
			return;
		}
		VFSEntry* DeviceFile = &(VFSEntry) {};
		DeviceFile->Name = Device->Name;
		if (VirtualDev->Next != 0) {
			DeviceFile->Next = VirtualDev->Next;
			VirtualDev->Next->Previous = DeviceFile;
		}
		DeviceFile->Previous = VirtualDev;
		VirtualDev->Next = DeviceFile;
		ConFormatTo(DefaultConsole, "Registering %s\r\n", Device->Name);
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
		VFSEntry* DeviceFile = &(VFSEntry) {};
		DeviceFile->Name = Child->Name;
		if (VirtualDev->Next != 0) {
			DeviceFile->Next = VirtualDev->Next;
			VirtualDev->Next->Previous = DeviceFile;
		}
		DeviceFile->Previous = VirtualDev;
		VirtualDev->Next = DeviceFile;
		ConFormatTo(DefaultConsole, "Registering %s\r\n", DeviceFile->Name);
		Parent->Children[Parent->ChildrenCount] = Child;
		Parent->Children[Parent->ChildrenCount]->SendKrnMessage = MessageHandler;
		if (Parent->Children[Parent->ChildrenCount]->Initialize) {
			Parent->Children[Parent->ChildrenCount]->Initialize(Child);
		}
	}
}

void PlaceholderInit(DALDevice* Device) {
	Device->SendKrnMessage(MsgDevReady, Device);
} 

void PlaceholderUninit(DALDevice* Device) {
	Device->SendKrnMessage(MsgDevUnloaded, Device);
} 

void* PlaceholderCommand(int Function, void* Arguments, DALDevice* Device) {
	(void)Device;
	(void)Arguments;
	(void)Function;
	return NULL;
} 