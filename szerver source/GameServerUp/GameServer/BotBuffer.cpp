// BotBuffer.cpp: implementation of the CBotBuffer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BotBuffer.h"
#include "EffectManager.h"
#include "ItemManager.h"
#include "MapServerManager.h"
#include "Monster.h"
#include "Notice.h"
#include "ObjectManager.h"
#include "User.h"
#include "Util.h"

CBotBuffer gBotBuffer;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBotBuffer::CBotBuffer() // OK
{

}

CBotBuffer::~CBotBuffer() // OK
{

}

void CBotBuffer::Load(char* path) // OK
{
	pugi::xml_document file;
	pugi::xml_parse_result res = file.load_file(path);

	if (res.status != pugi::status_ok)
	{
		ErrorMessageBox("File %s load fail. Error: %s", path, res.description());
		return;
	}

	this->m_BotBufferInfo.clear();

	pugi::xml_node BotsBuffer = file.child("BotsBuffer");

	for (pugi::xml_node Bot = BotsBuffer.child("Bot"); Bot; Bot = Bot.next_sibling())
	{
		if (Bot.attribute("Enable").as_int() != 1)
		{
			continue;
		}

		BOT_BUFFER_INFO info;

		info.Id = Bot.attribute("Id").as_int();
		info.Class = Bot.attribute("Class").as_int();
		//	info.Evo = Bot.attribute("Evo").as_int();
		info.PKLevel = Bot.attribute("PKLevel").as_int();
		info.Map = Bot.attribute("Map").as_int();
		info.PosX = Bot.attribute("PosX").as_int();
		info.PosY = Bot.attribute("PosY").as_int();
		info.Dir = Bot.attribute("Dir").as_int();
		strcpy_s(info.Name, Bot.attribute("Name").as_string());

		pugi::xml_node Equipment = Bot.child("Equipment");

		for (pugi::xml_node Item = Equipment.child("Item"); Item; Item = Item.next_sibling())
		{
			BOT_BUFFER_ITEM_INFO infoitem;

			infoitem.Slot = Item.attribute("Slot").as_int();
			infoitem.Index = SafeGetItem(GET_ITEM(Item.attribute("ItemCat").as_int(), Item.attribute("ItemIndex").as_int()));
			infoitem.Level = Item.attribute("ItemLevel").as_int();

			info.ItemList.push_back(infoitem);
		}

		pugi::xml_node BuffList = Bot.child("BuffList");

		for (pugi::xml_node Buff = BuffList.child("Buff"); Buff; Buff = Buff.next_sibling())
		{
			BOT_BUFFER_BUFF_INFO infobuff;

			infobuff.Index = Buff.attribute("Index").as_int();
			infobuff.Power[0] = Buff.attribute("Power1").as_int();
			infobuff.Power[1] = Buff.attribute("Power2").as_int();
			infobuff.Power[2] = Buff.attribute("Power3").as_int();
			infobuff.Power[2] = Buff.attribute("Power4").as_int();
			infobuff.Duration = Buff.attribute("Duration").as_int();

			info.BuffList.push_back(infobuff);
		}

		this->SetInfo(info);
	}

	this->BotSpawn();
}

void CBotBuffer::SetInfo(BOT_BUFFER_INFO info) // OK
{
	if (this->m_BotBufferInfo.size() >= MAX_BOT_BUFFER)
	{
		return;
	}

	if (gMapServerManager.CheckMapServer(info.Map) == 0)
	{
		return;
	}

	this->m_BotBufferInfo.insert(std::pair<int, BOT_BUFFER_INFO>(info.Id, info));
}

void CBotBuffer::BotSpawn() // OK
{
	for (std::map<int, BOT_BUFFER_INFO>::iterator it = this->m_BotBufferInfo.begin(); it != this->m_BotBufferInfo.end(); it++)
	{
		int index = gObjAddSummon();

		if (index >= 0)
		{
			LPOBJ lpBot = &gObj[index];

			int px = it->second.PosX;
			int py = it->second.PosY;

			it->second.MobIndex = index;
			lpBot->BotId = it->second.Id;
			lpBot->BotType = BOT_BUFFER;
			lpBot->PosNum = -1;
			lpBot->X = px;
			lpBot->Y = py;
			lpBot->OldX = px;
			lpBot->OldY = py;
			lpBot->TX = px;
			lpBot->TY = py;
			lpBot->Dir = it->second.Dir;
			lpBot->Map = it->second.Map;

			gObjSetMonsterBot(index, it->second.Class);

			strcpy_s(lpBot->Name, it->second.Name);

			//		lpBot->ChangeUp = it->second.Evo;
			lpBot->DBClass = it->second.Class;
			lpBot->Level = 400;
			lpBot->PKLevel = it->second.PKLevel;
			lpBot->Inventory = new CItem[INVENTORY_SIZE];

			for (std::vector<BOT_BUFFER_ITEM_INFO>::iterator inv = it->second.ItemList.begin(); inv != it->second.ItemList.end(); inv++)
			{
				CItem item;
				item.m_Level = inv->Level;
				item.m_Durability = 255.0f;
				item.Convert(inv->Index, 0, 1, 0, 0, 0, 0, 0, 0, 0xFF);
				lpBot->Inventory[inv->Slot] = item;
			}

			gObjectManager.CharacterMakePreviewCharSet(index);
		}
	}
}

bool CBotBuffer::BotTalk(int aIndex, int bIndex) // OK
{
	LPOBJ lpObj = &gObj[aIndex];

	if (gObj[bIndex].BotType != BOT_BUFFER)
	{
		return 0;
	}

	std::map<int, BOT_BUFFER_INFO>::iterator it = this->m_BotBufferInfo.find(gObj[bIndex].BotId);

	if (it == this->m_BotBufferInfo.end())
	{
		return 0;
	}
	else
	{
		for (std::vector<BOT_BUFFER_BUFF_INFO>::iterator ib = it->second.BuffList.begin(); ib != it->second.BuffList.end(); ib++)
		{
			if (gEffectManager.GetEffect(lpObj, ib->Index) != 0)
			{
				continue;
			}

			gEffectManager.AddEffect(lpObj, 0, ib->Index, ib->Duration, ib->Power[0], ib->Power[1], ib->Power[2], ib->Power[3]);
		}

		GCActionSend(&gObj[bIndex], ACTION_GOODBYE1, bIndex, aIndex);

		return 1;
	}
}