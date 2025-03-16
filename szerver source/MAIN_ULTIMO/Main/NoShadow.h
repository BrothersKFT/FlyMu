#pragma once

#define MAX_NO_SHADOW 300

struct ITEM_NO_SHADOW_INFO
{
	int Index;
	int ItemType;
	int ItemIndex;
};

class cNoShadow
{
public:
	cNoShadow();
	virtual ~cNoShadow();
	void Init();
	void Load(ITEM_NO_SHADOW_INFO* info);
	void SetInfo(ITEM_NO_SHADOW_INFO info);
	ITEM_NO_SHADOW_INFO* GetInfo(int index);
	ITEM_NO_SHADOW_INFO* GetInfoByItem(int ItemIndex);
	bool CheckEffectRemake(int ItemIndex);
public:
	ITEM_NO_SHADOW_INFO m_NoShadowInfo[MAX_NO_SHADOW];
}; extern cNoShadow gNoShadow;