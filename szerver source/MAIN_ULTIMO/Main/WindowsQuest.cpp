#include "stdafx.h"
#include "WindowsQuest.h"
#include "Interface.h"
#include "Protocol.h"
#include "Item.h"
#include "Offset.h"
#include "Item.h"
#include "Defines.h"
#include "CustomMap.h"
#include "postInterface.h"
#include "Central.h"
#include "Common.h"

// ----------------------------------------------------------------------------------------------

ExWinQuestSystem g_ExWinQuestSystem;
// ----------------------------------------------------------------------------------------------

ExWinQuestSystem::ExWinQuestSystem()
{
	this->Init();
}
// ----------------------------------------------------------------------------------------------

ExWinQuestSystem::~ExWinQuestSystem()
{
	// --
}
// ----------------------------------------------------------------------------------------------

void ExWinQuestSystem::Init()
{
	// --
	this->DrawMiniInfoFlag = false;
	ZeroMemory(&this->ewdata, sizeof(this->ewdata));
}
// ----------------------------------------------------------------------------------------------

void ExWinQuestSystem::Load()
{
	this->Init();
}
// ----------------------------------------------------------------------------------------------

void ExWinQuestSystem::ImageLoad()
{
	pLoadImage("Custom\\Interface\\Party_info_block.tga", ex_INFO_2, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Interface\\newui_cha_textbox03.tga", ex_TEXT_BOX3, 0x2601, 0x2900, 1, 0);
}
// ----------------------------------------------------------------------------------------------

void ExWinQuestSystem::BindImages()
{
	int eWHig = 303 + 60 + 45 + 15;

	gInterface.BindObject(OBJECT_WIN_QUEST_MAIN, 0x7A5A, 222, eWHig, -1, -1);
	gInterface.BindObject(OBJECT_WIN_QUEST_TITLE, 0x7A63, 230, 67, -1, -1);
	gInterface.BindObject(OBJECT_WIN_QUEST_FRAME, 0x7A58, 230, 15, -1, -1);
	gInterface.BindObject(OBJECT_WIN_QUEST_FOOTER, 0x7A59, 230, 50, -1, -1);
	gInterface.BindObject(OBJECT_WIN_QUEST_DIV, 0x7A62, 223, 21, -1, -1);
	gInterface.BindObject(OBJECT_WIN_QUEST_CLOSE, 0x7EC5, 36, 29, -1, -1);
	gInterface.BindObject(OBJECT_WIN_QUEST_TAB, 0x7AE0, 166, 22, -1, -1);
	gInterface.BindObject(OBJECT_WIN_QUEST_TAB1, 0x7AE1, 55, 22, -1, -1);
	gInterface.BindObject(OBJECT_WIN_QUEST_TAB2, 0x7AE1, 55, 22, -1, -1);
	gInterface.BindObject(OBJECT_WIN_QUEST_TAB3, 0x7AE1, 55, 22, -1, -1);
	gInterface.BindObject(OBJECT_WIN_QUEST_FINISH, 71522, 108, 30.5, -1, -1);
	gInterface.BindObject(OBJECT_WIN_QUEST_COUNT1, 0x7BAC, 168, 18, -1, -1);
	gInterface.BindObject(OBJECT_WIN_QUEST_COUNT2, 0x7BAC, 168, 18, -1, -1);
	gInterface.BindObject(OBJECT_WIN_QUEST_COUNT3, 0x7BAC, 168, 18, -1, -1);
	gInterface.BindObject(OBJECT_WIN_QUEST_INFOBG, 0x7AA3, 170, 21, -1, -1);
	gInterface.BindObject(OBJECT_WIN_QUEST_INFOBG2, 0x7AA1, 170, 22, -1, -1);
	gInterface.BindObject(OBJECT_WIN_QUEST_LINE1, 0x7B67, 154, 3, -1, -1);
	gInterface.BindObject(OBJECT_WIN_QUEST_POINT1, 0x7B68, 10, 10, -1, -1);
	gInterface.BindObject(OBJECT_WIN_QUEST_INFO, ex_INFO_2, 22, 19, -1, -1);
	gInterface.BindObject(OBJECT_WIN_QUEST_INFOBG3, ex_TEXT_BOX3, 170, 21, -1, -1);
	gInterface.BindObject(OPEN_QUEST, 0x7904, 25, 40, -1, -1);
}
// ----------------------------------------------------------------------------------------------

void ExWinQuestSystem::Draw()
{
	if (!gInterface.Data[OBJECT_WIN_QUEST_MAIN].OnShow)
	{
		return;
	}

	pSetCursorFocus = true;

	pSetBlend(true);

	int a = this->OpenTab;

	DWORD ItemNameColor = eWhite;
	float MainWidth = 230.0;
	float MainHeight = 360.0;
	float StartY = ((MAX_WIN_HEIGHT - 51) / 2) - (MainHeight / 2);
	float StartX = (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float MainCenter = StartX + (MainWidth / 3);
	float ButtonX = MainCenter - (float)(29.0 / 2);

	float ContentX = StartX;
	float ContentY = StartY;
	float TabX = StartX + 30;
	float TabY = ContentY + 30 + 5;
	float InfoX = 0;
	float InfoY = 0;
	int InfoA = 0;
	int InfoM = 0;
	int bColor = 0;
	//--
	gInterface.Data[OBJECT_WIN_QUEST_MAIN].MaxX = StartX + MainWidth;
	gInterface.Data[OBJECT_WIN_QUEST_MAIN].MaxY = StartY + MainHeight;

	gCentral.PrintDropBox(StartX, StartY, MainWidth, MainHeight, 0, 0);

	gInterface.DrawFormat(eGold, (int)StartX + 10, (int)StartY + 10, 210, 3,"Quest Panel");

	gInterface.DrawGUI(OBJECT_WIN_QUEST_CLOSE, StartX + MainWidth - gInterface.Data[OBJECT_WIN_QUEST_CLOSE].Width, ContentY);
	// ----
	if (gInterface.IsWorkZone(OBJECT_WIN_QUEST_CLOSE))
	{
		DWORD Color = eGray100;
		// ----
		if (gInterface.Data[OBJECT_WIN_QUEST_CLOSE].OnClick)
		{
			Color = eGray150;
		}
		// ----
		gInterface.DrawColoredGUI(OBJECT_WIN_QUEST_CLOSE, gInterface.Data[OBJECT_WIN_QUEST_CLOSE].X, gInterface.Data[OBJECT_WIN_QUEST_CLOSE].Y, Color);
		gInterface.DrawToolTip(gInterface.Data[OBJECT_WIN_QUEST_CLOSE].X + 5, gInterface.Data[OBJECT_WIN_QUEST_CLOSE].Y + 25, "Close");
	}
	// ------------------------------------
	// -> Tab
	// ------------------------------------
	gInterface.DrawGUI(OBJECT_WIN_QUEST_TAB, TabX, TabY);

	if (this->OpenTab == 0)
	{
		gInterface.DrawGUI(OBJECT_WIN_QUEST_TAB1, TabX, TabY);
		gInterface.DrawGUI(OBJECT_WIN_QUEST_TAB2, TabX + gInterface.Data[OBJECT_WIN_QUEST_TAB2].Width, TabY);
		gInterface.DrawGUI(OBJECT_WIN_QUEST_TAB3, TabX + gInterface.Data[OBJECT_WIN_QUEST_TAB3].Width + gInterface.Data[OBJECT_WIN_QUEST_TAB3].Width, TabY);
	}
	else if (this->OpenTab == 1)
	{
		gInterface.DrawGUI(OBJECT_WIN_QUEST_TAB1, TabX, TabY);
		gInterface.DrawGUI(OBJECT_WIN_QUEST_TAB2, TabX + gInterface.Data[OBJECT_WIN_QUEST_TAB2].Width, TabY);
		gInterface.DrawGUI(OBJECT_WIN_QUEST_TAB3, TabX + gInterface.Data[OBJECT_WIN_QUEST_TAB3].Width + gInterface.Data[OBJECT_WIN_QUEST_TAB3].Width, TabY);
	}
	else
	{
		gInterface.DrawGUI(OBJECT_WIN_QUEST_TAB1, TabX, TabY);
		gInterface.DrawGUI(OBJECT_WIN_QUEST_TAB2, TabX + gInterface.Data[OBJECT_WIN_QUEST_TAB2].Width, TabY);
		gInterface.DrawGUI(OBJECT_WIN_QUEST_TAB3, TabX + gInterface.Data[OBJECT_WIN_QUEST_TAB3].Width + gInterface.Data[OBJECT_WIN_QUEST_TAB3].Width, TabY);
	}

	if (this->ewdata[0].b_End)
	{
		gInterface.DrawText(eRed, TabX, TabY + 10, 60, 3, "Off");
	}
	else
	{
		gInterface.DrawText(eGold, TabX, TabY + 10, 60, 3, "Quest");

		gInterface.DrawText(eAncient, ContentX + 30, TabY + 30, 180, 3, "%s", this->ewdata[0].NameQuest);
	}
	if (this->ewdata[1].b_End)
	{
		gInterface.DrawText(eRed, TabX + gInterface.Data[OBJECT_WIN_QUEST_TAB2].Width, TabY + 10, 60, 3, "Off");
	}
	else
	{
		gInterface.DrawText(eGold, TabX + gInterface.Data[OBJECT_WIN_QUEST_TAB2].Width, TabY + 10, 60, 3, "Quest");

		gInterface.DrawText(eAncient, ContentX + 30, TabY + 30, 180, 3, "%s", this->ewdata[1].NameQuest);
	}
	if (this->ewdata[2].b_End)
	{
		gInterface.DrawText(eRed, TabX + gInterface.Data[OBJECT_WIN_QUEST_TAB3].Width + gInterface.Data[OBJECT_WIN_QUEST_TAB3].Width, TabY + 10, 60, 3, "Off");
	}
	else
	{
		gInterface.DrawText(eGold, TabX + gInterface.Data[OBJECT_WIN_QUEST_TAB3].Width + gInterface.Data[OBJECT_WIN_QUEST_TAB3].Width, TabY + 10, 60, 3, "Quest");

		gInterface.DrawText(eAncient, ContentX + 30, TabY + 30, 180, 3, "%s", this->ewdata[2].NameQuest);
	}
	// ------------------------------------
	// -> End Quest
	// ------------------------------------
	if (this->ewdata[a].b_End)
	{
		float EndY = ContentY + 53;
		gInterface.DrawGUI(OBJECT_WIN_QUEST_INFOBG3, StartX + 30, EndY + 12);
		gInterface.DrawText(eAncient, ContentX + 30, EndY + 17, 170, 3, "End");
		gInterface.Data[OBJECT_WIN_QUEST_FINISH].Attribute = false;
		return;
	}
	// ------------------------------------
	// -> Content Need
	// ------------------------------------
	float NeededY = ContentY + 53;

	pDrawGUI(71520, StartX + 10, NeededY +5 , 200, 1); //-- Divisor

	float CountNeededY = NeededY + 30;

	gInterface.DrawText(eWhite, StartX + 40, CountNeededY + 6, 100, 1, "Level:");

	if (this->ewdata[a].b_Level)
	{
		bColor = eGold;
	}
	else
	{
		bColor = eRed;
	}

	gInterface.DrawText(bColor, StartX + 70, CountNeededY + 6, 100, 1, "%d", this->ewdata[a].NeedLevel);
	gInterface.DrawText(eWhite, StartX + 100, CountNeededY + 6, 100, 1, "Reset:");

	if (this->ewdata[a].b_Reset)
	{
		bColor = eGold;
	}
	else
	{
		bColor = eRed;
	}

	gInterface.DrawText(bColor, StartX + 130, CountNeededY + 6, 100, 1, "%d", this->ewdata[a].NeedReset);
	gInterface.DrawText(eWhite, StartX + 160, CountNeededY + 6, 100, 1, "GReset:");

	if (this->ewdata[a].b_Grand)
	{
		bColor = eGold;
	}
	else
	{
		bColor = eRed;
	}

	gInterface.DrawText(bColor, StartX + 195, CountNeededY + 6, 100, 1, "%d", this->ewdata[a].NeedGrand);
	CountNeededY += 21;
	// ------------------------------------
	// -> Content Mission
	// ------------------------------------
	float MissionX = StartX;
	float MissionY = ContentY + 53 + 60;

	pDrawGUI(71520, StartX +10, MissionY, 200, 1); //-- Divisor

	MissionY += 10;

	gInterface.DrawText(eAncient, ContentX + 30, MissionY + 2, 170, 3, "Mission");

	float CountMissionY = MissionY + 20;

	//----------------------------------------------------

	for (int m = 0; m < EW_MAX_MISSION; m++)
	{
		if (this->ewdata[a].MissionType[m] == Hunting ||
			this->ewdata[a].MissionType[m] == Droping ||
			this->ewdata[a].MissionType[m] == Searching)
		{
			if (this->ewdata[a].b_Mission[m])
			{
				bColor = eExcellent;
			}
			else
			{
				bColor = eWhite;
			}

			CountMissionY += 10;

			if (this->ewdata[a].MissionType[m] == Hunting)
			{
				if (this->ewdata[a].MissionID[m] == 65535)
				{
					gInterface.DrawText(bColor, MissionX + 30 + 5 + 15, CountMissionY, 200, 1, "- Kill Level %d~%d: %d/%d",
						this->ewdata[a].MissionOpt[m], this->ewdata[a].MissionExl[m], this->ewdata[a].Count[m], this->ewdata[a].MissionCount[m]);
				}
				else
				{
					gInterface.DrawText(bColor, MissionX + 30 + 5 + 15, CountMissionY, 200, 1, "- %s: %d/%d", pGetMonsterName(this->ewdata[a].MissionID[m]/*gMonster.GetMonsterName(this->ewdata[a].MissionID[m]*/), this->ewdata[a].Count[m], this->ewdata[a].MissionCount[m]);
				}
			}
			else if (this->ewdata[a].MissionType[m] == Droping)
			{
				gInterface.DrawText(bColor, MissionX + 30 + 5 + 15, CountMissionY, 200, 1, "- %s: %d/%d", gItem.getItemName(GET_ITEM(this->ewdata[a].MissionID[m], this->ewdata[a].MissionIndex[m])), ewdata[a].Count[m], ewdata[a].MissionCount[m]);
			}
			else if (this->ewdata[a].MissionType[m] == Searching)
			{
				gInterface.DrawText(bColor, MissionX + 30 + 5 + 15, CountMissionY, 200, 1, "- %s", gItem.getItemName(GET_ITEM(this->ewdata[a].MissionID[m], this->ewdata[a].MissionIndex[m])));
			}
		}
	}
	// ------------------------------------
	// -> Content Reward
	// ------------------------------------
	float RewardY = ContentY + 53 + 100 + 42 + 15;

	pDrawGUI(71520, StartX +10, RewardY, 200, 1); //-- Divisor

	gInterface.DrawText(eAncient, ContentX + 30, RewardY + 12, 170, 3, "Reward");

	float CountRewardY = RewardY + 34 - 4;

	for (int r = 0; r < EW_MAX_REWARD; r++)
	{
		if (this->ewdata[a].RewardType[r] == ewZen ||
			this->ewdata[a].RewardType[r] == ewFreePoint ||
			this->ewdata[a].RewardType[r] == ewItem ||
			this->ewdata[a].RewardType[r] == ewBonus ||
			this->ewdata[a].RewardType[r] == ewBuff)
		{
			if (this->ewdata[a].RewardType[r] == ewZen)
			{
				char RewardMSG[64] = { 0 };
				gInterface.DrawText(eWhite, StartX + 30 + 5, CountRewardY + 5, 100, 1, "Zen:");
				pGetMoneyFormat((double)(int)this->ewdata[a].RewardCount[r], RewardMSG, 0);
				gInterface.DrawText(eGold, StartX + 30 + 70, CountRewardY + 5, 100, 3, "%s", RewardMSG);
			}
			else if (this->ewdata[a].RewardType[r] == ewFreePoint)
			{
				gInterface.DrawFormat(eWhite, StartX + 30 + 5, CountRewardY + 5, 100, 1, "Lvl Point:");
				gInterface.DrawFormat(eGold, StartX + 30 + 70, CountRewardY + 5, 100, 3, "%d", this->ewdata[a].RewardCount[r]);
			}
			else if (this->ewdata[a].RewardType[r] == ewItem)
			{
				ItemBmdStruct* ItemInfo = pGetItemBmdStruct(ITEM(this->ewdata[a].RewardItemType[r], this->ewdata[a].RewardItemIndex[r]));

				const int WidthValue = 24;
				const int HeightValue = 26;
				float barWidth = WidthValue * ItemInfo->ItemWidth;
				float barHeight = HeightValue * ItemInfo->ItemHeight;

				if (this->ewdata[a].RewardItemLevel[r] > 0)
				{
					gInterface.DrawText(eGold, StartX + 70, CountRewardY + 5, 100, 3, "%s +%d x %d",
						gItem.getItemName(GET_ITEM(this->ewdata[a].RewardItemType[r], this->ewdata[a].RewardItemIndex[r])), this->ewdata[a].RewardItemLevel[r], this->ewdata[a].RewardCount[r]);
				}
				else
				{
					gInterface.DrawText(eGold, StartX + 70, CountRewardY + 5, 100, 3, "%s x %d",
						gItem.getItemName(GET_ITEM(this->ewdata[a].RewardItemType[r], this->ewdata[a].RewardItemIndex[r])), this->ewdata[a].RewardCount[r]);
				}

				gPostInterface.DrawItemIMG(ContentX + 70, CountRewardY -5, barWidth, barHeight, GET_ITEM(this->ewdata[a].RewardItemType[r], this->ewdata[a].RewardItemIndex[r]), 0, 1, 0, 0);
				
			}
			else if (this->ewdata[a].RewardType[r] == ewBonus)
			{
				gInterface.DrawFormat(eWhite, StartX + 30 + 5, CountRewardY + 5, 100, 1, "WCoin:");
				gInterface.DrawFormat(eGold, StartX + 30 + 70, CountRewardY + 5, 100, 3, "%d", this->ewdata[a].RewardCount[r]);
			}
			else if (this->ewdata[a].RewardType[r] == ewBuff)
			{
				gInterface.DrawText(eWhite, StartX + 30 + 5, CountRewardY + 5, 100, 1, "Buff:");

				switch (this->ewdata[a].RewardItemType[r])
				{
				case 1:
					gInterface.DrawFormat(eGold, StartX + 30 + 70, CountRewardY + 5, 100, 3, "%s", "Experience: + 15%%");
					break;
				case 2:
					gInterface.DrawFormat(eGold, StartX + 30 + 70, CountRewardY + 5, 100, 3, "%s", "Dmg: +10%%/Wizard Dmg: +10%%");
					break;
				case 3:
					gInterface.DrawFormat(eGold, StartX + 30 + 70, CountRewardY + 5, 100, 3, "%s", "Defence: +10%%");
					break;
				case 4:
					gInterface.DrawFormat(eGold, StartX + 30 + 70, CountRewardY + 5, 100, 3, "%s", "Exel Dmg Rate: +5%%/Ctcal Dmg Rate: +5%%");
					break;
				case 5:
					gInterface.DrawFormat(eGold, StartX + 30 + 70, CountRewardY + 5, 100, 3, "%s", "Zen Drop: +50%%");
					break;
				case 6:
					gInterface.DrawFormat(eGold, StartX + 30 + 70, CountRewardY + 5, 100, 3, "%s", "Double Damage: +5%%");
					break;
				}
			}

			CountRewardY += 21;
		}
	}
	// ------------------------------------
	// -> Finish
	// ------------------------------------
	bool Finish = 0;

	if (this->ewdata[a].Start)
	{
		Finish = this->ewdata[a].b_done;
	}
	else
	{
		Finish = this->ewdata[a].b_accept;
	}

	//------
	if (gInterface.IsWorkZone(OBJECT_WIN_QUEST_FINISH))
	{
		if (gInterface.Data[OBJECT_WIN_QUEST_FINISH].OnClick)
		{
			PlayBuffer(25, 0, 0);
			gInterface.DrawButtonRender(OBJECT_WIN_QUEST_FINISH, StartX + (MainWidth / 2) - (110 / 2), StartY + MainHeight - 32, 0, 28);
		}
		else
		{
			gInterface.DrawButtonRender(OBJECT_WIN_QUEST_FINISH, StartX + (MainWidth / 2) - (110 / 2), StartY + MainHeight - 32, 0, 0);
		}
	}
	else
	{
		gInterface.DrawButtonRender(OBJECT_WIN_QUEST_FINISH, StartX + (MainWidth / 2) - (110 / 2), StartY + MainHeight - 32, 0, 0);
	}

	if (this->ewdata[a].Start)
	{
		gInterface.DrawFormat(eWhite, StartX + (MainWidth / 2) - (110 / 2), StartY + MainHeight - 23, 110, 3, "Finish");
	}
	else
	{
		gInterface.DrawFormat(eWhite, StartX + (MainWidth / 2) - (110 / 2), StartY + MainHeight - 23, 110, 3, "Accept");
	}
	//------
	if (!Finish)
	{
		gInterface.Data[OBJECT_WIN_QUEST_FINISH].Attribute = false;
	}
	else
	{
		// ----
		gInterface.Data[OBJECT_WIN_QUEST_FINISH].Attribute = true;
		// ----
	}

	pSetBlend(false);
}

void ExWinQuestSystem::DrawMiniInfo()
{

	try
	{
		if (gInterface.CheckWindow(Party)
			|| gInterface.CheckWindow(Guild)
			|| gInterface.CheckWindow(Trade)
			|| gInterface.CheckWindow(Warehouse)
			|| gInterface.CheckWindow(ChaosBox)
			|| gInterface.CheckWindow(CommandWindow)
			|| gInterface.CheckWindow(PetInfo)
			|| gInterface.CheckWindow(Shop)
			|| gInterface.CheckWindow(Inventory)
			|| gInterface.CheckWindow(Store)
			|| gInterface.CheckWindow(OtherStore)
			|| gInterface.CheckWindow(Character)
			|| gInterface.CheckWindow(FastMenu)
			|| gInterface.CheckWindow(SkillTree)
			|| gInterface.CheckWindow(NPC_Titus)
			|| gInterface.CheckWindow(CashShop)
			|| gInterface.CheckWindow(FullMap)
			|| gInterface.CheckWindow(NPC_Dialog)
			|| gInterface.CheckWindow(GensInfo)
			|| gInterface.CheckWindow(NPC_Julia)
			|| gInterface.CheckWindow(ExpandInventory)
			|| gInterface.CheckWindow(ExpandWarehouse)
			|| gInterface.CheckWindow(MuHelper)
			|| gInterface.CheckWindow(Quest)
			|| gInterface.CheckWindow(NPC_Devin)
			|| gInterface.CheckWindow(DevilSquare)
			|| gInterface.CheckWindow(GuardNPC)
			|| gInterface.CheckWindow(CastleGateSwitch)
			|| gInterface.CheckWindow(GoldenArcher2)
			|| gInterface.CheckWindow(LuckyCoin1)
			|| gInterface.CheckWindow(LuckyCoin2)
			|| gInterface.CheckWindow(BloodCastle))
		{
			return;
		}

		if (gProtect.m_MainInfo.MiniMapType == 1)
		{
			if (MiniMap == 1)
			{
				return;
			}
		}

		int qCount = 0;
		int mCount = 0;
		bool DrInfo = false;

		for (int a = 0; a < EW_MAX_ACT; a++)
		{
			if (this->ewdata[a].Start == TRUE)
			{
				qCount += 15;

				for (int m = 0; m < EW_MAX_MISSION; m++)
				{
					if (this->ewdata[a].MissionType[m] == Hunting ||
						this->ewdata[a].MissionType[m] == Droping ||
						this->ewdata[a].MissionType[m] == Searching)
					{
						mCount += 10;
						DrInfo = true;
					}
				}
			}
		}

		if (DrInfo == false)
		{

			return;
		}

		float iX = 530;
		float iY = 320;
		float Wind = 100;
		float Hig = qCount + mCount;

		float StartiY = 420;

		iY = StartiY - Hig;

		pSetBlend(true);

		pDrawColorButton(0x7980, iX, iY, Wind, Hig, NULL, NULL, Color4f(0, 0, 0, 100));

		iY += 3;

		for (int a = 0; a < EW_MAX_ACT; a++)
		{
			if (this->ewdata[a].Start == TRUE)
			{
				gInterface.DrawText(eOrange, iX + 5, iY, 200, 1, "%s", this->ewdata[a].NameQuest);

				for (int m = 0; m < EW_MAX_MISSION; m++)
				{
					if (this->ewdata[a].MissionType[m] == Hunting ||
						this->ewdata[a].MissionType[m] == Droping ||
						this->ewdata[a].MissionType[m] == Searching)
					{
						iY += 10;

						if (this->ewdata[a].MissionType[m] == Hunting)
						{
							if (this->ewdata[a].MissionID[m] == 65535)
							{
								gInterface.DrawText(eWhite, iX + 10, iY, 200, 1, "- Kill Level %d~%d: %d/%d",
									this->ewdata[a].MissionOpt[m], this->ewdata[a].MissionExl[m], this->ewdata[a].Count[m], this->ewdata[a].MissionCount[m]);
							}
							else
							{
								gInterface.DrawText(eWhite, iX + 10, iY, 200, 1, "- %s: %d/%d", pGetMonsterName(this->ewdata[a].MissionID[m]/*gMonster.GetMonsterName(this->ewdata[a].MissionID[m]*/), this->ewdata[a].Count[m], this->ewdata[a].MissionCount[m]);
							}
						}
						else if (this->ewdata[a].MissionType[m] == Droping)
						{
							gInterface.DrawText(eWhite, iX + 10, iY, 200, 1, "- %s: %d/%d", gItem.getItemName(GET_ITEM(this->ewdata[a].MissionID[m], this->ewdata[a].MissionIndex[m])), ewdata[a].Count[m], ewdata[a].MissionCount[m]);
						}
						else if (this->ewdata[a].MissionType[m] == Searching)
						{
							gInterface.DrawText(eWhite, iX + 10, iY, 200, 1, "- %s", gItem.getItemName(GET_ITEM(this->ewdata[a].MissionID[m], this->ewdata[a].MissionIndex[m])));
						}
					}
				}

				iY += 15;
			}
		}

		pSetBlend(false);
	}
	catch (...)
	{
	}
}
//// ----------------------------------------------------------------------------------------------
void ExWinQuestSystem::DrawOpenWQ()
{
	if (gInterface.Data[OPEN_QUEST].OnShow)
	{
		gInterface.Data[OPEN_QUEST].OnShow = false;
	}

      if (gInterface.CheckWindow(Party)
			|| gInterface.CheckWindow(Guild)
			|| gInterface.CheckWindow(Trade)
			|| gInterface.CheckWindow(Warehouse)
			|| gInterface.CheckWindow(ChaosBox)
			|| gInterface.CheckWindow(CommandWindow)
			|| gInterface.CheckWindow(PetInfo)
			|| gInterface.CheckWindow(Shop)
			|| gInterface.CheckWindow(Inventory)
			|| gInterface.CheckWindow(Store)
			|| gInterface.CheckWindow(OtherStore)
			|| gInterface.CheckWindow(Character)
			|| gInterface.CheckWindow(FastMenu)
			|| gInterface.CheckWindow(SkillTree)
			|| gInterface.CheckWindow(NPC_Titus)
			|| gInterface.CheckWindow(CashShop)
			|| gInterface.CheckWindow(FullMap)
			|| gInterface.CheckWindow(NPC_Dialog)
			|| gInterface.CheckWindow(GensInfo)
			|| gInterface.CheckWindow(NPC_Julia)
			|| gInterface.CheckWindow(ExpandInventory)
			|| gInterface.CheckWindow(ExpandWarehouse)
			|| gInterface.CheckWindow(MuHelper)
			|| gInterface.CheckWindow(Quest)
			|| gInterface.CheckWindow(NPC_Devin)
			|| gInterface.CheckWindow(DevilSquare)
			|| gInterface.CheckWindow(GuardNPC)
			|| gInterface.CheckWindow(CastleGateSwitch)
			|| gInterface.CheckWindow(GoldenArcher2)
			|| gInterface.CheckWindow(LuckyCoin1)
			|| gInterface.CheckWindow(LuckyCoin2)
			|| gInterface.CheckWindow(BloodCastle))
		{
			return;
		}

	  gInterface.Data[OPEN_QUEST].OnShow = true;

	  gInterface.DrawGUI(OPEN_QUEST, 615, 370);

	  if (gInterface.IsWorkZone(OPEN_QUEST))
	  {

		  gInterface.DrawToolTip(562, 385, "Quest Panel");
		  // ----
		  if (gInterface.Data[OPEN_QUEST].OnClick)
		  {
			  gInterface.DrawColoredGUI(OPEN_QUEST, 615, 370, pMakeColor(40, 20, 3, 130));
			  return;
		  }
		  // ----
		  gInterface.DrawColoredGUI(OPEN_QUEST, 615, 370, pMakeColor(255, 204, 20, 200));
	  }
		
}

//
int ExWinQuestSystem::Button(DWORD Event)
{
	if (gInterface.ButtonEx(Event, OPEN_QUEST, false))
	{
		if (gInterface.Data[OBJECT_WIN_QUEST_MAIN].OnShow)
		{
			g_ExWinQuestSystem.SwitchStatsWindowState();
		}
		else
		{
			if (gInterface.CheckWindow(Party) || gInterface.CheckWindow(Guild) || gInterface.CheckWindow(Trade)
				|| gInterface.CheckWindow(Warehouse) || gInterface.CheckWindow(ChaosBox) || gInterface.CheckWindow(CommandWindow)
				|| gInterface.CheckWindow(PetInfo) || gInterface.CheckWindow(Shop) || gInterface.CheckWindow(Inventory)
				|| gInterface.CheckWindow(Store) || gInterface.CheckWindow(OtherStore) || gInterface.CheckWindow(Character)
				|| gInterface.CheckWindow(FastMenu) || gInterface.CheckWindow(SkillTree) || gInterface.CheckWindow(NPC_Titus)
				|| gInterface.CheckWindow(CashShop) || gInterface.CheckWindow(FullMap) || gInterface.CheckWindow(NPC_Dialog)
				|| gInterface.CheckWindow(GensInfo) || gInterface.CheckWindow(NPC_Julia) || gInterface.CheckWindow(ExpandInventory)
				|| gInterface.CheckWindow(ExpandWarehouse) || gInterface.CheckWindow(MuHelper) || gInterface.CheckWindow(Quest)
				|| gInterface.CheckWindow(NPC_Devin) || gInterface.CheckWindow(DevilSquare) || gInterface.CheckWindow(GuardNPC)
				|| gInterface.CheckWindow(CastleGateSwitch) || gInterface.CheckWindow(GoldenArcher2) || gInterface.CheckWindow(LuckyCoin1)
				|| gInterface.CheckWindow(LuckyCoin2) || gInterface.CheckWindow(BloodCastle))
			{
				// A conflicting window is open, do nothing.
			}
			else
			{
				g_ExWinQuestSystem.SwitchStatsWindowState();
			}
		}
		return true; 
	}

	// --- From here, handle buttons INSIDE the quest window ---
	if (!gInterface.Data[OBJECT_WIN_QUEST_MAIN].OnShow)
	{
		return false;
	}

	if (gInterface.ButtonEx(Event, OBJECT_WIN_QUEST_CLOSE, false))
	{
		pSetCursorFocus = false;
		gInterface.Data[OBJECT_WIN_QUEST_MAIN].Close();
		return true;
	}

	if (gInterface.ButtonEx(Event, OBJECT_WIN_QUEST_FINISH, true))
	{
		this->CG_AcceptQuest();
		return true;
	}
	else if (gInterface.ButtonEx(Event, OBJECT_WIN_QUEST_TAB1, false))
	{
		this->OpenTab = 0;
		return true;
	}
	else if (gInterface.ButtonEx(Event, OBJECT_WIN_QUEST_TAB2, false))
	{
		this->OpenTab = 1;
		return true;
	}
	else if (gInterface.ButtonEx(Event, OBJECT_WIN_QUEST_TAB3, false))
	{
		this->OpenTab = 2;
		return true;
	}

	return false;
}
//// ----------------------------------------------------------------------------------------------
//
void ExWinQuestSystem::GC_RecvMain(GC_MainPacket* aRecv)
{
	for (int a = 0; a < EW_MAX_ACT; a++)
	{
		strncpy(this->ewdata[a].NameQuest, aRecv->exQuest[a].NameQuest, 25);
		this->ewdata[a].b_accept = aRecv->exQuest[a].b_accept;
		this->ewdata[a].b_done = aRecv->exQuest[a].b_done;
		this->ewdata[a].b_End = aRecv->exQuest[a].b_End;
		// -> user send
		this->ewdata[a].Start = aRecv->exQuest[a].Start;
		this->ewdata[a].Number = aRecv->exQuest[a].Number;
		for (int m = 0; m < EW_MAX_MISSION; m++)
		{
			this->ewdata[a].Count[m] = aRecv->exQuest[a].Count[m];
		}
		// -> need send
		this->ewdata[a].b_Level = aRecv->exQuest[a].b_Level;
		this->ewdata[a].b_Reset = aRecv->exQuest[a].b_Reset;
		this->ewdata[a].b_Grand = aRecv->exQuest[a].b_Grand;

		this->ewdata[a].NeedLevel = aRecv->exQuest[a].NeedLevel;
		this->ewdata[a].NeedReset = aRecv->exQuest[a].NeedReset;
		this->ewdata[a].NeedGrand = aRecv->exQuest[a].NeedGrand;
		// -> mission send
		for (int m = 0; m < EW_MAX_MISSION; m++)
		{
			this->ewdata[a].b_Mission[m] = aRecv->exQuest[a].b_Mission[m];
			this->ewdata[a].MissionType[m] = aRecv->exQuest[a].MissionType[m];
			this->ewdata[a].MissionID[m] = aRecv->exQuest[a].MissionID[m];
			this->ewdata[a].MissionIndex[m] = aRecv->exQuest[a].MissionIndex[m];
			this->ewdata[a].MissionLevel[m] = aRecv->exQuest[a].MissionLevel[m];
			this->ewdata[a].MissionLuck[m] = aRecv->exQuest[a].MissionLuck[m];
			this->ewdata[a].MissionOpt[m] = aRecv->exQuest[a].MissionOpt[m];
			this->ewdata[a].MissionExl[m] = aRecv->exQuest[a].MissionExl[m];
			this->ewdata[a].MissionCount[m] = aRecv->exQuest[a].MissionCount[m];
			this->ewdata[a].MissionProcent[m] = aRecv->exQuest[a].MissionProcent[m];
		}
		for (int r = 0; r < EW_MAX_REWARD; r++)
		{

			this->ewdata[a].RewardType[r] = aRecv->exQuest[a].RewardType[r];
			this->ewdata[a].RewardCount[r] = aRecv->exQuest[a].RewardCount[r];
			this->ewdata[a].RewardItemType[r] = aRecv->exQuest[a].RewardItemType[r];
			this->ewdata[a].RewardItemIndex[r] = aRecv->exQuest[a].RewardItemIndex[r];
			this->ewdata[a].RewardItemLevel[r] = aRecv->exQuest[a].RewardItemLevel[r];
		}
	}

	if (aRecv->isOpenWindow)
	{
		if (!gInterface.Data[OBJECT_WIN_QUEST_MAIN].OnShow)
		{
			this->SwitchStatsWindowState();
			pSetCursorFocus = true;
		}
	}

}
//// ----------------------------------------------------------------------------------------------
//
void ExWinQuestSystem::CG_AcceptQuest()
{
	CG_Accept_Done pReq = { 0 };
	pReq.h.set(0xFD, 0x0D, sizeof(pReq));
	pReq.Result = this->OpenTab;
	DataSend((LPBYTE)&pReq, pReq.h.size);
}
//// ----------------------------------------------------------------------------------------------
//
void ExWinQuestSystem::GC_MiniInfoRecv(GC_ExWinMiniInfo* aRecv)
{
	for (int a = 0; a < EW_MAX_ACT; a++)
	{
		strncpy(this->ewdata[a].NameQuest, aRecv->exQuest[a].NameQuest, 25);

		this->ewdata[a].Start = aRecv->exQuest[a].Start;

		for (int m = 0; m < EW_MAX_MISSION; m++)
		{
			this->ewdata[a].Count[m] = aRecv->exQuest[a].ExWQuestCount[m];
			this->ewdata[a].MissionType[m] = aRecv->exQuest[a].MissionType[m];
			this->ewdata[a].MissionID[m] = aRecv->exQuest[a].MissionID[m];
			this->ewdata[a].MissionIndex[m] = aRecv->exQuest[a].MissionIndex[m];
			this->ewdata[a].MissionLevel[m] = aRecv->exQuest[a].MissionLevel[m];
			this->ewdata[a].MissionLuck[m] = aRecv->exQuest[a].MissionLuck[m];
			this->ewdata[a].MissionOpt[m] = aRecv->exQuest[a].MissionOpt[m];
			this->ewdata[a].MissionExl[m] = aRecv->exQuest[a].MissionExl[m];
			this->ewdata[a].MissionCount[m] = aRecv->exQuest[a].MissionCount[m];
		}
	}
}
//// ----------------------------------------------------------------------------------------------
//
void ExWinQuestSystem::GC_MiniInfoRecvEx(GC_ExWinMiniInfoEx* aRecv)
{
	int a = aRecv->a;
	int m = aRecv->m;

	if (a < 0 || a >= EW_MAX_ACT)
	{
		return;
	}

	if (m < 0 && m >= EW_MAX_MISSION)
	{
		return;
	}

	this->ewdata[a].Count[m]++;
}
//// ----------------------------------------------------------------------------------------------
//
void ExWinQuestSystem::GC_Start(GC_ExWinStart* aRecv)
{
	int a = aRecv->Act;
	int s = aRecv->Start;

	if (a < 0 || a >= EW_MAX_ACT)
	{
		return;
	}

	if (s == true)
	{
		this->ewdata[a].Start = true;
	}
}
//// ----------------------------------------------------------------------------------------------