#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <Abstraction/DAL.h>

struct _VFSMount {
	char* Name;
	int PartID;
	DALDevice* Device;
	struct _VFSMount* Previous;
	struct _VFSMount* Next;
}; typedef struct _VFSMount VFSMount;

struct _VFSEntry {
	char* Name;
	char* Extension;
	uint16_t Flags;
	size_t Size;
	VFSMount* Mount;
    int (*Read)(struct _VFSEntry* Entry, char* Buffer, size_t Size);
    int (*Write)(struct _VFSEntry* Entry, char* Buffer, size_t Size, size_t Position);
	struct _VFSEntry* Link;
	struct _VFSEntry* Child;
	struct _VFSEntry* Previous;
	struct _VFSEntry* Next;
}; typedef struct _VFSEntry VFSEntry;

// Flags
// Bit 1 (Directory)
// Bit 2 (Virtual)
// Bit 3 (Mount Link)
// Bit 4-9 (Reserved)

extern VFSEntry* VFSRoot;
extern VFSEntry* VFSLast;
extern void VFSChangeRootMount(VFSMount* Mount);
extern void VFSChangeRoot(VFSMount* Mount, VFSEntry* Root);
extern DALDevice* VFSLoopback;
extern void VFSInit(void* MessageCallback);
extern char* VFSLoopName;
extern void VFSAdd(VFSEntry* Entry);
extern int VFSLoopRead(VFSEntry* Entry, char* Buffer, size_t Size);
extern int VFSLoopWrite(VFSEntry* Entry, char* Buffer, size_t Size, size_t Position);
extern void VFSSetLoop(VFSEntry* Entry);
extern VFSEntry* VirtualDev;
extern VFSEntry* VirtualLoop;