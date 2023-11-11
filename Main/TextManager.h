#pragma once

#define MAX_TEXT 600
#define MAX_TEXT_LEN 300

class CTextManager
{
public:
	CTextManager();
	~CTextManager();
	void Load(char* path);
	char* GetText(int ID);
private:
	std::vector<std::string> m_GameText;
};

extern CTextManager gTextManager;
