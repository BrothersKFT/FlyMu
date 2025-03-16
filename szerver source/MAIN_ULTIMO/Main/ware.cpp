#include "stdafx.h"
#if (WARE==1)
#include "ware.h"
#include "Defines.h"
#include "Protocol.h"
#include "Util.h"
#include "User.h"
#include "Interface.h"
#include "Central.h"


ware gwareinterface;

int AnimatedWarehouse = 1;

void ware::DrawWarehouseWindow()
{
	if (!gInterface.Data[eWAREHOUSE_MAIN].OnShow)
	{
		return;
	}

	float MainWidth = 230.0;
	float MainHeight = 380.0;
	float StartY = ((MAX_WIN_HEIGHT - 51) / 2) - (MainHeight / 2);
	float StartX = (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float MainCenter = StartX + (MainWidth / 3);
	float ButtonX = MainCenter - (float)(29.0 / 2);
	//--
	gInterface.Data[eWAREHOUSE_MAIN].MaxX = StartX + MainWidth;
	gInterface.Data[eWAREHOUSE_MAIN].MaxY = StartY + MainHeight;

	gCentral.PrintDropBox(StartX, StartY, MainWidth, MainHeight, 0, 0);

	gInterface.DrawFormat(eGold, (int)StartX + 10, (int)StartY + 10, 210, 3, "WAREHOUSE");

	gInterface.DrawFormat(eGold, (int)StartX + 50, (int)StartY + 45, 150, 1, "Dear %s, please select warehouse...", gObjUser.lpPlayer->Name);
	

	pDrawGUI(71520, StartX + (MainWidth / 2) - (200 / 2), StartY + 67, 200, 1); //-- Divisor

	float CurrentMove;
	int BtCount = -1;
	int BtStart = StartY + 75;

	int ObjectIDs[8] =
	{
		eWAREHOUSE_NUM1,
		eWAREHOUSE_NUM2,
		eWAREHOUSE_NUM3,
		eWAREHOUSE_NUM4,
		eWAREHOUSE_NUM5,
		eWAREHOUSE_NUM6,
		eWAREHOUSE_NUM7,
		eWAREHOUSE_NUM8,
	};

	this->WareButtons[0] = 1;
	if (gObjUser.m_MaxWarehouse >= 2)
	{
		this->WareButtons[1] = 1;
	}
	if (gObjUser.m_MaxWarehouse >= 3)
	{
		this->WareButtons[2] = 1;
	}
	if (gObjUser.m_MaxWarehouse >= 4)
	{
		this->WareButtons[3] = 1;
	}
	if (gObjUser.m_MaxWarehouse >= 5)
	{
		this->WareButtons[4] = 1;
	}
	if (gObjUser.m_MaxWarehouse >= 6)
	{
		this->WareButtons[5] = 1;
	}
	if (gObjUser.m_MaxWarehouse >= 7)
	{
		this->WareButtons[6] = 1;
	}
	if (gObjUser.m_MaxWarehouse >= 8)
	{
		this->WareButtons[7] = 1;
	}


	for (int n = 0; n < 8; n++)
	{
		if (this->WareButtons[n] == 1)
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

		
		gInterface.DrawButton(ObjectIDs[n], StartX + (MainWidth / 2) - (108 / 2), BtStart + (33.0f * BtCount), 0, CurrentMove);
		gInterface.DrawFormat(eWhite, StartX + (MainWidth / 2) - (108 / 2), BtStart + (33.0f * BtCount) + 9, 108, 3, gCustomMessage.GetMessage((n == 8) ? 44 : 76 + n));
	}

	pDrawGUI(71520, StartX + (MainWidth / 2) - (200 / 2), StartY + MainHeight - 40, 200, 1); //-- Divisor

	if (gInterface.IsWorkZone(eWAREHOUSE_CLOSE))
	{
		if (gInterface.Data[eWAREHOUSE_CLOSE].OnClick)
		{
			PlayBuffer(25, 0, 0);
			gInterface.DrawButtonRender(eWAREHOUSE_CLOSE, StartX + (MainWidth / 2) - (59 / 2), StartY + MainHeight - 32, 0, 28);
		}
		else
		{
			gInterface.DrawButtonRender(eWAREHOUSE_CLOSE, StartX + (MainWidth / 2) - (59 / 2), StartY + MainHeight - 32, 0, 0);
		}
	}
	else
	{
		gInterface.DrawButtonRender(eWAREHOUSE_CLOSE, StartX + (MainWidth / 2) - (59 / 2), StartY + MainHeight - 32, 0, 0);
	}
	gInterface.DrawFormat(eWhite, StartX + (MainWidth / 2) - (59 / 2), StartY + MainHeight - 25, 59, 3, "Close");
}



void ware::EventWarehouseWindow_Main(DWORD Event)
{
	this->EventWarehouseWindow_Close(Event);
	// 4136

	DWORD CurrentTick = GetTickCount();

	if ((CurrentTick - gInterface.Data[eWAREHOUSE_MAIN].EventTick) < 500)
	{
		return;
	}

	// ----
	if (!gInterface.Data[eWAREHOUSE_MAIN].OnShow)
	{
		return;
	}

	int ObjectIDs[8] =
	{
		eWAREHOUSE_NUM1,
		eWAREHOUSE_NUM2,
		eWAREHOUSE_NUM3,
		eWAREHOUSE_NUM4,
		eWAREHOUSE_NUM5,
		eWAREHOUSE_NUM6,
		eWAREHOUSE_NUM7,
		eWAREHOUSE_NUM8
	};

	for (int i = 0; i < 8; i++)
	{
		if (gInterface.IsWorkZone(ObjectIDs[i]))
		{
			DWORD Delay = (CurrentTick - gInterface.Data[ObjectIDs[i]].EventTick);

			if (Event == WM_LBUTTONDOWN)
			{
				gInterface.Data[ObjectIDs[i]].OnClick = true;
				return;
			}
			// ----
			gInterface.Data[ObjectIDs[i]].OnClick = false;;
			// ----
			if (Delay < 500)
			{
				return;
			}
			// ----
			gInterface.Data[ObjectIDs[i]].EventTick = GetTickCount();
			CGSendWarehouseOpen(i);
			gInterface.Data[eWAREHOUSE_MAIN].Close(MAX_WIN_HEIGHT, 20);
		}
	}
}

void ware::EventWarehouseWindow_Close(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - gInterface.Data[eWAREHOUSE_CLOSE].EventTick);
	// ----
	if (!gInterface.Data[eWAREHOUSE_MAIN].OnShow || !gInterface.IsWorkZone(eWAREHOUSE_CLOSE))
	{
		return;
	}
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		gInterface.Data[eWAREHOUSE_CLOSE].OnClick = true;
		return;
	}
	// ----
	gInterface.Data[eWAREHOUSE_CLOSE].OnClick = false;
	// ----
	if (Delay < 500)
	{
		return;
	}
	// ----
	gInterface.Data[eWAREHOUSE_CLOSE].EventTick = GetTickCount();
	gInterface.Data[eWAREHOUSE_MAIN].Close(MAX_WIN_HEIGHT, 20);
	// ----
	return;
}
#endif