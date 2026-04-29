#pragma once
#define StructType(Struct, Name) typedef struct Struct Name
#define StructPacked __attribute__((packed));
#define SectionVars(Start, End)  extern unsigned char Start[]; extern unsigned char End[];
#define Section(Name) __attribute__((noinline, section(Name)))
#include <stdbool.h>
#include <Shared/int.h>

enum DSupportedCPU {
    CPUi386,
    CPUi486,
    CPUP5,
    CPUP6,
    CPUAthlon64
};

typedef char* String;

extern char* KernelName;
extern int KernelVersion;
extern enum DSupportedCPU SupportedCPU;
extern bool DebugMode;
extern bool Takeover;

struct _CHS {
    Word Cylinders, Heads, Sectors;
}; StructType(_CHS, CHS);

String DSupportedCPUToString(enum DSupportedCPU CPU);

CHS LBAToCHs(int LBA, int SPT);