#include "stdafx.h"
#include "SmithItem.h"
#include "Protocol.h"
#include "Interface.h"
#include "Defines.h"
#include "CSmithItem.h"
#include "Protect.h"

cSmithItem gSmithItem;

cSmithItem::cSmithItem(){
	this->ItemType = 0;
	this->ItemIndex = 0;
	this->Days = 0;
	this->mLevel = 0;
	this->mSkill = 0;
	this->mLuck = 0;
	this->mOpt = 0;
	this->ExcOption = 0;
	this->ExcOption1 = 0;
	this->ExcOption2 = 0;
	this->ExcOption3 = 0;
	this->ExcOption4 = 0;
	this->ExcOption5 = 0;
	this->mExc = 0;
	this->TotalPrice = 0;
}

cSmithItem::~cSmithItem(){
}

void cSmithItem::Bind(){
	gInterface.BindObject(eUNCHECK_2, iOptionCheck, 15, 15, 175, 60);
	gInterface.BindObject(eUNCHECK_3, iOptionCheck, 15, 15, 175, 90);
	gInterface.BindObject(eUNCHECK_6, iOptionCheck, 15, 15, 195, 90);
	gInterface.BindObject(eUNCHECK_4, iOptionCheck, 15, 15, 175, 120);
	gInterface.BindObject(eUNCHECK_5, iOptionCheck, 15, 15, 175, 150);
	gInterface.BindObject(eCHECKED_2, iOptionCheck, 15, 15, 175, 60);
	gInterface.BindObject(eCHECKED_3, iOptionCheck, 15, 15, 175, 90);
	gInterface.BindObject(eCHECKED_6, iOptionCheck, 15, 15, 195, 90);
	gInterface.BindObject(eCHECKED_4, iOptionCheck, 15, 15, 175, 120);
	gInterface.BindObject(eCHECKED_5, iOptionCheck, 15, 15, 175, 150);
	gInterface.BindObject(eSMITH_MAIN, 0x7A5A, 222, 383, -1, -1);
	gInterface.BindObject(eSMITH_TITLE, 0x7A63, 230, 67, -1, -1);
	gInterface.BindObject(eSMITH_FOOTER, 0x7A59, 230, 50, -1, -1);
	gInterface.BindObject(eSMITH_FRAME, 0x7A58, 230, 15, -1, -1);
	gInterface.BindObject(eSMITH_DIV, 0x7A62, 223, 21, -1, -1);
	gInterface.BindObject(eSMITH_CLOSE, 0x7EC5, 36, 29, -1, -1);
	gInterface.BindObject(eSMITH_BUY, 0x7A5E, 128, 29, -1, -1);
	gInterface.BindObject(eSMITH_ITEMTYPE, 0x7C0D, 16, 15, 215, 70);
	gInterface.BindObject(eSMITH_ITEMTYPE_1, 0xAA4, 16, 15, 273, 70);
	gInterface.BindObject(eSMITH_ITEMINDEX, 0x7C0D, 17, 18, 208, 103);
	gInterface.BindObject(eSMITH_ITEMINDEX_1, 0xAA4, 17, 18, 400, 103);
	gInterface.BindObject(eSMITH_DAYS, 0x7C0D, 16, 15, 340, 70);
	gInterface.BindObject(eSMITH_DAYS_1, 0xAA4, 16, 15, 393, 70);
	gInterface.BindObject(eSMITH_LEVEL, 0x7C0D, 16, 15, 340, 153);
	gInterface.BindObject(eSMITH_LEVEL_1, 0xAA4, 16, 15, 380, 153);
	gInterface.BindObject(eSMITH_OPT, 0x7C0D, 16, 15, 340, 213);
	gInterface.BindObject(eSMITH_OPT_1, 0xAA4, 16, 15, 380, 213);
	gInterface.BindObject(eSMITH_SKILL, 0x7B69, 15, 15, 380, 175);
	gInterface.BindObject(eSMITH_SKILL_1, 0x7B69, 15, 15, 380, 175);
	gInterface.BindObject(eSMITH_LUCK, 0x7B69, 15, 15, 380, 195);
	gInterface.BindObject(eSMITH_LUCK_1, 0x7B69, 15, 15, 380, 195);
	gInterface.BindObject(eSMITH_EXC, 0x7B69, 15, 15, 380, 235);
	gInterface.BindObject(eSMITH_EXC_1, 0x7B69, 15, 15, 380, 235);
	gInterface.BindObject(eSMITH_EXC1, 0x7B69, 15, 15, 380, 255);
	gInterface.BindObject(eSMITH_EXC1_1, 0x7B69, 15, 15, 380, 255);
	gInterface.BindObject(eSMITH_EXC2, 0x7B69, 15, 15, 380, 275);
	gInterface.BindObject(eSMITH_EXC2_1, 0x7B69, 15, 15, 380, 275);
	gInterface.BindObject(eSMITH_EXC3, 0x7B69, 15, 15, 380, 295);
	gInterface.BindObject(eSMITH_EXC3_1, 0x7B69, 15, 15, 380, 295);
	gInterface.BindObject(eSMITH_EXC4, 0x7B69, 15, 15, 380, 315);
	gInterface.BindObject(eSMITH_EXC4_1, 0x7B69, 15, 15, 380, 315);
	gInterface.BindObject(eSMITH_EXC5, 0x7B69, 15, 15, 380, 335);
	gInterface.BindObject(eSMITH_EXC5_1, 0x7B69, 15, 15, 380, 335);
}

void cSmithItem::GetInfo(SDHP_SENDSVSHOP * lpMsg){
	this->MaxLevel = lpMsg->MaxLevel;
	this->MaxSkill = lpMsg->MaxSkill;
	this->MaxLuck = lpMsg->MaxLuck;
	this->MaxOpt = lpMsg->MaxOpt;
	this->MaxExc = lpMsg->MaxExc;
	this->pLevel = lpMsg->pLevel;
	this->pSkill = lpMsg->pSkill;
	this->pLuck = lpMsg->pLuck;
	this->pOpt = lpMsg->pOpt;
	this->pExc = lpMsg->pExc;
	this->pExc1 = lpMsg->pExc1;
	this->pExc2 = lpMsg->pExc2;
	this->pExc3 = lpMsg->pExc3;
	this->pExc4 = lpMsg->pExc4;
	this->pExc5 = lpMsg->pExc5;
	this->TotalPrice = lpMsg->TotalPrice;
}

void cSmithItem::DrawSmithItem(){
	if (gInterface.CheckWindow(CashShop) || gInterface.CheckWindow(ChaosBox) || gInterface.CheckWindow(FullMap) || gInterface.CheckWindow(SkillTree) ||
		gInterface.CheckWindow(Warehouse) || gInterface.CheckWindow(Shop) || gInterface.CheckWindow(Trade) || gInterface.CheckWindow(ExpandInventory) ||
		gInterface.CheckWindow(ExpandWarehouse))
		return;
	if (!gInterface.Data[eSMITH_MAIN].OnShow){
		return;
	}
	pSetCursorFocus = true;
	float MainWidth, MainHeight, StartY, StartX, MainCenter, ButtonX, ticket, button1, button2, text1;
	MainWidth = 230.0f;
	MainHeight = 313.0f;
	StartY = 100.0f;
	StartX = (MAX_WIN_WIDTH / 2.0f) - (MainWidth / 2.0f);
	MainCenter = StartX + (MainWidth / 3.0f);
	ButtonX = MainCenter - (29.0f / 2.0f);
	gInterface.DrawGUI(eSMITH_MAIN, StartX, StartY - 78);
	gInterface.DrawGUI(eSMITH_TITLE, StartX, StartY - 80);
	StartY = gInterface.DrawRepeatGUI(eSMITH_FRAME, StartX, StartY - 13.0, 13);
	gInterface.DrawGUI(eSMITH_FOOTER, StartX, StartY + 80);
	pDrawGUI(0x7A7B, StartX, 275, 5, 100);
	pDrawGUI(0x7A7B, StartX + 221, 276, 5, 100);
	gInterface.DrawGUI(eSMITH_CLOSE, StartX + MainWidth - gInterface.Data[eSMITH_CLOSE].Width, gInterface.Data[eSMITH_TITLE].Height + gInterface.Data[eSMITH_CLOSE].Height - 78);
	if (gProtect.m_MainInfo.CustomTypeSmithItem == 0){
		gInterface.DrawFormat(eGold, StartX + 95, 30, 25, 5, "SmithItem");
	}
	else{
		gInterface.DrawFormat(eGold, StartX + 95, 30, 25, 5, "ShopItem");
	}
	if (gInterface.IsWorkZone(eSMITH_CLOSE)){
		DWORD Color = eGray100;
		if (gInterface.Data[eSMITH_CLOSE].OnClick){
			Color = eGray150;
		}
		gInterface.DrawColoredGUI(eSMITH_CLOSE, gInterface.Data[eSMITH_CLOSE].X, gInterface.Data[eSMITH_CLOSE].Y, Color);
		gInterface.DrawToolTip(gInterface.Data[eSMITH_CLOSE].X + 5, gInterface.Data[eSMITH_CLOSE].Y + 25, "Close");
	}
	float button1Time, button2Time, TextTitleTime, TextTime;
	ticket = StartX + 180;
	button1 = StartX + 140;
	button2 = StartX + 180;
	text1 = StartX + 155;
	button1Time = StartX + 140;
	button2Time = StartX + 193;
	TextTitleTime = StartX + 160;
	TextTime = StartX + 163;
	gInterface.DrawFormat(eGold, StartX + 30, 50, 210, 1, "Group Item");
	pDrawGUI(0x7C0D, StartX + 15, 70, 16, 15);
	pDrawGUI(0x7AA4, StartX + 73, 70, 16, 15);
	switch (gSmithItem.ItemType){
	case 0:
		gInterface.DrawFormat(eGold, StartX + 40, 73, 25, 5, "Sword");
		break;
	case 1:
		gInterface.DrawFormat(eGold, StartX + 40, 73, 25, 5, "Axe");
		break;
	case 2:
		gInterface.DrawFormat(eGold, StartX + 40, 73, 25, 5, "Scepter");
		break;
	case 3:
		gInterface.DrawFormat(eGold, StartX + 40, 73, 25, 5, "Spear");
		break;
	case 4:
		gInterface.DrawFormat(eGold, StartX + 40, 73, 25, 5, "Bow");
		break;
	case 5:
		gInterface.DrawFormat(eGold, StartX + 40, 73, 25, 5, "Staff");
		break;
	case 6:
		gInterface.DrawFormat(eGold, StartX + 40, 73, 25, 5, "Shield");
		break;
	case 7:
		gInterface.DrawFormat(eGold, StartX + 40, 73, 25, 5, "Helm");
		break;
	case 8:
		gInterface.DrawFormat(eGold, StartX + 40, 73, 25, 5, "Armor");
		break;
	case 9:
		gInterface.DrawFormat(eGold, StartX + 40, 73, 25, 5, "Pant");
		break;
	case 10:
		gInterface.DrawFormat(eGold, StartX + 40, 73, 25, 5, "Glove");
		break;
	case 11:
		gInterface.DrawFormat(eGold, StartX + 40, 73, 25, 5, "Boot");
		break;
	}
	if (gProtect.m_MainInfo.CustomTypeSmithItem == 0){
		gInterface.DrawFormat(eGold, TextTitleTime, 50, 210, 1, "Item Time");
		pDrawGUI(0x7C0D, button1Time, 70, 16, 15);
		pDrawGUI(0x7AA4, button2Time, 70, 16, 15);
		switch (gSmithItem.Days){
		case 0:
			gInterface.DrawFormat(eGold, TextTime, 73, 25, 5, "1 Days");
			break;
		case 1:
			gInterface.DrawFormat(eGold, TextTime, 73, 25, 5, "7 Days");
			break;
		case 2:
			gInterface.DrawFormat(eGold, TextTime, 73, 25, 5, "30 Days");
			break;
		}
	}
	float ButtonIzquierdaX, ButtonDerechaX, ButtonsY, panelStartX, panelStartY, textItemsX, textItemsY;
	float drawItemX, drawItemY, drawItemX1, drawItemX2, drawItemY1, drawItemY2, drawItemY3;
	ButtonIzquierdaX = StartX + 8;
	ButtonDerechaX = StartX + 200;
	ButtonsY = 103;
	panelStartX = StartX + 27;
	panelStartY = 100;
	textItemsX = StartX + 35;
	textItemsY = 106;
	if (gProtect.m_MainInfo.CustomTypeSmithItem == 1){
		drawItemX = StartX + 85;
		drawItemX1 = StartX + 90;
		drawItemX2 = StartX + 95;
	}
	else{
		drawItemX = StartX + 40;
		drawItemX1 = StartX + 55;
		drawItemX2 = StartX + 65;
	}
	drawItemY = 20;
	drawItemY1 = 15;
	drawItemY2 = 5;
	drawItemY3 = 10;
	pDrawGUI(0x79A2, panelStartX, panelStartY, 171, 23);
	pDrawGUI(0x7BAA, ButtonIzquierdaX, ButtonsY, 17, 18);
	pDrawGUI(0x7BAB, ButtonDerechaX, ButtonsY, 17, 18);
	switch (gSmithItem.ItemType){
	case 0:
		gInterface.DrawItemIMG(drawItemX, drawItemY, 100, 100, ITEM(gSmithItem.ItemType, gSmithItem.ItemIndex), gSmithItem.mLevel, gSmithItem.mExc, 0, 0);
		gInterface.DrawFormat(eGold, textItemsX, textItemsY, 25, 5, "%s", gCustomSmith.m_SmithSwordInfo[gSmithItem.ItemIndex].ItemName);
		break;
	case 1:
		gInterface.DrawItemIMG(drawItemX, drawItemY, 100, 100, ITEM(gSmithItem.ItemType, gSmithItem.ItemIndex), gSmithItem.mLevel, gSmithItem.mExc, 0, 0);
		gInterface.DrawFormat(eGold, textItemsX, textItemsY, 25, 5, "%s", gCustomSmith.m_SmithAxeInfo[gSmithItem.ItemIndex].ItemName);
		break;
	case 2:
		gInterface.DrawItemIMG(drawItemX, drawItemY, 100, 100, ITEM(gSmithItem.ItemType, gSmithItem.ItemIndex), gSmithItem.mLevel, gSmithItem.mExc, 0, 0);
		gInterface.DrawFormat(eGold, textItemsX, textItemsY, 25, 5, "%s", gCustomSmith.m_SmithMaceInfo[gSmithItem.ItemIndex].ItemName);
		break;
	case 3:
		gInterface.DrawItemIMG(drawItemX1, drawItemY, 100, 100, ITEM(gSmithItem.ItemType, gSmithItem.ItemIndex), gSmithItem.mLevel, gSmithItem.mExc, 0, 0);
		gInterface.DrawFormat(eGold, textItemsX, textItemsY, 25, 5, "%s", gCustomSmith.m_SmithSpearInfo[gSmithItem.ItemIndex].ItemName);
		break;
	case 4:
		gInterface.DrawItemIMG(drawItemX2, drawItemY, 100, 100, ITEM(gSmithItem.ItemType, gSmithItem.ItemIndex), gSmithItem.mLevel, gSmithItem.mExc, 0, 0);
		gInterface.DrawFormat(eGold, textItemsX, textItemsY, 25, 5, "%s", gCustomSmith.m_SmithBowInfo[gSmithItem.ItemIndex].ItemName);
		break;
	case 5:
		gInterface.DrawItemIMG(drawItemX1, drawItemY, 100, 100, ITEM(gSmithItem.ItemType, gSmithItem.ItemIndex), gSmithItem.mLevel, gSmithItem.mExc, 0, 0);
		gInterface.DrawFormat(eGold, textItemsX, textItemsY, 25, 5, "%s", gCustomSmith.m_SmithStaffInfo[gSmithItem.ItemIndex].ItemName);
		break;
	case 6:
		gInterface.DrawItemIMG(drawItemX2, drawItemY, 100, 100, ITEM(gSmithItem.ItemType, gSmithItem.ItemIndex), gSmithItem.mLevel, gSmithItem.mExc, 0, 0);
		gInterface.DrawFormat(eGold, textItemsX, textItemsY, 25, 5, "%s", gCustomSmith.m_SmithShieldInfo[gSmithItem.ItemIndex].ItemName);
		break;
	case 7:
		gInterface.DrawItemIMG(drawItemX2, drawItemY3, 100, 100, ITEM(gSmithItem.ItemType, gSmithItem.ItemIndex), gSmithItem.mLevel, gSmithItem.mExc, 0, 0);
		gInterface.DrawFormat(eGold, textItemsX, textItemsY, 25, 5, "%s", gCustomSmith.m_SmithHelmInfo[gSmithItem.ItemIndex].ItemName);
		break;
	case 8:
		gInterface.DrawItemIMG(drawItemX2, drawItemY1, 100, 100, ITEM(gSmithItem.ItemType, gSmithItem.ItemIndex), gSmithItem.mLevel, gSmithItem.mExc, 0, 0);
		gInterface.DrawFormat(eGold, textItemsX, textItemsY, 25, 5, "%s", gCustomSmith.m_SmithArmorInfo[gSmithItem.ItemIndex].ItemName);
		break;
	case 9:
		gInterface.DrawItemIMG(drawItemX2, drawItemY2, 100, 100, ITEM(gSmithItem.ItemType, gSmithItem.ItemIndex), gSmithItem.mLevel, gSmithItem.mExc, 0, 0);
		gInterface.DrawFormat(eGold, textItemsX, textItemsY, 25, 5, "%s", gCustomSmith.m_SmithPantInfo[gSmithItem.ItemIndex].ItemName);
		break;
	case 10:
		gInterface.DrawItemIMG(drawItemX2, drawItemY2, 100, 100, ITEM(gSmithItem.ItemType, gSmithItem.ItemIndex), gSmithItem.mLevel, gSmithItem.mExc, 0, 0);
		gInterface.DrawFormat(eGold, textItemsX, textItemsY, 25, 5, "%s", gCustomSmith.m_SmithGloveInfo[gSmithItem.ItemIndex].ItemName);
		break;
	case 11:
		gInterface.DrawItemIMG(drawItemX2, drawItemY2, 100, 100, ITEM(gSmithItem.ItemType, gSmithItem.ItemIndex), gSmithItem.mLevel, gSmithItem.mExc, 0, 0);
		gInterface.DrawFormat(eGold, textItemsX, textItemsY, 25, 5, "%s", gCustomSmith.m_SmithBootInfo[gSmithItem.ItemIndex].ItemName);
		break;
	}
	gInterface.DrawGUI(eSMITH_DIV, StartX, 130);
	for (int i = 0; i < 10; i++){
		pDrawGUI(iOptionDot, StartX + 15, 147 + (20 * i) + 9, 10, 10);
		pDrawGUI(0x7B5E, StartX + 30, 160 + (20 * i) + 9, 82.0, 2.0);
		pDrawGUI(0x7B5E, StartX + 30 + 82, 160 + (20 * i) + 9, 82.0, 2.0);
	}
	/*Level*/
	gInterface.DrawFormat(eGold, StartX + 40, 155, 15, 5, "Item Level");
	pDrawGUI(0x7C0D, button1, 153, 16, 15);
	pDrawGUI(0x7AA4, button2, 153, 16, 15);
	gInterface.DrawFormat(eGold, text1, 155, 25, 5, "     %d", gSmithItem.mLevel);
	/*Skill*/
	gInterface.DrawFormat(eGold, StartX + 40, 175, 15, 5, "Item Skill");
	pDrawButton(iOptionCheck, ticket, 175, 15, 15, 0, 15);
	if (gSmithItem.mSkill == 1){
		pDrawButton(iOptionCheck, ticket, 175, 15, 15, 0, 0);
	}
	/*Luck*/
	gInterface.DrawFormat(eGold, StartX + 40, 195, 15, 5, "Lucky Option");
	pDrawButton(iOptionCheck, ticket, 195, 15, 15, 0, 15);
	if (gSmithItem.mLuck == 1){
		pDrawButton(iOptionCheck, ticket, 195, 15, 15, 0, 0);
	}
	/*Option[Life]*/
	gInterface.DrawFormat(eGold, StartX + 40, 215, 15, 5, "Add Option");
	pDrawGUI(0x7C0D, button1, 213, 16, 15);
	pDrawGUI(0x7AA4, button2, 213, 16, 15);
	gInterface.DrawFormat(eGold, text1, 215, 25, 5, "     %d", gSmithItem.mOpt);
	/*----*/
	if (gSmithItem.ItemType <= 5){
		gInterface.DrawFormat(eGold, StartX + 40, 235, 15, 5, "Excellent Damange Rate");
		pDrawButton(iOptionCheck, ticket, 235, 15, 15, 0, 15);
		if (gSmithItem.ExcOption == 32){
			pDrawButton(iOptionCheck, ticket, 235, 15, 15, 0, 0);
		}
		/*------*/
		gInterface.DrawFormat(eGold, StartX + 40, 255, 15, 5, "Increase Damage Level");
		pDrawButton(iOptionCheck, ticket, 255, 15, 15, 0, 15);
		if (gSmithItem.ExcOption1 == 16){
			pDrawButton(iOptionCheck, ticket, 255, 15, 15, 0, 0);
		}
		/*------*/
		gInterface.DrawFormat(eGold, StartX + 40, 275, 15, 5, "Increase Damage");
		pDrawButton(iOptionCheck, ticket, 275, 15, 15, 0, 15);
		if (gSmithItem.ExcOption2 == 8){
			pDrawButton(iOptionCheck, ticket, 275, 15, 15, 0, 0);
		}
		/*------*/
		gInterface.DrawFormat(eGold, StartX + 40, 295, 15, 5, "Increase Attacking(Wizard)Speed");
		pDrawButton(iOptionCheck, ticket, 295, 15, 15, 0, 15);
		if (gSmithItem.ExcOption3 == 4){
			pDrawButton(iOptionCheck, ticket, 295, 15, 15, 0, 0);
		}
		/*------*/
		gInterface.DrawFormat(eGold, StartX + 40, 315, 15, 5, "Increase Life Hunting Monster");
		pDrawButton(iOptionCheck, ticket, 315, 15, 15, 0, 15);
		if (gSmithItem.ExcOption4 == 2){
			pDrawButton(iOptionCheck, ticket, 315, 15, 15, 0, 0);
		}
		/*------*/
		gInterface.DrawFormat(eGold, StartX + 40, 335, 15, 5, "Increase Mana Hunting Monster");
		pDrawButton(iOptionCheck, ticket, 335, 15, 15, 0, 15);
		if (gSmithItem.ExcOption5 == 1){
			pDrawButton(iOptionCheck, ticket, 335, 15, 15, 0, 0);
		}
	}
	if (gSmithItem.ItemType >= 6){
		gInterface.DrawFormat(eGold, StartX + 40, 235, 15, 5, "Increase Max HP");
		pDrawButton(iOptionCheck, ticket, 235, 15, 15, 0, 15);
		if (gSmithItem.ExcOption == 32){
			pDrawButton(iOptionCheck, ticket, 235, 15, 15, 0, 0);
		}
		gInterface.DrawFormat(eGold, StartX + 40, 255, 15, 5, "Increase Max Mana");
		pDrawButton(iOptionCheck, ticket, 255, 15, 15, 0, 15);
		if (gSmithItem.ExcOption1 == 16){
			pDrawButton(iOptionCheck, ticket, 255, 15, 15, 0, 0);
		}
		gInterface.DrawFormat(eGold, StartX + 40, 275, 15, 5, "Damage Decrease");
		pDrawButton(iOptionCheck, ticket, 275, 15, 15, 0, 15);
		if (gSmithItem.ExcOption2 == 8){
			pDrawButton(iOptionCheck, ticket, 275, 15, 15, 0, 0);
		}
		gInterface.DrawFormat(eGold, StartX + 40, 295, 15, 5, "Reflect Damage");
		pDrawButton(iOptionCheck, ticket, 295, 15, 15, 0, 15);
		if (gSmithItem.ExcOption3 == 4){
			pDrawButton(iOptionCheck, ticket, 295, 15, 15, 0, 0);
		}
		gInterface.DrawFormat(eGold, StartX + 40, 315, 15, 5, "Defense Success Rate");
		pDrawButton(iOptionCheck, ticket, 315, 15, 15, 0, 15);
		if (gSmithItem.ExcOption4 == 2){
			pDrawButton(iOptionCheck, ticket, 315, 15, 15, 0, 0);
		}
		gInterface.DrawFormat(eGold, StartX + 40, 335, 15, 5, "Zen After Hunting Monsters");
		pDrawButton(iOptionCheck, ticket, 335, 15, 15, 0, 15);
		if (gSmithItem.ExcOption5 == 1){
			pDrawButton(iOptionCheck, ticket, 335, 15, 15, 0, 0);
		}
	}
	gInterface.DrawGUI(eSMITH_DIV, StartX, gInterface.Data[eSMITH_FOOTER].Y - 15);
	gInterface.DrawGUI(eSMITH_BUY, ButtonX, gInterface.Data[eSMITH_FOOTER].Y + 10);
	gInterface.DrawFormat(eGold, StartX + 105, gInterface.Data[eSMITH_FOOTER].Y + 15, 15, 5, "Buy Item");
	if (gInterface.IsWorkZone(eSMITH_BUY)){
		DWORD Color = eGray100;
		if (gInterface.Data[eSMITH_BUY].OnClick){
			Color = eGray150;
		}
		gInterface.DrawColoredGUI(eSMITH_BUY, gInterface.Data[eSMITH_BUY].X, gInterface.Data[eSMITH_BUY].Y, Color);
	}
	float priceTextX, priceTextY;
	priceTextX = StartX + 150;
	priceTextY = 106;
	if (gSmithItem.ItemType == 0){
		switch (gSmithItem.Days){
		case 0:
			gInterface.DrawFormat(eRed, priceTextX, priceTextY, 15, 5, "Price %d", gCustomSmith.m_SmithSwordInfo[gSmithItem.ItemIndex].Price1Days + gSmithItem.TotalPrice);
			break;
		case 1:
			gInterface.DrawFormat(eRed, priceTextX, priceTextY, 15, 5, "Price %d", gCustomSmith.m_SmithSwordInfo[gSmithItem.ItemIndex].Price7Days + gSmithItem.TotalPrice);
			break;
		case 2:
			gInterface.DrawFormat(eRed, priceTextX, priceTextY, 15, 5, "Price %d", gCustomSmith.m_SmithSwordInfo[gSmithItem.ItemIndex].Price30Days + gSmithItem.TotalPrice);
			break;
		}
	}
	else if (gSmithItem.ItemType == 1){
		switch (gSmithItem.Days){
		case 0:
			gInterface.DrawFormat(eRed, priceTextX, priceTextY, 15, 5, "Price %d", gCustomSmith.m_SmithAxeInfo[gSmithItem.ItemIndex].Price1Days + gSmithItem.TotalPrice);
			break;
		case 1:
			gInterface.DrawFormat(eRed, priceTextX, priceTextY, 15, 5, "Price %d", gCustomSmith.m_SmithAxeInfo[gSmithItem.ItemIndex].Price7Days + gSmithItem.TotalPrice);
			break;
		case 2:
			gInterface.DrawFormat(eRed, priceTextX, priceTextY, 15, 5, "Price %d", gCustomSmith.m_SmithAxeInfo[gSmithItem.ItemIndex].Price30Days + gSmithItem.TotalPrice);
			break;
		}
	}
	if (gSmithItem.ItemType == 2){
		switch (gSmithItem.Days){
		case 0:
			gInterface.DrawFormat(eRed, priceTextX, priceTextY, 15, 5, "Price %d", gCustomSmith.m_SmithMaceInfo[gSmithItem.ItemIndex].Price1Days + gSmithItem.TotalPrice);
			break;
		case 1:
			gInterface.DrawFormat(eRed, priceTextX, priceTextY, 15, 5, "Price %d", gCustomSmith.m_SmithMaceInfo[gSmithItem.ItemIndex].Price7Days + gSmithItem.TotalPrice);
			break;
		case 2:
			gInterface.DrawFormat(eRed, priceTextX, priceTextY, 15, 5, "Price %d", gCustomSmith.m_SmithMaceInfo[gSmithItem.ItemIndex].Price30Days + gSmithItem.TotalPrice);
			break;
		}
	}
	if (gSmithItem.ItemType == 3){
		switch (gSmithItem.Days){
		case 0:
			gInterface.DrawFormat(eRed, priceTextX, priceTextY, 15, 5, "Price %d", gCustomSmith.m_SmithSpearInfo[gSmithItem.ItemIndex].Price1Days + gSmithItem.TotalPrice);
			break;
		case 1:
			gInterface.DrawFormat(eRed, priceTextX, priceTextY, 15, 5, "Price %d", gCustomSmith.m_SmithSpearInfo[gSmithItem.ItemIndex].Price7Days + gSmithItem.TotalPrice);
			break;
		case 2:
			gInterface.DrawFormat(eRed, priceTextX, priceTextY, 15, 5, "Price %d", gCustomSmith.m_SmithSpearInfo[gSmithItem.ItemIndex].Price30Days + gSmithItem.TotalPrice);
			break;
		}
	}
	if (gSmithItem.ItemType == 4){
		switch (gSmithItem.Days){
		case 0:
			gInterface.DrawFormat(eRed, priceTextX, priceTextY, 15, 5, "Price %d", gCustomSmith.m_SmithBowInfo[gSmithItem.ItemIndex].Price1Days + gSmithItem.TotalPrice);
			break;
		case 1:
			gInterface.DrawFormat(eRed, priceTextX, priceTextY, 15, 5, "Price %d", gCustomSmith.m_SmithBowInfo[gSmithItem.ItemIndex].Price7Days + gSmithItem.TotalPrice);
			break;
		case 2:
			gInterface.DrawFormat(eRed, priceTextX, priceTextY, 15, 5, "Price %d", gCustomSmith.m_SmithBowInfo[gSmithItem.ItemIndex].Price30Days + gSmithItem.TotalPrice);
			break;
		}
	}
	if (gSmithItem.ItemType == 5){
		switch (gSmithItem.Days){
		case 0:
			gInterface.DrawFormat(eRed, priceTextX, priceTextY, 15, 5, "Price %d", gCustomSmith.m_SmithStaffInfo[gSmithItem.ItemIndex].Price1Days + gSmithItem.TotalPrice);
			break;
		case 1:
			gInterface.DrawFormat(eRed, priceTextX, priceTextY, 15, 5, "Price %d", gCustomSmith.m_SmithStaffInfo[gSmithItem.ItemIndex].Price7Days + gSmithItem.TotalPrice);
			break;
		case 2:
			gInterface.DrawFormat(eRed, priceTextX, priceTextY, 15, 5, "Price %d", gCustomSmith.m_SmithStaffInfo[gSmithItem.ItemIndex].Price30Days + gSmithItem.TotalPrice);
			break;
		}
	}
	if (gSmithItem.ItemType == 6){
		switch (gSmithItem.Days){
		case 0:
			gInterface.DrawFormat(eRed, priceTextX, priceTextY, 15, 5, "Price %d", gCustomSmith.m_SmithShieldInfo[gSmithItem.ItemIndex].Price1Days + gSmithItem.TotalPrice);
			break;
		case 1:
			gInterface.DrawFormat(eRed, priceTextX, priceTextY, 15, 5, "Price %d", gCustomSmith.m_SmithShieldInfo[gSmithItem.ItemIndex].Price7Days + gSmithItem.TotalPrice);
			break;
		case 2:
			gInterface.DrawFormat(eRed, priceTextX, priceTextY, 15, 5, "Price %d", gCustomSmith.m_SmithShieldInfo[gSmithItem.ItemIndex].Price30Days + gSmithItem.TotalPrice);
			break;
		}
	}
	if (gSmithItem.ItemType == 7){
		switch (gSmithItem.Days){
		case 0:
			gInterface.DrawFormat(eRed, priceTextX, priceTextY, 15, 5, "Price %d", gCustomSmith.m_SmithHelmInfo[gSmithItem.ItemIndex].Price1Days + gSmithItem.TotalPrice);
			break;
		case 1:
			gInterface.DrawFormat(eRed, priceTextX, priceTextY, 15, 5, "Price %d", gCustomSmith.m_SmithHelmInfo[gSmithItem.ItemIndex].Price7Days + gSmithItem.TotalPrice);
			break;
		case 2:
			gInterface.DrawFormat(eRed, priceTextX, priceTextY, 15, 5, "Price %d", gCustomSmith.m_SmithHelmInfo[gSmithItem.ItemIndex].Price30Days + gSmithItem.TotalPrice);
			break;
		}
	}
	if (gSmithItem.ItemType == 8){
		switch (gSmithItem.Days){
		case 0:
			gInterface.DrawFormat(eRed, priceTextX, priceTextY, 15, 5, "Price %d", gCustomSmith.m_SmithArmorInfo[gSmithItem.ItemIndex].Price1Days + gSmithItem.TotalPrice);
			break;
		case 1:
			gInterface.DrawFormat(eRed, priceTextX, priceTextY, 15, 5, "Price %d", gCustomSmith.m_SmithArmorInfo[gSmithItem.ItemIndex].Price7Days + gSmithItem.TotalPrice);
			break;
		case 2:
			gInterface.DrawFormat(eRed, priceTextX, priceTextY, 15, 5, "Price %d", gCustomSmith.m_SmithArmorInfo[gSmithItem.ItemIndex].Price30Days + gSmithItem.TotalPrice);
			break;
		}
	}
	if (gSmithItem.ItemType == 9){
		switch (gSmithItem.Days){
		case 0:
			gInterface.DrawFormat(eRed, priceTextX, priceTextY, 15, 5, "Price %d", gCustomSmith.m_SmithPantInfo[gSmithItem.ItemIndex].Price1Days + gSmithItem.TotalPrice);
			break;
		case 1:
			gInterface.DrawFormat(eRed, priceTextX, priceTextY, 15, 5, "Price %d", gCustomSmith.m_SmithPantInfo[gSmithItem.ItemIndex].Price7Days + gSmithItem.TotalPrice);
			break;
		case 2:
			gInterface.DrawFormat(eRed, priceTextX, priceTextY, 15, 5, "Price %d", gCustomSmith.m_SmithPantInfo[gSmithItem.ItemIndex].Price30Days + gSmithItem.TotalPrice);
			break;
		}
	}
	if (gSmithItem.ItemType == 10){
		switch (gSmithItem.Days){
		case 0:
			gInterface.DrawFormat(eRed, priceTextX, priceTextY, 15, 5, "Price %d", gCustomSmith.m_SmithGloveInfo[gSmithItem.ItemIndex].Price1Days + gSmithItem.TotalPrice);
			break;
		case 1:
			gInterface.DrawFormat(eRed, priceTextX, priceTextY, 15, 5, "Price %d", gCustomSmith.m_SmithGloveInfo[gSmithItem.ItemIndex].Price7Days + gSmithItem.TotalPrice);
			break;
		case 2:
			gInterface.DrawFormat(eRed, priceTextX, priceTextY, 15, 5, "Price %d", gCustomSmith.m_SmithGloveInfo[gSmithItem.ItemIndex].Price30Days + gSmithItem.TotalPrice);
			break;
		}
	}
	if (gSmithItem.ItemType == 11){
		switch (gSmithItem.Days){
		case 0:
			gInterface.DrawFormat(eRed, priceTextX, priceTextY, 15, 5, "Price %d", gCustomSmith.m_SmithBootInfo[gSmithItem.ItemIndex].Price1Days + gSmithItem.TotalPrice);
			break;
		case 1:
			gInterface.DrawFormat(eRed, priceTextX, priceTextY, 15, 5, "Price %d", gCustomSmith.m_SmithBootInfo[gSmithItem.ItemIndex].Price7Days + gSmithItem.TotalPrice);
			break;
		case 2:
			gInterface.DrawFormat(eRed, priceTextX, priceTextY, 15, 5, "Price %d", gCustomSmith.m_SmithBootInfo[gSmithItem.ItemIndex].Price30Days + gSmithItem.TotalPrice);
			break;
		}
	}
}
#if(MAIN_VERSION_S8)
bool cSmithItem::drawNewInterfaceSmith(){
	if (gInterface.CheckWindow(ObjWindow::FullMap)){
		CustomWindow.CustomSmithItem->onShow = false;
	}
	if (!CustomWindow.CustomSmithItem->onShow)
		return false;
	bool res;
	if (gProtect.m_MainInfo.CustomTypeSmithItem == 0){
		res = nInterface.DrawWindowBG(CustomWindow.CustomSmithItem, "Smith Item");
	}
	else{
		res = nInterface.DrawWindowBG(CustomWindow.CustomSmithItem, "Shop Item");
	}
	gInterface.DrawFormat(eGold, CustomWindow.CustomSmithItem->X + 35, CustomWindow.CustomSmithItem->Y + 60, 210, 1, "Group Item");
	if (nInterface.Drawbutton(CustomWindow.prevButton[0], CustomWindow.CustomSmithItem->X + 21, CustomWindow.CustomSmithItem->Y + 60, "")){
		if (gSmithItem.ItemType <= 0){
			return false;
		}
		else{
			gSmithItem.ItemType -= 1;
			gSmithItem.ItemIndex = 0;
		}
	}
	if (nInterface.Drawbutton(CustomWindow.nextButton[0], CustomWindow.CustomSmithItem->X + 78, CustomWindow.CustomSmithItem->Y + 60, "")){
		if (gSmithItem.ItemType >= 11){
			return false;
		}
		else{
			gSmithItem.ItemType += 1;
			gSmithItem.ItemIndex = 0;
		}
	}
	switch (gSmithItem.ItemType){
	case 0:
		gInterface.DrawFormat(eGold, CustomWindow.CustomSmithItem->X + 40, CustomWindow.CustomSmithItem->Y + 73, 25, 5, "Sword");
		break;
	case 1:
		gInterface.DrawFormat(eGold, CustomWindow.CustomSmithItem->X + 40, CustomWindow.CustomSmithItem->Y + 73, 25, 5, "Axe");
		break;
	case 2:
		gInterface.DrawFormat(eGold, CustomWindow.CustomSmithItem->X + 40, CustomWindow.CustomSmithItem->Y + 73, 25, 5, "Scepter");
		break;
	case 3:
		gInterface.DrawFormat(eGold, CustomWindow.CustomSmithItem->X + 40, CustomWindow.CustomSmithItem->Y + 73, 25, 5, "Spear");
		break;
	case 4:
		gInterface.DrawFormat(eGold, CustomWindow.CustomSmithItem->X + 40, CustomWindow.CustomSmithItem->Y + 73, 25, 5, "Bow");
		break;
	case 5:
		gInterface.DrawFormat(eGold, CustomWindow.CustomSmithItem->X + 40, CustomWindow.CustomSmithItem->Y + 73, 25, 5, "Staff");
		break;
	case 6:
		gInterface.DrawFormat(eGold, CustomWindow.CustomSmithItem->X + 40, CustomWindow.CustomSmithItem->Y + 73, 25, 5, "Shield");
		break;
	case 7:
		gInterface.DrawFormat(eGold, CustomWindow.CustomSmithItem->X + 40, CustomWindow.CustomSmithItem->Y + 73, 25, 5, "Helm");
		break;
	case 8:
		gInterface.DrawFormat(eGold, CustomWindow.CustomSmithItem->X + 40, CustomWindow.CustomSmithItem->Y + 73, 25, 5, "Armor");
		break;
	case 9:
		gInterface.DrawFormat(eGold, CustomWindow.CustomSmithItem->X + 40, CustomWindow.CustomSmithItem->Y + 73, 25, 5, "Pant");
		break;
	case 10:
		gInterface.DrawFormat(eGold, CustomWindow.CustomSmithItem->X + 40, CustomWindow.CustomSmithItem->Y + 73, 25, 5, "Glove");
		break;
	case 11:
		gInterface.DrawFormat(eGold, CustomWindow.CustomSmithItem->X + 40, CustomWindow.CustomSmithItem->Y + 73, 25, 5, "Boot");
		break;
	}
	if (gProtect.m_MainInfo.CustomTypeSmithItem == 0){
		gInterface.DrawFormat(eGold, CustomWindow.CustomSmithItem->X + 120, CustomWindow.CustomSmithItem->Y + 60, 210, 1, "Item Time");
		if (nInterface.Drawbutton(CustomWindow.prevButton[1], CustomWindow.CustomSmithItem->X + 106, CustomWindow.CustomSmithItem->Y + 60, "")){
			if (gSmithItem.Days <= 0){
				return false;
			}
			else{
				gSmithItem.Days -= 1;
			}
		}
		if (nInterface.Drawbutton(CustomWindow.nextButton[1], CustomWindow.CustomSmithItem->X + 157, CustomWindow.CustomSmithItem->Y + 60, "")){
			if (gSmithItem.Days >= 2){
				return false;
			}
			else{
				gSmithItem.Days += 1;
			}
		}
		switch (gSmithItem.Days){
		case 0:
			gInterface.DrawFormat(eGold, CustomWindow.CustomSmithItem->X + 123, CustomWindow.CustomSmithItem->Y + 73, 25, 5, "1 Days");
			break;
		case 1:
			gInterface.DrawFormat(eGold, CustomWindow.CustomSmithItem->X + 123, CustomWindow.CustomSmithItem->Y + 73, 25, 5, "7 Days");
			break;
		case 2:
			gInterface.DrawFormat(eGold, CustomWindow.CustomSmithItem->X + 123, CustomWindow.CustomSmithItem->Y + 73, 25, 5, "30 Days");
			break;
		}
	}
	float drawItemX, drawItemY, drawItemX1, drawItemX2, drawItemY1, drawItemY2, drawItemY3, textItemsX, textItemsY;
	textItemsX = CustomWindow.CustomSmithItem->X + 35;
	textItemsY = CustomWindow.CustomSmithItem->Y + 119;
	if (gProtect.m_MainInfo.CustomTypeSmithItem == 1){
		drawItemX = CustomWindow.CustomSmithItem->X + 85;
		drawItemX1 = CustomWindow.CustomSmithItem->X + 90;
		drawItemX2 = CustomWindow.CustomSmithItem->X + 95;
	}
	else{
		drawItemX = CustomWindow.CustomSmithItem->X + 55;
		drawItemX1 = CustomWindow.CustomSmithItem->X + 70;
		drawItemX2 = CustomWindow.CustomSmithItem->X + 80;
	}
	drawItemY = CustomWindow.CustomSmithItem->Y + 60;
	drawItemY1 = CustomWindow.CustomSmithItem->Y + 55;
	drawItemY2 = CustomWindow.CustomSmithItem->Y + 45;
	drawItemY3 = CustomWindow.CustomSmithItem->Y + 50;
	gInterface.DrawFormat(eGold, CustomWindow.CustomSmithItem->X + 35, CustomWindow.CustomSmithItem->Y + 106, 210, 1, "Item Name");
	if (nInterface.Drawbutton(CustomWindow.prevButton[2], CustomWindow.CustomSmithItem->X + 20, CustomWindow.CustomSmithItem->Y + 105, "")){
		if (gSmithItem.ItemIndex <= 0){
			return false;
		}
		if (gSmithItem.ItemType == 0){
			if (gSmithItem.ItemIndex == 31){
				gSmithItem.ItemIndex -= 6;
			}
			else{
				gSmithItem.ItemIndex -= 1;
			}
		}
		else if (gSmithItem.ItemType == 2){
			if (gSmithItem.ItemIndex == 18){
				gSmithItem.ItemIndex -= 2;
			}
			else{
				gSmithItem.ItemIndex -= 1;
			}
		}
		else if (gSmithItem.ItemType == 4){
			if (gSmithItem.ItemIndex == 8 || gSmithItem.ItemIndex == 16 || gSmithItem.ItemIndex == 24){
				gSmithItem.ItemIndex -= 2;
			}
			else{
				gSmithItem.ItemIndex -= 1;
			}
		}
		else if (gSmithItem.ItemType == 7){
			if (gSmithItem.ItemIndex == 16 || gSmithItem.ItemIndex == 11 || gSmithItem.ItemIndex == 24 || gSmithItem.ItemIndex == 33 || gSmithItem.ItemIndex == 38){
				gSmithItem.ItemIndex -= 2;
			}
			else{
				gSmithItem.ItemIndex -= 1;
			}
		}
		else{
			gSmithItem.ItemIndex -= 1;
		}
	}
	if (nInterface.Drawbutton(CustomWindow.nextButton[2], CustomWindow.CustomSmithItem->X + 74, CustomWindow.CustomSmithItem->Y + 105, "")){
		if (gSmithItem.ItemType == 0){
			if (gSmithItem.ItemIndex >= 35){
				return false;
			}
			if (gSmithItem.ItemIndex == 25){
				gSmithItem.ItemIndex += 6;
			}
			else{
				gSmithItem.ItemIndex += 1;
			}
		}
		else if (gSmithItem.ItemType == 1){
			if (gSmithItem.ItemIndex >= 8){
				return false;
			}
			else{
				gSmithItem.ItemIndex += 1;
			}
		}
		else if (gSmithItem.ItemType == 2){
			if (gSmithItem.ItemIndex >= 18){
				return false;
			}
			if (gSmithItem.ItemIndex == 16){
				gSmithItem.ItemIndex += 2;
			}
			else{
				gSmithItem.ItemIndex += 1;
			}
		}
		else if (gSmithItem.ItemType == 3){
			if (gSmithItem.ItemIndex >= 11){
				return false;
			}
			else{
				gSmithItem.ItemIndex += 1;
			}
		}
		else if (gSmithItem.ItemType == 4){
			if (gSmithItem.ItemIndex >= 24){
				return false;
			}
			else if (gSmithItem.ItemIndex == 6 || gSmithItem.ItemIndex == 14 || gSmithItem.ItemIndex == 22){
				gSmithItem.ItemIndex += 2;
			}
			else{
				gSmithItem.ItemIndex += 1;
			}
		}
		else if (gSmithItem.ItemType == 5){
			if (gSmithItem.ItemIndex >= 23){
				return false;
			}
			else{
				gSmithItem.ItemIndex += 1;
			}
		}
		else if (gSmithItem.ItemType == 6){
			if (gSmithItem.ItemIndex >= 16){
				return false;
			}
			else{
				gSmithItem.ItemIndex += 1;
			}
		}
		else if (gSmithItem.ItemType == 7){
			if (gSmithItem.ItemIndex >= 43){
				return false;
			}
			else if (gSmithItem.ItemIndex == 14 || gSmithItem.ItemIndex == 19 || gSmithItem.ItemIndex == 22 || gSmithItem.ItemIndex == 31 || gSmithItem.ItemIndex == 36)	{
				gSmithItem.ItemIndex += 2;
			}
			else{
				gSmithItem.ItemIndex += 1;
			}
		}
		else{
			if (gSmithItem.ItemIndex >= 43){
				return false;
			}
			gSmithItem.ItemIndex += 1;
		}
	}
	switch (gSmithItem.ItemType){
	case 0:
		gInterface.DrawItemIMG(drawItemX, drawItemY, 100, 100, ITEM(gSmithItem.ItemType, gSmithItem.ItemIndex), gSmithItem.mLevel, gSmithItem.mExc, 0, 0);
		gInterface.DrawFormat(eGold, textItemsX, textItemsY, 25, 5, "%s", gCustomSmith.m_SmithSwordInfo[gSmithItem.ItemIndex].ItemName);
		break;
	case 1:
		gInterface.DrawItemIMG(drawItemX, drawItemY, 100, 100, ITEM(gSmithItem.ItemType, gSmithItem.ItemIndex), gSmithItem.mLevel, gSmithItem.mExc, 0, 0);
		gInterface.DrawFormat(eGold, textItemsX, textItemsY, 25, 5, "%s", gCustomSmith.m_SmithAxeInfo[gSmithItem.ItemIndex].ItemName);
		break;
	case 2:
		gInterface.DrawItemIMG(drawItemX, drawItemY, 100, 100, ITEM(gSmithItem.ItemType, gSmithItem.ItemIndex), gSmithItem.mLevel, gSmithItem.mExc, 0, 0);
		gInterface.DrawFormat(eGold, textItemsX, textItemsY, 25, 5, "%s", gCustomSmith.m_SmithMaceInfo[gSmithItem.ItemIndex].ItemName);
		break;
	case 3:
		gInterface.DrawItemIMG(drawItemX1, drawItemY, 100, 100, ITEM(gSmithItem.ItemType, gSmithItem.ItemIndex), gSmithItem.mLevel, gSmithItem.mExc, 0, 0);
		gInterface.DrawFormat(eGold, textItemsX, textItemsY, 25, 5, "%s", gCustomSmith.m_SmithSpearInfo[gSmithItem.ItemIndex].ItemName);
		break;
	case 4:
		gInterface.DrawItemIMG(drawItemX2, drawItemY, 100, 100, ITEM(gSmithItem.ItemType, gSmithItem.ItemIndex), gSmithItem.mLevel, gSmithItem.mExc, 0, 0);
		gInterface.DrawFormat(eGold, textItemsX, textItemsY, 25, 5, "%s", gCustomSmith.m_SmithBowInfo[gSmithItem.ItemIndex].ItemName);
		break;
	case 5:
		gInterface.DrawItemIMG(drawItemX1, drawItemY, 100, 100, ITEM(gSmithItem.ItemType, gSmithItem.ItemIndex), gSmithItem.mLevel, gSmithItem.mExc, 0, 0);
		gInterface.DrawFormat(eGold, textItemsX, textItemsY, 25, 5, "%s", gCustomSmith.m_SmithStaffInfo[gSmithItem.ItemIndex].ItemName);
		break;
	case 6:
		gInterface.DrawItemIMG(drawItemX2, drawItemY, 100, 100, ITEM(gSmithItem.ItemType, gSmithItem.ItemIndex), gSmithItem.mLevel, gSmithItem.mExc, 0, 0);
		gInterface.DrawFormat(eGold, textItemsX, textItemsY, 25, 5, "%s", gCustomSmith.m_SmithShieldInfo[gSmithItem.ItemIndex].ItemName);
		break;
	case 7:
		gInterface.DrawItemIMG(drawItemX2, drawItemY3, 100, 100, ITEM(gSmithItem.ItemType, gSmithItem.ItemIndex), gSmithItem.mLevel, gSmithItem.mExc, 0, 0);
		gInterface.DrawFormat(eGold, textItemsX, textItemsY, 25, 5, "%s", gCustomSmith.m_SmithHelmInfo[gSmithItem.ItemIndex].ItemName);
		break;
	case 8:
		gInterface.DrawItemIMG(drawItemX2, drawItemY1, 100, 100, ITEM(gSmithItem.ItemType, gSmithItem.ItemIndex), gSmithItem.mLevel, gSmithItem.mExc, 0, 0);
		gInterface.DrawFormat(eGold, textItemsX, textItemsY, 25, 5, "%s", gCustomSmith.m_SmithArmorInfo[gSmithItem.ItemIndex].ItemName);
		break;
	case 9:
		gInterface.DrawItemIMG(drawItemX2, drawItemY2, 100, 100, ITEM(gSmithItem.ItemType, gSmithItem.ItemIndex), gSmithItem.mLevel, gSmithItem.mExc, 0, 0);
		gInterface.DrawFormat(eGold, textItemsX, textItemsY, 25, 5, "%s", gCustomSmith.m_SmithPantInfo[gSmithItem.ItemIndex].ItemName);
		break;
	case 10:
		gInterface.DrawItemIMG(drawItemX2, drawItemY2, 100, 100, ITEM(gSmithItem.ItemType, gSmithItem.ItemIndex), gSmithItem.mLevel, gSmithItem.mExc, 0, 0);
		gInterface.DrawFormat(eGold, textItemsX, textItemsY, 25, 5, "%s", gCustomSmith.m_SmithGloveInfo[gSmithItem.ItemIndex].ItemName);
		break;
	case 11:
		gInterface.DrawItemIMG(drawItemX2, drawItemY2, 100, 100, ITEM(gSmithItem.ItemType, gSmithItem.ItemIndex), gSmithItem.mLevel, gSmithItem.mExc, 0, 0);
		gInterface.DrawFormat(eGold, textItemsX, textItemsY, 25, 5, "%s", gCustomSmith.m_SmithBootInfo[gSmithItem.ItemIndex].ItemName);
		break;
	}
	for (int i = 0; i < 10; i++){
		pDrawGUI(iOptionDot, CustomWindow.CustomSmithItem->X + 6, CustomWindow.CustomSmithItem->Y + 147 + (20 * i) + 9, 10, 10);
		pDrawGUI(0x7B5E, CustomWindow.CustomSmithItem->X + 16, CustomWindow.CustomSmithItem->Y + 160 + (20 * i) + 9, 82.0, 2.0);
		pDrawGUI(0x7B5E, CustomWindow.CustomSmithItem->X + 16 + 82, CustomWindow.CustomSmithItem->Y + 160 + (20 * i) + 9, 82.0, 2.0);
	}
	/*Level*/
	int ticket, button1, button2, text1, button1Time, button2Time, TextTitleTime, TextTime;
	ticket = CustomWindow.CustomSmithItem->X + 165;
	button1 = CustomWindow.CustomSmithItem->X + 139;
	button2 = CustomWindow.CustomSmithItem->X + 164;
	text1 = CustomWindow.CustomSmithItem->X + 143;
	button1Time = CustomWindow.CustomSmithItem->X + 140;
	button2Time = CustomWindow.CustomSmithItem->X + 193;
	TextTitleTime = CustomWindow.CustomSmithItem->X + 160;
	TextTime = CustomWindow.CustomSmithItem->X + 163;
	gInterface.DrawFormat(eGold, CustomWindow.CustomSmithItem->X + 20, CustomWindow.CustomSmithItem->Y + 155, 15, 5, "Item Level");
	if (nInterface.Drawbutton(CustomWindow.prevButton[3], button1, CustomWindow.CustomSmithItem->Y + 153, "")){
		if (gSmithItem.mLevel <= 0){
			return false;
		}
		else{
			gSmithItem.mLevel -= 1;
			gSmithItem.TotalPrice -= gSmithItem.pLevel;
		}
	}
	if (nInterface.Drawbutton(CustomWindow.nextButton[3], button2, CustomWindow.CustomSmithItem->Y + 153, "")){
		if (gSmithItem.mLevel >= gSmithItem.MaxLevel){
			return false;
		}
		else{
			gSmithItem.mLevel += 1;
			gSmithItem.TotalPrice += gSmithItem.pLevel;
		}
	}
	gInterface.DrawFormat(eGold, text1, CustomWindow.CustomSmithItem->Y + 155, 25, 5, "     %d", gSmithItem.mLevel);
	/*Skill*/
	gInterface.DrawFormat(eGold, CustomWindow.CustomSmithItem->X + 20, CustomWindow.CustomSmithItem->Y + 175, 15, 5, "Item Skill");
	if (nInterface.DrawCheckbox(CustomWindow.CustomCheckBox[0], ticket, CustomWindow.CustomSmithItem->Y + 175, "")){
		if (gSmithItem.mSkill == 0){
			gSmithItem.mSkill = 1;
			gSmithItem.TotalPrice += gSmithItem.pSkill;
		}
		else{
			gSmithItem.mSkill = 0;
			gSmithItem.TotalPrice -= gSmithItem.pSkill;
		}
	}
	/*Luck*/
	gInterface.DrawFormat(eGold, CustomWindow.CustomSmithItem->X + 20, CustomWindow.CustomSmithItem->Y + 195, 15, 5, "Lucky Option");
	if (nInterface.DrawCheckbox(CustomWindow.CustomCheckBox[1], ticket, CustomWindow.CustomSmithItem->Y + 195, "")){
		if (gSmithItem.mLuck == 0){
			gSmithItem.mLuck = 1;
			gSmithItem.TotalPrice += gSmithItem.pLuck;
		}
		else{
			gSmithItem.mLuck = 0;
			gSmithItem.TotalPrice -= gSmithItem.pLuck;
		}
	}
	/*Option[Life]*/
	gInterface.DrawFormat(eGold, CustomWindow.CustomSmithItem->X + 20, CustomWindow.CustomSmithItem->Y + 215, 15, 5, "Add Option");
	if (nInterface.Drawbutton(CustomWindow.prevButton[4], button1, CustomWindow.CustomSmithItem->Y + 213, "")){
		if (gSmithItem.mOpt <= 0){
			return false;
		}
		else{
			gSmithItem.mOpt -= 1;
			gSmithItem.TotalPrice -= gSmithItem.pOpt;
		}
	}
	if (nInterface.Drawbutton(CustomWindow.nextButton[4], button2, CustomWindow.CustomSmithItem->Y + 213, "")){
		if (gSmithItem.mOpt >= gSmithItem.MaxOpt){
			return false;
		}
		else{
			gSmithItem.mOpt += 1;
			gSmithItem.TotalPrice += gSmithItem.pOpt;
		}
	}
	gInterface.DrawFormat(eGold, text1, CustomWindow.CustomSmithItem->Y + 215, 25, 5, "     %d", gSmithItem.mOpt);
	/*----*/
	if (gSmithItem.ItemType <= 5){
		gInterface.DrawFormat(eGold, CustomWindow.CustomSmithItem->X + 20, CustomWindow.CustomSmithItem->Y + 235, 15, 5, "Excellent Damange Rate");
		if (nInterface.DrawCheckbox(CustomWindow.CustomCheckBox[2], ticket, CustomWindow.CustomSmithItem->Y + 235, "")){
			if (gSmithItem.ExcOption == 0){
				gSmithItem.ExcOption = 32;
				gSmithItem.mExc += 1;
				gSmithItem.TotalPrice += gSmithItem.pExc;
			}
			else{
				gSmithItem.ExcOption = 0;
				gSmithItem.mExc -= 1;
				gSmithItem.TotalPrice -= gSmithItem.pExc;
			}
		}
		/*------*/
		gInterface.DrawFormat(eGold, CustomWindow.CustomSmithItem->X + 20, CustomWindow.CustomSmithItem->Y + 255, 15, 5, "Increase Damage Level");
		if (nInterface.DrawCheckbox(CustomWindow.CustomCheckBox[3], ticket, CustomWindow.CustomSmithItem->Y + 255, "")){
			if (gSmithItem.ExcOption1 == 0){
				gSmithItem.ExcOption1 = 16;
				gSmithItem.mExc += 1;
				gSmithItem.TotalPrice += gSmithItem.pExc1;
			}
			else{
				gSmithItem.ExcOption1 = 0;
				gSmithItem.mExc -= 1;
				gSmithItem.TotalPrice -= gSmithItem.pExc1;
			}
		}
		/*------*/
		gInterface.DrawFormat(eGold, CustomWindow.CustomSmithItem->X + 20, CustomWindow.CustomSmithItem->Y + 275, 15, 5, "Increase Damage");
		if (nInterface.DrawCheckbox(CustomWindow.CustomCheckBox[4], ticket, CustomWindow.CustomSmithItem->Y + 275, "")){
			if (gSmithItem.ExcOption2 == 0){
				gSmithItem.ExcOption2 = 8;
				gSmithItem.mExc += 1;
				gSmithItem.TotalPrice += gSmithItem.pExc2;
			}
			else{
				gSmithItem.ExcOption2 = 0;
				gSmithItem.mExc -= 1;
				gSmithItem.TotalPrice -= gSmithItem.pExc2;
			}
		}
		/*------*/
		gInterface.DrawFormat(eGold, CustomWindow.CustomSmithItem->X + 20, CustomWindow.CustomSmithItem->Y + 295, 15, 5, "Increase Attacking(Wizard)Speed");
		if (nInterface.DrawCheckbox(CustomWindow.CustomCheckBox[5], ticket, CustomWindow.CustomSmithItem->Y + 295, "")){
			if (gSmithItem.ExcOption3 == 0){
				gSmithItem.ExcOption3 = 4;
				gSmithItem.mExc += 1;
				gSmithItem.TotalPrice += gSmithItem.pExc3;
			}
			else{
				gSmithItem.ExcOption3 = 0;
				gSmithItem.mExc -= 1;
				gSmithItem.TotalPrice -= gSmithItem.pExc3;
			}
		}
		/*------*/
		gInterface.DrawFormat(eGold, CustomWindow.CustomSmithItem->X + 20, CustomWindow.CustomSmithItem->Y + 315, 15, 5, "Increase Life Hunting Monster");
		if (nInterface.DrawCheckbox(CustomWindow.CustomCheckBox[6], ticket, CustomWindow.CustomSmithItem->Y + 315, "")){
			if (gSmithItem.ExcOption4 == 0){
				gSmithItem.ExcOption4 = 2;
				gSmithItem.mExc += 1;
				gSmithItem.TotalPrice += gSmithItem.pExc4;
			}
			else{
				gSmithItem.ExcOption4 = 0;
				gSmithItem.mExc -= 1;
				gSmithItem.TotalPrice -= gSmithItem.pExc4;
			}
		}
		/*------*/
		gInterface.DrawFormat(eGold, CustomWindow.CustomSmithItem->X + 20, CustomWindow.CustomSmithItem->Y + 335, 15, 5, "Increase Mana Hunting Monster");
		if (nInterface.DrawCheckbox(CustomWindow.CustomCheckBox[7], ticket, CustomWindow.CustomSmithItem->Y + 335, "")){
			if (gSmithItem.ExcOption5 == 0){
				gSmithItem.ExcOption5 = 1;
				gSmithItem.mExc += 1;
				gSmithItem.TotalPrice += gSmithItem.pExc5;
			}
			else{
				gSmithItem.ExcOption5 = 0;
				gSmithItem.mExc -= 1;
				gSmithItem.TotalPrice -= gSmithItem.pExc5;
			}
		}
	}
	if (gSmithItem.ItemType >= 6){
		gInterface.DrawFormat(eGold, CustomWindow.CustomSmithItem->X + 20, CustomWindow.CustomSmithItem->Y + 235, 15, 5, "Increase Max HP");
		if (nInterface.DrawCheckbox(CustomWindow.CustomCheckBox[8], ticket, CustomWindow.CustomSmithItem->Y + 235, "")){
			if (gSmithItem.ExcOption == 0){
				gSmithItem.ExcOption = 32;
				gSmithItem.mExc += 1;
				gSmithItem.TotalPrice += gSmithItem.pExc;
			}
			else{
				gSmithItem.ExcOption = 0;
				gSmithItem.mExc -= 1;
				gSmithItem.TotalPrice -= gSmithItem.pExc;
			}
		}
		gInterface.DrawFormat(eGold, CustomWindow.CustomSmithItem->X + 20, CustomWindow.CustomSmithItem->Y + 255, 15, 5, "Increase Max Mana");
		if (nInterface.DrawCheckbox(CustomWindow.CustomCheckBox[9], ticket, CustomWindow.CustomSmithItem->Y + 255, "")){
			if (gSmithItem.ExcOption1 == 0){
				gSmithItem.ExcOption1 = 16;
				gSmithItem.mExc += 1;
				gSmithItem.TotalPrice += gSmithItem.pExc1;
			}
			else{
				gSmithItem.ExcOption1 = 0;
				gSmithItem.mExc -= 1;
				gSmithItem.TotalPrice -= gSmithItem.pExc1;
			}
		}
		gInterface.DrawFormat(eGold, CustomWindow.CustomSmithItem->X + 20, CustomWindow.CustomSmithItem->Y + 275, 15, 5, "Damage Decrease");
		if (nInterface.DrawCheckbox(CustomWindow.CustomCheckBox[10], ticket, CustomWindow.CustomSmithItem->Y + 275, "")){
			if (gSmithItem.ExcOption2 == 0){
				gSmithItem.ExcOption2 = 8;
				gSmithItem.mExc += 1;
				gSmithItem.TotalPrice += gSmithItem.pExc2;
			}
			else{
				gSmithItem.ExcOption2 = 0;
				gSmithItem.mExc -= 1;
				gSmithItem.TotalPrice -= gSmithItem.pExc2;
			}
		}
		gInterface.DrawFormat(eGold, CustomWindow.CustomSmithItem->X + 20, CustomWindow.CustomSmithItem->Y + 295, 15, 5, "Reflect Damage");
		if (nInterface.DrawCheckbox(CustomWindow.CustomCheckBox[11], ticket, CustomWindow.CustomSmithItem->Y + 295, "")){
			if (gSmithItem.ExcOption3 == 0){
				gSmithItem.ExcOption3 = 4;
				gSmithItem.mExc += 1;
				gSmithItem.TotalPrice += gSmithItem.pExc3;
			}
			else{
				gSmithItem.ExcOption3 = 0;
				gSmithItem.mExc -= 1;
				gSmithItem.TotalPrice -= gSmithItem.pExc3;
			}
		}
		gInterface.DrawFormat(eGold, CustomWindow.CustomSmithItem->X + 20, CustomWindow.CustomSmithItem->Y + 315, 15, 5, "Defense Success Rate");
		if (nInterface.DrawCheckbox(CustomWindow.CustomCheckBox[12], ticket, CustomWindow.CustomSmithItem->Y + 315, "")){
			if (gSmithItem.ExcOption4 == 0){
				gSmithItem.ExcOption4 = 2;
				gSmithItem.mExc += 1;
				gSmithItem.TotalPrice += gSmithItem.pExc4;
			}
			else{
				gSmithItem.ExcOption4 = 0;
				gSmithItem.mExc -= 1;
				gSmithItem.TotalPrice -= gSmithItem.pExc4;
			}
		}
		gInterface.DrawFormat(eGold, CustomWindow.CustomSmithItem->X + 20, CustomWindow.CustomSmithItem->Y + 335, 15, 5, "Zen After Hunting Monsters");
		if (nInterface.DrawCheckbox(CustomWindow.CustomCheckBox[13], ticket, CustomWindow.CustomSmithItem->Y + 335, "")){
			if (gSmithItem.ExcOption5 == 0){
				gSmithItem.ExcOption5 = 1;
				gSmithItem.mExc += 1;
				gSmithItem.TotalPrice += gSmithItem.pExc5;
			}
			else{
				gSmithItem.ExcOption5 = 0;
				gSmithItem.mExc -= 1;
				gSmithItem.TotalPrice -= gSmithItem.pExc5;
			}
		}
	}
	float priceTextX, priceTextY;
	priceTextX = CustomWindow.CustomSmithItem->X + 75;
	priceTextY = CustomWindow.CustomSmithItem->Y + 360;
	if (gSmithItem.ItemType == 0){
		switch (gSmithItem.Days){
		case 0:
			gInterface.DrawFormat(eRed, priceTextX, priceTextY, 15, 5, "Price %d", gCustomSmith.m_SmithSwordInfo[gSmithItem.ItemIndex].Price1Days + gSmithItem.TotalPrice);
			break;
		case 1:
			gInterface.DrawFormat(eRed, priceTextX, priceTextY, 15, 5, "Price %d", gCustomSmith.m_SmithSwordInfo[gSmithItem.ItemIndex].Price7Days + gSmithItem.TotalPrice);
			break;
		case 2:
			gInterface.DrawFormat(eRed, priceTextX, priceTextY, 15, 5, "Price %d", gCustomSmith.m_SmithSwordInfo[gSmithItem.ItemIndex].Price30Days + gSmithItem.TotalPrice);
			break;
		}
	}
	else if (gSmithItem.ItemType == 1){
		switch (gSmithItem.Days){
		case 0:
			gInterface.DrawFormat(eRed, priceTextX, priceTextY, 15, 5, "Price %d", gCustomSmith.m_SmithAxeInfo[gSmithItem.ItemIndex].Price1Days + gSmithItem.TotalPrice);
			break;
		case 1:
			gInterface.DrawFormat(eRed, priceTextX, priceTextY, 15, 5, "Price %d", gCustomSmith.m_SmithAxeInfo[gSmithItem.ItemIndex].Price7Days + gSmithItem.TotalPrice);
			break;
		case 2:
			gInterface.DrawFormat(eRed, priceTextX, priceTextY, 15, 5, "Price %d", gCustomSmith.m_SmithAxeInfo[gSmithItem.ItemIndex].Price30Days + gSmithItem.TotalPrice);
			break;
		}
	}
	if (gSmithItem.ItemType == 2){
		switch (gSmithItem.Days){
		case 0:
			gInterface.DrawFormat(eRed, priceTextX, priceTextY, 15, 5, "Price %d", gCustomSmith.m_SmithMaceInfo[gSmithItem.ItemIndex].Price1Days + gSmithItem.TotalPrice);
			break;
		case 1:
			gInterface.DrawFormat(eRed, priceTextX, priceTextY, 15, 5, "Price %d", gCustomSmith.m_SmithMaceInfo[gSmithItem.ItemIndex].Price7Days + gSmithItem.TotalPrice);
			break;
		case 2:
			gInterface.DrawFormat(eRed, priceTextX, priceTextY, 15, 5, "Price %d", gCustomSmith.m_SmithMaceInfo[gSmithItem.ItemIndex].Price30Days + gSmithItem.TotalPrice);
			break;
		}
	}
	if (gSmithItem.ItemType == 3){
		switch (gSmithItem.Days){
		case 0:
			gInterface.DrawFormat(eRed, priceTextX, priceTextY, 15, 5, "Price %d", gCustomSmith.m_SmithSpearInfo[gSmithItem.ItemIndex].Price1Days + gSmithItem.TotalPrice);
			break;
		case 1:
			gInterface.DrawFormat(eRed, priceTextX, priceTextY, 15, 5, "Price %d", gCustomSmith.m_SmithSpearInfo[gSmithItem.ItemIndex].Price7Days + gSmithItem.TotalPrice);
			break;
		case 2:
			gInterface.DrawFormat(eRed, priceTextX, priceTextY, 15, 5, "Price %d", gCustomSmith.m_SmithSpearInfo[gSmithItem.ItemIndex].Price30Days + gSmithItem.TotalPrice);
			break;
		}
	}
	if (gSmithItem.ItemType == 4){
		switch (gSmithItem.Days){
		case 0:
			gInterface.DrawFormat(eRed, priceTextX, priceTextY, 15, 5, "Price %d", gCustomSmith.m_SmithBowInfo[gSmithItem.ItemIndex].Price1Days + gSmithItem.TotalPrice);
			break;
		case 1:
			gInterface.DrawFormat(eRed, priceTextX, priceTextY, 15, 5, "Price %d", gCustomSmith.m_SmithBowInfo[gSmithItem.ItemIndex].Price7Days + gSmithItem.TotalPrice);
			break;
		case 2:
			gInterface.DrawFormat(eRed, priceTextX, priceTextY, 15, 5, "Price %d", gCustomSmith.m_SmithBowInfo[gSmithItem.ItemIndex].Price30Days + gSmithItem.TotalPrice);
			break;
		}
	}
	if (gSmithItem.ItemType == 5){
		switch (gSmithItem.Days){
		case 0:
			gInterface.DrawFormat(eRed, priceTextX, priceTextY, 15, 5, "Price %d", gCustomSmith.m_SmithStaffInfo[gSmithItem.ItemIndex].Price1Days + gSmithItem.TotalPrice);
			break;
		case 1:
			gInterface.DrawFormat(eRed, priceTextX, priceTextY, 15, 5, "Price %d", gCustomSmith.m_SmithStaffInfo[gSmithItem.ItemIndex].Price7Days + gSmithItem.TotalPrice);
			break;
		case 2:
			gInterface.DrawFormat(eRed, priceTextX, priceTextY, 15, 5, "Price %d", gCustomSmith.m_SmithStaffInfo[gSmithItem.ItemIndex].Price30Days + gSmithItem.TotalPrice);
			break;
		}
	}
	if (gSmithItem.ItemType == 6){
		switch (gSmithItem.Days){
		case 0:
			gInterface.DrawFormat(eRed, priceTextX, priceTextY, 15, 5, "Price %d", gCustomSmith.m_SmithShieldInfo[gSmithItem.ItemIndex].Price1Days + gSmithItem.TotalPrice);
			break;
		case 1:
			gInterface.DrawFormat(eRed, priceTextX, priceTextY, 15, 5, "Price %d", gCustomSmith.m_SmithShieldInfo[gSmithItem.ItemIndex].Price7Days + gSmithItem.TotalPrice);
			break;
		case 2:
			gInterface.DrawFormat(eRed, priceTextX, priceTextY, 15, 5, "Price %d", gCustomSmith.m_SmithShieldInfo[gSmithItem.ItemIndex].Price30Days + gSmithItem.TotalPrice);
			break;
		}
	}
	if (gSmithItem.ItemType == 7){
		switch (gSmithItem.Days){
		case 0:
			gInterface.DrawFormat(eRed, priceTextX, priceTextY, 15, 5, "Price %d", gCustomSmith.m_SmithHelmInfo[gSmithItem.ItemIndex].Price1Days + gSmithItem.TotalPrice);
			break;
		case 1:
			gInterface.DrawFormat(eRed, priceTextX, priceTextY, 15, 5, "Price %d", gCustomSmith.m_SmithHelmInfo[gSmithItem.ItemIndex].Price7Days + gSmithItem.TotalPrice);
			break;
		case 2:
			gInterface.DrawFormat(eRed, priceTextX, priceTextY, 15, 5, "Price %d", gCustomSmith.m_SmithHelmInfo[gSmithItem.ItemIndex].Price30Days + gSmithItem.TotalPrice);
			break;
		}
	}
	if (gSmithItem.ItemType == 8){
		switch (gSmithItem.Days){
		case 0:
			gInterface.DrawFormat(eRed, priceTextX, priceTextY, 15, 5, "Price %d", gCustomSmith.m_SmithArmorInfo[gSmithItem.ItemIndex].Price1Days + gSmithItem.TotalPrice);
			break;
		case 1:
			gInterface.DrawFormat(eRed, priceTextX, priceTextY, 15, 5, "Price %d", gCustomSmith.m_SmithArmorInfo[gSmithItem.ItemIndex].Price7Days + gSmithItem.TotalPrice);
			break;
		case 2:
			gInterface.DrawFormat(eRed, priceTextX, priceTextY, 15, 5, "Price %d", gCustomSmith.m_SmithArmorInfo[gSmithItem.ItemIndex].Price30Days + gSmithItem.TotalPrice);
			break;
		}
	}
	if (gSmithItem.ItemType == 9){
		switch (gSmithItem.Days){
		case 0:
			gInterface.DrawFormat(eRed, priceTextX, priceTextY, 15, 5, "Price %d", gCustomSmith.m_SmithPantInfo[gSmithItem.ItemIndex].Price1Days + gSmithItem.TotalPrice);
			break;
		case 1:
			gInterface.DrawFormat(eRed, priceTextX, priceTextY, 15, 5, "Price %d", gCustomSmith.m_SmithPantInfo[gSmithItem.ItemIndex].Price7Days + gSmithItem.TotalPrice);
			break;
		case 2:
			gInterface.DrawFormat(eRed, priceTextX, priceTextY, 15, 5, "Price %d", gCustomSmith.m_SmithPantInfo[gSmithItem.ItemIndex].Price30Days + gSmithItem.TotalPrice);
			break;
		}
	}
	if (gSmithItem.ItemType == 10){
		switch (gSmithItem.Days){
		case 0:
			gInterface.DrawFormat(eRed, priceTextX, priceTextY, 15, 5, "Price %d", gCustomSmith.m_SmithGloveInfo[gSmithItem.ItemIndex].Price1Days + gSmithItem.TotalPrice);
			break;
		case 1:
			gInterface.DrawFormat(eRed, priceTextX, priceTextY, 15, 5, "Price %d", gCustomSmith.m_SmithGloveInfo[gSmithItem.ItemIndex].Price7Days + gSmithItem.TotalPrice);
			break;
		case 2:
			gInterface.DrawFormat(eRed, priceTextX, priceTextY, 15, 5, "Price %d", gCustomSmith.m_SmithGloveInfo[gSmithItem.ItemIndex].Price30Days + gSmithItem.TotalPrice);
			break;
		}
	}
	if (gSmithItem.ItemType == 11){
		switch (gSmithItem.Days){
		case 0:
			gInterface.DrawFormat(eRed, priceTextX, priceTextY, 15, 5, "Price %d", gCustomSmith.m_SmithBootInfo[gSmithItem.ItemIndex].Price1Days + gSmithItem.TotalPrice);
			break;
		case 1:
			gInterface.DrawFormat(eRed, priceTextX, priceTextY, 15, 5, "Price %d", gCustomSmith.m_SmithBootInfo[gSmithItem.ItemIndex].Price7Days + gSmithItem.TotalPrice);
			break;
		case 2:
			gInterface.DrawFormat(eRed, priceTextX, priceTextY, 15, 5, "Price %d", gCustomSmith.m_SmithBootInfo[gSmithItem.ItemIndex].Price30Days + gSmithItem.TotalPrice);
			break;
		}
	}
	char* buttonName[] = { "Buy", "Close" };
	for (char i = 0; i < 2; i++){
		if (nInterface.Drawbutton(CustomWindow.CustomSmithBTN[i], CustomWindow.CustomSmithItem->X + 10 + (i % 2) * (124 / 1.5 + 10), CustomWindow.CustomSmithItem->Y + 370 + i / 2 * (35 / 1.5 + 10), buttonName[i])){
			if (i == 0){
				if (gSmithItem.ItemType >= 7){
					gSmithItem.mSkill = 0;
				}
				SDHP_BUYSVSHOP pMsg;
				pMsg.h.set(0xFB, 0x08, sizeof(pMsg));
				pMsg.ItemType = gSmithItem.ItemType;
				pMsg.ItemIndex = gSmithItem.ItemIndex;
				pMsg.Days = gSmithItem.Days;
				pMsg.mLevel = gSmithItem.mLevel;
				pMsg.mSkill = gSmithItem.mSkill;
				pMsg.mLuck = gSmithItem.mLuck;
				pMsg.mOpt = gSmithItem.mOpt;
				pMsg.ExcOption = gSmithItem.ExcOption;
				pMsg.ExcOption1 = gSmithItem.ExcOption1;
				pMsg.ExcOption2 = gSmithItem.ExcOption2;
				pMsg.ExcOption3 = gSmithItem.ExcOption3;
				pMsg.ExcOption4 = gSmithItem.ExcOption4;
				pMsg.ExcOption5 = gSmithItem.ExcOption5;
				pMsg.mExc = gSmithItem.mExc;
				DataSend((BYTE*)&pMsg, pMsg.h.size);
				CustomWindow.CustomSmithItem->onShow = false;
			}
			else if (i == 1){
				CustomWindow.CustomSmithItem->onShow = false;
			}
		}
	}
	return res;
}
#endif

void cSmithItem::EventSmithItem_Main(DWORD Event){
	DWORD CurrentTick = GetTickCount();
	if (!gInterface.Data[eSMITH_MAIN].OnShow){
		return;
	}
	if (gInterface.IsWorkZone(eSMITH_SKILL)){
		DWORD Delay = (CurrentTick - gInterface.Data[eSMITH_SKILL].EventTick);
		if (Event == WM_LBUTTONDOWN){
			gInterface.Data[eSMITH_SKILL].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		gInterface.Data[eSMITH_SKILL].OnClick = false;
		pSetCursorFocus = true;
		if (Delay < 500){
			return;
		}
		gInterface.Data[eSMITH_SKILL].EventTick = GetTickCount();
		if (!gInterface.Data[eSMITH_SKILL_1].OnShow){
			gInterface.Data[eSMITH_SKILL_1].OnShow = true;
			gSmithItem.mSkill = 1;
			gSmithItem.TotalPrice += gSmithItem.pSkill;
		}
		else{
			gInterface.Data[eSMITH_SKILL_1].OnShow = false;
			gSmithItem.mSkill = 0;
			gSmithItem.TotalPrice -= gSmithItem.pSkill;
		}
	}
	else if (gInterface.IsWorkZone(eSMITH_LUCK)){
		DWORD Delay = (CurrentTick - gInterface.Data[eSMITH_LUCK].EventTick);
		if (Event == WM_LBUTTONDOWN){
			gInterface.Data[eSMITH_LUCK].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		gInterface.Data[eSMITH_LUCK].OnClick = false;
		pSetCursorFocus = true;
		if (Delay < 500){
			return;
		}
		gInterface.Data[eSMITH_LUCK].EventTick = GetTickCount();
		if (!gInterface.Data[eSMITH_LUCK_1].OnShow){
			gInterface.Data[eSMITH_LUCK_1].OnShow = true;
			gSmithItem.mLuck = 1;
			gSmithItem.TotalPrice += gSmithItem.pLuck;
		}
		else{
			gInterface.Data[eSMITH_LUCK_1].OnShow = false;
			gSmithItem.mLuck = 0;
			gSmithItem.TotalPrice -= gSmithItem.pLuck;
		}
	}
	else if (gInterface.IsWorkZone(eSMITH_EXC)){
		DWORD Delay = (CurrentTick - gInterface.Data[eSMITH_EXC].EventTick);
		if (Event == WM_LBUTTONDOWN){
			gInterface.Data[eSMITH_EXC].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		gInterface.Data[eSMITH_EXC].OnClick = false;
		pSetCursorFocus = true;
		if (Delay < 500){
			return;
		}
		gInterface.Data[eSMITH_EXC].EventTick = GetTickCount();
		if (!gInterface.Data[eSMITH_EXC_1].OnShow){
			gInterface.Data[eSMITH_EXC_1].OnShow = true;
			gSmithItem.ExcOption = 32;
			gSmithItem.mExc += 1;
			gSmithItem.TotalPrice += gSmithItem.pExc;
		}
		else{
			gInterface.Data[eSMITH_EXC_1].OnShow = false;
			gSmithItem.ExcOption = 0;
			gSmithItem.mExc -= 1;
			gSmithItem.TotalPrice -= gSmithItem.pExc;
		}
	}
	else if (gInterface.IsWorkZone(eSMITH_EXC1)){
		DWORD Delay = (CurrentTick - gInterface.Data[eSMITH_EXC1].EventTick);
		if (Event == WM_LBUTTONDOWN){
			gInterface.Data[eSMITH_EXC1].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		gInterface.Data[eSMITH_EXC1].OnClick = false;
		pSetCursorFocus = true;
		if (Delay < 500){
			return;
		}
		gInterface.Data[eSMITH_EXC1].EventTick = GetTickCount();
		if (!gInterface.Data[eSMITH_EXC1_1].OnShow){
			gInterface.Data[eSMITH_EXC1_1].OnShow = true;
			gSmithItem.ExcOption1 = 16;
			gSmithItem.mExc += 1;
			gSmithItem.TotalPrice += gSmithItem.pExc1;
		}
		else{
			gInterface.Data[eSMITH_EXC1_1].OnShow = false;
			gSmithItem.ExcOption1 = 0;
			gSmithItem.mExc -= 1;
			gSmithItem.TotalPrice -= gSmithItem.pExc1;
		}
	}
	else if (gInterface.IsWorkZone(eSMITH_EXC2)){
		DWORD Delay = (CurrentTick - gInterface.Data[eSMITH_EXC2].EventTick);
		if (Event == WM_LBUTTONDOWN){
			gInterface.Data[eSMITH_EXC2].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		gInterface.Data[eSMITH_EXC2].OnClick = false;
		pSetCursorFocus = true;
		if (Delay < 500){
			return;
		}
		gInterface.Data[eSMITH_EXC2].EventTick = GetTickCount();
		if (!gInterface.Data[eSMITH_EXC2_1].OnShow){
			gInterface.Data[eSMITH_EXC2_1].OnShow = true;
			gSmithItem.ExcOption2 = 8;
			gSmithItem.mExc += 1;
			gSmithItem.TotalPrice += gSmithItem.pExc2;
		}
		else{
			gInterface.Data[eSMITH_EXC2_1].OnShow = false;
			gSmithItem.ExcOption2 = 0;
			gSmithItem.mExc -= 1;
			gSmithItem.TotalPrice -= gSmithItem.pExc2;
		}
	}
	else if (gInterface.IsWorkZone(eSMITH_EXC3)){
		DWORD Delay = (CurrentTick - gInterface.Data[eSMITH_EXC3].EventTick);
		if (Event == WM_LBUTTONDOWN){
			gInterface.Data[eSMITH_EXC3].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		gInterface.Data[eSMITH_EXC3].OnClick = false;
		pSetCursorFocus = true;
		if (Delay < 500){
			return;
		}
		gInterface.Data[eSMITH_EXC3].EventTick = GetTickCount();
		if (!gInterface.Data[eSMITH_EXC3_1].OnShow){
			gInterface.Data[eSMITH_EXC3_1].OnShow = true;
			gSmithItem.ExcOption3 = 4;
			gSmithItem.mExc += 1;
			gSmithItem.TotalPrice += gSmithItem.pExc3;
		}
		else{
			gInterface.Data[eSMITH_EXC3_1].OnShow = false;
			gSmithItem.ExcOption3 = 0;
			gSmithItem.mExc -= 1;
			gSmithItem.TotalPrice -= gSmithItem.pExc3;
		}
	}
	else if (gInterface.IsWorkZone(eSMITH_EXC4)){
		DWORD Delay = (CurrentTick - gInterface.Data[eSMITH_EXC4].EventTick);
		if (Event == WM_LBUTTONDOWN){
			gInterface.Data[eSMITH_EXC4].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		gInterface.Data[eSMITH_EXC4].OnClick = false;
		pSetCursorFocus = true;
		if (Delay < 500){
			return;
		}
		gInterface.Data[eSMITH_EXC4].EventTick = GetTickCount();
		if (!gInterface.Data[eSMITH_EXC4_1].OnShow){
			gInterface.Data[eSMITH_EXC4_1].OnShow = true;
			gSmithItem.ExcOption4 = 2;
			gSmithItem.mExc += 1;
			gSmithItem.TotalPrice += gSmithItem.pExc4;
		}
		else{
			gInterface.Data[eSMITH_EXC4_1].OnShow = false;
			gSmithItem.ExcOption4 = 0;
			gSmithItem.mExc -= 1;
			gSmithItem.TotalPrice -= gSmithItem.pExc4;
		}
	}
	else if (gInterface.IsWorkZone(eSMITH_EXC5)){
		DWORD Delay = (CurrentTick - gInterface.Data[eSMITH_EXC5].EventTick);
		if (Event == WM_LBUTTONDOWN){
			gInterface.Data[eSMITH_EXC5].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		gInterface.Data[eSMITH_EXC5].OnClick = false;
		pSetCursorFocus = true;
		if (Delay < 500){
			return;
		}
		gInterface.Data[eSMITH_EXC5].EventTick = GetTickCount();
		if (!gInterface.Data[eSMITH_EXC5_1].OnShow){
			gInterface.Data[eSMITH_EXC5_1].OnShow = true;
			gSmithItem.ExcOption5 = 1;
			gSmithItem.mExc += 1;
			gSmithItem.TotalPrice += gSmithItem.pExc5;
		}
		else{
			gInterface.Data[eSMITH_EXC5_1].OnShow = false;
			gSmithItem.ExcOption5 = 0;
			gSmithItem.mExc -= 1;
			gSmithItem.TotalPrice -= gSmithItem.pExc5;
		}
	}
	else if (gInterface.IsWorkZone(eSMITH_LEVEL)){
		DWORD Delay = (CurrentTick - gInterface.Data[eSMITH_LEVEL].EventTick);
		if (Event == WM_LBUTTONDOWN){
			gInterface.Data[eSMITH_LEVEL].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		gInterface.Data[eSMITH_LEVEL].OnClick = false;
		pSetCursorFocus = true;
		if (Delay < 100){
			return;
		}
		gInterface.Data[eSMITH_LEVEL].EventTick = GetTickCount();
		if (gSmithItem.mLevel <= 0){
			return;
		}
		else{
			gSmithItem.mLevel -= 1;
			gSmithItem.TotalPrice -= gSmithItem.pLevel;
		}
	}
	else if (gInterface.IsWorkZone(eSMITH_LEVEL_1)){
		DWORD Delay = (CurrentTick - gInterface.Data[eSMITH_LEVEL_1].EventTick);
		if (Event == WM_LBUTTONDOWN){
			gInterface.Data[eSMITH_LEVEL_1].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		gInterface.Data[eSMITH_LEVEL_1].OnClick = false;
		pSetCursorFocus = true;
		if (Delay < 100){
			return;
		}
		gInterface.Data[eSMITH_LEVEL_1].EventTick = GetTickCount();
		if (gSmithItem.mLevel >= gSmithItem.MaxLevel){
			return;
		}
		else{
			gSmithItem.mLevel += 1;
			gSmithItem.TotalPrice += gSmithItem.pLevel;
		}
	}
	else if (gInterface.IsWorkZone(eSMITH_OPT)){
		DWORD Delay = (CurrentTick - gInterface.Data[eSMITH_OPT].EventTick);
		if (Event == WM_LBUTTONDOWN){
			gInterface.Data[eSMITH_OPT].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		gInterface.Data[eSMITH_OPT].OnClick = false;
		pSetCursorFocus = true;
		if (Delay < 100){
			return;
		}
		gInterface.Data[eSMITH_OPT].EventTick = GetTickCount();
		if (gSmithItem.mOpt <= 0){
			return;
		}
		else{
			gSmithItem.mOpt -= 1;
			gSmithItem.TotalPrice -= gSmithItem.pOpt;
		}
	}
	else if (gInterface.IsWorkZone(eSMITH_OPT_1)){
		DWORD Delay = (CurrentTick - gInterface.Data[eSMITH_OPT_1].EventTick);
		if (Event == WM_LBUTTONDOWN){
			gInterface.Data[eSMITH_OPT_1].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		gInterface.Data[eSMITH_OPT_1].OnClick = false;
		pSetCursorFocus = true;
		if (Delay < 100){
			return;
		}
		gInterface.Data[eSMITH_OPT_1].EventTick = GetTickCount();
		if (gSmithItem.mOpt >= gSmithItem.MaxOpt){
			return;
		}
		else{
			gSmithItem.mOpt += 1;
			gSmithItem.TotalPrice += gSmithItem.pOpt;
		}
	}
	else if (gInterface.IsWorkZone(eSMITH_ITEMTYPE)){
		DWORD Delay = (CurrentTick - gInterface.Data[eSMITH_ITEMTYPE].EventTick);
		if (Event == WM_LBUTTONDOWN){
			gInterface.Data[eSMITH_ITEMTYPE].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		gInterface.Data[eSMITH_ITEMTYPE].OnClick = false;
		pSetCursorFocus = true;
		if (Delay < 100){
			return;
		}
		gInterface.Data[eSMITH_ITEMTYPE].EventTick = GetTickCount();
		if (gSmithItem.ItemType <= 0){
			return;
		}
		else{
			gSmithItem.ItemType -= 1;
			gSmithItem.ItemIndex = 0;
		}
	}
	else if (gInterface.IsWorkZone(eSMITH_ITEMTYPE_1)){
		DWORD Delay = (CurrentTick - gInterface.Data[eSMITH_ITEMTYPE_1].EventTick);
		if (Event == WM_LBUTTONDOWN){
			gInterface.Data[eSMITH_ITEMTYPE_1].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		gInterface.Data[eSMITH_ITEMTYPE_1].OnClick = false;
		pSetCursorFocus = true;
		if (Delay < 100){
			return;
		}
		gInterface.Data[eSMITH_ITEMTYPE_1].EventTick = GetTickCount();
		if (gSmithItem.ItemType >= 11){
			return;
		}
		else{
			gSmithItem.ItemType += 1;
			gSmithItem.ItemIndex = 0;
		}
	}
	else if (gInterface.IsWorkZone(eSMITH_DAYS)){
		DWORD Delay = (CurrentTick - gInterface.Data[eSMITH_DAYS].EventTick);
		if (Event == WM_LBUTTONDOWN){
			gInterface.Data[eSMITH_DAYS].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		gInterface.Data[eSMITH_DAYS].OnClick = false;
		pSetCursorFocus = true;
		if (Delay < 100){
			return;
		}
		gInterface.Data[eSMITH_DAYS].EventTick = GetTickCount();
		if (gSmithItem.Days <= 0){
			return;
		}
		else{
			gSmithItem.Days -= 1;
		}
	}
	else if (gInterface.IsWorkZone(eSMITH_DAYS_1)){
		DWORD Delay = (CurrentTick - gInterface.Data[eSMITH_DAYS_1].EventTick);
		if (Event == WM_LBUTTONDOWN){
			gInterface.Data[eSMITH_DAYS_1].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		gInterface.Data[eSMITH_DAYS_1].OnClick = false;
		pSetCursorFocus = true;
		if (Delay < 100){
			return;
		}
		gInterface.Data[eSMITH_DAYS_1].EventTick = GetTickCount();
		if (gSmithItem.Days >= 2){
			return;
		}
		else{
			gSmithItem.Days += 1;
		}
	}
	else if (gInterface.IsWorkZone(eSMITH_ITEMINDEX)){
		DWORD Delay = (CurrentTick - gInterface.Data[eSMITH_ITEMINDEX].EventTick);
		if (Event == WM_LBUTTONDOWN){
			gInterface.Data[eSMITH_ITEMINDEX].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		gInterface.Data[eSMITH_ITEMINDEX].OnClick = false;
		pSetCursorFocus = true;
		if (Delay < 100){
			return;
		}
		gInterface.Data[eSMITH_ITEMINDEX].EventTick = GetTickCount();
		if (gSmithItem.ItemIndex <= 0){
			return;
		}
		if (gSmithItem.ItemType == 0){
			if (gSmithItem.ItemIndex == 31){
				gSmithItem.ItemIndex -= 6;
			}
			else{
				gSmithItem.ItemIndex -= 1;
			}
		}
		else if (gSmithItem.ItemType == 2){
			if (gSmithItem.ItemIndex == 18){
				gSmithItem.ItemIndex -= 2;
			}
			else{
				gSmithItem.ItemIndex -= 1;
			}
		}
		else if (gSmithItem.ItemType == 4){
			if (gSmithItem.ItemIndex == 8 || gSmithItem.ItemIndex == 16 || gSmithItem.ItemIndex == 24){
				gSmithItem.ItemIndex -= 2;
			}
			else{
				gSmithItem.ItemIndex -= 1;
			}
		}
		else if (gSmithItem.ItemType == 7){
			if (gSmithItem.ItemIndex == 16 || gSmithItem.ItemIndex == 11 || gSmithItem.ItemIndex == 24 || gSmithItem.ItemIndex == 33 || gSmithItem.ItemIndex == 38){
				gSmithItem.ItemIndex -= 2;
			}
			else{
				gSmithItem.ItemIndex -= 1;
			}
		}
		else{
			gSmithItem.ItemIndex -= 1;
		}
	}
	else if (gInterface.IsWorkZone(eSMITH_ITEMINDEX_1)){
		DWORD Delay = (CurrentTick - gInterface.Data[eSMITH_ITEMINDEX_1].EventTick);
		if (Event == WM_LBUTTONDOWN){
			gInterface.Data[eSMITH_ITEMINDEX_1].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		gInterface.Data[eSMITH_ITEMINDEX_1].OnClick = false;
		pSetCursorFocus = true;
		if (Delay < 100){
			return;
		}
		gInterface.Data[eSMITH_ITEMINDEX_1].EventTick = GetTickCount();
		if (gSmithItem.ItemType == 0){
			if (gSmithItem.ItemIndex >= 35){
				return;
			}
			if (gSmithItem.ItemIndex == 25){
				gSmithItem.ItemIndex += 6;
			}
			else{
				gSmithItem.ItemIndex += 1;
			}
		}
		else if (gSmithItem.ItemType == 1){
			if (gSmithItem.ItemIndex >= 8){
				return;
			}
			else{
				gSmithItem.ItemIndex += 1;
			}
		}
		else if (gSmithItem.ItemType == 2){
			if (gSmithItem.ItemIndex >= 18){
				return;
			}
			if (gSmithItem.ItemIndex == 16){
				gSmithItem.ItemIndex += 2;
			}
			else{
				gSmithItem.ItemIndex += 1;
			}
		}
		else if (gSmithItem.ItemType == 3){
			if (gSmithItem.ItemIndex >= 11){
				return;
			}
			else{
				gSmithItem.ItemIndex += 1;
			}
		}
		else if (gSmithItem.ItemType == 4){
			if (gSmithItem.ItemIndex >= 24){
				return;
			}
			else if (gSmithItem.ItemIndex == 6 || gSmithItem.ItemIndex == 14 || gSmithItem.ItemIndex == 22){
				gSmithItem.ItemIndex += 2;
			}
			else{
				gSmithItem.ItemIndex += 1;
			}
		}
		else if (gSmithItem.ItemType == 5){
			if (gSmithItem.ItemIndex >= 23){
				return;
			}
			else{
				gSmithItem.ItemIndex += 1;
			}
		}
		else if (gSmithItem.ItemType == 6){
			if (gSmithItem.ItemIndex >= 16){
				return;
			}
			else{
				gSmithItem.ItemIndex += 1;
			}
		}
		else if (gSmithItem.ItemType == 7){
			if (gSmithItem.ItemIndex >= 43){
				return;
			}
			else if (gSmithItem.ItemIndex == 14 || gSmithItem.ItemIndex == 19 || gSmithItem.ItemIndex == 22 || gSmithItem.ItemIndex == 31 || gSmithItem.ItemIndex == 36)	{
				gSmithItem.ItemIndex += 2;
			}
			else{
				gSmithItem.ItemIndex += 1;
			}
		}
		else{
			if (gSmithItem.ItemIndex >= 43){
				return;
			}
			gSmithItem.ItemIndex += 1;
		}
	}
	else if (gInterface.IsWorkZone(eSMITH_CLOSE)){
		DWORD Delay = (CurrentTick - gInterface.Data[eSMITH_CLOSE].EventTick);
		if (Event == WM_LBUTTONDOWN){
			gInterface.Data[eSMITH_CLOSE].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		gInterface.Data[eSMITH_CLOSE].OnClick = false;
		pSetCursorFocus = false;
		if (Delay < 500){
			return;
		}
		gInterface.Data[eSMITH_CLOSE].EventTick = GetTickCount();
		this->CloseSmithItemWindow();
	}
	else if (gInterface.IsWorkZone(eSMITH_BUY)){
		DWORD Delay = (CurrentTick - gInterface.Data[eSMITH_BUY].EventTick);
		if (Event == WM_LBUTTONDOWN){
			gInterface.Data[eSMITH_BUY].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		gInterface.Data[eSMITH_BUY].OnClick = false;
		pSetCursorFocus = false;
		if (Delay < 500){
			return;
		}
		gInterface.Data[eSMITH_BUY].EventTick = GetTickCount();
		if (gSmithItem.ItemType >= 7){
			gSmithItem.mSkill = 0;
		}
		SDHP_BUYSVSHOP pMsg;
		pMsg.h.set(0xFD, 0x08, sizeof(pMsg));
		pMsg.ItemType = gSmithItem.ItemType;
		pMsg.ItemIndex = gSmithItem.ItemIndex;
		pMsg.Days = gSmithItem.Days;
		pMsg.mLevel = gSmithItem.mLevel;
		pMsg.mSkill = gSmithItem.mSkill;
		pMsg.mLuck = gSmithItem.mLuck;
		pMsg.mOpt = gSmithItem.mOpt;
		pMsg.ExcOption = gSmithItem.ExcOption;
		pMsg.ExcOption1 = gSmithItem.ExcOption1;
		pMsg.ExcOption2 = gSmithItem.ExcOption2;
		pMsg.ExcOption3 = gSmithItem.ExcOption3;
		pMsg.ExcOption4 = gSmithItem.ExcOption4;
		pMsg.ExcOption5 = gSmithItem.ExcOption5;
		pMsg.mExc = gSmithItem.mExc;
		DataSend((BYTE*)&pMsg, pMsg.h.size);
		this->CloseSmithItemWindow();
	}
}