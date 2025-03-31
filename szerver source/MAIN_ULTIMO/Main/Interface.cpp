#include "stdafx.h"
#include "Common.h"
#include "CustomCommandInfo.h"
#include "CustomEventTime.h"
#include "Interface.h"
#include "Import.h"
#include "Reconnect.h"
#include "TMemory.h"
#include "Defines.h"
#include "OffTrade.h"
#include "Protect.h"
#include "Protocol.h"
#include "PrintPlayer.h"
#include "User.h"
#include "Util.h"
#include "array.h"
#include "Offset.h"
#include "StatsAdvance.h"
#include "CustomCloak.h"
#include "ChatExpanded.h"
#include "Camera.h"
#include "TrayModeNew.h"
#include "Controller.h"
#include "postInterface.h"
#include "Ruud.h"
#include "Inter3.h"
#include "InterEx.h"
#include "Central.h"
#include "ware.h"
#include "JewelryBank.h"
#include "PartySearch.h"
#include "PartySearchSettings.h"
#include "ChangeClass.h"
#include "ResetSystem.h"
#include "LuckyWheel.h"
#include "WindowsStruct.h"
#include "ShopSearch.h"
#include "Achievements.h"
#include "Ranking.h"
#include "SmithItem.h"
#include "WindowsQuest.h"
#include "MuHelper.h"
#include "ResetSystemPanel.h"
#include "GrandResetSystem.h"

Interface gInterface;

Interface::Interface()
{
}

Interface::~Interface()
{
}

void Interface::RenderObjectSystem()
{
	if(gProtect.m_MainInfo.MonitorMS == 1){
		gInterface.lastReport = GetTickCount();
		gInterface.frameCount = 0;
	}
	if(gProtect.m_MainInfo.MonitorFPS == 1){
		gInterface.iniciador = 1;
	}
	//51522
	//--
	
	this->BindObject(eMenu_MAIN, 0x7A5A, 222, 340, 205, -1);
	this->BindObject(eMenu_MAIN2, 0x7A5A, 222, 340, 205, -1);
	this->BindObject(eMenu_CLOSE, 71521, 59, 28, -1, -1);
	this->BindObject(eMenu_OPT1, 71522, 108, 30.5f, -1, -1);
	this->BindObject(eMenu_OPT2, 71522, 108, 30.5f, -1, -1);
	this->BindObject(eMenu_OPT3, 71522, 108, 30.5f, -1, -1);
	this->BindObject(eMenu_OPT4, 71522, 108, 30.5f, -1, -1);
	this->BindObject(eMenu_OPT5, 71522, 108, 30.5f, -1, -1);
	this->BindObject(eMenu_OPT6, 71522, 108, 30.5f, -1, -1);
	this->BindObject(eMenu_OPT7, 71522, 108, 30.5f, -1, -1);
	this->BindObject(eMenu_OPT8, 71522, 108, 30.5f, -1, -1);
	this->BindObject(eMenu_OPT9, 71522, 108, 30.5f, -1, -1);
	this->BindObject(eMenu_OPT10, 71522, 108, 30.5f, -1, -1);
	this->BindObject(eMenu_OPT11, 71522, 108, 30.5f, -1, -1);
	//--
	this->BindObject(eButtonOption1, 31593, 15, 15, -1, -1);
	this->BindObject(eButtonOption2, 31593, 15, 15, -1, -1);
	this->BindObject(eButtonOption3, 31593, 15, 15, -1, -1);
	this->BindObject(eButtonOption4, 31593, 15, 15, -1, -1);
	this->BindObject(eButtonOption5, 31593, 15, 15, -1, -1);
	this->BindObject(eButtonOption6, 31593, 15, 15, -1, -1);
	this->BindObject(eButtonOption7, 31593, 15, 15, -1, -1);
	this->BindObject(eButtonOption8, 31593, 15, 15, -1, -1);
	this->BindObject(eButtonOption9, 31593, 15, 15, -1, -1);
	this->BindObject(eCloseOption, 71521, 59, 28, -1, -1);
	//--
	this->BindObject(eTIME, 0x787F, 131, 70, -10, 359);
	this->BindObject(eFlag01, 0x7880, 78, 78, -1, -1);
	this->BindObject(eFlag02, 0x7881, 78, 78, -1, -1);
	this->BindObject(eFlag03, 0x7882, 78, 78, -1, -1);
	this->BindObject(eFlag04, 0x7883, 78, 78, -1, -1);
	this->BindObject(eFlag05, 0x7884, 78, 78, -1, -1);
	this->BindObject(eFlag06, 0x7885, 78, 78, -1, -1);
	this->BindObject(eFlag07, 0x7886, 78, 78, -1, -1);
	this->BindObject(eFlag08, 0x7887, 78, 78, -1, -1);
	this->BindObject(eFlag09, 0x7888, 78, 78, -1, -1);
	this->BindObject(eFlag10, 0x7889, 78, 78, -1, -1);
	this->BindObject(eFlag11, 0x7890, 78, 78, -1, -1);
	this->BindObject(eFlag12, 0x7891, 78, 78, -1, -1);
	this->BindObject(eFlag13, 0x7892, 78, 78, -1, -1);
	this->BindObject(eFlag14, 0x7893, 78, 78, -1, -1);
	this->BindObject(eFlag15, 0x7894, 78, 78, -1, -1);
	this->BindObject(eFlag16, 0x7895, 78, 78, -1, -1);
	this->BindObject(eFlag17, 0x7896, 78, 78, -1, -1);
	this->BindObject(eFlag18, 0x7897, 78, 78, -1, -1);
	this->BindObject(eFlag19, 0x7898, 78, 78, -1, -1);
	this->BindObject(eFlag20, 0x7899, 78, 78, -1, -1);
	this->BindObject(eFlag21, 0x7900, 78, 78, -1, -1);
	this->BindObject(eFlag22, 0x7901, 78, 78, -1, -1);
	//--
	this->BindObject(eMAIN_RANKING, 0x7A5A, 445, 364, 205, -1);
	//--
	this->BindObject(eSAMPLEBUTTON, 0x7903, 25, 40, -1, -1);
	this->BindObject(eSAMPLEBUTTON2, 0x7904, 25, 40, -1, -1);
	//--
	this->BindObject(eVip_MAIN, 0x7A5A, 222, 300, 205, -1);
	this->BindObject(eVip_TITLE, 0x7A63, 230, 67, -1, -1);
	this->BindObject(eVip_FRAME, 0x7A58, 230, 15, -1, -1);
	this->BindObject(eVip_FOOTER, 0x7A59, 230, 50, -1, -1);
	this->BindObject(eVip_DIV, 0x7A62, 223, 21, -1, -1);
	this->BindObject(eVip_CLOSE, 0x7EC5, 36, 29, -1, -1);
	this->BindObject(eVip_BRONZE, 0x7A5E, 108, 29, -1, -1);
	this->BindObject(eVip_SILVER, 0x7A5E, 108, 29, -1, -1);
	this->BindObject(eVip_GOLD, 0x7A5E, 108, 29, -1, -1);
	this->BindObject(eVip_PLATINUM, 0x7A5E, 108, 29, -1, -1);
	this->BindObject(eVip_STATUS, 0x7A5E, 108, 29, -1, -1);
	
	//--
	this->BindObject(eCommand_MAIN, 0x7A5A, 222, 300, 205, -1);
	this->BindObject(eCommand_TITLE, 0x7A63, 230, 67, -1, -1);
	this->BindObject(eCommand_FRAME, 0x7A58, 230, 15, -1, -1);
	this->BindObject(eCommand_FOOTER, 0x7A59, 230, 50, -1, -1);
	this->BindObject(eCommand_DIV, 0x7A62, 223, 21, -1, -1);
	this->BindObject(eCommand_CLOSE, 0x7EC5, 36, 29, -1, -1);
	//--
	this->BindObject(eEventTime_MAIN, 0x7A5A, 222, 300, 205, -1);
	this->BindObject(eEventTime_CLOSE, 0x7EC5, 36, 29, -1, -1);
	//--
	this->BindObject(eCONFIRM_MAIN, 0x7A5A, 222, 120, 205, -1);
	this->BindObject(eCONFIRM_TITLE, 0x7A63, 230, 67, -1, -1);
	this->BindObject(eCONFIRM_FRAME, 0x7A58, 230, 15, -1, -1);
	this->BindObject(eCONFIRM_FOOTER, 0x7A59, 230, 50, -1, -1);
	this->BindObject(eCONFIRM_DIV, 0x7A62, 223, 21, -1, -1);
	this->BindObject(eCONFIRM_BTN_OK, 0x7A5B, 54, 30, -1, -1);
	this->BindObject(eCONFIRM_BTN_CANCEL, 0x7A5C, 54, 30, -1, -1);
	this->BindObject(eLogo, 0x7905, 150, 114, -1, -1);
	this->BindObject(chatbackground, 51545, 300.0f, 128.0f, -10, 569);
	//Custom Store
	this->BindObject(eOFFTRADE_JoB, 0x7908, 40, 19, -1, -1);
	this->BindObject(eOFFTRADE_JoS, 0x7908, 40, 19, -1, -1);
	this->BindObject(eOFFTRADE_JoC, 0x7908, 40, 19, -1, -1);
	this->BindObject(eOFFTRADE_WCC, 0x7908, 40, 19, -1, -1);
	this->BindObject(eOFFTRADE_WCP, 0x7908, 40, 19, -1, -1);
	this->BindObject(eOFFTRADE_WCG, 0x7908, 40, 19, -1, -1);
	this->BindObject(eOFFTRADE_OPEN, 0x7BFD, 108, 30, -1, -1);
	//-- custom
	this->BindObject(eSTORE_CLOSE, 0x7BFD, 108, 30, -1, -1);
	//Minimap
	this->BindObject(eNULL_MAP, 31461, 128, 128, -1, -1);
	this->BindObject(ePLAYER_POINT, 31460, 3, 3, -1, -1);

	this->BindObject(eNextCommand, 31659, 17, 18, -1, -1);
	this->BindObject(ePrevCommand, 31658, 17, 18, -1, -1);
	this->BindObject(eNextEvent, 31659, 17, 18, -1, -1);
	this->BindObject(ePrevEvent, 31658, 17, 18, -1, -1);
	this->BindObject(eCamera3DInit, 31659, 17, 18, -1, -1);
	this->BindObject(eCamera3DSwitch, 31659, 17, 18, -1, -1);
	this->Data[eTIME].OnShow = true;
	if(gProtect.m_MainInfo.CustomInterfaceType == 3 || gProtect.m_MainInfo.CustomInterfaceType == 4)
	{
		this->BindObject(ButtonSettings, 51522, 19, 19, -1, -1);
		this->BindObject(ButtonStart, 51522, 19, 19, -1, -1);
		this->BindObject(ButtonStop, 51522, 19, 19, -1, -1);
		this->BindObject(ButtonCamera, 51522, 19, 19, -1, -1);
	}
	else
	{
		this->BindObject(ButtonSettings, 31761, 18, 13.3, -1, -1);
		this->BindObject(ButtonStart, 31762, 18, 13.3, -1, -1);
		this->BindObject(ButtonStop, 31763, 18, 13.3, -1, -1);
	}
	this->BindObject(ButtonStartAttack, 31593, 15, 15, -15, -15);
	this->BindObject(ButtonZenOff, 31593, 15, 15, -15, -15);
	//--
	this->BindObject(eJewelOfBank, 51522, 230.0, 270.0, -1, -1);
	this->BindObject(eJewelOfBankPush, 71521, 59, 28, -1, -1);
	this->BindObject(eJewelOfBankRemove, 71521, 59, 28, -1, -1);
	this->BindObject(eJewelOfBankClose, 71521, 59, 28, -1, -1);

	switch(gProtect.m_MainInfo.CustomInterfaceType)
	{
	case 1:
	case 2:
		//--
		if (gProtect.m_MainInfo.CustomMenuType == 1)
		{
			this->BindObject(eMenu, 0x7906, 102, 29, -1, -1);
		}
		else
		{
			this->BindObject(eMenu, 0x7906, 16, 12, -1, -1);
			this->BindObject(eMenuBG, 0x7907, 36, 18, 174, 0);
		}
		//--
		this->BindObject(MINIMAP_FRAME, 31608, 154, 162, -10, 359);
		this->BindObject(MINIMAP_TIME_FRAME, 31609, 134.0, 37.0, -10, 359);
		this->BindObject(MINIMAP_BUTTOM, 31617, 38.0f, 24.0f, -10, 569);
		//---
		this->BindObject(eDragonLeft, 2337, 108.0, 45.0, 0.0, 385);
		this->BindObject(eDragonRight, 2336, 108.0, 45.0, 532.0, 385);
		this->BindObject(eParty, iNewParty, 25, 25, 348, 449);
		this->BindObject(eCharacter, iNewCharacter, 25, 25, 379, 449);
		this->BindObject(eInventory, iNewInventory, 25, 25, 409, 449);
		this->BindObject(eFriend, iNewWinpush, 52, 18, 581, 432);

		if(gProtect.m_MainInfo.CustomInterfaceType == 2)
		{
			this->BindObject(eFastMenu, iNewFastMenu, 53, 19, 5, 432);
		}
		this->BindObject(eGuild, iNewGuild, 52, 18, 581, 454);
		break;
	case 3:
	case 4:
		this->BindObject(eButton1, 61525, 43.0f, 17.0f, -43.0f, -17.0f);
		this->BindObject(eButton2, 61525, 43.0f, 17.0f, -43.0f, -17.0f);
		this->BindObject(eButton3, 61525, 43.0f, 17.0f, -43.0f, -17.0f);
		this->BindObject(eButton4, 61525, 43.0f, 17.0f, -43.0f, -17.0f);
		this->BindObject(eButton5, 61525, 43.0f, 17.0f, -43.0f, -17.0f);

		this->BindObject(eButtonAncient, 61525, 43.0f, 17.0f, -43.0f, -17.0f);
		this->BindObject(eButtonSocket, 61525, 43.0f, 17.0f, -43.0f, -17.0f);
		this->BindObject(eButtonRepair, 61525, 43.0f, 17.0f, -43.0f, -17.0f);
		this->BindObject(eButtonRepairShop, 61525, 43.0f, 17.0f, -43.0f, -17.0f);
		this->BindObject(eButtonRepairAll, 61525, 43.0f, 17.0f, -43.0f, -17.0f);
		this->BindObject(eButtonStorage, 61525, 43.0f, 17.0f, -43.0f, -17.0f);
		this->BindObject(eButtonInvExt, 61525, 43.0f, 17.0f, -43.0f, -17.0f);

		if (gProtect.m_MainInfo.CustomMenuType == 1)
		{
			this->BindObject(eMenu, 0x7906, 102, 29, -1, -1);
		}
		else
		{
			this->BindObject(eMenu, 51522, 19, 19, -1, -1);
			this->BindObject(eMenuBG, 51522, 36, 18, 174, 0);
		}

		if (gProtect.m_MainInfo.NewPanelCharacterS10 == 0)
		{
			if (gProtect.m_MainInfo.DisableAdvance == 0)
			{
				gInterface.BindObject(eADVANCE_STAT_INFO, ex_INFO_3, 35, 30, -1, -1);
			}
		}

		//Ex700
		this->BindObject(chatbackground, 51545, 300.0f, 128.0f, -10, 569);
		this->BindObject(eShop, 51522, 19.5f, 19.5f, -1, -1);
		this->BindObject(eCharacter, 51522, 19.5f, 19.5f, -1, -1);
		this->BindObject(eInventory, 51522, 19.5f, 19.5f, -1, -1);
		this->BindObject(eQuest, 51522, 19.5f, 19.5f, -1, -1);
		this->BindObject(eCommunity, 51522, 19.5f, 19.5f, -1, -1);
		this->BindObject(eSystem, 51522, 19.5f, 19.5f, -1, -1);
		break;
	default:
		if (gProtect.m_MainInfo.CustomMenuType == 1)
		{
			this->BindObject(eMenu, 0x7906, 102, 29, -1, -1);
		}
		else
		{
			this->BindObject(eMenu, 0x7906, 16, 12, -1, -1);
			this->BindObject(eMenuBG, 0x7907, 36, 18, 174, 0);
		}
		break;
	}
	if(gProtect.m_MainInfo.InventoryUPGRADE == 1)
	{
		this->BindObject(eMoney1, 0x7909, 75, 13, -1, -1);
		this->BindObject(eMoney2, 0x7910, 75, 13, -1, -1);
	}
	if(gProtect.m_MainInfo.DisableAdvance == 0)
	{
		gInterface.BindObject(eADVANCE_STAT_INFO, ex_INFO_3, 35, 30, -1, -1);
	}

	//customware
#if (WARE==1)
	this->BindObject(eWAREHOUSE_MAIN, 0x7A5A, 222, 370, 205, -1);
	this->BindObject(eWAREHOUSE_CLOSE, 71521, 59, 28, -1, -1);
	this->BindObject(eWAREHOUSE_NUM1, 71522, 108, 30.5f, -1, -1);
	this->BindObject(eWAREHOUSE_NUM2, 71522, 108, 30.5f, -1, -1);
	this->BindObject(eWAREHOUSE_NUM3, 71522, 108, 30.5f, -1, -1);
	this->BindObject(eWAREHOUSE_NUM4, 71522, 108, 30.5f, -1, -1);
	this->BindObject(eWAREHOUSE_NUM5, 71522, 108, 30.5f, -1, -1);
	this->BindObject(eWAREHOUSE_NUM6, 71522, 108, 30.5f, -1, -1);
	this->BindObject(eWAREHOUSE_NUM7, 71522, 108, 30.5f, -1, -1);
	this->BindObject(eWAREHOUSE_NUM8, 71522, 108, 30.5f, -1, -1);
#endif

	// party search
	this->BindObject(ePARTYSETTINGS_MAIN, 0x7A5A, 222, 345, -1, -1);
	this->BindObject(ePARTYSETTINGS_TITLE, 0x7A63, 230, 67, -1, -1);
	this->BindObject(ePARTYSETTINGS_FRAME, 0x7A58, 230, 15, -1, -1);
	this->BindObject(ePARTYSETTINGS_FOOTER, 0x7A59, 230, 50, -1, -1);
	this->BindObject(ePARTYSETTINGS_DIV, 0x7A62, 223, 21, -1, -1);
	this->BindObject(ePARTYSETTINGS_CLOSE, 0x7EC5, 36, 29, -1, -1);
	this->BindObject(ePARTYSETTINGS_SYSTEM_ACTIVE, 0x7BAE, 15, 15, -1, -1);
	this->BindObject(ePARTYSETTINGS_ONLY_GUILD, 0x7BAE, 15, 15, -1, -1);
	this->BindObject(ePARTYSETTINGS_ONE_CLASS, 0x7BAE, 15, 15, -1, -1);
	this->BindObject(ePARTYSETTINGS_DARK_WIZARD, 0x7BAE, 15, 15, -1, -1);
	this->BindObject(ePARTYSETTINGS_DARK_KNIGHT, 0x7BAE, 15, 15, -1, -1);
	this->BindObject(ePARTYSETTINGS_ELF, 0x7BAE, 15, 15, -1, -1);
	this->BindObject(ePARTYSETTINGS_MAGIC_GLADIATOR, 0x7BAE, 15, 15, -1, -1);
	this->BindObject(ePARTYSETTINGS_DARK_LORD, 0x7BAE, 15, 15, -1, -1);
	this->BindObject(ePARTYSETTINGS_SUMMONER, 0x7BAE, 15, 15, -1, -1);
	this->BindObject(ePARTYSETTINGS_RAGE_FIGHTER, 0x7BAE, 15, 15, -1, -1);
	this->BindObject(ePARTYSETTINGS_LEVEL_MINUS, 0x7C0D, 16, 15, -1, -1);
	this->BindObject(ePARTYSETTINGS_LEVEL_PLUS, 0x7AA4, 16, 15, -1, -1);
	this->BindObject(ePARTYSETTINGS_OK, 0x7A5B, 54, 30, -1, -1);
	this->BindObject(ePARTYSEARCH_MAIN, 0x7A5A, 222, 345, -1, -1);
	this->BindObject(ePARTYSEARCH_TITLE, 0x7A63, 230, 67, -1, -1);
	this->BindObject(ePARTYSEARCH_FRAME, 0x7A58, 230, 15, -1, -1);
	this->BindObject(ePARTYSEARCH_FOOTER, 0x7A59, 230, 50, -1, -1);
	this->BindObject(ePARTYSEARCH_DIV, 0x7A62, 223, 21, -1, -1);
	this->BindObject(ePARTYSEARCH_CLOSE, 0x7EC5, 36, 29, -1, -1);
	this->BindObject(ePARTYSEARCH_LEFT, 0x7E56, 20, 23, -1, -1);
	this->BindObject(ePARTYSEARCH_RIGHT, 0x7E57, 20, 23, -1, -1);

	// change Class
	this->BindObject(eCHANGE_MAIN, 0x7A5A, 222, 340, 205, -1);
	this->BindObject(eCHANGEDW_FINISH, 71522, 108, 30.5f, -1, -1);
	this->BindObject(eCHANGEDK_FINISH, 71522, 108, 30.5f, -1, -1);
	this->BindObject(eCHANGEELF_FINISH, 71522, 108, 30.5f, -1, -1);
	this->BindObject(eCHANGEMG_FINISH, 71522, 108, 30.5f, -1, -1);
	this->BindObject(eCHANGEDL_FINISH, 71522, 108, 30.5f, -1, -1);
	this->BindObject(eCHANGESU_FINISH, 71522, 108, 30.5f, -1, -1);
	this->BindObject(eCHANGERF_FINISH, 71522, 108, 30.5f, -1, -1);

#if (RESETCHANGE == 1)
	this->BindObject(eRESETCHANGE, 0x7A5A, 222, 320, 205, -1);
	this->BindObject(eMenu_CLOSE, 71521, 59, 28, -1, -1);
	this->BindObject(eBOTON1, 71521, 59, 28, -1, -1);
	this->BindObject(eBOTON2, 71521, 59, 28, -1, -1);
	this->BindObject(eBOTON3, 71521, 59, 28, -1, -1);
	this->BindObject(eBOTON4, 71521, 59, 28, -1, -1);
	this->BindObject(eBOTON5, 71521, 59, 28, -1, -1);
#endif

	//Lucky Wheel
	this->BindObject(eLuckyWheelStart, 71522, 108, 30.5f, -1, -1);
	this->BindObject(eLuckyWheelPanel, 0x7A5A, 312, 292, -1, -1);
	this->BindObject(eLuckyWheel_CLOSE, 71521, 59, 28, -1, -1);

	this->BindObject(OBJECT_RESET_MAIN, 0x7A5A, 222, 303, -1, -1);
	this->BindObject(OBJECT_RESET_TITLE, 0x7A63, 230, 67, -1, -1);
	this->BindObject(OBJECT_RESET_FRAME, 0x7A58, 230, 15, -1, -1);
	this->BindObject(OBJECT_RESET_FOOTER, 0x7A59, 230, 50, -1, -1);
	this->BindObject(OBJECT_RESET_DIV, 0x7A62, 223, 21, -1, -1);
	this->BindObject(OBJECT_RESET_INFO_BG, 0x7AA3, 170, 21, -1, -1);
	this->BindObject(OBJECT_RESET_MONEY_BG, 0x7A89, 170, 26, -1, -1);
	this->BindObject(OBJECT_RESET_CLOSE, 0x7EC5, 36, 29, -1, -1);
	this->BindObject(OBJECT_RESET_FINISH, 0x7A5E, 106, 29, -1, -1);

	this->BindObject(OBJECT_GRESET_MAIN, 0x7A5A, 222, 303, -1, -1);
	this->BindObject(OBJECT_GRESET_TITLE, 0x7A63, 230, 67, -1, -1);
	this->BindObject(OBJECT_GRESET_FRAME, 0x7A58, 230, 15, -1, -1);
	this->BindObject(OBJECT_GRESET_FOOTER, 0x7A59, 230, 50, -1, -1);
	this->BindObject(OBJECT_GRESET_DIV, 0x7A62, 223, 21, -1, -1);
	this->BindObject(OBJECT_GRESET_INFO_BG, 0x7AA3, 170, 21, -1, -1);
	this->BindObject(OBJECT_GRESET_MONEY_BG, 0x7A89, 170, 26, -1, -1);
	this->BindObject(OBJECT_GRESET_CLOSE, 0x7EC5, 36, 29, -1, -1);
	this->BindObject(OBJECT_GRESET_FINISH, 0x7A5E, 128, 29, -1, -1);


	SetRange((LPVOID)0x00842086, 5, ASM::NOP);
	SetRange((LPVOID)0x0084234F, 5, ASM::NOP);
	SetRange((LPVOID)0x008423C3, 5, ASM::NOP);
	SetOp((LPVOID)oLoadSomeForm_Call, this->LoadImages, ASM::CALL);
	SetOp((LPVOID)oDrawInterface_Call, this->Work, ASM::CALL);

	if(gProtect.m_MainInfo.InventoryUPGRADE == 1)
	{
		SetRange((LPVOID)0x00835116, 5, ASM::NOP);
		SetOp((LPVOID)0x00835116, this->DrawZenAndRud, ASM::CALL);
	}

	this->ClickTime = 0;

	g_PersonalShopEx.BindImages();

#if (ARCHIVEMENT == 1)
	gAchievements.BindImages();
#endif

#if (JEWEL_BANK == 1)
	gJewelsBank.JewelsBankLoad();
#endif

	gSmithItem.Bind();

	g_ExWinQuestSystem.BindImages();
}

void Interface::DrawZenAndRud(int a1, int a2, int a3, int a4)
{
	int v10;
	int v11;
	DWORD v23;
	v10 = *(DWORD*)(a1 + 40);
	v11 = *(DWORD*)(a1 + 36);
	v23 = *(DWORD*)(*(DWORD*)0x8128AC4 + 5956);
	*(float*)(0x00D24E88); //Width

	char MoneyBuff1[50], MoneyBuff2[50], MoneyBuff3[50], MoneyBuff4[50], test[50];
	ZeroMemory(MoneyBuff1, sizeof(MoneyBuff1));
	ZeroMemory(MoneyBuff2, sizeof(MoneyBuff2));
	ZeroMemory(MoneyBuff3, sizeof(MoneyBuff3));
	ZeroMemory(MoneyBuff4, sizeof(MoneyBuff4));

	pGetMoneyFormat(v23, MoneyBuff1, 0);
	pGetMoneyFormat(Coin3, MoneyBuff2, 0);
	pGetMoneyFormat(Coin1, MoneyBuff3, 0);
	pGetMoneyFormat(Coin2, MoneyBuff4, 0);

	gInterface.DrawFormat(eWhite, v11, v10 + 12, 190, 3, pGetTextLine(pTextLineThis, 223));
	//--
	gInterface.DrawGUI(eMoney1, v11 + 18, v10 + 365);
	gInterface.DrawFormat(eBlack, v11 + 18, v10 + 367, 20, 1, "Zen");
	gInterface.DrawFormat(eRed, v11 + 40, v10 + 367, 50, 3, "%s", MoneyBuff1);
	//--
	gInterface.DrawGUI(eMoney2, v11 + 102, v10 + 365);
	gInterface.DrawFormat(eBlack, v11 + 102, v10 + 367, 20, 1, "GP");
	gInterface.DrawFormat(eWhite, v11 + 128, v10 + 367, 45, 4, "%s", MoneyBuff2);
	//--
	gInterface.DrawGUI(eMoney2, v11 + 18, v10 + 378);
	gInterface.DrawFormat(eBlack, v11 + 17, v10 + 380, 20, 1, "WC");
	gInterface.DrawFormat(eGold, v11 + 38, v10 + 381, 50, 4, "%s", MoneyBuff3);
	//--
	gInterface.DrawGUI(eMoney2, v11 + 102, v10 + 378);
	gInterface.DrawFormat(eBlack, v11 + 98, v10 + 380, 20, 1, "WCP");
	gInterface.DrawFormat(eBlue, v11 + 128, v10 + 381, 45, 4, "%s", MoneyBuff4);
}

void Interface::LoadModels()
{
	pLoadModel(406, "Data\\Custom\\Bmd\\VIP1\\", "musign", -1);
	pLoadTexture(406, "Custom\\Bmd\\VIP1\\", 0x2901, 0x2600, 1);
	pLoadModel(407, "Data\\Custom\\Bmd\\VIP2\\", "musign", -1);
	pLoadTexture(407, "Custom\\Bmd\\VIP2\\", 0x2901, 0x2600, 1);
	pLoadModel(408, "Data\\Custom\\Bmd\\VIP3\\", "musign", -1);
	pLoadTexture(408, "Custom\\Bmd\\VIP3\\", 0x2901, 0x2600, 1);
	// ----
	pInitModelData2();
}

void Interface::LoadImages()
{
	if(gProtect.m_MainInfo.InventoryUPGRADE == 1)
	{
		pLoadImage("Custom\\Interface\\Money\\item_money.tga", 0x7909, 0x2601, 0x2901, 1, 0);
		pLoadImage("Custom\\Interface\\Money\\item_money2.tga", 0x7910, 0x2601, 0x2901, 1, 0);
	}
	//
	pLoadImage("Custom\\Interface\\Rank01.tga", 0x7880, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank02.tga", 0x7881, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank03.tga", 0x7882, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank04.tga", 0x7883, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank05.tga", 0x7884, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank06.tga", 0x7885, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank07.tga", 0x7886, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank08.tga", 0x7887, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank09.tga", 0x7888, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank10.tga", 0x7889, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank11.tga", 0x7890, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank12.tga", 0x7891, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank13.tga", 0x7892, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank14.tga", 0x7893, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank15.tga", 0x7894, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank16.tga", 0x7895, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank17.tga", 0x7896, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank18.tga", 0x7897, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank19.tga", 0x7898, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank20.tga", 0x7899, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank21.tga", 0x7900, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank22.tga", 0x7901, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Ranking.tga", 0x7902, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Next.tga", 0x7903, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Previous.tga", 0x7904, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\MU-logo.tga", 0x7905, 0x2601, 0x2901, 1, 0);

	if (gProtect.m_MainInfo.CustomMenuType == 1)
	{
		pLoadImage("Custom\\Interface\\Menu1.tga", 0x7906, 0x2601, 0x2901, 1, 0);
	}
	else
	{
		pLoadImage("Custom\\Interface\\Menu2.tga", 0x7906, 0x2601, 0x2901, 1, 0);
		pLoadImage("Custom\\Interface\\Menu_BG.tga", 0x7907, 0x2601, 0x2901, 1, 0);
	}
	pLoadImage("Custom\\Interface\\Button.tga", 0x7908, 0x2601, 0x2900,1,0);
	//MiniMap
	pLoadImage("Custom\\Interface\\none.tga", 31461, 0x2601, 0x2900, 1, 0);
	//--
	pLoadImage("Interface\\mini_map_ui_party.tga", 61520, 0x2601, 0x2901, 1, 0); //esquina abajo derecha

	if(gProtect.m_MainInfo.TooltipS15 == 1)
	{
		//-- itemtooltip
		pLoadImage("Interface\\GFx\\tooltip_bg01.tga", 61511, 0x2601, 0x2901, 1, 0); //esquina arriba izquierda
		pLoadImage("Interface\\GFx\\tooltip_bg02.tga", 61512, 0x2601, 0x2901, 1, 0);
		pLoadImage("Interface\\GFx\\tooltip_bg03.tga", 61513, 0x2601, 0x2901, 1, 0); //esquina arriba derecha
		pLoadImage("Interface\\GFx\\tooltip_bg04.tga", 61514, 0x2601, 0x2901, 1, 0);
		pLoadImage("Interface\\GFx\\tooltip_bg06.tga", 61515, 0x2601, 0x2901, 1, 0);
		pLoadImage("Interface\\GFx\\tooltip_bg07.tga", 61516, 0x2601, 0x2901, 1, 0); //esquina abajo izquierda
		pLoadImage("Interface\\GFx\\tooltip_bg08.tga", 61517, 0x2601, 0x2901, 1, 0);
		pLoadImage("Interface\\GFx\\tooltip_bg09.tga", 61518, 0x2601, 0x2901, 1, 0); //esquina abajo derecha
	}
	//-- itemtooltip
	pLoadImage("Interface\\GFx\\popupbg01.tga", 71511, 0x2601, 0x2901, 1, 0); //esquina arriba izquierda
	pLoadImage("Interface\\GFx\\popupbg02.tga", 71512, 0x2601, 0x2901, 1, 0);
	pLoadImage("Interface\\GFx\\popupbg03.tga", 71513, 0x2601, 0x2901, 1, 0); //esquina arriba derecha
	pLoadImage("Interface\\GFx\\popupbg04.tga", 71514, 0x2601, 0x2901, 1, 0);
	pLoadImage("Interface\\GFx\\popupbg06.tga", 71515, 0x2601, 0x2901, 1, 0);
	pLoadImage("Interface\\GFx\\popupbg07.tga", 71516, 0x2601, 0x2901, 1, 0); //esquina abajo izquierda
	pLoadImage("Interface\\GFx\\popupbg08.tga", 71517, 0x2601, 0x2901, 1, 0);
	pLoadImage("Interface\\GFx\\popupbg09.tga", 71518, 0x2601, 0x2901, 1, 0); //esquina abajo derecha
	//--
	pLoadImage("Interface\\GFx\\popup_line_m.tga", 71519, 0x2601, 0x2901, 1, 0); //esquina abajo derecha
	pLoadImage("Interface\\GFx\\popup_line_s.tga", 71520, 0x2601, 0x2901, 1, 0); //esquina abajo derecha
	//--
	pLoadImage("Interface\\GFx\\Render_buttom_1.tga", 71521, 0x2601, 0x2901, 1, 0); //esquina abajo derecha
	pLoadImage("Interface\\GFx\\Render_buttom_2.tga", 71522, 0x2601, 0x2901, 1, 0); //esquina abajo derecha
	pLoadImage("Interface\\GFx\\Render_buttom_3.tga", 71524, 0x2601, 0x2901, 1, 0); //esquina abajo derecha
	//--
	pLoadImage("Interface\\GFx\\RenderBits_Sound.tga", 71523, 0x2601, 0x2901, 1, 0); //esquina abajo derecha
	//pLoadImage("Interface\\GFx\\JewelBank.tga", 71525, 0x2601, 0x2901, 1, 0); //esquina abajo derecha
	//pLoadImage("Interface\\GFx\\PetInventoryFrame.tga", 71526, 0x2601, 0x2901, 1, 0); //esquina abajo derecha
	//--
	pLoadImage("Interface\\GFx\\newui_option_volume01.tga", 31596, 0x2601, 0x2901, 1, 0); //esquina abajo derecha
	pLoadImage("Interface\\GFx\\newui_option_volume02.tga", 31597, 0x2601, 0x2901, 1, 0); //esquina abajo derecha
	pLoadImage("Interface\\GFx\\Party\\newui_Party_Back.tga", 81520, 0x2601, 0x2901, 1, 0);
	pLoadImage("Interface\\GFx\\Party\\newui_Party_flag.tga", 81521, 0x2601, 0x2901, 1, 0);
	pLoadImage("Interface\\GFx\\Party\\newui_Party_HpBar.jpg", 81522, 0x2601, 0x2901, 1, 0);
	pLoadImage("Interface\\GFx\\Party\\newui_Party_ManaBar.jpg", 81523, 0x2601, 0x2901, 1, 0);
	pLoadImage("Interface\\GFx\\Party\\newui_Party_X.tga", 81524, 0x2601, 0x2901, 1, 0);
	//--
	pLoadImage("Interface\\GFx\\Party\\BarraMixta.jpg", 81525, 0x2601, 0x2901, 1, 0);
	pLoadImage("Interface\\GFx\\Party\\newui_Party_Manabar02.jpg", 81526, 0x2601, 0x2901, 1, 0);
	pLoadImage("Interface\\GFx\\Party\\PartyPlayerInfo.tga", 81527, 0x2601, 0x2901, 1, 0);
	//-------------- custom interfaces
	LoadBitmapA("Interface\\newui_number1.tga", 31337, 9729, 10496, 1, 0);

	LoadBitmapA("Interface\\newui_SW_Minimap_Frame.tga", 31608, GL_LINEAR, GL_CLAMP, 1, 0);
	LoadBitmapA("Interface\\newui_SW_Time_Frame.tga", 31609, GL_LINEAR, GL_CLAMP, 1, 0);
	LoadBitmapA("Interface\\newui_SW_MiniMap_Bt_clearness.jpg", 31617, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Custom\\Maps\\mini_map_ui_blacksmith.tga", 31466, 0x2601, 0x2900, 1, 0); //-- Dungeon
	pLoadImage("Custom\\Maps\\mini_map_ui_Potion.tga", 31467, 0x2601, 0x2900, 1, 0); //-- Dungeon
	pLoadImage("Custom\\Maps\\mini_map_ui_baul.tga", 31468, 0x2601, 0x2900, 1, 0); //-- Dungeon
	pLoadImage("Custom\\Maps\\mini_map_ui_Que.tga", 31469, 0x2601, 0x2900, 1, 0); //-- Dungeon
	//Radar
//	pLoadImage("Custom\\Maps\\edBtUcx.tga", 31463, 0x2601, 0x2900, 1, 0);
//	pLoadImage("Custom\\Maps\\edBtUcx_1.tga", 31464, 0x2601, 0x2900, 1, 0);
//	pLoadImage("Custom\\Maps\\YYB6BUk.tga", 31465, 0x2601, 0x2900, 1, 0);
//	pLoadImage("Custom\\Maps\\mini_map_ui_monsterred.tga", 31471, 0x2601, 0x2900, 1, 0);
//	pLoadImage("Custom\\Maps\\mini_map_ui_monsterblue.tga", 31472, 0x2601, 0x2900, 1, 0);

	pLoadImage("Custom\\Maps\\edBtUcx.tga", 31463, 0x2601, 0x2900, 1, 0); //-- Dungeon
	pLoadImage("Custom\\Maps\\time700.tga", 31458, 0x2601, 0x2900, 1, 0); //-- Dungeon
	pLoadImage("Custom\\Maps\\edBtUcx_2.tga", 31464, 0x2601, 0x2900, 1, 0); //-- Dungeon
	pLoadImage("Custom\\Maps\\edBtUcx_1.tga", 31459, 0x2601, 0x2900, 1, 0); //-- Dungeon
	pLoadImage("Custom\\Maps\\YYB6BUk.tga", 31465, 0x2601, 0x2900, 1, 0); //-- Dungeon
	pLoadImage("Custom\\Maps\\mini_map_ui_blacksmith.tga", 31466, 0x2601, 0x2900, 1, 0); //-- Dungeon
	pLoadImage("Custom\\Maps\\mini_map_ui_Potion.tga", 31467, 0x2601, 0x2900, 1, 0); //-- Dungeon
	pLoadImage("Custom\\Maps\\mini_map_ui_baul.tga", 31468, 0x2601, 0x2900, 1, 0); //-- Dungeon
	pLoadImage("Custom\\Maps\\mini_map_ui_Que.tga", 31469, 0x2601, 0x2900, 1, 0); //-- Dungeon
	pLoadImage("Custom\\Maps\\mini_map_ui_monsterred.tga", 31471, 0x2601, 0x2900, 1, 0); //-- Dungeon Red
	pLoadImage("Custom\\Maps\\mini_map_ui_monsterblue.tga", 31472, 0x2601, 0x2900, 1, 0); //-- Dungeon Blue
	pLoadImage("Custom\\Maps\\mini_map_ui_monstergold.tga", 31473, 0x2601, 0x2900, 1, 0); //-- Dungeon Gold

	LoadBitmapA("Custom\\Maps\\map_radar.tga", 61519, 0x2601, 0x2901, 1, 0); //esquina abajo derecha
	LoadBitmapA("Custom\\Maps\\CRadar.tga", 91520, 0x2601, 0x2901, 1, 0); //esquina abajo derecha
	LoadBitmapA("Custom\\Interface\\info_block.tga", 61521, GL_LINEAR, GL_CLAMP, 1, 0);
	LoadBitmapA("Custom\\Interface\\Point.jpg", 91461, 0x2600, 0x2900, 1, 0);

	pLoadImage("Interface\\mini_map_ui_party.tga", 61520, 0x2601, 0x2901, 1, 0); //esquina abajo derecha

	switch(gProtect.m_MainInfo.CustomInterfaceType) 
	{
	case 0:
		LoadBitmapA("Interface\\GFx\\InventoryFrame_RuudShop.tga", 61560, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\Menu_RuudShopFrame.tga", 61561, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\Menu_Button03.tga", 61562, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\newSytemButton.tga", 61542, GL_LINEAR, GL_CLAMP, 1, 0);
		break;
	case 1:
	case 2:
		//--
		LoadBitmapA("Custom\\InterfaceS2\\Item_Back01.tga", 61522, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\none.tga", 51522, GL_LINEAR, GL_CLAMP, 1, 0);
		//--
		LoadBitmapA("Custom\\InterfaceS2\\DragonRight.tga", 2336, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\InterfaceS2\\DragonLeft.tga", 2337, GL_LINEAR, GL_CLAMP, 1, 0);
		//--
		if(gProtect.m_MainInfo.CustomInterfaceType == 1)
		{
			LoadBitmapA("Custom\\InterfaceS2\\Menu_left97.jpg", 31292, GL_LINEAR, GL_CLAMP, 1, 0); //replace
			LoadBitmapA("Custom\\Interface\\none.tga", 31300, GL_LINEAR, GL_CLAMP, 1, 0);
		}else
		{
			LoadBitmapA("Custom\\InterfaceS2\\Menu_left.jpg", 31292, GL_LINEAR, GL_CLAMP, 1, 0); //replace
			LoadBitmapA("Custom\\InterfaceS2\\Menu_SD.jpg", 31300, GL_LINEAR, GL_CLAMP, 1, 0);
		}
		
		LoadBitmapA("Custom\\InterfaceS2\\Menu_right.jpg", 31294, GL_LINEAR, GL_CLAMP, 1, 0); //replace
		LoadBitmapA("Custom\\InterfaceS2\\Menu_middle.jpg", 31293, GL_LINEAR, GL_CLAMP, 1, 0); //replace
		//--
		LoadBitmapA("Custom\\InterfaceS2\\Menu_Red.jpg", 0x7A42, GL_LINEAR, GL_CLAMP, 1, 0);//replace
		LoadBitmapA("Custom\\InterfaceS2\\Menu_Green.jpg", 0x7A41, GL_LINEAR, GL_CLAMP, 1, 0);//replace
		LoadBitmapA("Custom\\InterfaceS2\\Menu_Blue.jpg", 0x7A40, GL_LINEAR, GL_CLAMP, 1, 0);//replace
		LoadBitmapA("Custom\\InterfaceS2\\Menu_AG.jpg", 31299, GL_LINEAR, GL_CLAMP, 1, 0);
		//--
		LoadBitmapA("Custom\\InterfaceS2\\Boton\\Menu_fastmenu.jpg", iNewFastMenu, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\none.tga", 31295, GL_LINEAR, GL_CLAMP, 1, 0); //replace
		LoadBitmapA("Custom\\InterfaceS2\\Boton\\Menu_Inventory.jpg", iNewInventory, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\InterfaceS2\\Boton\\Menu_Character.jpg", iNewCharacter, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\InterfaceS2\\Boton\\Menu_Party.jpg", iNewParty, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\InterfaceS2\\Boton\\Menu_friend.jpg", iNewWinpush, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\InterfaceS2\\Boton\\Menu_guild.jpg", iNewGuild, GL_LINEAR, GL_CLAMP, 1, 0);
		//--
		LoadBitmapA("Custom\\InterfaceS2\\skillboxR.jpg", 0x700003, 0x2601, 0x2901, 1, 0);
		LoadBitmapA("Custom\\InterfaceS2\\newui_skill.jpg", 31308, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\InterfaceS2\\newui_skill2.jpg", 31309, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\InterfaceS2\\newui_skill3.jpg", 31311, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\InterfaceS2\\newui_command.jpg", 31310, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\InterfaceS2\\newui_non_skill.jpg", 31314, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\InterfaceS2\\newui_non_skill2.jpg", 31315, GL_LINEAR, GL_CLAMP, 1, 0); 
		LoadBitmapA("Custom\\InterfaceS2\\newui_non_skill3.jpg", 31317, GL_LINEAR, GL_CLAMP, 1, 0); 
		//--
		LoadBitmapA("Custom\\InterfaceS2\\newui_skillbox.jpg", 31312, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\InterfaceS2\\newui_skillbox2.jpg", 31313, GL_LINEAR, GL_CLAMP, 1, 0);
		//--
		//Interface Character
		LoadBitmapA("Custom\\InterfaceS2\\Menu\\Stats.jpg", 31352, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\InterfaceS2\\Menu\\StatsDL.jpg", 51291, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\InterfaceS2\\Menu\\Stats2.jpg", 51292, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\InterfaceS2\\Menu\\Level_box.jpg", 35353, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\InterfaceS2\\Menu\\Level_button.jpg", 51290, GL_LINEAR, GL_CLAMP, 1, 0);
		//-- chat
		LoadBitmapA("Custom\\InterfaceS2\\chat\\nis_vframe.jpg", 51551, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\InterfaceS2\\chat\\nis_rsframe.tga", 51552, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\InterfaceS2\\chat\\nis_rsframe_up.jpg", 51553, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\InterfaceS2\\chat\\nis_rsframe_m.jpg", 51554, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\InterfaceS2\\chat\\nis_rsframe_down.jpg", 51555, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\InterfaceS2\\chat\\nis_hframe.jpg", 31275, 9729, 10496, 1, 0);
		LoadBitmapA("Custom\\InterfaceS2\\Chat\\dialogue1.tga", 51530, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\InterfaceS2\\Chat\\dialogue2.tga", 51531, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\InterfaceS2\\Chat\\dialogue2_1.jpg", 51532, GL_LINEAR, GL_CLAMP, 1, 0);

		LoadBitmapA("Interface\\GFx\\InventoryFrame_RuudShop.tga", 61560, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\Menu_RuudShopFrame.tga", 61561, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\Menu_Button03.tga", 61562, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\newSytemButton.tga", 61542, GL_LINEAR, GL_CLAMP, 1, 0);
		break;
	case 3:

		LoadBitmapA("Interface\\GFx\\Buttom_empty_small.tga", 61525, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\InventoryFrame_I1.tga", 61522, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\InventoryFrame_I2.tga", 61523, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\InventoryFrame_I3.tga", 61524, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\Frame_I3.tga", 61526, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\StoreFrame_I1.tga", 615270, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\Item_Back02.tga", 615260, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\InventoryFrame_I4.tga", 61527, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\Draw_money.tga", 61528, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\button_close.tga", 61529, GL_LINEAR, GL_CLAMP, 1, 0);
		//--
		LoadBitmapA("Interface\\GFx\\ex700\\CharacterInfoFrame_I1.tga", 61532, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\newui_chainfo_btn_level.tga", 61533, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\ButtonCharacterInfo.tga", 61535, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\ExtensionBagFrame_I1.tga", 61536, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\ExtensionBagFrame_I2.tga", 61537, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\CharacterInfoFrame_I2.tga", 61538, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\BaulFrame_I1.tga", 61539, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\BaulFrame_I2.tga", 61540, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\ShopFrame_I1.tga", 61541, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\newSytemButton.tga", 61542, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\ShopFrame_I2.tga", 61555, GL_LINEAR, GL_CLAMP, 1, 0);

		LoadBitmapA("Interface\\GFx\\ex700\\CombinationFrame_I1.tga", 61543, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\PrivateStoreFrame_I3.tga", 61544, GL_LINEAR, GL_CLAMP, 1, 0);
		//--
		LoadBitmapA("Interface\\GFx\\ex700\\Main_IE.tga", 31293, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\Main_IE_Exp.tga", 59000, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\Main_I1.tga", 31296, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\Main_I4.jpg", 31300, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\Main_I5.jpg", 31299, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\newui_skillbox2.tga", 31313, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\newui_skillbox.tga", 31312, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\Main_Skillbox.tga", 51500, GL_LINEAR, GL_CLAMP, 1, 0);

		LoadBitmapA("Interface\\GFx\\ex700\\guege_mp.tga", 31296, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\guege_mp_1.tga", 51501, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\guege_hp_green.tga", 31297, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\guege_hp.tga", 31298, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\guege_hp_1.tga", 51502, GL_LINEAR, GL_CLAMP, 1, 0);
		goto LOAD_TEXTURE;
	case 4:

		LoadBitmapA("Interface\\GFx\\Buttom_empty_small.tga", 61525, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\InventoryFrame_I1.tga", 61522, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\InventoryFrame_I2.tga", 61523, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\InventoryFrame_I3.tga", 61524, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\Frame_I3.tga", 61526, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\StoreFrame_I1.tga", 615270, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\Item_Back02.tga", 615260, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\InventoryFrame_I4.tga", 61527, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\Draw_money.tga", 61528, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\button_close.tga", 61529, GL_LINEAR, GL_CLAMP, 1, 0);
		//--
		LoadBitmapA("Interface\\GFx\\ex700\\CharacterInfoFrame_I1.tga", 61532, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\newui_chainfo_btn_level.tga", 61533, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\ButtonCharacterInfo.tga", 61535, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\ExtensionBagFrame_I1.tga", 61536, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\ExtensionBagFrame_I2.tga", 61537, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\CharacterInfoFrame_I2.tga", 61538, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\BaulFrame_I1.tga", 61539, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\BaulFrame_I2.tga", 61540, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\ShopFrame_I1.tga", 61541, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\newSytemButton.tga", 61542, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\ShopFrame_I2.tga", 61555, GL_LINEAR, GL_CLAMP, 1, 0);

		LoadBitmapA("Interface\\GFx\\ex700\\CombinationFrame_I1.tga", 61543, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\PrivateStoreFrame_I3.tga", 61544, GL_LINEAR, GL_CLAMP, 1, 0);

		LoadBitmapA("Interface\\GFx\\Legends\\Main_IE.tga", 31293, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\Legends\\Main_I3.tga", 31298, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\Legends\\guege_mp.tga", 31296, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\Legends\\guege_mp_1.tga", 51501, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\Legends\\guege_hp_green.tga", 31297, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\Legends\\guege_hp.tga", 31298, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\Legends\\guege_hp_1.tga", 51502, GL_LINEAR, GL_CLAMP, 1, 0);

		LoadBitmapA("Interface\\GFx\\Legends\\Main_I5.jpg", 31299, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\Legends\\Main_I4.jpg", 31300, GL_LINEAR, GL_CLAMP, 1, 0);
		//--
		LoadBitmapA("Interface\\GFx\\Legends\\newui_skillbox2.tga", 31313, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\Legends\\newui_skillbox.tga", 31312, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\Legends\\Main_Skillbox.tga", 51500, GL_LINEAR, GL_CLAMP, 1, 0);
		goto LOAD_TEXTURE;
LOAD_TEXTURE:
		LoadBitmapA("Interface\\GFx\\chat_bg01.tga", 61550, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\chat_bg02.tga", 61551, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\chat_bg03.tga", 61534, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\Chat_I5.tga", 61548, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\newui_chat_back.tga", 61549, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\Main_IE_Buttons.tga", 0x901, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\skill_render.tga", 61546, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\item_pbtnbg.tga", 61547, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\ex700\\winPet_I1.tga", 61545, GL_LINEAR, GL_CLAMP, 1, 0);
		//-- Folder MacroUI
		LoadBitmapA("Interface\\GFx\\MacroUI\\MacroUI_Main.tga", 51550, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\MacroUI\\MacroUI_BSetup.tga", 51546, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\MacroUI\\MacroUI_BStart.tga", 51547, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\MacroUI\\MacroUI_Stop.tga", 51548, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\MacroUI\\MacroUI_Bar.jpg", 51549, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\MacroUI\\MacroUI_Menu.tga", 51553, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\MacroUI\\MacroUI_BCamera.tga", 51554, GL_LINEAR, GL_CLAMP, 1, 0);
//-- Folder Inteface
		//-- Botones del Main
		LoadBitmapA("Custom\\Interface\\none.tga", 31303, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\none.tga", 31304, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\none.tga", 31305, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\none.tga", 31306, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\none.tga", 31307, GL_LINEAR, GL_CLAMP, 1, 0);
		//--
		LoadBitmapA("Custom\\Interface\\none.tga", 51522, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\none.tga", 31294, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\none.tga", 31295, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Custom\\Interface\\none.tga", 31292, GL_LINEAR, GL_CLAMP, 1, 0);
		//-- Folder GFx
		LoadBitmapA("Interface\\GFx\\newui_number1.tga", 6829, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\InventoryFrame_RuudShop.tga", 61560, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\Menu_RuudShopFrame.tga", 61561, GL_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("Interface\\GFx\\Menu_Button03.tga", 61562, GL_LINEAR, GL_CLAMP, 1, 0);

		LoadBitmapA("Interface\\GFx\\Party\\Ex700\\PartyBar.tga", 81525, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Interface\\GFx\\Party\\Ex700\\newui_Party_Back.tga", 81520, 0x2601, 0x2901, 1, 0);
		pLoadImage("Interface\\GFx\\Party\\Ex700\\newui_Party_flag.tga", 81521, 0x2601, 0x2901, 1, 0);
		pLoadImage("Interface\\GFx\\Party\\Ex700\\newui_Party_HpBar.jpg", 81522, 0x2601, 0x2901, 1, 0);
		pLoadImage("Interface\\GFx\\Party\\Ex700\\newui_Party_ManaBar.jpg", 81523, 0x2601, 0x2901, 1, 0);
		pLoadImage("Interface\\GFx\\Party\\Ex700\\newui_Party_X.tga", 81524, 0x2601, 0x2901, 1, 0);

		break;
	}
	pLoadImage("Custom\\Interface\\TimeBar.tga", 0x787F, 0x2601, 0x2901, 1, 0);

	//partysearch
	pLoadImage("Custom\\Interface\\PartySearch_Title.tga", 92400, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Interface\\Party_info_block.tga", 92401, 0x2601, 0x2900, 1, 0);
	//--
	pLoadImage("Custom\\vip\\viplvl1.tga", 0x9960, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Custom\\vip\\viplvl2.tga", 0x9961, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Custom\\vip\\viplvl3.tga", 0x9962, GL_LINEAR, GL_CLAMP, 1, 0);

	pLoadImage("Custom\\interface\\itembackpanel.tga", 0x9326, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\interface\\topmenutabbt1.tga", 0x9327, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\interface\\ui_dialog_d.tga", 0x9328, 0x2601, 0x2900, 1, 0);

	if(gProtect.m_MainInfo.DisableEffectRemake == 0)
	{
		pLoadImage("Effect\\flare01.jpg", 52002, GL_LINEAR, GL_REPEAT, 1, 0);
		pLoadImage("Effect\\flareRed.jpg", 52230, GL_LINEAR, GL_REPEAT, 1, 0);
		pLoadImage("Effect\\JointLaser01.jpg", 52224, GL_LINEAR, GL_REPEAT, 1, 0);
		pLoadImage("Effect\\hikorora.jpg", 52379, GL_LINEAR, GL_REPEAT, 1, 0);
		pLoadImage("Effect\\flareBlue.jpg", 52229, GL_LINEAR, GL_REPEAT, 1, 0);
		pLoadImage("Effect\\bostar3_R.jpg", 32614, GL_LINEAR, GL_REPEAT, 1, 0);
		pLoadImage("Effect\\line_of_big_R.jpg", 32772, GL_LINEAR, GL_REPEAT, 1, 0);
		pLoadImage("Effect\\flare01.jpg", 42134, GL_LINEAR, GL_REPEAT, 1, 0);
	}
	//--
	if(gProtect.m_MainInfo.DisableCustomCloack == 0)
	{
		gCloak.LoadTexture();
	}

#if (ARCHIVEMENT == 1)
	gAchievements.LoadImages();
#endif

	g_ExWinQuestSystem.ImageLoad();
	//--
	pLoadSomeForm();
}

void Interface::BindObject(short MonsterID, DWORD ModelID, float Width, float Height, float X, float Y)
{
	this->Data[MonsterID].EventTick	= 0;
	this->Data[MonsterID].OnClick	= false;
	this->Data[MonsterID].OnShow	= false;
	this->Data[MonsterID].ModelID	= ModelID;
	this->Data[MonsterID].Width		= Width;
	this->Data[MonsterID].Height	= Height;
	this->Data[MonsterID].X			= X;
	this->Data[MonsterID].Y			= Y;
	this->Data[MonsterID].MaxX		= X + Width;
	this->Data[MonsterID].MaxY		= Y + Height;
	this->Data[MonsterID].Attribute	= 0;
}

void Interface::DrawText(DWORD Color, int PosX, int PosY, int Width, int Align, LPCSTR Text, ...) // OK
{
	char Buff[2048];
	const int BuffLen = sizeof(Buff) - 1;
	ZeroMemory(Buff, BuffLen);

	va_list args;
	va_start(args, Text);
	vsprintf_s(Buff, BuffLen, Text, args);
	va_end(args);

	char * Line = strtok(Buff, "\n");

	while (Line != nullptr)
	{
		DrawInterfaceText(Line, PosX, PosY, Width, 0, Color, 0, Align);
		PosY += 10;
		Line = strtok(NULL, "\n");
	}
}

void Interface::DrawMessageBox(LPCSTR Text, ...)
{
	char Buff[2048];
	int BuffLen = sizeof(Buff);
	ZeroMemory(Buff, BuffLen);
	// ----
	va_list args;
	va_start(args, Text);
	int Len = vsprintf_s(Buff, BuffLen, Text, args);
	va_end(args);

	CharTest v15;

	LPCSTR pText = Buff;
	sub_409A50_addr(&v15, (int)pText);
	pOpenInfoBox1(&v15, -1);
	sub_409AD0_Addr((LPVOID)&v15);
}

void Interface::TextDrawx(int PosX, int PosY, int Width, int Arg5, int Color, int Arg7, int Align, HGDIOBJ Font, LPCTSTR Format, ...)
{
	char TextBuff[1024] = { 0 };
	va_list va;
	va_start(va, Format);
	vsprintf_s(TextBuff, Format, va);
	va_end(va);

	int v13; // ST1C_4@1
	int v15; // ST20_4@1
	pSetFont(pTextThis(), (int)Font);
	v13 = sub_41FFE0_Addr(pTextThis());
	v15 = sub_420010_Addr(pTextThis());
	SetTextColorByHDC(pTextThis(), Color);
	sub_4200F0_Addr(pTextThis(), Arg7);
	pSetBkColor(pTextThis(), 255, 255, 255, 0);
	pDrawText(pTextThis(), PosX, PosY, TextBuff, Width, Arg5, (int*)Align, 0);
	SetTextColorByHDC(pTextThis(), v13);
	sub_4200F0_Addr(pTextThis(), v15);
}

void Interface::DrawGUI(short ObjectID, float PosX, float PosY)
{
	if( this->Data[ObjectID].X == -1 || this->Data[ObjectID].Y == -1 )
	{
		this->Data[ObjectID].X		= PosX;
		this->Data[ObjectID].Y		= PosY;
		this->Data[ObjectID].MaxX	= PosX + this->Data[ObjectID].Width;
		this->Data[ObjectID].MaxY	= PosY + this->Data[ObjectID].Height;
	}

	pDrawGUI(this->Data[ObjectID].ModelID, PosX, PosY,this->Data[ObjectID].Width, this->Data[ObjectID].Height);
}

void Interface::DrawGUI2(short ObjectID, float PosX, float PosY)
{
	this->Data[ObjectID].X		= PosX;
	this->Data[ObjectID].Y		= PosY;
	this->Data[ObjectID].MaxX	= PosX + this->Data[ObjectID].Width;
	this->Data[ObjectID].MaxY	= PosY + this->Data[ObjectID].Height;

	pDrawGUI(this->Data[ObjectID].ModelID, PosX, PosY,this->Data[ObjectID].Width, this->Data[ObjectID].Height);
}

void Interface::DrawGUI3(short ObjectID, float PosX, float PosY, float ScaleX, float ScaleY)
{
	this->Data[ObjectID].X		= PosX;
	this->Data[ObjectID].Y		= PosY;
	this->Data[ObjectID].MaxX	= PosX + this->Data[ObjectID].Width;
	this->Data[ObjectID].MaxY	= PosY + this->Data[ObjectID].Height;

	pDrawImage(this->Data[ObjectID].ModelID, PosX, PosY,this->Data[ObjectID].Width, this->Data[ObjectID].Height,0,0,ScaleX,ScaleY,1,1,0);
}

void Interface::DrawIMG(short ObjectID, float PosX, float PosY, float ScaleX, float ScaleY)
{
	if( this->Data[ObjectID].X == -1 || this->Data[ObjectID].Y == -1 )
	{
		this->Data[ObjectID].X		= PosX;
		this->Data[ObjectID].Y		= PosY;
		this->Data[ObjectID].MaxX	= PosX + this->Data[ObjectID].Width;
		this->Data[ObjectID].MaxY	= PosY + this->Data[ObjectID].Height;
	}

	pDrawImage(this->Data[ObjectID].ModelID, PosX, PosY,this->Data[ObjectID].Width, this->Data[ObjectID].Height,0,0,ScaleX,ScaleY,1,1,0);
}

void Interface::DrawWindow(int ObjMain, int ObjTitle, int ObjFrame, int ObjFooter, int Repeat, float X, float Y, char* Text)
{
	float StartY = Y;
	float StartX = X;

	gInterface.DrawGUI(ObjMain, StartX, StartY + 2);
	gInterface.DrawGUI(ObjTitle, StartX, StartY);
	StartY = gInterface.DrawRepeatGUI(ObjFrame, StartX, StartY + 67.0, Repeat);
	gInterface.DrawGUI(ObjFooter, StartX, StartY);

	gInterface.DrawFormat(eGold, StartX + 10, Y + 10, 210, 3, Text);
}

bool Interface::ButtonEx(DWORD Event, int ButtonID, bool Type)
{
	if (!this->IsWorkZone(ButtonID))
	{
		return false;
	}

	if (Type == true)
	{
		if (!this->Data[ButtonID].Attribute)
		{
			return false;
		}
	}

	// ----
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->Data[ButtonID].EventTick);
	// ----

	if (Event == WM_LBUTTONDOWN  && this->Data[ButtonID].OnClick == false)
	{
		this->Data[ButtonID].OnClick = true;
		//return false;
	}

	if (Event == WM_LBUTTONUP && this->Data[ButtonID].OnClick == true)
	{
		this->Data[ButtonID].OnClick = false;
		return true;
	}
	// ----
	if (Delay < 500)
	{
		return false;
	}
	// ----
	this->Data[ButtonID].OnClick = false;
	// ----
	this->Data[ButtonID].EventTick = GetTickCount();
	// ----
	return false;
}

void Interface::ResetDrawIMG(short ObjectID)
{
	if( this->Data[ObjectID].X != -1 || this->Data[ObjectID].Y != -1 )
	{
		this->Data[ObjectID].X		= -1;
		this->Data[ObjectID].Y		= -1;
		this->Data[ObjectID].MaxX	= -1;
		this->Data[ObjectID].MaxY	= -1;
	}
}

bool Interface::IsWorkZone(float X, float Y, float MaxX, float MaxY, bool a5)
{
	if (a5) {
		if ((pCursorX < X || pCursorX > X + MaxX) || (pCursorY < Y || pCursorY > Y + MaxY))
			return false;
		return true;
	}
	if ((pCursorX < X || pCursorX > MaxX) || (pCursorY < Y || pCursorY > MaxY))
		return false;
	return true;
}

bool Interface::CheckWindowEx2(int WindowID)
{
	return this->Data[WindowID].OnShow;
}

void Interface::OpenWindowEx(int WindowID)
{
	Data[WindowID].Open();
}

void Interface::CloseWindowEx(int WindowID)
{
	Data[WindowID].Close();
}

void Interface::TextDraw(int PosX, int PosY, int Width, int Arg5, int Color, int Arg7, int Align, HGDIOBJ Font, LPCTSTR Format, ...)
{
	char TextBuff[1024] = { 0 };
	va_list va;
	va_start(va, Format);
	vsprintf_s(TextBuff, Format, va);
	va_end(va);

	int v13; // ST1C_4@1
	int v15; // ST20_4@1
	pSetFont(pTextThis(), (int)Font);
	v13 = sub_41FFE0_Addr(pTextThis());
	v15 = sub_420010_Addr(pTextThis());
	SetTextColorByHDC(pTextThis(), Color);
	sub_4200F0_Addr(pTextThis(), Arg7);
	pSetBkColor(pTextThis(), 255, 255, 255, 0);
	pDrawText(pTextThis(), PosX, PosY, TextBuff, Width, Arg5, (int*)Align, 0);
	SetTextColorByHDC(pTextThis(), v13);
	sub_4200F0_Addr(pTextThis(), v15);
}

void Interface::MiniButtonDraw(int BtnID, float X, float Y, bool isHover, char* Text)
{

	if (isHover)
	{
		this->DrawButtonRender(BtnID, X, Y, 0, 29);
	}
	else
	{
		this->DrawButtonRender(BtnID, X, Y, 0, 0);
	}
	this->DrawFormat(eWhite, X + 7, Y + 9, 50, 3, Text);
}


void Interface::DrawCheckLineEx(bool isChecked, int PointID, int CheckID, int LineID, float X, float Y, DWORD Color, char* Text)
{
	this->DrawGUI2(PointID, X + 20, Y - 4); // Point
	this->DrawFormat(eWhite, X + 50, Y + 1, 200, 1, Text);

	if (isChecked)
	{
		this->DrawButtonRender(CheckID, X + 190, Y - 6, 0, 0);
	}
	else
	{
		this->DrawButtonRender(CheckID, X + 190, Y - 6, 0, 15);
	}

	this->DrawGUI2(LineID, X + 33, Y + 10);
}

bool checkBtn(int obj)
{
	if (gObjUser.m_CursorX < gInterface.Data[obj].X || gObjUser.m_CursorX > gInterface.Data[obj].MaxX ||
		gObjUser.m_CursorY < gInterface.Data[obj].Y || gObjUser.m_CursorY > gInterface.Data[obj].MaxY)
	{
		return false;
	}
	return true;
}

void Interface::PartUPandDNEx(int PointID, int UpID, int DownID, int LineID, float X, float Y, DWORD Color, int Value, char* Text)
{
	this->DrawGUI2(PointID, X + 20, Y - 4); // Point

	this->DrawFormat(eWhite, X + 50, Y + 1, 200, 1, Text);

	this->DrawButtonRender(DownID, X + 150, Y - 6, 0, 0); // 

	if (checkBtn(DownID))
	{
		if (this->Data[DownID].OnClick)
		{
			this->DrawButtonRender(DownID, X + 150, Y - 6, 0, 16);
		}
	}

	pSetBlend(true);
	this->DrawBarForm(X + 168, Y - 5, 19, 13, 0.0, 0.0, 0.0, 1.0);//ReqItems
	glColor3f(1, 1, 1);
	pSetBlend(false);
	char szText[10];
	sprintf(szText, "%d", Value);
	gInterface.TextDraw(X + 128, Y - 2, 100, 1, eWhite, 0, 3, pFontNormal, "%d", Value);

	this->DrawButtonRender(UpID, X + 190, Y - 6, 0, 0); // 

	if (checkBtn(UpID))
	{
		if (this->Data[UpID].OnClick)
		{
			this->DrawButtonRender(UpID, X + 190, Y - 6, 0, 16);
		}
	}

	this->DrawGUI(LineID, X + 33, Y + 10);
}

int Interface::DrawFormatx(DWORD Color, int PosX, int PosY, int Width, int Align, LPCSTR Text, ...)
{
	char Buff[2048] = { 0 };
	// ---
	int BuffLen = sizeof(Buff) - 1;
	// ---
	ZeroMemory(Buff, BuffLen);
	// ---
	va_list args;
	// ---
	va_start(args, Text);
	// ---
	int Len = vsprintf_s(Buff, BuffLen, Text, args);
	// ---
	va_end(args);
	// ---
	int LineCount = 0;
	// ---
	char * Line = strtok(Buff, "\n");
	// ---
	while (Line != NULL)
	{
		pDrawColorText(Line, PosX, PosY, Width, 5, Color, 9, Align);
		// ---
		PosY += 10;
		// ---
		Line = strtok(NULL, "\n");
	}
	// ---
	return PosY;
}

#define sub_630BC0   ((bool(*)()) 0x630BC0)

void ChangeSize(int a1, int a2)
{
	int v2; // esi@1
	DWORD v3; // edi@1
	int v4; // eax@2
	int v5; // eax@2
	DWORD *v6; // esi@2

	v2 = a2;
	v3 = a1;
	if (pMUIsLoaded)
	{
		pWinWidth = a1;
		pWinHeight = a2;
		pWinWidthReal = (double)(signed int)a1 / 640.0;
		pWinHeightReal = (double)a2 / 480.0;
		SetWindowPos(pGameWindow, 0, 0, 0, a1, a2 + 30, 0x116u);
		sub_630BC0();
	}
}

void Interface::Work()
{
	gObjUser.Refresh();

	if (gProtect.m_MainInfo.MiniMapType == 1)
	{
		gInterface.DrawMiniMap();
	}

	if (gProtect.m_MainInfo.MiniMapType == 2)
	{
//		gInterface.DrawRadar();
	}

	if (gProtect.m_MainInfo.MiniMapType == 2)
	{
		if (gObjUser.lpViewPlayer->WeaponFirstSlot >= ITEM2(4, 0) && gObjUser.lpViewPlayer->WeaponFirstSlot <= ITEM2(4, 255)
			|| gObjUser.lpViewPlayer->WeaponSecondSlot >= ITEM2(4, 0) && gObjUser.lpViewPlayer->WeaponSecondSlot <= ITEM2(4, 255))
		{
			if (MiniMap == 0)
			{
				gInterface.PetY = 38.0f;
			}
			else
			{
				gInterface.PetY = 13.0f;
			}

		}
		else
		{
			if (MiniMap == 0)
			{
				gInterface.PetY = 26.0f;
			}
			else
			{
				gInterface.PetY = 1.0f;
			}
		}
	}
	else
	{
		if (gObjUser.lpViewPlayer->WeaponFirstSlot >= ITEM2(4, 0) && gObjUser.lpViewPlayer->WeaponFirstSlot <= ITEM2(4, 255)
			|| gObjUser.lpViewPlayer->WeaponSecondSlot >= ITEM2(4, 0) && gObjUser.lpViewPlayer->WeaponSecondSlot <= ITEM2(4, 255))
		{
			gInterface.PetY = 38.0f;

		}
		else
		{
			gInterface.PetY = 26.0f;
		}
	}

	if(gProtect.m_MainInfo.CustomInterfaceType == 1 || gProtect.m_MainInfo.CustomInterfaceType == 2){

		if(gObjUser.lpViewPlayer->PetSlot!= -1)
		{
			gInterface.PetX = 61.0f;
		}else
		{
			gInterface.PetX = 0;
		}
		gInterface.DrawInterfaceDragonLS3();
		gInterface.DrawInterfaceDragonRS3();
	}

	gRanking.Draw();

	gInterface.DrawTimeUI();

	gCustomEventTime.DrawEventTimePanelWindow();
	
	ReconnectMainProc();

	gInterface.DrawVipWindow();

	gInterface.DrawMenu();

	gInterface.DrawMenuOpen();

	gInterface.DrawMenu2Open();

	gCustomCommandInfo.DrawCommandWindow();

	gInterface.DrawConfirmOpen();

#if (WARE==1)
	gwareinterface.DrawWarehouseWindow();
#endif
#if (JEWEL_BANK == 1)
	gJewelsBank.Draw();
#endif

	gInterface.DrawPartySearchWindow();
	gInterface.DrawPartySettingsWindow();

	gChangeClass.DrawChangeWindow();
#if (RESETCHANGE ==1)
	gResetChange.DrawResetChange();
#endif

	gInterface.DrawLuckyWheel();

	g_PersonalShopEx.Draw();

#if (ARCHIVEMENT == 1)
	gAchievements.Draw();
#endif

	gSmithItem.DrawSmithItem();

	g_ExWinQuestSystem.DrawMiniInfo();
	g_ExWinQuestSystem.Draw();
	g_ExWinQuestSystem.DrawOpenWQ();

	gGrandResetSystem.draw_grand_reset_system();
	gResetSystem.draw_reset_system();

	pDrawInterface();

	if (gProtect.m_MainInfo.CustomInterfaceType == 3 || gProtect.m_MainInfo.CustomInterfaceType == 4)
	{
		gInterface.DrawInterfaceCustom();
	}

	if(gProtect.m_MainInfo.CustomInterfaceType == 1 || gProtect.m_MainInfo.CustomInterfaceType == 2)
	{
		
		if(gProtect.m_MainInfo.CustomInterfaceType == 1)
		{
			gInterface.DrawInterface97Menu();
		}
		if(gProtect.m_MainInfo.CustomInterfaceType == 2)
		{
			gInterface.DrawInterfaceS2Menu();
		}

		gInterface.DrawCoord();
	}

	if( GetForegroundWindow() == pGameWindow )
	{
		if (GetKeyState(VK_SNAPSHOT) < 0) 
		{
			gInterface.DrawLogo(1); 
		}
		if (GetKeyState(VK_END) & 0x4000) 
		{
			if((GetTickCount()-gInterface.Data[eVip_MAIN].EventTick) > 300)
			{
				if (gInterface.CheckVipWindow())
				{
					gInterface.Data[eVip_MAIN].EventTick = GetTickCount();
					gInterface.CloseVipWindow();
				}
				else
				{
					gInterface.Data[eVip_MAIN].EventTick = GetTickCount();
					gInterface.CloseCustomWindow();
					gInterface.OpenVipWindow();
				}
			}
		}
		if (GetKeyState('H') & 0x4000) 
		{
			gCustomEventTime.OpenWindow();
		}
		if (GetKeyState('J') & 0x4000) 
		{
			if((GetTickCount()-gInterface.Data[eJEWELBANK_MAIN].EventTick) > 300)
			{
				if (gInterface.CheckWindow(ObjWindow::CreateGuild) || 
        			gInterface.CheckWindow(ObjWindow::ChatWindow) || 
        			gInterface.CheckWindow(ObjWindow::NPC_Dialog) ||
        			gInterface.CheckWindow(ObjWindow::CashShop))
    			{
    			    return;
    			}

				if (gJewelsBank.Active != true)
				{
					gJewelsBank.Active = true;
					gInterface.Data[eJEWELBANK_MAIN].OnShow = true;
					if (gProtect.m_MainInfo.CustomInterfaceType != 3 && gProtect.m_MainInfo.CustomInterfaceType != 4)
					{
						pSetCursorFocus = false;
					}
				}
				else
				{
					gJewelsBank.Active = false;
					gInterface.Data[eJEWELBANK_MAIN].OnShow = false;
					if (gProtect.m_MainInfo.CustomInterfaceType != 3 && gProtect.m_MainInfo.CustomInterfaceType != 4)
					{
						pSetCursorFocus = false;
					}
				}
				gInterface.Data[eJEWELBANK_MAIN].EventTick = GetTickCount();
			}
		}
//--------
/*		if (GetKeyState('Y') & 0x4000)
		{
			HKEY hKey;
			DWORD dwType, dwSize;
			DWORD buffer;
			LONG result;

			int width;
			int height;
			float rea1;
			unsigned long type = REG_DWORD, size = 1024;

			RegOpenKeyEx(HKEY_CURRENT_USER, "SOFTWARE\\Webzen\\Mu\\Config", 0, KEY_ALL_ACCESS, &hKey);
			DWORD value = 4;

			RegSetValueEx(hKey, TEXT("Resolution"), 0, REG_DWORD, (const BYTE*)&value, sizeof(value));

			RegCloseKey(hKey);

			result = RegOpenKeyEx(HKEY_CURRENT_USER, "SOFTWARE\\Webzen\\Mu\\Config", 0, KEY_READ, &hKey);
			RegQueryValueEx(hKey, "Resolution", NULL, &type, (LPBYTE)&buffer, &size);
			RegCloseKey(hKey);

			switch (buffer)
			{
			case 0:
				pWinWidth = 640;
				pWinHeight = 480;
				break;
			case 1:
				pWinWidth = 800;
				pWinHeight = 600;
				break;
			case 2:
				pWinWidth = 1024;
				pWinHeight = 768;
				break;
			case 3:
				pWinWidth = 1280;
				pWinHeight = 1024;
				break;
			case 4:
				pWinWidth = 1360;
				pWinHeight = 768;
				break;
			case 5:
				pWinWidth = 1440;
				pWinHeight = 900;
				break;
			default:
				break;
			}

			ChangeSize(pWinWidth, pWinHeight);
			pWinFontHeight = 10;
		}*/
//---------
		if (GetKeyState('O') & 0x4000) 
		{
			gInterface.OpenConfig(0);
		}
		if (GetKeyState(VK_UP) & 0x4000) 
		{
			gInterface.OpenConfig(1);
		}
		else if (GetKeyState(VK_DOWN) & 0x4000) 
		{
			gInterface.OpenConfig(1);
		}
		if (GetKeyState(VK_F7) & 0x4000)
		{
			g_ExWinQuestSystem.SwitchStatsWindowState();
		}
		if (GetKeyState(VK_F6) & 0x4000) 
		{
			gInterface.SwitchChatExpand();
		}
		if (GetKeyState(VK_F8) & 0x4000) 
		{
			if (Encoger == 1)
			{
				Encoger = 0;
				gInterface.DrawMessage(1, "[OFF]");
			}
			else
			{
				Encoger = 1;
				Encoger = 2;
				Encoger = 1;
				gInterface.DrawMessage(1, "[ON]");
			}
		}
		if (GetKeyState(VK_F10) & 0x4000) 
		{
			gInterface.SwitchCamera();
		}
		if (GetKeyState(VK_F11) & 0x4000) 
		{
			gInterface.CameraInit();
		}
		if (GetKeyState(VK_F12) & 0x4000) 
		{
			if( gTrayMode.TempWindowProc == NULL )
			{
				gTrayMode.TempWindowProc = SetWindowLong(pGameWindow, GWL_WNDPROC, (long)gController.Window);
			}
			// ----
			gTrayMode.SwitchState();
		}
		if (GetKeyState(VK_ESCAPE) < 0) 
		{
			if (gInterface.Data[eCommand_MAIN].OnShow == true)
			{
				gInterface.Data[eCommand_MAIN].OnShow = false;
				
	if(gProtect.m_MainInfo.CustomInterfaceType != 3 || gProtect.m_MainInfo.CustomInterfaceType != 4)
	{
		pSetCursorFocus = false;
	}
			}

			if (gInterface.Data[eRankPANEL_MAIN].OnShow == true)
			{
				gInterface.Data[eRankPANEL_MAIN].OnShow = false;
				
	if(gProtect.m_MainInfo.CustomInterfaceType != 3 || gProtect.m_MainInfo.CustomInterfaceType != 4)
	{
		pSetCursorFocus = false;
	}
			}

			if (gInterface.Data[eEventTimePANEL_MAIN].OnShow == true)
			{
				gInterface.Data[eEventTimePANEL_MAIN].OnShow = false;
				
	if(gProtect.m_MainInfo.CustomInterfaceType != 3 || gProtect.m_MainInfo.CustomInterfaceType != 4)
	{
		pSetCursorFocus = false;
	}
			}

			if (gJewelsBank.Active == true)
			{
				gJewelsBank.Active = false;
				gInterface.Data[eJEWELBANK_MAIN].OnShow = false;
				if (gProtect.m_MainInfo.CustomInterfaceType != 3 || gProtect.m_MainInfo.CustomInterfaceType != 4)
				{
					pSetCursorFocus = false;
				}
			}

			if (gInterface.CheckVipWindow())
			{
				gInterface.CloseVipWindow();
			}

			if (gInterface.CheckMenuWindow())
			{
				gInterface.CloseMenuWindow();
			}

			if (gRanking.Show == true)
			{
				gRanking.Show = false;
				pSetCursorFocus = false;
			}

#if (ARCHIVEMENT == 1)
			if (gInterface.Data[OBJECT_ACHIEVEMENTS_MAIN].OnShow == true)
			{
				gInterface.Data[OBJECT_ACHIEVEMENTS_MAIN].Close();
			}
#endif
		}
	}

	if (!pCheckWindow(pWindowThis(), 13))
	{
		jCRenderRuud.OpeningRuud = false;
	}

	if (gInterface.CheckWindow(ObjWindow::MuHelper) || gInterface.CheckWindow(ObjWindow::MuHelperSetting))
	{
		CloseHelper();
	}

	gInterface.DrawLogo(0);
}

void Interface::SwitchMiniMap()
{
	if((GetTickCount() - gInterface.Data[eNULL_MAP].EventTick) < 1000 ||this->CheckWindow(ChatWindow))
	{
		return;
	}

	gInterface.Data[eNULL_MAP].EventTick = GetTickCount();

	if (MiniMap != 0)
	{
		gInterface.DrawMessage(1, "MiniMap Window [OFF]");
		MiniMap = 0;
		WritePrivateProfileStringA("Graphics","MiniMap","0","./Settings.ini");
	}
	else 
	{
		gInterface.DrawMessage(1, "MiniMap Window [ON]");
		MiniMap = 1;
		WritePrivateProfileStringA("Graphics","MiniMap","1","./Settings.ini");
	}
}


void Interface::DrawTimeUI()
{

	if(TimerBar == 0 || (this->CheckWindow(ObjWindow::CashShop)|| this->CheckWindow(ObjWindow::FullMap) || this->CheckWindow(ObjWindow::ChatWindow) || this->CheckWindow(ObjWindow::SkillTree)
	|| this->CheckWindow(ObjWindow::MoveList) || pMapNumber == 34 || pMapNumber == 30 ))
	{
		return;
	}
	// -----
	this->DrawGUI(eTIME, this->Data[eTIME].X, this->Data[eTIME].Y);
	this->DrawGUI(eTIME, this->Data[eTIME].X, this->Data[eTIME].Y + 22);
	// -----
	time_t TimeServer, TimeLocal;
	struct tm * ServerT, *LocalT;
	time(&TimeServer);
	time(&TimeLocal);
	// ----
	ServerT = gmtime(&TimeServer);
	// ----
	char ServerTimeName[25] = "Server:";
	char ServerTime[30];

	sprintf(ServerTime, "%2d:%02d:%02d", (ServerT->tm_hour + GMT) % 24, ServerT->tm_min, ServerT->tm_sec);
	// -----
	LocalT = localtime(&TimeLocal);
	// -----
	char LocalTimeName[25] = "Local:";
	char LocalTime[30];
	sprintf(LocalTime, "%2d:%02d:%02d", LocalT->tm_hour, LocalT->tm_min, LocalT->tm_sec);
	// -----
	this->DrawFormat(eGold, 5, 391, 50, 1, ServerTimeName);
	this->DrawFormat(eWhite, 55, 391, 100, 1, ServerTime);
	// ----
	this->DrawFormat(eGold, 5, 413, 50, 1, LocalTimeName);
	this->DrawFormat(eWhite, 55, 413, 100, 1, LocalTime);
}

int Interface::DrawFormat(DWORD Color, int PosX, int PosY, int Width, int Align, LPCSTR Text, ...)
{
	char Buff[2048];
	int BuffLen	= sizeof(Buff)-1;
	ZeroMemory(Buff, BuffLen);
	
	va_list args;
	va_start(args, Text);
	int Len	= vsprintf_s(Buff, BuffLen, Text, args);
	va_end(args);
	
	int LineCount = 0;
	
	char * Line = strtok(Buff, "\n");
	
	while( Line != NULL )
	{
		pDrawColorText(Line, PosX, PosY, Width, 0, Color, 0, Align);
		PosY += 10;
		Line = strtok(NULL, "\n");
	}
	
	return PosY;
}

bool Interface::CheckWindow(int WindowID)
{
	return pCheckWindow(pWindowThis(), WindowID);
}
bool Interface::CheckWindowzx(int WindowID)
{
	return this->Data[WindowID].OnShow;
}
int Interface::CloseWindow(int WindowID)
{
	return pCloseWindow(pWindowThis(), WindowID);
}
int Interface::OpenWindow(int WindowID)
{
	return pOpenWindow(pWindowThis(), WindowID);
}

bool Interface::IsWorkZone2(float X, float Y, float MaxX, float MaxY)
{
	if ((gObjUser.m_CursorX < X || gObjUser.m_CursorX > MaxX) || (gObjUser.m_CursorY < Y || gObjUser.m_CursorY > MaxY))
	{
		return false;
	}
	// ----
	return true;
}


/*bool Interface::IsWorkZone(short ObjectID)
{
	if( (pCursorX < this->Data[ObjectID].X || pCursorX > this->Data[ObjectID].MaxX) || (pCursorY < this->Data[ObjectID].Y || pCursorY > this->Data[ObjectID].MaxY) )
		return false;

	return true;
}*/

bool Interface::IsWorkZone(short ObjectID)
{
	float PosX = this->Data[ObjectID].X;
	float MaxX = PosX + this->Data[ObjectID].Width;
	// ----
	if (ObjectID == eSAMPLEBUTTON || ObjectID == eMenu)
	{
		PosX = this->GetResizeX(ObjectID);
		MaxX = PosX + this->Data[ObjectID].Width;
	}
	// ----
	if ((pCursorX < this->Data[ObjectID].X || pCursorX > this->Data[ObjectID].MaxX) || (pCursorY < this->Data[ObjectID].Y || pCursorY > this->Data[ObjectID].MaxY))
	{
		return false;
	}
	// ----
	return true;
}

float Interface::GetResizeX(short ObjectID)
{
	if( pWinWidth == 800 )
	{
		return this->Data[ObjectID].X + 16.0;
	}
	else if( pWinWidth != 1024 )
	{
		return this->Data[ObjectID].X - 16.0;
	}
	
	return this->Data[ObjectID].X;
}

int Interface::DrawToolTip(int X, int Y, LPCSTR Text, ...)
{
	char Buff[2048];
	int BuffLen	= sizeof(Buff);
	ZeroMemory(Buff, BuffLen);
	
	va_list args;
	va_start(args, Text);
	int Len	= vsprintf_s(Buff, BuffLen, Text, args);
	va_end(args);
	
	return pDrawToolTip(X, Y, Buff);
}

int Interface::DrawMessage(int Mode, LPCSTR Text, ...)
{
	char Buff[2048];
	int BuffLen	= sizeof(Buff);
	ZeroMemory(Buff, BuffLen);
	// ----
	va_list args;
	va_start(args, Text);
	int Len	= vsprintf_s(Buff, BuffLen, Text, args);
	va_end(args);
	// ----
	return pDrawMessage(Buff, Mode);
}

void Interface::DrawVipWindow()
{

	if( !this->Data[eVip_MAIN].OnShow )
	{
		return;
	}

	if( gProtect.m_MainInfo.EnableVipShop != 1 )
	{
		this->CloseVipWindow();
		return;
	}

	if (this->CheckWindow(ObjWindow::MoveList) || this->CheckWindow(ObjWindow::CashShop) || this->CheckWindow(ObjWindow::SkillTree) || this->CheckWindow(ObjWindow::FullMap)
		||  (this->CheckWindow(Inventory) 
		&& this->CheckWindow(ExpandInventory) 
		&& this->CheckWindow(Store)) 
		||  (this->CheckWindow(Inventory) 
		&& this->CheckWindow(Warehouse) 
		&& this->CheckWindow(ExpandWarehouse)) )
	{
		CloseVipWindow();
		return;
	}

	// ----
	float MainWidth			= 230.0;
	float MainHeight		= 320.0;
	float StartBody			= ((MAX_WIN_HEIGHT - 51) / 2) - (MainHeight / 2);
	float StartY			= ((MAX_WIN_HEIGHT - 51) / 2) - (MainHeight / 2);
	float StartX			= (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float MainCenter		= StartX + (MainWidth / 3);
	float ButtonX			= MainCenter - (float)(29.0 / 2);
	// ----
	gCentral.PrintDropBox(StartX, StartY, MainWidth, MainHeight, 0, 0);
	// ----
	this->DrawFormat(eGold, (int)StartX + 10, (int)StartBody + 10, 210, 3, gCustomMessage.GetMessage(5));
	int LineY = this->DrawFormat(eWhite, (int)StartX + 30, (int)StartBody + 35, 210, 1, gCustomMessage.GetMessage(6), gObjUser.lpPlayer->Name);
	LineY = this->DrawFormat(eGold, (int)StartX + 30, (int)LineY, 210, 1, gCustomMessage.GetMessage(14));
	LineY = this->DrawFormat(eWhite, (int)StartX + 30, (int)LineY, 210, 1, gCustomMessage.GetMessage(7));
	LineY = this->DrawFormat(eWhite, (int)StartX + 30, (int)LineY, 210, 1, gCustomMessage.GetMessage(8));
	//--
	pDrawGUI(71520, StartX + (MainWidth / 2) - (200 / 2), StartBody + 85, 200, 1); //-- Divisor
	//--
	this->DrawFormat(eGold, (int)StartX + 30, (int)StartBody + 95 - 2, 210, 1, "Plan");
	this->DrawFormat(eGold, (int)StartX + 80, (int)StartBody + 95 - 2 , 210, 1, "Exp");
	this->DrawFormat(eGold, (int)StartX + 130, (int)StartBody + 95 - 2, 210, 1, "Drop");
	this->DrawFormat(eGold, (int)StartX + 170, (int)StartBody + 95 - 2, 210, 1, "Time");
	// ----

	if (gProtect.m_MainInfo.VipTypes < 1 || gProtect.m_MainInfo.VipTypes > 3)
	{
		gProtect.m_MainInfo.VipTypes = 3;
	}

	for( int i = 0; i < (int)gProtect.m_MainInfo.VipTypes; i++ )
	{
		this->DrawFormat(eWhite, (int)StartX + 30, (int)StartBody + 110 + (12 * i) - 5, 210, 1, gCustomBuyVip.m_CustomBuyVipInfo[i].VipName);
		// ----
		this->DrawFormat(eWhite, (int)StartX + 80, (int)StartBody + 110 + (12 * i) - 5, 210, 1, "+%d%%", gCustomBuyVip.m_CustomBuyVipInfo[i].Exp);
		// ----
		this->DrawFormat(eWhite, (int)StartX + 130, (int)StartBody + 110 + (12 * i) - 5, 210, 1, "+%d%%", gCustomBuyVip.m_CustomBuyVipInfo[i].Drop);
		// ----
		this->DrawFormat(eWhite, (int)StartX + 170, (int)StartBody + 110 + (12 * i) - 5, 210, 1, "%d day(s)", gCustomBuyVip.m_CustomBuyVipInfo[i].Days);

		pDrawGUI(0x7B5E, StartX + 30, StartBody + 110 + (12 * i) + 9 - 5, 82.0, 2.0);
		pDrawGUI(0x7B5E, StartX + 30 + 82, StartBody + 110 + (12 * i) + 9 - 5, 82.0, 2.0);
	}

	if (gProtect.m_MainInfo.VipTypes > 0)
	{
	// ---- bronze start 
	if (IsWorkZone(eVip_BRONZE))
	{
		if (this->Data[eVip_BRONZE].OnClick)
			this->DrawButton(eVip_BRONZE, StartX + 64, 220, 0, 58);
		else
			this->DrawButton(eVip_BRONZE, StartX + 64, 220, 0, 29);
		// ----
		this->DrawFormat(eGold, (int)StartX + 30, (int)StartBody + 142, 210, 1, gCustomMessage.GetMessage(10));
		this->DrawFormat(eGold, (int)StartX + 70, (int)StartBody + 142, 210, 1, gCustomMessage.GetMessage(11), gCustomBuyVip.m_CustomBuyVipInfo[0].Coin1);
		this->DrawFormat(eGold, (int)StartX + 120, (int)StartBody + 142, 210, 1, gCustomMessage.GetMessage(12), gCustomBuyVip.m_CustomBuyVipInfo[0].Coin2);
		this->DrawFormat(eGold, (int)StartX + 160, (int)StartBody + 142, 210, 1, gCustomMessage.GetMessage(13), gCustomBuyVip.m_CustomBuyVipInfo[0].Coin3);
	}
	else
		this->DrawButton(eVip_BRONZE, StartX + 64, 220, 0, 0);
	// ----
	this->DrawFormat(eWhite, (int)StartX + 90, 220 + 9, 160, 1, gCustomMessage.GetMessage(9),gCustomBuyVip.m_CustomBuyVipInfo[0].VipName);
	// ---- bronze end ------------------------------------
	}

	if (gProtect.m_MainInfo.VipTypes > 1)
	{
	// ---- Silver start ------------------------------------
	if (IsWorkZone(eVip_SILVER))
	{
		if (this->Data[eVip_SILVER].OnClick)
			this->DrawButton(eVip_SILVER, StartX + 64, 250, 0, 58);
		else
			this->DrawButton(eVip_SILVER, StartX + 64, 250, 0, 29);
		// ----
		this->DrawFormat(eGold, (int)StartX + 30, (int)StartBody + 142, 210, 1, gCustomMessage.GetMessage(10));
		this->DrawFormat(eGold, (int)StartX + 70, (int)StartBody + 142, 210, 1, gCustomMessage.GetMessage(11), gCustomBuyVip.m_CustomBuyVipInfo[1].Coin1);
		this->DrawFormat(eGold, (int)StartX + 120, (int)StartBody + 142, 210, 1, gCustomMessage.GetMessage(12), gCustomBuyVip.m_CustomBuyVipInfo[1].Coin2);
		this->DrawFormat(eGold, (int)StartX + 160, (int)StartBody + 142, 210, 1, gCustomMessage.GetMessage(13), gCustomBuyVip.m_CustomBuyVipInfo[1].Coin3);
	}
	else
		this->DrawButton(eVip_SILVER, StartX + 64, 250, 0, 0);

	this->DrawFormat(eWhite, (int)StartX + 90, 250 + 9, 160, 1, gCustomMessage.GetMessage(9),gCustomBuyVip.m_CustomBuyVipInfo[1].VipName);
	// ---- silver end ------------------------------------
	}

	if (gProtect.m_MainInfo.VipTypes > 2)
	{
	// ---- gold start ------------------------------------
	if (IsWorkZone(eVip_GOLD))
	{
		if (this->Data[eVip_GOLD].OnClick)
			this->DrawButton(eVip_GOLD, StartX + 64, 280, 0, 58);
		else
			this->DrawButton(eVip_GOLD, StartX + 64, 280, 0, 29);
		// ----
		this->DrawFormat(eGold, (int)StartX + 30, (int)StartBody + 142, 210, 1, gCustomMessage.GetMessage(10));
		this->DrawFormat(eGold, (int)StartX + 70, (int)StartBody + 142, 210, 1, gCustomMessage.GetMessage(11), gCustomBuyVip.m_CustomBuyVipInfo[2].Coin1);
		this->DrawFormat(eGold, (int)StartX + 120, (int)StartBody + 142, 210, 1, gCustomMessage.GetMessage(12), gCustomBuyVip.m_CustomBuyVipInfo[2].Coin2);
		this->DrawFormat(eGold, (int)StartX + 160, (int)StartBody + 142, 210, 1, gCustomMessage.GetMessage(13), gCustomBuyVip.m_CustomBuyVipInfo[2].Coin3);
	}
	else
		this->DrawButton(eVip_GOLD, StartX + 64, 280, 0, 0);

	this->DrawFormat(eWhite, (int)StartX + 90, 280 + 9, 160, 1, gCustomMessage.GetMessage(9),gCustomBuyVip.m_CustomBuyVipInfo[2].VipName);
	// ---- gold end ------------------------------------
	}

	pDrawGUI(71520, StartX + (MainWidth / 2) - (200 / 2), 280 + 55, 200, 1); //-- Divisor
}


bool Interface::EventVipWindow_Close(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->Data[eVip_CLOSE].EventTick);
	// ----
	if (!this->Data[eVip_MAIN].OnShow || !IsWorkZone(eVip_CLOSE))
	{
		return false;
	}
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[eVip_CLOSE].OnClick = true;
		return true;
	}
	// ----
	this->Data[eVip_CLOSE].OnClick = false;
	// ----
	if (Delay < 500)
	{
		return false;
	}
	// ----
	this->Data[eVip_CLOSE].EventTick = GetTickCount();
	this->CloseVipWindow();
	// ----
	return false;
}
// ----------------------------------------------------------------------------------------------

bool Interface::EventVipWindow_Bronze(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->Data[eVip_BRONZE].EventTick);
	// ----
	if (!this->Data[eVip_MAIN].OnShow || !IsWorkZone(eVip_BRONZE))
	{
		return false;
	}
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[eVip_BRONZE].OnClick = true;
		return true;
	}
	// ----
	this->Data[eVip_BRONZE].OnClick = false;;
	// ----
	if (Delay < 500)
	{
		return false;
	}
	// ----
	this->Data[eVip_BRONZE].EventTick = GetTickCount();
	gCustomBuyVip.BuyStatus(1);
	this->CloseVipWindow();
	// ----
	return false;
}
// ----------------------------------------------------------------------------------------------

bool Interface::EventVipWindow_Silver(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->Data[eVip_SILVER].EventTick);
	// ----
	if (!this->Data[eVip_MAIN].OnShow || !IsWorkZone(eVip_SILVER))
	{
		return false;
	}
	if (gProtect.m_MainInfo.VipTypes < 2)
	{
		return false;
	}
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[eVip_SILVER].OnClick = true;
		return true;
	}
	// ----
	this->Data[eVip_SILVER].OnClick = false;;
	// ----
	if (Delay < 500)
	{
		return false;
	}
	// ----
	this->Data[eVip_SILVER].EventTick = GetTickCount();
	gCustomBuyVip.BuyStatus(2);
	this->CloseVipWindow();
	// ----
	return false;
}

// ----------------------------------------------------------------------------------------------
bool Interface::EventVipWindow_Gold(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->Data[eVip_GOLD].EventTick);
	// ----
	if (!this->Data[eVip_MAIN].OnShow || !IsWorkZone(eVip_GOLD))
	{
		return false;
	}
	if (gProtect.m_MainInfo.VipTypes < 3)
	{
		return false;
	}
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[eVip_GOLD].OnClick = true;
		return true;
	}
	// ----
	this->Data[eVip_GOLD].OnClick = false;;
	// ----
	if (Delay < 500)
	{
		return false;
	}
	// ----
	this->Data[eVip_GOLD].EventTick = GetTickCount();
	gCustomBuyVip.BuyStatus(3);
	this->CloseVipWindow();
	// ----
	return false;
}
// ----------------------------------------------------------------------------------------------

bool Interface::EventVipWindow_Main(DWORD Event)
{
	this->EventVipWindow_Close(Event);
	this->EventVipWindow_Bronze(Event);
	this->EventVipWindow_Silver(Event);
	this->EventVipWindow_Gold(Event);
	// ----
	return true;
}

float Interface::DrawRepeatGUI(short MonsterID, float X, float Y, int Count)
{
	float StartY = Y;
	// ----
	for( int i = 0; i < Count; i++ )
	{
		pDrawGUI(this->Data[MonsterID].ModelID, X, StartY,
			this->Data[MonsterID].Width, this->Data[MonsterID].Height);
		// ----
		StartY += this->Data[MonsterID].Height;
	}
	// ----
	return StartY;
}

float Interface::DrawRepeatGUIScale(short MonsterID, float X, float Y,float ScaleX, float ScaleY, int Count)
{
	float StartY = Y;
	// ----
	for( int i = 0; i < Count; i++ )
	{
		this->DrawIMG(this->Data[MonsterID].ModelID, X, StartY,ScaleX,ScaleY);
		// ----
		StartY += this->Data[MonsterID].Height;
	}
	// ----
	return StartY;
}

void Interface::DrawButton(short ObjectID, float PosX, float PosY, float ScaleX, float ScaleY)
{
	if( this->Data[ObjectID].X == -1 || this->Data[ObjectID].Y == -1 )
	{
		this->Data[ObjectID].X = PosX;
		this->Data[ObjectID].Y = PosY;
		this->Data[ObjectID].MaxX = PosX + this->Data[ObjectID].Width;
		this->Data[ObjectID].MaxY = PosY + this->Data[ObjectID].Height;
	}
	// ----
	pDrawButton(this->Data[ObjectID].ModelID, PosX, PosY,
		this->Data[ObjectID].Width, this->Data[ObjectID].Height, ScaleX, ScaleY);
}

void Interface::DrawButtonRender(short ObjectID, float PosX, float PosY, float ScaleX, float ScaleY)
{
	this->Data[ObjectID].X = PosX;
	this->Data[ObjectID].Y = PosY;
	this->Data[ObjectID].MaxX = PosX + this->Data[ObjectID].Width;
	this->Data[ObjectID].MaxY = PosY + this->Data[ObjectID].Height;
	// ----
	pDrawButton(this->Data[ObjectID].ModelID, PosX, PosY,
		this->Data[ObjectID].Width, this->Data[ObjectID].Height, ScaleX, ScaleY);
}


void Interface::DrawColoredButton(short ObjectID, float PosX, float PosY, float ScaleX, float ScaleY, DWORD Color)
{
	if (this->Data[ObjectID].X == -1 || this->Data[ObjectID].Y == -1)
	{
		this->Data[ObjectID].X = PosX;
		this->Data[ObjectID].Y = PosY;
		this->Data[ObjectID].MaxX = PosX + this->Data[ObjectID].Width;
		this->Data[ObjectID].MaxY = PosY + this->Data[ObjectID].Height;
	}
	// ----
	pDrawColorButton(this->Data[ObjectID].ModelID, PosX, PosY,
		this->Data[ObjectID].Width, this->Data[ObjectID].Height, ScaleX, ScaleY, Color);
}

void Interface::DrawColoredGUI(short ObjectID, float X, float Y, DWORD Color)
{
	if( this->Data[ObjectID].X == -1 || this->Data[ObjectID].Y == -1 )
	{
		this->Data[ObjectID].X		= X;
		this->Data[ObjectID].Y		= Y;
		this->Data[ObjectID].MaxX	= X + this->Data[ObjectID].Width;
		this->Data[ObjectID].MaxY	= Y + this->Data[ObjectID].Height;
	}
	// ----
	pDrawColorButton(this->Data[ObjectID].ModelID, X, Y, 
		this->Data[ObjectID].Width, this->Data[ObjectID].Height, 0, 0, Color);
}

void Interface::DrawLogo(bool active)
{
	if (gProtect.m_MainInfo.PrintLogo != 0)
	{

		if (active == 1)
		{
			this->Data[eLogo].EventTick = GetTickCount()+1500;
		}

		if (gInterface.Data[eLogo].EventTick > GetTickCount())
		{
			if (gProtect.m_MainInfo.PrintLogo == 1)
			{
				this->DrawGUI(eLogo, 10, 10);
			}

			if (gProtect.m_MainInfo.PrintLogo == 2)
			{
				this->DrawGUI(eLogo, MAX_WIN_WIDTH - 160, 10);

			}

			if (gProtect.m_MainInfo.PrintLogo == 3)
			{
				this->DrawGUI(eLogo, 10, MAX_WIN_HEIGHT - 144);
			}

			if (gProtect.m_MainInfo.PrintLogo == 4)
			{
				this->DrawGUI(eLogo, MAX_WIN_WIDTH - 160, MAX_WIN_HEIGHT - 144);
			}

			if (gProtect.m_MainInfo.PrintLogo == 5)
			{
				this->DrawGUI(eLogo, (MAX_WIN_WIDTH/2)-(150/2), (MAX_WIN_HEIGHT/2)-(114/2));
			}
		}
	}
}

void Interface::DrawMenu()
{
	if (gProtect.m_MainInfo.CustomMenuSwitch != 1)
	{
		return;
	}

	if (this->Data[eMenu].OnShow)
	{
		this->Data[eMenu].OnShow = false;
	}

	if (this->CheckWindow(ObjWindow::MoveList) || this->CheckWindow(ObjWindow::CashShop) || this->CheckWindow(ObjWindow::SkillTree) || this->CheckWindow(ObjWindow::FullMap)
		||  (this->CheckWindow(Inventory) 
		&& this->CheckWindow(ExpandInventory) 
		&& this->CheckWindow(Store))
		||  (this->CheckWindow(Inventory) 
		&& this->CheckWindow(ExpandInventory) 
		&& this->CheckWindow(Character))
		||  (this->CheckWindow(Inventory) 
		&& this->CheckWindow(Warehouse) 
		&& this->CheckWindow(ExpandWarehouse)) )
	{
		CloseMenuWindow();
		return;
	}
	
	this->Data[eMenu].OnShow = true;

	if (gProtect.m_MainInfo.CustomInterfaceType == 3 || gProtect.m_MainInfo.CustomInterfaceType == 4)
	{
		return;
	}
	else
	{
		if (gProtect.m_MainInfo.CustomMenuType == 1)
		{
			this->DrawGUI(eMenu, 3, 55);
		}
	}
}

bool Interface::EventDrawMenu_Open(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->Data[eMenu].EventTick);
	// ----
	if (!this->Data[eMenu].OnShow || !IsWorkZone(eMenu))
	{
		return false;
	}
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		
	if(gProtect.m_MainInfo.CustomInterfaceType != 3 || gProtect.m_MainInfo.CustomInterfaceType != 4)
	{
		pSetCursorFocus = true;
	}
		this->Data[eMenu].OnClick = true;
		return true;
	}
	// ----
	this->Data[eMenu].OnClick = false;
	// ----
	if (Delay < 500)
	{
		return false;
	}
	
	// ----
	this->Data[eMenu].EventTick = GetTickCount();
	
	if (Menu == 1)
	{
		if (CheckMenuWindow())
		{
			CloseMenuWindow();
			pSetCursorFocus = false;
		}
		else
		{
			CloseCustomWindow();
			OpenMenuWindow();
		}
	}
	// ----
	return false;
}

void Interface::DrawMenuOpen()
{
	if (gProtect.m_MainInfo.CustomMenuSwitch != 1 || !this->Data[eMenu_MAIN].OnShow || pCheckWindow(pWindowThis(), 35))
	{
		return;
	}

	float MainWidth = 230.0;
	float MainHeight = 360.0;
	float StartY = ((MAX_WIN_HEIGHT - 51) / 2) - (MainHeight / 2);
	float StartX = (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float MainCenter = StartX + (MainWidth / 3);
	float ButtonX = MainCenter - (float)(29.0 / 2);
	//--
	this->Data[eMenu_MAIN].MaxX = StartX + MainWidth;
	this->Data[eMenu_MAIN].MaxY = StartY + MainHeight;

	gCentral.PrintDropBox(StartX, StartY, MainWidth, MainHeight, 0, 0);

	this->DrawFormat(eGold, (int)StartX + 10, (int)StartY + 10, 210, 3, "Menu");

	

	if (gProtect.m_MainInfo.EnableCoinStatus == 1)
	{
		this->DrawFormat(eGold, (int)StartX + 10, (int)StartY + 35, 210, 3, gCustomMessage.GetMessage(50));

		this->DrawFormat(eWhite, (int)StartX + 25, (int)StartY + 55, 40, 1, gCustomMessage.GetMessage(51));
		this->DrawFormat(eGold, (int)StartX + 50, (int)StartY + 55, 40, 1, "%d", Coin1);

		this->DrawFormat(eWhite, (int)StartX + 90, (int)StartY + 55, 40, 1, gCustomMessage.GetMessage(52));
		this->DrawFormat(eGold, (int)StartX + 115, (int)StartY + 55, 40, 1, "%d", Coin2);

		this->DrawFormat(eWhite, (int)StartX + 153, (int)StartY + 55, 40, 1, gCustomMessage.GetMessage(53));
		this->DrawFormat(eGold, (int)StartX + 176, (int)StartY + 55, 40, 1, "%d", Coin3);
	}
	else
	{
		this->DrawFormat(eGold, (int)StartX + 10, (int)StartY + 45, 210, 3, gCustomMessage.GetMessage(54));
	}

	pDrawGUI(71520, StartX + (MainWidth / 2) - (200 / 2), StartY + 75, 200, 1); //-- Divisor

	gInterface.DrawGUI(eSAMPLEBUTTON, StartX + MainWidth - gInterface.Data[eSAMPLEBUTTON].Width - 15, 170);

	if (IsWorkZone(eSAMPLEBUTTON))
	{

		this->DrawToolTip(StartX + MainWidth - gInterface.Data[eSAMPLEBUTTON].Width - 15, 190, "NEXT");
		// ----
		if (this->Data[eSAMPLEBUTTON].OnClick)
		{
			this->DrawColoredGUI(eSAMPLEBUTTON, StartX + MainWidth - gInterface.Data[eSAMPLEBUTTON].Width - 15, 170, pMakeColor(40, 20, 3, 130));
			return;
		}
		// ----
		this->DrawColoredGUI(eSAMPLEBUTTON, StartX + MainWidth - gInterface.Data[eSAMPLEBUTTON].Width - 15, 170, pMakeColor(255, 204, 20, 200));
	}

	float CurrentMove;
	int BtCount = -1;
	int BtStart = StartY + 88;

	int ObjectIDs[7] =
	{
		eMenu_OPT1,
		eMenu_OPT2,
		eMenu_OPT3,
		eMenu_OPT4,
		eMenu_OPT5,
		eMenu_OPT6,
		eMenu_OPT7,
	};

	for (int n = 0; n < 7; n++)
	{
		if (PanelButtons[n] == 1)
		{
			BtCount++;
		}
		else
		{
			continue;
		}

		CurrentMove = 0.0;
		if (IsWorkZone(ObjectIDs[n]))
		{
			if (this->Data[ObjectIDs[n]].OnClick)
			{
				PlayBuffer(25, 0, 0);
				CurrentMove = 30.5f;
			}
		}
		this->DrawButton(ObjectIDs[n], StartX + (MainWidth / 2) - (108 / 2), BtStart + (33.0f * BtCount), 0, CurrentMove);
		this->DrawFormat(eWhite, StartX + (MainWidth / 2) - (108 / 2), BtStart + (33.0f * BtCount) + 9, 108, 3, gCustomMessage.GetMessage((n == 7) ? 44 : 25 + n));
	}

	pDrawGUI(71520, StartX + (MainWidth / 2) - (200 / 2), StartY + MainHeight - 40, 200, 1); //-- Divisor

	if (IsWorkZone(eMenu_CLOSE))
	{
		if (this->Data[eMenu_CLOSE].OnClick)
		{
			PlayBuffer(25, 0, 0);
			gInterface.DrawButtonRender(eMenu_CLOSE, StartX + (MainWidth / 2) - (59 / 2), StartY + MainHeight - 32, 0, 28);
		}
		else
		{
			gInterface.DrawButtonRender(eMenu_CLOSE, StartX + (MainWidth / 2) - (59 / 2), StartY + MainHeight - 32, 0, 0);
		}
	}
	else
	{
		gInterface.DrawButtonRender(eMenu_CLOSE, StartX + (MainWidth / 2) - (59 / 2), StartY + MainHeight - 32, 0, 0);
	}
	gInterface.DrawFormat(eWhite, StartX + (MainWidth / 2) - (59 / 2), StartY + MainHeight - 25, 59, 3, "Close");
}

void Interface::DrawMenu2Open()
{
	if (gProtect.m_MainInfo.CustomMenuSwitch != 1 || !this->Data[eMenu_MAIN2].OnShow || pCheckWindow(pWindowThis(), 35))
	{
		return;
	}

	float MainWidth = 230.0;
	float MainHeight = 360.0;
	float StartY = ((MAX_WIN_HEIGHT - 51) / 2) - (MainHeight / 2);
	float StartX = (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float MainCenter = StartX + (MainWidth / 3);
	float ButtonX = MainCenter - (float)(29.0 / 2);
	//--
	this->Data[eMenu_MAIN2].MaxX = StartX + MainWidth;
	this->Data[eMenu_MAIN2].MaxY = StartY + MainHeight;

	gCentral.PrintDropBox(StartX, StartY, MainWidth, MainHeight, 0, 0);

	this->DrawFormat(eGold, (int)StartX + 10, (int)StartY + 10, 210, 3, "Menu");

	

	if (gProtect.m_MainInfo.EnableCoinStatus == 1)
	{
		this->DrawFormat(eGold, (int)StartX + 10, (int)StartY + 35, 210, 3, gCustomMessage.GetMessage(50));

		this->DrawFormat(eWhite, (int)StartX + 25, (int)StartY + 55, 40, 1, gCustomMessage.GetMessage(51));
		this->DrawFormat(eGold, (int)StartX + 50, (int)StartY + 55, 40, 1, "%d", Coin1);

		this->DrawFormat(eWhite, (int)StartX + 90, (int)StartY + 55, 40, 1, gCustomMessage.GetMessage(52));
		this->DrawFormat(eGold, (int)StartX + 115, (int)StartY + 55, 40, 1, "%d", Coin2);

		this->DrawFormat(eWhite, (int)StartX + 153, (int)StartY + 55, 40, 1, gCustomMessage.GetMessage(53));
		this->DrawFormat(eGold, (int)StartX + 176, (int)StartY + 55, 40, 1, "%d", Coin3);
	}
	else
	{
		this->DrawFormat(eGold, (int)StartX + 10, (int)StartY + 45, 210, 3, gCustomMessage.GetMessage(54));
	}

	pDrawGUI(71520, StartX + (MainWidth / 2) - (200 / 2), StartY + 75, 200, 1); //-- Divisor

	gInterface.DrawGUI(eSAMPLEBUTTON2, StartX + 10, 170);

	if (IsWorkZone(eSAMPLEBUTTON2))
	{

		this->DrawToolTip(StartX + 10, 190, "BACK");
		// ----
		if (this->Data[eSAMPLEBUTTON2].OnClick)
		{
			this->DrawColoredGUI(eSAMPLEBUTTON2, StartX + 10, 170, pMakeColor(40, 20, 3, 130));
			return;
		}
		// ----
		this->DrawColoredGUI(eSAMPLEBUTTON2, StartX + 10, 170, pMakeColor(255, 204, 20, 200));
	}

	float CurrentMove;
	int BtCount = -1;
	int BtStart = StartY + 88;

	int ObjectIDs[4] =
	{
		eMenu_OPT8,
		eMenu_OPT9,
		eMenu_OPT10,
		eMenu_OPT11,
	};

	for (int n = 0; n < 4; n++)
	{
		if (Panel2Buttons[n] == 1)
		{
			BtCount++;
		}
		else
		{
			continue;
		}

		CurrentMove = 0.0;
		if (IsWorkZone(ObjectIDs[n]))
		{
			if (this->Data[ObjectIDs[n]].OnClick)
			{
				PlayBuffer(25, 0, 0);
				CurrentMove = 30.5f;
			}
		}
		this->DrawButton(ObjectIDs[n], StartX + (MainWidth / 2) - (108 / 2), BtStart + (33.0f * BtCount), 0, CurrentMove);
		this->DrawFormat(eWhite, StartX + (MainWidth / 2) - (108 / 2), BtStart + (33.0f * BtCount) + 9, 108, 3, gCustomMessage.GetMessage((n == 4) ? 44 : 32 + n));
	}

	pDrawGUI(71520, StartX + (MainWidth / 2) - (200 / 2), StartY + MainHeight - 40, 200, 1); //-- Divisor

	if (IsWorkZone(eMenu_CLOSE))
	{
		if (this->Data[eMenu_CLOSE].OnClick)
		{
			PlayBuffer(25, 0, 0);
			gInterface.DrawButtonRender(eMenu_CLOSE, StartX + (MainWidth / 2) - (59 / 2), StartY + MainHeight - 32, 0, 28);
		}
		else
		{
			gInterface.DrawButtonRender(eMenu_CLOSE, StartX + (MainWidth / 2) - (59 / 2), StartY + MainHeight - 32, 0, 0);
		}
	}
	else
	{
		gInterface.DrawButtonRender(eMenu_CLOSE, StartX + (MainWidth / 2) - (59 / 2), StartY + MainHeight - 32, 0, 0);
	}
	gInterface.DrawFormat(eWhite, StartX + (MainWidth / 2) - (59 / 2), StartY + MainHeight - 25, 59, 3, "Close");
}

bool Interface::EventDrawMenu_Close(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->Data[eMenu_CLOSE].EventTick);
	// ----
	if (!this->Data[eMenu_MAIN].OnShow || !IsWorkZone(eMenu_CLOSE))
	{
		return false;
	}
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[eMenu_CLOSE].OnClick = true;
		return true;
	}
	// ----
	this->Data[eMenu_CLOSE].OnClick = false;
	// ----
	if (Delay < 500)
	{
		return false;
	}
	// ----
	this->Data[eMenu_CLOSE].EventTick = GetTickCount();
	this->CloseMenuWindow();
	// ----
	return false;
}

bool Interface::EventDrawMenu2_Close(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->Data[eMenu_CLOSE].EventTick);
	// ----
	if (!this->Data[eMenu_MAIN2].OnShow || !IsWorkZone(eMenu_CLOSE))
	{
		return false;
	}
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[eMenu_CLOSE].OnClick = true;
		return true;
	}
	// ----
	this->Data[eMenu_CLOSE].OnClick = false;
	// ----
	if (Delay < 500)
	{
		return false;
	}
	// ----
	this->Data[eMenu_CLOSE].EventTick = GetTickCount();
	this->CloseMenu2Window();
	if (gProtect.m_MainInfo.CustomInterfaceType != 3 || gProtect.m_MainInfo.CustomInterfaceType != 4)
	{
		pSetCursorFocus = false;
	}
	// ----
	return false;
}
// ----------------------------------------------------------------------------------------------
bool Interface::EventDrawMenu_Next(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->Data[eSAMPLEBUTTON].EventTick);
	// ----
	if (!this->Data[eMenu_MAIN].OnShow || !IsWorkZone(eSAMPLEBUTTON))
	{
		return false;
	}
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[eSAMPLEBUTTON].OnClick = true;
		return true;
	}
	// ----
	this->Data[eSAMPLEBUTTON].OnClick = false;;
	// ----
	if (Delay < 500)
	{
		return false;
	}
	// ----
	this->Data[eSAMPLEBUTTON].EventTick = GetTickCount();

	this->CloseMenuWindow();
	this->OpenMenu2Window();
	// ----
	return false;
}

bool Interface::EventDrawMenu_Back(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->Data[eSAMPLEBUTTON2].EventTick);
	// ----
	if (!this->Data[eMenu_MAIN2].OnShow || !IsWorkZone(eSAMPLEBUTTON2))
	{
		return false;
	}
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[eSAMPLEBUTTON2].OnClick = true;
		return true;
	}
	// ----
	this->Data[eSAMPLEBUTTON2].OnClick = false;;
	// ----
	if (Delay < 500)
	{
		return false;
	}
	// ----
	this->Data[eSAMPLEBUTTON2].EventTick = GetTickCount();

	this->CloseMenu2Window();
	this->OpenMenuWindow();

	// ----
	return false;
}
// ----------------------------------------------------------------------------------------------

bool Interface::EventDrawMenu_Op1(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->Data[eMenu_OPT1].EventTick);
	// ----
	if (!this->Data[eMenu_MAIN].OnShow || !IsWorkZone(eMenu_OPT1))
	{
		return false;
	}
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[eMenu_OPT1].OnClick = true;
		return true;
	}
	// ----
	this->Data[eMenu_OPT1].OnClick = false;;
	// ----
	if (Delay < 500)
	{
		return false;
	}
	// ----
	this->Data[eMenu_OPT1].EventTick = GetTickCount();

	this->CloseMenuWindow();

	gCustomEventTime.OpenWindow();
	// ----
	return false;
}

bool Interface::EventDrawMenu_Op2(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->Data[eMenu_OPT2].EventTick);
	// ----
	if (!this->Data[eMenu_MAIN].OnShow || !IsWorkZone(eMenu_OPT2))
	{
		return false;
	}
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[eMenu_OPT2].OnClick = true;
		return true;
	}
	// ----
	this->Data[eMenu_OPT2].OnClick = false;;
	// ----
	if (Delay < 500)
	{
		return false;
	}
	// ----
	this->Data[eMenu_OPT2].EventTick = GetTickCount();

	this->CloseCustomWindow();

	this->OpenVipWindow();
	// ----
	return false;
}

bool Interface::EventDrawMenu_Op3(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->Data[eMenu_OPT3].EventTick);
	// ----
	if (!this->Data[eMenu_MAIN].OnShow || !IsWorkZone(eMenu_OPT3))
	{
		return false;
	}
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[eMenu_OPT3].OnClick = true;
		return true;
	}
	// ----
	this->Data[eMenu_OPT3].OnClick = false;;
	// ----
	if (Delay < 500)
	{
		return false;
	}
	// ----
	this->Data[eMenu_OPT3].EventTick = GetTickCount();

	this->CloseMenuWindow();

	UP_SEND_REQ pRequest;
	pRequest.h.set(0xFD, 0x21, sizeof(pRequest));
	DataSend((BYTE*)&pRequest, pRequest.h.size);
	gRanking.Show = true;
	// ----
	return false;
}

bool Interface::EventDrawMenu_Op4(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->Data[eMenu_OPT4].EventTick);
	// ----
	if (!this->Data[eMenu_MAIN].OnShow || !IsWorkZone(eMenu_OPT4))
	{
		return false;
	}
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[eMenu_OPT4].OnClick = true;
		return true;
	}
	// ----
	this->Data[eMenu_OPT4].OnClick = false;;
	// ----
	if (Delay < 500)
	{
		return false;
	}
	// ----
	this->Data[eMenu_OPT4].EventTick = GetTickCount();

	this->CloseMenuWindow();

	gCustomCommandInfo.OpenCommandWindow();
	// ----
	return false;
}

bool Interface::EventDrawMenu_Op20(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->Data[eMenu_OPT5].EventTick);
	// ----
	if (!this->Data[eMenu_MAIN].OnShow || !IsWorkZone(eMenu_OPT5))
	{
		return false;
	}
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[eMenu_OPT5].OnClick = true;
		return true;
	}
	// ----
	this->Data[eMenu_OPT5].OnClick = false;;
	// ----
	if (Delay < 500)
	{
		return false;
	}
	// ----
	this->Data[eMenu_OPT5].EventTick = GetTickCount();

	this->CloseMenuWindow();

	if (gJewelsBank.Active != true)
	{
		gJewelsBank.Active = true;
	}
	else
	{
		gJewelsBank.Active = false;
	}

//	this->OpenWindow(ObjWindow::Options);
	// ----
	return false;
}

bool Interface::EventDrawMenu_Op6(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->Data[eMenu_OPT6].EventTick);
	// ----
	if (!this->Data[eMenu_MAIN].OnShow || !IsWorkZone(eMenu_OPT6))
	{
		return false;
	}
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[eMenu_OPT6].OnClick = true;
		return true;
	}
	// ----
	this->Data[eMenu_OPT6].OnClick = false;;
	// ----
	if (Delay < 500)
	{
		return false;
	}
	// ----
	this->Data[eMenu_OPT6].EventTick = GetTickCount();

	this->CloseMenuWindow();

	gInterface.SwitchPartySettingsWindowState();
	// ----
	return false;
}

bool Interface::EventDrawMenu_Op7(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->Data[eMenu_OPT7].EventTick);
	// ----
	if (!this->Data[eMenu_MAIN].OnShow || !IsWorkZone(eMenu_OPT7))
	{
		return false;
	}
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[eMenu_OPT7].OnClick = true;
		return true;
	}
	// ----
	this->Data[eMenu_OPT7].OnClick = false;;
	// ----
	if (Delay < 500)
	{
		return false;
	}
	// ----
	this->Data[eMenu_OPT7].EventTick = GetTickCount();

	this->CloseMenuWindow();

	gChangeClass.OpenChangeWindow();
	// ----
	return false;
}

bool Interface::EventDrawMenu_Op8(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->Data[eMenu_OPT8].EventTick);
	// ----
	if (!this->Data[eMenu_MAIN2].OnShow || !IsWorkZone(eMenu_OPT8))
	{
		return false;
	}
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[eMenu_OPT8].OnClick = true;
		return true;
	}
	// ----
	this->Data[eMenu_OPT8].OnClick = false;;
	// ----
	if (Delay < 500)
	{
		return false;
	}
	// ----
	this->Data[eMenu_OPT8].EventTick = GetTickCount();

	this->CloseMenu2Window();
	gResetChange.OpenResetChange();
	// ----
	return false;
}

bool Interface::EventDrawMenu_Op9(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->Data[eMenu_OPT9].EventTick);
	// ----
	if (!this->Data[eMenu_MAIN2].OnShow || !IsWorkZone(eMenu_OPT9))
	{
		return false;
	}
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[eMenu_OPT9].OnClick = true;
		return true;
	}
	// ----
	this->Data[eMenu_OPT9].OnClick = false;;
	// ----
	if (Delay < 500)
	{
		return false;
	}
	// ----
	this->Data[eMenu_OPT9].EventTick = GetTickCount();

	this->CloseMenu2Window();
	if (GetForegroundWindow() == pGameWindow)
	{
		gInterface.LuckyWheelState();
	}
	// ----
	return false;
}

bool Interface::EventDrawMenu_Op10(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->Data[eMenu_OPT10].EventTick);
	// ----
	if (!this->Data[eMenu_MAIN2].OnShow || !IsWorkZone(eMenu_OPT10))
	{
		return false;
	}
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[eMenu_OPT10].OnClick = true;
		return true;
	}
	// ----
	this->Data[eMenu_OPT10].OnClick = false;;
	// ----
	if (Delay < 500)
	{
		return false;
	}
	// ----
	this->Data[eMenu_OPT10].EventTick = GetTickCount();

	this->CloseMenu2Window();
#if (ARCHIVEMENT == 1)
	gAchievements.CGWindowOpen();
#endif
	// ----
	return false;
}

bool Interface::EventDrawMenu_Op11(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->Data[eMenu_OPT11].EventTick);
	// ----
	if (!this->Data[eMenu_MAIN2].OnShow || !IsWorkZone(eMenu_OPT11))
	{
		return false;
	}
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[eMenu_OPT11].OnClick = true;
		return true;
	}
	// ----
	this->Data[eMenu_OPT11].OnClick = false;;
	// ----
	if (Delay < 500)
	{
		return false;
	}
	// ----
	this->Data[eMenu_OPT11].EventTick = GetTickCount();

	this->CloseMenu2Window();
	gSmithItem.OpenSmithItemWindow();
	// ----
	return false;
}

bool Interface::MiniMapCheck()
{
	bool visual = false;

	if (gProtect.m_MainInfo.CustomInterfaceType == 3 && gProtect.m_MainInfo.NewPanelCharacterS10 == 0 ||
		gProtect.m_MainInfo.CustomInterfaceType == 4 && gProtect.m_MainInfo.NewPanelCharacterS10 == 0 ||
		gProtect.m_MainInfo.CustomInterfaceType == 0 ||
		gProtect.m_MainInfo.CustomInterfaceType == 1 ||
		gProtect.m_MainInfo.CustomInterfaceType == 2)
	{
		if (gInterface.CheckWindow(13) && gInterface.CheckWindow(Character)
			|| gInterface.CheckWindow(8)
			|| gInterface.CheckWindow(12)
			|| gInterface.CheckWindow(9)
			|| gInterface.CheckWindow(7)
			|| gInterface.CheckWindow(14)
			|| gInterface.CheckWindow(15)
			|| gInterface.CheckWindow(60)
			|| gInterface.CheckWindow(76))
		{
			visual = true;
		}
		else
		{
			if (gInterface.CheckWindow(16) && (gInterface.CheckWindow(4) || gInterface.CheckWindow(69)))
			{
				visual = true;
			}
			else
			{
				if (gInterface.CheckWindow(16) && gInterface.CheckWindow(11))
				{
					visual = true;
				}
				else
				{
					if (gInterface.CheckWindow(27))
					{
						visual = true;
					}
					else
					{
						if (gInterface.CheckWindow(13)
							|| gInterface.CheckWindow(16)
							|| gInterface.CheckWindow(3)
							|| gInterface.CheckWindow(21)
							|| gInterface.CheckWindow(6)
							|| gInterface.CheckWindow(22)
							|| gInterface.CheckWindow(23)
							|| gInterface.CheckWindow(24)
							|| gInterface.CheckWindow(4)
							|| gInterface.CheckWindow(18)
							|| gInterface.CheckWindow(10)
							|| gInterface.CheckWindow(5)
							|| gInterface.CheckWindow(25)
							|| gInterface.CheckWindow(26)
							|| gInterface.CheckWindow(19)
							|| gInterface.CheckWindow(20)
							|| gInterface.CheckWindow(58)
							|| gInterface.CheckWindow(59)
							|| gInterface.CheckWindow(62)
							|| gInterface.CheckWindow(73)
							|| gInterface.CheckWindow(68)
							|| gInterface.CheckWindow(69)
							|| gInterface.CheckWindow(70)
							|| gInterface.CheckWindow(66)
							|| gInterface.CheckWindow(75)
							|| gInterface.CheckWindow(74))
						{
							visual = true;
						}
						else
						{
							if (gInterface.CheckWindow(79))
							{
								if (gInterface.CheckWindow(80))
								{
									visual = true;
								}
								else
								{
									visual = true;
								}
							}
						}
					}
				}
			}
		}

		if (gInterface.CheckWindow(77))
		{
			if (gInterface.CheckWindow(Warehouse) ||
				gInterface.CheckWindow(ChaosBox) ||
				gInterface.CheckWindow(Store) ||
				gInterface.CheckWindow(OtherStore) ||
				gInterface.CheckWindow(Character))
			{
				visual = true;
			}
			else
			{
				visual = true;
			}
		}
		else if (gInterface.CheckWindow(78))
		{
			visual = true;
		}
	}
	else if (gProtect.m_MainInfo.CustomInterfaceType == 3 && gProtect.m_MainInfo.NewPanelCharacterS10 == 1 ||
		gProtect.m_MainInfo.CustomInterfaceType == 4 && gProtect.m_MainInfo.NewPanelCharacterS10 == 1 )
	{
		if (gInterface.CheckWindow(13)
			|| gInterface.CheckWindow(8)
			|| gInterface.CheckWindow(12)
			|| gInterface.CheckWindow(9)
			|| gInterface.CheckWindow(7)
			|| gInterface.CheckWindow(14)
			|| gInterface.CheckWindow(15)
			|| gInterface.CheckWindow(60)
			|| gInterface.CheckWindow(76))
		{
			visual = true;
		}
		else
		{
			if (gInterface.CheckWindow(11))
				{
					visual = true;
				}
				else
				{
					if (gInterface.CheckWindow(27))
					{
						visual = true;
					}
					else
					{
						if (gInterface.CheckWindow(13)
							|| gInterface.CheckWindow(3)
							|| gInterface.CheckWindow(21)
							|| gInterface.CheckWindow(6)
							|| gInterface.CheckWindow(22)
							|| gInterface.CheckWindow(23)
							|| gInterface.CheckWindow(24)
							|| gInterface.CheckWindow(4)
							|| gInterface.CheckWindow(18)
							|| gInterface.CheckWindow(10)
							|| gInterface.CheckWindow(5)
							|| gInterface.CheckWindow(25)
							|| gInterface.CheckWindow(26)
							|| gInterface.CheckWindow(19)
							|| gInterface.CheckWindow(20)
							|| gInterface.CheckWindow(58)
							|| gInterface.CheckWindow(59)
							|| gInterface.CheckWindow(62)
							|| gInterface.CheckWindow(73)
							|| gInterface.CheckWindow(68)
							|| gInterface.CheckWindow(69)
							|| gInterface.CheckWindow(70)
							|| gInterface.CheckWindow(66)
							|| gInterface.CheckWindow(75)
							|| gInterface.CheckWindow(74))
						{
							visual = true;
						}
						else
						{
							if (gInterface.CheckWindow(79))
							{
								if (gInterface.CheckWindow(80))
								{
									visual = true;
								}
								else
								{
									visual = true;
								}
							}
						}
					}
				}
		}

		if (gInterface.CheckWindow(77))
		{
			if (gInterface.CheckWindow(Warehouse) ||
				gInterface.CheckWindow(ChaosBox) ||
				gInterface.CheckWindow(Store) ||
				gInterface.CheckWindow(OtherStore))
			{
				visual = true;
			}
			else
			{
				visual = true;
			}
		}
		else if (gInterface.CheckWindow(78))
		{
			visual = true;
		}
	}
	return visual;
}

bool Interface::CombinedChecks()
{
	if ((this->CheckWindow(Inventory)
		&& this->CheckWindow(ExpandInventory)
		&& this->CheckWindow(Store)) ||
		(this->CheckWindow(Inventory)
		&& this->CheckWindow(Warehouse)
		&& this->CheckWindow(ExpandWarehouse)) ||
		(this->CheckWindow(Inventory)
		&& this->CheckWindow(Character)
		&& this->CheckWindow(Store)))
		return true;
	return false;
}

bool Interface::CheckMap()
{
	switch(gObjUser.m_MapNumber)
	{
		case eMapNumber::Lorencia:
			return false;
			break;
		case eMapNumber::Dungeon:
			return false;
			break;
		case eMapNumber::Devias:
			return false;
			break;
		case eMapNumber::Noria:
			return false;
			break;
		case eMapNumber::LostTower:
			return false;
			break;
		case eMapNumber::Stadium:
			return false;
		case eMapNumber::Atlans:
			return false;
			break;
		case eMapNumber::Tarkan:
			return false;
			break;
		case eMapNumber::Elbeland:
			return false;
			break;
		case eMapNumber::Icarus:
			return false;
			break;
		case eMapNumber::Trials:
			return false;
			break;
		case eMapNumber::Aida:
			return false;
			break;
		case eMapNumber::Crywolf:
			return false;
			break;
		case eMapNumber::Kanturu1:
			return false;
			break;
		case eMapNumber::Kanturu3:
			return false;
			break;
		case eMapNumber::Barracks:
			return false;
			break;
		case eMapNumber::Calmness:
			return false;
			break;
		case eMapNumber::Raklion:
			return false;
			break;
		case eMapNumber::Vulcanus:
			return false;
			break;
		case eMapNumber::Karutan1:
			return false;
			break;
		case eMapNumber::Karutan2:
			return false;
			break;
		default:
			return true;
			break;
	}
}

void Interface::CloseCustomWindow()
{
	this->CloseMenuWindow();
	this->CloseVipWindow();
	this->Data[eRankPANEL_MAIN].OnShow		= false;
	this->Data[eEventTimePANEL_MAIN].OnShow = false;
	this->Data[eCommand_MAIN].OnShow		= false;
	
	if(gProtect.m_MainInfo.CustomInterfaceType != 3 || gProtect.m_MainInfo.CustomInterfaceType != 4)
	{
		pSetCursorFocus = false;
	}
}

void testfunc()
{
	glMatrixMode(0x1700u);
	glPopMatrix();
	glMatrixMode(0x1701u);
	glPopMatrix();
}

#define sub_636720_Addr ((int(*)())0x636720)
#define sub_6363D0_Addr ((void(__cdecl*)(GLint x, int a2, GLsizei width, GLsizei height)) 0x6363D0)
#define sub_6358A0_Addr ((int(__cdecl*)(float a1, float a2, float a3, float a4)) 0x6358A0)
#define sub_635830_Addr ((void(__cdecl*)(LPVOID a1)) 0x635830)
#define sub_635DE0_Addr ((void(*)()) 0x635DE0)
#define sub_635E40_Addr ((void(*)()) 0x635E40)
#define sub_637770_Addr ((void(*)()) 0x637770)

void Interface::DrawItemIMG(float PosX, float PosY, float Width, float Height, int ItemID, int Level, int Excl, int Anc, bool OnMouse) // code hien thi item
{

	glMatrixMode(0x1701);
	glPushMatrix();
	glLoadIdentity();

	sub_6363D0_Addr(0, 0, *(GLsizei*)MAIN_RESOLUTION_X, *(GLsizei*)MAIN_RESOLUTION_Y);
	float v2 = *(float*)MAIN_RESOLUTION_X / *(float*)MAIN_RESOLUTION_Y;
	sub_6358A0_Addr(1.0, v2, *(float*)0xE61E38, *(float*)0xE61E3C);

	glMatrixMode(0x1700);
	glPushMatrix();
	glLoadIdentity();

	sub_635830_Addr((LPVOID)0x87933A0);
	sub_635DE0_Addr();
	sub_635E40_Addr();

	pDrawItemModel(PosX, PosY, Width, Height, ItemID, Level, Excl, Anc, OnMouse);

	testfunc();

	glColor3f(1, 1, 1);
	pSetBlend(false);
}

void Interface::DrawConfirmOpen()
{
	if(!this->CheckWindow(Shop) && this->Data[eCONFIRM_MAIN].OnShow == true)
	{
		this->Data[eCONFIRM_MAIN].OnShow = false;
	}

	if ((GetTickCount() - this->Data[eCONFIRM_BTN_OK].EventTick) < 100)
	{
		this->Data[eCONFIRM_MAIN].OnShow = false;
	}

	if ((GetTickCount() - this->Data[eCONFIRM_BTN_CANCEL].EventTick) < 100)
	{
		this->Data[eCONFIRM_MAIN].OnShow = false;
	}

	if( !this->Data[eCONFIRM_MAIN].OnShow )
	{
		return;
	}
	
	if (gProtect.m_MainInfo.CustomInterfaceType == 3 || gProtect.m_MainInfo.CustomInterfaceType == 4)
	{
		float MainWidth = 230.0;
		float MainHeight = 130.0;
		float StartBody = 90.0;
		float StartY = 90.0;
		float StartX = 200;
		float MainCenter = StartX + (MainWidth / 3);
		float ButtonX = MainCenter - (float)(29.0 / 2);

		gCentral.PrintDropBox(StartX, StartY, MainWidth, MainHeight, 0, 0);

		this->DrawFormat(eGold, (int)StartX + 10, (int)StartBody + 10, 210, 3, gCustomMessage.GetMessage(66));

		this->DrawFormat(eGold, (int)StartX + 10, (int)StartBody + 40, 210, 3, gCustomMessage.GetMessage(67));

		this->DrawButton(eCONFIRM_BTN_OK, (int)StartX + 40, (int)StartBody + 70, 0, 0);

		if (this->IsWorkZone(eCONFIRM_BTN_OK))
		{
			int ScaleY = 30;
			// ----
			if (this->Data[eCONFIRM_BTN_OK].OnClick)
			{
				ScaleY = 60;
			}
			// ----
			this->DrawButton(eCONFIRM_BTN_OK, (int)StartX + 40, (int)StartBody + 70, 0, ScaleY);
		}

		this->DrawButton(eCONFIRM_BTN_CANCEL, (int)StartX + 140, (int)StartBody + 70, 0, 0);

		if (this->IsWorkZone(eCONFIRM_BTN_CANCEL))
		{
			int ScaleY = 30;
			// ----
			if (this->Data[eCONFIRM_BTN_CANCEL].OnClick)
			{
				ScaleY = 60;
			}
			// ----
			this->DrawButton(eCONFIRM_BTN_CANCEL, (int)StartX + 140, (int)StartBody + 70, 0, ScaleY);
		}
	}
	else
	{

		float MainWidth = 230.0;
		float MainHeight = 130.0;
		float StartBody = 90.0;
		float StartY = 90.0;
		float StartX = 25;
		float MainCenter = StartX + (MainWidth / 3);
		float ButtonX = MainCenter - (float)(29.0 / 2);

		gInterface.DrawGUI(eCONFIRM_MAIN, StartX, StartY + (float)2.0);
		gInterface.DrawGUI(eVip_TITLE, StartX, StartY);
		StartY = gInterface.DrawRepeatGUI(eVip_FRAME, StartX, StartY + (float)5.0, 5);
		gInterface.DrawGUI(eVip_FOOTER, StartX, StartY);

		this->DrawFormat(eGold, (int)StartX + 10, (int)StartBody + 10, 210, 3, gCustomMessage.GetMessage(66));

		this->DrawFormat(eGold, (int)StartX + 10, (int)StartBody + 40, 210, 3, gCustomMessage.GetMessage(67));

		this->DrawButton(eCONFIRM_BTN_OK, (int)StartX + 40, (int)StartBody + 70, 0, 0);

		if (this->IsWorkZone(eCONFIRM_BTN_OK))
		{
			int ScaleY = 30;
			// ----
			if (this->Data[eCONFIRM_BTN_OK].OnClick)
			{
				ScaleY = 60;
			}
			// ----
			this->DrawButton(eCONFIRM_BTN_OK, (int)StartX + 40, (int)StartBody + 70, 0, ScaleY);
		}

		this->DrawButton(eCONFIRM_BTN_CANCEL, (int)StartX + 140, (int)StartBody + 70, 0, 0);

		if (this->IsWorkZone(eCONFIRM_BTN_CANCEL))
		{
			int ScaleY = 30;
			// ----
			if (this->Data[eCONFIRM_BTN_CANCEL].OnClick)
			{
				ScaleY = 60;
			}
			// ----
			this->DrawButton(eCONFIRM_BTN_CANCEL, (int)StartX + 140, (int)StartBody + 70, 0, ScaleY);
		}
	}

}


bool Interface::EventConfirm_OK(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->Data[eCONFIRM_BTN_OK].EventTick);
	// ----
	if (!this->Data[eCONFIRM_MAIN].OnShow || !IsWorkZone(eCONFIRM_BTN_OK))
	{
		return false;
	}
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[eCONFIRM_BTN_OK].OnClick = true;
		return true;
	}
	// ----
	this->Data[eCONFIRM_BTN_OK].OnClick = false;;
	// ----
	if (Delay < 500)
	{
		return false;
	}
	// ----
	this->Data[eCONFIRM_BTN_OK].EventTick = GetTickCount();

	PMSG_ITEM_BUY_RECV pMsg;

	pMsg.header.set(0xF3, 0xED,sizeof(pMsg));

	pMsg.slot = this->ConfirmSlot;

	DataSend((BYTE*)&pMsg,pMsg.header.size);

	this->Data[eCONFIRM_MAIN].OnShow = false;
	
	if(gProtect.m_MainInfo.CustomInterfaceType != 3 || gProtect.m_MainInfo.CustomInterfaceType != 4)
	{
		pSetCursorFocus = false;
	}
	// ----
	return false;
}

bool Interface::EventConfirm_CANCEL(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->Data[eCONFIRM_BTN_CANCEL].EventTick);
	// ----
	if (!this->Data[eCONFIRM_MAIN].OnShow || !IsWorkZone(eCONFIRM_BTN_CANCEL))
	{
		return false;
	}
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[eCONFIRM_BTN_CANCEL].OnClick = true;
		return true;
	}
	// ----
	this->Data[eCONFIRM_BTN_CANCEL].OnClick = false;;
	// ----
	if (Delay < 500)
	{
		return false;
	}
	// ----
	this->Data[eCONFIRM_BTN_CANCEL].EventTick = GetTickCount();

	this->Data[eCONFIRM_MAIN].OnShow = false;

	if(gProtect.m_MainInfo.CustomInterfaceType != 3 || gProtect.m_MainInfo.CustomInterfaceType != 4)
	{
		pSetCursorFocus = false;
	}
	// ----
	return false;
}

//-- advance
void Interface::DrawBarForm(float PosX, float PosY, float Width, float Height, GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
	pSetBlend(true);
	glColor4f((GLfloat)0.0, (GLfloat)0.0, (GLfloat)0.0, (float)0.8);
	pDrawBarForm(PosX, PosY, Width, Height, 0.0f, 0);
	pGLSwitchBlend();
	pGLSwitch();
	glColor3f(1.0, 1.0, 1.0);
	pSetBlend(false);
}
// ----------------------------------------------------------------------------------------------
bool Interface::CheckWindowEx(int WindowID)
{
	if (WindowID < 0 || WindowID > MAX_WINDOW_EX)
	{
		return 0;
	}
	return this->WindowEx[WindowID];
}

//---- cosas peladas

void Interface::UPDATE_FPS(){
	gInterface.frameCount++;
	if (GetTickCount() - gInterface.lastReport >= 1000)
	{
		gInterface.frameRate = gInterface.frameCount / ((GetTickCount() - gInterface.lastReport) / 1000);
		sprintf(gInterface.FPS_REAL, "FPS: %d", gInterface.frameRate);
		gInterface.lastReport = GetTickCount();
		gInterface.frameCount = 0;
	}

	if (this->MiniMapCheck() || this->CombinedChecks() || this->CheckWindow(FullMap) || this->CheckWindow(FriendList) || this->CheckWindow(SkillTree) || this->CheckWindow(CashShop))
	{
		return;
	}

	if (gProtect.m_MainInfo.CustomInterfaceType == 0 || gProtect.m_MainInfo.CustomInterfaceType == 2 || gProtect.m_MainInfo.CustomInterfaceType == 3)
	{
		if (gInterface.CheckWindow(ObjWindow::Character))
		{
			return;
		}
	}

	//	pDrawInterfaceNumBer(630, 5, gInterface.frameRate, 0.5);
	this->DrawFormat(eGold, 470, 16, 80, 1, gInterface.FPS_REAL);
}

void Interface::guiMonitore(){
	if (this->MiniMapCheck() || this->CombinedChecks() || this->CheckWindow(FullMap) || this->CheckWindow(FriendList) || this->CheckWindow(SkillTree) || this->CheckWindow(CashShop))
	{
		return;
	}

	if (gProtect.m_MainInfo.CustomInterfaceType == 0 || gProtect.m_MainInfo.CustomInterfaceType == 2 || gProtect.m_MainInfo.CustomInterfaceType == 3)
	{
		if (gInterface.CheckWindow(ObjWindow::Character))
		{
			return;
		}
	}
	pSetBlend(true);
	glColor4f((GLfloat)0.0, (GLfloat)0.0, (GLfloat)0.0, (float)0.8);
	pDrawBarForm(460.0, 0.0, 80.0, 27.0, 0.0f, 0);
	pGLSwitchBlend();
	pGLSwitch();
	glColor3f(1.0, 1.0, 1.0);
	pSetBlend(false);
}

void Interface::DrawPing()
{
	gInterface.msPing = GetTickCount() - gInterface.lastSend;
	gInterface.iniciador = 3;
}

struct PMSG_PING
{
	PBMSG_HEAD h;
};

void Interface::SendPingRecv()
{
	if (gInterface.iniciador == 1){
		PMSG_PING pMsgPing;
		pMsgPing.h.set(0xFF, sizeof(pMsgPing));
		gInterface.lastSend = GetTickCount();
		DataSend((BYTE*)&pMsgPing, sizeof(pMsgPing));
		gInterface.iniciador = 2;
	}
	else if (gInterface.iniciador == 3){
		if (GetTickCount() >= gInterface.lastSend + 1000){
			PMSG_PING pMsgPing;
			pMsgPing.h.set(0xFF, sizeof(pMsgPing));
			gInterface.lastSend = GetTickCount();
			DataSend((BYTE*)&pMsgPing, sizeof(pMsgPing));
			gInterface.iniciador = 2;
		}
	}

	if (this->MiniMapCheck() || this->CombinedChecks() || this->CheckWindow(FullMap) || this->CheckWindow(FriendList) || this->CheckWindow(SkillTree) || this->CheckWindow(CashShop))
	{
		return;
	}

	if (gProtect.m_MainInfo.CustomInterfaceType == 0 || gProtect.m_MainInfo.CustomInterfaceType == 2 || gProtect.m_MainInfo.CustomInterfaceType == 3)
	{
		if (gInterface.CheckWindow(ObjWindow::Character))
		{
			return;
		}
	}
	sprintf(gInterface.ServerRTT, "RTT: %d ms", gInterface.msPing);
	sprintf(gInterface.ServerPing, "PING: %d ms", (gInterface.msPing / 2));
	// ----
	//	pDrawInterfaceNumBer(490, 5, gInterface.msPing, 0.5);
	//	pDrawInterfaceNumBer(560, 5, (gInterface.msPing/2), 0.5);
	// ----
	gInterface.validar = 0;

	if (gInterface.msPing > 0){
		//----
		this->DrawFormat(eGold, 470, 2, 100, 1, gInterface.ServerRTT);
		this->DrawFormat(eGold, 470, 9, 100, 1, gInterface.ServerPing);
		//--
		sprintf(gInterface.ultimoRTT, gInterface.ServerRTT);
		sprintf(gInterface.ultimoPing, gInterface.ServerPing);
		//--
		gInterface.ultimo_RTT = gInterface.msPing;
		gInterface.validar = 1;
	}

	if (gInterface.validar == 0)
	{
		if (gInterface.ultimo_RTT > 0)
		{
			this->DrawFormat(eGold, 470, 2, 60, 1, gInterface.ultimoRTT);
			this->DrawFormat(eGold, 470, 9, 100, 1, gInterface.ultimoPing);
		}
		else
		{
			this->DrawFormat(eGold, 470, 2, 100, 1, gInterface.ServerRTT);
			this->DrawFormat(eGold, 470, 9, 100, 1, gInterface.ServerPing);
		}
	}


}

void Interface::SwitchChatExpand()
{

	if((GetTickCount() - gInterface.Data[chatbackground].EventTick) < 1000 ||this->CheckWindow(ChatWindow))
	{
		return;
	}

	gInterface.Data[chatbackground].EventTick = GetTickCount();

	if (SeparateChat != 0)
	{
		gInterface.DrawMessage(1, "Chat Window Separate [OFF]");
		SeparateChat = 0;
		WritePrivateProfileStringA("Setting","SeparateChat","0","./Settings.ini");
	}
	else 
	{
		gInterface.DrawMessage(1, "Chat Window Separate [ON]");
		SeparateChat = 1;
		WritePrivateProfileStringA("Setting","SeparateChat","1","./Settings.ini");
	}
	gChatExpanded.Switch();
}

void Interface::OpenConfig(int type)
{
	if(type == 0)
	{
		if( (GetTickCount() - gInterface.Data[ePLAYER_POINT].EventTick) < 400 
			|| this->CheckWindow(ChatWindow) 
			|| this->CheckWindow(MuHelper) 
			|| this->CheckWindow(Inventory) 
			|| this->CheckWindow(Store) 
			|| this->CheckWindow(Character) 
			|| this->CheckWindow(CreateGuild) )
		{
			return;
		}

		gInterface.Data[ePLAYER_POINT].EventTick = GetTickCount();

		if (pCheckWindow(pWindowThis(), 35))
		{
			pCloseWindow(pWindowThis(), 35);
		}
		else 
		{
			pOpenWindow(pWindowThis(), 35);
		}
	}
	else if(type = 1 )
	{
		if( (GetTickCount() - gInterface.Data[ePLAYER_POINT].EventTick) < 400 || OpenSwicthSkill == 0)
		{
			return;
		}

		gInterface.Data[ePLAYER_POINT].EventTick = GetTickCount();

		if (SkillPage == 1)
		{
			SkillPage = 2;
		}
		else
		{
			SkillPage = 1;
		}
	}

	PlayBuffer(25, 0, 0);
}
//-- SwitchCamera
void Interface::SwitchCamera()
{
	if((GetTickCount() - gInterface.Data[eCamera3DSwitch].EventTick) < 1000)
	{
		return;
	}

	gInterface.Data[eCamera3DSwitch].EventTick = GetTickCount();

	gCamera.Toggle();

	if (gCamera.getEnabled())
	{
		gInterface.DrawMessage(1, "Camera3D [ON]");
	}
	else
	{
		gInterface.DrawMessage(1, "Camera3D [OFF] Haha buzigeci :)");
	}
}
//-- CameraInit
void Interface::CameraInit(){

	if((GetTickCount() - gInterface.Data[eCamera3DInit].EventTick) < 1000)
	{
		return;
	}

	gInterface.Data[eCamera3DInit].EventTick = GetTickCount();

	if (gCamera.getEnabled())
	{
		gInterface.DrawMessage(1, "Camera Restore [DEFAULT]");
		gCamera.Restore();
	}
}

bool Interface::Button(DWORD Event, int WinID, int ButtonID, bool Type)
{
	if (!this->IsWorkZone(ButtonID))
	{
		return false;
	}

	if (Type == true)
	{
		if (!this->Data[ButtonID].Attribute)
		{
			return false;
		}
	}

	// ----
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->Data[ButtonID].EventTick);
	// ----

	if (Event == WM_LBUTTONDOWN  && this->Data[ButtonID].OnClick == false)
	{
		this->Data[ButtonID].OnClick = true;
	}

	if (Event == WM_LBUTTONUP && this->Data[ButtonID].OnClick == true)
	{
		this->Data[ButtonID].OnClick = false;
		return true;
	}
	// ----
	if (Delay < 500)
	{
		return false;
	}
	// ----
	this->Data[ButtonID].OnClick = false;
	// ----
	this->Data[ButtonID].EventTick = GetTickCount();
	// ----
	return false;
}

void Interface::DrawInterfaceS2Menu()
{
	if (IsWorkZone(eParty))
	{
		this->DrawToolTip(345, 420, "Party");
	}
	if (this->CheckWindow(Party))
	{
		gInterface.DrawButton(eParty, 348, 451, 0.0, 0.0);
	}
	if (IsWorkZone(eCharacter))
	{
		this->DrawToolTip(375, 420, "Character");
	}
	if (this->CheckWindow(Character))
	{
		gInterface.DrawButton(eCharacter, 378.5f, 451, 0.0, 0.0);
	}
	if (IsWorkZone(eInventory))
	{
		this->DrawToolTip(405, 420, "Inventory");
	}
	if (this->CheckWindow(Inventory))
	{
		gInterface.DrawButton(eInventory, 409, 451, 0.0, 0.0);
	}
	if (IsWorkZone(eShop))
	{
		this->DrawToolTip(430, 420, "CashShop");
	}
	if (this->CheckWindow(CashShop))
	{
		gInterface.DrawButton(eShop, 439.5f, 451, 0.0, 0.0);
	}
	if (IsWorkZone(eFriend))
	{
		this->DrawToolTip(580, 420, "Friends");
	}
	if (this->CheckWindow(FriendList))
	{
		gInterface.DrawButton(eFriend, 581, 433, 0.0, 0.0);
	}
	if (IsWorkZone(eGuild))
	{
		this->DrawToolTip(580, 444, "Guild");
	}
	if (this->CheckWindow(Guild))
	{
		gInterface.DrawButton(eGuild, 581, 457, 0.0, 0.0);
	}
	if (IsWorkZone(eFastMenu))
	{
		this->DrawToolTip(13, 420, "System");
	}
	if (this->CheckWindow(FastMenu))
	{
		gInterface.DrawButton(eFastMenu, 6, 433, 0.0, 0.0);
	}
}
//--------------------------------------
void Interface::DrawInterface97Menu()
{
	if (IsWorkZone(eParty))
	{
		this->DrawToolTip(345, 420, "Party");
	}
	if (this->CheckWindow(Party))
	{
		gInterface.DrawButton(eParty, 348, 451, 0.0, 0.0);
	}
	if (IsWorkZone(eCharacter))
	{
		this->DrawToolTip(375, 420, "Character");
	}
	if (this->CheckWindow(Character))
	{
		gInterface.DrawButton(eCharacter, 378.5f, 451, 0.0, 0.0);
	}
	if (IsWorkZone(eInventory))
	{
		this->DrawToolTip(405, 420, "Inventory");
	}
	if (this->CheckWindow(Inventory))
	{
		gInterface.DrawButton(eInventory, 409, 451, 0.0, 0.0);
	}
	if (IsWorkZone(eShop))
	{
		this->DrawToolTip(430, 420, "CashShop");
	}
	if (this->CheckWindow(CashShop))
	{
		gInterface.DrawButton(eShop, 439.5f, 451, 0.0, 0.0);
	}
	if (IsWorkZone(eFriend))
	{
		this->DrawToolTip(580, 420, "Friends");
	}
	if (this->CheckWindow(FriendList))
	{
		gInterface.DrawButton(eFriend, 581, 433, 0.0, 0.0);
	}
	if (IsWorkZone(eGuild))
	{
		this->DrawToolTip(580, 444, "Guild");
	}
	if (this->CheckWindow(Guild))
	{
		gInterface.DrawButton(eGuild, 581, 457, 0.0, 0.0);
	}
}
//--------------------------------------
void Interface::EventNewInterface_All(DWORD Event){
	DWORD CurrentTick = GetTickCount();
	if (this->CheckWindow(ChaosBox))
	{
		return;
	}
	
	if (IsWorkZone(eFastMenu))
	{
		DWORD Delay = (CurrentTick - this->Data[eFastMenu].EventTick);
		if (Event == WM_LBUTTONDOWN) {
			this->Data[eFastMenu].OnClick = true;
			return;
		}
		this->Data[eFastMenu].OnClick = false;
		if (Delay < 500) {
			return;
		}
		this->Data[eFastMenu].EventTick = GetTickCount();
		if (this->CheckWindow(FastMenu)) {
				this->CloseWindow(FastMenu);
		}
		else {
			this->OpenWindow(FastMenu);
		}
	}
	else if (IsWorkZone(eParty))
	{
		DWORD Delay = (CurrentTick - this->Data[eParty].EventTick);
		if (Event == WM_LBUTTONDOWN) {
			this->Data[eParty].OnClick = true;
			return;
		}
		this->Data[eParty].OnClick = false;
		if (Delay < 500) {
			return;
		}
		this->Data[eParty].EventTick = GetTickCount();
		if (this->CheckWindow(Party)) {
			this->CloseWindow(Party);
		}
		else {
			this->OpenWindow(Party);
		}
	}
	
	else if (IsWorkZone(eCharacter))
	{
		DWORD Delay = (CurrentTick - this->Data[eCharacter].EventTick);
		if (Event == WM_LBUTTONDOWN) {
			this->Data[eCharacter].OnClick = true;
			return;
		}
		this->Data[eCharacter].OnClick = false;
		if (Delay < 500) {
			return;
		}
		this->Data[eCharacter].EventTick = GetTickCount();
		if (this->CheckWindow(Character)) {
			this->CloseWindow(Character);
		}
		else {
			this->OpenWindow(Character);
		}
	}
	else if (IsWorkZone(eInventory))
	{
		DWORD Delay = (CurrentTick - this->Data[eInventory].EventTick);
		if (Event == WM_LBUTTONDOWN) {
			this->Data[eInventory].OnClick = true;
			return;
		}
		this->Data[eInventory].OnClick = false;
		if (Delay < 500) {
			return;
		}
		this->Data[eInventory].EventTick = GetTickCount();
		if (this->CheckWindow(Inventory)) {
			this->CloseWindow(Inventory);
		}
		else {
			this->OpenWindow(Inventory);
		}
	}
	else if (IsWorkZone(eFriend))
	{
		DWORD Delay = (CurrentTick - this->Data[eFriend].EventTick);
		if (Event == WM_LBUTTONDOWN) {
			this->Data[eFriend].OnClick = true;
			return;
		}
		this->Data[eFriend].OnClick = false;
		if (Delay < 500) {
			return;
		}
		this->Data[eFriend].EventTick = GetTickCount();
		if (this->CheckWindow(FriendList)) {
			this->CloseWindow(FriendList);
		}
		else {
			this->OpenWindow(FriendList);
		}
	}
	else if (IsWorkZone(eGuild))
	{
		DWORD Delay = (CurrentTick - this->Data[eGuild].EventTick);
		if (Event == WM_LBUTTONDOWN) {
			this->Data[eGuild].OnClick = true;
			return;
		}
		this->Data[eGuild].OnClick = false;
		if (Delay < 500) {
			return;
		}
		this->Data[eGuild].EventTick = GetTickCount();
		if (this->CheckWindow(Guild)) {
			this->CloseWindow(Guild);
		}
		else {
			this->OpenWindow(Guild);
		}
	}
}
void Interface::EventNewInterface97_All(DWORD Event){
	DWORD CurrentTick = GetTickCount();
	if (this->CheckWindow(ChaosBox))
	{
		return;
	}
	
	if (IsWorkZone(eParty))
	{
		DWORD Delay = (CurrentTick - this->Data[eParty].EventTick);
		if (Event == WM_LBUTTONDOWN) {
			this->Data[eParty].OnClick = true;
			return;
		}
		this->Data[eParty].OnClick = false;
		if (Delay < 500) {
			return;
		}
		this->Data[eParty].EventTick = GetTickCount();
		if (this->CheckWindow(Party)) {
			this->CloseWindow(Party);
		}
		else {
			this->OpenWindow(Party);
		}
	}
	
	else if (IsWorkZone(eCharacter))
	{
		DWORD Delay = (CurrentTick - this->Data[eCharacter].EventTick);
		if (Event == WM_LBUTTONDOWN) {
			this->Data[eCharacter].OnClick = true;
			return;
		}
		this->Data[eCharacter].OnClick = false;
		if (Delay < 500) {
			return;
		}
		this->Data[eCharacter].EventTick = GetTickCount();
		if (this->CheckWindow(Character)) {
			this->CloseWindow(Character);
		}
		else {
			this->OpenWindow(Character);
		}
	}
	else if (IsWorkZone(eInventory))
	{
		DWORD Delay = (CurrentTick - this->Data[eInventory].EventTick);
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eInventory].OnClick = true;
			return;
		}
		this->Data[eInventory].OnClick = false;
		if (Delay < 500)
		{
			return;
		}
		this->Data[eInventory].EventTick = GetTickCount();
		if (this->CheckWindow(Inventory))
		{
			this->CloseWindow(Inventory);
		}
		else {
			this->OpenWindow(Inventory);
		}
	}
	else if (IsWorkZone(eFriend))
	{
		DWORD Delay = (CurrentTick - this->Data[eFriend].EventTick);
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eFriend].OnClick = true;
			return;
		}
		this->Data[eFriend].OnClick = false;
		if (Delay < 500)
		{
			return;
		}
		this->Data[eFriend].EventTick = GetTickCount();
		if (this->CheckWindow(FriendList))
		{
			this->CloseWindow(FriendList);
		}
		else {
			this->OpenWindow(FriendList);
		}
	}
	else if (IsWorkZone(eGuild))
	{
		DWORD Delay = (CurrentTick - this->Data[eGuild].EventTick);
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eGuild].OnClick = true;
			return;
		}
		this->Data[eGuild].OnClick = false;
		if (Delay < 500)
		{
			return;
		}
		this->Data[eGuild].EventTick = GetTickCount();
		if (this->CheckWindow(Guild))
		{
			this->CloseWindow(Guild);
		}
		else {
			this->OpenWindow(Guild);
		}
	}
}

void Interface::DrawInterfaceDragonLS3()
{
	if (this->CheckWindow(ObjWindow::CashShop)
		|| this->CheckWindow(ObjWindow::FullMap)
		|| this->CheckWindow(ObjWindow::SkillTree)
		|| this->CheckWindow(ObjWindow::MoveList)
		|| TimerBar == 1
		)
	{
		return;
	}
	this->DrawGUI(eDragonLeft, this->Data[eDragonLeft].X, this->Data[eDragonLeft].Y);
}

void Interface::DrawInterfaceDragonRS3()
{	
	if (this->MiniMapCheck()||(this->CheckWindow(SkillTree)|| this->CheckWindow(CashShop) || this->CheckWindow(FullMap)
		|| this->CheckWindow(FastMenu) || this->CheckWindow(FriendList))
		|| pMapNumber == 39 //Kanturu
		|| pMapNumber == 58 //Selupam
		|| pMapNumber == 64 //Duel Arena
		|| pMapNumber == 65 //Doppelganger
		|| pMapNumber == 66 //Doppelganger
		|| pMapNumber == 67 //Doppelganger
		|| pMapNumber == 68 //Doppelganger
		|| pMapNumber == 69 //Imperial Guardian
		|| pMapNumber == 70 //Imperial Guardian
		|| pMapNumber == 71 //Imperial Guardian
		|| pMapNumber == 72 //Imperial Guardian
		|| pMapNumber == 11	//Blood Castle
		|| pMapNumber == 12	//Blood Castle
		|| pMapNumber == 13	//Blood Castle
		|| pMapNumber == 14	//Blood Castle
		|| pMapNumber == 15	//Blood Castle
		|| pMapNumber == 16	//Blood Castle
		|| pMapNumber == 17	//Blood Castle
		|| pMapNumber == 52	//Blood Castle
		|| pMapNumber == 9	//Devil Square
		|| pMapNumber == 32	//Devil Square
		|| pMapNumber == 18	//Chaos Castle
		|| pMapNumber == 19	//Chaos Castle
		|| pMapNumber == 20	//Chaos Castle
		|| pMapNumber == 21	//Chaos Castle
		|| pMapNumber == 22	//Chaos Castle
		|| pMapNumber == 23	//Chaos Castle
		|| pMapNumber == 53	//Chaos Castle
		|| pMapNumber == 45	//Illusion Temple
		|| pMapNumber == 46	//Illusion Temple
		|| pMapNumber == 47	//Illusion Temple
		|| pMapNumber == 48	//Illusion Temple
		|| pMapNumber == 49	//Illusion Temple
		|| pMapNumber == 50	//Illusion Temple
		|| pMapNumber == 18	//Chaos Castle
		|| pMapNumber == 19	//Chaos Castle
		|| pMapNumber == 20	//Chaos Castle
		|| pMapNumber == 21	//Chaos Castle
		|| pMapNumber == 22	//Chaos Castle
		|| pMapNumber == 23	//Chaos Castle
		|| pMapNumber == 53	//Chaos Castle
		|| pMapNumber == 34 //Crywolf
		|| pMapNumber == 30 //Valley/CastleSiege
		|| pMapNumber == 65 /*DuelArena*/)
	{
		return;
	}
	this->DrawGUI(eDragonRight, this->Data[eDragonRight].X, this->Data[eDragonRight].Y);
}

void Interface::DrawCoord()
{
	gObjUser.Refresh();

	if (*(DWORD*)MAIN_SCREEN_STATE == 5)
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		pDrawInterfaceNumBer(22, 461, gObjUser.lpViewPlayer->MapPosX, 1);
		pDrawInterfaceNumBer(46, 461, gObjUser.lpViewPlayer->MapPosY, 1);

	}
}

// ============================================================= PARTY SEARCH

void Interface::DrawPartySettingsWindow()
{
	if (!this->Data[ePARTYSETTINGS_MAIN].OnShow)
	{
		return;
	}
	// ----
	float MainWidth = 230.0;
	float MainHeight = 313.0;
	float StartY = 50.0;
	float StartX = (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float MainCenter = StartX + (MainWidth / 3);
	float ButtonX = MainCenter - (29.0 / 2);
	// ----
	this->DrawGUI(ePARTYSETTINGS_MAIN, StartX, StartY + 2);
	this->DrawGUI(ePARTYSETTINGS_TITLE, StartX, StartY);
	StartY = this->DrawRepeatGUI(ePARTYSETTINGS_FRAME, StartX, StartY + 67.0, 16);
	this->DrawGUI(ePARTYSETTINGS_FOOTER, StartX, StartY);
	this->DrawGUI(ePARTYSETTINGS_CLOSE, StartX + MainWidth - this->Data[ePARTYSETTINGS_CLOSE].Width + 2, 49);
	// ----
	if (this->IsWorkZone(ePARTYSETTINGS_CLOSE))
	{
		DWORD Color = eGray100;
		// ----
		if (this->Data[ePARTYSETTINGS_CLOSE].OnClick)
		{
			Color = eGray150;
		}
		// ----
		this->DrawColoredGUI(ePARTYSETTINGS_CLOSE, this->Data[ePARTYSETTINGS_CLOSE].X, this->Data[ePARTYSETTINGS_CLOSE].Y, Color);
		this->DrawToolTip(this->Data[ePARTYSETTINGS_CLOSE].X + 5, this->Data[ePARTYSETTINGS_CLOSE].Y + 25, "Close");
	}
	// ----
	this->DrawFormat(eGold, StartX + 10, 56, 210, 3, "Party Search Settings");
	///////////////////////////////////////////ACTIVE SYSTEM///////////////////////////////////////////
	this->DrawFormat(eWhite, StartX + 40, this->Data[ePARTYSETTINGS_MAIN].Y + 33, 200, 1, "Active System");

	if (gPartySearchSettings.m_SystemActive == false)
	{
		this->DrawButton(ePARTYSETTINGS_SYSTEM_ACTIVE, ButtonX + 110, this->Data[ePARTYSETTINGS_MAIN].Y + 30, 0, 0);
	}
	else
	{
		this->DrawButton(ePARTYSETTINGS_SYSTEM_ACTIVE, ButtonX + 110, this->Data[ePARTYSETTINGS_MAIN].Y + 30, 0, 15);
	}
	this->DrawGUI(ePARTYSETTINGS_DIV, StartX, this->Data[ePARTYSETTINGS_MAIN].Y + 40); // �������� �������
	/////////////////////////////////////////ACTIVE SYSTEM END/////////////////////////////////////////

	/////////////////////////////////////////////MAX LEVEL/////////////////////////////////////////////
	this->DrawFormat(eWhite, StartX + 40, this->Data[ePARTYSETTINGS_MAIN].Y + 60, 200, 1, "Max Level");
	this->DrawGUI(ePARTYSETTINGS_DIV, StartX, this->Data[ePARTYSETTINGS_MAIN].Y + 67); // �������� �������

	this->DrawToolTip(StartX + 174, this->Data[ePARTYSETTINGS_MAIN].Y + 62, "%d", gPartySearchSettings.m_Level);

	if (gPartySearchSettings.m_SystemActive == 0)
	{
		this->DrawColoredButton(ePARTYSETTINGS_LEVEL_MINUS, StartX + 150, this->Data[ePARTYSETTINGS_MAIN].Y + 57, 0, 0, eGray150); // 
	}
	else
	{
		this->DrawButton(ePARTYSETTINGS_LEVEL_MINUS, StartX + 150, this->Data[ePARTYSETTINGS_MAIN].Y + 57, 0, 0); // 

		if (this->IsWorkZone(ePARTYSETTINGS_LEVEL_MINUS))
		{
			if (this->Data[ePARTYSETTINGS_LEVEL_MINUS].OnClick)
			{
				this->DrawButton(ePARTYSETTINGS_LEVEL_MINUS, StartX + 150, this->Data[ePARTYSETTINGS_MAIN].Y + 57, 0, 16);
			}
		}
	}

	if (gPartySearchSettings.m_SystemActive == 0)
	{
		this->DrawColoredButton(ePARTYSETTINGS_LEVEL_PLUS, StartX + 193, this->Data[ePARTYSETTINGS_MAIN].Y + 57, 0, 0, eGray150); //
	}
	else
	{
		this->DrawButton(ePARTYSETTINGS_LEVEL_PLUS, StartX + 193, this->Data[ePARTYSETTINGS_MAIN].Y + 57, 0, 0); //

		if (this->IsWorkZone(ePARTYSETTINGS_LEVEL_PLUS))
		{
			if (this->Data[ePARTYSETTINGS_LEVEL_PLUS].OnClick)
			{
				this->DrawButton(ePARTYSETTINGS_LEVEL_PLUS, StartX + 193, this->Data[ePARTYSETTINGS_MAIN].Y + 57, 0, 16);
			}
		}
	}

	///////////////////////////////////////////MAX LEVEL END///////////////////////////////////////////

	///////////////////////////////////////////////GUILD///////////////////////////////////////////////

	this->DrawFormat(eWhite, StartX + 40, this->Data[ePARTYSETTINGS_MAIN].Y + 87, 200, 1, "Only Guild");

	if (gPartySearchSettings.m_SystemActive)
	{
		if (gPartySearchSettings.m_OnlyGuild == false)
		{
			this->DrawButton(ePARTYSETTINGS_ONLY_GUILD, ButtonX + 110, this->Data[ePARTYSETTINGS_MAIN].Y + 83, 0, 0);
		}
		else
		{
			this->DrawButton(ePARTYSETTINGS_ONLY_GUILD, ButtonX + 110, this->Data[ePARTYSETTINGS_MAIN].Y + 83, 0, 15);
		}
	}
	else
	{
		this->DrawButton(ePARTYSETTINGS_ONLY_GUILD, ButtonX + 110, this->Data[ePARTYSETTINGS_MAIN].Y + 83, 0, 30);
	}

	pDrawGUI(0x7B5E, StartX + 30, this->Data[ePARTYSETTINGS_MAIN].Y + 100, 82.0, 2.0); // �������� ������ 1
	pDrawGUI(0x7B5E, StartX + 30 + 82, this->Data[ePARTYSETTINGS_MAIN].Y + 100, 82.0, 2.0); // �������� ������ 2

	this->DrawFormat(eWhite, StartX + 40, this->Data[ePARTYSETTINGS_MAIN].Y + 109, 200, 1, "Only One Class");

	if (gPartySearchSettings.m_SystemActive)
	{
		if (gPartySearchSettings.m_OneClass == false)
		{
			this->DrawButton(ePARTYSETTINGS_ONE_CLASS, ButtonX + 110, this->Data[ePARTYSETTINGS_MAIN].Y + 105, 0, 0);
		}
		else
		{
			this->DrawButton(ePARTYSETTINGS_ONE_CLASS, ButtonX + 110, this->Data[ePARTYSETTINGS_MAIN].Y + 105, 0, 15);
		}
	}
	else
	{
		this->DrawButton(ePARTYSETTINGS_ONE_CLASS, ButtonX + 110, this->Data[ePARTYSETTINGS_MAIN].Y + 105, 0, 30);
	}

	this->DrawGUI(ePARTYSETTINGS_DIV, StartX, this->Data[ePARTYSETTINGS_MAIN].Y + 115);// 94 // �������� �������
	/////////////////////////////////////////////GUILD END/////////////////////////////////////////////
	char szCharNames[7][32] =
	{
		"Dark Wizard",
		"Dard Knight",
		"Elf",
		"Magic Gladiator",
		"Dark Lord",
		"Summoner",
		"Rage Fighter"
	};

	int ObjectIDs[7] =
	{
		ePARTYSETTINGS_DARK_WIZARD,
		ePARTYSETTINGS_DARK_KNIGHT,
		ePARTYSETTINGS_ELF,
		ePARTYSETTINGS_MAGIC_GLADIATOR,
		ePARTYSETTINGS_DARK_LORD,
		ePARTYSETTINGS_SUMMONER,
		ePARTYSETTINGS_RAGE_FIGHTER
	};

	for (int i = 0; i<7; i++)
	{
		this->DrawFormat(eWhite, StartX + 40, this->Data[ePARTYSETTINGS_MAIN].Y + 135 + (i * 22), 200, 1, szCharNames[i]);

		bool ClassValue = 0;
		switch (i)
		{
		case 0:
			ClassValue = gPartySearchSettings.m_DarkWizard;
			break;
		case 1:
			ClassValue = gPartySearchSettings.m_DarkKnight;
			break;
		case 2:
			ClassValue = gPartySearchSettings.m_Elf;
			break;
		case 3:
			ClassValue = gPartySearchSettings.m_MagicGladiator;
			break;
		case 4:
			ClassValue = gPartySearchSettings.m_DarkLord;
			break;
		case 5:
			ClassValue = gPartySearchSettings.m_Summoner;
			break;
		case 6:
			ClassValue = gPartySearchSettings.m_RageFighter;
			break;
		}

		if (gPartySearchSettings.m_SystemActive)
		{
			if (ClassValue == false)
			{
				this->DrawButton(ObjectIDs[i], ButtonX + 110, this->Data[ePARTYSETTINGS_MAIN].Y + 131 + (i * 22), 0, 0);
			}
			else
			{
				this->DrawButton(ObjectIDs[i], ButtonX + 110, this->Data[ePARTYSETTINGS_MAIN].Y + 131 + (i * 22), 0, 15);
			}
		}
		else
		{
			this->DrawButton(ObjectIDs[i], ButtonX + 110, this->Data[ePARTYSETTINGS_MAIN].Y + 131 + (i * 22), 0, 30);
		}

		pDrawGUI(0x7B5E, StartX + 30, this->Data[ePARTYSETTINGS_MAIN].Y + 148 + (i * 22), 82.0, 2.0); // �������� ������ 1
		pDrawGUI(0x7B5E, StartX + 30 + 82, this->Data[ePARTYSETTINGS_MAIN].Y + 148 + (i * 22), 82.0, 2.0); // �������� ������ 2
	}

	this->DrawGUI(ePARTYSETTINGS_DIV, StartX, this->Data[ePARTYSETTINGS_MAIN].Y + 290); // �������� �������

	//if (gPartySearchSettings.m_SystemActive)
	//{
	this->DrawButton(ePARTYSETTINGS_OK, StartX + this->Data[ePARTYSETTINGS_MAIN].Width / 2 - this->Data[ePARTYSETTINGS_OK].Width / 2, this->Data[ePARTYSETTINGS_MAIN].Y + 310, 0, 0);

	if (this->IsWorkZone(ePARTYSETTINGS_OK))
	{
		int ScaleY = 30;
		// ----
		if (this->Data[ePARTYSETTINGS_OK].OnClick)
		{
			ScaleY = 60;
		}
		// ----
		this->DrawButton(ePARTYSETTINGS_OK, StartX + this->Data[ePARTYSETTINGS_MAIN].Width / 2 - this->Data[ePARTYSETTINGS_OK].Width / 2, this->Data[ePARTYSETTINGS_MAIN].Y + 310, 0, ScaleY);
	}
	//}

}
// ----------------------------------------------------------------------------------------------

bool Interface::EventPartySettingsWindow_Main(DWORD Event)
{
	this->EventPartySettingsWindow_Close(Event);
	this->EventPartySettingsWindow_All(Event);
	// ----
	// ----
	return true;
}
// ----------------------------------------------------------------------------------------------

bool Interface::EventPartySettingsWindow_All(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();

	if (!this->Data[ePARTYSETTINGS_MAIN].OnShow)
	{
		return false;
	}

	if (IsWorkZone(ePARTYSETTINGS_SYSTEM_ACTIVE))
	{
		DWORD Delay = (CurrentTick - this->Data[ePARTYSETTINGS_SYSTEM_ACTIVE].EventTick);

		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[ePARTYSETTINGS_SYSTEM_ACTIVE].OnClick = true;
			return true;
		}
		// ----
		this->Data[ePARTYSETTINGS_SYSTEM_ACTIVE].OnClick = false;
		// ----
		if (Delay < 500)
		{
			return false;
		}
		// ----
		this->Data[ePARTYSETTINGS_SYSTEM_ACTIVE].EventTick = GetTickCount();
		gPartySearchSettings.m_SystemActive ^= 1;

		for (int i = 0; i<7; i++)
		{
			gPartySearchSettings.m_SystemActive == true ? gPartySearchSettings.SetClassValue(i, true) : gPartySearchSettings.SetClassValue(i, false);
		}
	}

	if (IsWorkZone(ePARTYSETTINGS_LEVEL_MINUS))
	{
		if (gPartySearchSettings.m_SystemActive == 0)
		{
			return false;
		}

		DWORD Delay = (CurrentTick - this->Data[ePARTYSETTINGS_LEVEL_MINUS].EventTick);

		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[ePARTYSETTINGS_LEVEL_MINUS].OnClick = true;
			return false;
		}
		// ----
		this->Data[ePARTYSETTINGS_LEVEL_MINUS].OnClick = false;
		// ----
		if (Delay < 200)
		{
			return false;
		}
		// ----
		this->Data[ePARTYSETTINGS_LEVEL_MINUS].EventTick = GetTickCount();

		gPartySearchSettings.m_Level -= 10;
		if (gPartySearchSettings.m_Level <= 0)
		{
			gPartySearchSettings.m_Level = 0;
		}
	}

	if (IsWorkZone(ePARTYSETTINGS_LEVEL_PLUS))
	{
		if (gPartySearchSettings.m_SystemActive == 0)
		{
			return false;
		}

		DWORD Delay = (CurrentTick - this->Data[ePARTYSETTINGS_LEVEL_PLUS].EventTick);

		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[ePARTYSETTINGS_LEVEL_PLUS].OnClick = true;
			return false;
		}
		// ----
		this->Data[ePARTYSETTINGS_LEVEL_PLUS].OnClick = false;
		// ----
		if (Delay < 200)
		{
			return false;
		}
		// ----
		this->Data[ePARTYSETTINGS_LEVEL_PLUS].EventTick = GetTickCount();

		gPartySearchSettings.m_Level += 10;
		if (gPartySearchSettings.m_Level >= 400)
		{
			gPartySearchSettings.m_Level = 400;
		}
	}

	if (IsWorkZone(ePARTYSETTINGS_ONLY_GUILD))
	{
		DWORD Delay = (CurrentTick - this->Data[ePARTYSETTINGS_ONLY_GUILD].EventTick);

		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[ePARTYSETTINGS_ONLY_GUILD].OnClick = true;
			return true;
		}
		// ----
		this->Data[ePARTYSETTINGS_ONLY_GUILD].OnClick = false;
		// ----
		if (Delay < 500)
		{
			return false;
		}
		// ----
		this->Data[ePARTYSETTINGS_ONLY_GUILD].EventTick = GetTickCount();
		gPartySearchSettings.m_OnlyGuild ^= 1;
	}

	if (IsWorkZone(ePARTYSETTINGS_ONE_CLASS))
	{
		DWORD Delay = (CurrentTick - this->Data[ePARTYSETTINGS_ONE_CLASS].EventTick);

		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[ePARTYSETTINGS_ONE_CLASS].OnClick = true;
			return true;
		}
		// ----
		this->Data[ePARTYSETTINGS_ONE_CLASS].OnClick = false;
		// ----
		if (Delay < 500)
		{
			return false;
		}
		// ----
		this->Data[ePARTYSETTINGS_ONE_CLASS].EventTick = GetTickCount();
		gPartySearchSettings.m_OneClass ^= 1;

		for (int i = 0; i<7; i++)
		{
			gPartySearchSettings.m_OneClass == false ? gPartySearchSettings.SetClassValue(i, true) : gPartySearchSettings.SetClassValue(i, false);
		}
	}

	if (IsWorkZone(ePARTYSETTINGS_OK))
	{

		DWORD Delay = (CurrentTick - this->Data[ePARTYSETTINGS_OK].EventTick);

		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[ePARTYSETTINGS_OK].OnClick = true;
			return false;
		}
		// ----
		this->Data[ePARTYSETTINGS_OK].OnClick = false;
		// ----
		if (Delay < 500)
		{
			return false;
		}
		// ----
		this->Data[ePARTYSETTINGS_OK].EventTick = GetTickCount();
		gPartySearchSettings.CGSendPartySearchAdd();
		this->SwitchPartySettingsWindowState();
	}

	int ObjectIDs[7] =
	{
		ePARTYSETTINGS_DARK_WIZARD,
		ePARTYSETTINGS_DARK_KNIGHT,
		ePARTYSETTINGS_ELF,
		ePARTYSETTINGS_MAGIC_GLADIATOR,
		ePARTYSETTINGS_DARK_LORD,
		ePARTYSETTINGS_SUMMONER,
		ePARTYSETTINGS_RAGE_FIGHTER
	};

	for (int i = 0; i<7; i++)
	{
		if (IsWorkZone(ObjectIDs[i]))
		{
			DWORD Delay = (CurrentTick - this->Data[ObjectIDs[i]].EventTick);

			if (Event == WM_LBUTTONDOWN)
			{
				this->Data[ObjectIDs[i]].OnClick = true;
				return true;
			}
			// ----
			this->Data[ObjectIDs[i]].OnClick = false;
			// ----
			if (Delay < 500)
			{
				return false;
			}
			// ----
			this->Data[ObjectIDs[i]].EventTick = GetTickCount();
			gPartySearchSettings.ChangeClassValue(i);

			if (gPartySearchSettings.m_OneClass == true)
			{
				gPartySearchSettings.m_OneClass = false;
			}
		}
	}
	return false;
}

bool Interface::EventPartySettingsWindow_Close(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->Data[ePARTYSETTINGS_CLOSE].EventTick);
	// ----
	if (!this->Data[ePARTYSETTINGS_MAIN].OnShow || !IsWorkZone(ePARTYSETTINGS_CLOSE))
	{
		return false;
	}
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[ePARTYSETTINGS_CLOSE].OnClick = true;
		return true;
	}
	// ----
	this->Data[ePARTYSETTINGS_CLOSE].OnClick = false;
	// ----
	if (Delay < 500)
	{
		return false;
	}
	// ----
	this->Data[ePARTYSETTINGS_CLOSE].EventTick = GetTickCount();
	this->Data[ePARTYSETTINGS_MAIN].Close();
	// ----
	return false;
}
// ----------------------------------------------------------------------------------------------

void Interface::DrawPartySearchWindow()
{
	if (!this->Data[ePARTYSEARCH_MAIN].OnShow)
	{
		return;
	}
	// ----
	float MainWidth = 230.0;
	float MainHeight = 313.0;
	float StartY = 50.0;
	float StartX = (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float MainCenter = StartX + (MainWidth / 3);
	float ButtonX = MainCenter - (29.0 / 2);
	// ----
	this->DrawGUI(ePARTYSEARCH_MAIN, StartX, StartY + 2);
	this->DrawGUI(ePARTYSEARCH_TITLE, StartX, StartY);
	StartY = this->DrawRepeatGUI(ePARTYSEARCH_FRAME, StartX, StartY + 67.0, 16);
	this->DrawGUI(ePARTYSEARCH_FOOTER, StartX, StartY);
	this->DrawGUI(ePARTYSEARCH_CLOSE, StartX + MainWidth - this->Data[ePARTYSEARCH_CLOSE].Width + 2, 49);
	// ----
	if (this->IsWorkZone(ePARTYSEARCH_CLOSE))
	{
		DWORD Color = eGray100;
		// ----
		if (this->Data[ePARTYSEARCH_CLOSE].OnClick)
		{
			Color = eGray150;
		}
		// ----
		this->DrawColoredGUI(ePARTYSEARCH_CLOSE, this->Data[ePARTYSEARCH_CLOSE].X, this->Data[ePARTYSEARCH_CLOSE].Y, Color);
		this->DrawToolTip(this->Data[ePARTYSEARCH_CLOSE].X + 5, this->Data[ePARTYSEARCH_CLOSE].Y + 25, "Close");
	}
	// ----
	this->DrawFormat(eGold, StartX + 10, 60, 210, 3, "Party Search");
	// ----
	int x = GetPrivateProfileIntA("Graphics", "X", 0, "./Settings.ini");
	int y = GetPrivateProfileIntA("Graphics", "Y", 0, "./Settings.ini");
	// ----
	this->DrawFormat(eWhite, StartX + 20, this->Data[ePARTYSEARCH_MAIN].Y + 34, 20, 1, "Status:");

	if (gPartySearchSettings.m_SystemActive == false)
	{
		this->DrawFormat(eRed, StartX + 42, this->Data[ePARTYSEARCH_MAIN].Y + 34, 20, 1, "OFF");
	}
	else
	{
		this->DrawFormat(eShinyGreen, StartX + 42, this->Data[ePARTYSEARCH_MAIN].Y + 34, 20, 1, "ON");
	}

	// ----
	this->DrawGUI(ePARTYSETTINGS_DIV, StartX, this->Data[ePARTYSEARCH_MAIN].Y + 40); // �������� �������
	// ----
	this->DrawFormat(eWhite, StartX + 5, this->Data[ePARTYSEARCH_MAIN].Y + 56, 50, 3, "Player");
	// ----
	this->DrawFormat(eWhite, StartX + 45, this->Data[ePARTYSEARCH_MAIN].Y + 56, 50, 3, "Map");
	// ----
	this->DrawFormat(eWhite, StartX + 95, this->Data[ePARTYSEARCH_MAIN].Y + 56, 50, 3, "X");
	// ----
	this->DrawFormat(eWhite, StartX + 115, this->Data[ePARTYSEARCH_MAIN].Y + 56, 50, 3, "Y");
	// ----
	this->DrawFormat(eWhite, StartX + 140, this->Data[ePARTYSEARCH_MAIN].Y + 56, 50, 3, "Count");
	// ----
	this->DrawFormat(eWhite, StartX + 170, this->Data[ePARTYSEARCH_MAIN].Y + 56, 50, 3, "Join");
	// ----
	this->DrawGUI(ePARTYSETTINGS_DIV, StartX, this->Data[ePARTYSEARCH_MAIN].Y + 60); // �������� �������
	// ----
	if (gPartySearch.CountPages>1)
	{
		this->DrawFormat(eGold, StartX + 104, 379, 20, 3, "%d/%d", gPartySearch.Page + 1, gPartySearch.CountPages);
	}

	if (gPartySearch.Page + 1 > 1)
	{
		this->DrawButton(ePARTYSEARCH_LEFT, StartX + 73, 372, 0, 0);
	}

	if (gPartySearch.Page + 1 < gPartySearch.CountPages)
	{
		this->DrawButton(ePARTYSEARCH_RIGHT, StartX + 73 + 60, 372, 0, 0);
	}

	int DrawnItems = 0;

	for (int i = 0; i<gPartySearch.ListsCount; i++)
	{
		if (DrawnItems >= 10)
		{
			break;
		}

		PARTYLIST* info = gPartySearch.GetPartyList(i + (10 * gPartySearch.Page));

		if (info == 0)
		{
			continue;
		}

		pDrawGUI(92400, StartX + 10, this->Data[ePARTYSEARCH_MAIN].Y + 80 + (20 * i), 170, 21);

		this->DrawFormat(eYellow, StartX + 15, this->Data[ePARTYSEARCH_MAIN].Y + 86 + (20 * i), 50, 1, info->Name);

		this->DrawFormat(eWhite, StartX + 45, this->Data[ePARTYSEARCH_MAIN].Y + 86 + (20 * i), 50, 3, pGetMapName(info->Map));

		this->DrawFormat(eWhite, StartX + 95, this->Data[ePARTYSEARCH_MAIN].Y + 86 + (20 * i), 50, 3, "%d", info->X);

		this->DrawFormat(eWhite, StartX + 115, this->Data[ePARTYSEARCH_MAIN].Y + 86 + (20 * i), 50, 3, "%d", info->Y);

		this->DrawFormat(eWhite, StartX + 140, this->Data[ePARTYSEARCH_MAIN].Y + 86 + (20 * i), 50, 3, "%d / 5", info->Count);

		pDrawGUI(92401, StartX + 178, this->Data[ePARTYSEARCH_MAIN].Y + 80 + (i * 20), 22, 19);

		if (info->ButtonActive == true)
		{
			pDrawButton(0x7AA4, StartX + 203, this->Data[ePARTYSEARCH_MAIN].Y + 82 + (i * 20), 16, 15, 0, 0);
		}

		int X = StartX + 203;
		int Y = this->Data[ePARTYSEARCH_MAIN].Y + 82 + (i * 20);
		int MaxX = X + 16;
		int MaxY = Y + 15;

		if (info->ButtonActive == true)
		{
			if (IsWorkZone2(X, Y, MaxX, MaxY))
			{
				pDrawColorButton(0x7AA4, X, Y, 16, 15, 0, 16, eGray100);
			}
		}

		DrawnItems++;
	}

	DrawnItems = 0;

	for (int i = 0; i<gPartySearch.ListsCount; i++)
	{
		if (DrawnItems >= 10)
		{
			break;
		}

		PARTYLIST* info = gPartySearch.GetPartyList(i + (10 * gPartySearch.Page));

		if (info == 0)
		{
			continue;
		}

		int X = StartX + 178;
		int Y = this->Data[ePARTYSEARCH_MAIN].Y + 80 + (i * 20);
		int MaxX = X + 22;
		int MaxY = Y + 19;

		if (IsWorkZone2(X, Y, MaxX, MaxY))
		{
			char szText[2048];
			sprintf(szText, "Need to Party:\n_____________________\nLevel:%d", info->Level);

			if (info->DarkWizard == true)
			{
				strcat(szText, "\nDark Wizard");
			}
			if (info->DarkKnight == true)
			{
				strcat(szText, "\nDark Knight");
			}
			if (info->Elf == true)
			{
				strcat(szText, "\nElf");
			}
			if (info->MagicGladiator == true)
			{
				strcat(szText, "\nMagic Gladiator");
			}
			if (info->DarkLord == true)
			{
				strcat(szText, "\nDark Lord");
			}
			if (info->Summoner == true)
			{
				strcat(szText, "\nSummoner");
			}
			if (info->RageFighter == true)
			{
				strcat(szText, "\nRage Fighter");
			}
			if (info->OnlyGuild == true)
			{
				strcat(szText, "\nOnly Guild");
			}

			strcat(szText, "\n_____________________");

			//this->DrawToolTipEx(eWhite, StartX + 230, this->Data[ePARTYSEARCH_MAIN].Y + 62 + (i * 20), 100, 30, 3, szText);
			glColor4f(0.0, 0.0, 0.0, 0.8);
			pDrawBarForm((float)(StartX + 230), (float)(this->Data[ePARTYSEARCH_MAIN].Y + 62 + (i * 20)), 100.0f, 110.0f, 0.0f, 0);


			this->DrawFormatx(eWhite, StartX + 230, this->Data[ePARTYSEARCH_MAIN].Y + 62 + (i * 20), 100, 3, szText);
		}

		DrawnItems++;
	}

	if (gPartySearch.Page + 1 > 1)
	{
		if (IsWorkZone(ePARTYSEARCH_LEFT))
		{
			if (this->Data[ePARTYSEARCH_LEFT].OnClick)
			{
				this->DrawButton(ePARTYSEARCH_LEFT, StartX + 73, 372, 0, 46);
				return;
			}
			this->DrawButton(ePARTYSEARCH_LEFT, StartX + 73, 372, 0, 23);
		}
	}
	if (gPartySearch.Page + 1 < gPartySearch.CountPages)
	{
		if (IsWorkZone(ePARTYSEARCH_RIGHT))
		{
			if (this->Data[ePARTYSEARCH_RIGHT].OnClick)
			{
				this->DrawButton(ePARTYSEARCH_RIGHT, StartX + 73 + 60, 372, 0, 46);
				return;
			}
			this->DrawButton(ePARTYSEARCH_RIGHT, StartX + 73 + 60, 372, 0, 23);
		}
	}
}

void Interface::EventPartySearchWindow_All(DWORD Event)
{
	float StartX = (MAX_WIN_WIDTH / 2) - (230.0 / 2);
	DWORD CurrentTick = GetTickCount();
	if (!this->Data[ePARTYSEARCH_MAIN].OnShow)
	{
		return;
	}

	if (IsWorkZone(ePARTYSEARCH_CLOSE))
	{
		DWORD Delay = (CurrentTick - this->Data[ePARTYSEARCH_CLOSE].EventTick);

		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[ePARTYSEARCH_CLOSE].OnClick = true;
			return;
		}
		// ----
		this->Data[ePARTYSEARCH_CLOSE].OnClick = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[ePARTYSEARCH_CLOSE].EventTick = GetTickCount();
		this->SwitchPartySearchWindowState();
	}
	if (IsWorkZone(ePARTYSEARCH_LEFT) && gPartySearch.Page + 1 > 1)
	{
		DWORD Delay = (CurrentTick - this->Data[ePARTYSEARCH_LEFT].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[ePARTYSEARCH_LEFT].OnClick = true;
			return;
		}
		// ----
		this->Data[ePARTYSEARCH_LEFT].OnClick = false;
		// ----
		if (Delay < 100)
		{
			return;
		}
		// ----
		this->Data[ePARTYSEARCH_LEFT].EventTick = GetTickCount();
		// ----
		gPartySearch.Page--;
	}
	if (IsWorkZone(ePARTYSEARCH_RIGHT) && gPartySearch.Page + 1 < gPartySearch.CountPages)
	{
		DWORD Delay = (CurrentTick - this->Data[ePARTYSEARCH_RIGHT].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[ePARTYSEARCH_RIGHT].OnClick = true;
			return;
		}
		// ----
		this->Data[ePARTYSEARCH_RIGHT].OnClick = false;
		// ----
		if (Delay < 100)
		{
			return;
		}
		// ----
		this->Data[ePARTYSEARCH_RIGHT].EventTick = GetTickCount();
		// ----
		gPartySearch.Page++;
	}

	int DrawnItems = 0;

	for (int i = 0; i<gPartySearch.ListsCount; i++)
	{
		if (DrawnItems >= 10)
		{
			break;
		}
		if (IsWorkZone2(StartX + 203, this->Data[ePARTYSEARCH_MAIN].Y + 82 + (i * 20), StartX + 203 + 16, this->Data[ePARTYSEARCH_MAIN].Y + 82 + (i * 20) + 15))
		{
			DWORD Delay = (CurrentTick - this->Data[ePARTYSEARCH_RIGHT].EventTick);
			// ----
			if (Event == WM_LBUTTONDOWN)
			{
				this->Data[ePARTYSEARCH_RIGHT].OnClick = true;
				return;
			}
			// ----
			this->Data[ePARTYSEARCH_RIGHT].OnClick = false;
			// ----
			if (Delay < 100)
			{
				return;
			}
			// ----
			if (gPartySearch.gPartyList[i + (10 * gPartySearch.Page)].ButtonActive == false)
			{
				return;
			}
			// ----
			this->Data[ePARTYSEARCH_RIGHT].EventTick = GetTickCount();
			// ----
			gPartySearch.SendPartyRequest(i + (10 * gPartySearch.Page));
		}
	}
}

//=========================================================== LUCKYWHELL

void Interface::DrawLuckyWheel()
{
	if (!this->Data[eLuckyWheelMain].OnShow)
	{
		return;
	}
	// ---
	float MainWidth = 312.0;
	float MainHeight = 292.0;
	float StartY = ((MAX_WIN_HEIGHT - 51) / 2) - (MainHeight / 2);
	float StartX = (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float MainCenter = StartX + (MainWidth / 3);
	float ButtonX = MainCenter - (float)(29.0 / 2);
	//--
	this->Data[eLuckyWheelPanel].MaxX = StartX + MainWidth;
	this->Data[eLuckyWheelPanel].MaxY = StartY + MainHeight;

	gCentral.PrintDropBox(StartX, StartY, MainWidth, MainHeight, 0, 0);

	this->DrawFormat(eGold, (int)StartX + 50, (int)StartY + 10, 210, 3, "LuckyWheel");
	// ---
	//	pDrawGUI(0x7A5A, 145, 55, 312, 292); //1
	//
	pDrawGUI(0x9326, 180, 100, 70, 57); //1
	pDrawGUI(0x9326, 250, 100, 70, 57); //2
	pDrawGUI(0x9326, 320, 100, 70, 57); //3
	pDrawGUI(0x9326, 390, 100, 70, 57); //4
	//
	pDrawGUI(0x9326, 390, 157, 70, 57); //5
	pDrawGUI(0x9326, 390, 214, 70, 57); //6
	//
	pDrawGUI(0x9326, 390, 271, 70, 57); //7
	pDrawGUI(0x9326, 320, 271, 70, 57); //8
	pDrawGUI(0x9326, 250, 271, 70, 57); //9
	pDrawGUI(0x9326, 180, 271, 70, 57); //10
	//
	pDrawGUI(0x9326, 180, 157, 70, 57); //11
	pDrawGUI(0x9326, 180, 214, 70, 57); //12

	if (this->LuckyWheelNumber >= 0)
	{
		pSetBlend(true);
		glColor4f(1.0, 1.0, 0.0, 0.3);
		switch (LuckyWheelNumber)
		{
		case 0:
			pDrawBarForm(180, 100, 70, 57, 0, 0);
			break;
		case 1:
			pDrawBarForm(250, 100, 70, 57, 0, 0);
			break;
		case 2:
			pDrawBarForm(320, 100, 70, 57, 0, 0);
			break;
		case 3:
			pDrawBarForm(390, 100, 70, 57, 0, 0);
			break;
		case 4:
			pDrawBarForm(390, 157, 70, 57, 0, 0);
			break;
		case 5:
			pDrawBarForm(390, 214, 70, 57, 0, 0);
			break;
		case 6:
			pDrawBarForm(390, 271, 70, 57, 0, 0);
			break;
		case 7:
			pDrawBarForm(320, 271, 70, 57, 0, 0);
			break;
		case 8:
			pDrawBarForm(250, 271, 70, 57, 0, 0);
			break;
		case 9:
			pDrawBarForm(180, 271, 70, 57, 0, 0);
			break;
		case 10:
			pDrawBarForm(180, 157, 70, 57, 0, 0);
			break;
		case 11:
			pDrawBarForm(180, 214, 70, 57, 0, 0);
			break;
		}
		pGLSwitchBlend();
		glColor3f(1.0, 1.0, 1.0);
	}

	if (this->StartRoll >= 1)
	{
		pSetBlend(true);
		glColor4f(1.0, 1.0, 0.0, 0.3);
		int roll = rand() % 12;
		switch (roll)
		{
		case 0:
			pDrawBarForm(180, 100, 70, 57, 0, 0);
			break;
		case 1:
			pDrawBarForm(250, 100, 70, 57, 0, 0);
			break;
		case 2:
			pDrawBarForm(320, 100, 70, 57, 0, 0);
			break;
		case 3:
			pDrawBarForm(390, 100, 70, 57, 0, 0);
			break;
		case 4:
			pDrawBarForm(390, 157, 70, 57, 0, 0);
			break;
		case 5:
			pDrawBarForm(390, 214, 70, 57, 0, 0);
			break;
		case 6:
			pDrawBarForm(390, 271, 70, 57, 0, 0);
			break;
		case 7:
			pDrawBarForm(320, 271, 70, 57, 0, 0);
			break;
		case 8:
			pDrawBarForm(250, 271, 70, 57, 0, 0);
			break;
		case 9:
			pDrawBarForm(180, 271, 70, 57, 0, 0);
			break;
		case 10:
			pDrawBarForm(180, 157, 70, 57, 0, 0);
			break;
		case 11:
			pDrawBarForm(180, 214, 70, 57, 0, 0);
			break;
		}
		pGLSwitchBlend();
		glColor3f(1.0, 1.0, 1.0);
	}

	DrawItemIMG(190, 100, 70, 50, ITEM(gLuckyWheel.m_LuckyWheelInfo[0].ItemType, gLuckyWheel.m_LuckyWheelInfo[0].ItemIndex), SET_ITEMOPT_LEVEL(gLuckyWheel.m_LuckyWheelInfo[0].Level), gLuckyWheel.m_LuckyWheelInfo[0].Exc, 0, 0);
	DrawItemIMG(260, 100, 65, 47, ITEM(gLuckyWheel.m_LuckyWheelInfo[1].ItemType, gLuckyWheel.m_LuckyWheelInfo[1].ItemIndex), SET_ITEMOPT_LEVEL(gLuckyWheel.m_LuckyWheelInfo[1].Level), gLuckyWheel.m_LuckyWheelInfo[1].Exc, 0, 0);
	DrawItemIMG(330, 100, 65, 47, ITEM(gLuckyWheel.m_LuckyWheelInfo[2].ItemType, gLuckyWheel.m_LuckyWheelInfo[2].ItemIndex), SET_ITEMOPT_LEVEL(gLuckyWheel.m_LuckyWheelInfo[2].Level), gLuckyWheel.m_LuckyWheelInfo[2].Exc, 0, 0);
	DrawItemIMG(400, 100, 65, 50, ITEM(gLuckyWheel.m_LuckyWheelInfo[3].ItemType, gLuckyWheel.m_LuckyWheelInfo[3].ItemIndex), SET_ITEMOPT_LEVEL(gLuckyWheel.m_LuckyWheelInfo[3].Level), gLuckyWheel.m_LuckyWheelInfo[3].Exc, 0, 0);

	DrawItemIMG(400, 157, 65, 50, ITEM(gLuckyWheel.m_LuckyWheelInfo[4].ItemType, gLuckyWheel.m_LuckyWheelInfo[4].ItemIndex), SET_ITEMOPT_LEVEL(gLuckyWheel.m_LuckyWheelInfo[4].Level), gLuckyWheel.m_LuckyWheelInfo[4].Exc, 0, 0);
	DrawItemIMG(400, 214, 63, 50, ITEM(gLuckyWheel.m_LuckyWheelInfo[5].ItemType, gLuckyWheel.m_LuckyWheelInfo[5].ItemIndex), SET_ITEMOPT_LEVEL(gLuckyWheel.m_LuckyWheelInfo[5].Level), gLuckyWheel.m_LuckyWheelInfo[5].Exc, 0, 0);

	DrawItemIMG(400, 271, 70, 45, ITEM(gLuckyWheel.m_LuckyWheelInfo[6].ItemType, gLuckyWheel.m_LuckyWheelInfo[6].ItemIndex), SET_ITEMOPT_LEVEL(gLuckyWheel.m_LuckyWheelInfo[6].Level), gLuckyWheel.m_LuckyWheelInfo[6].Exc, 0, 0);
	DrawItemIMG(330, 271, 70, 45, ITEM(gLuckyWheel.m_LuckyWheelInfo[7].ItemType, gLuckyWheel.m_LuckyWheelInfo[7].ItemIndex), SET_ITEMOPT_LEVEL(gLuckyWheel.m_LuckyWheelInfo[7].Level), gLuckyWheel.m_LuckyWheelInfo[7].Exc, 0, 0);
	DrawItemIMG(260, 271, 70, 45, ITEM(gLuckyWheel.m_LuckyWheelInfo[8].ItemType, gLuckyWheel.m_LuckyWheelInfo[8].ItemIndex), SET_ITEMOPT_LEVEL(gLuckyWheel.m_LuckyWheelInfo[8].Level), gLuckyWheel.m_LuckyWheelInfo[8].Exc, 0, 0);
	DrawItemIMG(190, 271, 70, 45, ITEM(gLuckyWheel.m_LuckyWheelInfo[9].ItemType, gLuckyWheel.m_LuckyWheelInfo[9].ItemIndex), SET_ITEMOPT_LEVEL(gLuckyWheel.m_LuckyWheelInfo[9].Level), gLuckyWheel.m_LuckyWheelInfo[9].Exc, 0, 0);

	DrawItemIMG(190, 157, 70, 50, ITEM(gLuckyWheel.m_LuckyWheelInfo[10].ItemType, gLuckyWheel.m_LuckyWheelInfo[10].ItemIndex), SET_ITEMOPT_LEVEL(gLuckyWheel.m_LuckyWheelInfo[10].Level), gLuckyWheel.m_LuckyWheelInfo[10].Exc, 0, 0);
	DrawItemIMG(190, 214, 70, 50, ITEM(gLuckyWheel.m_LuckyWheelInfo[11].ItemType, gLuckyWheel.m_LuckyWheelInfo[11].ItemIndex), SET_ITEMOPT_LEVEL(gLuckyWheel.m_LuckyWheelInfo[11].Level), gLuckyWheel.m_LuckyWheelInfo[11].Exc, 0, 0);

	//this->DrawFormat(eWhite, 270, 165, 50.0f, 1.0f, "You Wind!");
	if (this->LuckyWheelNumber >= 0)
	{
		DrawItemIMG(297, 160, 50, 50, ITEM(gLuckyWheel.m_LuckyWheelInfo[this->LuckyWheelNumber].ItemType, gLuckyWheel.m_LuckyWheelInfo[this->LuckyWheelNumber].ItemIndex), gLuckyWheel.m_LuckyWheelInfo[this->LuckyWheelNumber].Level, gLuckyWheel.m_LuckyWheelInfo[this->LuckyWheelNumber].Exc, 0, 0);
	}

	// ----
	if (IsWorkZone(eLuckyWheel_CLOSE))
	{
		if (this->Data[eLuckyWheel_CLOSE].OnClick)
		{
			PlayBuffer(25, 0, 0);
			gInterface.DrawButtonRender(eLuckyWheel_CLOSE, StartX + (MainWidth / 2) - (59 / 2), StartY + MainHeight - 32, 0, 28);
		}
		else
		{
			gInterface.DrawButtonRender(eLuckyWheel_CLOSE, StartX + (MainWidth / 2) - (59 / 2), StartY + MainHeight - 32, 0, 0);
		}
	}
	else
	{
		gInterface.DrawButtonRender(eLuckyWheel_CLOSE, StartX + (MainWidth / 2) - (59 / 2), StartY + MainHeight - 32, 0, 0);
	}
	gInterface.DrawFormat(eWhite, StartX + (MainWidth / 2) - (59 / 2), StartY + MainHeight - 25, 59, 3, "Close");
	// ----

	gInterface.DrawFormat(eWhite, 264, 220, 40, 1, "WC:");
	gInterface.DrawFormat(eGold, 280, 220, 40, 1, "%d", gLuckyWheel.CostWcoinC);

	gInterface.DrawFormat(eWhite, 309, 220, 40, 1, "WP:");
	gInterface.DrawFormat(eGold, 325, 220, 40, 1, "%d", gLuckyWheel.CostWcoinP);

	gInterface.DrawFormat(eWhite, 354, 220, 40, 1, "GP:");
	gInterface.DrawFormat(eGold, 370, 220, 40, 1, "%d", gLuckyWheel.CostGoblin);

	DrawGUI(eLuckyWheelStart, 265, 230);
	this->DrawFormat(eWhite, 305, 240, 50.0f, 1.0f, "START");

	if (IsWorkZone(eLuckyWheelStart))
	{
		DWORD Color = eGray100;
		// ----
		if (this->Data[eLuckyWheelStart].OnClick)
		{
			Color = eGray150;
		}
		// ----
		this->DrawColoredGUI(eLuckyWheelStart, this->Data[eLuckyWheelStart].X, this->Data[eLuckyWheelStart].Y, Color);
	}
}

void Interface::EventLuckyWheelWindow_Close(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();

	if (!this->Data[eLuckyWheelMain].OnShow)
	{
		return;
	}

	if (this->IsWorkZone(eLuckyWheel_CLOSE))
	{
		DWORD Delay = (CurrentTick - this->Data[eLuckyWheel_CLOSE].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eLuckyWheel_CLOSE].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eLuckyWheel_CLOSE].OnClick = false;
		// ----
		if (Delay < 30000)
		{
			return;
		}
		// ----
		this->Data[eLuckyWheel_CLOSE].EventTick = GetTickCount();
		pSetCursorFocus = false;
		gInterface.Data[eLuckyWheelMain].OnShow = false;
	}
}

void Interface::EventLuckyWheel_Main(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();

	if (!this->Data[eLuckyWheelMain].OnShow)
	{
		return;
	}

	if (this->IsWorkZone(eLuckyWheelStart))
	{
		DWORD Delay = (CurrentTick - this->Data[eLuckyWheelStart].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eLuckyWheelStart].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eLuckyWheelStart].OnClick = false;
		// ----
		if (Delay < 30000)
		{
			return;
		}
		// ----
		this->Data[eLuckyWheelStart].EventTick = GetTickCount();
		pSetCursorFocus = false;

		if (gLuckyWheel.CostWcoinC > 0)
		{
			if (Coin1 < gLuckyWheel.CostWcoinC)
			{
				return;
			}
		}

		if (gLuckyWheel.CostWcoinP > 0)
		{
			if (Coin2 < gLuckyWheel.CostWcoinP)
			{
				return;
			}
		}

		if (gLuckyWheel.CostGoblin > 0)
		{
			if (Coin3 < gLuckyWheel.CostGoblin)
			{
				return;
			}
		}
		//Func
		UP_SEND_REQ pMsg;
		pMsg.h.set(0xF3, 0xF1, sizeof(pMsg));
		DataSend((BYTE*)&pMsg, pMsg.h.size);
		StartRoll = 1;
	}
}

