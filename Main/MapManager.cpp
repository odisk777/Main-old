#include "stdafx.h"
#include "MapManager.h"

CMapManager gMapManager;

CMapManager::CMapManager()
{
	this->World = MAP_ID_LOGIN;
}

CMapManager::~CMapManager()
{
}