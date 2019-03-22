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

	ColorF Opacity(const float f)
	{
		rgba[3] = f;
		return *this;
	}

	GLfloat* GL() { return rgba; }
};

#define RED   ColorF(1,0,0)
#define GREEN ColorF(0,1,0)
#define BLUE  ColorF(0,0,1)
#define BLACK ColorF(0,0,0)
#define WHITE ColorF(1,1,1)
