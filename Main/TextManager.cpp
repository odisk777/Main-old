#include "stdafx.h"
#include "Main.h"
#include "Util.h"
#include "TextManager.h"

/*
    Decompile By:YolaxD
    Date:10/03/2021
    Status:Complete-Mod

*/

CTextManager gTextManager;

CTextManager::CTextManager()
{

}

CTextManager::~CTextManager()
{

}

void CTextManager::Load(char* path)
{
    CHAR Text[256]; 

    FILE* pFile = fopen(path, "rb");

    if (pFile == NULL)
    {
        sprintf(Text, "%s file not found.", path);

        MessageBox(g_pnpGL, Text, 0, 0);
        
        SendMessage(g_pnpGL, WM_DESTROY, 0, 0);
    }

    size_t TotalSize = MAX_TEXT * MAX_TEXT_LEN;

    BYTE* pAlloc = (BYTE*)operator new(TotalSize);

    fread(pAlloc, TotalSize, 1, pFile);

    BuxConvert((BYTE*)pAlloc, TotalSize);

    int size = 0;

    for (size_t i = 0; i < MAX_TEXT; i++)
    {
        char Text[300];

        memcpy(Text, &pAlloc[size],sizeof(Text));

        this->m_GameText.push_back(Text);

        size += MAX_TEXT_LEN;
    }

    operator delete(pAlloc);
       
    fclose(pFile);
}

char* CTextManager::GetText(int ID)
{
    if (this->m_GameText.size() < ID)
    {
        char Buffer[256];

        wsprintf(Buffer, "Text ID Overflow :%d", ID);

        return Buffer;
    }

    return (char*)this->m_GameText.at(ID).c_str();
}