// MonsterKillCount.cpp: interface for the CMonsterKillCount class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MonsterKillCount.h"
#include "CashShop.h"
#include "DSProtocol.h"
#include "GameMain.h"
#include "ItemManager.h"
#include "Message.h"
#include "Notice.h"
#include "Log.h"
#include "Util.h"

CMonsterKillCount gMonsterKillCount;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMonsterKillCount::CMonsterKillCount() // OK
{
	this->m_MonsterKillCountInfo.clear();
}

CMonsterKillCount::~CMonsterKillCount() // OK
{

}

void CMonsterKillCount::Load(char* path) // OK
{
	pugi::xml_document file;
	pugi::xml_parse_result res = file.load_file(path);

	if (res.status != pugi::status_ok)
	{
		ErrorMessageBox("File %s load fail. Error: %s", path, res.description());
		return;
	}

	this->m_MonsterKillCountInfo.clear();

	pugi::xml_node MonsterKillCount = file.child("MonsterKillCount");

	if (MonsterKillCount.attribute("EnableFeature").as_int() == 0)
	{
		return;
	}

	for (pugi::xml_node Monster = MonsterKillCount.child("Monster"); Monster; Monster = Monster.next_sibling())
	{
		MONSTER_KILL_COUNT_INFO info;

		info.MonsterIndex = Monster.attribute("Index").as_int();

		for (pugi::xml_node Reward = Monster.child("Reward"); Reward; Reward = Reward.next_sibling())
		{
			MONSTER_KILL_COUNT_REWARD_INFO reward;

			reward.Count = Reward.attribute("Count").as_int();
			reward.Money = Reward.attribute("Money").as_int();
			reward.WCoinC = Reward.attribute("WCoinC").as_int();
			reward.WCoinP = Reward.attribute("WCoinP").as_int();
			reward.GoblinPoint = Reward.attribute("GoblinPoint").as_int();
			reward.Ruud = Reward.attribute("Ruud").as_int();
			strcpy_s(reward.Description, Reward.attribute("Description").as_string());

			for (pugi::xml_node Item = Reward.child("Item"); Item; Item = Item.next_sibling())
			{
				MONSTER_KILL_COUNT_ITEM_LIST item;

				item.Index = SafeGetItem(GET_ITEM(Item.attribute("Cat").as_int(), Item.attribute("Index").as_int()));
				item.Level = Item.attribute("Level").as_int();
				item.Durability = Item.attribute("Durability").as_int();
				item.Skill = Item.attribute("Skill").as_int();
				item.Luck = Item.attribute("Luck").as_int();
				item.Option = Item.attribute("Option").as_int();
				item.Exc = Item.attribute("Exc").as_int();
				item.Set = Item.attribute("Set").as_int();
				item.Socket = Item.attribute("SocketCount").as_int();
				item.Duration = Item.attribute("Duration").as_int();

				reward.ItemList.push_back(item);
			}

			info.RewardInfo.insert(std::pair<int, MONSTER_KILL_COUNT_REWARD_INFO>(reward.Count, reward));
		}

		this->m_MonsterKillCountInfo.insert(std::pair<int, MONSTER_KILL_COUNT_INFO>(info.MonsterIndex, info));
	}
}

void CMonsterKillCount::CheckMonsterKillCount(LPOBJ lpObj, int MonsterClass) // OK
{
	std::map<int, MONSTER_KILL_COUNT_INFO>::iterator it = this->m_MonsterKillCountInfo.find(MonsterClass);

	if (it != this->m_MonsterKillCountInfo.end())
	{
		SDHP_MONSTER_KILL_COUNT_SEND pMsg;

		pMsg.header.set(0x12, 0x00, sizeof(pMsg));

		pMsg.index = lpObj->Index;
		pMsg.MonsterClass = MonsterClass;
		memcpy(pMsg.Name, lpObj->Name, sizeof(pMsg.Name));

		gDataServerConnection.DataSend((BYTE*)&pMsg, pMsg.header.size);
	}
}

void CMonsterKillCount::DGMonsterKillCountRecv(SDHP_MONSTER_KILL_COUNT_RECV* lpMsg) // OK
{
	if (gObjIsConnectedGP(lpMsg->index) == 0)
	{
		return;
	}

	std::map<int, MONSTER_KILL_COUNT_INFO>::iterator it = this->m_MonsterKillCountInfo.find(lpMsg->MonsterClass);

	if (it != this->m_MonsterKillCountInfo.end())
	{
		std::map<int, MONSTER_KILL_COUNT_REWARD_INFO>::iterator ic = it->second.RewardInfo.find(lpMsg->Count);

		if (ic != it->second.RewardInfo.end())
		{
			if (ic->second.Money > 0)
			{
				gObj[lpMsg->index].Money += ic->second.Money;
				GCMoneySend(lpMsg->index, gObj[lpMsg->index].Money);
			}

			if (ic->second.WCoinC > 0 || ic->second.WCoinP > 0 || ic->second.GoblinPoint > 0 || ic->second.Ruud > 0)
			{
				gCashShop.GDCashShopAddPointSaveSend(lpMsg->index, 0, ic->second.WCoinC, ic->second.WCoinP, ic->second.GoblinPoint, ic->second.Ruud);
				gNotice.GCNoticeSend(lpMsg->index, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(549), ic->second.WCoinC, ic->second.WCoinP, ic->second.GoblinPoint, ic->second.Ruud);
			}

			for (std::vector<MONSTER_KILL_COUNT_ITEM_LIST>::iterator ir = ic->second.ItemList.begin(); ir != ic->second.ItemList.end(); ir++)
			{
				BYTE ItemSocketOption[MAX_SOCKET_OPTION] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

				for (int u = 0; u < ir->Socket && ir->Socket <= MAX_SOCKET_OPTION; u++)
				{
					ItemSocketOption[u] = 0xFE;
				}

				GDCreateItemSend(lpMsg->index, 0xEB, 0, 0, ir->Index, ir->Level, ir->Durability, ir->Skill, ir->Luck, ir->Option, lpMsg->index, ir->Exc, ir->Set, 0, 0, ItemSocketOption, 0xFF, (((ir->Duration * 60)>0) ? ((DWORD)time(0) + (ir->Duration * 60)) : 0));
			}

			gNotice.GCNoticeSend(lpMsg->index, 1, 0, 0, 0, 0, 0, ic->second.Description);

			GCServerCommandSend(lpMsg->index, 58, SET_NUMBERHB(lpMsg->index), SET_NUMBERLB(lpMsg->index));
		}
	}
}