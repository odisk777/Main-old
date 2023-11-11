#pragma once

bool CreateOpenglWindow();
void KillGLWindow();
void BindTexture(GLuint texture);
void BeginOpengl(int aPosX, int aPosY, int aWidth, int aHeight);
void GetOpenGLMatrix(vec34_t cMatrix);
void glViewport2(GLint x, int y, GLsizei width, GLsizei height);
void gluPerspective2(float fovy, float aspect, float zNear, float zFar);
void DisableDepthTest();
void BeginBitmap();

void pGLPopMatrix();

void pGLMatrixExit();

extern HDC glHdc;