#pragma once

#if (JEWEL_BANK == 1)

#include "stdafx.h"
#include "protocol.h"

struct PMSG_JEWELBANK
{
	PSBMSG_HEAD h;
	int Result;
};

struct PMSG_JEWELSBANK
{
#pragma pack(1)
	PSBMSG_HEAD h;
#if (JEWEL_BANK == 1)
	int Zen;
	int Chaos;
	int Bless;
	int Soul;
	int Life;
	int CreateonBank;
	int GuardianBank;
	int HarmonyBank;
	int LowStoneBank;
	int HighStoneBank;
	int GemStoneBank;
#endif
#pragma pack()
};


class JewelsBank
{
public:
	bool Active;
	void JewelsBankLoad();
	void Bind();
	void DrawItem(int ItemType, int ItemIndex, int ItemLevel);
	void Draw();
	void DrawLine(int ItemType, int ItemIndex, int ItemLevel, float DrawX, float DrawY, char * ItemName, int Count);
	void DrawInfo(float InfoDrawX, float InfoDrawY, char* Text, bool Type, int Count);
	bool EventJewelBank_Close(DWORD Event);
	void Button(DWORD key);
	void Packet(int number);
	void RecibirJewelsBank(PMSG_JEWELSBANK * aRecv);
};
extern JewelsBank gJewelsBank;


//void JewelsBankRecv(EXINFO_UPDATE* aRecv);

#endif