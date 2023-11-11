#include "stdafx.h"
#include "Main.h"
#include "Util.h"
#include "TextManager.h"
#include "OpenGL.h"

HDC glHdc;

bool CreateOpenglWindow()
{
	PIXELFORMATDESCRIPTOR ppfd;

	memset(&ppfd, 0, sizeof(ppfd));

	ppfd.iPixelType = PFD_TYPE_RGBA;

	ppfd.cColorBits = 16;

	ppfd.cDepthBits = 16;

	ppfd.nSize = 40;

	ppfd.nVersion = 1;

	ppfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

	g_hInst = GetDC(g_pnpGL);

	if (g_hInst == NULL)
	{
		KillGLWindow();

		MessageBox(0, gTextManager.GetText(4), "OpenGL Get DC Error.", 0x30u);

		return false;
	}

	int format = ChoosePixelFormat(g_hInst, &ppfd);

	if (format == 0)	//ERROR
	{
		KillGLWindow();

		MessageBox(0, gTextManager.GetText(4), "OpenGL Choose Pixel Format Error.", 0x30u);

		return false;
	}

	if (SetPixelFormat(g_hInst, format, &ppfd) == 0)
	{
		KillGLWindow();

		MessageBox(0, gTextManager.GetText(4), "OpenGL Set Pixel Format Error.", 0x30u);

		return false;
	}

	g_hRC = wglCreateContext(g_hInst);

	if (g_hRC == NULL)
	{
		KillGLWindow();

		MessageBox(0, gTextManager.GetText(4), "OpenGL Create Context Error.", 0x30u);

		return false;
	}

	if (wglMakeCurrent(g_hInst, g_hRC) == 0)
	{
		KillGLWindow();

		MessageBox(0, gTextManager.GetText(4), "OpenGL Make Current Error.", 0x30u);

		return false;
	}

	ShowWindow(g_pnpGL, SW_SHOW);

	SetForegroundWindow(g_pnpGL);

	SetFocus(g_pnpGL);

	return true;
}

void KillGLWindow()
{
	if (g_hRC != NULL)
	{
		if (wglMakeCurrent(0, 0) == 0)
		{
			MessageBox(0, "Release Of DC And RC Failed.", "Error", 0x40u);
		}

		if (wglDeleteContext(g_hRC) == 0)
		{
			MessageBox(0, "Release Rendering Context Failed.", "Error", 0x40u);
		}

		g_hRC = NULL;
	}

	DeleteDC(glHdc);

	if (g_hInst != NULL && ReleaseDC(g_pnpGL, g_hInst) == 0)
	{
		MessageBox(0, "OpenGL Release Error.", "Error", 0x40u);

		g_hInst = NULL;
	}

	if (g_bUseWindowMode == true)
	{
		ChangeDisplaySettings(0, 0);

		ShowCursor(1);
	}
}

void BindTexture(GLuint texture)
{
	if (CachTexture == texture)
	{
		return;
	}
		
	CachTexture = texture;

	glBindTexture(GL_TEXTURE_2D, texture);
}

void BeginOpengl(int aPosX, int aPosY, int aWidth, int aHeight)
{
	int PosX = aPosX * WindowWidth / 640;

	int PosY = aPosY * WindowHeight / 480;

	int Width = aWidth * WindowWidth / 640;

	int Height = aHeight * WindowHeight / 480;

	glMatrixMode(GL_PROJECTION);

	glPushMatrix();

	glLoadIdentity();

	glViewport2(PosX, PosY, Width, Height);

	gluPerspective2(CameraFOV, (float)(Width / Height), CameraViewNear, (CameraViewFar * 1.4f));

	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();

	glLoadIdentity();

	glRotatef(CameraAngle[1], 0.0f, 1.0f, 0.0f);

	if (CameraTopViewEnable == 0)
	{
		glRotatef(CameraAngle[0], 1.0f, 0.0f, 0.0f);
	}

	glRotatef(CameraAngle[2], 0.0f, 0.0f, 1.0f);

	glTranslatef(-CameraPosition[0], -CameraPosition[1], -CameraPosition[2]);

	glDisable(GL_ALPHA_TEST);

	glEnable(GL_TEXTURE_2D);

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);

	glDepthMask(GL_TRUE);

	AlphaTestEnable = 0;

	TextureEnable = 1;

	DepthTestEnable = 1;

	CullFaceEnable = 1;

	DepthMaskEnable = 1;

	glDepthFunc(GL_LEQUAL);	

	glAlphaFunc(GL_GREATER, 0.25f);	

	if (FogEnable != 0)
	{
		glEnable(GL_FOG);

		glFogi(GL_FOG_MODE, GL_EXP2);

		glFogf(GL_FOG_DENSITY, FogDensity);

		glFogfv(GL_FOG_COLOR, FogColor);
	}
	else
	{
		glDisable(GL_FOG);
	}

	GetOpenGLMatrix(CameraMatrix);
}

void GetOpenGLMatrix(vec34_t cMatrix)
{
	GLfloat params[4][4];

	glGetFloatv(GL_MODELVIEW_MATRIX, (GLfloat*)params);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cMatrix[i][j] = params[i][j];
		}
	}
}

void glViewport2(GLint x, int y, GLsizei width, GLsizei height)
{
	OpenglWindowX = x;

	OpenglWindowY = y;

	OpenglWindowWidth = width;

	OpenglWindowHeight = height;

	glViewport(x, WindowHeight - (height + y), width, height);
}

void gluPerspective2(float fovy, float aspect, float zNear, float zFar)
{
	gluPerspective(fovy, aspect, zNear, zFar);

	ScreenCenterX = OpenglWindowX + OpenglWindowWidth / 2;

	ScreenCenterY = OpenglWindowY + OpenglWindowHeight / 2;

	ScreenCenterYFlip = WindowWidth - ScreenCenterY;

	PerspectiveX = (int)(tan(fovy * 0.00872664f) / (OpenglWindowWidth / 2) * aspect);

	PerspectiveY = (int)(WindowHeight / OpenglWindowHeight * (tan(fovy * 0.00872664f) / (OpenglWindowHeight / 2)));
}

void DisableDepthTest()
{
	if (DepthTestEnable == 0)
	{
		return;
	}

	DepthTestEnable = 0;

	glDisable(GL_DEPTH_TEST);
}

void BeginBitmap()
{
	glPushMatrix();

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	glViewport(0, 0, WindowWidth, WindowHeight);

	gluPerspective(CameraFOV, WindowWidth / WindowHeight, CameraViewNear, CameraViewFar);

	glLoadIdentity();

	gluOrtho2D(0.0, WindowWidth, 0.0, WindowHeight);

	glPushMatrix();

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	DisableDepthTest();
}

void pGLPopMatrix()
{
	glPopMatrix();

	glPopMatrix();
}

void pGLMatrixExit()
{
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);

	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
}