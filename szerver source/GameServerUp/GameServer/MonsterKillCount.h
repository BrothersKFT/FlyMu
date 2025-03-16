// MonsterKillCount.h: interface for the CMonsterKillCount class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "User.h"
#include "Protocol.h"

//**********************************************//
//********** DataServer -> GameServer **********//
//**********************************************//

struct SDHP_MONSTER_KILL_COUNT_RECV
{
	PSBMSG_HEAD header; // C1:12:00
	WORD index;
	WORD MonsterClass;
	WORD Count;
};

//**********************************************//
//********** GameServer -> DataServer **********//
//**********************************************//

struct SDHP_MONSTER_KILL_COUNT_SEND
{
	PSBMSG_HEAD header; // C1:12:00
	WORD index;
	WORD MonsterClass;
	char Name[11];
};

//**********************************************//
//**********************************************//
//**********************************************//

struct MONSTER_KILL_COUNT_ITEM_LIST
{
	int Index;
	int Level;
	int Durability;
	int Skill;
	int Luck;
	int Option;
	int Exc;
	int Set;
	int Socket;
	int Duration;
};
struct MONSTER_KILL_COUNT_REWARD_INFO
{
	int Count;
	int Money;
	int WCoinC;
	int WCoinP;
	int GoblinPoint;
	int Ruud;
	char Description[128];
	std::vector<MONSTER_KILL_COUNT_ITEM_LIST> ItemList;
};
struct MONSTER_KILL_COUNT_INFO
{
	int MonsterIndex;
	std::map<int, MONSTER_KILL_COUNT_REWARD_INFO> RewardInfo;
};

class CMonsterKillCount
{
public:
	CMonsterKillCount();
	virtual ~CMonsterKillCount();
	void Load(char* path);
	void CheckMonsterKillCount(LPOBJ lpObj, int MonsterIndex);
	void DGMonsterKillCountRecv(SDHP_MONSTER_KILL_COUNT_RECV* lpMsg);
private:
	std::map<int, MONSTER_KILL_COUNT_INFO> m_MonsterKillCountInfo;
};

extern CMonsterKillCount gMonsterKillCount;
