#include <stdint.h>
#include <DAL.h>

extern int VGAApplyGeneric(DALDevice* GraphicsCtrl);
extern void VGAInitializeHandler(DALDevice* GraphicsCtrl);
extern void VGAUninitializeHandler(DALDevice* GraphicsCtrl);
extern void VGACommandHandler(int Function, void* Arguments, DALDevice* GraphicsCtrl); 