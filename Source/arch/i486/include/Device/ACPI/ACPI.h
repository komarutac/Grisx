#pragma once
#include <stdint.h>
#include <DAL.h>
#define ZeroOp 0x00
#define OneOp 0x01
#define AliasOp 0x06
#define NameOp 0x08
#define BytePrefix 0x0A
#define WordPrefix 0x0B
#define DWordPrefix 0x0C
#define StringPrefix 0x0D
#define QWordPrefix 0x0E
#define ScopeOp 0x10
#define BufferOp 0x11
#define PackageOp 0x12
#define VarPackageOp 0x13
#define MethodOp 0x14
#define ExternalOp 0x15
#define DualNamePrefix 0x2E
#define MultiNamePrefix 0x2F
#define DigitChar 0x30
#define NameChar 0x41
#define ExtOpPrefix 0x5B
#define RootChar 0x5C
#define ParentPrefixChar 0x5E
#define NameCharUnder 0x5F

extern DALDevice* ACPISystem;
extern void ACPIUninit(DALDevice* Device);
extern void ACPIInit(DALDevice* Device);
extern void* ACPICommand(int Function, void* Arguments, DALDevice* Device);
extern void ACPINoDriverInit(DALDevice* Device);