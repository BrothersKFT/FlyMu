// CustomPet.h: interface for the CLuckyWheel class.
//
//////////////////////////////////////////////////////////////////////

#pragma once
#if (LUCKYWHEEL == 1)
#include "Item.h"
#include "User.h"
#include "Protocol.h"

#define MAX_LUCKYWHEEL_ITEM 12

struct LUCKYWHEEL_INFO
{
	int Index;
	int ItemType;
	int ItemIndex;
	int Level;
	int Luck;
	int Skill;
	int Option;
	int Exc;
};

struct ITEM_WIN_SEND
{
	PSBMSG_HEAD header;
	int	number;
};

struct PMSG_LUCKY_WHEEL
{
#pragma pack(1)
	PSBMSG_HEAD h;
	int CostWcoinC;
	int CostWcoinP;
	int CostGoblin;
#pragma pack()
};

class CLuckyWheel
{
public:
	CLuckyWheel();
	virtual ~CLuckyWheel();
	void Init();
	void Load(char* File);
	void SetInfo(LUCKYWHEEL_INFO info);
	void Start(LPOBJ lpUser);
	int WcoinLucky;
	int WcoinPLucky;
	int goblinCoinLucky;
	void EnvioCostoWheel(int aIndex);
public:
	LUCKYWHEEL_INFO m_LuckyWheelInfo[MAX_LUCKYWHEEL_ITEM];
};

extern CLuckyWheel gLuckyWheel;
#endif