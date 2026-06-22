#pragma once
#include <stdint.h>
#include <Color.h>
#define VCRTCommand 0x3D4
#define VCRTValue 0x3D5
#define VGATextColor(Background, Foreground) (Foreground | Background << 4)
#define VCPage (VCResWidth * VCResHeight)

extern void VCWriteRegister(uint16_t Port, uint8_t Register, uint8_t Value);
extern uint8_t VCReadRegister(uint16_t Port, uint8_t Register);
extern void VCSetPlane(unsigned Plane);
extern void VCSetFont(uint8_t* Buffer, uint16_t FontHeight);

extern uint8_t VCResWidth;
extern uint8_t VCResHeight;
extern uint8_t VCResLeft;
extern uint8_t VCResTop;
extern uint16_t* VCTextBuffer0;
extern uint8_t VCCharLeft;
extern uint8_t VCCharTop;
extern uint8_t VCForeground;
extern uint8_t VCBackground;
extern uint8_t VCTextColor;
extern uint8_t VCLineHeight;
extern uint16_t VCConsoleBuffer[80 * 25];
extern uint8_t VCIndent;

enum VGATextColors
{
	CTMBlack = 0x0,
	CTMBlue = 0x1,
	CTMGreen = 0x2,
	CTMCyan = 0x3,
	CTMRed = 0x4,
	CTMMagenta = 0x5,
	CTMBrown = 0x6,
	CTMGray = 0x7,
	CTMDarkGray = 0x8,
	CTMLightBlue = 0x9,
	CTMLightGreen = 0xA,
	CTMLightCyan = 0xB,
	CTMLightRed = 0xC,
	CTMLightMagenta = 0xD,
	CTMOrange = 0xE,
	CTMWhite = 0xF
};

extern uint16_t VCCharEntry(const uint16_t Char, const uint16_t Attribute);
extern int VCGetPixels();
extern uint16_t VCCreateIndex(const uint8_t Top, const uint8_t Left);
extern void VCScrollDown();
extern void VCSetForegroundColor(ARGB Color);
extern void VCSetBackgroundColor(ARGB Color);
extern void VCEraseLine();
extern void VCNewLine();
extern void VCClear();
extern void VCUpdate();
extern void VCAddEntry(uint16_t* Array, uint16_t Entry);
extern void VCWriteCharAt(uint8_t Char, int X, int Y);
extern void VCWriteChar(uint8_t Char);
extern void VCWriteString(char* Text);
extern void VCWriteLine(char* Text);
extern void VCLoadConsolePointers();
extern void VDisableCursor();
extern uint16_t VGetCursorPosition();
extern void VEnableCursor(const uint8_t Start, const uint8_t End);
extern void VMoveCursor(const uint8_t Top, const uint8_t Left);