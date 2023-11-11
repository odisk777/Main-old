#include "stdafx.h"
#include "Util.h"
#include "Main.h"
#include "Texture.h"

CTexture gTexture;

typedef struct my_error_mgr* my_error_ptr;

CTexture::CTexture()
{

}

CTexture::~CTexture()
{

}

void CTexture::Save_Image(size_t TCopySize, char* Format, char* path, BYTE* TextureInfo, size_t TextureSize)
{
    BYTE TextureData[24];

    memcpy(TextureData, TextureInfo, TCopySize);

    char FileName[256];

    FileName[ClearPathExtension(path, FileName) + 1] = 0;

    strcat(FileName, Format);

    char FilePath[256];

    strcpy(FilePath, "Data\\");

    strcat(FilePath, FileName);

    FILE* pFile = fopen(FilePath, "wb");

    if (pFile == NULL)
    {
        return;
    }

    fwrite(TextureData, sizeof(BYTE), TCopySize, pFile);

    fwrite(TextureInfo, sizeof(BYTE), TextureSize, pFile);

    fclose(pFile);
}

void CTexture::UnloadTexture(int Index)
{
    if (TEXTURE_RANGE(Index) == false)
    {
        char BUfferito[256];

        wsprintf(BUfferito, "UnloadTexture (Overflow) Index:[%d/%d]", Index, MAX_TEXTURE);

        MessageBox(g_pnpGL, BUfferito, NULL, MB_OK);

        return;
    }


    if (this->m_Texture[Index].pBitmap == NULL)
    {
        return;
    }

    int BitMapSize = this->m_Texture[Index].width * (this->m_Texture[Index].height * this->m_Texture[Index].BitMapMul);

    operator delete(this->m_Texture[Index].pBitmap);

    this->m_Texture[Index].pBitmap = NULL;

    GlobalBitMapSize -= BitMapSize;
}

int CTexture::FindTexture(char* textureName)
{
    if (TextureInit >= TextureCount)
    {
        return -1;
    }

    size_t i = 0;

    for (i = TextureInit; i < TextureCount; i++)
    {
        TextureInfo* lpTexture = &this->m_Texture[i];

        if (strcmp(textureName, lpTexture->name) != 0)
        {
            continue;
        }

        return i;
    }

    return -1;
}

void CTexture::SetTextureCount(int count)
{
    TextureInit = 0;

    TextureCount = count;
}