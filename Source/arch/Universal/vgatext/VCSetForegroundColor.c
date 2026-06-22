#include <Color.h>
#include <vgatext.h>

void VCSetForegroundColor(ARGB Color) {
	VCForeground = 0;

	if (Color.Red == 0)
	{
		if (Color.Green == 0)
		{
			if (Color.Blue == 0)
			{
				VCForeground = 0;
			}

			if (Color.Blue == 170)
			{
				VCForeground = 1;
			}
		}

		if (Color.Green == 170)
		{
			if (Color.Blue == 0)
			{
				VCForeground = 2;
			}

			if (Color.Blue == 170)
			{
				VCForeground = 3;
			}
		}
	}

	if (Color.Red == 170)
	{
		if (Color.Green == 0)
		{
			if (Color.Blue == 0)
			{
				VCForeground = 4;
			}

			if (Color.Blue == 170)
			{
				VCForeground = 5;
			}
		}

		if (Color.Green == 85 && Color.Blue == 0)
		{
			VCForeground = 6;
		}

		if (Color.Green == 170 && Color.Blue == 170)
		{
			VCForeground = 7;
		}
	}

	if (Color.Red == 85)
	{
		if (Color.Green == 85)
		{
			if (Color.Blue == 85)
			{
				VCForeground = 8;
			}

			if (Color.Blue == 255)
			{
				VCForeground = 9;
			}
		}

		if (Color.Green == 255)
		{
			if (Color.Blue == 85)
			{
				VCForeground = 10;
			}

			if (Color.Blue == 255)
			{
				VCForeground = 11;
			}
		}
	}

	if (Color.Red == 255)
	{
		if (Color.Green == 85)
		{
			if (Color.Blue == 85)
			{
				VCForeground = 12;
			}
			
			if (Color.Blue == 255)
			{
				VCForeground = 13;
			}
		}

		if (Color.Green == 255)
		{
			if (Color.Blue == 85)
			{
				VCForeground = 14;
			}
			
			if (Color.Blue == 255)
			{
				VCForeground = 15;
			}
		}
	}
	VCTextColor = VGATextColor(VCForeground, VCForeground);
}