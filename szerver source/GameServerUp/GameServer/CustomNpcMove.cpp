//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CustomNpcMove.h"
#include "CastleSiegeSync.h"
#include "GensSystem.h"
#include "Map.h"
#include "MapManager.h"
#include "MemScript.h"
#include "Message.h"
#include "Notice.h"
#include "NpcTalk.h"
#include "Path.h"
#include "Util.h"

CCustomNpcMove gCustomNpcMove;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCustomNpcMove::CCustomNpcMove() // OK
{
	this->m_CustomNpcMove.clear();
}

CCustomNpcMove::~CCustomNpcMove() // OK
{

}

void CCustomNpcMove::Load(char* path) // OK
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

	this->m_CustomNpcMove.clear();

	try
	{
		while (true)
		{
			if (lpMemScript->GetToken() == TOKEN_END)
			{
				break;
			}

			if (strcmp("end", lpMemScript->GetString()) == 0)
			{
				break;
			}

			NPC_MOVE_INFO info;

			info.Index = lpMemScript->GetNumber();

			info.MonsterClass = lpMemScript->GetAsNumber();

			strcpy_s(info.Name, lpMemScript->GetAsString());

			info.Map = lpMemScript->GetAsNumber();

			info.X = lpMemScript->GetAsNumber();

			info.Y = lpMemScript->GetAsNumber();

			info.MoveMap = lpMemScript->GetAsNumber();

			info.MoveX = lpMemScript->GetAsNumber();

			info.MoveY = lpMemScript->GetAsNumber();

			info.MinLevel = lpMemScript->GetAsNumber();

			info.MaxLevel = lpMemScript->GetAsNumber();

			info.MinReset = lpMemScript->GetAsNumber();

			info.MaxReset = lpMemScript->GetAsNumber();

			info.MinMReset = lpMemScript->GetAsNumber();

			info.MaxMReset = lpMemScript->GetAsNumber();

			info.AccountLevel = lpMemScript->GetAsNumber();

			info.PkMove = lpMemScript->GetAsNumber();

			info.Category = lpMemScript->GetAsNumber();

			info.ItemIndex = lpMemScript->GetAsNumber();

			info.Level = lpMemScript->GetAsNumber();

			info.Luck = lpMemScript->GetAsNumber();

			info.Skill = lpMemScript->GetAsNumber();

			info.Quantity = lpMemScript->GetAsNumber();

			this->m_CustomNpcMove.insert(std::pair<int, NPC_MOVE_INFO>(info.Index, info));
		}
	}
	catch (...)
	{
		ErrorMessageBox(lpMemScript->GetLastError());
	}

	delete lpMemScript;
}

bool CCustomNpcMove::CheckItem(LPOBJ lpObj, int npc) // OK
{
	int ItemOK;
	int Qtd;

	for (std::map<int, NPC_MOVE_INFO>::iterator it = this->m_CustomNpcMove.begin(); it != this->m_CustomNpcMove.end(); it++)
	{
		if (it->second.Index <= 0)
		{
			continue;
		}

		if (it->second.Index != npc)
		{
			continue;
		}

		ItemOK = 0;
		Qtd = 0;

		if (it->second.Category >= 0 && it->second.ItemIndex >= 0)
		{
			for (int x = 12; x < INVENTORY_MAIN_SIZE; x++)
			{
				if (lpObj->Inventory[x].IsItem() == TRUE)
				{
					if (lpObj->Inventory[x].m_Index == GET_ITEM(it->second.Category, it->second.ItemIndex))
					{
						ItemOK = 0;
						if (it->second.Level >= 0)
						{
							if (lpObj->Inventory[x].m_Level == it->second.Level)
							{
								ItemOK++;
							}
						}
						else
						{
							ItemOK++;
						}

						if (it->second.Luck >= 0)
						{
							if (lpObj->Inventory[x].m_Option2 == it->second.Luck)
							{
								ItemOK++;
							}
						}
						else
						{
							ItemOK++;
						}

						if (it->second.Skill >= 0)
						{
							if (lpObj->Inventory[x].m_Option1 == it->second.Skill)
							{
								ItemOK++;
							}
						}
						else
						{
							ItemOK++;
						}

						if (ItemOK >= 3)
						{
							Qtd++;
						}
					}
				}
			}

			if (Qtd < it->second.Quantity)
			{
				char text[100];
				char level[10];
				wsprintf(level, "+%d", it->second.Level);

				wsprintf(text, "%d %s %s %s %s", it->second.Quantity, gItemManager.GetItemName(GET_ITEM(it->second.Category, it->second.ItemIndex)), (it->second.Level >= 0) ? level : "", (it->second.Luck >= 0) ? (it->second.Luck == 1) ? "+Luck" : "-No Luck" : "", (it->second.Skill >= 0) ? (it->second.Skill == 1) ? "+Skill" : "-No Skill" : "");
				gNotice.GCNoticeSend(lpObj->Index, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(727), it->second.Name, it->second.Quantity, text);

				return 0;
			}
		}

	}
	return 1;
}

void CCustomNpcMove::RemoveItem(LPOBJ lpObj, int npc) // OK
{
	int ItemOK;
	int QtdRemove;

	for (std::map<int, NPC_MOVE_INFO>::iterator it = this->m_CustomNpcMove.begin(); it != this->m_CustomNpcMove.end(); it++)
	{

		if (it->second.Index <= 0)
		{
			continue;
		}

		if (it->second.Index != npc)
		{
			continue;
		}

		if (it->second.Quantity > 0)
		{
			if (it->second.Category >= 0 && it->second.ItemIndex >= 0)
			{
				QtdRemove = 0;

				for (int x = 12; x < INVENTORY_MAIN_SIZE; x++)
				{
					if (lpObj->Inventory[x].IsItem() == TRUE)
					{
						if (lpObj->Inventory[x].m_Index == GET_ITEM(it->second.Category, it->second.ItemIndex))
						{
							ItemOK = 0;

							if (it->second.Level >= 0)
							{
								if (lpObj->Inventory[x].m_Level == it->second.Level)
								{
									ItemOK++;
								}
							}
							else
							{
								ItemOK++;
							}

							if (it->second.Luck >= 0)
							{
								if (lpObj->Inventory[x].m_Option2 == it->second.Luck)
								{
									ItemOK++;
								}
							}
							else
							{
								ItemOK++;
							}

							if (it->second.Skill >= 0)
							{
								if (lpObj->Inventory[x].m_Option1 == it->second.Skill)
								{
									ItemOK++;
								}
							}
							else
							{
								ItemOK++;
							}

							if (ItemOK >= 3)
							{
								gItemManager.InventoryDelItem(lpObj->Index, x);
								gItemManager.GCItemDeleteSend(lpObj->Index, x, 1);

								QtdRemove++;

								if (QtdRemove >= it->second.Quantity)
								{
									break;
								}
							}
						}
					}
				}
			}
		}
	}
}

bool CCustomNpcMove::GetNpcMove(LPOBJ lpObj, int MonsterClass, int Map, int X, int Y) // OK
{
	for (std::map<int, NPC_MOVE_INFO>::iterator it = this->m_CustomNpcMove.begin(); it != this->m_CustomNpcMove.end(); it++)
	{
		if (it->second.MonsterClass == MonsterClass && it->second.Map == Map && it->second.X == X && it->second.Y == Y)
		{

			if (it->second.MinLevel != -1 && lpObj->Level
#if (LEVEL_PLUS ==1)
				+ lpObj->LevelPlus
#endif
				< it->second.MinLevel)
			{
				gNotice.GCNoticeSend(lpObj->Index, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(224), it->second.MinLevel);
				return 1;
			}

			if (it->second.MaxLevel != -1 && lpObj->Level
#if (LEVEL_PLUS ==1)
				+ lpObj->LevelPlus
#endif
				> it->second.MaxLevel)
			{
				gNotice.GCNoticeSend(lpObj->Index, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(230), it->second.MaxLevel);
				return 1;
			}

			if (it->second.MinReset != -1 && lpObj->Reset < it->second.MinReset)
			{
				gNotice.GCNoticeSend(lpObj->Index, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(231), it->second.MinReset);
				return 1;
			}

			if (it->second.MaxReset != -1 && lpObj->Reset > it->second.MaxReset)
			{
				gNotice.GCNoticeSend(lpObj->Index, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(232), it->second.MaxReset);
				return 1;
			}

			if (it->second.MinReset != -1 && lpObj->MasterReset < it->second.MinMReset)
			{
				gNotice.GCNoticeSend(lpObj->Index, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(818), it->second.MinMReset);
				return 1;
			}

			if (it->second.MaxReset != -1 && lpObj->MasterReset > it->second.MaxMReset)
			{
				gNotice.GCNoticeSend(lpObj->Index, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(819), it->second.MaxMReset);
				return 1;
			}

			if (lpObj->AccountLevel < it->second.AccountLevel)
			{
				gNotice.GCNoticeSend(lpObj->Index, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(226));
				return 1;
			}

			if (it->second.PkMove == 0 && lpObj->PKLevel >= 5)
			{
				gNotice.GCNoticeSend(lpObj->Index, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(227));
				return 1;
			}

			if (lpObj->Interface.use != 0 || lpObj->Teleport != 0 || lpObj->DieRegen != 0 || lpObj->PShopOpen != 0)
			{
				gNotice.GCNoticeSend(lpObj->Index, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(226));
				return 1;
			}

			if (it->second.MoveMap == MAP_ATLANS && (lpObj->Inventory[8].IsItem() != 0 && (lpObj->Inventory[8].m_Index == GET_ITEM(13, 2) || lpObj->Inventory[8].m_Index == GET_ITEM(13, 3)))) // Uniria,Dinorant
			{
				gNotice.GCNoticeSend(lpObj->Index, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(274));
				return 1;
			}

			if ((it->second.MoveMap == MAP_ICARUS || it->second.MoveMap == MAP_KANTURU3) && (lpObj->Inventory[7].IsItem() == 0 && lpObj->Inventory[8].m_Index != GET_ITEM(13, 3) && lpObj->Inventory[8].m_Index != GET_ITEM(13, 37))) // Dinorant,Fenrir
			{
				gNotice.GCNoticeSend(lpObj->Index, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(228));
				return 1;
			}

#if(GAMESERVER_UPDATE>=501)

			if (lpObj->GensFamily == GENS_FAMILY_NONE && gMapManager.GetMapGensBattle(it->second.MoveMap) != 0)
			{
				gNotice.GCNoticeSend(lpObj->Index, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(229));
				return 1;
			}
#endif

			// ==================================================================================================================================

			int ItemOK = 0;
			int Slot = -1;
			int Qtd = 0;

			if (it->second.Category >= 0 && it->second.ItemIndex >= 0)
			{
				for (int x = 12; x < INVENTORY_MAIN_SIZE; x++)
				{
					if (lpObj->Inventory[x].IsItem() == TRUE)
					{
						if (lpObj->Inventory[x].m_Index == GET_ITEM(it->second.Category, it->second.ItemIndex))
						{
							ItemOK = 0;
							if (it->second.Level >= 0)
							{
								if (lpObj->Inventory[x].m_Level == it->second.Level)
								{
									ItemOK++;
								}
							}
							else
							{
								ItemOK++;
							}

							if (it->second.Luck >= 0)
							{
								if (lpObj->Inventory[x].m_Option2 == it->second.Luck)
								{
									ItemOK++;
								}
							}
							else
							{
								ItemOK++;
							}

							if (it->second.Skill >= 0)
							{
								if (lpObj->Inventory[x].m_Option1 == it->second.Skill)
								{
									ItemOK++;
								}
							}
							else
							{
								ItemOK++;
							}

							if (ItemOK >= 3)
							{
								Qtd = x;
								break;
							}
						}
					}
				}

				if (Qtd < it->second.Quantity)
				{
					char text[100];
					char level[10];
					wsprintf(level, "+%d", it->second.Level);

					wsprintf(text, "%d %s %s %s %s", it->second.Quantity, gItemManager.GetItemName(GET_ITEM(it->second.Category, it->second.ItemIndex)), (it->second.Level >= 0) ? level : "", (it->second.Luck >= 0) ? (it->second.Luck == 1) ? "+Luck" : "-No Luck" : "", (it->second.Skill >= 0) ? (it->second.Skill == 1) ? "+Skill" : "-No Skill" : "");
					gNotice.GCNoticeSend(lpObj->Index, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(727), it->second.Name, text);

					return 1;
				}
			}

			if (Qtd >= it->second.Quantity)
			{
				gItemManager.InventoryDelItem(lpObj->Index, Qtd);
				gItemManager.GCItemDeleteSend(lpObj->Index, Qtd, 1);
			}

			// ==================================================================================================================================

			gObjTeleport(lpObj->Index, it->second.MoveMap, it->second.MoveX, it->second.MoveY);
			return 1;
		}

	}
	return 0;
}