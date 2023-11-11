#pragma once


struct tagITEM	//SIZE = 68
{
	tagITEM()
	{
		sizeof(tagITEM);
	}
	WORD Type;
	int Level;
	BYTE Part;
	BYTE Class;
	BYTE TwoHand;
	WORD DamageMin;
	WORD DamageMax;
	BYTE SuccessfulBlocking;
	WORD Defense;
	WORD MagicDefense;
	//BYTE MagicPower;
	BYTE WeaponSpeed;
	WORD WalkSpeed;
	BYTE Durability;
	//BYTE Option1;
	//BYTE ExtOption;
	WORD RequireStrength;
	WORD RequireDexterity;
	WORD RequireEnergy;
	//WORD RequireCharisma;
	WORD RequireLevel;
	BYTE SpecialNum;
	BYTE Special[8];
	BYTE SpecialValue[8];
	int Number;
	WORD field_40;
	BYTE x;
	BYTE y;
	BYTE Color;
	BYTE field_45;
	BYTE field_46;
	BYTE field_47;
};

class CObjectManager	//size = 376
{
public:
	CObjectManager();
	~CObjectManager();
	CObjectManager* CreateObject(int ID, vec3_t vecTA2, vec3_t vecTA3, float a4);

private:
	BYTE byte_0;
	BYTE aling_1;
	WORD ID;
	BYTE field_4[4];
	float float_8;
	float float_C;
	float float_10;
	float float_14;
	float float_18;
	float float_1C;
	float float_20;
	float float_24;
	float float_28;
	float float_2C;
	BYTE field_30[36];
	DWORD dword_54;
	BYTE field_58[8];
	DWORD dword_60;
	float float_64;
	float float_68;
	float float_6C;
	BYTE aling_70;
	BYTE byte_71;
	BYTE field_72[2];
	float float_74;
	BYTE field_78[56];
	float float_B0;
	float float_B4;
	float float_B8;
	float float_BC;
	float float_C0;
	float float_C4;
	BYTE field_C8[4];
	BYTE byte_CC;
	BYTE field_CD[7];
	BYTE byte_D4;
	BYTE field_D5[3];
	float float_D8;
	float float_DC;
	float float_E0;
	BYTE field_E4[17];
	BYTE byte_F5;
	BYTE byte_F6;
	BYTE aling_F7;
	float float_F8;
	float float_FC;
	BYTE byte_100;
	BYTE field_101[7];
	float float_108;
	float float_10C;
	float float_110;
	float float_114;
	float float_118;
	float float_11C;
	BYTE field_120[48];
	BYTE byte_150;
	BYTE byte_151;
	BYTE field_152[2];
	float float_154;
	float float_158;
	BYTE field_15C[16];
	BYTE ObjectBlockID;
	BYTE field_16D[3];
	CObjectManager* lpObject1;
	CObjectManager* lpObject2;
};

extern CObjectManager gObjectManager;