#include "stdafx.h"
#include "Main.h"
#include "Util.h"
#include "Texture.h"
#include "OpenGL.h"
#include "BMDManager.h"
#include "InterfaceManager.h"

CInterfaceManager gInterfaceManager;

CInterfaceManager::CInterfaceManager()
{

}

CInterfaceManager::~CInterfaceManager()
{

}

bool CInterfaceManager::LoadImageTga(char* path, GLuint Index, GLint paramFilter, GLint paramWrap, char* ErrorMode, bool IsErrorBox)
{
    char FileName[256];

    FileName[ClearPathExtension(path, FileName) + 1] = 0;

    char FilePath[256];

    strcpy(FilePath, "Data\\");

    strcat(FilePath, FileName);
  
    strcat(FilePath, "OZT");

    FILE* pFile = fopen(FilePath, "rb");

    if (pFile == NULL)
    {
        if (IsErrorBox != 0)
        {
            if (ErrorMode != NULL)
            {
                sprintf(FileName, " %s of %s - File not exist.", ErrorMode, FilePath);
            }
            else 
            {
                sprintf(FileName, "%s - File not exist..", FilePath);
            }
               
            MessageBox(g_pnpGL, FileName, NULL, MB_OK);
            
            SendMessage(g_pnpGL, WM_DESTROY, 0, 0);

            return false;
        }

        return false;
    }

    fseek(pFile, 0, SEEK_END);

    int fileSize = ftell(pFile);

    fseek(pFile, 0, SEEK_SET);

    BYTE * pAlloc = (BYTE*)operator new(fileSize);

    fread(pAlloc, sizeof(BYTE), fileSize, pFile);

    fclose(pFile);

    int initTSize = 12;

    if (LoadDataType == 1)
    {
        initTSize = 16;
    }
    else
    {
        gTexture.Save_Image(4, "OZT", path, pAlloc, fileSize);
    }

    WORD width = *(WORD*)&pAlloc[initTSize];

    initTSize += sizeof(WORD);

    WORD height = *(WORD*)&pAlloc[initTSize];

    initTSize += sizeof(WORD);

    char Key = pAlloc[initTSize];

    if (Key != ' ' || width > 256 || height > 256)
    {
        operator delete(pAlloc);
        return false;
    }

    GLsizei width_c = 1;

    do
    {
        if (width_c >= width)
        {
            break;
        }

        width_c *= 2;

    } while (width_c < 256);

    GLsizei height_c = 1;

    do
    {
        if (height_c >= height)
        {
            break;
        }

        height_c *= 2;

    } while (height_c < 256);

    GLsizei height_c_cpy = height_c;

    TextureInfo* lpTexture = gTexture.GetTexture(Index);

    gTexture.UnloadTexture(Index);

    lpTexture->BitMapMul = 4;

    lpTexture->width = width_c;

    lpTexture->height = height_c;

    int BitMapSize = width_c * height_c * lpTexture->BitMapMul;

    lpTexture->pBitmap = (BYTE*)operator new(BitMapSize);

    GlobalBitMapSize += BitMapSize;

    // repasar cuando ya tengamos echo el sistema de dibujado y optimizar esta weba

    if (height > 0)
    {
        int height_cpy = height;

        BYTE* v26 = &pAlloc[initTSize];

        int cheight = height - 1;

        bool CharVal = false;

        do
        {
            BYTE* TBitMap_1 = v26;

            v26 += 4 * width;

            BYTE * TBitMap = &lpTexture->pBitmap[width_c * cheight * lpTexture->BitMapMul];

            int count = width;

            if (width > 0)
            {
                do
                {
                    BYTE v30 = TBitMap_1[2];

                    TBitMap_1 += 4;

                    *TBitMap = v30;

                    TBitMap[1] = *(TBitMap_1 - 3);

                    TBitMap[2] = *(TBitMap_1 - 4);

                    TBitMap[3] = *(TBitMap_1 - 1);

                    TBitMap += lpTexture->BitMapMul;

                    count--;

                } while (count);
            }

            CharVal = height_cpy == 1;

            cheight--;

            height_cpy--;

        } while (CharVal == false);
    }

	operator delete(pAlloc);

	glBindTexture(GL_TEXTURE_2D, Index);    

	glTexImage2D(GL_TEXTURE_2D, 0, 4, width_c, height_c, 0, GL_RGBA, GL_UNSIGNED_BYTE, lpTexture->pBitmap);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, paramFilter);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, paramFilter);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, paramWrap);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, paramWrap);

	return true;
}

static void my_error_exit(j_common_ptr cinfo)
{
    my_error_ptr myerr = (my_error_ptr)cinfo->err;

    (*cinfo->err->output_message) (cinfo);

    longjmp(myerr->setjmp_buffer, 1);
}

bool CInterfaceManager::LoadImageJpg(char* path, GLuint Index, GLint paramFilter, GLint paramWrap, char* ErrorMode, bool IsErrorBox)
{
    char FileName[256];

    FileName[ClearPathExtension(path, FileName) + 1] = 0;

    char FilePath[256];

    strcpy(FilePath, "Data\\");

    strcat(FilePath, FileName);

    strcat(FilePath, "OZJ");

    FILE* pFile = fopen(FilePath, "rb");

    if (pFile == NULL)
    {
        if (IsErrorBox != 0)
        {
            if (ErrorMode != NULL)
            {
                sprintf(FileName, " %s of %s - File not exist.", ErrorMode, FilePath);
            }
            else
            {
                sprintf(FileName, "%s - File not exist..", FilePath);
            }

            MessageBox(g_pnpGL, FileName, NULL, MB_OK);

            SendMessage(g_pnpGL, WM_DESTROY, 0, 0);

            return false;
        }

        return false;
    }

    if (LoadDataType != 0)
    {
        fseek(pFile, 24, SEEK_SET);
    }
    else
    {
        gTexture.Save_Image(24, "OZJ", path, NULL, 0);
    }

    struct my_error_mgr jpgError;

    struct jpeg_decompress_struct jpginfo;

    jpginfo.err = jpeg_std_error(&jpgError.pub);

    jpgError.pub.error_exit = my_error_exit;

    if (setjmp(jpgError.setjmp_buffer) != 0)
    {
        jpeg_destroy_decompress(&jpginfo);
        return 0;
    }

    jpeg_create_decompress(&jpginfo);   //jpeg_CreateDecompress(&jpginfo, 62, 464); -> no lee bien con esto

    jpeg_stdio_src(&jpginfo, pFile);

    jpeg_read_header(&jpginfo, 1);

    jpeg_start_decompress(&jpginfo);

    if (jpginfo.output_width <= 256 && jpginfo.output_height <= 256)
    {
        GLsizei image_width_c = 1;

        GLsizei image_width_T = 1;

        do
        {
            if (image_width_c >= jpginfo.output_width)
            {
                break;
            }

            image_width_c *= 2;

        } while (image_width_c < 256);

        GLsizei image_height_c = 1;

        image_width_T = image_width_c;

        GLsizei image_height_T = 1;

        do
        {
            if (image_height_c >= jpginfo.output_height)
            {
                break;
            }

            image_height_c *= 2;

        } while (image_height_c < 256);

        image_height_T = image_height_c;
    
        TextureInfo* lpTexture = gTexture.GetTexture(Index);

        gTexture.UnloadTexture(Index);

        lpTexture->BitMapMul = 3;

        lpTexture->width = image_width_T;

        lpTexture->height = image_height_T;

        int BitMapSize = lpTexture->BitMapMul * image_width_c * image_height_c;

        lpTexture->pBitmap = (BYTE*)operator new(BitMapSize);

        int row_stride = jpginfo.output_width * jpginfo.output_components;

        GlobalBitMapSize += BitMapSize;

        int row_stride_T = row_stride;

        JSAMPARRAY buffer = (*jpginfo.mem->alloc_sarray)((j_common_ptr)&jpginfo, JPOOL_IMAGE, row_stride, 1);

        if (jpginfo.output_scanline < jpginfo.output_height)
        {
            while (true)
            {
                jpeg_read_scanlines(&jpginfo, buffer, 1);

                memcpy(&lpTexture->pBitmap[3 * image_width_c * (jpginfo.output_scanline - 1)], *buffer, row_stride);

                if (jpginfo.output_scanline >= jpginfo.output_height)
                {
                    break;
                }

                row_stride = row_stride_T;

                image_width_c = image_width_T;
            }

            image_width_c = image_width_T;
        }

        glBindTexture(GL_TEXTURE_2D, Index);

        glTexImage2D(GL_TEXTURE_2D, 0, 3, image_width_c, image_height_T, 0, GL_RGB, GL_UNSIGNED_BYTE, lpTexture->pBitmap);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, paramFilter);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, paramFilter);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, paramWrap);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, paramWrap);
    }

    jpeg_finish_decompress(&jpginfo);

    jpeg_destroy_decompress(&jpginfo);

    fclose(pFile);

    return true;
}

void CInterfaceManager::RenderBitmap(GLuint Index, float PosX, float PosY, float Width, float Height, int a7, int a8, float a9, float a10, BYTE ConveWH, BYTE ConveXY)
{
    if (ConveXY != 0)
    {
        PosX = ConvertX(PosX);

        PosY = ConvertY(PosY);
    }

    if (ConveWH != 0)
    {
        Width = ConvertX(Width);

        Height = ConvertY(Height);
    }

    BindTexture(Index);

    GLfloat s[8];

    GLfloat x[8];

    x[2] = PosX;

    float v11 = WindowHeight - PosY;

    x[0] = PosX;

    s[0] = a7;

    s[1] = a8;

    s[2] = a7;

    x[1] = v11;

    x[3] = v11 - Height;

    GLfloat v15 = PosX + Width;

    x[4] = v15;

    x[5] = x[3];

    x[6] = v15;

    x[7] = v11;

    s[7] = a8;

    s[6] = a7 + a9;

    s[4] = s[6];

    s[5] = a8 + a10;

    s[3] = s[5];

    glBegin(GL_TRIANGLE_FAN);

    for (int i = 0; i < 8; i += 2)
    {
        glTexCoord2f(s[i], s[i + 1]);

        glVertex2f(x[i], x[i + 1]);
    }

    glEnd();
}

void CInterfaceManager::AccessModel(int ID, char* path, char* Model, int PathID)
{
    char buffer[64];

    if (PathID == -1)
    {
        sprintf(buffer, "%s.bmd", Model);
    }
    else if (PathID >= 10)
    {
        sprintf(buffer, "%s%d.bmd", Model, PathID);
    }
    else
    {
        sprintf(buffer, "%s0%d.bmd", Model, PathID);
    }

    if (LoadDataType != 0)
    {
        gBMDManager[ID].Open(path, buffer);
    }

   /* else if (word_57293BA[92 * ID] > 0)
    {
        sub_411020(&BMD_Data[184 * ID], (int)path, buffer);
    }*/
}

void CInterfaceManager::OpenTexture(int ID, char* Model, GLint paramFilter, bool IsErrorBox)
{
    CBMDManager* lpBMD = &gBMDManager[ID];

    char* ErrorMode = lpBMD->Name;

    if (lpBMD->NumMeshs < 1)
    {
        return;
    }

    for (size_t i = 0; i < lpBMD->NumMeshs; i++)
    {
        char* textureName = lpBMD->lpTextures[i].FileName;

        int Index = gTexture.FindTexture(textureName);

        if (Index < 0)
        {
            int FormatSlot;

            for (FormatSlot = 0; FormatSlot < strlen(textureName); FormatSlot++)
            {
                if (textureName[FormatSlot] != '.')
                {
                    continue;
                }

                break;
            }

            char buffer[64];

            strcpy(buffer, Model);

            int Tsize = strlen(textureName) + 1;

            memcpy(&buffer[strlen(buffer)], textureName, Tsize);

            char FormatKEY = textureName[FormatSlot + 1];

            if (FormatKEY == 't')
            {
                this->LoadImageTga(buffer, TextureCount, GL_NEAREST, GL_REPEAT, lpBMD->Name, IsErrorBox);
            }
            else
            {
                this->LoadImageJpg(buffer, TextureCount, paramFilter, GL_REPEAT, lpBMD->Name, IsErrorBox);
            }

            strcpy(gTexture.GetTexture(TextureCount)->name, textureName);

            lpBMD->lpIndexTexture[i] = TextureCount;

            TextureCount++;
        }
        else
        {
            lpBMD->lpIndexTexture[i] = Index;
        }

        if (textureName[0] == 's' && textureName[1] == 'k' && textureName[2] == 'i')
        {
            lpBMD->lpIndexTexture[i] = 301;
        }
        else if (textureName[0] == 'h' && textureName[1] == 'i' && textureName[2] == 'd')
        {
            lpBMD->lpIndexTexture[i] = 300;
        }
    }
}






















