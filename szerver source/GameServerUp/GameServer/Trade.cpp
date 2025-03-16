// Trade.cpp: implementation of the CTrade class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Trade.h"
#include "DSProtocol.h"
#include "EventHideAndSeek.h"
#include "EventPvP.h"
#include "EventRussianRoulette.h"
#include "EventInventory.h"
#include "ItemValueTrade.h"
#include "Log.h"
#include "Map.h"
#include "ObjectManager.h"
#include "PentagramSystem.h"
#include "ServerInfo.h"
#include "User.h"
#include "Util.h"

#include "BotBuffer.h"
#include "BotTrader.h"

#if (DUEL_CUSTOM_APUESTAS == 1)
#include "CastleSiege.h"
#include "Message.h"
#include "Duel.h"
#include "Notice.h"
#endif

CTrade gTrade;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTrade::CTrade() // OK
{

}

CTrade::~CTrade() // OK
{

}

void CTrade::ClearTrade(LPOBJ lpObj) // OK
{
	for (int n = 0; n < TRADE_SIZE; n++)
	{
		lpObj->Trade[n].Clear();
	}

	memset(lpObj->TradeMap, 0xFF, TRADE_SIZE);
}

void CTrade::ResetTrade(int aIndex) // OK
{
	LPOBJ lpObj = &gObj[aIndex];

	if (lpObj->Interface.use == 0 || lpObj->Interface.type != INTERFACE_TRADE || lpObj->Interface.state == 0)
	{
		return;
	}

	gObjInventoryRollback(aIndex);

	gItemManager.GCItemListSend(aIndex);

#if(GAMESERVER_UPDATE>=802)

	gEventInventory.GCEventItemListSend(aIndex);

#endif

	GCMoneySend(aIndex, lpObj->Money);

	gObjectManager.CharacterMakePreviewCharSet(aIndex);

	gItemManager.GCItemEquipmentSend(aIndex);

	this->ClearTrade(lpObj);

	lpObj->Interface.use = 0;
	lpObj->Interface.type = INTERFACE_NONE;
	lpObj->Interface.state = 0;
	lpObj->TargetNumber = -1;
	lpObj->TradeOk = 0;
	lpObj->TradeOkTime = 0;
	lpObj->TradeMoney = 0;
}

bool CTrade::ExchangeTradeItem(LPOBJ lpObj, LPOBJ lpTarget) // OK
{
	for (int n = 0; n < TRADE_SIZE; n++)
	{
		if (lpObj->Trade[n].IsItem() != 0)
		{
			if (lpObj->Trade[n].IsEventItem() == 0)
			{
				if ((lpObj->Trade[n].m_Slot = gItemManager.InventoryInsertItem(lpTarget->Index, lpObj->Trade[n])) == 0xFF)
				{
					return 0;
				}
			}
			else
			{
				if ((lpObj->Trade[n].m_Slot = gEventInventory.EventInventoryInsertItem(lpTarget->Index, lpObj->Trade[n])) == 0xFF)
				{
					return 0;
				}
			}
		}
	}

	return 1;
}

void CTrade::ExchangeTradeItemLog(LPOBJ lpObj, LPOBJ lpTarget) // OK
{
	for (int n = 0; n < TRADE_SIZE; n++)
	{
		if (lpObj->Trade[n].IsItem() != 0)
		{
			gLog.Output(LOG_TRADE, "[ExchangeTradeItem][%s][%s] - (Account: %s, Name: %s, Index: %04d, Level: %02d, Serial: %08X, Option1: %01d, Option2: %01d, Option3: %01d, NewOption: %03d, JewelOfHarmonyOption: %03d, ItemOptionEx: %03d, SocketOption: %03d, %03d, %03d, %03d, %03d)", lpObj->Account, lpObj->Name, lpTarget->Account, lpTarget->Name, lpObj->Trade[n].m_Index, lpObj->Trade[n].m_Level, lpObj->Trade[n].m_Serial, lpObj->Trade[n].m_Option1, lpObj->Trade[n].m_Option2, lpObj->Trade[n].m_Option3, lpObj->Trade[n].m_NewOption, lpObj->Trade[n].m_JewelOfHarmonyOption, lpObj->Trade[n].m_ItemOptionEx, lpObj->Trade[n].m_SocketOption[0], lpObj->Trade[n].m_SocketOption[1], lpObj->Trade[n].m_SocketOption[2], lpObj->Trade[n].m_SocketOption[3], lpObj->Trade[n].m_SocketOption[4]);
		}
	}
}
#if (DUEL_CUSTOM_APUESTAS == 0)
void CTrade::CGTradeRequestRecv(PMSG_TRADE_REQUEST_RECV* lpMsg, int aIndex) // OK
{
	if (gServerInfo.m_TradeSwitch == 0)
	{
		return;
	}

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

	if (lpTarget->Type == OBJECT_BOT)
	{
		if (gBotBuffer.BotTalk(aIndex, bIndex) != 0)
		{
			return;
		}

		if (gBotTrader.BotTalk(aIndex, bIndex) != 0)
		{
			return;
		}

		return;
	}

	if (lpObj->Interface.use != 0 || lpTarget->Interface.use != 0)
	{
		return;
	}

	if (CA_MAP_RANGE(lpTarget->Map) != 0 || DS_MAP_RANGE(lpTarget->Map) != 0 || BC_MAP_RANGE(lpTarget->Map) != 0 || CC_MAP_RANGE(lpTarget->Map) != 0 || IT_MAP_RANGE(lpTarget->Map) != 0 || DA_MAP_RANGE(lpTarget->Map) != 0 || DG_MAP_RANGE(lpTarget->Map) != 0 || IG_MAP_RANGE(lpTarget->Map) != 0)
	{
		this->GCTradeResponseSend(aIndex, 0, lpTarget->Name, 0, 0);
		return;
	}

	if (lpObj->X < (lpTarget->X - 2) || lpObj->X >(lpTarget->X + 2) || lpObj->Y < (lpTarget->Y - 2) || lpObj->Y >(lpTarget->Y + 2))
	{
		this->GCTradeResponseSend(aIndex, 0, lpTarget->Name, 0, 0);
		return;
	}

	if (lpObj->PShopOpen != 0 || lpTarget->PShopOpen != 0)
	{
		this->GCTradeResponseSend(aIndex, 0, lpTarget->Name, 0, 0);
		return;
	}

	if (gEventHideAndSeek.EventHideAndSeekTrade(aIndex, bIndex) == 1)
	{
		return;
	}

	if (gEventPvP.EventPvPTradeJoin(aIndex, bIndex) == 1)
	{
		return;
	}

	if (gEventRussianRoulette.EventRussianRouletteTrade(aIndex, bIndex) == 1)
	{
		return;
	}

	if ((lpTarget->Option & 1) == 0)
	{
		this->GCTradeResponseSend(aIndex, 0, lpTarget->Name, 0, 0);
		return;
	}

	int	number = MAKE_NUMBERW(lpMsg->index[0], lpMsg->index[1]);

	if (OBJMAX_RANGE(number) == FALSE)
	{
		LogAdd(LOG_BLACK, "Error : %s %d (%d)", __FILE__, __LINE__, number);
		return;
	}
	if (number == aIndex)
	{
		return;
	}

	lpObj->Interface.use = 1;
	lpObj->Interface.type = INTERFACE_TRADE;
	lpObj->Interface.state = 0;
	lpObj->InterfaceTime = GetTickCount();
	lpObj->TargetNumber = bIndex;

	lpTarget->Interface.use = 1;
	lpTarget->Interface.type = INTERFACE_TRADE;
	lpTarget->Interface.state = 0;
	lpTarget->InterfaceTime = GetTickCount();
	lpTarget->TargetNumber = aIndex;

	this->GCTradeRequestSend(bIndex, lpObj->Name);
}
#else
void CTrade::CGTradeRequestRecv(PMSG_TRADE_REQUEST_RECV* lpMsg, int aIndex) // OK
{
	if (gServerInfo.m_TradeSwitch == 0)
	{
		return;
	}

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

	if (lpTarget->Type == OBJECT_BOT)
	{
		if (gBotBuffer.BotTalk(aIndex, bIndex) != 0)
		{
			return;
		}

		if (gBotTrader.BotTalk(aIndex, bIndex) != 0)
		{
			return;
		}

		return;
	}


	if (lpObj->Interface.use != 0 || lpTarget->Interface.use != 0)
	{
		return;
	}

	if (CA_MAP_RANGE(lpTarget->Map) != 0 || DS_MAP_RANGE(lpTarget->Map) != 0 || BC_MAP_RANGE(lpTarget->Map) != 0 || CC_MAP_RANGE(lpTarget->Map) != 0 || IT_MAP_RANGE(lpTarget->Map) != 0 || DA_MAP_RANGE(lpTarget->Map) != 0 || DG_MAP_RANGE(lpTarget->Map) != 0 || IG_MAP_RANGE(lpTarget->Map) != 0)
	{
		this->GCTradeResponseSend(aIndex, 0, lpTarget->Name, 0, 0, 0);
		return;
	}

	if (lpObj->X < (lpTarget->X - 2) || lpObj->X >(lpTarget->X + 2) || lpObj->Y < (lpTarget->Y - 2) || lpObj->Y >(lpTarget->Y + 2))
	{
		this->GCTradeResponseSend(aIndex, 0, lpTarget->Name, 0, 0, 0);
		return;
	}

	if (lpObj->PShopOpen != 0 || lpTarget->PShopOpen != 0)
	{
		this->GCTradeResponseSend(aIndex, 0, lpTarget->Name, 0, 0, 0);
		return;
	}

	if (gEventHideAndSeek.EventHideAndSeekTrade(aIndex, bIndex) == 1)
	{
		return;
	}

	if (gEventPvP.EventPvPTradeJoin(aIndex, bIndex) == 1)
	{
		return;
	}

	if (gEventRussianRoulette.EventRussianRouletteTrade(aIndex, bIndex) == 1)
	{
		return;
	}

	if ((lpTarget->Option & 1) == 0)
	{
		this->GCTradeResponseSend(aIndex, 0, lpTarget->Name, 0, 0, 0);
		return;
	}

	int	number = MAKE_NUMBERW(lpMsg->index[0], lpMsg->index[1]);

	if (OBJMAX_RANGE(number) == FALSE)
	{
		LogAdd(LOG_BLACK, "Error : %s %d (%d)", __FILE__, __LINE__, number);
		return;
	}
	if (number == aIndex)
	{
		return;
	}

	lpObj->Interface.use = 1;
	lpObj->Interface.type = INTERFACE_TRADE;
	lpObj->Interface.state = 0;
	lpObj->InterfaceTime = GetTickCount();
	lpObj->TargetNumber = bIndex;

	lpTarget->Interface.use = 1;
	lpTarget->Interface.type = INTERFACE_TRADE;
	lpTarget->Interface.state = 0;
	lpTarget->InterfaceTime = GetTickCount();
	lpTarget->TargetNumber = aIndex;

	this->GCTradeRequestSend(bIndex, lpObj->Name);
}
#endif
#if (DUEL_CUSTOM_APUESTAS == 0)
void CTrade::CGTradeResponseRecv(PMSG_TRADE_RESPONSE_RECV* lpMsg, int aIndex) // OK
{
	LPOBJ lpObj = &gObj[aIndex];

	if (gObjIsConnectedGP(aIndex) == 0)
	{
		return;
	}

	int bIndex = lpObj->TargetNumber;

	if (gObjIsConnectedGP(bIndex) == 0)
	{
		return;
	}

	LPOBJ lpTarget = &gObj[bIndex];

	if (lpObj->Interface.use == 0 || lpObj->Interface.type != INTERFACE_TRADE || lpObj->Interface.state != 0)
	{
		return;
	}

	if (lpTarget->Interface.use == 0 || lpTarget->Interface.type != INTERFACE_TRADE || lpTarget->Interface.state != 0)
	{
		return;
	}

	if (CA_MAP_RANGE(lpTarget->Map) != 0 || DS_MAP_RANGE(lpTarget->Map) != 0 || BC_MAP_RANGE(lpTarget->Map) != 0 || CC_MAP_RANGE(lpTarget->Map) != 0 || IT_MAP_RANGE(lpTarget->Map) != 0 || DA_MAP_RANGE(lpTarget->Map) != 0 || DG_MAP_RANGE(lpTarget->Map) != 0 || IG_MAP_RANGE(lpTarget->Map) != 0)
	{
		goto CLEAR_JUMP;
	}

	if (lpObj->X < (lpTarget->X - 2) || lpObj->X >(lpTarget->X + 2) || lpObj->Y < (lpTarget->Y - 2) || lpObj->Y >(lpTarget->Y + 2))
	{
		goto CLEAR_JUMP;
	}

	if (lpObj->PShopOpen != 0 || lpTarget->PShopOpen != 0)
	{
		goto CLEAR_JUMP;
	}

	if (lpMsg->response == 0)
	{
		goto CLEAR_JUMP;
	}

	gObjFixInventoryPointer(aIndex);

	if (lpObj->Transaction == 1)
	{
		goto CLEAR_JUMP;
	}

	if (gObjInventoryTransaction(aIndex) == 0 || gObjInventoryTransaction(bIndex) == 0)
	{
		goto CLEAR_JUMP;
	}

	this->ClearTrade(lpObj);

	lpObj->Interface.use = 1;
	lpObj->Interface.type = INTERFACE_TRADE;
	lpObj->Interface.state = 1;
	lpObj->TradeOk = 0;
	lpObj->TradeOkTime = 0;
	lpObj->TradeMoney = 0;

	this->GCTradeResponseSend(aIndex, 1, lpTarget->Name, lpTarget->Level, lpTarget->GuildNumber);

	this->ClearTrade(lpTarget);

	lpTarget->Interface.use = 1;
	lpTarget->Interface.type = INTERFACE_TRADE;
	lpTarget->Interface.state = 1;
	lpTarget->TradeOk = 0;
	lpTarget->TradeOkTime = 0;
	lpTarget->TradeMoney = 0;

	this->GCTradeResponseSend(bIndex, 1, lpObj->Name, lpObj->Level, lpObj->GuildNumber);

	return;

CLEAR_JUMP:

	gObjInventoryCommit(aIndex);

	lpObj->Interface.use = 0;
	lpObj->Interface.type = INTERFACE_NONE;
	lpObj->Interface.state = 0;
	lpObj->TargetNumber = -1;

	this->GCTradeResponseSend(aIndex, 0, lpTarget->Name, 0, 0);

	gObjInventoryCommit(bIndex);

	lpTarget->Interface.use = 0;
	lpTarget->Interface.type = INTERFACE_NONE;
	lpTarget->Interface.state = 0;
	lpTarget->TargetNumber = -1;

	this->GCTradeResponseSend(bIndex, 0, lpObj->Name, 0, 0);
}
#else
void CTrade::CGTradeResponseRecv(PMSG_TRADE_RESPONSE_RECV* lpMsg, int aIndex) // OK
{
	LPOBJ lpObj = &gObj[aIndex];

	if (gObjIsConnectedGP(aIndex) == 0)
	{
		return;
	}

	int bIndex = lpObj->TargetNumber;

	if (gObjIsConnectedGP(bIndex) == 0)
	{
		return;
	}

	LPOBJ lpTarget = &gObj[bIndex];

	if (lpObj->Interface.use == 0 || lpObj->Interface.type != INTERFACE_TRADE || lpObj->Interface.state != 0)
	{
		return;
	}

	if (lpTarget->Interface.use == 0 || lpTarget->Interface.type != INTERFACE_TRADE || lpTarget->Interface.state != 0)
	{
		return;
	}

	if (CA_MAP_RANGE(lpTarget->Map) != 0 || DS_MAP_RANGE(lpTarget->Map) != 0 || BC_MAP_RANGE(lpTarget->Map) != 0 || CC_MAP_RANGE(lpTarget->Map) != 0 || IT_MAP_RANGE(lpTarget->Map) != 0 || DA_MAP_RANGE(lpTarget->Map) != 0 || DG_MAP_RANGE(lpTarget->Map) != 0 || IG_MAP_RANGE(lpTarget->Map) != 0)
	{
		goto CLEAR_JUMP;
	}

	if (lpObj->X < (lpTarget->X - 2) || lpObj->X >(lpTarget->X + 2) || lpObj->Y < (lpTarget->Y - 2) || lpObj->Y >(lpTarget->Y + 2))
	{
		goto CLEAR_JUMP;
	}

	if (lpObj->PShopOpen != 0 || lpTarget->PShopOpen != 0)
	{
		goto CLEAR_JUMP;
	}

	if (lpMsg->response == 0)
	{
		goto CLEAR_JUMP;
	}

	gObjFixInventoryPointer(aIndex);

	if (lpObj->Transaction == 1)
	{
		goto CLEAR_JUMP;
	}

	if (gObjInventoryTransaction(aIndex) == 0 || gObjInventoryTransaction(bIndex) == 0)
	{
		goto CLEAR_JUMP;
	}

	this->ClearTrade(lpObj);

	lpObj->Interface.use = 1;
	lpObj->Interface.type = INTERFACE_TRADE;
	lpObj->Interface.state = 1;
	lpObj->TradeOk = 0;
	lpObj->TradeOkTime = 0;
	lpObj->TradeMoney = 0;

	this->GCTradeResponseSend(aIndex, 1, lpTarget->Name, lpTarget->Level, lpTarget->GuildNumber, 1);

	this->ClearTrade(lpTarget);

	lpTarget->Interface.use = 1;
	lpTarget->Interface.type = INTERFACE_TRADE;
	lpTarget->Interface.state = 1;
	lpTarget->TradeOk = 0;
	lpTarget->TradeOkTime = 0;
	lpTarget->TradeMoney = 0;

	this->GCTradeResponseSend(bIndex, 1, lpObj->Name, lpObj->Level, lpObj->GuildNumber, 1);

	return;

CLEAR_JUMP:

	gObjInventoryCommit(aIndex);

	lpObj->Interface.use = 0;
	lpObj->Interface.type = INTERFACE_NONE;
	lpObj->Interface.state = 0;
	lpObj->TargetNumber = -1;

	this->GCTradeResponseSend(aIndex, 0, lpTarget->Name, 0, 0, 0);

	gObjInventoryCommit(bIndex);

	lpTarget->Interface.use = 0;
	lpTarget->Interface.type = INTERFACE_NONE;
	lpTarget->Interface.state = 0;
	lpTarget->TargetNumber = -1;

	this->GCTradeResponseSend(bIndex, 0, lpObj->Name, 0, 0, 0);
}
#endif

void CTrade::CGTradeMoneyRecv(PMSG_TRADE_MONEY_RECV* lpMsg, int aIndex) // OK
{
	LPOBJ lpObj = &gObj[aIndex];

	if (gObjIsConnectedGP(aIndex) == 0)
	{
		return;
	}

	int bIndex = lpObj->TargetNumber;

	if (gObjIsConnectedGP(bIndex) == 0)
	{
		return;
	}

	LPOBJ lpTarget = &gObj[bIndex];

	if (lpTarget->BotType == BOT_TRADER)
	{
		return;
	}

	if (lpObj->Interface.use == 0 || lpObj->Interface.type != INTERFACE_TRADE || lpObj->Interface.state == 0)
	{
		return;
	}

	if (lpTarget->Interface.use == 0 || lpTarget->Interface.type != INTERFACE_TRADE || lpTarget->Interface.state == 0)
	{
		return;
	}

	if (lpMsg->money >= MAX_TRADE_MONEY || lpObj->Money < lpMsg->money)
	{
		return;
	}

	GCMoneySend(aIndex, (lpObj->Money - lpMsg->money));

	PMSG_TRADE_RESULT_SEND pMsg;

	pMsg.header.set(0x3A, sizeof(pMsg));

	pMsg.result = 1;

	DataSend(aIndex, (BYTE*)&pMsg, pMsg.header.size);

	lpObj->TradeOk = 0;
	lpObj->TradeOkTime = GetTickCount();
	this->GCTradeOkButtonSend(aIndex, 0);

	lpTarget->TradeOk = 0;
	lpTarget->TradeOkTime = GetTickCount();
	this->GCTradeOkButtonSend(bIndex, 2);

	lpObj->TradeMoney = lpMsg->money;
	this->GCTradeMoneySend(bIndex, lpMsg->money);
}
#if (DUEL_CUSTOM_APUESTAS == 0)
void CTrade::CGTradeOkButtonRecv(PMSG_TRADE_OK_BUTTON_RECV* lpMsg, int aIndex) // OK
{
	LPOBJ lpObj = &gObj[aIndex];


	if (gObjIsConnectedGP(aIndex) == 0)
	{
		return;
	}

	int bIndex = lpObj->TargetNumber;

	if (gObjIsConnectedGP(bIndex) == 0)
	{
		return;
	}

	LPOBJ lpTarget = &gObj[bIndex];

	if (lpTarget->BotType == BOT_TRADER)
	{
		if (lpObj->Interface.use == 0 || lpObj->Interface.type != INTERFACE_TRADE || lpObj->Interface.state == 0)
		{
			return;
		}

		if (lpMsg->flag != 1)
		{
			return;
		}

		gBotTrader.TradeRequest(aIndex, bIndex);

		return;
	}

	if (lpObj->Interface.use == 0 || lpObj->Interface.type != INTERFACE_TRADE || lpObj->Interface.state == 0)
	{
		return;
	}

	if (lpTarget->Interface.use == 0 || lpTarget->Interface.type != INTERFACE_TRADE || lpTarget->Interface.state == 0)
	{
		return;
	}

	if ((GetTickCount() - lpObj->TradeOkTime) < 6000)
	{
		return;
	}

	if (lpMsg->flag == 0 && lpObj->TradeOk != 0)
	{
		lpObj->TradeOk = 0;
	}

	if (lpMsg->flag == 1 && lpObj->TradeOk == 0)
	{
		lpObj->TradeOk = 1;
	}

	this->GCTradeOkButtonSend(bIndex, lpObj->TradeOk);

	if (lpObj->TradeOk == 0 || lpTarget->TradeOk == 0)
	{
		return;
	}



#if(GAMESERVER_UPDATE>=701)

	if (gPentagramSystem.CheckExchangePentagramItem(lpObj) == 0 || gPentagramSystem.CheckExchangePentagramItem(lpTarget) == 0)
	{
		this->ResetTrade(aIndex);
		this->GCTradeResultSend(aIndex, 6);
		this->ResetTrade(bIndex);
		this->GCTradeResultSend(bIndex, 6);
		return;
	}

#endif

	if (gObjCheckMaxMoney(aIndex, lpTarget->TradeMoney) == 0 || gObjCheckMaxMoney(bIndex, lpObj->TradeMoney) == 0)
	{
		this->ResetTrade(aIndex);
		this->GCTradeResultSend(aIndex, 5);
		this->ResetTrade(bIndex);
		this->GCTradeResultSend(bIndex, 5);
		return;
	}

	if (this->ExchangeTradeItem(lpObj, lpTarget) == 0 || this->ExchangeTradeItem(lpTarget, lpObj) == 0)
	{
		this->ResetTrade(aIndex);
		this->GCTradeResultSend(aIndex, 2);
		this->ResetTrade(bIndex);
		this->GCTradeResultSend(bIndex, 2);
		return;
	}

	if (gItemValueTrade.CheckItemValueTrade(lpObj, lpTarget) == 0)
	{
		this->ResetTrade(aIndex);
		this->GCTradeResultSend(aIndex, 2);
		this->ResetTrade(bIndex);
		this->GCTradeResultSend(bIndex, 2);
		return;
	}

#if(GAMESERVER_UPDATE>=701)

	gPentagramSystem.ExchangePentagramItem(lpObj, lpTarget);

	gPentagramSystem.ExchangePentagramItem(lpTarget, lpObj);

#endif

	gObjInventoryCommit(aIndex);

	gItemManager.GCItemListSend(aIndex);

#if(GAMESERVER_UPDATE>=802)

	gEventInventory.GCEventItemListSend(aIndex);

#endif

	gObjectManager.CharacterMakePreviewCharSet(aIndex);

	lpObj->Money -= lpObj->TradeMoney;

	lpObj->Money += lpTarget->TradeMoney;

	GCMoneySend(aIndex, lpObj->Money);

	GDCharacterInfoSaveSend(aIndex);

	this->ExchangeTradeItemLog(lpObj, lpTarget);

	this->ClearTrade(lpObj);

	gObjInventoryCommit(bIndex);

	gItemManager.GCItemListSend(bIndex);

#if(GAMESERVER_UPDATE>=802)

	gEventInventory.GCEventItemListSend(bIndex);

#endif

	gObjectManager.CharacterMakePreviewCharSet(bIndex);

	lpTarget->Money -= lpTarget->TradeMoney;

	lpTarget->Money += lpObj->TradeMoney;

	GCMoneySend(bIndex, lpTarget->Money);

	GDCharacterInfoSaveSend(bIndex);

	this->ExchangeTradeItemLog(lpTarget, lpObj);

	this->ClearTrade(lpTarget);

	lpObj->Interface.use = 0;
	lpObj->Interface.type = INTERFACE_NONE;
	lpObj->Interface.state = 0;
	lpObj->TargetNumber = -1;
	lpObj->TradeOk = 0;
	lpObj->TradeOkTime = 0;
	lpObj->TradeMoney = 0;

	this->GCTradeResultSend(aIndex, 1);

	lpTarget->Interface.use = 0;
	lpTarget->Interface.type = INTERFACE_NONE;
	lpTarget->Interface.state = 0;
	lpTarget->TargetNumber = -1;
	lpTarget->TradeOk = 0;
	lpTarget->TradeOkTime = 0;
	lpTarget->TradeMoney = 0;

	this->GCTradeResultSend(bIndex, 1);
}
#else
void CTrade::CGTradeOkButtonRecv(PMSG_TRADE_OK_BUTTON_RECV* lpMsg, int aIndex) // OK
{

	LPOBJ lpObj = &gObj[aIndex];

	if (gObjIsConnectedGP(aIndex) == 0)
	{
		return;
	}

	int bIndex = lpObj->TargetNumber;
	if (gObjIsConnectedGP(bIndex) == 0)
	{
		return;
	}

	LPOBJ lpTarget = &gObj[bIndex];

	if (lpTarget->BotType == BOT_TRADER)
	{
		if (lpObj->Interface.use == 0 || lpObj->Interface.type != INTERFACE_TRADE || lpObj->Interface.state == 0)
		{
			return;
		}

		if (lpMsg->flag != 1)
		{
			return;
		}

		gBotTrader.TradeRequest(aIndex, bIndex);

		return;
	}

	if (lpObj->Interface.use == 0 || lpObj->Interface.type != INTERFACE_TRADE || lpObj->Interface.state == 0)
	{
		return;
	}

	if (lpTarget->Interface.use == 0 || lpTarget->Interface.type != INTERFACE_TRADE || lpTarget->Interface.state == 0)
	{
		return;
	}

	if ((GetTickCount() - lpObj->TradeOkTime) < 1000)
	{
		return;
	}

	if (lpMsg->flag == 0 && lpObj->TradeOk != 0)
	{
		lpObj->TradeOk = 0;
	}

	if (lpMsg->flag == 1 && lpObj->TradeOk == 0)
	{
		lpObj->TradeOk = 1;
	}

	this->GCTradeOkButtonSend(bIndex, lpObj->TradeOk);

	if (lpObj->TradeOk == 0 || lpTarget->TradeOk == 0)
	{
		return;
	}

	if ((lpObj->DueloEspecial == 1) && (lpTarget->DueloEspecial == 1))
	{
		if ((gTrade.HayItemEnTrade(lpObj) == 1) && (gTrade.HayItemEnTrade(lpTarget) == 0))
		{
			gNotice.GCNoticeSend(lpTarget->Index, 0, 0, 0, 0, 0, 0, gMessage.GetMessage(882));
			return;
		}

		if ((gTrade.HayItemEnTrade(lpObj) == 0) && (gTrade.HayItemEnTrade(lpTarget) == 1))
		{
			gNotice.GCNoticeSend(lpObj->Index, 0, 0, 0, 0, 0, 0, gMessage.GetMessage(882));
			return;
		}

		if (SlotDisponibles(lpObj) == FALSE)
		{
			gNotice.GCNoticeSend(lpObj->Index, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(883));
			return;
		}
		if (SlotDisponibles(lpTarget) == FALSE)
		{
			gNotice.GCNoticeSend(lpTarget->Index, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(883));
			return;
		}
		if ((gTrade.HayItemEnTrade(lpObj) == 1) && (gTrade.HayItemEnTrade(lpTarget) == 1))
		{
			lpObj->DueloConTradeActivo = 1;
			lpTarget->DueloConTradeActivo = 1;
		}
	}

#if(GAMESERVER_UPDATE>=701)

	if (gPentagramSystem.CheckExchangePentagramItem(lpObj) == 0 || gPentagramSystem.CheckExchangePentagramItem(lpTarget) == 0)
	{
		this->ResetTrade(aIndex);
		this->GCTradeResultSend(aIndex, 6);
		this->ResetTrade(bIndex);
		this->GCTradeResultSend(bIndex, 6);
		return;
	}

#endif

	if (gObjCheckMaxMoney(aIndex, lpTarget->TradeMoney) == 0 || gObjCheckMaxMoney(bIndex, lpObj->TradeMoney) == 0)
	{
		this->ResetTrade(aIndex);
		this->GCTradeResultSend(aIndex, 5);
		this->ResetTrade(bIndex);
		this->GCTradeResultSend(bIndex, 5);
		return;
	}
	//ENDTEST

	// ========================================================================================================================

	if ((lpObj->DueloConTradeActivo == 0) && (lpTarget->DueloConTradeActivo == 0))
	{
		if (this->ExchangeTradeItem(lpObj, lpTarget) == 0 || this->ExchangeTradeItem(lpTarget, lpObj) == 0)
		{
			this->ResetTrade(aIndex);
			this->GCTradeResultSend(aIndex, 2);
			this->ResetTrade(bIndex);
			this->GCTradeResultSend(bIndex, 2);
			return;
		}

#if(GAMESERVER_UPDATE>=701)

		gPentagramSystem.ExchangePentagramItem(lpObj, lpTarget);

		gPentagramSystem.ExchangePentagramItem(lpTarget, lpObj);

#endif

		gObjInventoryCommit(aIndex);

		gItemManager.GCItemListSend(aIndex);

#if(GAMESERVER_UPDATE>=802)

		gEventInventory.GCEventItemListSend(aIndex);

#endif

		gObjectManager.CharacterMakePreviewCharSet(aIndex);

		lpObj->Money -= lpObj->TradeMoney;

		lpObj->Money += lpTarget->TradeMoney;

		GCMoneySend(aIndex, lpObj->Money);

		GDCharacterInfoSaveSend(aIndex);

		this->ExchangeTradeItemLog(lpObj, lpTarget);

		this->ClearTrade(lpObj);

		gObjInventoryCommit(bIndex);

		gItemManager.GCItemListSend(bIndex);

#if(GAMESERVER_UPDATE>=802)

		gEventInventory.GCEventItemListSend(bIndex);

#endif

		gObjectManager.CharacterMakePreviewCharSet(bIndex);

		lpTarget->Money -= lpTarget->TradeMoney;

		lpTarget->Money += lpObj->TradeMoney;

		GCMoneySend(bIndex, lpTarget->Money);

		GDCharacterInfoSaveSend(bIndex);

		this->ExchangeTradeItemLog(lpTarget, lpObj);

		this->ClearTrade(lpTarget);
	}

	lpObj->Interface.use = 0;
	lpObj->Interface.type = INTERFACE_NONE;
	lpObj->Interface.state = 0;
	lpObj->TargetNumber = -1;
	lpObj->TradeOk = 0;
	lpObj->TradeOkTime = 0;
	lpObj->TradeMoney = 0;

	this->GCTradeResultSend(aIndex, 1);

	lpTarget->Interface.use = 0;
	lpTarget->Interface.type = INTERFACE_NONE;
	lpTarget->Interface.state = 0;
	lpTarget->TargetNumber = -1;
	lpTarget->TradeOk = 0;
	lpTarget->TradeOkTime = 0;
	lpTarget->TradeMoney = 0;

	this->GCTradeResultSend(bIndex, 1);

	if ((lpObj->DueloConTradeActivo == 1) && (lpTarget->DueloConTradeActivo == 1))
	{
		lpObj->Apuesta = EnDondeEstaElItem(lpObj);
		lpTarget->Apuesta = EnDondeEstaElItem(lpTarget);



		if (CA_MAP_RANGE(lpTarget->Map) != 0 || DS_MAP_RANGE(lpTarget->Map) != 0 || BC_MAP_RANGE(lpTarget->Map) != 0 || CC_MAP_RANGE(lpTarget->Map) != 0 || IT_MAP_RANGE(lpTarget->Map) != 0 || DA_MAP_RANGE(lpTarget->Map) != 0 || DG_MAP_RANGE(lpTarget->Map) != 0 || IG_MAP_RANGE(lpTarget->Map) != 0)
		{
			gNotice.GCNoticeSend(aIndex, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(167));
			gDuel.ResetDuel(lpObj);
			gDuel.ResetDuel(lpTarget);
			gDuel.GCDuelStartSend(bIndex, 0, aIndex);
			return;
		}

#if(GAMESERVER_TYPE==1)

		if (gCastleSiege.GetCastleState() == CASTLESIEGE_STATE_NOTIFY || gCastleSiege.GetCastleState() == CASTLESIEGE_STATE_READYSIEGE || gCastleSiege.GetCastleState() == CASTLESIEGE_STATE_STARTSIEGE)
		{
			gNotice.GCNoticeSend(aIndex, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(168));
			gDuel.ResetDuel(lpObj);
			gDuel.ResetDuel(lpTarget);
			gDuel.GCDuelStartSend(bIndex, 0, aIndex);
			return;
		}

#endif

		char name[11] = { 0 };

		memcpy(name, lpTarget->Name, 10);

		if (strcmp(lpTarget->Name, name) != 0)
		{
			gNotice.GCNoticeSend(aIndex, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(169));
			gDuel.ResetDuel(lpObj);
			gDuel.ResetDuel(lpTarget);
			gDuel.GCDuelStartSend(bIndex, 0, aIndex);
			return;
		}

#if(GAMESERVER_UPDATE>=402)

		if (gDuel.AddDuelArena(lpObj, lpTarget) == 0)
		{
			gNotice.GCNoticeSend(aIndex, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(173));
			gDuel.ResetDuel(lpObj);
			gDuel.ResetDuel(lpTarget);
			gDuel.GCDuelStartSend(bIndex, 0, aIndex);
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

		gDuel.GCDuelStartSend(aIndex, 1, bIndex);

		gDuel.GCDuelStartSend(bIndex, 1, aIndex);

		gDuel.GCDuelScoreSend(aIndex, bIndex);

		return;
	}

	this->ClearTrade(lpTarget);
	this->ClearTrade(lpObj);
	//ENDCUSTOM
}
#endif

#if (DUEL_CUSTOM_APUESTAS == 0)
void CTrade::CGTradeCancelButtonRecv(int aIndex) // OK
{
	LPOBJ lpObj = &gObj[aIndex];

	if (gObjIsConnectedGP(aIndex) == 0)
	{
		return;
	}

	int bIndex = lpObj->TargetNumber;

	if (gObjIsConnectedGP(bIndex) == 0)
	{
		return;
	}

	LPOBJ lpTarget = &gObj[bIndex];

	if (lpTarget->BotType == BOT_TRADER)
	{
		this->ResetTrade(aIndex);
		this->GCTradeResultSend(aIndex, 0);
		return;
	}

	if (lpObj->Interface.use == 0 || lpObj->Interface.type != INTERFACE_TRADE || lpObj->Interface.state == 0)
	{
		return;
	}

	if (lpTarget->Interface.use == 0 || lpTarget->Interface.type != INTERFACE_TRADE || lpTarget->Interface.state == 0)
	{
		return;
	}

	this->ResetTrade(aIndex);
	this->GCTradeResultSend(aIndex, 0);

	this->ResetTrade(bIndex);
	this->GCTradeResultSend(bIndex, 0);
}
#else
void CTrade::CGTradeCancelButtonRecv(int aIndex) // OK
{
	LPOBJ lpObj = &gObj[aIndex];

	if (gObjIsConnectedGP(aIndex) == 0)
	{
		return;
	}


	int bIndex = lpObj->TargetNumber;

	if (gObjIsConnectedGP(bIndex) == 0)
	{
		return;
	}

	LPOBJ lpTarget = &gObj[bIndex];

	if (lpTarget->BotType == BOT_TRADER)
	{
		this->ResetTrade(aIndex);
		this->GCTradeResultSend(aIndex, 0);
		return;
	}

	if (lpObj->Interface.use == 0 || lpObj->Interface.type != INTERFACE_TRADE || lpObj->Interface.state == 0)
	{
		return;
	}

	if (lpTarget->Interface.use == 0 || lpTarget->Interface.type != INTERFACE_TRADE || lpTarget->Interface.state == 0)
	{
		return;
	}
	if ((lpObj->DueloEspecial == 1) && (lpTarget->DueloEspecial == 1))
	{
		if (HayItemEnTrade(lpObj) == 1)
		{
			lpObj->Apuesta = EnDondeEstaElItem(lpObj);
			GDCreateItemSend(lpObj->Index, 0xEB, 0, 0, lpObj->Apuesta->m_Index, lpObj->Apuesta->m_Level, 0, lpObj->Apuesta->m_Option1, lpObj->Apuesta->m_Option2, lpObj->Apuesta->m_Option3, -1, lpObj->Apuesta->m_NewOption, lpObj->Apuesta->m_SetOption, lpObj->Apuesta->m_JewelOfHarmonyOption, 0, lpObj->Apuesta->m_SocketOption, 0xFF, 0);
			gObjFixInventoryPointer(lpObj->Index);
			gObjFixInventoryPointer(lpObj->Index);
			gTrade.ClearTrade(lpObj);
			gTrade.ResetTrade(lpObj->Index);
			lpObj->Apuesta = 0;
		}
		if (HayItemEnTrade(lpTarget) == 1)
		{
			lpTarget->Apuesta = EnDondeEstaElItem(lpTarget);
			GDCreateItemSend(lpTarget->Index, 0xEB, 0, 0, lpTarget->Apuesta->m_Index, lpTarget->Apuesta->m_Level, 0, lpTarget->Apuesta->m_Option1, lpTarget->Apuesta->m_Option2, lpTarget->Apuesta->m_Option3, -1, lpTarget->Apuesta->m_NewOption, lpTarget->Apuesta->m_SetOption, lpTarget->Apuesta->m_JewelOfHarmonyOption, 0, lpTarget->Apuesta->m_SocketOption, 0xFF, 0);
			gObjFixInventoryPointer(lpTarget->Index);
			gObjFixInventoryPointer(lpTarget->Index);
			gTrade.ClearTrade(lpTarget);
			gTrade.ResetTrade(lpTarget->Index);
			lpObj->Apuesta = 0;
		}

		if (CA_MAP_RANGE(lpTarget->Map) != 0 || DS_MAP_RANGE(lpTarget->Map) != 0 || BC_MAP_RANGE(lpTarget->Map) != 0 || CC_MAP_RANGE(lpTarget->Map) != 0 || IT_MAP_RANGE(lpTarget->Map) != 0 || DA_MAP_RANGE(lpTarget->Map) != 0 || DG_MAP_RANGE(lpTarget->Map) != 0 || IG_MAP_RANGE(lpTarget->Map) != 0)
		{
			gNotice.GCNoticeSend(aIndex, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(167));
			gDuel.ResetDuel(lpObj);
			gDuel.ResetDuel(lpTarget);
			gDuel.GCDuelStartSend(bIndex, 0, aIndex);
			return;
		}

#if(GAMESERVER_TYPE==1)

		if (gCastleSiege.GetCastleState() == CASTLESIEGE_STATE_NOTIFY || gCastleSiege.GetCastleState() == CASTLESIEGE_STATE_READYSIEGE || gCastleSiege.GetCastleState() == CASTLESIEGE_STATE_STARTSIEGE)
		{
			gNotice.GCNoticeSend(aIndex, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(168));
			gDuel.ResetDuel(lpObj);
			gDuel.ResetDuel(lpTarget);
			gDuel.GCDuelStartSend(bIndex, 0, aIndex);
			return;
		}

#endif

		char name[11] = { 0 };

		memcpy(name, lpTarget->Name, 10);

		if (strcmp(lpTarget->Name, name) != 0)
		{
			gNotice.GCNoticeSend(aIndex, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(169));
			gDuel.ResetDuel(lpObj);
			gDuel.ResetDuel(lpTarget);
			gDuel.GCDuelStartSend(bIndex, 0, aIndex);
			return;
		}

#if(GAMESERVER_UPDATE>=402)

		if (gDuel.AddDuelArena(lpObj, lpTarget) == 0)
		{
			gNotice.GCNoticeSend(aIndex, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(173));
			gDuel.ResetDuel(lpObj);
			gDuel.ResetDuel(lpTarget);
			gDuel.GCDuelStartSend(bIndex, 0, aIndex);
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

		gDuel.GCDuelStartSend(aIndex, 1, bIndex);

		gDuel.GCDuelStartSend(bIndex, 1, aIndex);

		gDuel.GCDuelScoreSend(aIndex, bIndex);
		lpObj->DueloConTradeActivo = 0;
		lpTarget->DueloConTradeActivo = 0;
		lpObj->DueloEspecial = 0;
		lpTarget->DueloEspecial = 0;

		ClearTrade(lpObj);
		ClearTrade(lpTarget);

		return;
	}
	lpObj->DueloConTradeActivo = 0;
	lpTarget->DueloConTradeActivo = 0;
	lpObj->DueloEspecial = 0;
	lpTarget->DueloEspecial = 0;

	this->ResetTrade(aIndex);
	this->GCTradeResultSend(aIndex, 0);

	this->ResetTrade(bIndex);
	this->GCTradeResultSend(bIndex, 0);
}
#endif

void CTrade::GCTradeRequestSend(int aIndex, char* name) // OK
{
	PMSG_TRADE_REQUEST_SEND pMsg;

	pMsg.header.setE(0x36, sizeof(pMsg));

	memcpy(pMsg.name, name, sizeof(pMsg.name));

	DataSend(aIndex, (BYTE*)&pMsg, pMsg.header.size);
}
#if (DUEL_CUSTOM_APUESTAS == 0)
void CTrade::GCTradeResponseSend(int aIndex, BYTE response, char* name, int level, int GuildNumber) // OK
{
	PMSG_TRADE_RESPONSE_SEND pMsg;

	pMsg.header.set(0x37, sizeof(pMsg));

	pMsg.response = response;

	memcpy(pMsg.name, name, sizeof(pMsg.name));

	pMsg.level = level;

	pMsg.GuildNumber = GuildNumber;

	DataSend(aIndex, (BYTE*)&pMsg, pMsg.header.size);
}
#else
void CTrade::GCTradeResponseSend(int aIndex, BYTE response, char* name, int level, int GuildNumber, int especial) // OK
{

	PMSG_TRADE_RESPONSE_SEND pMsg;

	pMsg.header.set(0x37, sizeof(pMsg));

	pMsg.response = response;

	memcpy(pMsg.name, name, sizeof(pMsg.name));

	pMsg.level = level;

	pMsg.GuildNumber = GuildNumber;

	DataSend(aIndex, (BYTE*)&pMsg, pMsg.header.size);
}
#endif

void CTrade::GCTradeItemDelSend(int aIndex, BYTE slot) // OK
{
	PMSG_TRADE_ITEM_DEL_SEND pMsg;

	pMsg.header.set(0x38, sizeof(pMsg));

	pMsg.slot = slot;

	DataSend(aIndex, (BYTE*)&pMsg, pMsg.header.size);
}

void CTrade::GCTradeItemAddSend(int aIndex, BYTE slot, BYTE* ItemInfo) // OK
{
	PMSG_TRADE_ITEM_ADD_SEND pMsg;

	pMsg.header.set(0x39, sizeof(pMsg));

	pMsg.slot = slot;

	memcpy(pMsg.ItemInfo, ItemInfo, sizeof(pMsg.ItemInfo));

	DataSend(aIndex, (BYTE*)&pMsg, pMsg.header.size);
}

void CTrade::GCTradeMoneySend(int aIndex, DWORD money) // OK
{
	PMSG_TRADE_MONEY_SEND pMsg;

	pMsg.header.set(0x3B, sizeof(pMsg));

	pMsg.money = money;

	DataSend(aIndex, (BYTE*)&pMsg, pMsg.header.size);
}

void CTrade::GCTradeOkButtonSend(int aIndex, BYTE flag) // OK
{
	PMSG_TRADE_OK_BUTTON_SEND pMsg;

	pMsg.header.set(0x3C, sizeof(pMsg));

	pMsg.flag = flag;

	DataSend(aIndex, (BYTE*)&pMsg, pMsg.header.size);
}

void CTrade::GCTradeResultSend(int aIndex, BYTE result) // OK
{
	PMSG_TRADE_RESULT_SEND pMsg;

	pMsg.header.set(0x3D, sizeof(pMsg));

	pMsg.result = result;

	DataSend(aIndex, (BYTE*)&pMsg, pMsg.header.size);
}

#if (DUEL_CUSTOM_APUESTAS == 1)
void CTrade::GCTradeResponseSendCUSTOM(int aIndex, BYTE response, char* name, int level, int GuildNumber, int especial) // OK
{
	PMSG_TRADE_RESPONSE_SEND pMsg;

	pMsg.header.set(0x37, sizeof(pMsg));

	pMsg.response = response;

	memcpy(pMsg.name, name, sizeof(pMsg.name));

	pMsg.level = level;

	pMsg.GuildNumber = GuildNumber;

	DataSend(aIndex, (BYTE*)&pMsg, pMsg.header.size);
}

void CTrade::CGTradeResponseRecvCUSTOM(PMSG_DUEL_OK_RECV_CUSTOM* lpMsg, int aIndex) // OK
{

	LPOBJ lpObj = &gObj[aIndex];

	if (gObjIsConnectedGP(aIndex) == 0)
	{
		return;
	}

	int bIndex = lpObj->TargetNumber;

	if (gObjIsConnectedGP(bIndex) == 0)
	{
		return;
	}

	LPOBJ lpTarget = &gObj[bIndex];

	if (lpObj->Interface.use == 0 || lpObj->Interface.type != INTERFACE_TRADE || lpObj->Interface.state != 0)
	{
		return;
	}

	if (lpTarget->Interface.use == 0 || lpTarget->Interface.type != INTERFACE_TRADE || lpTarget->Interface.state != 0)
	{
		return;
	}

	if (CA_MAP_RANGE(lpTarget->Map) != 0 || DS_MAP_RANGE(lpTarget->Map) != 0 || BC_MAP_RANGE(lpTarget->Map) != 0 || CC_MAP_RANGE(lpTarget->Map) != 0 || IT_MAP_RANGE(lpTarget->Map) != 0 || DA_MAP_RANGE(lpTarget->Map) != 0 || DG_MAP_RANGE(lpTarget->Map) != 0 || IG_MAP_RANGE(lpTarget->Map) != 0)
	{
		goto CLEAR_JUMP;
	}

	if (lpObj->X < (lpTarget->X - 2) || lpObj->X >(lpTarget->X + 2) || lpObj->Y < (lpTarget->Y - 2) || lpObj->Y >(lpTarget->Y + 2))
	{
		goto CLEAR_JUMP;
	}

	if (lpObj->PShopOpen != 0 || lpTarget->PShopOpen != 0)
	{
		goto CLEAR_JUMP;
	}
#if(GAMESERVER_UPDATE > 401)
	if (lpMsg->response == 0)
	{
		goto CLEAR_JUMP;
	}
#endif

	gObjFixInventoryPointer(aIndex);

	if (lpObj->Transaction == 1)
	{
		goto CLEAR_JUMP;
	}

	if (gObjInventoryTransaction(aIndex) == 0 || gObjInventoryTransaction(bIndex) == 0)
	{
		goto CLEAR_JUMP;
	}

	this->ClearTrade(lpObj);

	lpObj->Interface.use = 1;
	lpObj->Interface.type = INTERFACE_TRADE;
	lpObj->Interface.state = 1;
	lpObj->TradeOk = 0;
	lpObj->TradeOkTime = 0;
	lpObj->TradeMoney = 0;
	if (lpObj->DueloEspecial == 0)
	{

		this->GCTradeResponseSend(aIndex, 1, lpTarget->Name, lpTarget->Level, lpTarget->GuildNumber, 0);
	}
	else if (lpObj->DueloEspecial == 1)
	{

		this->GCTradeResponseSend(aIndex, 1, lpTarget->Name, lpTarget->Level, lpTarget->GuildNumber, 1);
	}

	this->ClearTrade(lpTarget);

	lpTarget->Interface.use = 1;
	lpTarget->Interface.type = INTERFACE_TRADE;
	lpTarget->Interface.state = 1;
	lpTarget->TradeOk = 0;
	lpTarget->TradeOkTime = 0;
	lpTarget->TradeMoney = 0;
	if (lpTarget->DueloEspecial == 0)
	{

		this->GCTradeResponseSend(bIndex, 1, lpObj->Name, lpObj->Level, lpObj->GuildNumber, 0);
	}
	else if (lpTarget->DueloEspecial == 1)
	{
		this->GCTradeResponseSend(bIndex, 1, lpObj->Name, lpObj->Level, lpObj->GuildNumber, 1);
	}
	return;

CLEAR_JUMP:

	gObjInventoryCommit(aIndex);

	lpObj->Interface.use = 0;
	lpObj->Interface.type = INTERFACE_NONE;
	lpObj->Interface.state = 0;
	lpObj->TargetNumber = -1;

	this->GCTradeResponseSend(aIndex, 0, lpTarget->Name, 0, 0, 0);

	gObjInventoryCommit(bIndex);

	lpTarget->Interface.use = 0;
	lpTarget->Interface.type = INTERFACE_NONE;
	lpTarget->Interface.state = 0;
	lpTarget->TargetNumber = -1;
	this->GCTradeResponseSend(bIndex, 0, lpObj->Name, 0, 0, 0);
}

bool CTrade::SlotDisponibles(LPOBJ lpObj)
{
	for (int n = 44; n<74; n++)
	{
		if (lpObj->Inventory[n].IsItem())
		{
			return false;
		}
	}
	return true;

}

bool CTrade::HayItemEnTrade(LPOBJ lpObj)
{
	for (int n = 0; n < 32; n++)
	{
		if (lpObj->Trade[n].IsItem())
		{
			return 1;
		}
	}
	return 0;
}

CItem* CTrade::EnDondeEstaElItem(LPOBJ lpObj)
{
	for (int n = 0; n < 32; n++)
	{
		if (lpObj->Trade[n].IsItem())
		{
			CItem* item = &lpObj->Trade[n];
			return item;
		}
	}
	return 0;
}
#endif