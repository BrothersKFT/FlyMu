// DefaultClassInfo.cpp: implementation of the CDefaultClassInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DefaultClassInfo.h"
#include "DSProtocol.h"
#include "ItemManager.h"
#include "Util.h"

CDefaultClassInfo gDefaultClassInfo;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDefaultClassInfo::CDefaultClassInfo() // OK
{
	this->Init();
}

CDefaultClassInfo::~CDefaultClassInfo() // OK
{

}

void CDefaultClassInfo::Init() // OK
{
	memset(this->m_DefaultClassInfo, 0, sizeof(this->m_DefaultClassInfo));
}

void CDefaultClassInfo::Load(char* path) // OK
{
	pugi::xml_document file;
	pugi::xml_parse_result res = file.load_file(path);

	if (res.status != pugi::status_ok)
	{
		ErrorMessageBox("File %s load fail. Error: %s", path, res.description());
		return;
	}

	this->Init();

	pugi::xml_node DefaultClassInfo = file.child("DefaultClassInfo");

	for (pugi::xml_node Class = DefaultClassInfo.child("Class"); Class; Class = Class.next_sibling())
	{
		DEFAULT_CLASS_INFO info;

		info.Class = Class.attribute("Index").as_int();

		pugi::xml_node DefaultStats = Class.child("DefaultStats");

		info.Money = DefaultStats.attribute("Money").as_int();
		info.Points = DefaultStats.attribute("Points").as_int();

		info.Strength = DefaultStats.attribute("Strength").as_int();
		info.Dexterity = DefaultStats.attribute("Dexterity").as_int();
		info.Vitality = DefaultStats.attribute("Vitality").as_int();
		info.Energy = DefaultStats.attribute("Energy").as_int();
		info.Leadership = DefaultStats.attribute("Leadership").as_int();

		info.MaxLife = DefaultStats.attribute("MaxLife").as_float();
		info.MaxMana = DefaultStats.attribute("MaxMana").as_float();
		info.LevelLife = DefaultStats.attribute("LevelLife").as_float();
		info.LevelMana = DefaultStats.attribute("LevelMana").as_float();
		info.VitalityToLife = DefaultStats.attribute("VitalityToLife").as_float();
		info.EnergyToMana = DefaultStats.attribute("EnergyToMana").as_float();

		pugi::xml_node ItemList = Class.child("ItemList");

		for (pugi::xml_node Item = ItemList.child("Item"); Item; Item = Item.next_sibling())
		{
			DEFAULT_CLASS_ITEM_INFO tmp;

			tmp.Index = SafeGetItem(GET_ITEM(Item.attribute("Cat").as_int(), Item.attribute("Index").as_int()));
			tmp.Level = Item.attribute("Level").as_int();
			tmp.Durability = Item.attribute("Durability").as_int();
			tmp.Skill = Item.attribute("Skill").as_int();
			tmp.Luck = Item.attribute("Luck").as_int();
			tmp.Option = Item.attribute("Option").as_int();
			tmp.Exc = Item.attribute("Exc").as_int();
			tmp.Set = Item.attribute("Set").as_int();
			tmp.Socket = Item.attribute("SocketCount").as_int();
			tmp.Duration = Item.attribute("Duration").as_int();

			info.ItemList.push_back(tmp);
		}

		pugi::xml_node BuffList = Class.child("BuffList");

		for (pugi::xml_node Buff = BuffList.child("Buff"); Buff; Buff = Buff.next_sibling())
		{
			DEFAULT_CLASS_BUFF_INFO tmp;

			tmp.Index = Buff.attribute("Index").as_int();
			tmp.Mode = Buff.attribute("Mode").as_bool();
			tmp.Power[0] = Buff.attribute("Power1").as_int();
			tmp.Power[1] = Buff.attribute("Power2").as_int();
			tmp.Power[2] = Buff.attribute("Power3").as_int();
			tmp.Power[3] = Buff.attribute("Power4").as_int();
			tmp.Duration = Buff.attribute("Duration").as_int();

			info.BuffList.push_back(tmp);
		}

		this->SetInfo(info);
	}
}

void CDefaultClassInfo::SetInfo(DEFAULT_CLASS_INFO info) // OK
{
	if (CHECK_RANGE(info.Class, MAX_CLASS) == 0)
	{
		return;
	}

	this->m_DefaultClassInfo[info.Class] = info;
}

int CDefaultClassInfo::GetCharacterDefaultStat(int Class, int stat) // OK
{
	if (CHECK_RANGE(Class, MAX_CLASS) == 0)
	{
		return 0;
	}

	switch (stat)
	{
	case 0:
		return this->m_DefaultClassInfo[Class].Strength;
	case 1:
		return this->m_DefaultClassInfo[Class].Dexterity;
	case 2:
		return this->m_DefaultClassInfo[Class].Vitality;
	case 3:
		return this->m_DefaultClassInfo[Class].Energy;
	case 4:
		return this->m_DefaultClassInfo[Class].Leadership;
	}

	return 0;
}

void CDefaultClassInfo::GetCharacterFreebies(LPOBJ lpObj, int status) // OK
{
	if (status == 3)
	{
		return;
	}

	DEFAULT_CLASS_INFO lpInfo = this->m_DefaultClassInfo[lpObj->Class];


	lpObj->Money += lpInfo.Money;
	GCMoneySend(lpObj->Index, lpObj->Money);

	lpObj->LevelUpPoint += lpInfo.Points;
	GCNewCharacterInfoSend(lpObj);
	GDCharacterInfoSaveSend(lpObj->Index);

	for (std::vector<DEFAULT_CLASS_ITEM_INFO>::iterator it = lpInfo.ItemList.begin(); it != lpInfo.ItemList.end(); it++)
	{
		BYTE ItemSocketOption[MAX_SOCKET_OPTION] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

		for (int u = 0; u < it->Socket && it->Socket <= MAX_SOCKET_OPTION; u++)
		{
			ItemSocketOption[u] = 0xFE;
		}

		GDCreateItemSend(lpObj->Index, 0xEB, 0, 0, it->Index, it->Level, it->Durability, it->Skill, it->Luck, it->Option, -1, it->Exc, it->Set, 0, 0, ItemSocketOption, 0xFF, (((it->Duration * 60)>0) ? ((DWORD)time(0) + (it->Duration * 60)) : 0));
	}

	for (std::vector<DEFAULT_CLASS_BUFF_INFO>::iterator it = lpInfo.BuffList.begin(); it != lpInfo.BuffList.end(); it++)
	{
		if (gEffectManager.GetEffect(lpObj, it->Index) != 0)
		{
			continue;
		}

		gEffectManager.AddEffect(lpObj, it->Mode, it->Index, (it->Mode == 0) ? it->Duration : (int)(time(0) + it->Duration), it->Power[0], it->Power[1], it->Power[2], it->Power[3]);
	}
}