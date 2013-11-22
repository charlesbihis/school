#pragma once

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include <stdio.h>

#define CLASS_NAME "OpenGL"

class CGLWindow{
private:
	HWND	hWnd;
	HDC		hDC;
	HGLRC	hRC;
	bool	fullscreen;
public:
	CGLWindow();
	~CGLWindow();

	bool Initialize(int width, int height,int bpp, bool fullscreen);
	void Terminate();
	void Resize(int width, int height);

	void Swap(){ SwapBuffers(hDC); }

	friend LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};