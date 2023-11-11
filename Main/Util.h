#pragma once
#include "OpenGL.h"

#define MAX_RANDOM_TABLE 100

#define MAX_WINDOWS_FROM_POINT_CHECK 4

static BYTE BUX_CONVERT_KEY[] = { 0xFC ,0xCF ,0xAB };

void OpenTextData();
bool OpenMainExe();
bool OpenInitFile();
void GetFileNameOfFilePath(char* buffer1, char* buffer2);
void BuxConvert(BYTE* buffer, size_t size);
int ClearPathExtension(char* path, char* PathClear);
float ConvertX(float posX);
float ConvertY(float posY);
void DebugMessageBox(char* message, ...);


extern HANDLE g_hMainExe;
extern int WindowWidth;
extern int WindowHeight;
extern int FontHeight;
extern int m_SoundOnOff;
extern int m_MusicOnOff;
extern int m_Resolution;
extern HFONT g_hFont;
extern HFONT g_hFontBold;
extern HFONT g_hFontBig;
extern int RandomTable[MAX_RANDOM_TABLE];
extern int g_iNoMouseTime;
extern int g_iInactiveTime;
extern bool g_bWndActive;
extern HDC g_hInst;
extern HGLRC g_hRC;
extern bool g_bUseWindowMode;
extern BYTE LoadDataType;
extern char* Language;
extern int GlobalBitMapSize;
extern GLuint CachTexture;
extern DWORD TimeCurrent;
extern BYTE Destroy;
extern bool GrabEnable;
extern int ChatTime;
extern int MacroTime;
extern int WaterTextureNumber;
extern int MoveSceneFrame;
extern bool InitLogIn;
extern int CurrentProtocolState;
extern bool EnableSocket;


extern BYTE FogEnable;
extern BYTE CameraTopViewEnable;
extern vec3_t CameraPosition;
extern vec3_t CameraAngle;
extern vec34_t CameraMatrix;
extern float CameraViewFar;
extern float CameraFOV;
extern float CameraViewNear;
extern GLfloat FogDensity;
extern GLfloat FogColor[4];

extern GLint OpenglWindowX;
extern GLint OpenglWindowY;
extern GLint OpenglWindowWidth;
extern GLint OpenglWindowHeight;

extern int ScreenCenterYFlip;
extern int ScreenCenterX;
extern int ScreenCenterY;
extern int PerspectiveX;
extern int PerspectiveY;

extern BYTE AlphaTestEnable;
extern BYTE TextureEnable;
extern BYTE DepthTestEnable;
extern BYTE CullFaceEnable;
extern BYTE DepthMaskEnable;

extern BYTE byte_81C1648;


extern BYTE ServerListCount;