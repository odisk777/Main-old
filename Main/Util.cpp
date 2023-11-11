#include "stdafx.h"
#include "TextManager.h"
#include "Macro.h"
#include "Util.h"

HANDLE g_hMainExe;
char m_Version[11];
char m_ID[12];
int m_SoundOnOff = 1;
int m_MusicOnOff = 0;
int m_Resolution = 0;
int WindowWidth = 1024;
int WindowHeight = 768;
int FontHeight;
HFONT g_hFont;
HFONT g_hFontBold;
HFONT g_hFontBig;
int RandomTable[MAX_RANDOM_TABLE];
int g_iNoMouseTime;
int g_iInactiveTime;
bool g_bWndActive = false;
HDC g_hInst;
HGLRC g_hRC;
bool g_bUseWindowMode = true;
BYTE LoadDataType = 1;
char* Language = "english";
int GlobalBitMapSize = 0;
GLuint CachTexture = -1;
// WORK
DWORD TimeCurrent = 40;
BYTE Destroy;
bool GrabEnable;
int ChatTime;
int MacroTime;
int WaterTextureNumber;
int MoveSceneFrame;
bool InitLogIn;
int CurrentProtocolState;
bool EnableSocket;
//-- FOG
BYTE FogEnable;

//CAMERA
BYTE CameraTopViewEnable;
vec3_t CameraPosition;
vec3_t CameraAngle;
vec34_t CameraMatrix;
float CameraViewFar = 2000.0f;
float CameraViewNear = 20.0f;
float CameraFOV = 55.0f;
GLfloat FogDensity = 0.0004f;
GLfloat FogColor[4] = { 0.1171875f, 0.078125f, 0.0390625f, 0.0f };
//OPENGL
GLint OpenglWindowX;
GLint OpenglWindowY;
GLint OpenglWindowWidth;
GLint OpenglWindowHeight;
//SCREEN
int ScreenCenterYFlip;
int ScreenCenterX;
int ScreenCenterY;
int PerspectiveX;
int PerspectiveY;
//--
BYTE AlphaTestEnable;
BYTE TextureEnable;
BYTE DepthTestEnable;
BYTE CullFaceEnable;
BYTE DepthMaskEnable;
BYTE byte_81C1648 = 0;
//ServerList
BYTE ServerListCount;

void OpenTextData()
{
    if (LoadDataType == 1)
    {
        gTextManager.Load("Data\\Text.bmd");

        gMacro.Load("Data\\Macro.txt");

        return;
    }

   /* char buffer[256];

    sprintf(buffer, "Data2\\Text(%s).txt", Language);

    sub_4248E0(buffer);

    sprintf(buffer, "Data\\Text.bmd", Language);

    sub_424A70((FILE*)buffer);*/
}

bool OpenMainExe()
{
    char FileName[256];

    GetFileNameOfFilePath(FileName, GetCommandLine());

    g_hMainExe = CreateFile(FileName, GENERIC_READ, 3u, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    return (char*)g_hMainExe + 1 != 0;   // hFile == INVALID_HANDLE_VALUE ???
}

bool OpenInitFile()
{
    char FileName[276]; 

    memset(FileName, 0, sizeof(FileName));

    char Buffer[256];

    GetCurrentDirectory(sizeof(Buffer), Buffer);

    strcpy(FileName, Buffer);

    const char* pFileDir = "config.ini";

    if (FileName[strlen(Buffer) + 275] != '\\')
    {
        pFileDir = "\\config.ini";
    }

    strcat(FileName, pFileDir);

    GetPrivateProfileString("LOGIN", "Version", "", m_Version, sizeof(m_Version), FileName);

    m_ID[0] = 0;

    m_SoundOnOff = 1;

    m_MusicOnOff = 0;

    m_Resolution = 0;

    HKEY phkResult;

    DWORD dwDisposition;
  
    if (RegCreateKeyEx(HKEY_CURRENT_USER, "SOFTWARE\\Webzen\\Mu\\Config", 0, 0, 0, KEY_ALL_ACCESS, 0, &phkResult, &dwDisposition) == 0)
    {
        DWORD cbData = 11;
        RegQueryValueEx(phkResult, "ID", 0, 0, (BYTE*)&m_ID, &cbData);
        cbData = 4;
        RegQueryValueEx(phkResult, "SoundOnOff", 0, 0, (BYTE*)&m_SoundOnOff, &cbData);
        cbData = 4;
        RegQueryValueEx(phkResult, "MusicOnOff", 0, 0, (BYTE*)&m_MusicOnOff, &cbData);
        cbData = 4;
        RegQueryValueEx(phkResult, "Resolution", 0, 0, (BYTE*)&m_Resolution, &cbData);
    }

    switch (m_Resolution)
    {
        case 0:
            WindowWidth = 640;
            WindowHeight = 480;
            break;
        case 1:
            WindowWidth = 800;
            WindowHeight = 600;
            break;
        case 2:
            WindowWidth = 1024;
            WindowHeight = 768;
            break;
        case 3:
            WindowWidth = 1280;
            WindowHeight = 1024;
            break;
        case 4:
            WindowWidth = 1600;
            WindowHeight = 1200;
            break;
        default:
            break;
    }

    return true;
}

void GetFileNameOfFilePath(char* buffer1, char* buffer2)
{
    char* v2 = buffer2;

    char* i;

    for (i = buffer2; v2; v2 = strchr(v2 + 1, '\\'))
    {
        i = v2;
    }

    if (strchr(buffer2, '\\') != NULL)
    {
        i++;
    }

    char* Key = strcpy(buffer1, i);

    DWORD End = 1;

    do
    {
        switch (*Key)
        {
            case ' ':
            case '"':
            case '/':
            case '\\':
                *Key = 0;
                goto LABEL_8;
            case '\0':
            LABEL_8:
                End = 0;
                break;
            default:
                break;
        }

        Key++;

    } while (End);
}

void BuxConvert(BYTE* buffer, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        buffer[i] ^= BUX_CONVERT_KEY[i % 3];
    }
}

int ClearPathExtension(char* path, char* PathClear)
{
    int path_size = 0;

    for (int i = 0; i < strlen(path); i++)
    {
        PathClear[i] = path[i];

        if (path[i] != '.')
        {
            continue;
        }

        path_size = i;

        break;
    }

    return path_size;
}

float ConvertX(float posX)
{
    return WindowWidth * posX * 0.0015625f;
}

float ConvertY(float posY)
{
    return WindowHeight * posY * 0.00208333f;
}

void DebugMessageBox(char* message, ...)
{
    char buff[256];

    memset(buff, 0, sizeof(buff));

    va_list arg;
    va_start(arg, message);
    vsprintf_s(buff, message, arg);
    va_end(arg);

    MessageBox(0, buff, "DEBUG_INFO", MB_OK | MB_ICONERROR);

}