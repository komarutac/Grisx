#pragma once
#include <DAL.h>
void VerifyConfig();
void SetupTextMode();
void SetupVideo();
void UninitializeDevices(DALDevice* Devices[]);
void ShutdownDevices();
int MessageCallback(int Message, DALDevice* Device);