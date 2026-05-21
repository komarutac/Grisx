#pragma once
#include <stddef.h>

struct _CommonTransferHeader
{
	int Context;
	int Operation;
	size_t DataSize;
	size_t HeaderSize;
}; typedef struct _CommonTransferHeader CommonTransferHeader;

struct _CommonMessageHeader
{
	int RequestNumber;
	size_t HeaderSize;
	size_t DataSize;
}; typedef struct _CommonMessageHeader CommonMessageHeader;