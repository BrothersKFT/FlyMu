#pragma once
// -------------------------------------------------------------------------------

#include "Protocol.h"
#include "defines.h"
#include "Interface.h"
// -------------------------------------------------------------------------------

#define	RESET_DEBUG			0
#define	MAX_RESET_GROUP		500
#define	MAX_RESET_MONEY		1500000000
#define MAX_RESET_ITEM		5
#define CHECK_RESET_INV		1
// -------------------------------------------------------------------------------

struct RESET_REQ_USERDATA
{
	PSBMSG_HEAD h;
};

struct RESET_RESULT_SEND
{
	PSBMSG_HEAD h;
	BYTE result;
};


// -------------------------------------------------------------------------------

struct RESET_ITEM_DATA
{
	WORD	ID;
	BYTE	MinLevel;
	BYTE	MaxLevel;
	BYTE	MinOption;
	BYTE	MaxOption;
	BYTE	IsLuck;
	BYTE	IsSkill;
	BYTE	IsExcellent;
	BYTE	IsAncient;
	BYTE	IsSocket;
	int		Count;
};
// -------------------------------------------------------------------------

struct RESET_REWARD_DATA
{
	int		LevelPoint;
	int		GensPoint;
	int		WCoinC;
	int		WCoinP;
	int		GoblinPoint;
	int		Credits;
};
// -------------------------------------------------------------------------

struct RESET_GROUP_DATA
{
	int		MinReset;
	int		MaxReset;
	int		MinGReset;
	int		MaxGReset;
	int		ReqLevel[MAX_ACCOUNT_LEVEL];
	int		ReqMoney[MAX_ACCOUNT_LEVEL];
	int		ItemCount;
	RESET_ITEM_DATA		ItemData[MAX_RESET_ITEM];
	RESET_REWARD_DATA	RewardData[7];
};
// -------------------------------------------------------------------------

struct RESET_ITEM_REWARD_ITEM
{
	WORD	ID;
	BYTE	MinLevel;
	BYTE	MaxLevel;
	BYTE	MinOption;
	BYTE	MaxOption;
	BYTE	IsLuck;
	BYTE	IsSkill;
	BYTE	ExcType;
	BYTE	MinExcOption;
	BYTE	MaxExcOption;
	BYTE	ExcCode;
	BYTE	IsAncient;
	BYTE	IsSocket;
	int		Count;
};


struct RESET_ITEM_REWARD
{
	int		Money;
	int		WCoinC;
	int		WCoinP;
	int		WCoinG;
	int		Credits;
	int		ItemCount;
	RESET_ITEM_REWARD_ITEM itemData[5];
};
// -------------------------------------------------------------------------

struct RESET_CURRENT_DATA
{
	int MinReset;
	int MaxReset;
	int MinGReset;
	int MaxGReset;
	int ReqLevel;
	int ItemCount;
	bool UseItemReward;
	RESET_ITEM_DATA		ItemData[MAX_RESET_ITEM];
	RESET_ITEM_REWARD	ItemReward;
	RESET_REWARD_DATA RewardData;
};
// -------------------------------------------------------------------------------

struct RESET_ANS_USERDATA
{
	PSWMSG_HEAD h;
	bool		ByDialog;
	int			Reset;
	int			GrandReset;
	int			ResetMoney;
	int			CommandPerReset;
	int			QuestStat;
	RESET_CURRENT_DATA ResetData;
	bool		ItemCheck[MAX_RESET_ITEM];
};

class ResetSystem
{
public:
	ResetSystem();
	virtual ~ResetSystem();
	// ----
	void draw_reset_system();
	bool		EventResetWindow_Main(DWORD Event);
	bool		EventResetWindow_Close(DWORD Event);
	bool		EventResetWindow_Finish(DWORD Event);
	int	get_reset_money() const;
	bool check_all_req() const;
	// ----
	static void reset_message_recv(RESET_RESULT_SEND* lpMsg);
	void set_data(RESET_ANS_USERDATA* lpMsg);
	void req_reset_finish();
	void get_reset_result();
	int	 get_reward_points() const;
	void SwitchStatsWindowState() { (gInterface.Data[OBJECT_RESET_MAIN].OnShow == true) ? gInterface.Data[OBJECT_RESET_MAIN].CloseAnimated(15) : gInterface.Data[OBJECT_RESET_MAIN].Open(-226, 20); };
	// ----
	int		m_GroupLoadedCount;
	RESET_GROUP_DATA	m_GroupData[MAX_RESET_GROUP];
	RESET_CURRENT_DATA m_ResetData;
	DWORD ResetMoney;
	int m_BonusCommand;
	// ----
}; extern ResetSystem gResetSystem;
// -------------------------------------------------------------------------------