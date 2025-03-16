#pragma once
#include "Protocol.h"

#define MAX_RUUDTOKENSELL_INFO		25
#define CursorPress					*(BYTE*)0x8793386
#define MAX_ITEM_INFO 12

//**********************************************//
//************ GameServer -> Client ************//
//**********************************************//

struct PMSG_RUUD_ITEM_LIST_RECV
{
	PWMSG_HEAD header; // C2:31
	BYTE type;
	BYTE count;
};

struct PMSG_RUUD_ITEM_LIST
{
	BYTE slot;
	DWORD dwRuudSell;
	BYTE ItemInfo[MAX_ITEM_INFO];
};

//**********************************************//
//************ Client -> GameServer ************//
//**********************************************//

struct PMSG_BUY_ITEMRUUD_SEND
{
	PBMSG_HEAD header; // EE:30
	BYTE PAGE;
	BYTE SLOT;
};

struct JCCoord
{
	int X;
	int Y;
};

#define JCConvertByteItem ((int (__thiscall*)(int a1, void *lp)) 0x7E1B10)
#define sub_7E3E30 ((signed int (__thiscall*)(int a1, JCCoord a5, int a6, int a7, int a8, int a9)) 0x007E3E30)


class cRenderRuud
{
public:
	cRenderRuud();
	virtual ~cRenderRuud();
	float JCMoveX; // ST08_4@1
	float JCMoveY; // ST04_4@1
public:
	bool isOpen();
	int CheckTimer;
	int Coordenada[3];
	bool OpeningRuud;
	bool OpenWindowConfirm;
	int JCSlot;
	int JCPage;
	void OpenRuud();
	void ClosedRuud();
	void CheckOpen();
	DWORD TimerEvent;
	bool EventPressButton(int x, int y, int w, int h);
public:
	bool CheckMouseOver();
	void MoverWinRuud(int x, int y);
	void WindowConfirm(int Page, int Slot);
	void ClearRuudInfo();
	void InsertRuudInfo(PMSG_RUUD_ITEM_LIST* lpInfo);
	void LoadRuudShop_Recv(PMSG_RUUD_ITEM_LIST_RECV * lpMsg);
	void OpenRuudShop_Recv(PMSG_NPC_TALK_RECV * lpMsg);
	PMSG_RUUD_ITEM_LIST * JCGetInfoRuud(int Page, int Slot);
public:
	int Enter;
	int Page;
	PMSG_RUUD_ITEM_LIST m_RuudInfo[MAX_RUUDTOKENSELL_INFO];
};

extern cRenderRuud jCRenderRuud;