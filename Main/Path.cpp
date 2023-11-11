#include "stdafx.h"
#include "Path.h"

CPath gPath;

CPath::CPath()
{

}

CPath::~CPath()
{

}

void CPath::Clear()
{
    if (this->HitMap != NULL)
    {
        operator delete(this->HitMap);
        this->HitMap = NULL;
    }

    if (this->pvoid404 != NULL)
    {
        operator delete(this->pvoid404);
        this->pvoid404 = NULL;
    }

    if (this->pvoid408 != NULL)
    {
        operator delete(this->pvoid408);
        this->pvoid408 = NULL;
    }

    if (this->pvoid40C != NULL)
    {
        operator delete(this->pvoid40C);
        this->pvoid40C = NULL;
    }

    this->dword3FC = 1950000000;

    this->dword400 = -1;
}

void CPath::InitPath()
{
    this->Clear();

    this->width = 256;

    this->height = 256;

    this->pTerrainWall = TerrainWall;

    this->HitMap = operator new(MAX_TERRAIN_SIZE);

    this->pvoid404 = operator new(0x40000);

    this->pvoid408 = operator new(0x40000);

    this->pvoid40C = operator new(0x40000);

    memset(this->HitMap, 0, (this->width * this->height));
}