//////////////////////////////////////////////////////////////////////

#pragma once

#include "User.h"

struct NPC_REQUIERE_INFO
{
	int Index;
	int MonsterClass;
	char Name[32];
	int Map;
	int X;
	int Y;
	int MinLevel;
	int MaxLevel;
	int MinReset;
	int MaxReset;
	int MinMReset;
	int MaxMReset;
	int AccountLevel;
	int PkMove;
	int Category;
	int ItemIndex;
	int Level;
	int Luck;
	int Skill;
	int Quantity;
};

class CCustomNpcReq
{
public:
	CCustomNpcReq();
	virtual ~CCustomNpcReq();
	void Load(char* path);
	bool GetNpcReq(LPOBJ lpObj, int MonsterClass, int Map, int X, int Y);
	bool CheckItem(LPOBJ lpObj, int npc);
	void RemoveItem(LPOBJ lpObj, int quest);
private:
	std::map<int, NPC_REQUIERE_INFO> m_CustomNpcReq;
};

extern CCustomNpcReq gCustomNpcReq;
