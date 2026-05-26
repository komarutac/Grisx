#include <Abstraction/VFS.h>
#include <Abstraction/DAL.h>
#include <stdint.h>
#include <stddef.h>
#include <Abstraction/Console.h>

char* VFSLoopName = "vfsloop";

VFSEntry* VirtualDev = &(VFSEntry) {
	.Name = "Device",
	.Directory = 1,
};

DALDevice* VFSLoopback = &(DALDevice) {
	.Properties = &(DALProperties) {
		.Bus = DeviceBusCPU,
		.Type = DeviceTypePowerManagement
	}
};

VFSMount* VirtualRootMount = &(VFSMount) {
	.PartID = 0
};

VFSEntry* VirtualRoot = &(VFSEntry) {
	.Name = "/",
	.Directory = 1,
	.MountLink = 1
};
VFSEntry* VirtualLoop = &(VFSEntry) {
	.Name = "loop",
};

VFSEntry* VFSRoot = 0;
VFSEntry* VFSLast = 0;

void VFSInit(void* MessageCallback) {
	VFSLoopback->Name = VFSLoopName;
	VirtualRootMount->Device = VFSLoopback;
	VFSLast = VirtualLoop;
	VFSAdd(VirtualRoot);
	VFSAdd(VirtualDev);
	RegisterDALDevice(VFSLoopback, MessageCallback);
}

void VFSAdd(VFSEntry* Entry) {
	printf("Adding VFS entry %s\r\n", Entry->Name);
	VFSLast->Next = Entry;
	VFSLast = Entry;
}

void VFSSetLoop(VFSEntry* Entry) {
	Entry->Read = VFSLoopRead;
	Entry->Write = VFSLoopWrite;
}

int VFSLoopRead(VFSEntry* Entry, char* Buffer, size_t Size) {
	/*if (Size > Entry->CacheSize) {
		return -1;
	}
	
	for (size_t i = 0; i < Size; i++) {
		Buffer[i] = Entry->Cache[i];
	}*/
	return Size;
}

int VFSLoopWrite(VFSEntry* Entry, char* Buffer, size_t Size, size_t Position) {
	/*if (Size + Position > Entry->CacheSize) {
		return -1;
	}
	
	for (size_t i = Position; i < Size; i++) {
		Entry->Cache[i] = Buffer[i];
	}*/
	return Size;
}