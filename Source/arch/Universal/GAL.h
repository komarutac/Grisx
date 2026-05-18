#pragma once
#include <DAL.h>
struct _GALRes {
	int Width;
	int Height;
	int BPP;
	int RefreshRate;
	bool LFB;
}; typedef _GALRes GALRes;

struct _GALDisplay {
	int Index;
	GALRes Properties;
	char* Name;
	DALDevice* Device;
}; typedef _GALDisplay GALDisplay;

struct _GALRect {
	int Width;
	int Height;
	int Top;
	int Left;
}; typedef _GALRect GALRect;

struct _GALPoint {
	int X, Y;
}; typedef _GALPoint GALPoint;

struct _GALAngle3D {
	int X, Y, Z;
}; typedef _GALAngle3D GALAngle3D;

struct _GALPoint3D {
	GALAngle3D Location;
	GALAngle3D Angle;
}; typedef _GALPoint GALPoint3D;

struct _GALPen {
	int Thickness;
	int Color;
	int OutlineColor;
}; typedef _GALPen GALPen;

struct _GALLine {
	GALPoint A;
	GALPoint B;
	GALPen Pen;
}; typedef _GALLine GALLine;

struct _GALBitmap {
	GALRect* Location;
	int BPP;
	int Size;
	char* Data;
}; typedef _GALBitmap GALBitmap;

void GALDrawLine(GALDisplay* Display, GALLine* Line);
void GALDrawRect(GALDisplay* Display, GALRect* Rect);
void GALDrawBitmap(GALDisplay* Display, GALBitmap* Bitmap);
void GALSetCursor(GALDisplay* Display, GALBitmap* Bitmap);