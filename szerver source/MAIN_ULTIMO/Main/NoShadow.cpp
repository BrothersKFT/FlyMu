#include "stdafx.h"
#include "NoShadow.h"
#include "Defines.h"

cNoShadow gNoShadow;

cNoShadow::cNoShadow() // OK
{
	this->Init();
}

cNoShadow::~cNoShadow() // OK
{

}

void cNoShadow::Init() // OK
{
	for (int n = 0; n < MAX_NO_SHADOW; n++)
	{
		this->m_NoShadowInfo[n].Index = -1;
	}
}

void cNoShadow::Load(ITEM_NO_SHADOW_INFO* info) // OK
{
	for (int n = 0; n < MAX_NO_SHADOW; n++)
	{
		this->SetInfo(info[n]);

	}

}

void cNoShadow::SetInfo(ITEM_NO_SHADOW_INFO info) // OK
{
	if (info.Index < 0 || info.Index >= MAX_NO_SHADOW)
	{
		return;
	}

	this->m_NoShadowInfo[info.Index] = info;
}

ITEM_NO_SHADOW_INFO* cNoShadow::GetInfo(int index) // OK
{
	if (index < 0 || index >= MAX_NO_SHADOW)
	{
		return 0;
	}

	if (this->m_NoShadowInfo[index].Index != index)
	{
		return 0;
	}

	return &this->m_NoShadowInfo[index];
}

ITEM_NO_SHADOW_INFO* cNoShadow::GetInfoByItem(int ItemIndex) // OK
{
	for (int n = 0; n < MAX_NO_SHADOW; n++)
	{
		ITEM_NO_SHADOW_INFO* lpInfo = this->GetInfo(n);

		if (lpInfo == 0)
		{
			continue;
		}

		if (ItemIndex == ITEM2(lpInfo->ItemType, lpInfo->ItemIndex))
		{
			return lpInfo;
		}
	}

	return 0;
}

bool cNoShadow::CheckEffectRemake(int ItemIndex){

	for (int i = 0; i<20; i++)
	{

		if (ItemIndex == ITEM2(m_NoShadowInfo[i].ItemType, m_NoShadowInfo[i].ItemIndex))
		{
			return true;
		}
	}
	return false;
}