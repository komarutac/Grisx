#include <Color.h>
#include <vgatext.h>

void VCSetForegroundColor(ARGB Color) {
	VCForegrond = Color.Red;
	VCTextColor = VGATextColor(VCBackground, VCForegrond);
}