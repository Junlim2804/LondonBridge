#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <iostream>
#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "GLU32.lib")

#define WINDOW_TITLE "OpenGL Window"
char s[256];
float x=0, y = 0.0 , z = 0.0;
float dec = 0.0;
float a = 0, b = 0, c = 0.0;
int viewstate = 0;
GLuint texture = 0;
BITMAP BMP;
HBITMAP hBMP = NULL;
LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) PostQuitMessage(0);

		if (wParam == 'A') dec += 1;
		if (wParam == 'S') dec -= 1;
		if (wParam == 'Z') z += 1;
		if (wParam == 'X') x += 1;
		if (wParam == 'C') y += 1;
		if (wParam == VK_UP) b += 0.01;
		if (wParam == VK_DOWN) b -= 0.01;
		if (wParam == VK_RIGHT) a += 0.01;
		if (wParam == VK_LEFT) a -= 0.01;
		if (wParam == VK_PRIOR) c += 0.01;
		if (wParam == VK_NEXT) c -= 0.01;
		if (wParam == 'V') viewstate=1;
		if (wParam == 'B') viewstate = 0;
		sprintf_s(s, "x=%f,y=%f,z=%f\n", a, b,c);
		OutputDebugString(s);
		break;
	

	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//--------------------------------------------------------------------

bool initPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.cAlphaBits = 8;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 0;

	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	// choose pixel format returns the number most similar pixel format available
	int n = ChoosePixelFormat(hdc, &pfd);

	// set pixel format returns whether it sucessfully set the pixel format
	if (SetPixelFormat(hdc, n, &pfd))
	{
		return true;
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------------------------


void decoration(float ymin, float ymax)
{

	glBegin(GL_QUADS);
	glVertex3f(-0.01, ymin, -0.01);
	glVertex3f(-0.01, ymin, 0.51);
	glVertex3f(0.21, ymin, 0.51);
	glVertex3f(0.21, ymin, -0.01);
	glEnd();


	//left
	glBegin(GL_QUADS);
	glVertex3f(-0.01, ymin, -0.01);
	glVertex3f(-0.01, ymax, -0.01);
	glVertex3f(-0.01, ymax, 0.51);
	glVertex3f(-0.01, ymin, 0.51);
	glEnd();

	//top
	glBegin(GL_QUADS);
	glVertex3f(-0.01, ymax, -0.01);
	glVertex3f(-0.01, ymax, 0.51);
	glVertex3f(0.21, ymax, 0.51);
	glVertex3f(0.21, ymax, -0.01);
	glEnd();

	//right
	glBegin(GL_QUADS);
	glVertex3f(0.21, ymax, 0.51);
	glVertex3f(0.21, ymax, -0.01);
	glVertex3f(0.21, ymin, -0.01);
	glVertex3f(0.21, ymin, 0.51);
	glEnd();
	//back
	glBegin(GL_QUADS);

	glVertex3f(0.21, ymax, 0.51);
	glVertex3f(-0.01, ymax, 0.51);
	glVertex3f(-0.01, ymin, 0.51);
	glVertex3f(0.21, ymin, 0.51);
	glEnd();

	//front
	glBegin(GL_QUADS);
	glVertex3f(-0.01, ymin, -0.01);
	glVertex3f(-0.01, ymax, -0.01);
	glVertex3f(0.21, ymax, -0.01);
	glVertex3f(0.21, ymin, -0.01);
	glEnd();
}
void hole()
{
	glBegin(GL_QUADS);
	glTexCoord2d(0.0, 0.0);
	glVertex3f(0.0, -0.45, 0.0);
	glTexCoord2d(0.0, 1.0);
	glVertex3f(0.0, -0.45, 0.1);
	glTexCoord2d(1.0, 1.0);
	glVertex3f(0.2, -0.45, 0.1);
	glTexCoord2d(1.0, 0.0);
	glVertex3f(0.2, -0.45, 0);
	glEnd();


	//left
	glBegin(GL_QUADS);
	glTexCoord2d(0.0, 0.0);
	glVertex3f(0, -0.45, 0);
	glTexCoord2d(1.0, 0.0);
	glVertex3f(0, -0.35, 0);
	glTexCoord2d(1.0, 1.0);
	glVertex3f(0, -0.35, 0.1);
	glTexCoord2d(0.0, 1.0);
	glVertex3f(0, -0.45, 0.1);
	glEnd();

	//top
	glBegin(GL_QUADS);
	glTexCoord2d(0.0, 0.0);
	glVertex3f(0, -0.35, 0);
	glTexCoord2d(0.0, 1.0);
	glVertex3f(0, -0.35, 0.1);
	glTexCoord2d(1.0, 1.0);
	glVertex3f(0.2, -0.35, 0.1);
	glTexCoord2d(1.0, 0.0);
	glVertex3f(0.2, -0.35, 0.0);
	glEnd();

	//right
	glBegin(GL_QUADS);
	glTexCoord2d(0.0, 1.0);
	glVertex3f(0.2, -0.35, 0.1);
	glTexCoord2d(0.0, 0.0);
	glVertex3f(0.2, -0.35, 0.0);
	glTexCoord2d(1.0, 0.0);
	glVertex3f(0.2, -0.45, 0);
	glTexCoord2d(1.0, 1.0);
	glVertex3f(0.2, -0.45, 0.1);
	glEnd();
	//back
	glBegin(GL_QUADS);
	glTexCoord2d(1.0, 1.0);
	glVertex3f(0.2, -0.35, 0.1);
	glTexCoord2d(0.0, 1.0);
	glVertex3f(0, -0.35, 0.1);
	glTexCoord2d(0.0, 0.0);
	glVertex3f(0, -0.45, 0.1);
	glTexCoord2d(1.0, 0.0);
	glVertex3f(0.2, -0.45, 0.1);
	glEnd();

	//front
	glBegin(GL_QUADS);
	glTexCoord2d(0.0, 0.0);
	glVertex3f(0.0, -0.45, 0.0);
	glTexCoord2d(0.0, 1.0);
	glVertex3f(0, -0.35, 0);
	glTexCoord2d(1.0, 1.0);
	glVertex3f(0.2, -0.35, 0.0);
	glTexCoord2d(1.0, 0.0);
	glVertex3f(0.2, -0.45, 0.0);
	glEnd();
}
void smallwindow(float xmin, float ymin)
{
	float ymax = ymin + 0.1;
	float xmax = xmin + 0.03;
	glBegin(GL_QUADS);
	glVertex3f(xmin, ymin, -0.01);
	glVertex3f(xmin, ymin, 0.51);
	glVertex3f(xmax, ymin, 0.51);
	glVertex3f(xmax, ymin, -0.01);
	glEnd();


	//left
	glBegin(GL_QUADS);
	glVertex3f(xmin, ymin, -0.01);
	glVertex3f(xmin, ymax, -0.01);
	glVertex3f(xmin, ymax, 0.51);
	glVertex3f(xmin, ymin, 0.51);
	glEnd();

	//top
	glBegin(GL_QUADS);
	glVertex3f(xmin, ymax, -0.01);
	glVertex3f(xmin, ymax, 0.51);
	glVertex3f(xmax, ymax, 0.51);
	glVertex3f(xmax, ymax, -0.01);
	glEnd();

	//right
	glBegin(GL_QUADS);
	glVertex3f(xmax, ymax, 0.51);
	glVertex3f(xmax, ymax, -0.01);
	glVertex3f(xmax, ymin, -0.01);
	glVertex3f(xmax, ymin, 0.51);
	glEnd();
	//back
	glBegin(GL_QUADS);

	glVertex3f(xmax, ymax, 0.51);
	glVertex3f(xmin, ymax, 0.51);
	glVertex3f(xmin, ymin, 0.51);
	glVertex3f(xmax, ymin, 0.51);
	glEnd();

	//front
	glBegin(GL_QUADS);
	glVertex3f(xmin, ymin, -0.01);
	glVertex3f(xmin, ymax, -0.01);
	glVertex3f(xmax, ymax, -0.01);
	glVertex3f(xmax, ymin, -0.01);
	glEnd();
}
void drawTiang()
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), "wood.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);



	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	


	//glPushMatrix();
	//glTranslatef(0,0.1,0);
	//pyramid on top
	glBegin(GL_QUADS);
	glVertex3f(0.0, 0.85, 0.00);
	glVertex3f(0.0, 0.85, 0.5);
	glVertex3f(0.2, 0.85, 0.5);
	glVertex3f(0.2, 0.85, 0.0);
	glEnd();

	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0,1.0);
	glVertex3f(0.0, 0.85, 0.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.2, 0.85, 0.0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.10, 1.1, 0.25);
	glEnd();

	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0, 0.85, 0.5);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.2, 0.85, 0.5);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.10, 1.1, 0.25);
	glEnd();

	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0, 0.85, 0.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.0, 0.85, 0.5);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.10, 1.1, 0.25);
	glEnd();

	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.2, 0.85, 0.5);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.2, 0.85, 0.5);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.10, 1.1, 0.25);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
	
	//glPopMatrix();


	//main tiang
	//bottom
	glPushMatrix();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	HBITMAP hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), "tiang.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);



	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);
	glTranslatef(0, 0.1, 0);
	//bottom
	glBegin(GL_QUADS);
	glTexCoord2d(0.0, 0.0);
	glVertex3f(0.0, -0.35, 0.0);
	glTexCoord2d(0.0, 1.0);
	glVertex3f(0.0, -0.35, 0.5);
	glTexCoord2d(1.0, 1.0);
	glVertex3f(0.2, -0.35, 0.5);
	glTexCoord2d(1.0, 0.0);
	glVertex3f(0.2, -0.35, 0);
	glEnd();

	//top
	glBegin(GL_QUADS);
	glTexCoord2d(0.0, 0.0);
	glVertex3f(0, 0.75, 0);
	glTexCoord2d(0.0, 1.0);
	glVertex3f(0, 0.75, 0.5);
	glTexCoord2d(1.0, 1.0);
	glVertex3f(0.2, 0.75, 0.5);
	glTexCoord2d(1.0, 0.0);
	glVertex3f(0.2, 0.75, 0.0);
	glEnd();


	//left
	glBegin(GL_QUADS);
	glTexCoord2d(0.0, 0.0);
	glVertex3f(0, -0.35, 0);
	glTexCoord2d(0.0, 1.0);
	glVertex3f(0, 0.75, 0);
	glTexCoord2d(1.0, 1.0);
	glVertex3f(0, 0.75, 0.5);
	glTexCoord2d(1.0, 0.0);
	glVertex3f(0, -0.35,0.5);
	glEnd();

	

	//right
	glBegin(GL_QUADS);
	glTexCoord2d(1.0, 1.0);
	glVertex3f(0.2, 0.75, 0.5);
	glTexCoord2d(0.0, 1.0);
	glVertex3f(0.2, 0.75, 0.0);
	glTexCoord2d(0.0, 0.0);
	glVertex3f(0.2, -0.35, 0);
	glTexCoord2d(1.0, 0.0);
	glVertex3f(0.2, -0.35, 0.5);
	glEnd();
	//back
	glBegin(GL_QUADS);
	glTexCoord2d(1.0, 1.0);
	glVertex3f(0.2, 0.75, 0.5);
	glTexCoord2d(0.0, 1.0);
	glVertex3f(0, 0.75, 0.5);
	glTexCoord2d(0.0, 0.0);
	glVertex3f(0, -0.35, 0.5);
	glTexCoord2d(1.0, 0.0);
	glVertex3f(0.2, -0.35, 0.5);
	glEnd();

	//front
	glBegin(GL_QUADS);
	glTexCoord2d(0.0, 0.0);
	glVertex3f(0.0, -0.35, 0.0);
	glTexCoord2d(0.0, 1.0);
	glVertex3f(0, 0.75, 0);
	glTexCoord2d(1.0, 1.0);
	glVertex3f(0.2, 0.75, 0.0);
	glTexCoord2d(1.0, 0.0);
	glVertex3f(0.2, -0.35, 0.0);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
	//Hole
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), "hole.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);



	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	hole();
	glPushMatrix();
	glTranslatef(0, 0, 0.4);
	hole();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
	//base
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), "base.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);



	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	glBegin(GL_QUADS);
	//front
	glTexCoord2d(1.0, 1.0);
	glVertex3f(0.33, -0.45, 0);
	glTexCoord2d(1.0, 0.0);
	glVertex3f(0.33, -0.75, 0);
	glTexCoord2d(0.0, 0.0);
	glVertex3f(-0.13, -0.75, 0);
	glTexCoord2d(0.0, 1.0);
	glVertex3f(-0.13, -0.45, 0);
	//back
	glTexCoord2d(1.0, 1.0);
	glVertex3f(0.33, -0.45, 0.6);
	glTexCoord2d(1.0, 0.0);
	glVertex3f(0.33, -0.75, 0.6);
	glTexCoord2d(0.0, 0.0);
	glVertex3f(-0.13, -0.75, 0.6);
	glTexCoord2d(0.0, 1.0);
	glVertex3f(-0.13, -0.45, 0.6);
	//top
	glTexCoord2d(1.0, 1.0);
	glVertex3f(0.33, -0.45, 0.6);
	glTexCoord2d(1.0, 0.0);
	glVertex3f(0.33, -0.45, 0.0);
	glTexCoord2d(0.0, 0.0);
	glVertex3f(-0.13, -0.45, 0.0);
	glTexCoord2d(0.0, 1.0);
	glVertex3f(-0.13, -0.45, 0.6);
	glPopMatrix();
	//base
	glTexCoord2d(1.0, 1.0);
	glVertex3f(0.33, -0.75, 0.6);
	glTexCoord2d(1.0, 0.0);
	glVertex3f(0.33, -0.75, 0.0);
	glTexCoord2d(0.0, 0.0);
	glVertex3f(-0.13, -0.75, 0.0);
	glTexCoord2d(0.0, 1.0);
	glVertex3f(-0.13, -0.75, 0.6);

	//left
	glTexCoord2d(0.0, 1.0);
	glVertex3f(-0.13, -0.75, 0.6);
	glTexCoord2d(0.0,0.0);
	glVertex3f(-0.13, -0.75, 0.0);
	glTexCoord2d(1.0, 0.0);
	glVertex3f(-0.13, -0.45, 0.0);
	glTexCoord2d(1.0, 1.0);
	glVertex3f(-0.13, -0.45, 0.6);

	//right
	glTexCoord2d(0.0, 1.0);
	glVertex3f(0.33, -0.75, 0.6);
	glTexCoord2d(0.0, 0.0);
	glVertex3f(0.33, -0.75, 0.0);
	glTexCoord2d(1.0, 0.0);
	glVertex3f(0.33, -0.45, 0.0);
	glTexCoord2d(1.0, 1.0);
	glVertex3f(0.33, -0.45, 0.6);
	
	glEnd();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
	//decoration
	
	//decoration(0, 0.1);
	
	//smallwindow(0.05, 0.15);
	//smallwindow(0.1, 0.15);
	//smallwindow(0.15, 0.15);
	

	//decoration(0.3, 0.4);
	//smallwindow(0.05, 0.45);
	//smallwindow(0.1, 0.45);
	//smallwindow(0.15, 0.45);
	//glColor3f(1, 1, 0);
	//decoration(-0.4, -0.3);
	//smallwindow(0.05, -0.20);
	//smallwindow(0.1, -0.20);
	//smallwindow(0.15, -0.20);
	glPushMatrix();
	glTranslatef(0.21, 0.60, 0.22);
	//glTranslatef(a, b, c);
	glRotatef(90, 0, 1, 0);
	
	float x1 = 0.0, y1 = 0.0, x2 = 0.0, y2 = 0.0;
	float angle = 0.0;
	float radius = 0.15;

	//

	glBegin(GL_TRIANGLE_FAN);
	
	glVertex3f(x1, y1,0.0);

	for (angle = 0.0; angle <= 360.0; angle += 0.2)
	{

		x2 = x1 + cos(angle) * radius;
		y2 = y1 + sin(angle) * radius;
		glVertex3f(x2, y2,0.0);
	}
	glEnd();
	glPushMatrix();
	//glTranslatef(a, b, c);
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex3f(-0.11,0.0,0.001);
	glVertex3f(-0.01,0.0,0.001);

	glVertex3f(-0.01, 0.1, 0.001);
	glVertex3f(-0.01, 0.0, 0.001);
	glEnd();
	glPopMatrix();
	glPopMatrix();
	glColor3f(1, 1, 1);
	
}
void topmiddle()
{
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), "topmiddle.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);



	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	//glRotatef(x, 1, 0, 0);
	//glRotatef(y, 0, 1, 0);
	//glRotatef(z, 0, 0, 1);
	glBegin(GL_QUADS);
	//front
	glTexCoord2d(1.0, 0.0);
	glVertex3f(0.3, 0, 0.1);
	glTexCoord2d(1.0, 1.0);
	glVertex3f(0.3, 0.1, 0.1);
	glTexCoord2d(0.0, 1.0);
	glVertex3f(-0.3, 0.1, 0.1);
	glTexCoord2d(0.0, 0.0);
	glVertex3f(-0.3, 0.0, 0.1);
	glEnd();
	
	//back
	glBegin(GL_QUADS);
	glTexCoord2d(1.0, 0.0);
	glVertex3f(0.3, 0, 0.4);
	glTexCoord2d(1.0, 1.0);
	glVertex3f(0.3, 0.1, 0.4);
	glTexCoord2d(0.0, 1.0);
	glVertex3f(-0.3, 0.1, 0.4);
	glTexCoord2d(0.0, 0.0);
	glVertex3f(-0.3, 0, 0.4);
	glEnd();
	
	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), "wood.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);



	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	//bottom
	glBegin(GL_QUADS);
	glTexCoord2d(0.0, 1.0);
	glVertex3f(-0.3, 0.0, 0.4);
	glTexCoord2d(1.0, 0.0);
	glTexCoord2d(1.0, 0.0);
	glTexCoord2d(1.0, 1.0);
	glVertex3f(0.3, 0.0, 0.4);
	glTexCoord2d(1.0, 0.0);
	glVertex3f(0.3, 0, 0.1);
	glTexCoord2d(0.0, 0.0);
	glVertex3f(-0.3, 0, 0.1);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
	//right
	glBegin(GL_QUADS);
	glVertex3f(0.3, 0, 0.1);
	glVertex3f(0.3, 0.0, 0.4);
	glVertex3f(0.3, 0.1, 0.4);
	glVertex3f(0.3, 0.1, 0.1);
	glEnd();
	//left
	glBegin(GL_QUADS);
	glVertex3f(-0.3, 0, 0.1);
	glVertex3f(-0.3, 0.0, 0.4);
	glVertex3f(-0.3, 0.1, 0.4);
	glVertex3f(-0.3, 0.1, 0.1);
	glEnd();
	//top



	



}
void middle()
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), "middle.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);



	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);
	//glRotatef(x, 1, 0, 0);
	//glRotatef(y, 0, 1, 0);
	//glRotatef(z, 0, 0, 1);
;	glBegin(GL_QUADS);
	//front
	glTexCoord2d(1.0, 0.0);
	glVertex3f(0.3, 0, 0.1);
	glTexCoord2d(1.0, 1.0);
	glVertex3f(0.3, 0.1, 0.1);
	glTexCoord2d(0.0, 1.0);
	glVertex3f(-0.3, 0.1, 0.1);
	glTexCoord2d(0.0, 0.0);
	glVertex3f(-0.3, 0.0, 0.1);
	glEnd();
	
	//bottom
	glBegin(GL_QUADS);
	glTexCoord2d(0.0, 1.0);
	glVertex3f(-0.3, 0.0,0.4);
	glTexCoord2d(1.0, 1.0);
	glVertex3f(0.3, 0.0, 0.4);
	glTexCoord2d(1.0, 0.0);
	glVertex3f(0.3, 0, 0.1);
	glTexCoord2d(0.0, 0.0);
	glVertex3f(-0.3, 0, 0.1);
	glEnd();

	//back
	glBegin(GL_QUADS);
	glTexCoord2d(1.0, 0.0);
	glVertex3f(0.3, 0, 0.4);
	glTexCoord2d(1.0, 1.0);
	glVertex3f(0.3, 0.1, 0.4);
	glTexCoord2d(0.0, 0.0);
	glVertex3f(-0.3, 0.1, 0.4);
	glTexCoord2d(0.0, 1.0);
	glVertex3f(-0.3, 0, 0.4);
	glEnd();
	
	//right
	glBegin(GL_QUADS);
	glTexCoord2d(0.0, 0.0);
	glVertex3f(0.3,0,0.1);
	glTexCoord2d(0.0, 1.0);
	glVertex3f(0.3, 0.0, 0.4);
	glTexCoord2d(1.0, 1.0);
	glVertex3f(0.3, 0.1, 0.4);
	glTexCoord2d(1.0, 0.0);
	glVertex3f(0.3, 0.1, 0.1);
	glEnd();
	//left
	glBegin(GL_QUADS);
	glTexCoord2d(0.0, 0.0);
	glVertex3f(-0.3, 0.0, 0.1);
	glTexCoord2d(0.0, 1.0);
	glVertex3f(-0.3, 0.0, 0.4);
	glTexCoord2d(1.0, 1.0);
	glVertex3f(-0.3, 0.1, 0.4);
	glTexCoord2d(1.0, 0.0);
	glVertex3f(-0.3, 0.1, 0.1);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
	//top
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), "road.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);



	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);
	
	glBegin(GL_QUADS);
	glTexCoord2d(0.0, 1.0);
	glVertex3f(-0.3, 0.1, 0.4);
	glTexCoord2d(1.0, 1.0);
	glVertex3f(0.3, 0.1, 0.4);
	glTexCoord2d(1.0, 0.0);
	glVertex3f(0.3, 0.1, 0.1);
	glTexCoord2d(0.0, 0.0);
	glVertex3f(-0.3, 0.1, 0.1);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
	
	
}
void water()
{

	glBegin(GL_QUADS);
	//front
	glTexCoord2d(1.0, 0.0);
	glVertex3f(2, -0.65, 0);
	glTexCoord2d(1.0, 1.0);
	glVertex3f(2, -1, 0);
	glTexCoord2d(0.0, 1.0);
	glVertex3f(-2, -1, 0);
	glTexCoord2d(0.0, 0.0);
	glVertex3f(-2, -0.65, 0);
	//back
	glTexCoord2d(1.0, 0.0);
	glVertex3f(2, -0.65, 0.6);
	glTexCoord2d(1.0, 1.0);
	glVertex3f(2, -1, 0.6);
	glTexCoord2d(0.0, 1.0);
	glVertex3f(-2, -1, 0.6);
	glTexCoord2d(0.0, 0.0);
	glVertex3f(-2, -0.65, 0.6);
	//top	
	

	glTexCoord2d(1.0, 0.0);
	glVertex3f(2, -0.65, 0.6);
	glTexCoord2d(0.0, 0.0);
	glVertex3f(2, -0.65, 0.0);
	glTexCoord2d(0.0, 1.0);
	glVertex3f(-2, -0.65, 0.0);
	glTexCoord2d(1.0, 1.0);
	glVertex3f(-2, -0.65, 0.6);

	//base
	glTexCoord2d(1.0, 0.0);
	glVertex3f(2, -1, 0.6);
	glTexCoord2d(0.0, 0.0);
	glVertex3f(2, -1, 0.0);
	glTexCoord2d(0.0, 1.0);
	glVertex3f(-2, -1, 0.0);
	glTexCoord2d(1.0, 1.0);
	glVertex3f(-2, -1, 0.6);	
	
	//left
	glTexCoord2d(1.0, 1.0);
	glVertex3f(-2, -1, 0.6);
	glTexCoord2d(1.0, 0.0);
	glVertex3f(-2, -1, 0.0);
	glTexCoord2d(0.0, 0.0);
	glVertex3f(-2, -0.65, 0.0);
	glTexCoord2d(0.0, 1.0);
	glVertex3f(-2, -0.65, 0.6);

	//right
	glTexCoord2d(1.0, 1.0);
	glVertex3f(2, -1, 0.6);
	glTexCoord2d(1.0, 0.0);
	glVertex3f(2, -1, 0.0);
	glTexCoord2d(0.0, 0.0);
	glVertex3f(2, -0.65, 0.0);
	glTexCoord2d(0.0, 1.0);
	glVertex3f(2, -0.65, 0.6);

	glEnd();
}
void display()
{	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.67, 0.84, 0.90, 1);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	
	glLoadIdentity();
	glTranslatef(0, 0, c);
	glRotatef(x, 1, 0, 0);
	glRotatef(y, 0, 1, 0);
	glRotatef(z, 0, 0, 1);
	
	glPushMatrix();
	
	glScalef(1.5, 1.2, 1);
	glTranslatef(0.05, 0.24, 0);
	
	topmiddle();
	glPopMatrix();

	if (dec < 0)
		dec = 0;
	if (dec > 55)
		dec = 55;
	glPushMatrix();
	
	glTranslatef(-0.3, 0, 0);
	//glTranslatef(a, b, c);
	glTranslatef(-0.18, -0.45, 0);
	glRotatef(dec, 0, 0, 1);
	//glTranslatef(0.18, 0.25, 0);
	glTranslatef(0.3, 0, 0);
	

	
	middle();
	
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.3, 0, 0);
	glTranslatef(0.38, -0.45, 0);
	glRotatef(-dec, 0, 0, 1);
	glTranslatef(-0.3, 0, 0);

	middle();
	glPopMatrix();

	glPushMatrix();;
	glTranslatef(0.5, 0, 0);
	drawTiang();
	glPopMatrix();
	glPushMatrix();

	glTranslatef(-0.5, 0, 0);
	
	drawTiang();
	
	glPopMatrix();

	glPushMatrix();
	
	glTranslatef(-0.71, -0.45, 0);

	

	middle();

	glPopMatrix();

	glPushMatrix();
	
	glTranslatef(0.92, -0.45, 0);	

	middle();

	glPopMatrix();
	/*

	*/
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), "concrete.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);



	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);
	glPushMatrix();	
	glTranslatef(-0.92, -0.36, 0.1);
	//glTranslatef(a, b, c);
	//z = 334;
	//glRotatef(x, 1, 0, 0);
	//glRotatef(y, 0, 1, 0);
	glRotatef(334, 0, 0, 1);
	glRotatef(-90, 1, 0, 0);
	GLUquadricObj* cylinder = NULL;
	cylinder = gluNewQuadric();

	
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluCylinder(cylinder, 0.02, 0.02, 1, 50, 50);

	gluDeleteQuadric(cylinder);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.92, -0.36, 0.4);
	//glTranslatef(a, b, c);
	//z = 334;
	//glRotatef(x, 1, 0, 0);
	//glRotatef(y, 0, 1, 0);
	glRotatef(334, 0, 0, 1);
	glRotatef(-90, 1, 0, 0);
	//GLUquadricObj* cylinder = NULL;
	cylinder = gluNewQuadric();


	gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluCylinder(cylinder, 0.02, 0.02, 1, 50, 50);
	gluQuadricTexture(cylinder, true);
	gluDeleteQuadric(cylinder);
	glPopMatrix();

	glPushMatrix();
	//glTranslatef(-0.92, -0.36, 0.4);
	glTranslatef(1.1, -0.39, 0.4);
	//z = 334;
	//glRotatef(x, 1, 0, 0);
	//glRotatef(y, 0, 1, 0);
	glRotatef(-334, 0, 0, 1);
	glRotatef(-90, 1, 0, 0);
	//GLUquadricObj* cylinder = NULL;
	cylinder = gluNewQuadric();


	gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluCylinder(cylinder, 0.02, 0.02, 1, 50, 50);

	gluDeleteQuadric(cylinder);
	glPopMatrix();

	glPushMatrix();
	//glTranslatef(-0.92, -0.36, 0.4);
	glTranslatef(1.1, -0.39, 0.1);
	//z = 334;
	//glRotatef(x, 1, 0, 0);
	//glRotatef(y, 0, 1, 0);
	glRotatef(-334, 0, 0, 1);
	glRotatef(-90, 1, 0, 0);
	//GLUquadricObj* cylinder = NULL;
	cylinder = gluNewQuadric();


	gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluCylinder(cylinder, 0.02, 0.02, 1, 50, 50);

	gluDeleteQuadric(cylinder);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);

	/*
	glPushMatrix();
	
	glTranslatef(0, -0.6, 0);
	glRotatef(90, 1, 0, 0);

	float x1 = 0.0, y1 = 0.0, x2 = 0.0, y2 = 0.0;
	float angle = 0.0;
	float radius = 1;

	*/
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), "water.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);



	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);
	water();
	/*
	glBegin(GL_TRIANGLE_FAN);

	glVertex3f(x1, y1, 0.0);

	for (angle = 0.0; angle <= 360.0; angle += 0.2)
	{

		x2 = x1 + cos(angle) * radius;
		y2 = y1 + sin(angle) * radius;
		glTexCoord2d(x2, y2);
		glVertex3f(x2, y2, 0.0);
	}
	glEnd();
	
	glPopMatrix();*/
	
	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);

	

	

}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = WindowProcedure;
	wc.lpszClassName = WINDOW_TITLE;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wc)) return false;

	HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 1200, 700,
		NULL, NULL, wc.hInstance, NULL);

	//--------------------------------
	//	Initialize window for OpenGL
	//--------------------------------

	HDC hdc = GetDC(hWnd);

	//	initialize pixel format for the window
	initPixelFormat(hdc);

	//	get an openGL context
	HGLRC hglrc = wglCreateContext(hdc);

	//	make context current
	if (!wglMakeCurrent(hdc, hglrc)) return false;

	//--------------------------------
	//	End initialization
	//--------------------------------

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	
	while (true)
	{

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		
		if (viewstate == 0)
		{
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
		}
		else
		{
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			//glScalef(0.5, 0.5, 0.5);
			glTranslatef(0, 0, -1);
			gluPerspective(40, 1.3, 1, 10);
			glFrustum(-2, 2, -2,2,1, 10);
			
			glEnable(GL_DEPTH_TEST);
		}
		display();

		SwapBuffers(hdc);
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
//--------------------------------------------------------------------