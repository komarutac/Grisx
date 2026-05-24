#include <Abstraction/DAL.h>
#include <Device/CPU/PIT.h>

void* PITCommandFunc(int Function, void* Arguments, DALDevice* Device) {
	(void)Device;
	if (Function == DevCMDAudioSetHz) {
		SetBeepHz(*(int*)Arguments);
	} else if (Function == DevCMDAudioPlayStop) {
		bool Play = *(bool*)Arguments;
		if (Play)
			PlayPCBeep();
		else
			StopPCBeep();
	}
	return 0;
}