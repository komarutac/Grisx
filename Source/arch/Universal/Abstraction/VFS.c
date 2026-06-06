#include <Abstraction/VFS.h>
#include <Abstraction/DAL.h>
#include <stdint.h>
#include <stddef.h>
#include <Abstraction/Console.h>
#include <balloc.h>
#include <macro.h>
#include <string.h>

char* VFSLoopName = "vfsloop";

DALDevice* VFSLoopback = &(DALDevice) {
	.Properties = &(DALProperties) {
		.Bus = DeviceBusCPU,
		.Type = DeviceTypePowerManagement
	}
};

VFSMount* VirtualRootMount = &(VFSMount) {
	.PartID = 0,
};

VFSEntry* VFSRoot = 0;
VFSEntry* VFSLast = 0;

VFSEntry* VFSCreateFile(char* Name)
{
	VFSEntry* Entry = allocator(bump, alloc)(sizeof(VFSEntry));
	Entry->Name = allocator(bump, alloc)(strlen(Name) + 1);
	strcpy(Name, Entry->Name);
	return Entry;
}

VFSEntry* VFSCreateDirectory(char* Name)
{
	VFSEntry* Entry = allocator(bump, alloc)(sizeof(VFSEntry));
	Entry->Flags |= 0b000000001; // Set directory bit
	Entry->Name = allocator(bump, alloc)(strlen(Name) + 1);
	strcpy(Name, Entry->Name);
	return Entry;
}

void VFSInit(void* MessageCallback) {
	VFSLoopback->Name = VFSLoopName;
	VirtualRootMount->Device = VFSLoopback;
	VFSAdd(VFSCreateDirectory("rom:/"));
	VFSAdd(VFSCreateDirectory("rom:/Device"));
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
	return Size;
}

int VFSLoopWrite(VFSEntry* Entry, char* Buffer, size_t Size, size_t Position) {
	return Size;
}