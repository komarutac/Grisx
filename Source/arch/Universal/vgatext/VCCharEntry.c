#include <stdint.h>
#include <vgatext.h>

uint16_t VCCharEntry(const uint16_t Char, const uint16_t Attribute) {
	return Char | Attribute << 8;
}