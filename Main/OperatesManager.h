#pragma once
#include "ObjectManager.h"

#define MAX_OPERATES 200

struct OPERATE	//size = 12
{
	OPERATE()
	{
		sizeof(OPERATE);
	}

	BYTE isCreated;
	BYTE gap1[7];
	CObjectManager* lpObject;
};

class COperatesManager	//size = 12
{
public:
	COperatesManager();
	~COperatesManager();

	void CreateOperate(CObjectManager* lpObject);

private:
	OPERATE m_List[MAX_OPERATES];
};

extern COperatesManager gOperatesManager;