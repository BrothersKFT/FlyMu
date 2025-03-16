// CustomPet.h: interface for the CLuckyWheel class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "Protocol.h"

#define MAX_ITEM 12

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
	void Load(LUCKYWHEEL_INFO* info);
	void SetInfo(LUCKYWHEEL_INFO info);
	void Start(int aIndex);
	void RecibirCostoWheel(PMSG_LUCKY_WHEEL * aRecv);
	int CostWcoinC;
	int CostWcoinP;
	int CostGoblin;
public:
	LUCKYWHEEL_INFO m_LuckyWheelInfo[MAX_ITEM];
};

extern CLuckyWheel gLuckyWheel;
