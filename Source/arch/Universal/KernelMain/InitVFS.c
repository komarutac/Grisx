#include <Abstraction/VFS.h>
#include <Abstraction/DAL.h>
#include <KernelMain.h>

void InitVFS()
{
	VFSInit(MessageCallback);
}