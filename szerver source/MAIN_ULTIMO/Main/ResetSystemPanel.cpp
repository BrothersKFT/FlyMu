#include "stdafx.h"
#include "ResetSystemPanel.h"
#include "Protocol.h"
#include "Interface.h"
#include "PrintPlayer.h"
#include "Util.h"
#include "User.h"
#include "GrandResetSystem.h"
#include "Offset.h"
#include "Central.h"
// -------------------------------------------------------------------------------

ResetSystem		gResetSystem;
// -------------------------------------------------------------------------------

ResetSystem::ResetSystem()
{
	//this->Init();
}
// -------------------------------------------------------------------------

ResetSystem::~ResetSystem()
{

}
// -------------------------------------------------------------------------

void ResetSystem::draw_reset_system()
{
	if (!gInterface.Data[OBJECT_RESET_MAIN].OnShow)
	{
		return;
	}

	pSetCursorFocus = true;

	DWORD ItemNameColor = eWhite;
//	const float main_width = 230.0;
//	float start_y = 100.0;
//	const float start_x = (MAX_WIN_WIDTH / 2) - (main_width / 2);
//	const float main_center = start_x + (main_width / 3);
//	const float button_x = main_center - (29.0 / 2);

	float main_width = 230.0;
	float MainHeight = 360.0;
	float start_y = ((MAX_WIN_HEIGHT - 51) / 2) - (MainHeight / 2);
	float start_x = (MAX_WIN_WIDTH / 2) - (main_width / 2);
	float main_center = start_x + (main_width / 3);
	float button_x = main_center - (float)(29.0 / 2);

	gInterface.Data[OBJECT_RESET_MAIN].MaxX = start_x + main_width;
	gInterface.Data[OBJECT_RESET_MAIN].MaxY = start_y + MainHeight;

	gCentral.PrintDropBox(start_x, start_y, main_width, MainHeight, 0, 0);

	gInterface.DrawFormat(eGold, (int)start_x + 10, (int)start_y + 10, 210, 3, "Windows Reset");
	// ----
	gInterface.DrawGUI(OBJECT_RESET_CLOSE, start_x + main_width - gInterface.Data[OBJECT_RESET_CLOSE].Width, start_y);
	// ----
	if (gInterface.IsWorkZone(OBJECT_RESET_CLOSE))
	{
		DWORD Color = eGray100;
		// ----
		if (gInterface.Data[OBJECT_RESET_CLOSE].OnClick)
		{
			Color = eGray150;
		}
		// ----
		gInterface.DrawColoredGUI(OBJECT_RESET_CLOSE, gInterface.Data[OBJECT_RESET_CLOSE].X, gInterface.Data[OBJECT_RESET_CLOSE].Y, Color);
		gInterface.DrawToolTip(gInterface.Data[OBJECT_RESET_CLOSE].X + 5, gInterface.Data[OBJECT_RESET_CLOSE].Y + 25, "Close");
	}

//	gInterface.DrawGUI(OBJECT_RESET_MAIN, start_x, start_y + 2);
//	gInterface.DrawGUI(OBJECT_RESET_TITLE, start_x, start_y);
//	start_y = gInterface.DrawRepeatGUI(OBJECT_RESET_FRAME, start_x, start_y + 67, 13);
//	gInterface.DrawGUI(OBJECT_RESET_FOOTER, start_x, start_y);
//	gInterface.DrawGUI(OBJECT_RESET_CLOSE, start_x + main_width - gInterface.Data[OBJECT_RESET_CLOSE].Width, gInterface.Data[OBJECT_RESET_TITLE].Height + gInterface.Data[OBJECT_RESET_CLOSE].Height + 2);
	// ----
//	if (gInterface.IsWorkZone(OBJECT_RESET_CLOSE))
//	{
//		DWORD Color = eGray100;
		// ----
//		if (gInterface.Data[OBJECT_RESET_CLOSE].OnClick)
//		{
//			Color = eGray150;
//		}
		// ----
//		gInterface.DrawColoredGUI(OBJECT_RESET_CLOSE, gInterface.Data[OBJECT_RESET_CLOSE].X, gInterface.Data[OBJECT_RESET_CLOSE].Y, Color);
//		gInterface.DrawToolTip(int(gInterface.Data[OBJECT_RESET_CLOSE].X) + 5, gInterface.Data[OBJECT_RESET_CLOSE].Y + 25, "Close");
//	}
	// ----
//	gInterface.DrawText(eGold, start_x + 10, 110, 210, 3, "Reset Master");
	// ----
	gInterface.DrawGUI(OBJECT_RESET_INFO_BG, start_x + 30, 140);
	gInterface.DrawText(eGold, start_x + 35, 145, 70, 3, "Next Reset:");
	gInterface.DrawText(eWhite, start_x + 135, 145, 70, 1, "%d", ViewReset + 1);
	gInterface.DrawGUI(OBJECT_RESET_INFO_BG, start_x + 30, 160);
	gInterface.DrawText(eGold, start_x + 35, 165, 70, 3, "Reward Points:");
	//gInterface.DrawText(eWhite, start_x + 135, 165, 70, 1, "%d", this->get_reward_points() + gObjUser.m_QuestStat);
	gInterface.DrawText(eWhite, start_x + 135, 165, 70, 1, "%d", this->get_reward_points());
	// ----
	gInterface.DrawGUI(OBJECT_RESET_DIV, start_x, 185);
	// ----
	gInterface.DrawText(eGold, start_x + 30, 215, 210, 1, "Required Level:");
	// ----
	if (gObjUser.lpPlayer->Level < this->m_ResetData.ReqLevel)
	{
		gInterface.DrawText(eRed, start_x + 30, 225, 210, 1, "- %d (Your: %d)",
			this->m_ResetData.ReqLevel, gObjUser.lpPlayer->Level);
	}
	else
	{
		gInterface.DrawText(eWhite, start_x + 30, 225, 210, 1, "- %d",
			this->m_ResetData.ReqLevel);
	}
	// ----

	gInterface.DrawText(eGold, start_x + main_width - 30, 215, 0, eRightToLeft, "Reward Items:");

	for (int i = 0; i < this->m_ResetData.ItemReward.ItemCount; i++)
	{
		char ItemNameBuff[150];
		ZeroMemory(ItemNameBuff, sizeof(ItemNameBuff));
		if (this->m_ResetData.ItemReward.itemData[i].Count > 0)
		{
			char buff[25];
			sprintf(buff, " %dx ", this->m_ResetData.ItemReward.itemData[i].Count);
			strcat(ItemNameBuff, buff);
		}
		// ----
		strcat(ItemNameBuff, (char*)(*(DWORD*)0x8128AC0 + 84 *
			this->m_ResetData.ItemReward.itemData[i].ID));
		// ----

		gInterface.DrawText(ItemNameColor, start_x + main_width - 30, 225 + (i * 8), 0, eRightToLeft, ItemNameBuff);
	}
	gInterface.DrawText(eGold, start_x + 30, 240, 210, 1, "Required Items:");
	// ----
	for (int i = 0; i < this->m_ResetData.ItemCount; i++)
	{
		char ItemNameBuff[150], LevelBuff[25], OptionBuff[25];
		// ----
		ZeroMemory(ItemNameBuff, sizeof(ItemNameBuff));
		// ----
		if (this->m_ResetData.ItemData[i].Count > 0)
		{
			char buff[25];
			sprintf(buff, " %dx ", this->m_ResetData.ItemData[i].Count);
			strcat(ItemNameBuff, buff);
		}
		// ----
		if (this->m_ResetData.ItemData[i].IsExcellent)
		{
			strcat(ItemNameBuff, "Excellent ");
			ItemNameColor = eExcellent;
		}
		// ----
		if (this->m_ResetData.ItemData[i].IsAncient)
		{
			strcat(ItemNameBuff, "Ancient ");
			ItemNameColor = eAncient;
		}
		// ----
		if (this->m_ResetData.ItemData[i].IsSocket)
		{
			strcat(ItemNameBuff, "Socket ");
			ItemNameColor = eSocket;
		}
		// ----
		strcat(ItemNameBuff, (char*)(*(DWORD*)0x8128AC0 + 84 *
			this->m_ResetData.ItemData[i].ID));
		// ----
		if (this->m_ResetData.ItemData[i].MinLevel
			== this->m_ResetData.ItemData[i].MaxLevel)
		{
			ZeroMemory(LevelBuff, sizeof(LevelBuff));
			sprintf(LevelBuff, " [+%d, ", this->m_ResetData.ItemData[i].MinLevel);
			strcat(ItemNameBuff, LevelBuff);
		}
		else
		{
			ZeroMemory(LevelBuff, sizeof(LevelBuff));
			sprintf(LevelBuff, " [+%d~%d, ",
				this->m_ResetData.ItemData[i].MinLevel,
				this->m_ResetData.ItemData[i].MaxLevel);
			strcat(ItemNameBuff, LevelBuff);
		}
		// ----
		if (this->m_ResetData.ItemData[i].MinOption
			== this->m_ResetData.ItemData[i].MaxOption)
		{
			ZeroMemory(OptionBuff, sizeof(OptionBuff));
			sprintf(OptionBuff, "+%d] ", this->m_ResetData.ItemData[i].MinOption * 4);
			strcat(ItemNameBuff, OptionBuff);
		}
		else
		{
			ZeroMemory(OptionBuff, sizeof(OptionBuff));
			sprintf(OptionBuff, "+%d~%d] ",
				this->m_ResetData.ItemData[i].MinOption * 4,
				this->m_ResetData.ItemData[i].MaxOption * 4);
			strcat(ItemNameBuff, OptionBuff);
		}
		// ----
		if (this->m_ResetData.ItemData[i].IsLuck == 0)
		{
			strcat(ItemNameBuff, "+ Without Luck ");
		}
		else if (this->m_ResetData.ItemData[i].IsLuck == 1)
		{
			strcat(ItemNameBuff, "+ Luck ");
		}
		// ----
		if (this->m_ResetData.ItemData[i].IsSkill == 0)
		{
			strcat(ItemNameBuff, "+ Without Skill");
		}
		else if (this->m_ResetData.ItemData[i].IsSkill == 1)
		{
			strcat(ItemNameBuff, "+ Skill");
		}
		// ----
		if (!gObjUser.m_reset_item_check[i])
		{
			pDrawGUI(0x7BC4, start_x + 22.0, 251 + (i * 8), 7.0, 7.0);
		}
		else
		{
			pDrawGUI(0x7BC1, start_x + 22.0, 251 + (i * 8), 7.0, 7.0);
		}
		// ----
		gInterface.DrawText(ItemNameColor, start_x + 30, 250 + (i * 8), 210, 1, ItemNameBuff);

	}
	// ----
	if (this->m_ResetData.ItemCount <= 0)
	{
		gInterface.DrawText(eWhite, start_x + 30, 250, 210, 1, "- None");
	}
	// ----
	gInterface.DrawText(eGold, start_x + 30, 295, 210, 1, "Required Zen:");
	gInterface.DrawGUI(OBJECT_RESET_MONEY_BG, start_x + 30, 305);
	// ----
	char MoneyBuff[50], MoneyBuff2[50];
	ZeroMemory(MoneyBuff, sizeof(MoneyBuff));
	ZeroMemory(MoneyBuff2, sizeof(MoneyBuff2));
	// ----
	if (gObjUser.lpPlayer->MoneyInventory
		< this->get_reset_money())
	{
		pGetMoneyFormat((double)this->get_reset_money(),
			MoneyBuff, 0);
		pGetMoneyFormat((double)this->get_reset_money() - gObjUser.lpPlayer->MoneyInventory,
			MoneyBuff2, 0);
		gInterface.DrawText(eRed, start_x + 70, 309, 170, 1, "%s\n(Need still %s)",
			MoneyBuff, MoneyBuff2);
	}
	else
	{
		pGetMoneyFormat((double)this->get_reset_money(),
			MoneyBuff, 0);
		gInterface.DrawText(eGold, start_x + 70, 312, 70, 1, "%s",
			MoneyBuff);
	}
	// ----
//	gInterface.DrawGUI(OBJECT_RESET_FINISH, button_x, gInterface.Data[OBJECT_RESET_FOOTER].Y + 10);
//	gInterface.DrawText(eWhite, start_x + 8, gInterface.Data[OBJECT_RESET_FOOTER].Y + 20, 210, 3, "Make Reset");
//	gInterface.DrawGUI(OBJECT_RESET_DIV, start_x, gInterface.Data[OBJECT_RESET_FOOTER].Y - 10);
	// ----
	if (this->m_ResetData.UseItemReward)
	{
		for (int i = 0; i < this->m_ResetData.ItemReward.ItemCount; i++)
		{
			if (gInterface.IsWorkZone2(start_x + main_width / 2, 225 + (i * 8), start_x + main_width - 30, 232 + (i * 8)))
			{
				RESET_ITEM_REWARD_ITEM* item = &this->m_ResetData.ItemReward.itemData[i];
				const auto ItemInfo = pGetItemBmdStruct(item->ID);
				const int WidthValue = 18;
				const int HeightValue = 20;
				const float barWidth = WidthValue * ItemInfo->ItemWidth;
				const float barHeight = HeightValue * ItemInfo->ItemHeight;
				float X = pCursorX - barWidth / 2;
				float Y = pCursorY - barHeight - 5;
				gInterface.DrawBarForm(X, Y, barWidth, barHeight, 0.04, 0.34, 0.0, 1.0);//ReqItems

				int ExcOpt = 0;

				if (item->ExcType == 1)
				{
					ExcOpt = item->ExcCode;
				}
				else
				{
					ExcOpt = item->MaxExcOption;
				}

				gInterface.DrawItemIMG(X, Y, barWidth, barHeight, item->ID, SET_ITEMOPT_LEVEL(item->MinLevel), ExcOpt, item->IsAncient, 0);
			}
		}
	}
	// ----
	if (!this->check_all_req())
	{
		gInterface.Data[OBJECT_RESET_FINISH].Attribute = false;
		gInterface.DrawColoredGUI(OBJECT_RESET_FINISH, gInterface.Data[OBJECT_RESET_FINISH].X, gInterface.Data[OBJECT_RESET_FINISH].Y, eGray150);
		return;
	}
	// ----
	gInterface.Data[OBJECT_RESET_FINISH].Attribute = true;
	// ----
	if (gInterface.IsWorkZone(OBJECT_RESET_FINISH))
	{
		if (gInterface.Data[OBJECT_RESET_FINISH].OnClick)
		{
			PlayBuffer(25, 0, 0);
			gInterface.DrawButtonRender(OBJECT_RESET_FINISH, start_x + (main_width / 2) - (110 / 2), start_y + MainHeight - 32, 0, 28);
		}
		else
		{
			gInterface.DrawButtonRender(OBJECT_RESET_FINISH, start_x + (main_width / 2) - (110 / 2), start_y + MainHeight - 32, 0, 0);
		}
	}
	else
	{
		gInterface.DrawButtonRender(OBJECT_RESET_FINISH, start_x + (main_width / 2) - (110 / 2), start_y + MainHeight - 32, 0, 0);
	}

	gInterface.DrawFormat(eWhite, start_x + (main_width / 2) - (70 / 2), start_y + MainHeight - 25, 59, 3, "Make Reset");

//	if (gInterface.IsWorkZone(OBJECT_RESET_FINISH))
//	{
//		DWORD Color = eGray100;
		// ----
//		if (gInterface.Data[OBJECT_RESET_FINISH].OnClick)
//		{
//			Color = eGray150;
//		}
		// ----
//		gInterface.DrawColoredGUI(OBJECT_RESET_FINISH, gInterface.Data[OBJECT_RESET_FINISH].X, gInterface.Data[OBJECT_RESET_FINISH].Y, Color);
//	}
}

bool ResetSystem::EventResetWindow_Main(DWORD Event)
{
	this->EventResetWindow_Close(Event);
	this->EventResetWindow_Finish(Event);
	return true;
}

bool ResetSystem::EventResetWindow_Close(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - gInterface.Data[OBJECT_RESET_CLOSE].EventTick);
	// ----
	if (!gInterface.Data[OBJECT_RESET_MAIN].OnShow || !gInterface.IsWorkZone(OBJECT_RESET_CLOSE))
	{
		return false;
	}
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		gInterface.Data[OBJECT_RESET_CLOSE].OnClick = true;
		return true;
	}
	// ----
	gInterface.Data[OBJECT_RESET_CLOSE].OnClick = false;
	// ----
	if (Delay < 500)
	{
		return false;
	}
	// ----
	gInterface.Data[OBJECT_RESET_CLOSE].EventTick = GetTickCount();
	gInterface.Data[OBJECT_RESET_MAIN].Close();
	// ----
	return false;
}
// ----------------------------------------------------------------------------------------------

bool ResetSystem::EventResetWindow_Finish(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - gInterface.Data[OBJECT_RESET_FINISH].EventTick);
	// ----
	if (!gInterface.Data[OBJECT_RESET_MAIN].OnShow || !gInterface.IsWorkZone(OBJECT_RESET_FINISH)
		|| !gInterface.Data[OBJECT_RESET_FINISH].Attribute)
	{
		return false;
	}
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		gInterface.Data[OBJECT_RESET_FINISH].OnClick = true;
		return true;
	}
	// ----
	gInterface.Data[OBJECT_RESET_FINISH].OnClick = false;;
	// ----
	if (Delay < 500)
	{
		return false;
	}
	// ----
	gInterface.Data[OBJECT_RESET_FINISH].EventTick = GetTickCount();
	this->req_reset_finish();
	// ----
	return false;
}

int ResetSystem::get_reset_money() const
{
	return this->ResetMoney;
}
// -------------------------------------------------------------------------

bool ResetSystem::check_all_req() const
{
	if (gObjUser.lpPlayer->MoneyInventory
		< this->ResetMoney)
	{
		return false;
	}
	// ----
	if (gObjUser.lpPlayer->Level < this->m_ResetData.ReqLevel)
	{
		return false;
	}
	// ----
	for (int i = 0; i < this->m_ResetData.ItemCount; i++)
	{
		if (!gObjUser.m_reset_item_check[i])
		{
			return false;
		}
	}
	// ----
	return true;
}

void ResetSystem::reset_message_recv(RESET_RESULT_SEND* lpMsg)
{
	if (lpMsg->result == 0x01)
	{
		gInterface.DrawMessageBox("You can't make reset on this map!");
	}
	else if (lpMsg->result == 0x02)
	{
		gInterface.DrawMessageBox("You can't make grand reset on this map!");
	}
}

// -------------------------------------------------------------------------

void ResetSystem::set_data(RESET_ANS_USERDATA* lpMsg)
{
	//gConsole.AddMessage(5, "get reset info");
	ZeroMemory(gObjUser.m_reset_item_check, sizeof(gObjUser.m_reset_item_check));
	// ----
	ViewReset = lpMsg->Reset;
	ViewGReset = lpMsg->GrandReset;

	this->ResetMoney = lpMsg->ResetMoney;
	this->m_BonusCommand = lpMsg->CommandPerReset;

	//gObjUser.m_QuestStat = lpMsg->QuestStat;

	this->m_ResetData = lpMsg->ResetData;

	for (int i = 0; i < 5; i++)
	{
		gObjUser.m_reset_item_check[i] = lpMsg->ItemCheck[i];
	}
	// ----
	if (lpMsg->ByDialog)
	{
		//this->reset_system_switch_state();
		gInterface.Data[OBJECT_RESET_MAIN].Open();
	}
}
// -------------------------------------------------------------------------

void ResetSystem::req_reset_finish()
{
	RESET_REQ_USERDATA pMsg;
	pMsg.h.set(0xFD, 0x01, sizeof(pMsg));
	DataSend((BYTE*)&pMsg, pMsg.h.size);
}
// -------------------------------------------------------------------------

void ResetSystem::get_reset_result()
{
	//this->reset_system_switch_state();
	gInterface.Data[OBJECT_RESET_MAIN].Close();
}
// -------------------------------------------------------------------------

int ResetSystem::get_reward_points() const
{
	return this->m_ResetData.RewardData.LevelPoint + gGrandResetSystem.get_reward_points(0);
}
