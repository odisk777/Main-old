#include "stdafx.h"
#include "TextManager.h"
#include "AutoUpdate.h"

bool UpdateMuExe()
{
    _WIN32_FIND_DATAA FindFileData;

    HANDLE pHandle = FindFirstFile(FindFileName, &FindFileData);

    if (pHandle == (HANDLE)-1)
    {
        return true;
    }

    FindClose(pHandle);

    bool IsFaildGameUpdate = 0;

    BYTE tryCount = 0;

    while (tryCount < MAX_AUTO_UPDATE_TRY)
    {
        HWND pHwnd = FindWindow("Dialog", "Mu");

        if (pHwnd != NULL)
        {
            SendMessage(pHwnd, WM_ENDSESSION, 0, 0);
            Sleep(500);
        }
        else
        {
            IsFaildGameUpdate = TRUE;
        }

        tryCount++;

        if (IsFaildGameUpdate == true)
        {
           break;
        }
    }

    if (IsFaildGameUpdate == false)
    {
        MessageBox(NULL, gTextManager.GetText(13), 0, 0);
        return false;
    }

    MessageBox(NULL, gTextManager.GetText(14), "Update", 0);

    tryCount = 0;

    while (true)
    {
        Sleep(500);

        if (CopyFile(FindFileName, "mu.exe", 0))
        {
            break;
        }

        tryCount++;

        if (tryCount >= MAX_AUTO_UPDATE_TRY)
        {
            MessageBox(0, gTextManager.GetText(13), 0, 0);
            return false;
        }
    }

    if (tryCount < MAX_AUTO_UPDATE_TRY)
    {
        DeleteFile(FindFileName);

        WinExec("mu.exe", 5u);

        return false;
    }
   
    MessageBox(NULL, gTextManager.GetText(13), 0, 0);

    return 0;
}