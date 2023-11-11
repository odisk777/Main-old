// Main.cpp: define el punto de entrada de la aplicación.
//

#include "stdafx.h"
#include "AutoUpdate.h"
#include "TextManager.h"
#include "OpenGL.h"
#include "GameState.h"
#include "Util.h"
#include "Main.h"

HWND g_pnpGL;
HINSTANCE g_hWnd;								// Instancia actual
TCHAR szTitle[MAX_LOADSTRING];					// Texto de la barra de título
TCHAR szWindowClass[MAX_LOADSTRING];			// nombre de clase de la ventana principal

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);	//necesario??
	LoadString(hInstance, IDC_MAIN, szWindowClass, MAX_LOADSTRING);	//necesario??

	OpenTextData();

	if(UpdateMuExe() == false)
	{
		return 0;
	}

	/*	NO ES NECESARIO...
	char aAddres[256];

	WORD aPort = -1;

	if (GetCommandLineIPAndPort(lpCmdLine, (char*)&aAddres, &aPort))
	{
		szServerIpAddress = (char*)&aAddres;
		g_ServerPort = aPort;
	}

	*/

	//-- Launcher System
	//if (strlen(lpCmdLine) < 1)	// #Error - no se ejecuta el launcher, el codigo esta bien! (Original pasa lo mismo)
	//{
	//	WinExec("mu.exe", SW_SHOW);
	//
	//	return 0;
	//}
	//--

	HWND FindClientInstance = FindWindow("Dialog", "Mu");

	if (FindClientInstance != NULL)
	{
		SendMessage(FindClientInstance, WM_ENDSESSION, 0, 0);
	}

	/*	esto que he?
	  v21 = 0;
      v20 = dword_54CA4F4;
	 */

	if (OpenMainExe() == 0)
	{
		return 0;
	}

	/*
	*		no es necesario.
	CSimpleModulus::LoadEncryptionKey((DWORD)"Data\\Enc1.dat");
	CSimpleModulus::LoadDecryptionKey((DWORD)"Data\\Dec2.dat");

	*/

	if (OpenInitFile() == 0)
	{
		return 0;
	}

	//---

	#if(DISABLE_WINDOWS_CODE_INCOMPLETE == 1)

	//	- esto cambia el size de todas las ventanas que tenemos fuera , por el momento genera error asique no lo activemos que necesitmaos mas codigo
	if (g_bUseWindowMode == 1) //#Test_Val
	{
		DEVMODEA DevMode;

		int iModeNum = 0;

		for (iModeNum = 0; EnumDisplaySettings(0, iModeNum, &DevMode); iModeNum++);

		DEVMODEA* pAllocModeNum = (DEVMODEA*)operator new(sizeof(DEVMODEA) * (iModeNum + 1));

		for (iModeNum = 0; EnumDisplaySettings(0, iModeNum, &pAllocModeNum[iModeNum]); iModeNum++);

		for (int i = 0; i < iModeNum; i++)
		{
			if (pAllocModeNum[i].dmPelsWidth == WindowWidth && pAllocModeNum[i].dmPelsHeight == WindowHeight && pAllocModeNum[i].dmBitsPerPel == 16)
			{
				ChangeDisplaySettings(&pAllocModeNum[i], 0);
				break;
			}
		}
	}

	#endif
	
	//---

	MyRegisterClass(hInstance);

	if (InitInstance(hInstance, nCmdShow) == 0)
	{
		return FALSE;
	}

	CreateOpenglWindow();

	//--
	
	switch (WindowWidth)
	{
		case 1024:
			FontHeight = 14;
			break;
		case 640:
			FontHeight = 12;
			break;
		case 800:
			FontHeight = 13;
			break;
		case 1280:
			FontHeight = 15;
			break;
	}

	int cHeight = FontHeight - 1;

	char* pszFaceName = strlen(gTextManager.GetText(0)) > 0 ? gTextManager.GetText(0) : 0;

	g_hFont = CreateFont(cHeight, 0, 0, 0, 400, 0, 0, 0, GB2312_CHARSET, 0, 0, 0, 0, pszFaceName);

	g_hFontBold = CreateFont(cHeight, 0, 0, 0, 700, 0, 0, 0, GB2312_CHARSET, 0, 0, 0, 0, pszFaceName);

	g_hFontBig = CreateFont(cHeight * 2, 0, 0, 0, 700, 0, 0, 0, GB2312_CHARSET, 0, 0, 0, 0, pszFaceName);

	//--

	setlocale(LC_ALL, "");

	if (m_SoundOnOff == 1)
	{
		//AudioCreate(g_pnpGL);	//wzAudioCreate | cargamos la lib??
	}

	SetTimer(g_pnpGL, 1000/*Need Define.. */, 20000, 0);

	srand(time(0));

	for (int i = 0; i < MAX_RANDOM_TABLE; i++)
	{
		RandomTable[i] = rand() % 360;
	}


	/*RendomMemoryDump = operator new(rand() % 100 + 1);

	GateAttribute = operator new(0x384u);

	SkillAttribute = operator new(0x900u);

	SkillAttribute_Copy = operator new(0x900u);

	ItemAttribute = operator new(0x3700u);

	ItemAttribute_Copy = operator new(0x3700u);

	g_pCharacterManager = (int)operator new(240800u);

	CharacterMachine = operator new(0x570u);

	memset(GateAttribute, 0, 0x384u);

	memset(SkillAttribute, 0, 0x900u);

	memset(SkillAttribute_Copy, 0, 0x900u);

	memset(ItemAttribute, 0, 0x3700u);

	memset(ItemAttribute_Copy, 0, 0x3700u);

	memset((void*)g_pCharacterManager, 0, 0x3ACA0u);

	memset(CharacterMachine, 0, 0x570u);

	CharacterAttribute = (int)CharacterMachine;

	CHARACTER_MACHINE::Init((CHARACTER_MACHINE*)CharacterMachine);

	Hero = (DWORD*)g_pCharacterManager;*/

	DWORD pvParam;

	SystemParametersInfo(SPI_SETSCREENSAVERRUNNING, 1, &pvParam, 0);

	RegisterHotKey(g_pnpGL, 0, MOD_ALT, VK_TAB);

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MAIN));

	MSG msg;

	int Result = 0;

	while (true)
	{
		while (true)
		{
			int aPoint = 0;

			if (PeekMessageA(&msg, 0, 0, 0, 0))
			{
				break;
			}

			g_iNoMouseTime++;

			if (g_iNoMouseTime > 30)
			{
				g_iInactiveTime++;

				if (g_iInactiveTime > 30)
				{
					g_iNoMouseTime = 0;
					SetTimer(g_pnpGL, 1001/*Need Define*/, 1000, 0);
				}
				
				POINT point[MAX_WINDOWS_FROM_POINT_CHECK] = { {0,0},{301,399},{629,1},{599,423} };

				int tPoint = 0;

				bool IsResetValues = true;
			
				while (g_pnpGL != WindowFromPoint(point[tPoint]))
				{
					aPoint++;

					tPoint++;

					if (aPoint >= MAX_WINDOWS_FROM_POINT_CHECK)
					{
						IsResetValues = false;
						break;
					}
				}

				if (IsResetValues == true)
				{
					g_iNoMouseTime = 0;
					g_iInactiveTime = 0;
				}
			}

			if (g_bWndActive == true)
			{
				Scene(g_hInst);

				//ProtocolCore();
			}
			else
			{	//genera problemas si no se tiene el wndactive puesto! - creo que esto  no habria que ponerlo, solo el protocolcore, ya que nos jode los estados de la ventana
				
				#if(DISABLE_WINDOWS_CODE_INCOMPLETE == 1)

				ShowWindow(g_pnpGL, SW_MINIMIZE);

				ShowWindow(g_pnpGL, SW_MAXIMIZE);

				#endif

				//ProtocolCore();
			}
		}

		if (GetMessage(&msg, 0, 0, 0) == 0)
		{
			break;
		}

		TranslateMessage(&msg);

		if (msg.message != 260/*Need Define?*/ && msg.message != 261/*Need Define?*/)
		{
			DispatchMessage(&msg);
			//ProtocolCore();
		}

		/*while (GetMessage(&msg, NULL, 0, 0))
		{
			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}*/

		//sub_403940(); Destroyd Pointers

		Result = (int)msg.wParam;
	}

	return Result;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MAIN));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground  = (HBRUSH)GetStockObject(BLACK_BRUSH);	//(HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MAIN);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   g_hWnd = hInstance;

   g_pnpGL = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, WindowWidth, WindowHeight, 0, 0, hInstance, NULL);

   if (g_pnpGL == NULL)
   {
      return FALSE;
   }

   ShowWindow(g_pnpGL, nCmdShow);

   UpdateWindow(g_pnpGL);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(g_hWnd, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_ACTIVATE:
		if (wParam == WA_INACTIVE)
		{
			g_bWndActive = false;

			//verificar si es necesario...

			//return DefWindowProc(hWnd, WM_ACTIVATE, wParam, lParam);	//porque lo vielve a enviar??
		}
		else
		{
			g_bWndActive = true;
		}
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
