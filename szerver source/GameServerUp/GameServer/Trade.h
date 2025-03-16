// Trade.h: interface for the CTrade class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "ItemManager.h"
#include "Protocol.h"
#if (DUEL_CUSTOM_APUESTAS == 1)
#include "Duel.h"
#endif

#define MAX_TRADE_MONEY 1000000000

//**********************************************//
//************ Client -> GameServer ************//
//**********************************************//

struct PMSG_TRADE_REQUEST_RECV
{
	PBMSG_HEAD header; // C1:36
	BYTE index[2];
};

struct PMSG_TRADE_RESPONSE_RECV
{
	PBMSG_HEAD header; // C1:37
	BYTE response;
	char name[10];
	WORD level;
	DWORD GuildNumber;
};

struct PMSG_TRADE_MONEY_RECV
{
	PBMSG_HEAD header; // C1:3B
	DWORD money;
};

struct PMSG_TRADE_OK_BUTTON_RECV
{
	PBMSG_HEAD header; // C1:3C
	BYTE flag;
};

//**********************************************//
//************ GameServer -> Client ************//
//**********************************************//

struct PMSG_TRADE_REQUEST_SEND
{
	PBMSG_HEAD header; // C3:36
	char name[10];
};

struct PMSG_TRADE_RESPONSE_SEND
{
	PBMSG_HEAD header; // C1:37
	BYTE response;
	char name[10];
	WORD level;
	DWORD GuildNumber;
};

struct PMSG_TRADE_ITEM_DEL_SEND
{
	PBMSG_HEAD header; // C1:38
	BYTE slot;
};

struct PMSG_TRADE_ITEM_ADD_SEND
{
	PBMSG_HEAD header; // C1:39
	BYTE slot;
	BYTE ItemInfo[MAX_ITEM_INFO];
};

struct PMSG_TRADE_MONEY_SEND
{
	PBMSG_HEAD header; // C1:3B
	DWORD money;
};

struct PMSG_TRADE_OK_BUTTON_SEND
{
	PBMSG_HEAD header; // C1:3C
	BYTE flag;
};

struct PMSG_TRADE_RESULT_SEND
{
	PBMSG_HEAD header; // C1:[3A:3D]
	BYTE result;
};

//**********************************************//
//**********************************************//
//**********************************************//

class CTrade
{
public:
	CTrade();
	virtual ~CTrade();
	void ClearTrade(LPOBJ lpObj);
	void ResetTrade(int aIndex);
	bool ExchangeTradeItem(LPOBJ lpObj, LPOBJ lpTarget);
	void ExchangeTradeItemLog(LPOBJ lpObj, LPOBJ lpTarget);
	void CGTradeRequestRecv(PMSG_TRADE_REQUEST_RECV* lpMsg, int aIndex);
	void CGTradeResponseRecv(PMSG_TRADE_RESPONSE_RECV* lpMsg, int aIndex);
	void CGTradeMoneyRecv(PMSG_TRADE_MONEY_RECV* lpMsg, int aIndex);
	void CGTradeOkButtonRecv(PMSG_TRADE_OK_BUTTON_RECV* lpMsg, int aIndex);
	void CGTradeCancelButtonRecv(int aIndex);
	void GCTradeRequestSend(int aIndex, char* name);
#if (DUEL_CUSTOM_APUESTAS == 0)
	void GCTradeResponseSend(int aIndex, BYTE response, char* name, int level, int GuildNumber);
#endif
	void GCTradeItemDelSend(int aIndex, BYTE slot);
	void GCTradeItemAddSend(int aIndex, BYTE slot, BYTE* ItemInfo);
	void GCTradeMoneySend(int aIndex, DWORD money);
	void GCTradeOkButtonSend(int aIndex, BYTE flag);
	void GCTradeResultSend(int aIndex, BYTE result);
#if (DUEL_CUSTOM_APUESTAS == 1)
	void GCTradeResponseSend(int aIndex, BYTE response, char* name, int level, int GuildNumber, int especial);
	void GCTradeResponseSendCUSTOM(int aIndex, BYTE response, char* name, int level, int GuildNumber, int especial); //CUSTOM
	void CGTradeResponseRecvCUSTOM(PMSG_DUEL_OK_RECV_CUSTOM* lpMsg, int aIndex); //CUSTOM
	bool HayItemEnTrade(LPOBJ lpObj); //CUSTOM
	CItem* EnDondeEstaElItem(LPOBJ lpObj); //CUSTOM
	bool SlotDisponibles(LPOBJ lpObj);
#endif
};

extern CTrade gTrade;
