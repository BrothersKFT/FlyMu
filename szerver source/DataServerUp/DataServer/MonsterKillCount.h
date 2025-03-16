// MonsterKilLCount.h: interface for the CMonsterKilLCount class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "DataServerProtocol.h"

//**********************************************//
//********** GameServer -> DataServer **********//
//**********************************************//

struct SDHP_MONSTER_KILL_COUNT_RECV
{
	PSBMSG_HEAD header; // C1:12:00
	WORD index;
	WORD MonsterClass;
	char Name[11];
};

//**********************************************//
//********** DataServer -> GameServer **********//
//**********************************************//

struct SDHP_MONSTER_KILL_COUNT_SEND
{
	PSBMSG_HEAD header; // C1:12:00
	WORD index;
	WORD MonsterClass;
	WORD Count;
};

//**********************************************//
//**********************************************//
//**********************************************//

class CMonsterKilLCount
{
public:
	CMonsterKilLCount();
	virtual ~CMonsterKilLCount();
	void GDMonsterKillCountRecv(SDHP_MONSTER_KILL_COUNT_RECV* lpMsg, int index);
};

extern CMonsterKilLCount gMonsterKilLCount;
