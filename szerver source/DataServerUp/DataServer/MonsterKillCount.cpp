// MonsterKilLCount.cpp: implementation of the CMonsterKilLCount class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MonsterKillCount.h"
#include "QueryManager.h"
#include "SocketManager.h"

CMonsterKilLCount gMonsterKilLCount;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMonsterKilLCount::CMonsterKilLCount() // OK
{

}

CMonsterKilLCount::~CMonsterKilLCount() // OK
{

}

void CMonsterKilLCount::GDMonsterKillCountRecv(SDHP_MONSTER_KILL_COUNT_RECV* lpMsg, int index) // OK
{
	SDHP_MONSTER_KILL_COUNT_SEND pMsg;

	pMsg.header.set(0x12, 0x00, sizeof(pMsg));

	pMsg.index = lpMsg->index;

	pMsg.MonsterClass = lpMsg->MonsterClass;

	if (gQueryManager.ExecQuery("SELECT * FROM MonsterKillCount WHERE Name='%s' and MonsterClass='%d'", lpMsg->Name, lpMsg->MonsterClass) == 0 || gQueryManager.Fetch() == SQL_NO_DATA)
	{
		gQueryManager.Close();
		gQueryManager.ExecQuery("INSERT INTO MonsterKillCount (Name,MonsterClass,MonsterKillCount) VALUES ('%s',%d,1)", lpMsg->Name, lpMsg->MonsterClass);
		gQueryManager.Close();

		pMsg.Count = 1;
	}
	else
	{
		pMsg.Count = gQueryManager.GetAsInteger("MonsterKillCount") + 1;

		gQueryManager.Close();
		gQueryManager.ExecQuery("UPDATE MonsterKillCount SET MonsterKillCount=MonsterKillCount+1 WHERE Name='%s' and MonsterClass='%d'", lpMsg->Name, lpMsg->MonsterClass);
		gQueryManager.Close();
	}

	gSocketManager.DataSend(index, (BYTE*)&pMsg, pMsg.header.size);
}