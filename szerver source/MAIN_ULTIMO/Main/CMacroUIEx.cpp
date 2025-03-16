#include "stdafx.h"
#include "CMacroUIEx.h"
#include "Util.h"
#include "Offset.h"
#include "Import.h"
#include "User.h"
#include "Interface.h"
#include "Defines.h"
#include "MuHelper.h"
#include "Protocol.h"
#include "Common.h"
#include "MiniMap.h"
#include "Camera.h"
#include "PrintPlayer.h"
#include "Ruud.h"
#include "WindowsStruct.h"
#include "InfoLog.h"

// ---------------------------------------------------------------------------------------------
int EventCamera;
int EventZoom;
int TypeZoom = 3;
DWORD BUTTON_DELAY;
DWORD EvkMenu;
// ---------------------------------------------------------------------------------------------
CMacroUIEx gCMacroUIEx;
// ---------------------------------------------------------------------------------------------

void CMacroUIEx::RenderFrame(int *This)
{
	float CY;
	char Cord[256];
	float X = (double)*((DWORD *)This + 5);
	float Y = (double)*((signed int *)This + 6);

	float renderMenu = 15.0f;

	EnableAlphaTest(1);
	glColor4f(1.0, 1.0, 1.0, 1.0);
	renderMenu = 10.0f;
//	RenderBitmap1(51550, X + 85.0 + renderMenu, Y, 124.0, 24.0, 0.0, 0.285, 0.725, 0.28, 1, 1, 0.0);
//	RenderBitmap1(51550, X, Y, 124.0, 24.0, 0.0, 0.0, 0.725, 0.28, 1, 1, 0.0);

	RenderBitmap1(51550, X + 99.0 + renderMenu, Y, 124.0, 24.0, 0.0, 0.285, 0.725, 0.28, 1, 1, 0.0);
	RenderBitmap1(51550, X, Y, 124.0, 24.0, 0.0, 0.0, 0.725, 0.28, 1, 1, 0.0);
	
	//Mapa y Coordenadas
	if (World >= 82 && World <= 100)
	{
		wsprintf(Cord, "%s  %d,%d", pGetTextLine(pTextLineThis, (3182 + World - 82)), gObjUser.CoordenadaX, gObjUser.CoordenadaY);
	}
	else
	{
		wsprintf(Cord, "%s  %d,%d", pMapName(World), gObjUser.CoordenadaX, gObjUser.CoordenadaY);
	}
	
	pSetBackgroundTextColor(pTextThis(), 0, 0, 0, 0);
	pSetTextColor(pTextThis(), 240, 240, 240, 255);
	pDrawText(pTextThis(), X - 35, Y + 4, Cord, 190, 0, (LPINT)3, 0);
	//Extra
	DWORD Color = Color4f(255, 189, 25, 255);
	if (!*(BYTE*)(*(DWORD*)(MUHELPER_STRUC)+0x08))
	{
		gInterface.DrawFormat(Color, X + 169 + renderMenu, Y + 2, 27.5, 3, "0");
	}
	else
	{
		gInterface.DrawFormat(Color, X + 169 + renderMenu, Y + 2, 27.5, 3, "1");
	}
	pGLSwitch();
	EnableAlphaTest(0);
//Botones
	renderMenu = 15.0f;
	gInterface.DrawButtonRender(ButtonSettings, 134.5f + renderMenu, 7.0, 0, 0);
	//-- Config
	if (gInterface.IsWorkZone(ButtonSettings))
	{
		gInterface.DrawToolTip(X + 134.5 + renderMenu, Y + 50, "Config Helper");

		if (gInterface.Data[ButtonSettings].OnClick)
		{
			RenderBitmap1(51546, X + 134.5 + renderMenu, Y + 7.0, 19, 19, 0.0, 0.451f, 0.878, 0.225, 1, 1, 0.0);
			//gInterface.DrawButtonRender(ButtonSettings, 119.5f, 7.0, 0, 40.0f);
		}
		else
		{
			RenderBitmap1(51546, X + 134.5 + renderMenu, Y + 7.0, 19, 19, 0.0, 0.2255f, 0.878, 0.225, 1, 1, 0.0);
		}
		//gInterface.DrawButtonRender(ButtonSettings, 119.5f, 7.0, 0, 20.0f);
	}
	else
	{
		RenderBitmap1(51546, X + 134.5 + renderMenu, Y + 7.0, 19, 19, 0.0, 0.0, 0.878, 0.225, 1, 1, 0.0);
	}
	if (!*(BYTE*)(*(DWORD*)(MUHELPER_STRUC)+0x08))
	{
		gInterface.DrawButtonRender(ButtonStart, 153.5f + renderMenu, 7.0, 0, 0.0f);
		//-- Play
		if (gInterface.IsWorkZone(ButtonStart))
		{
			gInterface.DrawToolTip(X + 153.5 + renderMenu, Y + 50, "Play Helper");

			if (gInterface.Data[ButtonStart].OnClick)
			{
				RenderBitmap1(51547, X + 153.5 + renderMenu, Y + 7.0, 19, 19, 0.0, 0.451f, 0.878, 0.225, 1, 1, 0.0);
			}
			else
			{
				RenderBitmap1(51547, X + 153.5 + renderMenu, Y + 7.0, 19, 19, 0.0, 0.2255f, 0.878, 0.225, 1, 1, 0.0);
			}
		}
		else
		{
			RenderBitmap1(51547, X + 153.5 + renderMenu, Y + 7.0, 19, 19, 0.0, 0.0, 0.878, 0.225, 1, 1, 0.0);
		}
	}
	else
	{
		gInterface.DrawButtonRender(ButtonStop, 153.5f + renderMenu, 7.0, 0, 0.0f);

		if(offhelper == 1)
		{
			gMuHelper.RunningOffHelper();
		}
		//-- Pause
		if (gInterface.IsWorkZone(ButtonStop))
		{
			gInterface.DrawToolTip(X + 153.5 + renderMenu, Y + 50, "Pause Helper");

			if (gInterface.Data[ButtonStop].OnClick)
			{
				RenderBitmap1(51548, X + 153.5 + renderMenu, Y + 7.0, 19, 19, 0.0, 0.451f, 0.878, 0.225, 1, 1, 0.0);
				
				//gMuHelper.ClearOffHelper();
			}
			else
			{
				RenderBitmap1(51548, X + 153.5 + renderMenu, Y + 7.0, 19, 19, 0.0, 0.2255f, 0.878, 0.225, 1, 1, 0.0);
			}
			//gInterface.DrawButtonRender(ButtonStart, 138.5, 7.0 , 0, 20.0f);
		}
		else
		{
			RenderBitmap1(51548, X + 153.5 + renderMenu, Y + 7.0, 19, 19, 0.0, 0.0, 0.878, 0.225, 1, 1, 0.0);
		}
	}
	// ----
	gInterface.DrawButtonRender(ButtonCamera, X + 96.0f + renderMenu, Y + 7.0, 0, 0.0f);

	if (gInterface.IsWorkZone(ButtonCamera))
	{
		gInterface.DrawToolTip(X + 96.0f + renderMenu, 50, "CAMERA ON|OFF|RESET");
		// ----
		if (gInterface.Data[ButtonCamera].OnClick)
		{
			RenderBitmap1(51554, X + 96.0f + renderMenu, Y + 7.0, 19, 19, 0.0, 0.451f, 0.878, 0.225, 1, 1, 0.0);
		}
		else
		{
			RenderBitmap1(51554, X + 96.0f + renderMenu, Y + 7.0, 19, 19, 0.0, 0.2255f, 0.878, 0.225, 1, 1, 0.0);
		}
	}
	else
	{
		RenderBitmap1(51554, X + 96.0f + renderMenu, Y + 7.0, 19, 19, 0.0, 0.0, 0.878, 0.225, 1, 1, 0.0);
	}
	// ----
	gInterface.DrawButtonRender(eMenu, X + 115.5f + renderMenu, Y + 7.0, 0, 0.0f);

	if (gInterface.IsWorkZone(eMenu))
	{
		
		if (Menu == 1)
		{
			gInterface.DrawToolTip(X + 115.5 + renderMenu, 50, "Custom Menu");
		}
		else
		{
			gInterface.DrawToolTip(X + 115.5 + renderMenu, 50, "Disable");
		}
		// ----
		if (gInterface.Data[eMenu].OnClick)
		{
			RenderBitmap1(51553, X + 115.5 + renderMenu, Y + 7.0, 19, 19, 0.0, 0.451f, 0.878, 0.225, 1, 1, 0.0);
		}
		else
		{
			RenderBitmap1(51553, X + 115.5 + renderMenu, Y + 7.0, 19, 19, 0.0, 0.2255f, 0.878, 0.225, 1, 1, 0.0);
		}
	}
	else
	{
		RenderBitmap1(51553, X + 115.5 + renderMenu, Y + 7.0, 19, 19, 0.0, 0.0, 0.878, 0.225, 1, 1, 0.0);
	}
}


void CMacroUIEx::Button(DWORD Event)
{
	DWORD CurrentTick	= GetTickCount();

	if( gInterface.IsWorkZone(ButtonSettings) )
	{
		DWORD Delay	= (CurrentTick - gInterface.Data[ButtonSettings].EventTick);
		// ----
		if( Event == WM_LBUTTONDOWN )
		{
			gInterface.Data[ButtonSettings].OnClick = true;
			return;
		}
		// ----
		gInterface.Data[ButtonSettings].OnClick = false;
		// ----
		if( Delay < 500 )
		{
			return;
		}
		// ----
		gInterface.Data[ButtonSettings].EventTick = GetTickCount();
		// ----
	}
	else if( gInterface.IsWorkZone(ButtonStart) )
	{
		DWORD Delay	= (CurrentTick - gInterface.Data[ButtonStart].EventTick);
		// ----
		if( Event == WM_LBUTTONDOWN )
		{
			gInterface.Data[ButtonStart].OnClick = true;

			return;
		}
		// ----
		gInterface.Data[ButtonStart].OnClick = false;
		// ----
		if( Delay < 500 )
		{
			return;
		}
		// ----
		gInterface.Data[ButtonStart].EventTick = GetTickCount();
		// ----
		}
	else if( gInterface.IsWorkZone(ButtonStop) )
	{
		DWORD Delay	= (CurrentTick - gInterface.Data[ButtonStop].EventTick);
		// ----
		if( Event == WM_LBUTTONDOWN )
		{
			gInterface.Data[ButtonStop].OnClick = true;
			return;
		}
		// ----
		gInterface.Data[ButtonStop].OnClick = false;
		// ----
		if( Delay < 500 )
		{
			return;
		}
		// ----
		gInterface.Data[ButtonStop].EventTick = GetTickCount();
		// ----
	}
	else if (gInterface.IsWorkZone(ButtonCamera))
	{
		DWORD Delay = (CurrentTick - gInterface.Data[ButtonCamera].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			gInterface.Data[ButtonCamera].OnClick = true;
			return;
		}
		// ----
		gInterface.Data[ButtonCamera].OnClick = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		gInterface.Data[ButtonCamera].EventTick = GetTickCount();
		// ----
		if (gCamera.getEnabled())
		{
			gCamera.Restore();
			gCamera.Toggle();
			gInterface.DrawMessage(1, "Camera3D [OFF||RESET]");
		}
		else
		{
			gCamera.Toggle();
			gInterface.DrawMessage(1, "Camera3D [ON]");
		}
	}
}

char BarTime(int This)
{
	float v1; // ST10_4@2
	float v2; // ST0C_4@2
	float v3; // ST30_4@3
	float v4; // ST08_4@3
	float v5; // ST04_4@3
	float v6; // ST10_4@5
	float v7; // ST0C_4@5
	float v8; // ST1C_4@5
	float v9; // ST08_4@5
	float v10; // ST04_4@5
	const CHAR *v11; // eax@7
	int v13; // [sp+30h] [bp-4h]@1

	 v13 = This;

	if ( *(BYTE *)(v13 + 72) == 1 )
	{
		v1 = (double)*(signed int *)(This + 20);
		v2 = (double)*(signed int *)(This + 16);
		RenderImage2(51522, v5, v4);
		if ( *(DWORD *)(v13 + 88) == 1 )
		{
			v3 = *(float *)(v13 + 92) * 50.0;
			v4 = (double)(*(DWORD *)(v13 + 20) + 2);
			v5 = (double)(*(DWORD *)(v13 + 16) + 2);
			RenderImage(51549, v5 + 108.0, v4 - 16.0, v3, 3.0);
		}
		else if ( *(DWORD *)(v13 + 88) > 1 )
		{
			RenderImage2(51522, v5, v4);
			v3 = *(float *)(v13 + 92) * 50.0;
			v4 = (double)(*(DWORD *)(v13 + 20) + 2);
			v5 = (double)(*(DWORD *)(v13 + 16) + 2);
			RenderImage(51549, v5 + 108.0, v4 - 16.0, v3, 3.0);
		}
		/*if ( *(BYTE *)(v13 + 128) == 1 )
		{
			v14 = (const CHAR *)sub_402880((void *)(v16 + 100));
			sub_597220(*(_DWORD *)(v16 + 132), *(_DWORD *)(v16 + 136), v14);
		}*/
	}
  return 1;
}

//-- (007D25C0)
__declspec(naked) void MuHelperRemake_01()  //<- ConfigHelper
{
	static DWORD Remake_Buffer = 0x007D26DA;
	static DWORD W = 19;
	static DWORD H = 19;
	static DWORD X = 134.5 + 15.0f;
	static DWORD Y = 7;
 
	_asm
	{
		PUSH H                                  ; |Arg6 = 0000000D
		PUSH W                                  ; |Arg5 = 00000012
		MOV EDX,DWORD PTR SS:[EBP-0xB8]         ; |
		MOV EAX,DWORD PTR DS:[EDX+0x18]            ; |
		PUSH Y                                 ; |Arg4
		MOV ECX,DWORD PTR SS:[EBP-0xB8]            ; |
		MOV EDX,DWORD PTR DS:[ECX+0x14]            ; |
		MOV EAX,DWORD PTR SS:[EBP-0xB8]            ; |
		MOV ECX,DWORD PTR DS:[EAX+0xC]             ; |
		LEA EDX,DWORD PTR DS:[EDX+ECX+0x29]        ; |
		PUSH X                                 ; |Arg3
		JMP [Remake_Buffer]
	}
}
//-- (007D25C0)
__declspec(naked) void MuHelperRemake_02()  //<- PlayHelper
{
	static DWORD Remake_Buffer = 0x007D2776;
	static DWORD W = 19;
	static DWORD H = 19;
	static DWORD X = 153.5 + 15.0f;
	static DWORD Y = 5;
 
	_asm
	{
		PUSH H                                     ; |Arg6 = 0000000D
		PUSH W                                     ; |Arg5 = 00000012
		MOV EAX,DWORD PTR SS:[EBP-0xB8]            ; |
		MOV ECX,DWORD PTR DS:[EAX+0x18]            ; |
		PUSH Y                                     ; |Arg4
		MOV EDX,DWORD PTR SS:[EBP-0xB8]            ; |
		MOV EAX,DWORD PTR DS:[EDX+0x14]            ; |
		MOV ECX,DWORD PTR SS:[EBP-0xB8]            ; |
		MOV EDX,DWORD PTR DS:[ECX+0xC]             ; |
		LEA EAX,DWORD PTR DS:[EAX+EDX+0x3B]        ; |
		PUSH X                                     ; |Arg3
		JMP [Remake_Buffer]
	}
}
//-- (007D25C0)
__declspec(naked) void MuHelperRemake_03()  //<- PauseHelper
{
	static DWORD Remake_Buffer = 0x007D2821;
	static DWORD W = 19;
	static DWORD H = 19;
	static DWORD X = 153.5 + 15.0f;
	static DWORD Y = 5;
 
	_asm
	{
		PUSH H                                     ; |Arg6 = 0000000D
		PUSH W                                     ; |Arg5 = 00000012
		MOV EAX,DWORD PTR SS:[EBP-0xB8]            ; |
		MOV ECX,DWORD PTR DS:[EAX+0x18]            ; |
		PUSH Y                                     ; |Arg4
		MOV EDX,DWORD PTR SS:[EBP-0xB8]            ; |
		MOV EAX,DWORD PTR DS:[EDX+0x14]            ; |
		MOV ECX,DWORD PTR SS:[EBP-0xB8]            ; |
		MOV EDX,DWORD PTR DS:[ECX+0xC]             ; |
		LEA EAX,DWORD PTR DS:[EAX+EDX+0x3B]        ; |
		PUSH X                                     ; |Arg3
		JMP [Remake_Buffer]
	}
}

//==========================================================================================

void CMacroUIEx::RenderHelperFrame(int *This)
{
	float CY;
	char Cord[256];
	float X = (double)*((DWORD *)This + 5);
	float Y = (double)*((signed int *)This + 6);
	float RenderX; 

	EnableAlphaTest(1);
	glColor4f(1.0, 1.0, 1.0, 1.0);
	RenderImage(31602, X, Y, 22.0, 25.0);

	for(int i = 0 ; i < 5 ; i ++)
	{
		RenderX = (double) X + 22.0 + (i * 26.0);
		RenderImage(31603, RenderX, Y, 26.0, 25.0);
	}

	RenderImage(31604, RenderX, Y, 73.0, 20.0);
	
	//Mapa y Coordenadas
	if (World >= 82 && World <= 100)
	{
		wsprintf(Cord, "%s  (%d , %d)", pGetTextLine(pTextLineThis, (3182 + World - 82)), gObjUser.CoordenadaX, gObjUser.CoordenadaY);
	}
	else
	{
		wsprintf(Cord, "%s  (%d , %d)", pMapName(World), gObjUser.CoordenadaX, gObjUser.CoordenadaY);
	}
	pSetBackgroundTextColor(pTextThis(), 0, 0, 0, 0);
	pSetTextColor(pTextThis(), 240, 240, 240, 255);
	pDrawText(pTextThis(), X - 30, Y + 4, Cord, 190, 0, (LPINT)3, 0);
	pGLSwitch();
	EnableAlphaTest(0);
	//-- Config
	gInterface.DrawButtonRender(ButtonSettings, 146, 1, 0, 0);

	if (gInterface.IsWorkZone(ButtonSettings))
	{
		gInterface.DrawToolTip(146, Y + 50, "Config Helper");

		if (gInterface.Data[ButtonSettings].OnClick)
		{
			pDrawButton(31761, 146, 1.6, 18.0f, 13.3, 0, 26.9);
		}
		else
		{
			pDrawButton(31761, 146, 1.6, 18.0f, 13.3, 0, 13.6);
		}
	}
	else
	{
		pDrawButton(31761, 146, 1.0,18.0f, 13.3, 0, 0);
	}

	if (!*(BYTE*)(*(DWORD*)(MUHELPER_STRUC)+0x08))
	{
		gInterface.DrawButtonRender(ButtonStart, 146 + 18, 1, 0, 0);
		//-- Play
		if (gInterface.IsWorkZone(ButtonStart))
		{
			gInterface.DrawToolTip(146 + 18, Y + 50,"Play Helper");

			if (gInterface.Data[ButtonStart].OnClick)
			{
				pDrawButton(31762, 146 + 18, 1.6, 18.0f, 13.3, 0, 26.9);
			}
			else
			{
				pDrawButton(31762, 146 + 18, 1.6, 18.0f, 13.3, 0, 13.6);
			}
		}
		else
		{
			pDrawButton(31762, 146 + 18, 1.0,18.0f, 13.3, 0, 0);
		}
	}
	else
	{
		gInterface.DrawButtonRender(ButtonStop, 146 + 18, 1, 0, 0);

		if(offhelper == 1)
		{
			gMuHelper.RunningOffHelper();
		}
		//-- Pause
		if (gInterface.IsWorkZone(ButtonStop))
		{
			gInterface.DrawToolTip(146 + 18, Y + 50,"Pause Helper");

			if (gInterface.Data[ButtonStop].OnClick)
			{
				pDrawButton(31763, 146 + 18, 1.6, 18.0f, 13.3, 0, 26.9);
			}
			else
			{
				pDrawButton(31763, 146 + 18, 1.6, 18.0f, 13.3, 0, 13.6);
			}
		}
		else
		{
			pDrawButton(31763, 146 + 18, 1.0, 18.0f, 13.3, 0, 0);
		}
	}
//=======================================================
	DWORD Color;
	if (gProtect.m_MainInfo.CustomMenuSwitch != 0)
	{
		pDrawButton(30983, 146 + 37.2, 0.0, 36, 18, 0, 0);

		gInterface.DrawButtonRender(eMenu, 146 + 37.2, Y + 1.0 , 0, 0.0f);

		if (gInterface.IsWorkZone(eMenu))
		{
			if (Menu == 1)
			{
				gInterface.DrawToolTip(146 + 37.2, 50, "Custom Menu");
			}
			else
			{
				gInterface.DrawToolTip(146 + 37.2, 50, "Disable");
			}
			// ----
			if (gInterface.Data[eMenu].OnClick)
			{
				Color = eGray150;

				gInterface.DrawColoredGUI(eMenu, 146 + 37.2, Y + 1.0, Color);
			}
			else
			{
				gInterface.DrawButtonRender(eMenu, 146 + 37.2, Y + 1.0 , 0, 0.0f);
			}
		}
		else
		{
			gInterface.DrawButtonRender(eMenu, 146 + 37.2, Y + 1.0 , 0, 0.0f);
		}
	}
}

__declspec(naked) void MuHelperRemake2_01()  //<- ConfigHelper
{
	static DWORD Addr_JMP = 0x007D26DA;
	static DWORD W = 18;
	static DWORD H = 13.3;
	static DWORD X = 146.0f;
	static DWORD Y = 1;
 
	_asm
	{
		PUSH H                                  ; |Arg6 = 0000000D
		PUSH W                                  ; |Arg5 = 00000012
		MOV EDX,DWORD PTR SS:[EBP-0xB8]         ; |
		MOV EAX,DWORD PTR DS:[EDX+0x18]            ; |
		PUSH Y                                 ; |Arg4
		MOV ECX,DWORD PTR SS:[EBP-0xB8]            ; |
		MOV EDX,DWORD PTR DS:[ECX+0x14]            ; |
		MOV EAX,DWORD PTR SS:[EBP-0xB8]            ; |
		MOV ECX,DWORD PTR DS:[EAX+0xC]             ; |
		LEA EDX,DWORD PTR DS:[EDX+ECX+0x29]        ; |
		PUSH X                                 ; |Arg3
		JMP [Addr_JMP]
	}
}
//-- (007D25C0)
__declspec(naked) void MuHelperRemake2_02()  //<- PlayHelper
{
	static DWORD Addr_JMP = 0x007D2776;
	static DWORD W = 18;
	static DWORD H = 13.3;
	static DWORD X = 146.0f + 18.0f;
	static DWORD Y = 1;
 
	_asm
	{
		PUSH H                                     ; |Arg6 = 0000000D
		PUSH W                                     ; |Arg5 = 00000012
		MOV EAX,DWORD PTR SS:[EBP-0xB8]            ; |
		MOV ECX,DWORD PTR DS:[EAX+0x18]            ; |
		PUSH Y                                     ; |Arg4
		MOV EDX,DWORD PTR SS:[EBP-0xB8]            ; |
		MOV EAX,DWORD PTR DS:[EDX+0x14]            ; |
		MOV ECX,DWORD PTR SS:[EBP-0xB8]            ; |
		MOV EDX,DWORD PTR DS:[ECX+0xC]             ; |
		LEA EAX,DWORD PTR DS:[EAX+EDX+0x3B]        ; |
		PUSH X                                     ; |Arg3
		JMP [Addr_JMP]
	}
}
//-- (007D25C0)
__declspec(naked) void MuHelperRemake2_03()  //<- PauseHelper
{
	static DWORD Addr_JMP = 0x007D2821;
	static DWORD W = 18;
	static DWORD H = 13.3;
	static DWORD X = 146.0f + 18.0f;
	static DWORD Y = 1;
 
	_asm
	{
		PUSH H                                     ; |Arg6 = 0000000D
		PUSH W                                     ; |Arg5 = 00000012
		MOV EAX,DWORD PTR SS:[EBP-0xB8]            ; |
		MOV ECX,DWORD PTR DS:[EAX+0x18]            ; |
		PUSH Y                                     ; |Arg4
		MOV EDX,DWORD PTR SS:[EBP-0xB8]            ; |
		MOV EAX,DWORD PTR DS:[EDX+0x14]            ; |
		MOV ECX,DWORD PTR SS:[EBP-0xB8]            ; |
		MOV EDX,DWORD PTR DS:[ECX+0xC]             ; |
		LEA EAX,DWORD PTR DS:[EAX+EDX+0x3B]        ; |
		PUSH X                                     ; |Arg3
		JMP [Addr_JMP]
	}
}

void OffHelper(DWORD id, float x, float y, float w, float h)
{
	pDrawGUI(id, x, y, w, h);

	if( gInterface.IsWorkZone(ButtonStartAttack) )
	{
		if( gInterface.Data[ButtonStartAttack].OnClick )
		{
			if(offhelper == 0)
			{
				offhelper = 1;
			}
			else
			{
				offhelper = 0;
			}
			gInterface.Data[ButtonStartAttack].OnClick = false;
		}
	}
	if(offhelper == 1)
	{
		gInterface.DrawButtonRender(ButtonStartAttack, x + 50, y + 8, 0, 0);
	}
	else
	{
		gInterface.DrawButtonRender(ButtonStartAttack, x + 50, y + 8, 0, 15);
	}
	gInterface.DrawFormat(eGold, x + 50 + 16, y + 12, 60, 1, "MuOffHelper");

	// ..........................
	if (gInterface.IsWorkZone(ButtonZenOff))
	{
		if (gInterface.Data[ButtonZenOff].OnClick)
		{
			if (zenoff == 0)
			{
				zenoff = 1;
			}
			else
			{
				zenoff = 0;
			}
			gInterface.Data[ButtonZenOff].OnClick = false;
		}
	}
	if (zenoff == 1)
	{
		gInterface.DrawButtonRender(ButtonZenOff, x + 75, y + 61, 0, 0);
	}
	else
	{
		gInterface.DrawButtonRender(ButtonZenOff, x + 75, y + 61, 0, 15);
	}
	gInterface.DrawFormat(eWhite, x + 75 + 16, y + 65, 60, 1, "OffHelperZen");
}

//====================================
//========= MINIMAPA HELPER ==========
//====================================

void JExecuteButtonHelper(float X, float Y, float W)
{
	float DropCurrentY;
	int isPlay;

	if (!*(BYTE *)(*(DWORD*)0xE8CB7C + 8))
	{
		DropCurrentY = 0.5016000271;
		isPlay = 0;
	}
	else
	{
		DropCurrentY = 0.5639800633;
		isPlay = 1;
	}

	if (pCheckMouseOver((int)X, (int)Y, (int)W, (int)W))
	{
		if (*(BYTE*)0x8793386)
		{
			RenderBitmap(61519, X, Y, W, W, 0.2588, DropCurrentY, 0.1209000051, 0.05900005624, 1, 1, 0.0);

		}
		else
		{
			RenderBitmap(61519, X, Y, W, W, 0.1341000199, DropCurrentY, 0.1209000051, 0.05900005624, 1, 1, 0.0);
		}
	}
	else
	{
		if (offhelper == 1)
		{
			gMuHelper.RunningOffHelper();
		}

		if (isPlay == 1)
		{
			RenderBitmap(61519, X, Y, W, W, 0.1341000199, DropCurrentY, 0.1209000051, 0.05900005624, 1, 1, 0.0);
		}
		else
		{
			RenderBitmap(61519, X, Y, W, W, 0.008999999613, DropCurrentY, 0.1209000051, 0.05900005624, 1, 1, 0.0);
		}
	}
}

void JExecuteButtonConfig(float X, float Y, float W)
{
	if (pCheckMouseOver((int)X, (int)Y, (int)W, (int)W))
	{
		if (*(BYTE*)0x8793386)
		{
			PlayBuffer(25, 0, 0);
			RenderBitmap(61519, X, Y, W, W, 0.2588, 0.6899006367, 0.1209000051, 0.05900005624, 1, 1, 0.0);
		}
		else
		{
			RenderBitmap(61519, X, Y, W, W, 0.1341000199, 0.6899006367, 0.1209000051, 0.05900005624, 1, 1, 0.0);
		}
	}
	else
	{
		if (pCheckWindow(pWindowThis(), MuHelper))
		{
			RenderBitmap(61519, X, Y, W, W, 0.1341000199, 0.6899006367, 0.1209000051, 0.05900005624, 1, 1, 0.0);
		}
		else
		{
			RenderBitmap(61519, X, Y, W, W, 0.008999999613, 0.6899006367, 0.1209000051, 0.05900005624, 1, 1, 0.0);
		}
	}
}

void JExecuteButtonCameraRestore(float X, float Y, float W, float DropCurrentY)
{
	if (pCheckMouseOver((int)X, (int)Y, (int)W, (int)W))
	{
		if (*(BYTE*)0x8793386 && GetTickCount() >= EventCamera + 300)
		{
			PlayBuffer(25, 0, 0);
			RenderBitmap(61519, X, Y, W, W, 0.2588, DropCurrentY, 0.1209000051, 0.05900005624, 1, 1, 0.0);
			gCamera.Restore();
			EventCamera = GetTickCount();
		}
		else
		{
			RenderBitmap(61519, X, Y, W, W, 0.1341000199, DropCurrentY, 0.1209000051, 0.05900005624, 1, 1, 0.0);
		}
	}
	else
	{
		RenderBitmap(61519, X, Y, W, W, 0.008999999613, DropCurrentY, 0.1209000051, 0.05900005624, 1, 1, 0.0);
	}
}

void JExecuteButtonCameraInit(float X, float Y, float W)
{
	if (pCheckMouseOver((int)X, (int)Y, (int)W, (int)W))
	{
		if (*(BYTE*)0x8793386 && GetTickCount() >= EventCamera + 300)
		{
			PlayBuffer(25, 0, 0);
			RenderBitmap(61519, X, Y, W, W, 0.2588, 0.6275005937, 0.1209000051, 0.05900005624, 1, 1, 0.0);
			gCamera.Toggle();
			EventCamera = GetTickCount();
		}
		else
		{
			RenderBitmap(61519, X, Y, W, W, 0.1341000199, 0.6275005937, 0.1209000051, 0.05900005624, 1, 1, 0.0);
		}
	}
	else
	{
		if (gCamera.getEnabled())
		{
			RenderBitmap(61519, X, Y, W, W, 0.1341000199, 0.6275005937, 0.1209000051, 0.05900005624, 1, 1, 0.0);
		}
		else
		{
			RenderBitmap(61519, X, Y, W, W, 0.008999999613, 0.6275005937, 0.1209000051, 0.05900005624, 1, 1, 0.0);
		}
	}
}

void JShowButtonSlash(float X, float Y, float W, float DropCurrentY)
{
	if (pCheckMouseOver((int)X, (int)Y, (int)W, (int)W))
	{
		if (*(BYTE*)0x8793386)
		{
			if (GetTickCount() >= EvkMenu + 300)
			{
				if (gInterface.CheckMenuWindow())
				{
					gInterface.CloseMenuWindow();
					pSetCursorFocus = false;
				}
				else
				{
					gInterface.CloseCustomWindow();
					gInterface.OpenMenuWindow();
				}
				EvkMenu = GetTickCount();
			}
			PlayBuffer(25, 0, 0);
			RenderBitmap(61519, X, Y, W, W, 0.2588, DropCurrentY, 0.1209000051, 0.05900005624, 1, 1, 0.0);
		}
		else
		{
			RenderBitmap(61519, X, Y, W, W, 0.1341000199, DropCurrentY, 0.1209000051, 0.05900005624, 1, 1, 0.0);
		}
	}
	else
	{
		RenderBitmap(61519, X, Y, W, W, 0.008999999613, DropCurrentY, 0.1209000051, 0.05900005624, 1, 1, 0.0);
	}
}

void JGetButtonClosed(float X, float Y, float W)
{
	if (pCheckMouseOver((int)X, (int)Y, (int)W, (int)W))
	{
		if (*(BYTE*)0x8793386)
		{
			PlayBuffer(25, 0, 0);
			RenderBitmap(61519, X, Y, W, W, 0.7661997676, 0.7609999776, 0.08950000256, 0.04200005904, 1, 1, 0.0);

			MiniMap = !MiniMap;

			if (MiniMap != 0)
				WritePrivateProfileStringA("Setting", "MiniMap", "1", "./Settings.ini");
			else
				WritePrivateProfileStringA("Setting", "MiniMap", "0", "./Settings.ini");
		}
		else
		{
			RenderBitmap(61519, X, Y, W, W, 0.6410998702, 0.7609999776, 0.08950000256, 0.04200005904, 1, 1, 0.0);
		}
	}
	else
	{
		RenderBitmap(61519, X, Y, W, W, 0.5159999728, 0.7609999776, 0.08950000256, 0.04200005904, 1, 1, 0.0);
	}
}

void JGetTimeBar(float X, float Y, float W, float H)
{
	time_t TimeLocal;
	struct tm * LocalT;
	time(&TimeLocal);

	LocalT = localtime(&TimeLocal);
	RenderBitmap(61519, X, Y, W, H, 0.7919999957, 0.4439999759, 0.1950000077, 0.05000000075, 1, 1, 0.0);

	char LocalTime[30];
	sprintf(LocalTime, "%2d:%02d", LocalT->tm_hour, LocalT->tm_min);

	pSetFont(pTextThis(), (int)pFontBold);
	pSetBackgroundTextColor(pTextThis(), 0, 0, 0, 0);
	SetTextColorByHDC(pTextThis(), -1);
	pDrawText(pTextThis(), (int)X, (int)Y + 4, LocalTime, (int)W, 0, (LPINT)3, 0);
}

double ScaleMap = 0.125;

void JGetEventZoom(float X, float Y, float W)
{
	if (pCheckMouseOver((int)X, (int)Y, (int)W, (int)W))
	{
		if (*(BYTE*)0x8793386 && ScaleMap != 0.125 && GetTickCount() >= EventZoom + 300)
		{
			PlayBuffer(25, 0, 0);
			ScaleMap = (ScaleMap == 0.375) ? 0.25 : 0.125;
			RenderBitmap(61519, X, Y, W, W, 0.2588, 0.3775999844, 0.1209000051, 0.05900005624, 1, 1, 0.0);
			EventZoom = GetTickCount();
		}
		else
		{
			RenderBitmap(61519, X, Y, W, W, (ScaleMap == 0.125) ? 0.3834999801 : 0.1341000199, 0.3775999844, 0.1209000051, 0.05900005624, 1, 1, 0.0);
		}
	}
	else
	{
		RenderBitmap(61519, X, Y, W, W, (ScaleMap == 0.125) ? 0.3834999801 : 0.008999999613, 0.3775999844, 0.1209000051, 0.05900005624, 1, 1, 0.0);
	}
}

void JGetEventinZoom(float X, float Y, float W)
{
	if (pCheckMouseOver((int)X, (int)Y, (int)W, (int)W))
	{
		if (*(BYTE*)0x8793386 && ScaleMap != 0.375 && GetTickCount() >= EventZoom + 300)
		{
			PlayBuffer(25, 0, 0);

			ScaleMap = (ScaleMap == 0.125) ? 0.25 : 0.375;

			RenderBitmap(61519, X, Y, W, W, 0.2588, 0.4396000206, 0.1209000051, 0.05900005624, 1, 1, 0.0);
			EventZoom = GetTickCount();
		}
		else
		{
			RenderBitmap(61519, X, Y, W, W, (ScaleMap == 0.375) ? 0.3834999801 : 0.1341000199, 0.4396000206, 0.1209000051, 0.05900005624, 1, 1, 0.0);
		}
	}
	else
	{
		RenderBitmap(61519, X, Y, W, W, (ScaleMap == 0.375) ? 0.3834999801 : 0.008999999613, 0.4396000206, 0.1209000051, 0.05900005624, 1, 1, 0.0);
	}
}

int CalDistance(int x, int y, int x1, int y1)
{
	if (x == x1 && y == y1)
	{
		return 0;
	}

	float tx = x - x1;
	float ty = y - y1;

	return sqrt(tx * tx + ty * ty);
}

void JGetDataVierport(float x, float y)
{
	float v53; // ST34_4@16
	float v48; // ST34_4@16
	float X; // ST34_4@16
	float Y; // ST38_4@16
	int v8; // [sp+2Ch] [bp-10h]@4
	signed int i; // [sp+30h] [bp-Ch]@1
	float lpObj[2]; // [sp+78h] [bp-3Ch]@1
	float lpTarget[2]; // [sp+78h] [bp-3Ch]@1
	EnableAlphaTest(1);
	float BoxPrintW; // ST20_4@12
	float BoxCurrentX; // ST70_4@12
	float BoxCurrentY; // ST6C_4@12

	BoxPrintW = (ScaleMap * 2);

	lpObj[0] = (double)*(signed int *)(dword_7BC4F04 + 172) + 2.5;
	lpObj[1] = (double)*(signed int *)(dword_7BC4F04 + 176);

	v53 = (double)(lpObj[0] + 2.5) / BoxPrintW;
	v48 = (double)(253.5 - lpObj[1]) / BoxPrintW;

	for (i = 0; i < 400; ++i)
	{
		v8 = pGetPreviewStruct(pPreviewThis(), i);
		if (v8 && *(BYTE *)(v8 + 780) && v8 != dword_7BC4F04
			&& (*(BYTE *)(v8 + 800) == 1 || *(BYTE *)(v8 + 800) == 2 || *(BYTE *)(v8 + 800) == 4))
		{
			lpTarget[0] = (double)*(signed int *)(v8 + 172) + 2.5;
			lpTarget[1] = (double)*(signed int *)(v8 + 176);

			if (ScaleMap == 0.125)
			{
				BoxCurrentX = 56.0 + ((lpObj[0] - lpTarget[0]) * ((lpObj[0] < lpTarget[0]) ? 1.1 : 1.7));
				BoxCurrentY = 46.0 - ((lpObj[1] - lpTarget[1]) * 1.4);
			}
			else if (ScaleMap == 0.25)
			{
				BoxCurrentX = 56.0 + ((lpObj[0] - lpTarget[0]) * 0.7);
				BoxCurrentY = 46.0 - ((lpObj[1] - lpTarget[1]) * 0.5);
			}
			else
			{
				BoxCurrentX = 51.0 + ((lpObj[0] - lpTarget[0]) * 0.4);
				BoxCurrentY = 46.0 - ((lpObj[1] - lpTarget[1]) * 0.4);
			}

			X = x + BoxCurrentX + (lpTarget[0] / BoxPrintW) - v53;
			Y = y + BoxCurrentY + ((253.5 - lpTarget[1]) / BoxPrintW) - v48;
			EnableAlphaTest(1);
			glColor4f(1.0, 1.0, 1.0, 1.0);

			if (*(BYTE *)(v8 + 800) != 4 && (*(BYTE *)(v8 + 800) != 2 || *(DWORD *)(v8 + 824) != 730))
			{
				sub_637E80(61519, Return2X(TransForX(X)), ReturnY(TransForY(Y)), Return2X(TransForX(10.0)), ReturnY(TransForY(10.0)), 0, 0.1349999905, 0.0, 0.1030000001, 0.05200000107);

			}
			else
			{
				if (*(WORD *)(v8 + 132) == 251) //-- herrero
				{
					sub_637E80(61519, Return2X(TransForX(X)), ReturnY(TransForY(Y)), Return2X(TransForX(10.0)), ReturnY(TransForY(10.0)), 0, 0.009999999776, 0.1319999844, 0.1030000001, 0.05200000107);
				}
				else if (*(WORD *)(v8 + 132) == 255
					|| *(WORD *)(v8 + 132) == 253) //-- posiones y barmaid
				{
					sub_637E80(61519, Return2X(TransForX(X)), ReturnY(TransForY(Y)), Return2X(TransForX(10.0)), ReturnY(TransForY(10.0)), 0, 0.1349999905, 0.1319999844, 0.1030000001, 0.05200000107);
				}
				else if (*(WORD *)(v8 + 132) == 240) //-- baul
				{
					sub_637E80(61519, Return2X(TransForX(X)), ReturnY(TransForY(Y)), Return2X(TransForX(10.0)), ReturnY(TransForY(10.0)), 0, 0.009999999776, 0.1920999587, 0.1030000001, 0.05200000107);
				}
				else if (*(WORD *)(v8 + 132) == 229
					|| *(WORD *)(v8 + 132) == 235
					|| *(WORD *)(v8 + 132) == 233
					|| *(WORD *)(v8 + 132) == 237) //-- quest
				{
					sub_637E80(61519, Return2X(TransForX(X)), ReturnY(TransForY(Y)), Return2X(TransForX(10.0)), ReturnY(TransForY(10.0)), 0, 0.0, 0.06599999219, 0.1030000001, 0.05200000107);
				}
				else
				{
					sub_637E80(61519, Return2X(TransForX(X)), ReturnY(TransForY(Y)), Return2X(TransForX(10.0)), ReturnY(TransForY(10.0)), 0, 0.1349999905, 0.06599999219, 0.1030000001, 0.05200000107);
				}
			}
			pGLSwitch();
			EnableAlphaTest(0);

			if (pCheckMouseOver((int)Return2X(TransForX(X)), (int)ReturnY(TransForY(Y)), (int)Return2X(TransForX(3.0)), (int)ReturnY(TransForY(3.0))))
			{
				pDrawToolTip((int)Return2X(TransForX(X)), (int)ReturnY(Y - TransForY(10)), (char *)(v8 + 56));
			}
		}
	}
	pGLSwitch();
	EnableAlphaTest(0);
	glColor3f(1.0, 1.0, 1.0);
}

LPCTSTR GetnameMap()
{
	if (World >= 82 && World <= 100)
	{
		return  pGetTextLine(pTextLineThis, (3182 + World - 82));
	}
	else
	{
		return pGetMapName(World);
	}
}

void MapFrameBarHelper(int a1)
{
	if (jCRenderRuud.isOpen())
	{
		return;
	}

	float v67; // [sp+94h] [bp-1094h]@172
	unsigned __int8 v87; // [sp+10EEh] [bp-3Ah]@72
	int v92; // [sp+10FCh] [bp-2Ch]@1
	char Cord[256]; // [sp+31h] [bp-FFh]@1
	float y; // ST1C_4@1
	float x; // ST18_4@1
	int JGetHelperBar; // [sp+2Ch] [bp-104h]@1
	double RectangleRotate[2][8];

	float usercurrenty; // ST74_4@3
	float usercurrentx; // ST20_4@12

	//-- 225
	RectangleRotate[0][0] = 50.0;
	RectangleRotate[1][0] = 70.0;
	//-- 180.0
	RectangleRotate[0][1] = 51.5;
	RectangleRotate[1][1] = 69.5;
	//-- 135.0
	RectangleRotate[0][2] = 52.5;
	RectangleRotate[1][2] = 68.5;
	//-- 90.0
	RectangleRotate[0][3] = 51.5;
	RectangleRotate[1][3] = 67.0;
	//-- 45.0
	RectangleRotate[0][4] = 51.0;
	RectangleRotate[1][4] = 66.0;
	//-- 360.0
	RectangleRotate[0][5] = 49.0;
	RectangleRotate[1][5] = 67.0;

	RectangleRotate[0][6] = 48.5;
	RectangleRotate[1][6] = 68.0;

	RectangleRotate[0][7] = 49.0;
	RectangleRotate[1][7] = 69.5;

	JGetHelperBar = *(DWORD *)(InstanceX() + 152);

	y = (double)*(signed int *)(JGetHelperBar + 24);
	x = (double)*(signed int *)(JGetHelperBar + 20);

	EnableAlphaTest(1);
	glColor4f(1.0, 1.0, 1.0, 1.0);
	//-- boton cerrar
	JGetButtonClosed(Return2X(TransForX(x)), ReturnY(TransForY(y)), Return2X(TransForX(15.0)));
	//-- coordenadas
	RenderBitmap(61519, Return2X(x + TransForX(16.0)), ReturnY(TransForY(y)), Return2X(TransForX(92.0)), ReturnY(TransForY(15.0)), 0.326000005, 0.004999999888, 0.6700000167, 0.04500000179, 1, 1, 0.0);
	
	wsprintf(Cord, "( %d, %d ) %s", pGetUserCoorX, pGetUserCoorY, GetnameMap());

	pSetFont(pTextThis(), (int)pFontNormal);
	pSetBackgroundTextColor(pTextThis(), 0, 0, 0, 0);
	SetTextColorByHDC(pTextThis(), -1);
	pDrawText(pTextThis(), Return2X(x + TransForX(20.0)), ReturnY(y + TransForY(3.0)), Cord, 88, 0, (LPINT)1, 0);

	 if (MiniMap == 1)
	{
		//RenderBitmap(61520, x + 9.5, y + 22.5, 82.0, 82.0, 0.3729999959, 0.03899973631, 0.2620999813, 0.2600000203, 1, 1, 0.0);
		if (pWinWidth == 800 || pWinWidth == 1360)
		{
			GetDrawCircle(71519, Return2X(x + TransForX(9.0)), ReturnY(y) + TransForY(20), Return2X(TransForX(84.0)), 0.5, 0.5, 0.5, 1, 1, 0.0);
			usercurrentx = (double)(*(signed int *)(dword_7BC4F04 + 172) + 2.5) / 256.0;
			usercurrenty = (double)(253.5 - *(signed int *)(dword_7BC4F04 + 176)) / 256.0;
			GetDrawCircle(550000, Return2X(x + TransForX(9.0)), ReturnY(y) + TransForY(20), Return2X(TransForX(84.0)), usercurrentx, usercurrenty, ScaleMap, 1, 1, 0.0);
		}
		else if (pWinWidth == 1024 || pWinWidth == 1280 || pWinWidth == 1440)
		{
			GetDrawCircle(71519, Return2X(x + TransForX(9.0)), ReturnY(y) + TransForY(14), Return2X(TransForX(84.0)), 0.5, 0.5, 0.5, 1, 1, 0.0);
			usercurrentx = (double)(*(signed int *)(dword_7BC4F04 + 172) + 2.5) / 256.0;
			usercurrenty = (double)(253.5 - *(signed int *)(dword_7BC4F04 + 176)) / 256.0;
			GetDrawCircle(550000, Return2X(x + TransForX(9.0)), ReturnY(y) + TransForY(14), Return2X(TransForX(84.0)), usercurrentx, usercurrenty, ScaleMap, 1, 1, 0.0);
		}

		JGetDataVierport(x + 3, y + 19.0);

		v92 = *(DWORD *)0x7BC4F04 + 776;
		v87 = (unsigned __int8)(signed int)((*(float *)(v92 + 272) + 22.5) / 360.0 * 8.0 + 1.0) % 8;
		v67 = 135 + (45 * v87);
		sub_637E80(61519, Return2X(x + TransForX(RectangleRotate[0][(int)v87])), ReturnY(y + TransForY(RectangleRotate[1][(int)v87] - 5)), Return2X(TransForX(12.0)), ReturnY(TransForY(12.0)), v67, 0.0, 0.0, 0.1030000001, 0.05200000107);

		//-- carcaza
		RenderBitmap(61519, Return2X(x + TransForX(5.0)), ReturnY(y + TransForY(18.0)), Return2X(TransForX(92.0)), ReturnY(TransForY(92.0)), 0.3700000048, 0.06200000271, 0.5769999027, 0.2899999917, 1, 1, 0.0);
		//-- Butoon menu
		JShowButtonSlash(Return2X(x + TransForX(1)), ReturnY(y + TransForY(23.0)), Return2X(TransForX(18.0)), 0.8768191338);
		JGetTimeBar(Return2X(x + TransForX(36)), ReturnY(y + TransForY(108)), Return2X(TransForX(30)), ReturnY(TransForY(17)));

		JGetEventZoom(Return2X(x), ReturnY(y + TransForY(77.0)), Return2X(TransForX(18.0))); //-- zoom in
		JGetEventinZoom(Return2X(x + TransForX(14.0)), ReturnY(y + TransForY(93.0)), Return2X(TransForX(18.0))); //-- walk away
		//0.6899006367
		JExecuteButtonCameraRestore(Return2X(x + TransForX(71.0)), ReturnY(y + TransForY(93.0)), Return2X(TransForX(18.0)), 0.7522068024); //-- Restaurar Camera
		JExecuteButtonCameraInit(Return2X(x + TransForX(85.0)), ReturnY(y + TransForY(75.0)), Return2X(TransForX(18.0))); //-- Activar 3D

		ChangeButtonInfo((char *)(JGetHelperBar + 36), (int)Return2X(x + TransForX(86.0)), (int)ReturnY(y + TransForY(37.0)), (int)Return2X(TransForX(18.0)), (int)ReturnY(TransForY(18.0)));
		JExecuteButtonConfig(Return2X(x + TransForX(88.0)), ReturnY(y + TransForY(37.0)), Return2X(TransForX(18.0)));
		//--
		ChangeButtonInfo((char *)(JGetHelperBar + 208), (int)Return2X(x + TransForX(88.0)), (int)ReturnY(y + TransForY(56.0)), (int)Return2X(TransForX(18.0)), (int)ReturnY(TransForY(18.0)));
		ChangeButtonInfo((char *)(JGetHelperBar + 380), (int)Return2X(x + TransForX(88.0)), (int)ReturnY(y + TransForY(56.0)), (int)Return2X(TransForX(18.0)), (int)ReturnY(TransForY(18.0)));
		JExecuteButtonHelper(Return2X(x + TransForX(90.0)), ReturnY(y + TransForY(56.0)), Return2X(TransForX(18.0)));
		//--
		pGLSwitch();
		EnableAlphaTest(0);
		//--
		EnableAlphaBlend();
		RenderBitmap(91520, Return2X(x + TransForX(9.5)), ReturnY(y + TransForY(22.5)), Return2X(TransForX(82.0)), ReturnY(TransForY(82.0)), 0.3729999959, 0.03899973631, 0.2620999813, 0.2600000203, 1, 1, 0.0);
		pGLSwitch();
		EnableAlphaTest(0);
	}
}

bool JGetCheckCursor(int x, int y, int w, int h)
{
	int JGetHelperBar; // [sp+2Ch] [bp-104h]@1
	bool Radar = false;
	bool CheckRuud = false;

	if (jCRenderRuud.isOpen())
	{
		CheckRuud = jCRenderRuud.CheckMouseOver();
	}

	JGetHelperBar = *(DWORD *)(InstanceX() + 152);

	y = *(signed int *)(JGetHelperBar + 24);
	x = *(signed int *)(JGetHelperBar + 20);

	return pCheckMouseOver(x, y, 115, 120) || CheckRuud;
}


char JGetBarTime(int This)
{
	return 1;
}

__declspec(naked) void MoveTextArrow()
{
	static DWORD Addr_main = 0x007DF898;
	static DWORD MOVEY = 99;

	_asm
	{
		MOV ECX, DWORD PTR SS : [EBP - 0x4]
			ADD ECX, MOVEY; |
			PUSH ECX; / Arg2
			MOV EDX, DWORD PTR SS : [EBP - 0x8]; |
			MOV EAX, DWORD PTR DS : [EDX + 0x10]; |
			PUSH EAX; | Arg1
			MOV ECX, DWORD PTR SS : [EBP - 0x8]; |
			JMP[Addr_main]
	}
}

void __thiscall CMacroUIEx::RenderInterfaceLeft(int thisa)
{

	POINT g_dir; // eax@9

	g_dir.x = *(DWORD *)(thisa + 16) /* +GetScreenWidth2() - 63 */ ;
	g_dir.y = *(DWORD *)(thisa + 20);

	if (Defineclass(*(BYTE *)(Hero + 19)) == 2 && RenderNumArrow(thisa, g_dir.x, g_dir.y))
	{
		g_dir.y += 11;
	}
	
	if (Defineclass(*(BYTE *)(Hero + 19)) == 2)
	{
		if (RenderSummonMonsterLife(thisa, g_dir.x, g_dir.y))
			g_dir.y += 24;
	};
}

BYTE __thiscall CMacroUIEx::lpUI_ArrowCount(int thisa, int PosX, int __DirY)
{
	if (MiniMap == 1)
	{
		__DirY = __DirY - 10;
		PosX = PosX + 115;
	}
	return ArrowCount(thisa, (int)PosX, __DirY - 10);
}

BOOL __thiscall CMacroUIEx::lpUI_SummonMonster(int thisa, int PosX, int __DirY)
{
	if (MiniMap == 1)
	{
		__DirY = __DirY;
		PosX = PosX + 87;
	}
	return RenderSummonMonsterLife(thisa, (int)PosX, __DirY);
}

BYTE __thiscall CMacroUIEx::lpUI_HelperMonster(int thisa, int PosX, int __DirY)
{
	if (MiniMap == 1)
	{
		__DirY = __DirY;
		PosX = PosX + 87;
	}
	return EquipedHelperLife(thisa, (int)PosX, __DirY);
}

void CMacroUIEx::Load()
{
	SetCompleteHook(0xE8, 0x007F76CD, &OffHelper);

	if (gProtect.m_MainInfo.MiniMapType == 2)
	{
		//-- Minimapa + Muhelper
	//	SetCompleteHook(0xE9, 0x007DF88A, &MoveTextArrow);

		SetCompleteHook(0xE8, 0x007DF898, &lpUI_ArrowCount);

//		SetCompleteHook(0xE8, 0x007DF930, &lpUI_SummonMonster);

//		SetCompleteHook(0xE8, 0x007DF8BB, &lpUI_HelperMonster);

		SetCompleteHook(0xE8, 0x007D2B3D, &JGetCheckCursor);
		SetCompleteHook(0xE9, 0x007D2BC0, &MapFrameBarHelper);
		SetCompleteHook(0xE9, 0x0080B8E0, &JGetBarTime);

	//	SetCompleteHook(0xE8, 0x007DF83E, &CMacroUIEx::RenderInterfaceLeft);
	}

	if (gProtect.m_MainInfo.MiniMapType == 1)
	{
		if (gProtect.m_MainInfo.CustomInterfaceType == 3 || gProtect.m_MainInfo.CustomInterfaceType == 4)
		{
			SetCompleteHook(0xE9, 0x007D2BC0, this->RenderFrame);
			SetCompleteHook(0xE9, 0x0080B8E0, &BarTime);
			SetCompleteHook(0xE9, 0x007D26B5, &MuHelperRemake_01);
			SetCompleteHook(0xE9, 0x007D2751, &MuHelperRemake_02);
			SetCompleteHook(0xE9, 0x007D27FC, &MuHelperRemake_03);
		}
		else
		{
			SetCompleteHook(0xE9, 0x007D26B5, &MuHelperRemake2_01);
			SetCompleteHook(0xE9, 0x007D2751, &MuHelperRemake2_02);
			SetCompleteHook(0xE9, 0x007D27FC, &MuHelperRemake2_03);
			SetCompleteHook(0xE9, 0x007D2BC0, this->RenderHelperFrame);
		}
	}
}
