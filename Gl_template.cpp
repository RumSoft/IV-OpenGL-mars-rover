

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
#include "szescian/Renderer.h"
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

Renderer* renderer = new Renderer();

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

		renderer->SetDCPixelFormat(hDC);

		hPalette = renderer->GetOpenGLPalette(hDC);

		hRC = wglCreateContext(hDC);
		wglMakeCurrent(hDC, hRC);
		renderer->SetupRC();
		glGenTextures(2, &texture[0]);


		bitmapData = renderer->LoadBitmapFile("Bitmapy\\checker.bmp", &bitmapInfoHeader);
		glBindTexture(GL_TEXTURE_2D, texture[0]);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmapInfoHeader.biWidth,
			bitmapInfoHeader.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmapData);
		if (bitmapData)
			free(bitmapData);

		bitmapData = renderer->LoadBitmapFile("Bitmapy\\crate.bmp", &bitmapInfoHeader);
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
		renderer->ChangeSize(LOWORD(lParam), HIWORD(lParam));
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
