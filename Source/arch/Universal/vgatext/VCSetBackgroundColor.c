#include <Color.h>
#include <vgatext.h>

void VCSetBackgroundColor(ARGB Color) {
	VCBackground = Color.Red;
	VCTextColor = VGATextColor(VCBackground, VCForegrond);
}