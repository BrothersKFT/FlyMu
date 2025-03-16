// Duel.cpp: implementation of the CDuel class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Duel.h"
#include "CastleSiege.h"
#include "DarkSpirit.h"
#include "DSProtocol.h"
#include "EffectManager.h"
#include "Guild.h"
#include "Map.h"
#include "MapServerManager.h"
#include "Message.h"
#include "Monster.h"
#include "Notice.h"
#include "ServerInfo.h"
#include "User.h"
#include "Util.h"

#if (DUEL_CUSTOM_APUESTAS == 1)
#include "Log.h"
#include "Trade.h"
#endif

CDuel gDuel;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDuel::CDuel() // OK
{
	#if(GAMESERVER_UPDATE>=402)

	for(int n=0;n < MAX_DUEL_ARENA;n++)
	{
		DUEL_ARENA_INFO* lpInfo = &this->m_DuelArenaInfo[n];

		lpInfo->Index = n;
		lpInfo->State = DA_STATE_EMPTY;
		lpInfo->RemainTime = 0;
		lpInfo->TargetTime = 0;
		lpInfo->TickCount = GetTickCount();

		memset(lpInfo->Gladiator,-1,sizeof(lpInfo->Gladiator));
		memset(lpInfo->Spectator,-1,sizeof(lpInfo->Spectator));
	}

	#endif
}

CDuel::~CDuel() // OK
{

}

void CDuel::MainProc() // OK
{
	#if(GAMESERVER_UPDATE>=402)

	for(int n=0;n < MAX_DUEL_ARENA;n++)
	{
		DUEL_ARENA_INFO* lpInfo = &this->m_DuelArenaInfo[n];

		if((GetTickCount()-lpInfo->TickCount) >= 1000)
		{
			lpInfo->TickCount = GetTickCount();

			lpInfo->RemainTime = (int)difftime(lpInfo->TargetTime,time(0));

			switch(lpInfo->State)
			{
				case DA_STATE_EMPTY:
					this->ProcState_EMPTY(lpInfo);
					break;
				case DA_STATE_START:
					this->ProcState_START(lpInfo);
					break;
				case DA_STATE_CLEAN:
					this->ProcState_CLEAN(lpInfo);
					break;
			}
		}
	}

	#endif
}

void CDuel::ProcState_EMPTY(DUEL_ARENA_INFO* lpInfo) // OK
{

}

void CDuel::ProcState_START(DUEL_ARENA_INFO* lpInfo) // OK
{
	#if(GAMESERVER_UPDATE>=402)

	this->CheckDuelArenaGladiator(lpInfo);

	this->CheckDuelArenaSpectator(lpInfo);

	if(this->GetDuelArenaGladiatorCount(lpInfo) < MAX_DUEL_ARENA_GLADIATOR)
	{
		this->SetState(lpInfo,DA_STATE_CLEAN);
		return;
	}

	this->GCDuelInterfaceSend(lpInfo);

	if(lpInfo->RemainTime <= 0)
	{
		this->SetState(lpInfo,DA_STATE_CLEAN);
		return;
	}

	#endif
}

void CDuel::ProcState_CLEAN(DUEL_ARENA_INFO* lpInfo) // OK
{
	#if(GAMESERVER_UPDATE>=402)

	this->CheckDuelArenaGladiator(lpInfo);

	this->CheckDuelArenaSpectator(lpInfo);

	if(lpInfo->RemainTime <= 0)
	{
		this->SetState(lpInfo,DA_STATE_EMPTY);
		return;
	}

	#endif
}

void CDuel::SetState(DUEL_ARENA_INFO* lpInfo,int state) // OK
{
	#if(GAMESERVER_UPDATE>=402)

	switch((lpInfo->State=state))
	{
		case DA_STATE_EMPTY:
			this->SetState_EMPTY(lpInfo);
			break;
		case DA_STATE_START:
			this->SetState_START(lpInfo);
			break;
		case DA_STATE_CLEAN:
			this->SetState_CLEAN(lpInfo);
			break;
	}

	#endif
}

void CDuel::SetState_EMPTY(DUEL_ARENA_INFO* lpInfo) // OK
{
	#if(GAMESERVER_UPDATE>=402)

	this->ClearDuelArenaGladiator(lpInfo);

	this->ClearDuelArenaSpectator(lpInfo);

	#endif
}

void CDuel::SetState_START(DUEL_ARENA_INFO* lpInfo) // OK
{
	#if(GAMESERVER_UPDATE>=402)

	lpInfo->RemainTime = 1200;

	lpInfo->TargetTime = (int)(time(0)+lpInfo->RemainTime);

	#endif
}

void CDuel::SetState_CLEAN(DUEL_ARENA_INFO* lpInfo) // OK
{
	#if(GAMESERVER_UPDATE>=402)

	for(int n=0;n < MAX_DUEL_ARENA_GLADIATOR;n++)
	{
		if(OBJECT_RANGE(lpInfo->Gladiator[n]) != 0)
		{
			if(OBJECT_RANGE(gObj[lpInfo->Gladiator[n]].DuelUser) != 0)
			{
				this->ResetDuel(&gObj[lpInfo->Gladiator[n]]);
				this->GCDuelEndSend(lpInfo->Gladiator[n],0);
			}
		}
	}

	lpInfo->RemainTime = 10;

	lpInfo->TargetTime = (int)(time(0)+lpInfo->RemainTime);

	#endif
}

#if (DUEL_CUSTOM_APUESTAS == 0)
bool CDuel::AddDuelArena(LPOBJ lpObj,LPOBJ lpTarget) // OK
{
	#if(GAMESERVER_UPDATE>=402)

	for(int n=0;n < MAX_DUEL_ARENA;n++)
	{
		DUEL_ARENA_INFO* lpInfo = &this->m_DuelArenaInfo[n];

		if(lpInfo->State == DA_STATE_EMPTY)
		{
			if(this->AddDuelArenaGladiator(lpInfo,lpObj->Index) == 0 || this->AddDuelArenaGladiator(lpInfo,lpTarget->Index) == 0)
			{
				memset(lpInfo->Gladiator,-1,sizeof(lpInfo->Gladiator));
				return 0;
			}

			lpObj->Interface.use = 0;
			lpObj->Interface.type = INTERFACE_NONE;
			lpObj->Interface.state = 0;

			gObjMoveGate(lpObj->Index,(295+(n*2)));

			gEffectManager.ClearAllEffect(lpObj);

			lpTarget->Interface.use = 0;
			lpTarget->Interface.type = INTERFACE_NONE;
			lpTarget->Interface.state = 0;

			gObjMoveGate(lpTarget->Index,(296+(n*2)));

			gEffectManager.ClearAllEffect(lpTarget);

			if(gServerInfo.m_DuelArenaAnnounceSwitch != 0){gNotice.GCNoticeSendToAll(0,0,0,0,0,0,gMessage.GetMessage(174),lpObj->Name,lpTarget->Name);}

			this->SetState(lpInfo,DA_STATE_START);
			return 1;
		}
	}

	return 0;

	#else

	return 0;

	#endif
}
#else
bool CDuel::AddDuelArena(LPOBJ lpObj, LPOBJ lpTarget) // OK
{
#if(GAMESERVER_UPDATE>=402)

	for (int n = 0; n < MAX_DUEL_ARENA; n++)
	{
		DUEL_ARENA_INFO* lpInfo = &this->m_DuelArenaInfo[n];

		if (lpInfo->State == DA_STATE_EMPTY)
		{
			if (this->AddDuelArenaGladiator(lpInfo, lpObj->Index) == 0 || this->AddDuelArenaGladiator(lpInfo, lpTarget->Index) == 0)
			{
				memset(lpInfo->Gladiator, -1, sizeof(lpInfo->Gladiator));
				return 0;
			}

			lpObj->Interface.use = 0;
			lpObj->Interface.type = INTERFACE_NONE;
			lpObj->Interface.state = 0;

			gObjMoveGate(lpObj->Index, (295 + (n * 2)));

			gEffectManager.ClearAllEffect(lpObj);

			lpTarget->Interface.use = 0;
			lpTarget->Interface.type = INTERFACE_NONE;
			lpTarget->Interface.state = 0;

			gObjMoveGate(lpTarget->Index, (296 + (n * 2)));

			gEffectManager.ClearAllEffect(lpTarget);
			if ((lpObj->DueloConTradeActivo == 1) && (lpTarget->DueloConTradeActivo == 1))
			{
				if (gServerInfo.m_DuelArenaAnnounceSwitch != 0)
				{
					ITEM_INFO ItemInfo;
					gItemManager.GetInfo(lpObj->Apuesta->m_Index, &ItemInfo);
					ITEM_INFO ItemInfo2;
					gItemManager.GetInfo(lpTarget->Apuesta->m_Index, &ItemInfo2);
					gNotice.GCNoticeSendToAll(0, 0, 0, 0, 0, 0, gMessage.GetMessage(877));
					gNotice.GCNoticeSendToAll(0, 0, 0, 0, 0, 0, gMessage.GetMessage(878), lpObj->Name, ItemInfo.Name);
					gNotice.GCNoticeSendToAll(0, 0, 0, 0, 0, 0, gMessage.GetMessage(879), lpTarget->Name, ItemInfo2.Name);
				}
			}
			else {
				if (gServerInfo.m_DuelArenaAnnounceSwitch != 0){ gNotice.GCNoticeSendToAll(0, 0, 0, 0, 0, 0, gMessage.GetMessage(174), lpObj->Name, lpTarget->Name); }
			}
			this->SetState(lpInfo, DA_STATE_START);
			return 1;
		}
	}

	return 0;

#else

	return 0;

#endif
}
#endif

DUEL_ARENA_INFO* CDuel::GetDuelArenaByGladiator(int aIndex) // OK
{
	#if(GAMESERVER_UPDATE>=402)

	if(OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if(gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	if(DA_MAP_RANGE(gObj[aIndex].Map) == 0)
	{
		return 0;
	}

	for(int n=0;n < MAX_DUEL_ARENA;n++)
	{
		DUEL_ARENA_INFO* lpInfo = &this->m_DuelArenaInfo[n];

		if(lpInfo->State != DA_STATE_EMPTY)
		{
			for(int i=0;i < MAX_DUEL_ARENA_GLADIATOR;i++)
			{
				if(lpInfo->Gladiator[i] == aIndex)
				{
					return lpInfo;
				}
			}
		}
	}

	return 0;

	#else

	return 0;

	#endif
}

DUEL_ARENA_INFO* CDuel::GetDuelArenaBySpectator(int aIndex) // OK
{
	#if(GAMESERVER_UPDATE>=402)

	if(OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if(gObj[aIndex].Type != OBJECT_USER)
	{
		return 0;
	}

	if(DA_MAP_RANGE(gObj[aIndex].Map) == 0)
	{
		return 0;
	}

	for(int n=0;n < MAX_DUEL_ARENA;n++)
	{
		DUEL_ARENA_INFO* lpInfo = &this->m_DuelArenaInfo[n];

		if(lpInfo->State != DA_STATE_EMPTY)
		{
			for(int i=0;i < MAX_DUEL_ARENA_SPECTATOR;i++)
			{
				if(lpInfo->Spectator[i] == aIndex)
				{
					return lpInfo;
				}
			}
		}
	}

	return 0;

	#else

	return 0;

	#endif
}

bool CDuel::AddDuelArenaGladiator(DUEL_ARENA_INFO* lpInfo,int aIndex) // OK
{
	#if(GAMESERVER_UPDATE>=402)

	if(OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if(this->GetDuelArenaGladiator(lpInfo,aIndex) != 0)
	{
		return 0;
	}

	for(int n=0;n < MAX_DUEL_ARENA_GLADIATOR;n++)
	{
		if(OBJECT_RANGE(lpInfo->Gladiator[n]) == 0)
		{
			lpInfo->Gladiator[n] = aIndex;
			return 1;
		}
	}

	return 0;

	#else

	return 0;

	#endif
}

bool CDuel::DelDuelArenaGladiator(DUEL_ARENA_INFO* lpInfo,int aIndex) // OK
{
	#if(GAMESERVER_UPDATE>=402)

	if(OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	int* gladiator = this->GetDuelArenaGladiator(lpInfo,aIndex);
	
	if(gladiator == 0)
	{
		return 0;
	}
	else
	{
		(*gladiator) = -1;
		return 1;
	}

	#else

	return 0;

	#endif
}

int* CDuel::GetDuelArenaGladiator(DUEL_ARENA_INFO* lpInfo,int aIndex) // OK
{
	#if(GAMESERVER_UPDATE>=402)

	if(OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	for(int n=0;n < MAX_DUEL_ARENA_GLADIATOR;n++)
	{
		if(lpInfo->Gladiator[n] == aIndex)
		{
			return &lpInfo->Gladiator[n];
		}
	}

	return 0;

	#else

	return 0;

	#endif
}

bool CDuel::AddDuelArenaSpectator(DUEL_ARENA_INFO* lpInfo,int aIndex) // OK
{
	#if(GAMESERVER_UPDATE>=402)

	if(OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	if(this->GetDuelArenaSpectator(lpInfo,aIndex) != 0)
	{
		return 0;
	}

	for(int n=0;n < MAX_DUEL_ARENA_SPECTATOR;n++)
	{
		if(OBJECT_RANGE(lpInfo->Spectator[n]) == 0)
		{
			lpInfo->Spectator[n] = aIndex;
			return 1;
		}
	}

	return 0;

	#else

	return 0;

	#endif
}

bool CDuel::DelDuelArenaSpectator(DUEL_ARENA_INFO* lpInfo,int aIndex) // OK
{
	#if(GAMESERVER_UPDATE>=402)

	if(OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	int* spectator = this->GetDuelArenaSpectator(lpInfo,aIndex);

	if(spectator == 0)
	{
		return 0;
	}
	else
	{
		(*spectator) = -1;
		return 1;
	}

	#else

	return 0;

	#endif
}

int* CDuel::GetDuelArenaSpectator(DUEL_ARENA_INFO* lpInfo,int aIndex) // OK
{
	#if(GAMESERVER_UPDATE>=402)

	if(OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	for(int n=0;n < MAX_DUEL_ARENA_SPECTATOR;n++)
	{
		if(lpInfo->Spectator[n] == aIndex)
		{
			return &lpInfo->Spectator[n];
		}
	}

	return 0;

	#else

	return 0;

	#endif
}

void CDuel::CheckDuelArenaGladiator(DUEL_ARENA_INFO* lpInfo) // OK
{
	#if(GAMESERVER_UPDATE>=402)

	for(int n=0;n < MAX_DUEL_ARENA_GLADIATOR;n++)
	{
		if(OBJECT_RANGE(lpInfo->Gladiator[n]) == 0)
		{
			continue;
		}

		if(gObjIsConnected(lpInfo->Gladiator[n]) == 0)
		{
			this->DelDuelArenaGladiator(lpInfo,lpInfo->Gladiator[n]);
			continue;
		}

		if(gObj[lpInfo->Gladiator[n]].Map != MAP_DUEL_ARENA)
		{
			this->ResetDuel(&gObj[lpInfo->Gladiator[n]]);
			this->GCDuelEndSend(lpInfo->Gladiator[n],0);
			this->DelDuelArenaGladiator(lpInfo,lpInfo->Gladiator[n]);
			continue;
		}

		if(lpInfo->State != DA_STATE_CLEAN)
		{
			if(OBJECT_RANGE(gObj[lpInfo->Gladiator[n]].DuelUser) == 0)
			{
				gObjMoveGate(lpInfo->Gladiator[n],17);
				this->DelDuelArenaGladiator(lpInfo,lpInfo->Gladiator[n]);
				continue;
			}
		}
	}

	#endif
}

void CDuel::CheckDuelArenaSpectator(DUEL_ARENA_INFO* lpInfo) // OK
{
	#if(GAMESERVER_UPDATE>=402)

	for(int n=0;n < MAX_DUEL_ARENA_SPECTATOR;n++)
	{
		if(OBJECT_RANGE(lpInfo->Spectator[n]) == 0)
		{
			continue;
		}

		if(gObjIsConnected(lpInfo->Spectator[n]) == 0)
		{
			this->GCDuelSpectatorDelSend(lpInfo->Spectator[n],lpInfo);
			this->DelDuelArenaSpectator(lpInfo,lpInfo->Spectator[n]);
			continue;
		}

		if(gObj[lpInfo->Spectator[n]].Map != MAP_DUEL_ARENA)
		{
			this->GCDuelGladiatorDelSend(lpInfo->Spectator[n],0);
			this->GCDuelSpectatorDelSend(lpInfo->Spectator[n],lpInfo);
			gEffectManager.DelEffect(&gObj[lpInfo->Spectator[n]],EFFECT_INVISIBILITY);
			gEffectManager.DelEffect(&gObj[lpInfo->Spectator[n]],EFFECT_DUEL_ARENA_WATCH);
			this->DelDuelArenaSpectator(lpInfo,lpInfo->Spectator[n]);
			continue;
		}
	}

	#endif
}

void CDuel::ClearDuelArenaGladiator(DUEL_ARENA_INFO* lpInfo) // OK
{
	#if(GAMESERVER_UPDATE>=402)

	for(int n=0;n < MAX_DUEL_ARENA_GLADIATOR;n++)
	{
		if(OBJECT_RANGE(lpInfo->Gladiator[n]) != 0)
		{
			gObjMoveGate(lpInfo->Gladiator[n],17);

			lpInfo->Gladiator[n] = -1;
		}
	}

	#endif
}

void CDuel::ClearDuelArenaSpectator(DUEL_ARENA_INFO* lpInfo) // OK
{
	#if(GAMESERVER_UPDATE>=402)

	for(int n=0;n < MAX_DUEL_ARENA_SPECTATOR;n++)
	{
		if(OBJECT_RANGE(lpInfo->Spectator[n]) != 0)
		{
			gEffectManager.DelEffect(&gObj[lpInfo->Spectator[n]],EFFECT_INVISIBILITY);

			gEffectManager.DelEffect(&gObj[lpInfo->Spectator[n]],EFFECT_DUEL_ARENA_WATCH);

			gObjMoveGate(lpInfo->Spectator[n],17);

			lpInfo->Spectator[n] = -1;
		}
	}

	#endif
}

int CDuel::GetDuelArenaGladiatorCount(DUEL_ARENA_INFO* lpInfo) // OK
{
	#if(GAMESERVER_UPDATE>=402)

	int count = 0;

	for(int n=0;n < MAX_DUEL_ARENA_GLADIATOR;n++)
	{
		if(OBJECT_RANGE(lpInfo->Gladiator[n]) != 0)
		{
			count++;
		}
	}
	
	return count;

	#else

	return 0;

	#endif
}

int CDuel::GetDuelArenaSpectatorCount(DUEL_ARENA_INFO* lpInfo) // OK
{
	#if(GAMESERVER_UPDATE>=402)

	int count = 0;

	for(int n=0;n < MAX_DUEL_ARENA_SPECTATOR;n++)
	{
		if(OBJECT_RANGE(lpInfo->Spectator[n]) != 0)
		{
			count++;
		}
	}
	
	return count;

	#else

	return 0;

	#endif
}

bool CDuel::CheckDuel(LPOBJ lpObj,LPOBJ lpTarget) // OK
{
	if(lpObj->Type != OBJECT_USER || lpTarget->Type != OBJECT_USER)
	{
		return 0;
	}

	if(OBJECT_RANGE(lpObj->DuelUser) == 0 || OBJECT_RANGE(lpTarget->DuelUser) == 0)
	{
		return 0;
	}

	if(lpObj->DuelUser == lpTarget->Index && lpTarget->DuelUser == lpObj->Index)
	{
		return 1;
	}

	return 0;
}
#if (DUEL_CUSTOM_APUESTAS == 0)
void CDuel::CheckDuelScore(LPOBJ lpObj,LPOBJ lpTarget) // OK
{
	if(this->CheckDuel(lpObj,lpTarget) == 0)
	{
		return;
	}

	lpTarget->KillerType = 3;

	if(lpObj->DuelScore >= gServerInfo.m_DuelScore)
	{
		this->ResetDuel(lpObj);

		this->GCDuelEndSend(lpObj->Index,0);

		#if(GAMESERVER_UPDATE>=402)

		this->GCDuelWinSend(lpObj->Index,lpObj->Name,lpTarget->Name);

		#else

		if(gServerInfo.m_DuelArenaAnnounceSwitch != 0){gNotice.GCNoticeSendToAll(0,0,0,0,0,0,gMessage.GetMessage(175),lpObj->Name,lpTarget->Name);}

		#endif

		GDRankingDuelSaveSend(lpObj->Index,1,0);

		this->ResetDuel(lpTarget);

		this->GCDuelEndSend(lpTarget->Index,0);

		#if(GAMESERVER_UPDATE>=402)

		this->GCDuelWinSend(lpTarget->Index,lpObj->Name,lpTarget->Name);

		#endif

		GDRankingDuelSaveSend(lpTarget->Index,0,1);

		GCFireworksSend(lpObj,lpObj->X,lpObj->Y);

		#if(GAMESERVER_UPDATE>=402)

		DUEL_ARENA_INFO* lpInfo = this->GetDuelArenaByGladiator(lpObj->Index);

		if(lpInfo != 0)
		{
			this->GCDuelWinSend(lpInfo,lpObj->Name,lpTarget->Name);

			gEffectManager.AddEffect(lpObj,0,EFFECT_GLADIATORS_GLORY,3600,20,0,0,0);

			if(gServerInfo.m_DuelArenaAnnounceSwitch != 0){gNotice.GCNoticeSendToAll(0,0,0,0,0,0,gMessage.GetMessage(175),lpObj->Name,lpTarget->Name);}

			this->SetState(lpInfo,DA_STATE_CLEAN);
		}

		#endif
	}
}
#else
void CDuel::CheckDuelScore(LPOBJ lpObj, LPOBJ lpTarget) // OK
{
	if (this->CheckDuel(lpObj, lpTarget) == 0)
	{
		return;
	}

	lpTarget->KillerType = 3;


	if (lpObj->DuelScore >= gServerInfo.m_DuelScore)
	{
#if (ARCHIVEMENT == 1)
		gAchievements.DuelWin(lpObj->Index);
#endif
		this->ResetDuel(lpObj);

		this->GCDuelEndSend(lpObj->Index, 0);

#if(GAMESERVER_UPDATE>=402)

		this->GCDuelWinSend(lpObj->Index, lpObj->Name, lpTarget->Name);

#endif

		GDRankingDuelSaveSend(lpObj->Index, 1, 0);

		this->ResetDuel(lpTarget);

		this->GCDuelEndSend(lpTarget->Index, 0);

#if(GAMESERVER_UPDATE>=402)

		this->GCDuelWinSend(lpTarget->Index, lpObj->Name, lpTarget->Name);

#endif

		GDRankingDuelSaveSend(lpTarget->Index, 0, 1);

		GCFireworksSend(lpObj, lpObj->X, lpObj->Y);

#if(GAMESERVER_UPDATE>=402)

		DUEL_ARENA_INFO* lpInfo = this->GetDuelArenaByGladiator(lpObj->Index);

		if (lpInfo != 0)
		{
			this->GCDuelWinSend(lpInfo, lpObj->Name, lpTarget->Name);

			//			gEffectManager.AddEffect(lpObj,0,EFFECT_GLADIATORS_GLORY,3600,20,0,0,0);

			if ((lpObj->DueloConTradeActivo == 1) || (lpTarget->DueloConTradeActivo == 1))
			{
				if (gServerInfo.m_DuelArenaAnnounceSwitch != 0)
				{
					ITEM_INFO ItemInfo2;
					gItemManager.GetInfo(lpTarget->Apuesta->m_Index, &ItemInfo2);
					gNotice.GCNoticeSendToAll(0, 0, 0, 0, 0, 0, gMessage.GetMessage(880), lpObj->Name, ItemInfo2.Name);
				}
				lpObj->DueloConTradeActivo = 0;
				lpTarget->DueloConTradeActivo = 0;
			}
			else
			{
				if (gServerInfo.m_DuelArenaAnnounceSwitch != 0){ gNotice.GCNoticeSendToAll(0, 0, 0, 0, 0, 0, gMessage.GetMessage(175), lpObj->Name, lpTarget->Name); }
			}
			this->SetState(lpInfo, DA_STATE_CLEAN);
		}

#endif
	}
}
#endif
#if (DUEL_CUSTOM_APUESTAS == 0)
void CDuel::CheckDuelUser() // OK
{
	for(int n=OBJECT_START_USER;n < MAX_OBJECT;n++)
	{
		if(gObjIsConnected(n) == 0)
		{
			continue;
		}

		LPOBJ lpObj = &gObj[n];

		if(OBJECT_RANGE(lpObj->DuelUserReserved) != 0)
		{
			if((GetTickCount()-lpObj->DuelTickCount) > 30000)
			{
				this->ResetDuel(&gObj[lpObj->DuelUserReserved]);
				this->GCDuelStartSend(lpObj->Index,0,lpObj->DuelUserReserved);
				this->ResetDuel(lpObj);
			}
		}

		if(OBJECT_RANGE(lpObj->DuelUserRequested) != 0)
		{
			if((GetTickCount()-lpObj->DuelTickCount) > 30000)
			{
				this->ResetDuel(&gObj[lpObj->DuelUserRequested]);
				this->GCDuelStartSend(lpObj->DuelUserRequested,0,lpObj->Index);
				this->ResetDuel(lpObj);
			}
		}

		if(OBJECT_RANGE(lpObj->DuelUser) != 0)
		{
			if((GetTickCount()-lpObj->DuelTickCount) > 60000)
			{
				this->ResetDuel(&gObj[lpObj->DuelUser]);
				this->GCDuelEndSend(lpObj->DuelUser,0);
				this->ResetDuel(lpObj);
				this->GCDuelEndSend(lpObj->Index,0);
			}
		}
	}
}
#else
void CDuel::CheckDuelUser() // OK
{
	for (int n = OBJECT_START_USER; n < MAX_OBJECT; n++)
	{
		if (gObjIsConnected(n) == 0)
		{
			continue;
		}

		LPOBJ lpObj = &gObj[n];

		if (OBJECT_RANGE(lpObj->DuelUserReserved) != 0)
		{
			if ((GetTickCount() - lpObj->DuelTickCount) > 30000)
			{
				this->ResetDuel(&gObj[lpObj->DuelUserReserved]);
				this->GCDuelStartSend(lpObj->Index, 0, lpObj->DuelUserReserved);
				this->ResetDuel(lpObj);
			}
		}

		if (OBJECT_RANGE(lpObj->DuelUserRequested) != 0)
		{
			if ((GetTickCount() - lpObj->DuelTickCount) > 30000)
			{
				this->ResetDuel(&gObj[lpObj->DuelUserRequested]);
				this->GCDuelStartSend(lpObj->DuelUserRequested, 0, lpObj->Index);
				this->ResetDuel(lpObj);
			}
		}

		if (OBJECT_RANGE(lpObj->DuelUser) != 0)
		{
			if ((GetTickCount() - lpObj->DuelTickCount) > 300000)
			{
				LPOBJ lpTarget = &gObj[lpObj->DuelUser];
				if ((lpObj->DueloConTradeActivo == 1) && (lpTarget->DueloConTradeActivo == 1))
				{

					GDCreateItemSend(lpObj->Index, 0xEB, 0, 0, lpObj->Apuesta->m_Index, lpObj->Apuesta->m_Level, 0, lpObj->Apuesta->m_Option1, lpObj->Apuesta->m_Option2, lpObj->Apuesta->m_Option3, -1, lpObj->Apuesta->m_NewOption, lpObj->Apuesta->m_SetOption, lpObj->Apuesta->m_JewelOfHarmonyOption, 0, lpObj->Apuesta->m_SocketOption, 0xFF, 0);
					GDCreateItemSend(lpTarget->Index, 0xEB, 0, 0, lpTarget->Apuesta->m_Index, lpTarget->Apuesta->m_Level, 0, lpTarget->Apuesta->m_Option1, lpTarget->Apuesta->m_Option2, lpTarget->Apuesta->m_Option3, -1, lpTarget->Apuesta->m_NewOption, lpTarget->Apuesta->m_SetOption, lpObj->Apuesta->m_JewelOfHarmonyOption, 0, lpObj->Apuesta->m_SocketOption, 0xFF, 0);

					lpTarget->DueloConTradeActivo = 0;
					lpObj->DueloConTradeActivo = 0;
					GDCharacterInfoSaveSend(lpObj->Index);
				}
				gNotice.GCNoticeSendToAll(0, 0, 0, 0, 0, 0, gMessage.GetMessage(881), lpObj->Name, lpTarget->Name);
				lpObj->DueloEspecial = 0;
				lpTarget->DueloEspecial = 0;

				this->ResetDuel(&gObj[lpObj->DuelUser]);
				this->GCDuelEndSend(lpObj->DuelUser, 0);
				this->ResetDuel(lpObj);
				this->GCDuelEndSend(lpObj->Index, 0);
			}
		}
	}
}
#endif

void CDuel::ResetDuel(LPOBJ lpObj) // OK
{
	gDarkSpirit[lpObj->Index].ResetTarget(lpObj->DuelUser);

	lpObj->DuelUserReserved = -1;
	lpObj->DuelUserRequested = -1;
	lpObj->DuelScore = 0;
	lpObj->DuelUser = -1;
	lpObj->DuelTickCount = 0;
}

void CDuel::RespawnDuelUser(LPOBJ lpObj) // OK
{
	gMap[lpObj->Map].GetMapRandomPos(&lpObj->X,&lpObj->Y,18);

	#if(GAMESERVER_UPDATE>=402)

	DUEL_ARENA_INFO* lpInfo = this->GetDuelArenaByGladiator(lpObj->Index);

	if(lpInfo == 0)
	{
		return;
	}

	if(OBJECT_RANGE(((lpInfo->Gladiator[0]==lpObj->Index)?lpInfo->Gladiator[1]:lpInfo->Gladiator[0])) == 0)
	{
		return;
	}

	LPOBJ lpTarget = ((lpInfo->Gladiator[0]==lpObj->Index)?(&gObj[lpInfo->Gladiator[1]]):(&gObj[lpInfo->Gladiator[0]]));

	if(gServerInfo.m_DuelArenaDisableRestoreHP == 0)
	{
		lpTarget->Life = lpTarget->MaxLife+lpTarget->AddLife;
	}

	lpTarget->Mana = lpTarget->MaxMana+lpTarget->AddMana;
	lpTarget->BP = lpTarget->MaxBP+lpTarget->AddBP;

	if(gServerInfo.m_DuelArenaDisableRestoreSD == 0)
	{
		lpTarget->Shield = lpTarget->MaxShield+lpTarget->AddShield;
	}

	gMap[lpTarget->Map].GetMapRandomPos(&lpTarget->X,&lpTarget->Y,18);

	gObjTeleport(lpTarget->Index,lpTarget->Map,lpTarget->X,lpTarget->Y);

	GCLifeSend(lpTarget->Index,0xFF,(int)lpTarget->Life,lpTarget->Shield);

	GCManaSend(lpTarget->Index,0xFF,(int)lpTarget->Mana,lpTarget->BP);

	gEffectManager.ClearAllEffect(lpTarget);

	this->GCDuelRoundStartSend(lpInfo,0);

	#endif
}

void CDuel::UserDieProc(LPOBJ lpObj,LPOBJ lpTarget) // OK
{
	if(this->CheckDuel(lpObj,lpTarget) == 0)
	{
		return;
	}

	lpTarget->DuelScore++;

	this->GCDuelScoreSend(lpObj->Index,lpTarget->Index);

	#if(GAMESERVER_UPDATE>=402)

	DUEL_ARENA_INFO* lpInfo = this->GetDuelArenaByGladiator(lpObj->Index);

	if(lpInfo != 0)
	{
		this->GCDuelScoreSend(lpInfo);
	}

	#endif
}
#if (DUEL_CUSTOM_APUESTAS == 0)
void CDuel::CGDuelStartRecv(PMSG_DUEL_START_RECV* lpMsg,int aIndex) // OK
{
	if(gServerInfo.m_DuelSwitch == 0)
	{
		return;
	}

	LPOBJ lpObj = &gObj[aIndex];

	if(gObjIsConnectedGP(aIndex) == 0)
	{
		return;
	}

	int bIndex = MAKE_NUMBERW(lpMsg->index[0],lpMsg->index[1]);

	if(gObjIsConnectedGP(bIndex) == 0 || aIndex == bIndex)
	{
		gNotice.GCNoticeSend(aIndex,1,0,0,0,0,0,gMessage.GetMessage(160));
		return;
	}

	LPOBJ lpTarget = &gObj[bIndex];

	if(lpObj->Interface.use != 0 || lpTarget->Interface.use != 0)
	{
		gNotice.GCNoticeSend(aIndex,1,0,0,0,0,0,gMessage.GetMessage(161));
		return; 
	}

	if((lpTarget->Option & 2) == 0)
	{
		gNotice.GCNoticeSend(aIndex,1,0,0,0,0,0,gMessage.GetMessage(162));
		return;
	}

	if(OBJECT_RANGE(lpObj->DuelUserReserved) != 0 || OBJECT_RANGE(lpObj->DuelUserRequested) != 0 || OBJECT_RANGE(lpObj->DuelUser) != 0)
	{
		gNotice.GCNoticeSend(aIndex,1,0,0,0,0,0,gMessage.GetMessage(163));
		return;
	}

	if(OBJECT_RANGE(lpTarget->DuelUserReserved) != 0 || OBJECT_RANGE(lpTarget->DuelUserRequested) != 0 || OBJECT_RANGE(lpTarget->DuelUser) != 0)
	{
		gNotice.GCNoticeSend(aIndex,1,0,0,0,0,0,gMessage.GetMessage(164));
		return;
	}

	if(lpObj->Guild != 0 && lpObj->Guild->WarState == 1)
	{
		gNotice.GCNoticeSend(aIndex,1,0,0,0,0,0,gMessage.GetMessage(165));
		return;
	}

	if(lpTarget->Guild != 0 && lpTarget->Guild->WarState == 1)
	{
		gNotice.GCNoticeSend(aIndex,1,0,0,0,0,0,gMessage.GetMessage(166));
		return;
	}

	//FIX LEVEL DUEL
	if(lpObj->Level <= 50 || lpTarget->Level < 50)
	{
		gNotice.GCNoticeSend(aIndex,1,0,0,0,0,0,gMessage.GetMessage(632), 50);
		return;
	}

	#if(GAMESERVER_UPDATE>=402)

	if(gMapServerManager.CheckMapServer(MAP_DUEL_ARENA) == 0)
	{
		gNotice.GCNoticeSend(aIndex,1,0,0,0,0,0,gMessage.GetMessage(167));
		return;
	}

	#endif

	if(CA_MAP_RANGE(lpObj->Map) != 0 || DS_MAP_RANGE(lpObj->Map) != 0 || BC_MAP_RANGE(lpObj->Map) != 0 || CC_MAP_RANGE(lpObj->Map) != 0 || IT_MAP_RANGE(lpObj->Map) != 0 || DA_MAP_RANGE(lpObj->Map) != 0 || DG_MAP_RANGE(lpObj->Map) != 0 || IG_MAP_RANGE(lpObj->Map) != 0)
	{
		gNotice.GCNoticeSend(aIndex,1,0,0,0,0,0,gMessage.GetMessage(167));
		return;
	}

	#if(GAMESERVER_TYPE==1)

	if(gCastleSiege.GetCastleState() == CASTLESIEGE_STATE_NOTIFY || gCastleSiege.GetCastleState() == CASTLESIEGE_STATE_READYSIEGE || gCastleSiege.GetCastleState() == CASTLESIEGE_STATE_STARTSIEGE)
	{
		gNotice.GCNoticeSend(aIndex,1,0,0,0,0,0,gMessage.GetMessage(168));
		return;
	}

	#endif

	char name[11] = {0};

	memcpy(name,lpMsg->name,sizeof(lpMsg->name));

	if(strcmp(lpTarget->Name,name) != 0)
	{
		gNotice.GCNoticeSend(aIndex,1,0,0,0,0,0,gMessage.GetMessage(169));
		return;
	}

	for(int n=0;n < MAX_SELF_DEFENSE;n++)
	{
		if(lpObj->SelfDefense[n] >= 0)
		{
			gNotice.GCNoticeSend(aIndex,1,0,0,0,0,0,gMessage.GetMessage(170));
			return;
		}

		if(lpTarget->SelfDefense[n] >= 0)
		{
			gNotice.GCNoticeSend(aIndex,1,0,0,0,0,0,gMessage.GetMessage(171));
			return;
		}
	}

	lpObj->DuelUserReserved = bIndex;
	lpObj->DuelUserRequested = -1;
	lpObj->DuelScore = 0;
	lpObj->DuelUser = -1;
	lpObj->DuelTickCount = GetTickCount();
	
	lpTarget->DuelUserReserved = -1;
	lpTarget->DuelUserRequested = aIndex;
	lpTarget->DuelScore = 0;
	lpTarget->DuelUser = -1;
	lpTarget->DuelTickCount = GetTickCount();

	this->GCDuelOkSend(bIndex,aIndex);
}
#else
void CDuel::CGDuelStartRecv(PMSG_DUEL_START_RECV* lpMsg, int aIndex) // OK
{
	if (gServerInfo.m_DuelSwitch == 0)
	{
		return;
	}

	LPOBJ lpObj = &gObj[aIndex];

	if (gObjIsConnectedGP(aIndex) == 0)
	{
		return;
	}

	int bIndex = MAKE_NUMBERW(lpMsg->index[0], lpMsg->index[1]);

	if (gObjIsConnectedGP(bIndex) == 0 || aIndex == bIndex)
	{
		gNotice.GCNoticeSend(aIndex, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(160));
		return;
	}

	LPOBJ lpTarget = &gObj[bIndex];

	if (lpObj->Interface.use != 0 || lpTarget->Interface.use != 0)
	{
		gNotice.GCNoticeSend(aIndex, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(161));
		return;
	}

	if ((lpTarget->Option & 2) == 0)
	{
		gNotice.GCNoticeSend(aIndex, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(162));
		return;
	}

	if (OBJECT_RANGE(lpObj->DuelUserReserved) != 0 || OBJECT_RANGE(lpObj->DuelUserRequested) != 0 || OBJECT_RANGE(lpObj->DuelUser) != 0)
	{
		gNotice.GCNoticeSend(aIndex, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(163));
		return;
	}

	if (OBJECT_RANGE(lpTarget->DuelUserReserved) != 0 || OBJECT_RANGE(lpTarget->DuelUserRequested) != 0 || OBJECT_RANGE(lpTarget->DuelUser) != 0)
	{
		gNotice.GCNoticeSend(aIndex, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(164));
		return;
	}

	if (lpObj->Guild != 0 && lpObj->Guild->WarState == 1)
	{
		gNotice.GCNoticeSend(aIndex, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(165));
		return;
	}

	if (lpTarget->Guild != 0 && lpTarget->Guild->WarState == 1)
	{
		gNotice.GCNoticeSend(aIndex, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(166));
		return;
	}

#if(GAMESERVER_UPDATE>=402)

	if (gMapServerManager.CheckMapServer(MAP_DUEL_ARENA) == 0)
	{
		gNotice.GCNoticeSend(aIndex, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(167));
		return;
	}

#endif

	if (CA_MAP_RANGE(lpObj->Map) != 0 || DS_MAP_RANGE(lpObj->Map) != 0 || BC_MAP_RANGE(lpObj->Map) != 0 || CC_MAP_RANGE(lpObj->Map) != 0 || IT_MAP_RANGE(lpObj->Map) != 0 || DA_MAP_RANGE(lpObj->Map) != 0 || DG_MAP_RANGE(lpObj->Map) != 0 || IG_MAP_RANGE(lpObj->Map) != 0)
	{
		gNotice.GCNoticeSend(aIndex, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(167));
		return;
	}

#if(GAMESERVER_TYPE==1)

	if (gCastleSiege.GetCastleState() == CASTLESIEGE_STATE_NOTIFY || gCastleSiege.GetCastleState() == CASTLESIEGE_STATE_READYSIEGE || gCastleSiege.GetCastleState() == CASTLESIEGE_STATE_STARTSIEGE)
	{
		gNotice.GCNoticeSend(aIndex, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(168));
		return;
	}

#endif

	char name[11] = { 0 };

	memcpy(name, lpMsg->name, sizeof(lpMsg->name));

	if (strcmp(lpTarget->Name, name) != 0)
	{
		gNotice.GCNoticeSend(aIndex, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(169));
		return;
	}

	for (int n = 0; n < MAX_SELF_DEFENSE; n++)
	{
		if (lpObj->SelfDefense[n] >= 0)
		{
			gNotice.GCNoticeSend(aIndex, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(170));
			return;
		}

		if (lpTarget->SelfDefense[n] >= 0)
		{
			gNotice.GCNoticeSend(aIndex, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(171));
			return;
		}
	}

	this->GCDuelOkSend(bIndex, aIndex);
}
#endif
#if (DUEL_CUSTOM_APUESTAS == 0)
void CDuel::CGDuelOkRecv(PMSG_DUEL_OK_RECV* lpMsg,int aIndex) // OK
{
	LPOBJ lpObj = &gObj[aIndex];

	if(gObjIsConnectedGP(aIndex) == 0)
	{
		return;
	}

	int bIndex = MAKE_NUMBERW(lpMsg->index[0],lpMsg->index[1]);

	if(gObjIsConnectedGP(bIndex) == 0)
	{
		return;
	}

	LPOBJ lpTarget = &gObj[bIndex];

	if(lpMsg->flag == 0)
	{
		gNotice.GCNoticeSend(aIndex,1,0,0,0,0,0,gMessage.GetMessage(172));
		this->ResetDuel(lpObj);
		this->ResetDuel(lpTarget);
		this->GCDuelStartSend(bIndex,0,aIndex);
		return;
	}

	if(OBJECT_RANGE(lpObj->DuelUserReserved) != 0 || OBJECT_RANGE(lpObj->DuelUser) != 0)
	{
		gNotice.GCNoticeSend(aIndex,1,0,0,0,0,0,gMessage.GetMessage(163));
		this->ResetDuel(lpObj);
		this->ResetDuel(lpTarget);
		this->GCDuelStartSend(bIndex,0,aIndex);
		return;
	}

	if(OBJECT_RANGE(lpTarget->DuelUserRequested) != 0 || OBJECT_RANGE(lpTarget->DuelUser) != 0)
	{
		gNotice.GCNoticeSend(aIndex,1,0,0,0,0,0,gMessage.GetMessage(164));
		this->ResetDuel(lpObj);
		this->ResetDuel(lpTarget);
		this->GCDuelStartSend(bIndex,0,aIndex);
		return;
	}

	if(lpTarget->DuelUserReserved != aIndex)
	{
		gNotice.GCNoticeSend(aIndex,1,0,0,0,0,0,gMessage.GetMessage(164));
		this->ResetDuel(lpObj);
		this->ResetDuel(lpTarget);
		this->GCDuelStartSend(bIndex,0,aIndex);
		return;
	}

	#if(GAMESERVER_UPDATE>=402)

	if(gMapServerManager.CheckMapServer(MAP_DUEL_ARENA) == 0)
	{
		gNotice.GCNoticeSend(aIndex,1,0,0,0,0,0,gMessage.GetMessage(167));
		this->ResetDuel(lpObj);
		this->ResetDuel(lpTarget);
		this->GCDuelStartSend(bIndex,0,aIndex);
		return;
	}

	#endif

	if(CA_MAP_RANGE(lpTarget->Map) != 0 || DS_MAP_RANGE(lpTarget->Map) != 0 || BC_MAP_RANGE(lpTarget->Map) != 0 || CC_MAP_RANGE(lpTarget->Map) != 0 || IT_MAP_RANGE(lpTarget->Map) != 0 || DA_MAP_RANGE(lpTarget->Map) != 0 || DG_MAP_RANGE(lpTarget->Map) != 0 || IG_MAP_RANGE(lpTarget->Map) != 0)
	{
		gNotice.GCNoticeSend(aIndex,1,0,0,0,0,0,gMessage.GetMessage(167));
		this->ResetDuel(lpObj);
		this->ResetDuel(lpTarget);
		this->GCDuelStartSend(bIndex,0,aIndex);
		return;
	}

	#if(GAMESERVER_TYPE==1)

	if(gCastleSiege.GetCastleState() == CASTLESIEGE_STATE_NOTIFY || gCastleSiege.GetCastleState() == CASTLESIEGE_STATE_READYSIEGE || gCastleSiege.GetCastleState() == CASTLESIEGE_STATE_STARTSIEGE)
	{
		gNotice.GCNoticeSend(aIndex,1,0,0,0,0,0,gMessage.GetMessage(168));
		this->ResetDuel(lpObj);
		this->ResetDuel(lpTarget);
		this->GCDuelStartSend(bIndex,0,aIndex);
		return;
	}

	#endif

	char name[11] = {0};

	memcpy(name,lpMsg->name,10);

	if(strcmp(lpTarget->Name,name) != 0)
	{
		gNotice.GCNoticeSend(aIndex,1,0,0,0,0,0,gMessage.GetMessage(169));
		this->ResetDuel(lpObj);
		this->ResetDuel(lpTarget);
		this->GCDuelStartSend(bIndex,0,aIndex);
		return;
	}

	#if(GAMESERVER_UPDATE>=402)

	if(this->AddDuelArena(lpObj,lpTarget) == 0)
	{
		gNotice.GCNoticeSend(aIndex,1,0,0,0,0,0,gMessage.GetMessage(173));
		this->ResetDuel(lpObj);
		this->ResetDuel(lpTarget);
		this->GCDuelStartSend(bIndex,0,aIndex);
		return;
	}

	#else

	if(gServerInfo.m_DuelArenaAnnounceSwitch != 0){gNotice.GCNoticeSendToAll(0,0,0,0,0,0,gMessage.GetMessage(174),lpObj->Name,lpTarget->Name);}

	#endif

	lpObj->DuelUserReserved = -1;
	lpObj->DuelUserRequested = -1;
	lpObj->DuelScore = 0;
	lpObj->DuelUser = bIndex;
	lpObj->DuelTickCount = GetTickCount();
	
	lpTarget->DuelUserReserved = -1;
	lpTarget->DuelUserRequested = -1;
	lpTarget->DuelScore = 0;
	lpTarget->DuelUser = aIndex;
	lpTarget->DuelTickCount = GetTickCount();

	this->GCDuelStartSend(aIndex,1,bIndex);

	this->GCDuelStartSend(bIndex,1,aIndex);

	this->GCDuelScoreSend(aIndex,bIndex);
}
#else
void CDuel::CGDuelOkRecv(PMSG_DUEL_OK_RECV* lpMsg, int aIndex) // OK
{
	LPOBJ lpObj = &gObj[aIndex];

	if (gObjIsConnectedGP(aIndex) == 0)
	{
		return;
	}

	int bIndex = MAKE_NUMBERW(lpMsg->index[0], lpMsg->index[1]);

	if (gObjIsConnectedGP(bIndex) == 0)
	{
		return;
	}

	LPOBJ lpTarget = &gObj[bIndex];

	if (lpMsg->flag == 0)
	{
		gNotice.GCNoticeSend(aIndex, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(172));
		this->ResetDuel(lpObj);
		this->ResetDuel(lpTarget);
		this->GCDuelStartSend(bIndex, 0, aIndex);
		return;
	}

	if (OBJECT_RANGE(lpObj->DuelUserReserved) != 0 || OBJECT_RANGE(lpObj->DuelUser) != 0)
	{
		gNotice.GCNoticeSend(aIndex, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(163));
		this->ResetDuel(lpObj);
		this->ResetDuel(lpTarget);
		this->GCDuelStartSend(bIndex, 0, aIndex);
		return;
	}

	if (OBJECT_RANGE(lpTarget->DuelUserRequested) != 0 || OBJECT_RANGE(lpTarget->DuelUser) != 0)
	{
		gNotice.GCNoticeSend(aIndex, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(164));
		this->ResetDuel(lpObj);
		this->ResetDuel(lpTarget);
		this->GCDuelStartSend(bIndex, 0, aIndex);
		return;
	}

	if (lpTarget->DuelUserReserved != aIndex)
	{
		gNotice.GCNoticeSend(aIndex, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(164));
		this->ResetDuel(lpObj);
		this->ResetDuel(lpTarget);
		this->GCDuelStartSend(bIndex, 0, aIndex);
		return;
	}

#if(GAMESERVER_UPDATE>=402)

	if (gMapServerManager.CheckMapServer(MAP_DUEL_ARENA) == 0)
	{
		gNotice.GCNoticeSend(aIndex, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(167)); //ACA PONER MENSAJE CON APUESTA DE ITEMS
		this->ResetDuel(lpObj);
		this->ResetDuel(lpTarget);
		this->GCDuelStartSend(bIndex, 0, aIndex);
		return;
	}

#endif

	if (CA_MAP_RANGE(lpTarget->Map) != 0 || DS_MAP_RANGE(lpTarget->Map) != 0 || BC_MAP_RANGE(lpTarget->Map) != 0 || CC_MAP_RANGE(lpTarget->Map) != 0 || IT_MAP_RANGE(lpTarget->Map) != 0 || DA_MAP_RANGE(lpTarget->Map) != 0 || DG_MAP_RANGE(lpTarget->Map) != 0 || IG_MAP_RANGE(lpTarget->Map) != 0)
	{
		gNotice.GCNoticeSend(aIndex, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(167));
		this->ResetDuel(lpObj);
		this->ResetDuel(lpTarget);
		this->GCDuelStartSend(bIndex, 0, aIndex);
		return;
	}

#if(GAMESERVER_TYPE==1)

	if (gCastleSiege.GetCastleState() == CASTLESIEGE_STATE_NOTIFY || gCastleSiege.GetCastleState() == CASTLESIEGE_STATE_READYSIEGE || gCastleSiege.GetCastleState() == CASTLESIEGE_STATE_STARTSIEGE)
	{
		gNotice.GCNoticeSend(aIndex, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(168));
		this->ResetDuel(lpObj);
		this->ResetDuel(lpTarget);
		this->GCDuelStartSend(bIndex, 0, aIndex);
		return;
	}

#endif

	char name[11] = { 0 };

	memcpy(name, lpMsg->name, 10);

	if (strcmp(lpTarget->Name, name) != 0)
	{
		gNotice.GCNoticeSend(aIndex, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(169));
		this->ResetDuel(lpObj);
		this->ResetDuel(lpTarget);
		this->GCDuelStartSend(bIndex, 0, aIndex);
		return;
	}

#if(GAMESERVER_UPDATE>=402)

	if (this->AddDuelArena(lpObj, lpTarget) == 0)
	{
		gNotice.GCNoticeSend(aIndex, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(173));
		this->ResetDuel(lpObj);
		this->ResetDuel(lpTarget);
		this->GCDuelStartSend(bIndex, 0, aIndex);
		return;
	}

#endif

	lpObj->DuelUserReserved = -1;
	lpObj->DuelUserRequested = -1;
	lpObj->DuelScore = 0;
	lpObj->DuelUser = bIndex;
	lpObj->DuelTickCount = GetTickCount();

	lpTarget->DuelUserReserved = -1;
	lpTarget->DuelUserRequested = -1;
	lpTarget->DuelScore = 0;
	lpTarget->DuelUser = aIndex;
	lpTarget->DuelTickCount = GetTickCount();

	this->GCDuelStartSend(aIndex, 1, bIndex);

	this->GCDuelStartSend(bIndex, 1, aIndex);

	this->GCDuelScoreSend(aIndex, bIndex);
}
#endif
#if (DUEL_CUSTOM_APUESTAS == 0)
void CDuel::CGDuelEndRecv(int aIndex) // OK
{
	LPOBJ lpObj = &gObj[aIndex];

	if(gObjIsConnectedGP(aIndex) == 0)
	{
		return;
	}

	if(OBJECT_RANGE(lpObj->DuelUserReserved) != 0)
	{
		this->ResetDuel(&gObj[lpObj->DuelUserReserved]);
		this->GCDuelStartSend(aIndex,0,lpObj->DuelUserReserved);
		this->ResetDuel(lpObj);
		return;
	}

	if(OBJECT_RANGE(lpObj->DuelUserRequested) != 0)
	{
		this->ResetDuel(&gObj[lpObj->DuelUserRequested]);
		this->GCDuelStartSend(lpObj->DuelUserRequested,0,aIndex);
		this->ResetDuel(lpObj);
		return;
	}

	if(OBJECT_RANGE(lpObj->DuelUser) != 0)
	{
		this->ResetDuel(&gObj[lpObj->DuelUser]);
		this->GCDuelEndSend(lpObj->DuelUser,0);
		this->ResetDuel(lpObj);
		this->GCDuelEndSend(aIndex,0);
		return;
	}
}
#else
void CDuel::CGDuelEndRecv(int aIndex) // OK
{
	return;
	LPOBJ lpObj = &gObj[aIndex];

	if (gObjIsConnectedGP(aIndex) == 0)
	{
		return;
	}

	if (OBJECT_RANGE(lpObj->DuelUserReserved) != 0)
	{
		this->ResetDuel(&gObj[lpObj->DuelUserReserved]);
		this->GCDuelStartSend(aIndex, 0, lpObj->DuelUserReserved);
		this->ResetDuel(lpObj);
		return;
	}

	if (OBJECT_RANGE(lpObj->DuelUserRequested) != 0)
	{
		this->ResetDuel(&gObj[lpObj->DuelUserRequested]);
		this->GCDuelStartSend(lpObj->DuelUserRequested, 0, aIndex);
		this->ResetDuel(lpObj);
		return;
	}

	if (OBJECT_RANGE(lpObj->DuelUser) != 0)
	{
		this->ResetDuel(&gObj[lpObj->DuelUser]);
		this->GCDuelEndSend(lpObj->DuelUser, 0);
		this->ResetDuel(lpObj);
		this->GCDuelEndSend(aIndex, 0);
		return;
	}
}
#endif

void CDuel::CGDuelWatchRecv(PMSG_DUEL_WATCH_RECV* lpMsg,int aIndex) // OK
{
	#if(GAMESERVER_UPDATE>=402)

	LPOBJ lpObj = &gObj[aIndex];

	if(gObjIsConnectedGP(aIndex) == 0)
	{
		return;
	}

	if(gMapServerManager.CheckMapServer(MAP_DUEL_ARENA) == 0)
	{
		return;
	}

	if(lpObj->Interface.use == 0 || lpObj->Interface.type != INTERFACE_COMMON)
	{
		return;
	}

	if(CHECK_RANGE(lpMsg->number,MAX_DUEL_ARENA) == 0)
	{
		return;
	}

	DUEL_ARENA_INFO* lpInfo = &this->m_DuelArenaInfo[lpMsg->number];

	if(lpInfo->State != DA_STATE_START)
	{
		return;
	}

	if(this->GetDuelArenaSpectatorCount(lpInfo) >= MAX_DUEL_ARENA_SPECTATOR)
	{
		return;
	}

	if(this->AddDuelArenaSpectator(lpInfo,aIndex) == 0)
	{
		return;
	}

	if(OBJECT_RANGE(lpObj->SummonIndex) != 0)
	{
		gObjSummonKill(aIndex);
		GCSummonLifeSend(aIndex,0,1);
	}

	lpObj->Interface.use = 0;
	lpObj->Interface.type = INTERFACE_NONE;
	lpObj->Interface.state = 0;

	gEffectManager.AddEffect(lpObj,0,EFFECT_INVISIBILITY,0,0,0,0,0);

	gEffectManager.AddEffect(lpObj,0,EFFECT_DUEL_ARENA_WATCH,0,0,0,0,0);

	gObjMoveGate(aIndex,(303+lpMsg->number));

	this->GCDuelGladiatorAddSend(aIndex,lpInfo);

	this->GCDuelSpectatorListSend(aIndex,lpInfo);

	this->GCDuelSpectatorAddSend(aIndex,lpInfo);

	this->GCDuelInterfaceSend(lpInfo);

	this->GCDuelScoreSend(lpInfo);

	#endif
}

void CDuel::CGDuelButtonRecv(PMSG_DUEL_BUTTON_RECV* lpMsg,int aIndex) // OK
{
	#if(GAMESERVER_UPDATE>=402)

	LPOBJ lpObj = &gObj[aIndex];

	if(gObjIsConnectedGP(aIndex) == 0)
	{
		return;
	}

	if(CHECK_RANGE(lpMsg->number,MAX_DUEL_ARENA) == 0)
	{
		return;
	}

	DUEL_ARENA_INFO* lpInfo = &this->m_DuelArenaInfo[lpMsg->number];

	if(this->GetDuelArenaSpectator(lpInfo,aIndex) == 0)
	{
		return;
	}

	gEffectManager.DelEffect(lpObj,EFFECT_INVISIBILITY);

	gEffectManager.DelEffect(lpObj,EFFECT_DUEL_ARENA_WATCH);

	gObjMoveGate(aIndex,17);

	this->GCDuelSpectatorDelSend(aIndex,lpInfo);

	this->DelDuelArenaSpectator(lpInfo,aIndex);

	#endif
}

void CDuel::GCDuelStartSend(int aIndex,BYTE result,int bIndex) // OK
{
	#if(GAMESERVER_UPDATE>=402)

	PMSG_DUEL_START_SEND pMsg;

	pMsg.header.set(0xAA,0x01,sizeof(pMsg));

	pMsg.result = ((result==0)?0x0F:0);

	pMsg.index[0] = SET_NUMBERHB(bIndex);
	pMsg.index[1] = SET_NUMBERLB(bIndex);

	memcpy(pMsg.name,gObj[bIndex].Name,sizeof(pMsg.name));

	DataSend(aIndex,(BYTE*)&pMsg,pMsg.header.size);

	#else

	PMSG_DUEL_START_SEND pMsg;

	pMsg.header.set(0xAA,sizeof(pMsg));

	pMsg.result = result;

	pMsg.index[0] = SET_NUMBERHB(bIndex);
	pMsg.index[1] = SET_NUMBERLB(bIndex);

	memcpy(pMsg.name,gObj[bIndex].Name,sizeof(pMsg.name));

	DataSend(aIndex,(BYTE*)&pMsg,pMsg.header.size);

	#endif
}

void CDuel::GCDuelOkSend(int aIndex,int bIndex) // OK
{
	#if(GAMESERVER_UPDATE>=402)

	PMSG_DUEL_OK_SEND pMsg;

	pMsg.header.set(0xAA,0x02,sizeof(pMsg));

	pMsg.index[0] = SET_NUMBERHB(bIndex);
	pMsg.index[1] = SET_NUMBERLB(bIndex);

	memcpy(pMsg.name,gObj[bIndex].Name,sizeof(pMsg.name));

	DataSend(aIndex,(BYTE*)&pMsg,pMsg.header.size);

	#else

	PMSG_DUEL_OK_SEND pMsg;

	pMsg.header.set(0xAC,sizeof(pMsg));

	pMsg.index[0] = SET_NUMBERHB(bIndex);
	pMsg.index[1] = SET_NUMBERLB(bIndex);

	memcpy(pMsg.name,gObj[bIndex].Name,sizeof(pMsg.name));

	DataSend(aIndex,(BYTE*)&pMsg,pMsg.header.size);

	#endif
}

void CDuel::GCDuelEndSend(int aIndex,BYTE result) // OK
{
	#if(GAMESERVER_UPDATE>=402)

	PMSG_DUEL_END_SEND pMsg;
	
	pMsg.header.set(0xAA,0x03,sizeof(pMsg));

	pMsg.result = result;

	DataSend(aIndex,(BYTE*)&pMsg,pMsg.header.size);

	#else

	PMSG_DUEL_END_SEND pMsg;

	pMsg.header.set(0xAB,sizeof(pMsg));

	pMsg.index[0] = SET_NUMBERHB(aIndex);
	pMsg.index[1] = SET_NUMBERLB(aIndex);

	memcpy(pMsg.name,gObj[aIndex].Name,sizeof(pMsg.name));

	DataSend(aIndex,(BYTE*)&pMsg,pMsg.header.size);

	#endif
}

void CDuel::GCDuelScoreSend(int aIndex,int bIndex) // OK
{
	#if(GAMESERVER_UPDATE>=402)

	PMSG_DUEL_SCORE_SEND pMsg;

	pMsg.header.set(0xAA,0x04,sizeof(pMsg));

	pMsg.index1[0] = SET_NUMBERHB(aIndex);
	pMsg.index1[1] = SET_NUMBERLB(aIndex);

	pMsg.index2[0] = SET_NUMBERHB(bIndex);
	pMsg.index2[1] = SET_NUMBERLB(bIndex);

	pMsg.score[0] = gObj[aIndex].DuelScore;
	pMsg.score[1] = gObj[bIndex].DuelScore;

	DataSend(aIndex,(BYTE*)&pMsg,pMsg.header.size);
	DataSend(bIndex,(BYTE*)&pMsg,pMsg.header.size);

	#else

	PMSG_DUEL_SCORE_SEND pMsg;

	pMsg.header.set(0xAD,sizeof(pMsg));

	pMsg.index1[0] = SET_NUMBERHB(aIndex);
	pMsg.index1[1] = SET_NUMBERLB(aIndex);

	pMsg.index2[0] = SET_NUMBERHB(bIndex);
	pMsg.index2[1] = SET_NUMBERLB(bIndex);

	pMsg.score[0] = gObj[aIndex].DuelScore;
	pMsg.score[1] = gObj[bIndex].DuelScore;

	DataSend(aIndex,(BYTE*)&pMsg,pMsg.header.size);
	DataSend(bIndex,(BYTE*)&pMsg,pMsg.header.size);

	#endif
}

void CDuel::GCDuelScoreSend(DUEL_ARENA_INFO* lpInfo) // OK
{
	#if(GAMESERVER_UPDATE>=402)

	PMSG_DUEL_SCORE_SEND pMsg;

	pMsg.header.set(0xAA,0x04,sizeof(pMsg));

	pMsg.index1[0] = SET_NUMBERHB(lpInfo->Gladiator[0]);
	pMsg.index1[1] = SET_NUMBERLB(lpInfo->Gladiator[0]);

	pMsg.index2[0] = SET_NUMBERHB(lpInfo->Gladiator[1]);
	pMsg.index2[1] = SET_NUMBERLB(lpInfo->Gladiator[1]);

	pMsg.score[0] = gObj[lpInfo->Gladiator[0]].DuelScore;
	pMsg.score[1] = gObj[lpInfo->Gladiator[1]].DuelScore;

	for(int n=0;n < MAX_DUEL_ARENA_SPECTATOR;n++)
	{
		if(OBJECT_RANGE(lpInfo->Spectator[n]) != 0)
		{
			DataSend(lpInfo->Spectator[n],(BYTE*)&pMsg,pMsg.header.size);
		}
	}

	#endif
}

void CDuel::GCDuelInterfaceSend(DUEL_ARENA_INFO* lpInfo) // OK
{
	#if(GAMESERVER_UPDATE>=402)

	PMSG_DUEL_INTERFACE_SEND pMsg;

	pMsg.header.set(0xAA,0x05,sizeof(pMsg));

	pMsg.index1[0] = SET_NUMBERHB(lpInfo->Gladiator[0]);
	pMsg.index1[1] = SET_NUMBERLB(lpInfo->Gladiator[0]);

	pMsg.index2[0] = SET_NUMBERHB(lpInfo->Gladiator[1]);
	pMsg.index2[1] = SET_NUMBERLB(lpInfo->Gladiator[1]);

	pMsg.life1 = (BYTE)((gObj[lpInfo->Gladiator[0]].Life*100)/(gObj[lpInfo->Gladiator[0]].MaxLife+gObj[lpInfo->Gladiator[0]].AddLife));

	pMsg.life2 = (BYTE)((gObj[lpInfo->Gladiator[1]].Life*100)/(gObj[lpInfo->Gladiator[1]].MaxLife+gObj[lpInfo->Gladiator[1]].AddLife));

	pMsg.shield1 = (gObj[lpInfo->Gladiator[0]].Shield*100)/(gObj[lpInfo->Gladiator[0]].MaxShield+gObj[lpInfo->Gladiator[0]].AddShield);

	pMsg.shield2 = (gObj[lpInfo->Gladiator[1]].Shield*100)/(gObj[lpInfo->Gladiator[1]].MaxShield+gObj[lpInfo->Gladiator[1]].AddShield);

	for(int n=0;n < MAX_DUEL_ARENA_SPECTATOR;n++)
	{
		if(OBJECT_RANGE(lpInfo->Spectator[n]) != 0)
		{
			DataSend(lpInfo->Spectator[n],(BYTE*)&pMsg,pMsg.header.size);
		}
	}

	#endif
}

void CDuel::GCDuelNpcInfoSend(int aIndex) // OK
{
	#if(GAMESERVER_UPDATE>=402)

	BYTE send[256];

	PMSG_DUEL_NPC_INFO_SEND pMsg;

	pMsg.header.set(0xAA,0x06,0);

	int size = sizeof(pMsg);

	PMSG_DUEL_NPC_INFO info;

	for(int n=0;n < MAX_DUEL_ARENA;n++)
	{
		DUEL_ARENA_INFO* lpInfo = &this->m_DuelArenaInfo[n];

		if(lpInfo->State == DA_STATE_EMPTY)
		{
			memset(info.name1,0,sizeof(info.name1));

			memset(info.name2,0,sizeof(info.name2));

			info.state = 0;

			info.flag = 0;
		}
		else
		{
			if(OBJECT_RANGE(lpInfo->Gladiator[0]) == 0)
			{
				memset(info.name1,0,sizeof(info.name1));
			}
			else
			{
				memcpy(info.name1,gObj[lpInfo->Gladiator[0]].Name,sizeof(info.name1));
			}

			if(OBJECT_RANGE(lpInfo->Gladiator[1]) == 0)
			{
				memset(info.name2,0,sizeof(info.name2));
			}
			else
			{
				memcpy(info.name2,gObj[lpInfo->Gladiator[1]].Name,sizeof(info.name2));
			}

			info.state = 1;

			info.flag = ((this->GetDuelArenaSpectatorCount(lpInfo)>=MAX_DUEL_ARENA_SPECTATOR)?0:1);
		}

		memcpy(&send[size],&info,sizeof(info));
		size += sizeof(info);
	}

	pMsg.header.size = size;

	memcpy(send,&pMsg,sizeof(pMsg));

	DataSend(aIndex,send,size);

	#endif
}

void CDuel::GCDuelGladiatorAddSend(int aIndex,DUEL_ARENA_INFO* lpInfo) // OK
{
	#if(GAMESERVER_UPDATE>=402)

	PMSG_DUEL_GLADIATOR_ADD_SEND pMsg;

	pMsg.header.set(0xAA,0x07,sizeof(pMsg));

	pMsg.result = 0;

	pMsg.number = lpInfo->Index;

	if(OBJECT_RANGE(lpInfo->Gladiator[0]) == 0)
	{
		memset(pMsg.name1,0,sizeof(pMsg.name1));
	}
	else
	{
		memcpy(pMsg.name1,gObj[lpInfo->Gladiator[0]].Name,sizeof(pMsg.name1));
	}

	if(OBJECT_RANGE(lpInfo->Gladiator[1]) == 0)
	{
		memset(pMsg.name2,0,sizeof(pMsg.name2));
	}
	else
	{
		memcpy(pMsg.name2,gObj[lpInfo->Gladiator[1]].Name,sizeof(pMsg.name2));
	}

	pMsg.index1[0] = SET_NUMBERHB(lpInfo->Gladiator[0]);
	pMsg.index1[1] = SET_NUMBERLB(lpInfo->Gladiator[0]);

	pMsg.index2[0] = SET_NUMBERHB(lpInfo->Gladiator[1]);
	pMsg.index2[1] = SET_NUMBERLB(lpInfo->Gladiator[1]);

	DataSend(aIndex,(BYTE*)&pMsg,pMsg.header.size);

	#endif
}

void CDuel::GCDuelSpectatorAddSend(int aIndex,DUEL_ARENA_INFO* lpInfo) // OK
{
	#if(GAMESERVER_UPDATE>=402)

	PMSG_DUEL_SPECTATOR_ADD_SEND pMsg;

	pMsg.header.set(0xAA,0x08,sizeof(pMsg));

	memcpy(pMsg.name,gObj[aIndex].Name,sizeof(pMsg.name));

	for(int n=0;n < MAX_DUEL_ARENA_SPECTATOR;n++)
	{
		if(OBJECT_RANGE(lpInfo->Spectator[n]) != 0 && lpInfo->Spectator[n] != aIndex)
		{
			DataSend(lpInfo->Spectator[n],(BYTE*)&pMsg,pMsg.header.size);
		}
	}

	#endif
}

void CDuel::GCDuelGladiatorDelSend(int aIndex,BYTE result) // OK
{
	#if(GAMESERVER_UPDATE>=402)

	PMSG_DUEL_GLADIATOR_DEL_SEND pMsg;

	pMsg.header.set(0xAA,0x09,sizeof(pMsg));

	pMsg.result = result;

	DataSend(aIndex,(BYTE*)&pMsg,pMsg.header.size);

	#endif
}

void CDuel::GCDuelSpectatorDelSend(int aIndex,DUEL_ARENA_INFO* lpInfo) // OK
{
	#if(GAMESERVER_UPDATE>=402)

	PMSG_DUEL_SPECTATOR_DEL_SEND pMsg;

	pMsg.header.set(0xAA,0x0A,sizeof(pMsg));

	memcpy(pMsg.name,gObj[aIndex].Name,sizeof(pMsg.name));

	for(int n=0;n < MAX_DUEL_ARENA_SPECTATOR;n++)
	{
		if(OBJECT_RANGE(lpInfo->Spectator[n]) != 0 && lpInfo->Spectator[n] != aIndex)
		{
			DataSend(lpInfo->Spectator[n],(BYTE*)&pMsg,pMsg.header.size);
		}
	}

	#endif
}

void CDuel::GCDuelSpectatorListSend(int aIndex,DUEL_ARENA_INFO* lpInfo) // OK
{
	#if(GAMESERVER_UPDATE>=402)

	BYTE send[256];

	PMSG_DUEL_SPECTATOR_LIST_SEND pMsg;

	pMsg.header.set(0xAA,0x0B,0);

	int size = sizeof(pMsg);

	pMsg.count = 0;

	PMSG_DUEL_SPECTATOR_LIST info;

	for(int n=0;n < MAX_DUEL_ARENA_SPECTATOR;n++)
	{
		if(OBJECT_RANGE(lpInfo->Spectator[n]) != 0)
		{
			memcpy(info.name,gObj[lpInfo->Spectator[n]].Name,sizeof(info.name));

			memcpy(&send[size],&info,sizeof(info));
			size += sizeof(info);

			pMsg.count++;
		}
	}

	pMsg.header.size = size;

	memcpy(send,&pMsg,sizeof(pMsg));

	DataSend(aIndex,send,size);

	#endif
}
#if (DUEL_CUSTOM_APUESTAS == 0)
void CDuel::GCDuelWinSend(int aIndex,char* WinnerName,char* LoserName) // OK
{
	#if(GAMESERVER_UPDATE>=402)

	PMSG_DUEL_WIN_SEND pMsg;

	pMsg.header.set(0xAA,0x0C,sizeof(pMsg));

	memcpy(pMsg.WinnerName,WinnerName,sizeof(pMsg.WinnerName));

	memcpy(pMsg.LoserName,LoserName,sizeof(pMsg.LoserName));

	DataSend(aIndex,(BYTE*)&pMsg,pMsg.header.size);

	#endif
}
#else
void CDuel::GCDuelWinSend(int aIndex, char* WinnerName, char* LoserName) // OK
{
	int iIndex = gObjGetIndex(WinnerName);
	LPOBJ lpObj = &gObj[aIndex];
	int bIndex = gObjGetIndex(LoserName);
	LPOBJ lpTarget = &gObj[bIndex];
	if ((lpObj->DueloConTradeActivo == 1) && (lpTarget->DueloConTradeActivo == 1))
	{
		GDCreateItemSend(lpObj->Index, 0xEB, 0, 0, lpObj->Apuesta->m_Index, lpObj->Apuesta->m_Level, 0, lpObj->Apuesta->m_Option1, lpObj->Apuesta->m_Option2, lpObj->Apuesta->m_Option3, -1, lpObj->Apuesta->m_NewOption, lpObj->Apuesta->m_SetOption, lpObj->Apuesta->m_JewelOfHarmonyOption, 0, lpObj->Apuesta->m_SocketOption, lpObj->Apuesta->m_SocketOptionBonus, 0);
		GDCreateItemSend(lpObj->Index, 0xEB, 0, 0, lpTarget->Apuesta->m_Index, lpTarget->Apuesta->m_Level, 0, lpTarget->Apuesta->m_Option1, lpTarget->Apuesta->m_Option2, lpTarget->Apuesta->m_Option3, -1, lpTarget->Apuesta->m_NewOption, lpTarget->Apuesta->m_SetOption, lpTarget->Apuesta->m_JewelOfHarmonyOption, 0, lpTarget->Apuesta->m_SocketOption, lpTarget->Apuesta->m_SocketOptionBonus, 0);
		lpTarget->DueloConTradeActivo = 0;
		GDCharacterInfoSaveSend(lpObj->Index);
	}

	gLog.Output(LOG_GENERAL, "[DUEL SYSTEM] Ganador: %s. Perdedor: %s. Score %d - %d", WinnerName, LoserName, lpObj->DuelScore, lpTarget->DuelScore);

	lpObj->DueloEspecial = 0;
	lpTarget->DueloEspecial = 0;

	lpObj->Interface.use = 0;
	lpObj->Interface.type = INTERFACE_NONE;
	lpObj->Interface.state = 0;
	lpObj->TargetNumber = -1;
	lpObj->TradeOk = 0;
	lpObj->TradeOkTime = 0;
	lpObj->TradeMoney = 0;
	gTrade.ClearTrade(lpObj);

	lpTarget->Interface.use = 0;
	lpTarget->Interface.type = INTERFACE_NONE;
	lpTarget->Interface.state = 0;
	lpTarget->TargetNumber = -1;
	lpTarget->TradeOk = 0;
	lpTarget->TradeOkTime = 0;
	lpTarget->TradeMoney = 0;
	gTrade.ClearTrade(lpTarget);

#if(GAMESERVER_UPDATE>=402)

	PMSG_DUEL_WIN_SEND pMsg;

	pMsg.header.set(0xAA, 0x0C, sizeof(pMsg));

	memcpy(pMsg.WinnerName, WinnerName, sizeof(pMsg.WinnerName));

	memcpy(pMsg.LoserName, LoserName, sizeof(pMsg.LoserName));

	DataSend(aIndex, (BYTE*)&pMsg, pMsg.header.size);

#endif
}
#endif
#if (DUEL_CUSTOM_APUESTAS == 0)
void CDuel::GCDuelWinSend(DUEL_ARENA_INFO* lpInfo,char* WinnerName,char* LoserName) // OK
{
	#if(GAMESERVER_UPDATE>=402)

	PMSG_DUEL_WIN_SEND pMsg;

	pMsg.header.set(0xAA,0x0C,sizeof(pMsg));

	memcpy(pMsg.WinnerName,WinnerName,sizeof(pMsg.WinnerName));

	memcpy(pMsg.LoserName,LoserName,sizeof(pMsg.LoserName));

	for(int n=0;n < MAX_DUEL_ARENA_SPECTATOR;n++)
	{
		if(OBJECT_RANGE(lpInfo->Spectator[n]) != 0)
		{
			DataSend(lpInfo->Spectator[n],(BYTE*)&pMsg,pMsg.header.size);
		}
	}

	#endif
}
#else
void CDuel::GCDuelWinSend(DUEL_ARENA_INFO* lpInfo, char* WinnerName, char* LoserName) // OK
{
#if(GAMESERVER_UPDATE>=402)

	PMSG_DUEL_WIN_SEND pMsg;

	pMsg.header.set(0xAA, 0x0C, sizeof(pMsg));

	memcpy(pMsg.WinnerName, WinnerName, sizeof(pMsg.WinnerName));

	memcpy(pMsg.LoserName, LoserName, sizeof(pMsg.LoserName));

	for (int n = 0; n < MAX_DUEL_ARENA_SPECTATOR; n++)
	{
		if (OBJECT_RANGE(lpInfo->Spectator[n]) != 0)
		{
			DataSend(lpInfo->Spectator[n], (BYTE*)&pMsg, pMsg.header.size);
		}
	}

#endif
}
#endif

void CDuel::GCDuelRoundStartSend(DUEL_ARENA_INFO* lpInfo,BYTE flag) // OK
{
	#if(GAMESERVER_UPDATE>=402)

	PMSG_DUEL_ROUND_START_SEND pMsg;

	pMsg.header.set(0xAA,0x0D,sizeof(pMsg));

	pMsg.flag = flag;

	for(int n=0;n < MAX_DUEL_ARENA_SPECTATOR;n++)
	{
		if(OBJECT_RANGE(lpInfo->Spectator[n]) != 0)
		{
			DataSend(lpInfo->Spectator[n],(BYTE*)&pMsg,pMsg.header.size);
		}
	}

	#endif
}

#if (DUEL_CUSTOM_APUESTAS == 1)
int CDuel::gObjGetIndex(char* szId)
{
	for (int n = OBJECT_START_USER; n<MAX_OBJECT; n++)
	{
		if (gObj[n].Connected >= OBJECT_ONLINE)
		{
			if (toupper(gObj[n].Name[0]) == toupper(*szId))
			{
				if (strcmp(&gObj[n].Name[0], szId) == 0)
				{
					return n;
				}
			}
		}
	}
	return -1;
}

void CDuel::CheckDuelScoreCUSTOMPerder(LPOBJ lpObj, LPOBJ lpTarget) // OK
{
	if (this->CheckDuel(lpObj, lpTarget) == 0)
	{
		return;
	}

	lpTarget->KillerType = 3;

	if (lpObj->DuelScore >= 0)
	{
		this->ResetDuel(lpObj);

		this->GCDuelEndSend(lpObj->Index, 0);

#if(GAMESERVER_UPDATE>=402)

		this->GCDuelWinSend(lpObj->Index, lpObj->Name, lpTarget->Name);

#endif

		GDRankingDuelSaveSend(lpObj->Index, 1, 0);

		this->ResetDuel(lpTarget);

		this->GCDuelEndSend(lpTarget->Index, 0);

#if(GAMESERVER_UPDATE>=402)

		this->GCDuelWinSend(lpTarget->Index, lpObj->Name, lpTarget->Name);

#endif

		GDRankingDuelSaveSend(lpTarget->Index, 0, 1);

		GCFireworksSend(lpObj, lpObj->X, lpObj->Y);

#if(GAMESERVER_UPDATE>=402)

		DUEL_ARENA_INFO* lpInfo = this->GetDuelArenaByGladiator(lpObj->Index);

		if (lpInfo != 0)
		{
			this->GCDuelWinSend(lpInfo, lpObj->Name, lpTarget->Name);

			//			gEffectManager.AddEffect(lpObj,0,EFFECT_GLADIATORS_GLORY,3600,20,0,0,0);

			if ((lpObj->DueloConTradeActivo == 1) || (lpTarget->DueloConTradeActivo == 1))
			{
				if (gServerInfo.m_DuelArenaAnnounceSwitch != 0)
				{
					ITEM_INFO ItemInfo2;
					gItemManager.GetInfo(lpTarget->Apuesta->m_Index, &ItemInfo2);
					gNotice.GCNoticeSendToAll(0, 0, 0, 0, 0, 0, gMessage.GetMessage(880), lpObj->Name, ItemInfo2.Name);
				}
				lpObj->DueloConTradeActivo = 0;
				lpTarget->DueloConTradeActivo = 0;
			}
			else
			{
				if (gServerInfo.m_DuelArenaAnnounceSwitch != 0){ gNotice.GCNoticeSendToAll(0, 0, 0, 0, 0, 0, gMessage.GetMessage(175), lpObj->Name, lpTarget->Name); }
			}
			this->SetState(lpInfo, DA_STATE_CLEAN);
		}

#endif
	}
}

void CDuel::CGDueloDespuesDelTrade(LPOBJ lpObj, LPOBJ lpTarget)
{
	if (gObjIsConnectedGP(lpObj->Index) == 0)
	{
		return;
	}


	if (gObjIsConnectedGP(lpTarget->Index) == 0)
	{
		return;
	}

	if (OBJECT_RANGE(lpObj->DuelUserReserved) != 0 || OBJECT_RANGE(lpObj->DuelUser) != 0)
	{
		gNotice.GCNoticeSend(lpObj->Index, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(163));
		this->ResetDuel(lpObj);
		this->ResetDuel(lpTarget);
		this->GCDuelStartSend(lpTarget->Index, 0, lpObj->Index);
		return;
	}

#if(GAMESERVER_UPDATE>=402)

	if (gMapServerManager.CheckMapServer(MAP_DUEL_ARENA) == 0)
	{
		gNotice.GCNoticeSend(lpObj->Index, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(167));
		this->ResetDuel(lpObj);
		this->ResetDuel(lpTarget);
		this->GCDuelStartSend(lpTarget->Index, 0, lpObj->Index);
		return;
	}

#endif

	if (CA_MAP_RANGE(lpTarget->Map) != 0 || DS_MAP_RANGE(lpTarget->Map) != 0 || BC_MAP_RANGE(lpTarget->Map) != 0 || CC_MAP_RANGE(lpTarget->Map) != 0 || IT_MAP_RANGE(lpTarget->Map) != 0 || DA_MAP_RANGE(lpTarget->Map) != 0 || DG_MAP_RANGE(lpTarget->Map) != 0 || IG_MAP_RANGE(lpTarget->Map) != 0)
	{
		gNotice.GCNoticeSend(lpObj->Index, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(167));
		this->ResetDuel(lpObj);
		this->ResetDuel(lpTarget);
		this->GCDuelStartSend(lpTarget->Index, 0, lpObj->Index);
		return;
	}

#if(GAMESERVER_UPDATE>=402)

	if (this->AddDuelArena(lpObj, lpTarget) == 0)
	{
		gNotice.GCNoticeSend(lpObj->Index, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(173));
		this->ResetDuel(lpObj);
		this->ResetDuel(lpTarget);
		this->GCDuelStartSend(lpTarget->Index, 0, lpObj->Index);
		return;
	}

#endif

	lpObj->DuelUserReserved = -1;
	lpObj->DuelUserRequested = -1;
	lpObj->DuelScore = 0;
	lpObj->DuelUser = lpTarget->Index;
	lpObj->DuelTickCount = GetTickCount();

	lpTarget->DuelUserReserved = -1;
	lpTarget->DuelUserRequested = -1;
	lpTarget->DuelScore = 0;
	lpTarget->DuelUser = lpObj->Index;
	lpTarget->DuelTickCount = GetTickCount();

	this->GCDuelStartSend(lpObj->Index, 1, lpTarget->Index);

	this->GCDuelStartSend(lpTarget->Index, 1, lpObj->Index);

	this->GCDuelScoreSend(lpObj->Index, lpTarget->Index);
}

void CDuel::CGTradeAntesDelDuelo(LPOBJ lpObj, LPOBJ lpTarget)
{
	gNotice.GCNoticeSend(lpObj->Index, 0, 0, 0, 0, 0, 0, "Si deseas apostar algún item en el duelo, ingresalo ahora. Si no, cancela el trade");
	gNotice.GCNoticeSend(lpTarget->Index, 0, 0, 0, 0, 0, 0, "Si deseas apostar algún item en el duelo, ingresalo ahora. Si no, cancela el trade");
	lpObj->DueloEspecial = 1;
	lpTarget->DueloEspecial = 1;
	lpObj->Interface.use = 1;
	lpObj->Interface.type = INTERFACE_TRADE;
	lpObj->Interface.state = 0;
	lpObj->InterfaceTime = GetTickCount();
	lpObj->TargetNumber = lpTarget->Index;

	lpTarget->Interface.use = 1;
	lpTarget->Interface.type = INTERFACE_TRADE;
	lpTarget->Interface.state = 0;
	lpTarget->InterfaceTime = GetTickCount();
	lpTarget->TargetNumber = lpObj->Index;

	gObjFixInventoryPointer(lpObj->Index);
	gObjFixInventoryPointer(lpTarget->Index);
	gTrade.ClearTrade(lpObj);
	lpObj->Interface.use = 1;
	lpObj->Interface.type = INTERFACE_TRADE;
	lpObj->Interface.state = 1;
	lpObj->TradeOk = 0;
	lpObj->TradeOkTime = 0;
	lpObj->TradeMoney = 0;

	gTrade.GCTradeResponseSendCUSTOM(lpObj->Index, 1, lpTarget->Name, lpTarget->Level
#if (LEVEL_PLUS ==1)
		+ lpObj->LevelPlus
#endif
		, lpTarget->GuildNumber, 1);

	gTrade.ClearTrade(lpTarget);

	lpTarget->Interface.use = 1;
	lpTarget->Interface.type = INTERFACE_TRADE;
	lpTarget->Interface.state = 1;
	lpTarget->TradeOk = 0;
	lpTarget->TradeOkTime = 0;
	lpTarget->TradeMoney = 0;
	gTrade.GCTradeResponseSend(lpTarget->Index, 1, lpObj->Name, lpObj->Level
#if (LEVEL_PLUS ==1)
		+ lpObj->LevelPlus
#endif
		, lpObj->GuildNumber, 1);
	return;
}

void CDuel::CGDuelOkRecvCUSTOM(PMSG_DUEL_OK_RECV_CUSTOM* lpMsg, int aIndex) // OK
{
	LPOBJ lpObj = &gObj[aIndex];

	if (gObjIsConnectedGP(aIndex) == 0)
	{
		return;
	}

	int bIndex = MAKE_NUMBERW(lpMsg->index[0], lpMsg->index[1]);


	if (gObjIsConnectedGP(bIndex) == 0)
	{
		return;
	}
	LPOBJ lpTarget = &gObj[bIndex];

	if (lpMsg->flag == 0)
	{
		gNotice.GCNoticeSend(aIndex, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(172));
		this->ResetDuel(lpObj);
		this->ResetDuel(lpTarget);
		this->GCDuelStartSend(bIndex, 0, aIndex);
		return;
	}
	CGTradeAntesDelDuelo(lpObj, lpTarget);

}

#endif