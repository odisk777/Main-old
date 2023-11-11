#pragma once

#define MAX_TERRAIN_SIZE 0x10000


class CPath
{
public:
	CPath();
	~CPath();
	void Clear();
	void InitPath();
private:
	DWORD width;
	DWORD height;
	BYTE* pTerrainWall;
	BYTE gapC[1004];
	void* HitMap;
	DWORD dword3FC;
	DWORD dword400;
	void* pvoid404;
	void* pvoid408;
	void* pvoid40C;
	BYTE END;
};

extern CPath gPath;

static BYTE TerrainWall[MAX_TERRAIN_SIZE];
