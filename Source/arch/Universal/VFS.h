#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <DAL.h>

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
	bool Directory;
	bool MountLink;
	size_t Size;
	char Cache[512];
	size_t CacheSize;
	VFSMount* Mount;
    int (*Read)(struct _VFSEntry* Entry, char* Buffer, size_t Size);
    int (*Write)(struct _VFSEntry* Entry, char* Buffer, size_t Size, size_t Position);
	struct _VFSEntry* Link;
	struct _VFSEntry* Child;
	struct _VFSEntry* Previous;
	struct _VFSEntry* Next;
}; typedef struct _VFSEntry VFSEntry;

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