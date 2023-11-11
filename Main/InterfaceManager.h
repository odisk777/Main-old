#pragma once



class CInterfaceManager
{
public:
	CInterfaceManager();
	~CInterfaceManager();
	bool LoadImageTga(char* patch, GLuint Index, GLint paramFilter, GLint paramWrap, char* ErrorMode, bool IsErrorBox);
	bool LoadImageJpg(char* path, GLuint Index, GLint paramFilter, GLint paramWrap, char* ErrorMode, bool IsErrorBox);
	void RenderBitmap(GLuint Index, float PosX, float PosY, float Width, float Height, int a7, int a8, float a9, float a10, BYTE a11, BYTE a12);
	void AccessModel(int ID, char* path, char* Model, int PathID);
	void OpenTexture(int ID, char* Model, GLint paramFilter, bool IsErrorBox);
private:

};

extern CInterfaceManager gInterfaceManager;