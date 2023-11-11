#pragma once

#include "resource.h"

#define MAX_LOADSTRING 100


// Declaraciones de funciones adelantadas incluidas en este módulo de código:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

extern HWND g_pnpGL;

static char szServerIpAddress[] = "192.168.1.37";

static WORD g_ServerPort = 44405;