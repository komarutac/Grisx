#pragma once
#define VCRTCommand 0x3D4
#define VCRTValue 0x3D5
#define VGATextColor(Background, Foreground) (Foreground | Background << 4)
#include <Device/IO.h>
#include <Device/VGA/Font8x8.h>
#include <Device/Terminal/Console.h>
#include <stdint.h>
#define VCPage (VCResWidth * VCResHeight)

#define VGA_SEQ_INDEX_PORT 0x3C4
#define VGA_SEQ_DATA_PORT 0x3C5

#define VGA_GC_INDEX_PORT 0x3CE
#define VGA_GC_DATA_PORT 0x3CF

#define VGA_CRTC_INDEX_PORT 0x3D4
#define VGA_CRTC_DATA_PORT 0x3D5

#define VGA_SEQ_MAP_MASK_REG 0x02
#define VGA_SEQ_CHARSET_REG 0x03
#define VGA_SEQ_MEMORY_MODE_REG 0x04

#define VGA_GC_READ_MAP_SELECT_REG 0x04
#define VGA_GC_GRAPHICS_MODE_REG 0x05
#define VGA_GC_MISC_REG 0x06

extern void VCWriteRegister(uint16_t Port, uint8_t Register, uint8_t Value);
extern uint8_t VCReadRegister(uint16_t Port, uint8_t Register);
extern void VCSetPlane(unsigned Plane);
extern void VCSetFont(uint8_t *Buffer, uint16_t FontHeight);

extern uint8_t VCResWidth;
extern uint8_t VCResHeight;
extern uint8_t VCResLeft;
extern uint8_t VCResTop;
extern uint16_t* VCTextBuffer0;
extern uint8_t VCCharLeft;
extern uint8_t VCCharTop;
extern uint8_t VCForegrond;
extern uint8_t VCBackground;
extern uint8_t VCTextColor;
extern uint8_t VCLineHeight;
extern uint16_t VCConsoleBuffer[80 * 50];
extern uint8_t VCIndent;
extern CommandQueueEntry CommandQueueSmallFont[45];

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
extern void VCLoadCommandQueue();
extern void VCClear();
extern void VCUpdate();
extern void VCAddEntry(uint16_t* Array, uint16_t Entry);
extern void VCWriteCharAt(uint8_t Char, int X, int Y);
extern void VCWriteChar(uint8_t Char);
extern void VCWriteString(char* Text);
extern void VCWriteLine(char* Text);
extern void VCLoadConsolePointers();
extern void VCExecuteCommandQueue();
extern unsigned char VCFont8x8[2048];
