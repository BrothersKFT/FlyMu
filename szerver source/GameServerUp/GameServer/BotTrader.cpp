// BotTrader.cpp: implementation of the CBotTrader class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BotTrader.h"
#include "DSProtocol.h"
#include "ItemManager.h"
#include "ItemOptionRate.h"
#include "MapServerManager.h"
#include "Message.h"
#include "Monster.h"
#include "ObjectManager.h"
#include "RandomManager.h"
#include "Trade.h"
#include "User.h"
#include "Util.h"

CBotTrader gBotTrader;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBotTrader::CBotTrader() // OK
{

}

CBotTrader::~CBotTrader() // OK
{

}

void CBotTrader::Load(char* path) // OK
{
	pugi::xml_document file;
	pugi::xml_parse_result res = file.load_file(path);

	if (res.status != pugi::status_ok)
	{
		ErrorMessageBox("File %s load fail. Error: %s", path, res.description());
		return;
	}

	this->m_BotTraderInfo.clear();

	pugi::xml_node IncreaseRate = file.child("IncreaseRate");

	this->m_IncreaseRateChaos = IncreaseRate.attribute("JewelOfChaos").as_int();
	this->m_IncreaseRateBless = IncreaseRate.attribute("JewelOfBless").as_int();
	this->m_IncreaseRateSoul = IncreaseRate.attribute("JewelOfSoul").as_int();
	this->m_IncreaseRateLife = IncreaseRate.attribute("JewelOfLife").as_int();
	this->m_IncreaseRateCreation = IncreaseRate.attribute("JewelOfCreation").as_int();

	pugi::xml_node BotsTrader = file.child("BotsTrader");

	for (pugi::xml_node Bot = BotsTrader.child("Bot"); Bot; Bot = Bot.next_sibling())
	{
		if(Bot.attribute("Enable").as_int() != 1)
		{
			continue;
		}

		BOT_TRADER_INFO info;

		info.Id = Bot.attribute("Id").as_int();
		info.Class = Bot.attribute("Class").as_int();
		//info.Evo = Bot.attribute("Evo").as_int();
		info.PKLevel = Bot.attribute("PKLevel").as_int();
		info.Map = Bot.attribute("Map").as_int();
		info.PosX = Bot.attribute("PosX").as_int();
		info.PosY = Bot.attribute("PosY").as_int();
		info.Dir = Bot.attribute("Dir").as_int();
		strcpy_s(info.Name, Bot.attribute("Name").as_string());

		pugi::xml_node Equipment = Bot.child("Equipment");

		for (pugi::xml_node Item = Equipment.child("Item"); Item; Item = Item.next_sibling())
		{
			BOT_TRADER_ITEM_INFO infoitem;

			infoitem.Slot = Item.attribute("Slot").as_int();
			infoitem.Index = SafeGetItem(GET_ITEM(Item.attribute("ItemCat").as_int(), Item.attribute("ItemIndex").as_int()));
			infoitem.Level = Item.attribute("ItemLevel").as_int();

			info.ItemList.push_back(infoitem);
		}

		pugi::xml_node ItemList = Bot.child("ItemList");

		for (pugi::xml_node Section = ItemList.child("Section"); Section; Section = Section.next_sibling())
		{
			int MinRate = Section.attribute("MinRate").as_int();
			int MaxRate = Section.attribute("MaxRate").as_int();

			for (pugi::xml_node Item = Section.child("Item"); Item; Item = Item.next_sibling())
			{
				BOT_TRADER_ITEM_RATE_INFO rate;

				rate.MinRate = MinRate;
				rate.MaxRate = MaxRate;
				rate.Index = SafeGetItem(GET_ITEM(Item.attribute("Cat").as_int(), Item.attribute("Index").as_int()));
				rate.Durability = Item.attribute("Durability").as_int();
				rate.Option0 = Item.attribute("LevelOption").as_int();
				rate.Option1 = Item.attribute("SkillOption").as_int();
				rate.Option2 = Item.attribute("LuckOption").as_int();
				rate.Option3 = Item.attribute("JoLOption").as_int();
				rate.Option4 = Item.attribute("ExcOption").as_int();
				rate.Option5 = Item.attribute("SetOption").as_int();
				rate.Option6 = Item.attribute("SocketOption").as_int();
				rate.Duration = Item.attribute("Duration").as_int();
				rate.Rate = Item.attribute("Rate").as_int();

				info.ItemRateInfo.push_back(rate);
			}
		}

		this->SetInfo(info);
	}

	this->BotSpawn();
}

void CBotTrader::SetInfo(BOT_TRADER_INFO info) // OK
{
	if (this->m_BotTraderInfo.size() >= MAX_BOT_TRADER)
	{
		return;
	}

	if (gMapServerManager.CheckMapServer(info.Map) == 0)
	{
		return;
	}

	this->m_BotTraderInfo.insert(std::pair<int, BOT_TRADER_INFO>(info.Id, info));
}

void CBotTrader::BotSpawn() // OK
{
	for (std::map<int, BOT_TRADER_INFO>::iterator it = this->m_BotTraderInfo.begin(); it != this->m_BotTraderInfo.end(); it++)
	{
		int index = gObjAddSummon();

		if (index >= 0)
		{
			LPOBJ lpBot = &gObj[index];

			int px = it->second.PosX;
			int py = it->second.PosY;

			it->second.MobIndex = index;
			lpBot->BotId = it->second.Id;
			lpBot->BotType = BOT_TRADER;
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

			//lpBot->ChangeUp = it->second.Evo;
			lpBot->DBClass = it->second.Class;
			lpBot->Level = 400;
			lpBot->PKLevel = it->second.PKLevel;
			lpBot->Inventory = new CItem[INVENTORY_SIZE];

			for (std::vector<BOT_TRADER_ITEM_INFO>::iterator inv = it->second.ItemList.begin(); inv != it->second.ItemList.end(); inv++)
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

bool CBotTrader::BotTalk(int aIndex, int bIndex) // OK
{
	LPOBJ lpObj = &gObj[aIndex];
	LPOBJ lpTarget = &gObj[bIndex];

	if (lpTarget->BotType != BOT_TRADER)
	{
		return 0;
	}

	std::map<int, BOT_TRADER_INFO>::iterator it = this->m_BotTraderInfo.find(lpTarget->BotId);

	if (it == this->m_BotTraderInfo.end())
	{
		return 0;
	}

	if (lpObj->Interface.use != 0)
	{
#if (DUEL_CUSTOM_APUESTAS == 0)
		gTrade.GCTradeResponseSend(aIndex, 0, lpTarget->Name, 0, 0);
#else
		gTrade.GCTradeResponseSend(aIndex, 0, lpTarget->Name, 0, 0, 0);
#endif
		return 0;
	}

	if (lpObj->X < (lpTarget->X - 2) || lpObj->X >(lpTarget->X + 2) || lpObj->Y < (lpTarget->Y - 2) || lpObj->Y >(lpTarget->Y + 2))
	{
#if (DUEL_CUSTOM_APUESTAS == 0)
		gTrade.GCTradeResponseSend(aIndex, 0, lpTarget->Name, 0, 0);
#else
		gTrade.GCTradeResponseSend(aIndex, 0, lpTarget->Name, 0, 0, 0);
#endif
		return 0;
	}

	if (lpObj->PShopOpen != 0)
	{
#if (DUEL_CUSTOM_APUESTAS == 0)
		gTrade.GCTradeResponseSend(aIndex, 0, lpTarget->Name, 0, 0);
#else
		gTrade.GCTradeResponseSend(aIndex, 0, lpTarget->Name, 0, 0, 0);
#endif
		return 0;
	}

	gObjFixInventoryPointer(aIndex);

	gObjInventoryTransaction(aIndex);

	gTrade.ClearTrade(lpObj);

	lpObj->Interface.use = 1;
	lpObj->Interface.type = INTERFACE_TRADE;
	lpObj->Interface.state = 1;
	lpObj->TargetNumber = bIndex;
	lpObj->TradeOk = 0;
	lpObj->TradeOkTime = 0;
	lpObj->TradeMoney = 0;

	GCChatTargetSend(lpObj, bIndex, gMessage.GetMessage(870));
#if (DUEL_CUSTOM_APUESTAS == 0)
	gTrade.GCTradeResponseSend(aIndex, 1, lpTarget->Name, lpTarget->Level, lpTarget->GuildNumber);
#else
	gTrade.GCTradeResponseSend(aIndex, 1, lpTarget->Name, lpTarget->Level, lpTarget->GuildNumber, 0);
#endif
}

void CBotTrader::TradeRequest(int aIndex, int bIndex) // OK
{
	LPOBJ lpObj = &gObj[aIndex];
	LPOBJ lpTarget = &gObj[bIndex];

	int TotalRate = 0;

	for (int n = 0; n < CHAOS_BOX_SIZE; n++)
	{
		if (lpObj->Trade[n].IsItem() == 0)
		{
			continue;
		}

		switch (lpObj->Trade[n].m_Index)
		{
		case GET_ITEM(12, 15):
			TotalRate += this->m_IncreaseRateChaos;
			break;
		case GET_ITEM(12, 141):
			TotalRate += (10 * this->m_IncreaseRateChaos) * (lpObj->Trade[n].m_Level + 1);
			break;
		case GET_ITEM(14, 13):
			TotalRate += this->m_IncreaseRateBless;
			break;
		case GET_ITEM(12, 30):
			TotalRate += (10 * this->m_IncreaseRateBless) * (lpObj->Trade[n].m_Level + 1);
			break;
		case GET_ITEM(14, 14):
			TotalRate += this->m_IncreaseRateSoul;
			break;
		case GET_ITEM(12, 31):
			TotalRate += (10 * this->m_IncreaseRateSoul) * (lpObj->Trade[n].m_Level + 1);
			break;
		case GET_ITEM(14, 16):
			TotalRate += this->m_IncreaseRateLife;
			break;
		case GET_ITEM(12, 136):
			TotalRate += (10 * this->m_IncreaseRateLife) * (lpObj->Trade[n].m_Level + 1);
			break;
		case GET_ITEM(14, 22):
			TotalRate += this->m_IncreaseRateCreation;
			break;
		case GET_ITEM(12, 137):
			TotalRate += (10 * this->m_IncreaseRateCreation) * (lpObj->Trade[n].m_Level + 1);
			break;
		}
	}

	if (gItemManager.CheckItemInventorySpace(lpObj, 5, 5) == 0)
	{
		GCChatTargetSend(lpObj, bIndex, gMessage.GetMessage(871));
		return;
	}

	std::map<int, BOT_TRADER_INFO>::iterator it = this->m_BotTraderInfo.find(lpTarget->BotId);

	CRandomManager RandomManager;

	if (it != this->m_BotTraderInfo.end())
	{
		for (std::vector<BOT_TRADER_ITEM_RATE_INFO>::iterator is = it->second.ItemRateInfo.begin(); is != it->second.ItemRateInfo.end(); is++)
		{
			if (is->MinRate > TotalRate)
			{
				continue;
			}

			if (is->MaxRate != -1 && is->MaxRate < TotalRate)
			{
				continue;
			}

			RandomManager.AddElement((int)(&(*is)), is->Rate);
		}
	}

	BOT_TRADER_ITEM_RATE_INFO* lpBotTrader = 0;

	if (RandomManager.GetRandomElement((int*)&lpBotTrader) == 0)
	{
		lpObj->Interface.use = 0;
		lpObj->Interface.type = INTERFACE_NONE;
		lpObj->Interface.state = 0;

		gObjInventoryCommit(aIndex);
		gTrade.ClearTrade(lpObj);
		gTrade.GCTradeResultSend(aIndex, 1);

		GCChatTargetSend(lpObj, bIndex, gMessage.GetMessage(872));

		return;
	}

	WORD ItemIndex = lpBotTrader->Index;
	BYTE ItemLevel = 0;
	BYTE ItemDur = (BYTE)lpBotTrader->Durability;
	BYTE ItemOption1 = 0;
	BYTE ItemOption2 = 0;
	BYTE ItemOption3 = 0;
	BYTE ItemNewOption = 0;
	BYTE ItemSetOption = 0;
	BYTE ItemSocketOption[MAX_SOCKET_OPTION] = { 0xFF,0xFF,0xFF,0xFF,0xFF };

	gItemOptionRate.GetItemOption0(lpBotTrader->Option0, &ItemLevel);

	gItemOptionRate.GetItemOption1(lpBotTrader->Option1, &ItemOption1);

	gItemOptionRate.GetItemOption2(lpBotTrader->Option2, &ItemOption2);

	gItemOptionRate.GetItemOption3(lpBotTrader->Option3, &ItemOption3);

	gItemOptionRate.GetItemOption4(lpBotTrader->Option4, &ItemNewOption);

	gItemOptionRate.GetItemOption5(lpBotTrader->Option5, &ItemSetOption);

	gItemOptionRate.GetItemOption6(lpBotTrader->Option6, &ItemSocketOption[0]);

	gItemOptionRate.MakeNewOption(ItemIndex, ItemNewOption, &ItemNewOption);

	gItemOptionRate.MakeSetOption(ItemIndex, ItemSetOption, &ItemSetOption);

	gItemOptionRate.MakeSocketOption(ItemIndex, ItemSocketOption[0], &ItemSocketOption[0]);

	GDCreateItemSend(lpObj->Index, 0xEB, 0, 0, ItemIndex, ItemLevel, 0, ItemOption1, ItemOption2, ItemOption3, -1, ItemNewOption, ItemSetOption, 0, 0, ItemSocketOption, 0xFF, ((lpBotTrader->Duration>0) ? ((DWORD)time(0) + lpBotTrader->Duration) : 0));

	lpObj->Interface.use = 0;
	lpObj->Interface.type = INTERFACE_NONE;
	lpObj->Interface.state = 0;

	gObjInventoryCommit(aIndex);
	gTrade.ClearTrade(lpObj);
	gTrade.GCTradeResultSend(aIndex, 1);

	GCChatTargetSend(lpObj, bIndex, gMessage.GetMessage(873));
}