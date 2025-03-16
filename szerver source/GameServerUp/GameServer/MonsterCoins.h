#pragma once
#if (MONSTER_COINS==1)
// -------------------------------------------------------------------------------

#define MAX_SHOPPOINTEX_EVENT		7
#define MAX_SHOPPOINTEX_MONSTER		1024
#include "User.h"
// -------------------------------------------------------------------------------

// -------------------------------------------------------------------------------

// -------------------------------------------------------------------------------

struct SHOPPOINTEX_MONSTER
{
	DWORD	MonsterID;
	int		MapNumber;
	int		AddCoinC;
	int		AddCoinP;
	int		AddCoinG;
	int		AddRuud;
	// ----
	SHOPPOINTEX_MONSTER()
	{
		ZeroMemory(this, sizeof(*this));
	}
};
// -------------------------------------------------------------------------------

class ShopPointEx
{
public:
	ShopPointEx();
	~ShopPointEx();
	// ----
	void	Init();
	void	Load(char* path);
	// ----
	int		GetMonsterSlot(int Class, int Map);
	// ----
	void	AddMonsterBonus(LPOBJ lpObj, LPOBJ lpTarget);
	// ----
public:
	bool	m_IsLoaded;
	int		m_MonsterLoaded;
	// ----
	std::vector<SHOPPOINTEX_MONSTER> m_MobsData;
	// ----
}; extern ShopPointEx gShopPointEx;
// -------------------------------------------------------------------------------
#endif