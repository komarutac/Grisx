#pragma once
#include <stdbool.h>
#include <Shared/int.h>
#include <Device/IO.h>

#define CMOSAddressRegister 0x70
#define CMOSDataRegister 0x71

#define RTCStatusARegister 0x0A
#define RTCStatusBRegister 0x0B
#define RTCYearRegister 0x09
#define RTCMonthRegister 0x08
#define RTCDayRegister 0x07
#define RTCWeekDayRegister 0x06
#define RTCHourRegister 0x04
#define RTCMinuteRegister 0x02
#define RTCSecondRegister 0x00

#define FloppyInfoRegister 0x10
#define FloppyNoDrive 0x00
#define Floppy525Inch360KB 0x01
#define Floppy525Inch12MB 0x02
#define Floppy35Inch720KB 0x03
#define Floppy35Inch144MB 0x04
#define Floppy35Inch288MB 0x05

Byte RTCSecond, RTCMinute, RTCHour, RTCDay, RTCMonth;
int RTCYear;