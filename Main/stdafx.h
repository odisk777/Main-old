// stdafx.h: archivo de inclusión de los archivos de inclusión estándar del sistema
// o archivos de inclusión específicos de un proyecto utilizados frecuentemente,
// pero rara vez modificados
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Excluir material rara vez utilizado de encabezados de Windows
// Archivos de encabezado de Windows:
#include <windows.h>

// Archivos de encabezado en tiempo de ejecución de C
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <vector>
#include <locale.h> 
#include <time.h>
#include <gl\GL.h>
#include <gl/GLU.h>
#include "..\\..\\Util\\libjpeg\\jpeglib.h"
#include <stdlib.h>
//#include <dsound.h>


// TODO: mencionar aquí los encabezados adicionales que el programa necesita

#pragma comment(lib,"Opengl32.lib")
#pragma comment(lib, "glu32.lib")

#if(_DEBUG == 1)
#pragma comment(lib,"..\\..\\Util\\libjpeg\\Debug\\jpeg.lib")
#else
#pragma comment(lib,"..\\..\\Util\\libjpeg\\Release\\jpeg.lib")
#endif

#define DISABLE_WINDOWS_CODE_INCOMPLETE 0

//original data in GAMESERVER -> ZZZMATHLIB.h
typedef float vec3_t[3];
typedef float vec4_t[4];
typedef float vec34_t[3][4];