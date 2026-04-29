#ifndef C_SHARED_ADDRESS_HEADER
#define C_SHARED_ADDRESS_HEADER
#include <Shared/Def.h>
#include <stdint.h>

struct _AddressStruct {
    size_t VirtualAddress;
    size_t PhysicalAddress;
} StructPacked StructType(_AddressStruct, AddressStruct);

#endif