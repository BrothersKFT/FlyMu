#include "StdAfx.h"
#if (MONSTER_COINS==1)
#include "MonsterCoins.h"
#include "user.h"
#include "MemScript.h"
#include "Util.h"
#include "CashShop.h"
#include "Monster.h"
#include "Notice.h"
#include "DSProtocol.h"
#include "Message.h"
// -------------------------------------------------------------------------------
ShopPointEx gShopPointEx;
// -------------------------------------------------------------------------------

ShopPointEx::ShopPointEx()
{
	this->Init();
}
// -------------------------------------------------------------------------------

ShopPointEx::~ShopPointEx()
{
	// ----
}
// -------------------------------------------------------------------------------

void ShopPointEx::Init()
{
	this->m_IsLoaded = false;
	this->m_MonsterLoaded = 0;
	// ----
	this->m_MobsData.clear();
}
// -------------------------------------------------------------------------------

void ShopPointEx::Load(char* path)
{
	CMemScript* lpMemScript = new CMemScript;

	if (lpMemScript == 0)
	{
		ErrorMessageBox(MEM_SCRIPT_ALLOC_ERROR, path);
		return;
	}

	if (lpMemScript->SetBuffer(path) == 0)
	{
		ErrorMessageBox(lpMemScript->GetLastError());
		delete lpMemScript;
		return;
	}

	this->Init();

	try
	{
		while (true)
		{
			if (lpMemScript->GetToken() == TOKEN_END)
			{
				break;
			}

			int section = lpMemScript->GetNumber();

			while (true)
			{
				if (section == 0)
				{
					if (strcmp("end", lpMemScript->GetAsString()) == 0)
					{
						break;
					}

					SHOPPOINTEX_MONSTER info;

					info.MonsterID = lpMemScript->GetNumber();

					info.MapNumber = lpMemScript->GetAsNumber();

					info.AddCoinC = lpMemScript->GetAsNumber();
					info.AddCoinP = lpMemScript->GetAsNumber();
					info.AddCoinG = lpMemScript->GetAsNumber();
					info.AddRuud = lpMemScript->GetAsNumber();

					this->m_MobsData.push_back(info);
				}
				else
				{
					break;
				}
			}
		}
	}
	catch (...)
	{
		ErrorMessageBox(lpMemScript->GetLastError());
	}

	delete lpMemScript;
	this->m_IsLoaded = true;
}
// -------------------------------------------------------------------------------

int ShopPointEx::GetMonsterSlot(int Class, int Map)
{
	for (int i = 0; i < this->m_MobsData.size(); i++)
	{
		if (this->m_MobsData[i].MonsterID != Class)
		{
			continue;
		}
		// ----
		if (this->m_MobsData[i].MapNumber != Map && this->m_MobsData[i].MapNumber != -1)
		{
			continue;
		}
		// ----
		return i;
	}
	// ----
	return -1;
}
// -------------------------------------------------------------------------------

void ShopPointEx::AddMonsterBonus(LPOBJ lpMonster, LPOBJ lpObj)
{
	if (!this->m_IsLoaded)
	{
		return;
	}
	// ----
	int MonsterSlot = this->GetMonsterSlot(gObj[lpMonster->Index].Class, gObj[lpMonster->Index].Map);
	// ----
	if (MonsterSlot == -1)
	{
		return;
	}

	int aIndex = gObjMonsterGetTopHitDamageUser(lpObj);

	if (OBJECT_RANGE(aIndex) != 0)
	{
		lpObj = &gObj[aIndex];
	}
	// ----
	GDSetCoinSend(lpObj->Index, this->m_MobsData[MonsterSlot].AddCoinC, this->m_MobsData[MonsterSlot].AddCoinP, this->m_MobsData[MonsterSlot].AddCoinG, this->m_MobsData[MonsterSlot].AddRuud, "Monster Coins");
	// ----
}
// -------------------------------------------------------------------------------
#endif