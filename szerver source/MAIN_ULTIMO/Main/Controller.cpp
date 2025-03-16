#include "stdafx.h"
#include "resource.h"
#include "Controller.h"
#include "CustomCommandInfo.h"
#include "CustomEventTime.h"
#include "Defines.h"
#include "OffTrade.h"
#include "Protocol.h"
#include "Import.h"
#include "Interface.h"
#include "Protect.h"
#include "TMemory.h"
#include "CSCharacterS13.h"
#include "CMacroUIEx.h"
#include "Camera.h"
#include "TrayModeNew.h"
#include "MiniMap.h"
#include "WindowsStruct.h"
#include "Ruud.h"
#include "Central.h"
#include "ware.h"
#include "JewelryBank.h"
#include "ChangeClass.h"
#include "ResetSystem.h"
#include "ShopSearch.h"
#include "Achievements.h"
#include "SmithItem.h"
#include "WindowsQuest.h"
#include "ResetSystemPanel.h"
#include "GrandResetSystem.h"
// ----------------------------------------------------------------------------------------------

Controller	gController;
// ----------------------------------------------------------------------------------------------
void __declspec(naked) iconHook()
{
	static DWORD dwIcon = (DWORD)LoadIcon(gController.Instance, MAKEINTRESOURCE(IDI_ICON1));
	static DWORD dwJmp = 0x004D0E3C;

	_asm
	{
		MOV EAX, dwIcon
		JMP dwJmp
	}
}

bool Controller::Load()
{
	if( !this->MouseHook )
	{
		this->MouseHook = SetWindowsHookEx(WH_MOUSE, this->Mouse, gController.Instance, GetCurrentThreadId());
		// ----
		if( !this->MouseHook )
		{
			return false;
		}
	}
	// ----
	if( !this->KeyboardHook )
	{
	}
	// ----
	SetOp((LPVOID)0x004D0E2F, iconHook, ASM::CALL);
	return true;
}


LRESULT Controller::Mouse(int Code, WPARAM wParam, LPARAM lParam)
{
	if( GetForegroundWindow() != pGameWindow )
	{
		return CallNextHookEx(gController.MouseHook, Code, wParam, lParam);
	}
	// ----
	MOUSEHOOKSTRUCTEX * Mouse	= (MOUSEHOOKSTRUCTEX*)lParam;
	gController.wMouse = wParam;
	switch(wParam)
	{
	case WM_LBUTTONUP:
	case WM_LBUTTONDOWN:
		{
			gInterface.EventVipWindow_Main(wParam);
			gCustomCommandInfo.EventCommandWindow_Close(wParam);
			gCustomCommandInfo.CommandNext(wParam);
			gCustomCommandInfo.CommandPrev(wParam);
			gCustomEventTime.EventEventTimeWindow_Close(wParam);
			gCustomEventTime.EventNext(wParam);
			gCustomEventTime.EventPrev(wParam);
			gInterface.EventDrawMenu_Open(wParam);
			gInterface.EventDrawMenu_Close(wParam);
			gInterface.EventDrawMenu2_Close(wParam);
			gInterface.EventDrawMenu_Next(wParam);
			gInterface.EventDrawMenu_Back(wParam);
			gInterface.EventDrawMenu_Op1(wParam);
			gInterface.EventDrawMenu_Op2(wParam);
			gInterface.EventDrawMenu_Op3(wParam);
			gInterface.EventDrawMenu_Op4(wParam);
			gInterface.EventDrawMenu_Op20(wParam);
			gInterface.EventDrawMenu_Op6(wParam);
			gInterface.EventDrawMenu_Op7(wParam);
			gInterface.EventDrawMenu_Op8(wParam);
			gInterface.EventDrawMenu_Op9(wParam);
			gInterface.EventDrawMenu_Op10(wParam);
			gInterface.EventDrawMenu_Op11(wParam);
			gInterface.EventConfirm_CANCEL(wParam);
			gInterface.EventConfirm_OK(wParam);
//			gCRuudShop.RuudShopEventButton(wParam);
			gCSCharacterS13.SelectCharButton(wParam);
			
			EventMuOffhelper(wParam);
			EventZenMuOffhelper(wParam);

#if (WARE==1)
			gwareinterface.EventWarehouseWindow_Main(wParam);
#endif
#if (JEWEL_BANK == 1)
			gJewelsBank.Button(wParam);
			gJewelsBank.EventJewelBank_Close(wParam);
#endif
			gInterface.EventPartySearchWindow_All(wParam);
			gInterface.EventPartySettingsWindow_Main(wParam);

			gChangeClass.EventChange_SelectAll(wParam);
#if (RESETCHANGE ==1)
			gResetChange.ButtonResetChange(wParam);
#endif
			gSmithItem.EventSmithItem_Main(wParam);

			gInterface.EventLuckyWheel_Main(wParam);
			gInterface.EventLuckyWheelWindow_Close(wParam);

			g_PersonalShopEx.Button(wParam);

			gAchievements.Button(wParam);

			g_ExWinQuestSystem.Button(wParam);

			gResetSystem.EventResetWindow_Main(wParam);

			gGrandResetSystem.EventGrandResetWindow_Main(wParam);

			if (jCRenderRuud.isOpen() && wParam == WM_LBUTTONDOWN)
			{
				if (pCheckMouseOver(jCRenderRuud.JCMoveX, jCRenderRuud.JCMoveY, 190, 70))
				{
					gController.CurHookX = (double)*(DWORD*)0x879340C - jCRenderRuud.JCMoveX;
					gController.CurHookY = (double)*(DWORD*)0x8793410 - jCRenderRuud.JCMoveY;
					gController.MoveRuud = 1;
				}
				else
				{
					gController.MoveRuud = 0;
				}
			}
			else
			{
				gController.MoveRuud = 0;
			}
			
			if(gProtect.m_MainInfo.CustomInterfaceType == 1)
			{
				gInterface.EventNewInterface97_All(wParam);
			}
			else if(gProtect.m_MainInfo.CustomInterfaceType == 2)
			{
				gInterface.EventNewInterface_All(wParam);
			}
			gCMacroUIEx.Button(wParam);
			gOffTrade.EventOffTradeWindow_Main(wParam);
			gOffTrade.EventCloseTradeWindow_Main(wParam);

			// MOVE WINDOWS

			if (gCentral.isOpenWinCustom() && wParam == WM_LBUTTONDOWN)
			{
				if (pCheckMouseOver(gCentral.JTMoveX, gCentral.JTMoveY, 190, 70))
				{
					gController.CurHookX = (double)*(DWORD*)0x879340C - gCentral.JTMoveX;
					gController.CurHookY = (double)*(DWORD*)0x8793410 - gCentral.JTMoveY;
					gController.MoveWinCustom = 1;
				}
				else
				{
					gController.MoveWinCustom = 0;
				}
			}
			else
			{
				gController.MoveWinCustom = 0;
			}
		}
		
		break;
		case WM_MOUSEMOVE:
			if(GetForegroundWindow() == *(HWND*)(0x00E8C578))
			{
				if (gController.MoveRuud == 1)
				{
					jCRenderRuud.MoverWinRuud(*(DWORD*)0x879340C - gController.CurHookX, *(DWORD*)0x8793410 - gController.CurHookY);
				}

				if (gController.MoveWinCustom == 1)
				{
					gCentral.MoverWinCustom(*(DWORD*)0x879340C - gController.CurHookX, *(DWORD*)0x8793410 - gController.CurHookY);
				}

				gCamera.Move(Mouse);
			}
			break;
		case WM_MBUTTONDOWN:
			if(GetForegroundWindow() == *(HWND*)(0x00E8C578))
			{
				gCamera.SetIsMove(1);
				gCamera.SetCursorX(Mouse->pt.x);
				gCamera.SetCursorY(Mouse->pt.y);
			}
			break;
		case WM_MBUTTONUP:
			if(GetForegroundWindow() == *(HWND*)(0x00E8C578))
			{
				gCamera.SetIsMove(0);
			}
			break;
		case WM_MOUSEWHEEL:
			if(GetForegroundWindow() == *(HWND*)(0x00E8C578))
			{
				gCamera.Zoom(Mouse);
			}
			break;
	}
	// ----
	return CallNextHookEx(gController.MouseHook, Code, wParam, lParam);
}
// ----------------------------------------------------------------------------------------------

LRESULT Controller::Keyboard(int Code, WPARAM wParam, LPARAM lParam)
{
	if( GetForegroundWindow() != pGameWindow )
	{
		return CallNextHookEx(gController.KeyboardHook, Code, wParam, lParam);
	}

	if (Code < 0) return CallNextHookEx(gController.KeyboardHook, Code, wParam, lParam);
	
	if( (Code == HC_ACTION) && (wParam == WM_KEYDOWN))
	{
		KBDLLHOOKSTRUCT Hook = *((KBDLLHOOKSTRUCT*)lParam);
		switch(Hook.vkCode)
		{
			// --
		case 0x48:
		{
			gCustomEventTime.OpenWindow();
		}
		break;
		case VK_ESCAPE:
		{

			if (gInterface.Data[eCommand_MAIN].OnShow == true  && (gProtect.m_MainInfo.CustomInterfaceType != 3 || gProtect.m_MainInfo.CustomInterfaceType != 4))
			{
				gInterface.Data[eCommand_MAIN].OnShow = false;

				pSetCursorFocus = false;

				return -1;
			}

			if (gInterface.Data[eRankPANEL_MAIN].OnShow == true  && (gProtect.m_MainInfo.CustomInterfaceType != 3 || gProtect.m_MainInfo.CustomInterfaceType != 4))
			{
				gInterface.Data[eRankPANEL_MAIN].OnShow = false;

				pSetCursorFocus = false;

				return -1;
			}

			if (gInterface.Data[eEventTimePANEL_MAIN].OnShow == true && (gProtect.m_MainInfo.CustomInterfaceType != 3 || gProtect.m_MainInfo.CustomInterfaceType != 4))
			{
				gInterface.Data[eEventTimePANEL_MAIN].OnShow = false;

				pSetCursorFocus = false;

				return -1;
			}

			if (gInterface.CheckVipWindow())
			{
				gInterface.CloseVipWindow();
				return -1;
			}

			if (gInterface.CheckMenuWindow())
			{
				gInterface.CloseMenuWindow();
				return -1;
			}
			
		}
		break;
		case VK_END:
		{
			if (gInterface.CheckVipWindow())
			{
				gInterface.CloseVipWindow();
			}
			else
			{
				gInterface.CloseCustomWindow();
				gInterface.OpenVipWindow();
			}
		}
		break;
		case VK_SNAPSHOT:
		{
			gInterface.Data[eLogo].EventTick = GetTickCount()+1500;
			return CallNextHookEx(gController.KeyboardHook, Code, wParam, lParam);
		}
		break;

		default:
		break;
		}
	} 
	return (LRESULT) NULL;
	
}
// ----------------------------------------------------------------------------------------------


LRESULT Controller::Window(HWND Window, DWORD Message, WPARAM wParam, LPARAM lParam)
{
	switch(Message)
	{

	case TRAYMODE_ICON_MESSAGE:
		{
			switch(lParam)
			{
			case WM_LBUTTONDBLCLK:
				{
					gTrayMode.SwitchState();
				}
				break;
			}
		}
		break;
	}
	// ----
	return CallWindowProc((WNDPROC)gTrayMode.TempWindowProc, Window, Message, wParam, lParam);
}


