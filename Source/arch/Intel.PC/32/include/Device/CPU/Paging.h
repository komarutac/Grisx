#pragma once
#define PagePresentBit			(1 << 0)
#define PageReadWriteBit		(1 << 1)
#define PageUserSupervisorBit	(1 << 2)
#define PageWriteTransparentBit	(1 << 3)
#define PageCacheDisableBit		(1 << 4)
#define PageAccessedBit			(1 << 5)
#define PageDirtyBit			(1 << 6)
#define PageAvailBits           (1 << 9)
#define PageFrameBits			(1 << 12)

struct _PageTableEntry
{
    unsigned char P;
    unsigned char RW;
    unsigned char US;
    unsigned char PWT;
    unsigned char PCD;
    unsigned char A;
    unsigned char D;
    unsigned char Avail;
}; typedef struct _PageTableEntry PageTableEntry;