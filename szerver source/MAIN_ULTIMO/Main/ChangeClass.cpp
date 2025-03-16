#include "StdAfx.h"
#include "ChangeClass.h"
#include "User.h"
#include "Protocol.h"
#include "Interface.h"
#include "PrintPlayer.h"
#include "Central.h"
#include "Protect.h"
#include "Defines.h"
// -------------------------------------------------------------------------------

CChangeClass gChangeClass;
// -------------------------------------------------------------------------------

CChangeClass::CChangeClass()
{

}
// -------------------------------------------------------------------------------

CChangeClass::~CChangeClass()
{
	// ----
}
// -------------------------------------------------------------------------------

bool CChangeClass::EventChange_SelectAll(DWORD Event)
{
	this->EventChangeWindow_Close(Event);
	this->EventChangeWindow_DW(Event);
	this->EventChangeWindow_DK(Event);
	this->EventChangeWindow_EL(Event);
	this->EventChangeWindow_MG(Event);
	if (gProtect.m_MainInfo.CustomInterfaceType == 0 || gProtect.m_MainInfo.CustomInterfaceType >= 2)
	{
		this->EventChangeWindow_DL(Event);
	}
	if (gProtect.m_MainInfo.CustomInterfaceType == 0 || gProtect.m_MainInfo.CustomInterfaceType >= 3)
	{
		this->EventChangeWindow_SU(Event);
		this->EventChangeWindow_RF(Event);
	}
	return true;
}
// -------- AREA DE PANELES ---------------------------------------------AREA PANELES

void CChangeClass::DrawChangeWindow()
{
	if (!gInterface.Data[eCHANGE_MAIN].OnShow)
	{
		return;
	}

	this->ChangeButtons[0] = 1;
	this->ChangeButtons[1] = 1;
	this->ChangeButtons[2] = 1;
	this->ChangeButtons[3] = 1;
	if (gProtect.m_MainInfo.CustomInterfaceType == 0 || gProtect.m_MainInfo.CustomInterfaceType >= 2)
	{
		this->ChangeButtons[4] = 1;
	}
	if (gProtect.m_MainInfo.CustomInterfaceType == 0 || gProtect.m_MainInfo.CustomInterfaceType >= 3)
	{
		this->ChangeButtons[5] = 1;
		this->ChangeButtons[6] = 1;
	}

	float MainWidth = 230.0;
	float MainHeight = 360.0;
	float StartY = ((MAX_WIN_HEIGHT - 51) / 2) - (MainHeight / 2);
	float StartX = (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float MainCenter = StartX + (MainWidth / 3);
	float ButtonX = MainCenter - (float)(29.0 / 2);
	//--
	gInterface.Data[eCHANGE_MAIN].MaxX = StartX + MainWidth;
	gInterface.Data[eCHANGE_MAIN].MaxY = StartY + MainHeight;

	gCentral.PrintDropBox(StartX, StartY, MainWidth, MainHeight, 0, 0);

	gInterface.DrawFormat(eGold, (int)StartX + 10, (int)StartY + 10, 210, 3, "Change Class System");

	//-------------------------
	gInterface.DrawFormat(eGold, (int)StartX + 10, (int)StartY + 35, 210, 3, "Choose Class!");
	//--------------------------

	pDrawGUI(71520, StartX + (MainWidth / 2) - (200 / 2), StartY + 75, 200, 1); //-- Divisor

	float CurrentMove;
	int BtCount = -1;
	int BtStart = StartY + 88;

	int ObjectIDs[4] =
	{
		eCHANGEDW_FINISH,
		eCHANGEDK_FINISH,
		eCHANGEELF_FINISH,
		eCHANGEMG_FINISH,
	};

	for (int n = 0; n < 4; n++)
	{
		if (ChangeButtons[n] == 1)
		{
			BtCount++;
		}
		else
		{
			continue;
		}

		CurrentMove = 0.0;
		if (gInterface.IsWorkZone(ObjectIDs[n]))
		{
			if (gInterface.Data[ObjectIDs[n]].OnClick)
			{
				PlayBuffer(25, 0, 0);
				CurrentMove = 30.5f;
			}
		}
		gInterface.DrawButton(ObjectIDs[n], StartX + (MainWidth / 2) - (216 / 2), BtStart + (33.0f * BtCount), 0, CurrentMove);
		gInterface.DrawFormat(eWhite, StartX + (MainWidth / 2) - (216 / 2), BtStart + (33.0f * BtCount) + 9, 108, 3, gCustomMessage.GetMessage((n == 4) ? 44 : 69 + n));
	}

	// ======================================================================================

	float CurrentMove2;
	int BtCount2 = -1;
	int BtStart2 = StartY + 88;

	int ObjectIDs2[3] =
	{
		eCHANGEDL_FINISH,
		eCHANGESU_FINISH,
		eCHANGERF_FINISH,
	};

	for (int i = 0; i < 3; i++)
	{
		if (ChangeButtons[i] == 1)
		{
			BtCount2++;
		}
		else
		{
			continue;
		}

		CurrentMove2 = 0.0;
		if (gInterface.IsWorkZone(ObjectIDs2[i]))
		{
			if (gInterface.Data[ObjectIDs2[i]].OnClick)
			{
				PlayBuffer(25, 0, 0);
				CurrentMove2 = 30.5f;
			}
		}
		gInterface.DrawButton(ObjectIDs2[i], StartX + (MainWidth / 2) - (108 / 2) + 54, BtStart2 + (33.0f * BtCount2), 0, CurrentMove2);
		gInterface.DrawFormat(eWhite, StartX + (MainWidth / 2) - (108 / 2) + 54, BtStart2 + (33.0f * BtCount2) + 9, 108, 3, gCustomMessage.GetMessage((i == 3) ? 44 : 73 + i));
	}
	// ======================================================================================

	pDrawGUI(71520, StartX + (MainWidth / 2) - (200 / 2), StartY + MainHeight - 40, 200, 1); //-- Divisor

	if (gInterface.IsWorkZone(eMenu_CLOSE))
	{
		if (gInterface.Data[eMenu_CLOSE].OnClick)
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
// -------
// ----- AREA DE CLOSE ----------------------------------------------------AREA CLOSE
bool CChangeClass::EventChangeWindow_Close(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - gInterface.Data[eMenu_CLOSE].EventTick);
	// ----
	if (!gInterface.Data[eCHANGE_MAIN].OnShow || !gInterface.IsWorkZone(eMenu_CLOSE))
	{
		return false;
	}
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		gInterface.Data[eMenu_CLOSE].OnClick = true;
		return true;
	}
	// ----
	gInterface.Data[eMenu_CLOSE].OnClick = false;
	// ----
	if (Delay < 500)
	{
		return false;
	}
	// ----
	gInterface.Data[eMenu_CLOSE].EventTick = GetTickCount();
	this->CloseChangeWindow();
	if (gProtect.m_MainInfo.CustomInterfaceType != 3 || gProtect.m_MainInfo.CustomInterfaceType != 4)
	{
		pSetCursorFocus = false;
	}
	// ----
	return false;
}
// ----

// -----------AREA DE SELECT--------------------------------------------------AREA SELECT
bool CChangeClass::EventChangeWindow_DW(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - gInterface.Data[eCHANGEDW_FINISH].EventTick);
	// ----
	if (!gInterface.Data[eCHANGE_MAIN].OnShow || !gInterface.IsWorkZone(eCHANGEDW_FINISH))
	{
		return false;
	}
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		gInterface.Data[eCHANGEDW_FINISH].OnClick = true;
		return true;
	}
	// ----
	gInterface.Data[eCHANGEDW_FINISH].OnClick = false;
	// ----
	if (Delay < 500)
	{
		return false;
	}
	// ----
	gInterface.Data[eCHANGEDW_FINISH].EventTick = GetTickCount();
	gChangeClass.SelectClass(0);
	// ----
	return false;
}
// ----
bool CChangeClass::EventChangeWindow_DK(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - gInterface.Data[eCHANGEDK_FINISH].EventTick);
	// ----
	if (!gInterface.Data[eCHANGE_MAIN].OnShow || !gInterface.IsWorkZone(eCHANGEDK_FINISH))
	{
		return false;
	}
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		gInterface.Data[eCHANGEDK_FINISH].OnClick = true;
		return true;
	}
	// ----
	gInterface.Data[eCHANGEDK_FINISH].OnClick = false;
	// ----
	if (Delay < 500)
	{
		return false;
	}
	// ----
	gInterface.Data[eCHANGEDK_FINISH].EventTick = GetTickCount();
	gChangeClass.SelectClass(1);
	// ----
	return false;
}
// ----
bool CChangeClass::EventChangeWindow_EL(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - gInterface.Data[eCHANGEELF_FINISH].EventTick);
	// ----
	if (!gInterface.Data[eCHANGE_MAIN].OnShow || !gInterface.IsWorkZone(eCHANGEELF_FINISH))
	{
		return false;
	}
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		gInterface.Data[eCHANGEELF_FINISH].OnClick = true;
		return true;
	}
	// ----
	gInterface.Data[eCHANGEELF_FINISH].OnClick = false;
	// ----
	if (Delay < 500)
	{
		return false;
	}
	// ----
	gInterface.Data[eCHANGEELF_FINISH].EventTick = GetTickCount();
	gChangeClass.SelectClass(2);
	// ----
	return false;
}
// ----
bool CChangeClass::EventChangeWindow_MG(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - gInterface.Data[eCHANGEMG_FINISH].EventTick);
	// ----
	if (!gInterface.Data[eCHANGE_MAIN].OnShow || !gInterface.IsWorkZone(eCHANGEMG_FINISH))
	{
		return false;
	}
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		gInterface.Data[eCHANGEMG_FINISH].OnClick = true;
		return true;
	}
	// ----
	gInterface.Data[eCHANGEMG_FINISH].OnClick = false;
	// ----
	if (Delay < 500)
	{
		return false;
	}
	// ----
	gInterface.Data[eCHANGEMG_FINISH].EventTick = GetTickCount();
	gChangeClass.SelectClass(3);
	// ----
	return false;
}
// ----
bool CChangeClass::EventChangeWindow_DL(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - gInterface.Data[eCHANGEDL_FINISH].EventTick);
	// ----
	if (!gInterface.Data[eCHANGE_MAIN].OnShow || !gInterface.IsWorkZone(eCHANGEDL_FINISH))
	{
		return false;
	}
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		gInterface.Data[eCHANGEDL_FINISH].OnClick = true;
		return true;
	}
	// ----
	gInterface.Data[eCHANGEDL_FINISH].OnClick = false;
	// ----
	if (Delay < 500)
	{
		return false;
	}
	// ----
	gInterface.Data[eCHANGEDL_FINISH].EventTick = GetTickCount();
	gChangeClass.SelectClass(4);
	// ----
	return false;
}
// ----
bool CChangeClass::EventChangeWindow_SU(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - gInterface.Data[eCHANGESU_FINISH].EventTick);
	// ----
	if (!gInterface.Data[eCHANGE_MAIN].OnShow || !gInterface.IsWorkZone(eCHANGESU_FINISH))
	{
		return false;
	}
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		gInterface.Data[eCHANGESU_FINISH].OnClick = true;
		return true;
	}
	// ----
	gInterface.Data[eCHANGESU_FINISH].OnClick = false;
	// ----
	if (Delay < 500)
	{
		return false;
	}
	// ----
	gInterface.Data[eCHANGESU_FINISH].EventTick = GetTickCount();
	gChangeClass.SelectClass(5);
	// ----
	return false;
}
// ----
bool CChangeClass::EventChangeWindow_RF(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - gInterface.Data[eCHANGERF_FINISH].EventTick);
	// ----
	if (!gInterface.Data[eCHANGE_MAIN].OnShow || !gInterface.IsWorkZone(eCHANGERF_FINISH))
	{
		return false;
	}
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		gInterface.Data[eCHANGERF_FINISH].OnClick = true;
		return true;
	}
	// ----
	gInterface.Data[eCHANGERF_FINISH].OnClick = false;
	// ----
	if (Delay < 500)
	{
		return false;
	}
	// ----
	gInterface.Data[eCHANGERF_FINISH].EventTick = GetTickCount();
	gChangeClass.SelectClass(6);
	// ----
	return false;
}
// ----
// -------------------------------------------------------------------------------

void CChangeClass::SelectClass(int numclass)
{
	CHANGE_REQ pRequest;
	pRequest.h.set(0xF3, 0xD6, sizeof(pRequest));
	pRequest.numclass = numclass;
	DataSend((LPBYTE)&pRequest, pRequest.h.size);
}
// -------------------------------------------------------------------------------
