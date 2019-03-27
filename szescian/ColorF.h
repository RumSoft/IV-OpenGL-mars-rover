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

	ColorF Red(const float r)		{ rgba[0] = r; return *this; }
	ColorF Green(const float g)		{ rgba[1] = g; return *this; }
	ColorF Blue(const float b)		{ rgba[2] = b; return *this; }
	ColorF Opacity(const float a)	{ rgba[3] = a; return *this; }
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


