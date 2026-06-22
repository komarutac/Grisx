#include <Color.h>
#include <vgatext.h>

void VCSetBackgroundColor(ARGB Color) {
	VCBackground = 0;

	if (Color.Red == 0)
	{
		if (Color.Green == 0)
		{
			if (Color.Blue == 0)
			{
				VCBackground = 0;
			}

			if (Color.Blue == 170)
			{
				VCBackground = 1;
			}
		}

		if (Color.Green == 170)
		{
			if (Color.Blue == 0)
			{
				VCBackground = 2;
			}

			if (Color.Blue == 170)
			{
				VCBackground = 3;
			}
		}
	}

	if (Color.Red == 170)
	{
		if (Color.Green == 0)
		{
			if (Color.Blue == 0)
			{
				VCBackground = 4;
			}

			if (Color.Blue == 170)
			{
				VCBackground = 5;
			}
		}

		if (Color.Green == 85 && Color.Blue == 0)
		{
			VCBackground = 6;
		}

		if (Color.Green == 170 && Color.Blue == 170)
		{
			VCBackground = 7;
		}
	}

	if (Color.Red == 85)
	{
		if (Color.Green == 85)
		{
			if (Color.Blue == 85)
			{
				VCBackground = 8;
			}

			if (Color.Blue == 255)
			{
				VCBackground = 9;
			}
		}

		if (Color.Green == 255)
		{
			if (Color.Blue == 85)
			{
				VCBackground = 10;
			}

			if (Color.Blue == 255)
			{
				VCBackground = 11;
			}
		}
	}

	if (Color.Red == 255)
	{
		if (Color.Green == 85)
		{
			if (Color.Blue == 85)
			{
				VCBackground = 12;
			}
			
			if (Color.Blue == 255)
			{
				VCBackground = 13;
			}
		}

		if (Color.Green == 255)
		{
			if (Color.Blue == 85)
			{
				VCBackground = 14;
			}
			
			if (Color.Blue == 255)
			{
				VCBackground = 15;
			}
		}
	}

	VCTextColor = VGATextColor(VCBackground, VCForeground);
}