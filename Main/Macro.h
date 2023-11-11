#pragma once

#define MAX_MACRO 10

#define MAX_MACRO_LEN 256

class CMacro
{
public:
	CMacro();
	~CMacro();
	void Load(char* path);
private:
	std::string m_MacroGame[MAX_MACRO];
};

extern CMacro gMacro;