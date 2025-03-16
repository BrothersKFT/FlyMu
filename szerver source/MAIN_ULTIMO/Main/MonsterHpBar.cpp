#include "stdafx.h"
#include "MonsterHpBar.h"


MonsterHpBar gMonsterHpBar;

MonsterHpBar::MonsterHpBar()
{
	this->Init();
}

MonsterHpBar::~MonsterHpBar()
{

}

void MonsterHpBar::Init()
{
	for (int n = 0; n < MAX_CUSTOM_HPBAR; n++)
	{
		this->m_CustomHpBar[n].Index = -1;
	}
}

void MonsterHpBar::Load(CUSTOM_HPBAR* info) // OK
{
	for (int n = 0; n < MAX_CUSTOM_HPBAR; n++)
	{
		this->SetInfo(info[n]);
	}
}

void MonsterHpBar::SetInfo(CUSTOM_HPBAR info) // OK
{
	if (info.Index < 0 || info.Index >= MAX_CUSTOM_HPBAR)
	{
		return;
	}

	this->m_CustomHpBar[info.Index] = info;

}

CUSTOM_HPBAR* MonsterHpBar::GetHpBar(int MosnterID) // OK
{
	for (int n = 0; n < MAX_CUSTOM_HPBAR; n++)
	{
		CUSTOM_HPBAR* lpInfo = this->GetHpBarByIndex(n);

		if (lpInfo == 0)
		{
			continue;
		}

		if (lpInfo->MonsterID == MosnterID)
		{
			return lpInfo;
		}
	}

	return 0;
}


CUSTOM_HPBAR* MonsterHpBar::GetHpBarByIndex(int index) // OK
{
	if (index < 0 || index >= MAX_CUSTOM_HPBAR)
	{
		return 0;
	}

	if (this->m_CustomHpBar[index].Index != index)
	{
		return 0;
	}

	return &this->m_CustomHpBar[index];
}