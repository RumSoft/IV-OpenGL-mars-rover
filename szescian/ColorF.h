#pragma once

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

class ColorF
{
public:
	float rgba[4];

	ColorF(
		const float r = 0, 
		const float g = 0, 
		const float b = 0, 
		const float a = 1)
	{
		rgba[0] = r;
		rgba[1] = g;
		rgba[2] = b;
		rgba[3] = a;
	}

	ColorF(int hex)
	{
		rgba[0] = ((hex >> 16) & 0xFF) / 255.0;  // Extract the RR byte
		rgba[1] = ((hex >> 8) & 0xFF) / 255.0;   // Extract the GG byte
		rgba[2] = ((hex) & 0xFF) / 255.0;        // Extract the BB byte
		rgba[3] = 1;
	}

	ColorF Red(float r) { r = min(1, r); rgba[0] = r; return *this; }
	ColorF Green(float g) { g = min(1, g); rgba[1] = g; return *this; }
	ColorF Blue(float b) { b = min(1, b);  rgba[2] = b; return *this; }
	ColorF Opacity(float a) { a = min(1, a); rgba[3] = a; return *this; }
	GLfloat* GL() { return rgba; }

};

#define RED   ColorF(1,0,0)
#define GREEN ColorF(0,1,0)
#define BLUE  ColorF(0,0,1)
#define BLACK ColorF(0,0,0)
#define WHITE ColorF(1,1,1)
#define GRAY ColorF(0.5,0.5,0.5)
#define DARKGRAY ColorF(0.25,0.25,0.25)
#define LIGHTGRAY ColorF(0.75,0.75,0.75)


