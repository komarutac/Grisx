#include <DAL.h>
#include <stddef.h>
#include <Device/Terminal/Console.h>

DALDevice* DALDevices[255];
int DALDevicesIndex = 0;

void RegisterDALDevice(DALDevice* Device, void* MessageHandler) {
	if (DALDevicesIndex++ < 255) {
		ConFormatTo(DebugConsole, "%s,%d,%s: Registering device from location 0x%h with message handler from location 0x%h\r\n", __FILE__, __LINE__, __FUNCTION__, Device, MessageHandler);
		DALDevices[DALDevicesIndex] = Device;
		DALDevices[DALDevicesIndex]->SendKrnMessage = MessageHandler;
		if (DALDevices[DALDevicesIndex]->Initialize) {
			ConFormatTo(DebugConsole, "%s,%d,%s: Running device initialize function from 0x%h for device at location 0x%h\r\n", __FILE__, __LINE__, __FUNCTION__, DALDevices[DALDevicesIndex]->Initialize, Device);
			DALDevices[DALDevicesIndex]->Initialize(Device);
		} else {
			if (DALDevices[DALDevicesIndex]->SendKrnMessage) {
				DALDevices[DALDevicesIndex]->SendKrnMessage(MsgDevError, Device);
			}
		}
	}
}


void RegisterDALDeviceChild(DALDevice* Parent, DALDevice* Child, void* MessageHandler) {
	if (Parent->ChildrenCount++ < 255) {
		Parent->Children[Parent->ChildrenCount] = Child;
		Parent->Children[Parent->ChildrenCount]->SendKrnMessage = MessageHandler;
		if (Parent->Children[Parent->ChildrenCount]->Initialize) {
			Parent->Children[Parent->ChildrenCount]->Initialize(Child);
		} else {
			if (Parent->Children[Parent->ChildrenCount]->SendKrnMessage) {
				Parent->Children[Parent->ChildrenCount]->SendKrnMessage(MsgDevError, Child);
			}
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
	return NULL;
} 