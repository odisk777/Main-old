#include "stdafx.h"
#include "Util.h"
#include "BMDManager.h"

CBMDManager gBMDManager[MAX_BMD];

CBMDManager::CBMDManager()
{
    sizeof(CBMDManager);
}

CBMDManager::~CBMDManager()
{

}

void CBMDManager::Init(BYTE Mode)
{
    if (Mode != 0)
    {
        for (int i = 0; i < this->NumBones; i++)
        {
            Bone_t * lpBones = &this->lpBones[i];

            lpBones->Dummy = lpBones->Name[0] == 'D' && lpBones->Name[1] == 'u';
        }
    }

    this->BoneHead = -1;

    this->StreamMesh = -1;

    this->CreateBoundingBox();
}

bool CBMDManager::Open(char* path, char* modelname)
{
    char PathFile[64];

    strcpy(PathFile, path);

    strcat(PathFile, modelname);

    FILE* pFile = fopen(PathFile, "rb");

    if (pFile == NULL)
    {
        return 0;
    }

    fseek(pFile, 0, SEEK_END);

    size_t FileSize = ftell(pFile);

    fseek(pFile, 0, SEEK_SET);

    BYTE* pAlloc = (BYTE*)operator new(FileSize);

    fread(pAlloc, sizeof(BYTE), FileSize, pFile);

    fclose(pFile);

    int Size_Count = 3;

    this->Version = pAlloc[Size_Count];

    Size_Count += 1;

    memcpy(this->Name, &pAlloc[Size_Count], sizeof(this->Name));

    Size_Count += sizeof(this->Name);

    this->NumMeshs = *((WORD*)&pAlloc[Size_Count]);

    Size_Count += sizeof(WORD);

    this->NumBones = *((WORD*)&pAlloc[Size_Count]);

    Size_Count += sizeof(WORD);

    this->NumActions = *((WORD*)&pAlloc[Size_Count]);

    Size_Count += sizeof(WORD);

    this->lpMeshs = (Mesh_t*)operator new(sizeof(Mesh_t) * this->NumMeshs);

    this->lpBones = (Bone_t*)operator new(sizeof(Bone_t) * this->NumBones);

    this->lpActions = (Action_t*)operator new(sizeof(Action_t) * this->NumActions);

    this->lpTextures = (Texture_t*)operator new(sizeof(Texture_t) * this->NumMeshs);

    this->lpIndexTexture = (WORD*)operator new(sizeof(WORD) * this->NumMeshs);

    for (size_t i = 0; i < this->NumMeshs; i++)
    {
        Mesh_t* lpMeshs = &this->lpMeshs[i];

        lpMeshs->NumVertices = *(WORD*)&pAlloc[Size_Count];

        Size_Count += sizeof(WORD);

        lpMeshs->NumNormals = *(WORD*)&pAlloc[Size_Count];

        Size_Count += sizeof(WORD);

        lpMeshs->NumTexCoords = *(WORD*)&pAlloc[Size_Count];

        Size_Count += sizeof(WORD);

        lpMeshs->NumTriangles = *(WORD*)&pAlloc[Size_Count];

        Size_Count += sizeof(WORD);

        lpMeshs->Texture = *(WORD*)&pAlloc[Size_Count];

        Size_Count += sizeof(WORD);

        size_t sizeVertices = sizeof(Vertex_t) * lpMeshs->NumVertices;

        size_t sizeNormals = sizeof(Normal_t) * lpMeshs->NumNormals;

        size_t sizeTexCoords = sizeof(TexCoord_t) * lpMeshs->NumTexCoords;

        size_t sizeTriangles = sizeof(Triangle_t) * lpMeshs->NumTriangles;

        lpMeshs->Vertices = (Vertex_t*)operator new(sizeVertices);

        lpMeshs->Normals = (Normal_t*)operator new(sizeNormals);

        lpMeshs->TexCoords = (TexCoord_t*)operator new(sizeTexCoords);

        lpMeshs->Triangles = (Triangle_t*)operator new(sizeTriangles);

        memcpy(lpMeshs->Vertices, &pAlloc[Size_Count], sizeVertices);

        Size_Count += sizeVertices;

        memcpy(lpMeshs->Normals, &pAlloc[Size_Count], sizeNormals);

        Size_Count += sizeNormals;

        memcpy(lpMeshs->TexCoords, &pAlloc[Size_Count], sizeTexCoords);

        Size_Count += sizeTexCoords;

        memcpy(lpMeshs->Triangles, &pAlloc[Size_Count], sizeTriangles);

        Size_Count += sizeTriangles;

        memcpy(this->lpTextures[i].FileName, &pAlloc[Size_Count], sizeof(this->lpTextures[i].FileName));

        Size_Count += sizeof(this->lpTextures[i].FileName);
    }

    for (int i = 0; i < this->NumActions; i++)
    {
        Action_t* lpActions = &this->lpActions[i];

        lpActions->Loop = 0;

        lpActions->NumAnimationKeys = *(WORD*)&pAlloc[Size_Count];

        Size_Count += sizeof(WORD);

        lpActions->LockPositions = *(BYTE*)&pAlloc[Size_Count];

        Size_Count += sizeof(BYTE);

        if (lpActions->LockPositions == 0)
        {
            lpActions->Positions = NULL;
            continue;
        }

        int sizeAC = sizeof(vec3_t) * lpActions->NumAnimationKeys;

        lpActions->Positions = (vec3_t*)operator new[](sizeAC);

        memcpy(lpActions->Positions, &pAlloc[Size_Count], sizeAC);

        Size_Count += sizeAC;
    }

    for (int i = 0; i < this->NumBones; i++)
    {
        Bone_t* lpBones = &this->lpBones[i];

        lpBones->Dummy = pAlloc[Size_Count];

        Size_Count += sizeof(BYTE);

        if (lpBones->Dummy != 0)
        {
            continue;
        }

        memcpy(lpBones->Name, &pAlloc[Size_Count], sizeof(lpBones->Name));

        Size_Count += sizeof(lpBones->Name);

        lpBones->Parent = *(WORD*)&pAlloc[Size_Count];

        Size_Count += sizeof(WORD);

        lpBones->BoneMatrixes = (BoneMatrix_t*)operator new[](sizeof(BoneMatrix_t) * this->NumActions);

        for (int k = 0; k < this->NumActions; k++)
        {
            BoneMatrix_t* lpBoneMatrix = &lpBones->BoneMatrixes[k];

            size_t sizeUK = sizeof(vec3_t) * this->lpActions[k].NumAnimationKeys;

            lpBoneMatrix->Position = (vec3_t*)operator new(sizeUK);

            lpBoneMatrix->Rotation = (vec3_t*)operator new(sizeUK);

            memcpy(lpBoneMatrix->Position, &pAlloc[Size_Count], sizeUK);

            Size_Count += sizeUK;

            memcpy(lpBoneMatrix->Rotation, &pAlloc[Size_Count], sizeUK);

            Size_Count += sizeUK;
        }
    }

    operator delete(pAlloc);

    this->Init(FALSE);
}

void CBMDManager::CreateBoundingBox()
{
    for (int i = 0; i < this->NumBones; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            BoundingMin[i][j] = 9999.0;

            BoundingMax[i][j] = -9999.0;
        }

        BoundingVertices[i] = 0;
    }

    for (int k = 0; k < this->NumMeshs; k++)
    {
        Mesh_t* lpMeshs = &this->lpMeshs[k];

        for (int l = 0; l < lpMeshs->NumVertices; l++)
        {
            Vertex_t* lpVertex = &lpMeshs->Vertices[l];

            for (int m = 0; m < 3; m++)
            {
                if (BoundingMin[lpVertex->Node][m] > lpVertex->Position[m])
                {
                    BoundingMin[lpVertex->Node][m] = lpVertex->Position[m];
                }

                if (BoundingMax[lpVertex->Node][m] < lpVertex->Position[m])
                {
                    BoundingMax[lpVertex->Node][m] = lpVertex->Position[m];
                }
            }

            BoundingVertices[lpVertex->Node]++;
        }
    }

    for (int n = 0; n < this->NumBones; n++)
    {
        Bone_t* lpBones = &this->lpBones[n];

        lpBones->BoundingBox = BoundingVertices[n] != 0 ? 1 : 0;

        lpBones->BoundingVertices[0][0] = BoundingMin[n][0];

        lpBones->BoundingVertices[0][1] = BoundingMin[n][1];

        lpBones->BoundingVertices[0][2] = BoundingMin[n][2];

        lpBones->BoundingVertices[1][0] = BoundingMin[n][0];

        lpBones->BoundingVertices[1][1] = BoundingMin[n][1];

        lpBones->BoundingVertices[1][2] = BoundingMax[n][2];

        lpBones->BoundingVertices[2][0] = BoundingMin[n][0];

        lpBones->BoundingVertices[2][1] = BoundingMax[n][1];

        lpBones->BoundingVertices[2][2] = BoundingMin[n][2];

        lpBones->BoundingVertices[3][0] = BoundingMin[n][0];

        lpBones->BoundingVertices[3][1] = BoundingMax[n][1];

        lpBones->BoundingVertices[3][2] = BoundingMax[n][2];

        lpBones->BoundingVertices[4][0] = BoundingMax[n][0];

        lpBones->BoundingVertices[4][1] = BoundingMin[n][1];

        lpBones->BoundingVertices[4][2] = BoundingMin[n][2];

        lpBones->BoundingVertices[5][0] = BoundingMax[n][0];

        lpBones->BoundingVertices[5][1] = BoundingMin[n][1];

        lpBones->BoundingVertices[5][2] = BoundingMax[n][2];


        lpBones->BoundingVertices[6][0] = BoundingMax[n][0];

        lpBones->BoundingVertices[6][1] = BoundingMax[n][1];

        lpBones->BoundingVertices[6][2] = BoundingMin[n][2];

        lpBones->BoundingVertices[7][0] = BoundingMax[n][0];

        lpBones->BoundingVertices[7][1] = BoundingMax[n][1];

        lpBones->BoundingVertices[7][2] = BoundingMax[n][2];
    }
}