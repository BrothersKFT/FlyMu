#pragma once

#if (HPTYPE == 1)
#pragma once

#define MAX_MAIN_VIEWPORT 400
#define RGBTOGLFLOAT(x) ((float)x/255.0f)
#define FLOATTORGB(x)	((float)x*255)
#define ABS(x) (((x) < 0) ? (-(x)) : (x))
#include "Protocol.h"

struct NEW_HEALTH_BAR
{
	WORD index;
	BYTE type;
	BYTE rate;
	WORD monsterid;
	float Life;
	float MaxLife;
	short Level;
	int Reset;
	int Shield;
	int MaxShield;
	BYTE SDrate;
	bool isSameGuild;
	bool HaveGuild;
	char GuildName[11];
	BYTE Mark[64];
	//BYTE Rank;
};

void ClearNewHealthBar();
void InsertNewHealthBar(PMSG_NEW_HEALTH_RECV* lpInfo);
NEW_HEALTH_BAR* GetNewHealthBar(WORD index, BYTE type);
//void DrawNewHealthBar();
void DrawHealthBar();
bool IsPartyMember(int ViewportID);

void AllInOne();

#else

#define MAX_MAIN_VIEWPORT 400

struct NEW_HEALTH_BAR
{
	WORD index;
	BYTE type;
	BYTE rate;
	BYTE rate2;
};

void ClearNewHealthBar();
void InsertNewHealthBar(WORD index, BYTE type, BYTE rate, BYTE rate2);
NEW_HEALTH_BAR* GetNewHealthBar(WORD index, BYTE type);
void DrawNewHealthBar();
#endif