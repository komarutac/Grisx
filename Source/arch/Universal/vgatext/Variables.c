#include <vgatext.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

uint8_t VCCharLeft = 0;
uint8_t VCCharTop = 0;
uint8_t VCForeground = 0x7;
uint8_t VCBackground = 0x0;
uint8_t VCTextColor = 0x07;
uint8_t VCLineHeight = 0x01;
uint16_t VCConsoleBuffer[80 * 25];
uint8_t VCIndent = 4;
uint8_t VCResWidth = 80;
uint8_t VCResHeight = 25;
uint8_t VCResLeft = 0;
uint8_t VCResTop = 0;