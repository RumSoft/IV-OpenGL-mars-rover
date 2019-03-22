

#define  _CRT_SECURE_NO_WARNINGS


#ifdef _MSC_VER                         
#  pragma comment(lib, "opengl32.lib")  
#  pragma comment(lib, "glu32.lib")     
#endif

#ifdef _MSC_VER        
#   ifndef _MBCS
#      define _MBCS    
#   endif
#   ifdef _UNICODE     
#      undef _UNICODE 
#   endif
#   ifdef UNICODE
#      undef UNICODE 
#   endif
#endif
#include <windows.h>            
#include <gl\gl.h>              
#include <gl\glu.h>             
#include <math.h>				
#include <stdio.h>
#include "resource.h"           

#define glRGB(x, y, z)	glColor3ub((GLubyte)x, (GLubyte)y, (GLubyte)z)
#define BITMAP_ID 0x4D42		
#define GL_PI 3.14

HPALETTE hPalette = NULL;

static LPCTSTR lpszAppName = "GL Template";
static HINSTANCE hInstance;

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
static GLsizei lastHeight;
static GLsizei lastWidth;

BITMAPINFOHEADER	bitmapInfoHeader;	
unsigned char* bitmapData;			
unsigned int		texture[2];			


LRESULT CALLBACK WndProc(HWND    hWnd,
	UINT    message,
	WPARAM  wParam,
	LPARAM  lParam);

BOOL APIENTRY AboutDlgProc(HWND hDlg, UINT message, UINT wParam, LONG lParam);

void SetDCPixelFormat(HDC hDC);


void ReduceToUnit(float vector[3])
{
	float length;
	
	length = (float)sqrt((vector[0] * vector[0]) +
		(vector[1] * vector[1]) +
		(vector[2] * vector[2]));
	
	
	if (length == 0.0f)
		length = 1.0f;
	
	
	vector[0] /= length;
	vector[1] /= length;
	vector[2] /= length;
}

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

void ChangeSize(GLsizei w, GLsizei h)
{
	GLfloat nRange = 100.0f;
	GLfloat fAspect;
	
	if (h == 0)
		h = 1;
	lastWidth = w;
	lastHeight = h;
	fAspect = (GLfloat)w / (GLfloat)h;
	
	glViewport(0, 0, w, h);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	if (w <= h)
		glOrtho(-nRange, nRange, -nRange * h / w, nRange * h / w, -nRange, nRange);
	else
		glOrtho(-nRange * w / h, nRange * w / h, -nRange, nRange, -nRange, nRange);
	
	/*
	gluPerspective(60.0f,fAspect,1.0,400);
	*/
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}



void SetupRC()
{
	
	
	
	
	
	

	glEnable(GL_DEPTH_TEST);	
	glFrontFace(GL_CCW);		
	

	
	

	
	
	
	
	
	

	
	

	
	

	
	
	
	

	
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	
	glColor3f(0.0, 0.0, 0.0);
}
void skrzynka(void)
{
	glColor3d(0.8, 0.7, 0.3);
	glEnable(GL_TEXTURE_2D); 

	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_QUADS);
	glNormal3d(0, 0, 1);
	glTexCoord2d(1.0, 1.0); glVertex3d(25, 25, 25);
	glTexCoord2d(0.0, 1.0); glVertex3d(-25, 25, 25);
	glTexCoord2d(0.0, 0.0); glVertex3d(-25, -25, 25);
	glTexCoord2d(1.0, 0.0); glVertex3d(25, -25, 25);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3d(1, 0, 0);
	glTexCoord2d(1.0, 1.0); glVertex3d(25, 25, 25);
	glTexCoord2d(0.0, 1.0); glVertex3d(25, -25, 25);
	glTexCoord2d(0.0, 0.0); glVertex3d(25, -25, -25);
	glTexCoord2d(1.0, 0.0); glVertex3d(25, 25, -25);
	glEnd();
	glDisable(GL_TEXTURE_2D); 

	glBegin(GL_QUADS);
	glNormal3d(0, 0, -1);
	glVertex3d(25, 25, -25);
	glVertex3d(25, -25, -25);
	glVertex3d(-25, -25, -25);
	glVertex3d(-25, 25, -25);
	glNormal3d(-1, 0, 0);
	glVertex3d(-25, 25, -25);
	glVertex3d(-25, -25, -25);
	glVertex3d(-25, -25, 25);
	glVertex3d(-25, 25, 25);
	glNormal3d(0, 1, 0);
	glVertex3d(25, 25, 25);
	glVertex3d(25, 25, -25);
	glVertex3d(-25, 25, -25);
	glVertex3d(-25, 25, 25);
	glNormal3d(0, -1, 0);
	glVertex3d(25, -25, 25);
	glVertex3d(-25, -25, 25);
	glVertex3d(-25, -25, -25);
	glVertex3d(25, -25, -25);
	glEnd();
}
void walec01(void)
{
	GLUquadricObj* obj;
	obj = gluNewQuadric();
	gluQuadricNormals(obj, GLU_SMOOTH);
	glColor3d(1, 0, 0);
	glPushMatrix();
	gluCylinder(obj, 20, 20, 30, 15, 7);
	gluCylinder(obj, 0, 20, 0, 15, 7);
	glTranslated(0, 0, 60);
	glRotated(180.0, 0, 1, 0);
	gluCylinder(obj, 0, 20, 30, 15, 7);
	glPopMatrix();
}
void kula(void)
{
	GLUquadricObj* obj;
	obj = gluNewQuadric();
	gluQuadricTexture(obj, GL_TRUE);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glColor3d(1.0, 0.8, 0.8);
	glEnable(GL_TEXTURE_2D);
	gluSphere(obj, 40, 15, 7);
	glDisable(GL_TEXTURE_2D);
}




unsigned char* LoadBitmapFile(char* filename, BITMAPINFOHEADER * bitmapInfoHeader)
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
void szescian(void)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	{
		

		GLfloat sa[3] = { 0.0f,0.0f,0.0f };
		GLfloat sb[3] = { 10.0f,0.0f,0.0f };
		GLfloat sc[3] = { 10.0f,10.0f,0.0f };
		GLfloat sd[3] = { 0.0f,10.0f,0.0f };
		GLfloat se[3] = { 0.0f,0.0f,-10.0f };
		GLfloat sf[3] = { 10.0f,0.0f,-10.0f };
		GLfloat sg[3] = { 10.0f,10.0f,-10.0f };
		GLfloat sh[3] = { 0.0f,10.0f,-10.0f };
		
		glColor3f(1.0f, 0.0f, 0.0f);
		glBegin(GL_POLYGON);
		glVertex3fv(sa);
		glVertex3fv(sb);
		glVertex3fv(sc);
		glVertex3fv(sd);
		glEnd();
		glColor3f(0.0f, 1.0f, 0.0f);
		glBegin(GL_POLYGON);
		glVertex3fv(sb);
		glVertex3fv(sf);
		glVertex3fv(sg);
		glVertex3fv(sc);
		glEnd();
		glColor3f(0.0f, 0.0f, 1.0f);
		glBegin(GL_POLYGON);
		glVertex3fv(sf);
		glVertex3fv(se);
		glVertex3fv(sh);
		glVertex3fv(sg);
		glEnd();
		glColor3f(1.0f, 1.0f, 0.0f);
		glBegin(GL_POLYGON);
		glVertex3fv(se);
		glVertex3fv(sa);
		glVertex3fv(sd);
		glVertex3fv(sh);
		glEnd();
		glColor3f(0.0f, 1.0f, 1.0f);
		glBegin(GL_POLYGON);
		glVertex3fv(sd);
		glVertex3fv(sc);
		glVertex3fv(sg);
		glVertex3fv(sh);
		glEnd();
		glColor3f(1.0f, 0.0f, 1.0f);
		glBegin(GL_POLYGON);
		glVertex3fv(sa);
		glVertex3fv(sb);
		glVertex3fv(sf);
		glVertex3fv(se);
		glEnd();
	}
}
void walec(double r, double h)
{
	double x, y, alpha, PI = 3.14;
	glBegin(GL_TRIANGLE_FAN);
	glColor3d(0.8, 0.0, 0);
	glVertex3d(0, 0, 0);
	for (alpha = 0; alpha <= 2 * PI; alpha += PI / 8.0)
	{
		x = r * sin(alpha);
		y = r * cos(alpha);
		glVertex3d(x, y, 0);
	}
	glEnd();
	glBegin(GL_QUAD_STRIP);
	for (alpha = 0.0; alpha <= 2 * PI; alpha += PI / 8.0)
	{
		x = r * sin(alpha);
		y = r * cos(alpha);
		glVertex3d(x, y, 0);
		glVertex3d(x, y, h);
	}
	glEnd();
	glBegin(GL_TRIANGLE_FAN);
	glVertex3d(0, 0, h);
	for (alpha = 0; alpha >= -2 * PI; alpha -= PI / 8.0)
	{
		x = r * sin(alpha);
		y = r * cos(alpha);
		glVertex3d(x, y, h);
	}
	glEnd();
}
void ramie(double r1, double r2, double h, double d)
{
	double PI = 3.14, alpha, x, y;
	glBegin(GL_TRIANGLE_FAN);
	glColor3d(0.8, 0.0, 0);
	glVertex3d(0, 0, 0);
	for (alpha = PI; alpha <= 2 * PI; alpha += PI / 8.0)
	{
		x = r1 * sin(alpha);
		y = r1 * cos(alpha);
		glVertex3d(x, y, 0);
	}
	glEnd();
	glBegin(GL_QUAD_STRIP);
	for (alpha = 0; alpha >= -PI; alpha -= PI / 8.0)
	{
		x = r1 * sin(alpha);
		y = r1 * cos(alpha);
		glVertex3d(x, y, h);
		glVertex3d(x, y, 0);
	}
	glEnd();
	glBegin(GL_TRIANGLE_FAN);
	glVertex3d(0, 0, h);
	for (alpha = 0; alpha >= -PI; alpha -= PI / 8.0)
	{
		x = r1 * sin(alpha);
		y = r1 * cos(alpha);
		glVertex3d(x, y, h);
	}
	glEnd();
	glBegin(GL_TRIANGLE_FAN);
	glColor3d(0.8, 0.0, 0);
	
	
	for (alpha = 0; alpha <= PI; alpha += PI / 8.0)
	{
		x = d + r2 * sin(alpha);
		y = d + r2 * cos(alpha);
		glVertex3d(x, y, 0);
	}
	glEnd();
	glBegin(GL_QUAD_STRIP);
	
	for (alpha = 0; alpha <= PI; alpha += PI / 8.0)
	{
		x = d + r2 * sin(alpha);
		y = d + r2 * cos(alpha);
		glVertex3d(x, y, h);
		glVertex3d(x, y, 0);
	}
	glEnd();
	glBegin(GL_TRIANGLE_FAN);
	
	for (alpha = 0; alpha <= PI; alpha += PI / 8.0)
	{
		x = d + r2 * sin(alpha);
		y = d + r2 * cos(alpha);
		glVertex3d(x, y, h);
	}
	glEnd();
}

void RenderScene(void)
{
	

	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glPushMatrix();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	
	
	
	

	
	glPolygonMode(GL_BACK, GL_LINE);
	
	szescian();
	
	

	
	

	
	
	
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	
	glFlush();
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
		0,0,0 };                                

	
	nPixelFormat = ChoosePixelFormat(hDC, &pfd);
	
	SetPixelFormat(hDC, nPixelFormat, &pfd);
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
		
		pPal->palPalEntry[i].peRed = (i >> pfd.cRedShift) & RedRange;
		pPal->palPalEntry[i].peRed = (unsigned char)(
			(double)pPal->palPalEntry[i].peRed * 255.0 / RedRange);
		pPal->palPalEntry[i].peGreen = (i >> pfd.cGreenShift) & GreenRange;
		pPal->palPalEntry[i].peGreen = (unsigned char)(
			(double)pPal->palPalEntry[i].peGreen * 255.0 / GreenRange);
		pPal->palPalEntry[i].peBlue = (i >> pfd.cBlueShift) & BlueRange;
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

int APIENTRY WinMain(HINSTANCE       hInst,
	HINSTANCE       hPrevInstance,
	LPSTR           lpCmdLine,
	int                     nCmdShow)
{
	MSG                     msg;            
	WNDCLASS        wc;                     
	HWND            hWnd;           

	hInstance = hInst;
	
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	
	wc.hbrBackground = NULL;
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU);
	wc.lpszClassName = lpszAppName;
	
	if (RegisterClass(&wc) == 0)
		return FALSE;
	
	hWnd = CreateWindow(
		lpszAppName,
		lpszAppName,
		
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
		
		50, 50,
		400, 400,
		NULL,
		NULL,
		hInstance,
		NULL);
	
	if (hWnd == NULL)
		return FALSE;
	
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
	
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND    hWnd,
	UINT    message,
	WPARAM  wParam,
	LPARAM  lParam)
{
	static HGLRC hRC;               
	static HDC hDC;                 

	switch (message)
	{
		
	case WM_CREATE:
		
		hDC = GetDC(hWnd);
		
		SetDCPixelFormat(hDC);
		
		hPalette = GetOpenGLPalette(hDC);
		
		hRC = wglCreateContext(hDC);
		wglMakeCurrent(hDC, hRC);
		SetupRC();
		glGenTextures(2, &texture[0]);                  

		
		bitmapData = LoadBitmapFile("Bitmapy\\checker.bmp", &bitmapInfoHeader);
		glBindTexture(GL_TEXTURE_2D, texture[0]);       

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmapInfoHeader.biWidth,
			bitmapInfoHeader.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmapData);
		if (bitmapData)
			free(bitmapData);
		
		bitmapData = LoadBitmapFile("Bitmapy\\crate.bmp", &bitmapInfoHeader);
		glBindTexture(GL_TEXTURE_2D, texture[1]);       

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmapInfoHeader.biWidth,
			bitmapInfoHeader.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmapData);
		if (bitmapData)
			free(bitmapData);
		
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		break;
		
	case WM_DESTROY:
		
		wglMakeCurrent(hDC, NULL);
		wglDeleteContext(hRC);
		
		if (hPalette != NULL)
			DeleteObject(hPalette);
		
		
		PostQuitMessage(0);
		break;
		
	case WM_SIZE:
		
		
		ChangeSize(LOWORD(lParam), HIWORD(lParam));
		break;
		
		
	case WM_PAINT:
	{
		
		RenderScene();
		SwapBuffers(hDC);
		
		ValidateRect(hWnd, NULL);
	}
	break;
	
	
	
	case WM_QUERYNEWPALETTE:
		
		if (hPalette)
		{
			int nRet;
			
			SelectPalette(hDC, hPalette, FALSE);
			
			
			
			nRet = RealizePalette(hDC);
			
			InvalidateRect(hWnd, NULL, FALSE);
			return nRet;
		}
		break;
		
		
	case WM_PALETTECHANGED:
		
		
		if ((hPalette != NULL) && ((HWND)wParam != hWnd))
		{
			
			SelectPalette(hDC, hPalette, FALSE);
			
			RealizePalette(hDC);
			
			UpdateColors(hDC);
			return 0;
		}
		break;
		
	case WM_KEYDOWN:
	{
		if (wParam == VK_UP)
			xRot -= 5.0f;
		if (wParam == VK_DOWN)
			xRot += 5.0f;
		if (wParam == VK_LEFT)
			yRot -= 5.0f;
		if (wParam == VK_RIGHT)
			yRot += 5.0f;
		xRot = (const int)xRot % 360;
		yRot = (const int)yRot % 360;
		InvalidateRect(hWnd, NULL, FALSE);
	}
	break;
	
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
			
		case ID_FILE_EXIT:
			DestroyWindow(hWnd);
			break;
			
		case ID_HELP_ABOUT:
			DialogBox(hInstance,
				MAKEINTRESOURCE(IDD_DIALOG_ABOUT),
				hWnd,
				DLGPROC(AboutDlgProc));
			break;
		}
	}
	break;
	default:   
		return (DefWindowProc(hWnd, message, wParam, lParam));
	}
	return (0L);
}

BOOL APIENTRY AboutDlgProc(HWND hDlg, UINT message, UINT wParam, LONG lParam)
{
	switch (message)
	{
		
	case WM_INITDIALOG:
	{
		int i;
		GLenum glError;
		
		SetDlgItemText(hDlg, IDC_OPENGL_VENDOR, LPCSTR(glGetString(GL_VENDOR)));
		SetDlgItemText(hDlg, IDC_OPENGL_RENDERER, LPCSTR(glGetString(GL_RENDERER)));
		SetDlgItemText(hDlg, IDC_OPENGL_VERSION, LPCSTR(glGetString(GL_VERSION)));
		SetDlgItemText(hDlg, IDC_OPENGL_EXTENSIONS, LPCSTR(glGetString(GL_EXTENSIONS)));
		
		SetDlgItemText(hDlg, IDC_GLU_VERSION, LPCSTR(gluGetString(GLU_VERSION)));
		SetDlgItemText(hDlg, IDC_GLU_EXTENSIONS, LPCSTR(gluGetString(GLU_EXTENSIONS)));
		
		i = 0;
		do {
			glError = glGetError();
			SetDlgItemText(hDlg, IDC_ERROR1 + i, LPCSTR(gluErrorString(glError)));
			i++;
		} while (i < 6 && glError != GL_NO_ERROR);
		return (TRUE);
	}
	break;
	
	case WM_COMMAND:
	{
		
		if (LOWORD(wParam) == IDOK)
			EndDialog(hDlg, TRUE);
	}
	break;
	
	case WM_CLOSE:
		EndDialog(hDlg, TRUE);
		break;
	}
	return FALSE;
}
