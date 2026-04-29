#include "Graphics.h"
#include <DAL.h>

int VGAApplyGeneric(DALDevice* GraphicsCtrl)
{
	GraphicsCtrl->Initialize(VGAInitializeHandler);
	GraphicsCtrl->Uninitialize(VGAUninitializeHandler);
	GraphicsCtrl->Command(VGACommadHandler);
}

void VGAInitializeHandler(DALDevice* GraphicsCtrl)
{
	GraphicsCtrl->SendKrnMessage(MsgDevReady, GraphicsCtrl);
}

void VGAUninitializeHandler(DALDevice* GraphicsCtrl)
{
	GraphicsCtrl->SendKrnMessage(MsgDevUnloaded, GraphicsCtrl);
}

void VGACommandHandler(int Function, void* Arguments, DALDevice* GraphicsCtrl) 
{
	(void)Function;
	(void)Arguments;
	(void)GraphicsCtrl;
}