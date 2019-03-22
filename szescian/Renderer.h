#pragma once
#define BITMAP_ID 0x4D42

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <cmath>

class Renderer {
public:
	int LastWidth;
	int LastHeight;

	void calcNormal(float v[3][3], float out[3])
	{
		float v1[3], v2[3];
		static const int x = 0;
		static const int y = 1;
		static const int z = 2;

		v1[x] = v[0][x] - v[1][x];
		v1[y] = v[0][y] - v[1][y];
		v1[z] = v[0][z] - v[1][z];
		v2[x] = v[1][x] - v[2][x];
		v2[y] = v[1][y] - v[2][y];
		v2[z] = v[1][z] - v[2][z];


		out[x] = v1[y] * v2[z] - v1[z] * v2[y];
		out[y] = v1[z] * v2[x] - v1[x] * v2[z];
		out[z] = v1[x] * v2[y] - v1[y] * v2[x];

		ReduceToUnit(out);
	}

	void ReduceToUnit(float vector[3])
	{
		float length;

		length = (float)sqrt(vector[0] * vector[0] +
			vector[1] * vector[1] +
			vector[2] * vector[2]);

		if (length == 0.0f)
			length = 1.0f;

		vector[0] /= length;
		vector[1] /= length;
		vector[2] /= length;
	}

	void ChangeSize(GLsizei w, GLsizei h)
	{
		GLfloat nRange = 100.0f;
		GLfloat fAspect;

		if (h == 0)
			h = 1;
		LastWidth = w;
		LastHeight = h;
		fAspect = (GLfloat)w / (GLfloat)h;

		glViewport(0, 0, w, h);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		if (w <= h)
			glOrtho(-nRange, nRange, -nRange * h / w, nRange * h / w, -nRange, nRange);
		else
			glOrtho(-nRange * w / h, nRange * w / h, -nRange, nRange, -nRange, nRange);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		/*
		gluPerspective(60.0f,fAspect,1.0,400);
		*/
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
	unsigned char* LoadBitmapFile(char* filename, BITMAPINFOHEADER* bitmapInfoHeader)
	{
		FILE* filePtr;
		BITMAPFILEHEADER	bitmapFileHeader;
		unsigned char* bitmapImage;
		int					imageIdx = 0;
		unsigned char		tempRGB;


		filePtr = fopen(filename, "rb");
		if (filePtr == NULL)
			return NULL;

		fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);

		if (bitmapFileHeader.bfType != BITMAP_ID)
		{
			fclose(filePtr);
			return NULL;
		}

		fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);

		fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);

		bitmapImage = (unsigned char*)malloc(bitmapInfoHeader->biSizeImage);

		if (!bitmapImage)
		{
			free(bitmapImage);
			fclose(filePtr);
			return NULL;
		}

		fread(bitmapImage, 1, bitmapInfoHeader->biSizeImage, filePtr);

		if (bitmapImage == NULL)
		{
			fclose(filePtr);
			return NULL;
		}

		for (imageIdx = 0; imageIdx < bitmapInfoHeader->biSizeImage; imageIdx += 3)
		{
			tempRGB = bitmapImage[imageIdx];
			bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
			bitmapImage[imageIdx + 2] = tempRGB;
		}

		fclose(filePtr);
		return bitmapImage;
	}
	HPALETTE GetOpenGLPalette(HDC hDC)
	{
		HPALETTE hRetPal = NULL;
		PIXELFORMATDESCRIPTOR pfd;
		LOGPALETTE* pPal;
		int nPixelFormat;
		int nColors;
		int i;
		BYTE RedRange, GreenRange, BlueRange;



		nPixelFormat = GetPixelFormat(hDC);
		DescribePixelFormat(hDC, nPixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd);


		if (!(pfd.dwFlags & PFD_NEED_PALETTE))
			return NULL;

		nColors = 1 << pfd.cColorBits;

		pPal = (LOGPALETTE*)malloc(sizeof(LOGPALETTE) + nColors * sizeof(PALETTEENTRY));

		pPal->palVersion = 0x300;
		pPal->palNumEntries = nColors;




		RedRange = (1 << pfd.cRedBits) - 1;
		GreenRange = (1 << pfd.cGreenBits) - 1;
		BlueRange = (1 << pfd.cBlueBits) - 1;

		for (i = 0; i < nColors; i++)
		{

			pPal->palPalEntry[i].peRed = i >> pfd.cRedShift & RedRange;
			pPal->palPalEntry[i].peRed = (unsigned char)(
				(double)pPal->palPalEntry[i].peRed * 255.0 / RedRange);
			pPal->palPalEntry[i].peGreen = i >> pfd.cGreenShift & GreenRange;
			pPal->palPalEntry[i].peGreen = (unsigned char)(
				(double)pPal->palPalEntry[i].peGreen * 255.0 / GreenRange);
			pPal->palPalEntry[i].peBlue = i >> pfd.cBlueShift & BlueRange;
			pPal->palPalEntry[i].peBlue = (unsigned char)(
				(double)pPal->palPalEntry[i].peBlue * 255.0 / BlueRange);
			pPal->palPalEntry[i].peFlags = (unsigned char)NULL;
		}

		hRetPal = CreatePalette(pPal);

		SelectPalette(hDC, hRetPal, FALSE);
		RealizePalette(hDC);

		free(pPal);

		return hRetPal;
	}
	void SetDCPixelFormat(HDC hDC)
	{
		int nPixelFormat;
		static PIXELFORMATDESCRIPTOR pfd = {
			sizeof(PIXELFORMATDESCRIPTOR),
			1,
			PFD_DRAW_TO_WINDOW |
			PFD_SUPPORT_OPENGL |
			PFD_DOUBLEBUFFER,
			PFD_TYPE_RGBA,
			24,
			0,0,0,0,0,0,
			0,0,
			0,0,0,0,0,
			32,
			0,
			0,
			PFD_MAIN_PLANE,
			0,
			0,0,0
		};


		nPixelFormat = ChoosePixelFormat(hDC, &pfd);

		SetPixelFormat(hDC, nPixelFormat, &pfd);
	}
	void SetupRC()
	{
		glEnable(GL_DEPTH_TEST);
		glFrontFace(GL_CCW);

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

		glColor3f(0.0, 0.0, 0.0);
	}

};