#include <vgatext.h>
#include <stdint.h>

uint16_t VCCreateIndex(const uint8_t Top, const uint8_t Left) {
	return (Top * VCResWidth) + Left;
}