#pragma once

enum CLASS_NUMBER
{
	CLASS_DW = 0,
	CLASS_DK = 1,
	CLASS_FE = 2,
	CLASS_MG = 3,
	CLASS_DL = 4,
	CLASS_SU = 5,
	CLASS_RF = 6,
	CLASS_GL = 7,
	CLASS_RW = 8,
	CLASS_SL = 9,
	CLASS_GC = 10,
};



class CCharacterMachine
{
public:
	CCharacterMachine();
	~CCharacterMachine();

private:

};

extern CCharacterMachine gCharacterMachine;