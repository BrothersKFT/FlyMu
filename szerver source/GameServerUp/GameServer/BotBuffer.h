// BotBuffer.h: interface for the CBotBuffer class.
//
//////////////////////////////////////////////////////////////////////

#pragma once
#define MAX_BOT_BUFFER 30


struct BOT_BUFFER_ITEM_INFO
{
	int Slot;
	int Index;
	int Level;
};

struct BOT_BUFFER_BUFF_INFO
{
	int Index;
	int Power[3];
	int Duration;
};

struct BOT_BUFFER_INFO
{
	int Id;
	int Class;
	int PKLevel;
	//	int Evo;
	int Map;
	int PosX;
	int PosY;
	int Dir;
	char Name[11];
	std::vector<BOT_BUFFER_ITEM_INFO> ItemList;
	std::vector<BOT_BUFFER_BUFF_INFO> BuffList;
	int MobIndex;
};

class CBotBuffer
{
public:
	CBotBuffer();
	virtual ~CBotBuffer();
	void Load(char* path);
	void SetInfo(BOT_BUFFER_INFO info);
	void BotSpawn();
	bool BotTalk(int aIndex, int bIndex);
private:
	std::map<int, BOT_BUFFER_INFO> m_BotBufferInfo;
};

extern CBotBuffer gBotBuffer;