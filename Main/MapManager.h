#pragma once

enum MAP_ID
{
	MAP_ID_LOGIN = 0,
	MAP_ID_LORENCIA = 1,
	MAP_ID_DUNGEON = 2,
	MAP_ID_DEVIAS = 3,
	MAP_ID_NORIA = 4,
	MAP_ID_LOST_TOWER = 5,
	MAP_ID_RESERVED1 = 6,
	MAP_ID_ARENA = 7,
	MAP_ID_ATLANS = 8,
	MAP_ID_TARKAN = 9,
};


class CMapManager
{
public:
	CMapManager();
	~CMapManager();
	void SetWorld(int ID) { this->World = ID; }
	int GetWorld() { return this->World; }
private:
	int World;
};

extern CMapManager gMapManager;