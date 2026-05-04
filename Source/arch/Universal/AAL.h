#include <DAL.h>
#define AALDisableInterrupts 0x00
#define AALEnableInterrupts 0x01
#define AALSaveRegisters 0x02
#define AALRestoreRegisters 0x03
#define AALHalt 0x04
extern DALDevice* ArchDevice;