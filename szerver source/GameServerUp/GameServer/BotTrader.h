// BotTrader.h: interface for the CBotTrader class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#define MAX_BOT_TRADER 30


struct BOT_TRADER_ITEM_INFO
{
	int Slot;
	int Index;
	int Level;
};

struct BOT_TRADER_ITEM_RATE_INFO
{
	int MinRate;
	int MaxRate;
	int Index;
	int Durability;
	int Option0;
	int Option1;
	int Option2;
	int Option3;
	int Option4;
	int Option5;
	int Option6;
	int Duration;
	int Rate;
};

struct BOT_TRADER_INFO
{
	int Id;
	int Class;
//	int Evo;
	int PKLevel;
	int Map;
	int PosX;
	int PosY;
	int Dir;
	char Name[11];
	std::vector<BOT_TRADER_ITEM_INFO> ItemList;
	std::vector<BOT_TRADER_ITEM_RATE_INFO> ItemRateInfo;
	int MobIndex;
};

class CBotTrader
{
public:
	CBotTrader();
	virtual ~CBotTrader();
	void Load(char* path);
	void SetInfo(BOT_TRADER_INFO info);
	void BotSpawn();
	bool BotTalk(int aIndex, int bIndex);
	void TradeRequest(int aIndex,int bIndex);
private:
	int m_IncreaseRateChaos;
	int m_IncreaseRateBless;
	int m_IncreaseRateSoul;
	int m_IncreaseRateLife;
	int m_IncreaseRateCreation;
	std::map<int, BOT_TRADER_INFO> m_BotTraderInfo;
};

extern CBotTrader gBotTrader;