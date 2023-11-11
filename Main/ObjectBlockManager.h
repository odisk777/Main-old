#pragma once

#define MAX_OBJECT_BLOCK 256

/*struct _OBJECT_BLOCK	//size = 16
{
	_OBJECT_BLOCK()
	{
		sizeof(_OBJECT_BLOCK);
	}

	char field_0[4];
	class CObjectManager* lpObject1;
	class CObjectManager* lpObject2;
	char field_C[3];
	BYTE END;
};*/

class CObjectBlockManager	// size 16
{
public:
	CObjectBlockManager();
	~CObjectBlockManager();

public:
	char field_0[4];
	class CObjectManager* lpObject1;
	class CObjectManager* lpObject2;
	char field_C[3];
	BYTE END;
};

extern CObjectBlockManager gObjectBlockManager[MAX_OBJECT_BLOCK];
