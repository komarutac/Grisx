#pragma once
struct _AllocCtx
{
    char TypeOfMemory;
    char TypeOfAllocator;
    int AllocatorID;
}; typedef struct _AllocCtx AllocCtx;

extern void SetAllocCtx(AllocCtx Ctx);
extern AllocCtx GetAllocCtx();