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
#include <gl/gl.h>
#include <gl/glu.h>
#include <cstdio>
#include "resource.h"
#include "szescian/Renderer.h"
#include "szescian/InputHandler.h"
#include "szescian/MyScene.h"
#include <iostream>
#include <chrono>

#define glRGB(x, y, z)	glColor3ub((GLubyte)x, (GLubyte)y, (GLubyte)z)
#define BITMAP_ID 0x4D42
#define GL_PI 3.14

HPALETTE hPalette = nullptr;

static LPCTSTR lpszAppName = "GL Template";
static HINSTANCE hInstance;

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
static GLsizei lastHeight;
static GLsizei lastWidth;

BITMAPINFOHEADER bitmapInfoHeader;
unsigned char* bitmapData;
unsigned int texture[2];

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL APIENTRY AboutDlgProc(HWND hDlg, UINT message, UINT wParam, LONG lParam);

Renderer* renderer = new Renderer();
IScene* scene = new MyScene();
InputHandler* inputHandler = InputHandler::GetInstance();

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;
	WNDCLASS wc;

	hInstance = hInst;

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = nullptr;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);

	wc.hbrBackground = nullptr;
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU);
	wc.lpszClassName = lpszAppName;

	if (RegisterClass(&wc) == 0)
		return FALSE;

	HWND hWnd = CreateWindow(lpszAppName, lpszAppName, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, 50,
		50, 1280, 720, NULL, NULL, hInstance, NULL);

	if (hWnd == nullptr)
		return FALSE;
	ShowWindow(hWnd, SW_SHOW);

		UpdateWindow(hWnd);
	
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
clock_t c1 = clock(), c2 = clock();
double lastframetime;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HGLRC hRC;
	static HDC hDC;

	inputHandler->Update();

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
		
		scene->Init();
		glClear(GL_ACCUM_BUFFER_BIT);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		break;

	case WM_DESTROY:
		wglMakeCurrent(hDC, nullptr);
		wglDeleteContext(hRC);
		if (hPalette != nullptr)
			DeleteObject(hPalette);
		PostQuitMessage(0);
		break;

	case WM_SIZE:
		renderer->ChangeSize(LOWORD(lParam), HIWORD(lParam));
		break;

	case WM_PAINT:
		c1 = clock();
		
		scene->Update(lastframetime);
		scene->UpdateAllGeometries(lastframetime);
		scene->RenderScene();

		scene->UpdatePhysics();
		//glAccum(GL_ACCUM, 1.0);
		//glAccum(GL_RETURN,1.0);
		//glAccum(GL_MULT, 0.4);
		SwapBuffers(hDC);

		//glDrawBuffer(GL_FRONT);

		ValidateRect(hWnd, nullptr);
		InvalidateRect(hWnd, nullptr, NULL);
		
		c2 = clock();
		lastframetime = double(c2 - c1) / CLOCKS_PER_SEC;
		break;


	case WM_QUERYNEWPALETTE:
		if (hPalette)
		{
			SelectPalette(hDC, hPalette, FALSE);
			const int nRet = RealizePalette(hDC);
			InvalidateRect(hWnd, nullptr, FALSE);
			return nRet;
		}
		break;


	case WM_PALETTECHANGED:


		if (hPalette != nullptr && (HWND)wParam != hWnd)
		{
			SelectPalette(hDC, hPalette, FALSE);
			RealizePalette(hDC);
			UpdateColors(hDC);
			return 0;
		}
		break;

	case WM_KEYDOWN:
	{
		InvalidateRect(hWnd, nullptr, FALSE);
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
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0L;
}

BOOL APIENTRY AboutDlgProc(HWND hDlg, UINT message, UINT wParam, LONG lParam)
{
	int i;
	switch (message)
	{
	case WM_INITDIALOG:
		GLenum glError;

		SetDlgItemText(hDlg, IDC_OPENGL_VENDOR, LPCSTR(glGetString(GL_VENDOR)));
		SetDlgItemText(hDlg, IDC_OPENGL_RENDERER, LPCSTR(glGetString(GL_RENDERER)));
		SetDlgItemText(hDlg, IDC_OPENGL_VERSION, LPCSTR(glGetString(GL_VERSION)));
		SetDlgItemText(hDlg, IDC_OPENGL_EXTENSIONS, LPCSTR(glGetString(GL_EXTENSIONS)));

		SetDlgItemText(hDlg, IDC_GLU_VERSION, LPCSTR(gluGetString(GLU_VERSION)));
		SetDlgItemText(hDlg, IDC_GLU_EXTENSIONS, LPCSTR(gluGetString(GLU_EXTENSIONS)));

		i = 0;
		do
		{
			glError = glGetError();
			SetDlgItemText(hDlg, IDC_ERROR1 + i, LPCSTR(gluErrorString(glError)));
			i++;
		} while (i < 6 && glError != GL_NO_ERROR);
		return true;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
			EndDialog(hDlg, TRUE);
		break;

	case WM_CLOSE:
		EndDialog(hDlg, TRUE);
		break;
	}
	return FALSE;
}
