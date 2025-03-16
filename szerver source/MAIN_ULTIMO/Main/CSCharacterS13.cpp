#include "stdafx.h"
#include "CSCharacterS13.h"
#include "Util.h"
#include "Interface.h"
#include "zzzMathLib.h"
#include "Offset.h"
#include "User.h"
#include "Defines.h"
#include "TMemory.h"
#include "import.h"
#include "MultiSelect.h"
#include "SelectChar.h"
#include "WindowsStruct.h"
#include "PrintPlayer.h"

#include "InfoLog.h"

CSCharacterS13 gCSCharacterS13;

int MAINCHAR; // [sp+8h] [bp-C0h]@1

bool JCCharEventButton(int x, int y, int w, int h)
{
	return pCheckMouseOver(x, y, w, h) && *(BYTE*)0x8793386;
}

//----- (00416210) --------------------------------------------------------
int sub_416210(int a1, int a5, int a6, int a7)
{
	int v16; // [sp+8h] [bp-Ch]@1
	int i; // [sp+10h] [bp-4h]@3

	v16 = a1;
	//sub_4161D0(a1, a2, a3);
	*(float *)(v16 + 20) = (double)a5;
	*(float *)(v16 + 24) = (double)a6;
	*(DWORD *)(v16 + 16) = a7;

	*(float *)(v16 + 40) = *(float *)(v16 + 8) - *(float *)(v16 + 24);
	*(float *)(v16 + 44) = *(float *)(v16 + 20);
	*(float *)(v16 + 48) = *(float *)(v16 + 8) - *(float *)(v16 + 24);
	*(float *)(v16 + 52) = *(float *)(v16 + 20);

	return 1;
}

//----- (00416640) --------------------------------------------------------
int __fastcall sub_416640(int a1, int a2, signed int a3, signed int a4, char a5)
{
	int result; // eax@1
	float v6; // [sp+4h] [bp-8h]@6
	float v7; // [sp+8h] [bp-4h]@2

	result = a5 & 1;
	if (a5 & 1)
	{
		v7 = *(float *)(a1 + 52) - *(float *)(a1 + 28);
		if (*(DWORD *)(a1 + 156) & 2)
		{
			*(float *)(a1 + 44) = (double)a3 + *(float *)(a1 + 20) - *(float *)(a1 + 92);
			*(float *)(a1 + 52) = *(float *)(a1 + 44);
			*(float *)(a1 + 36) = *(float *)(a1 + 52) - v7;
			result = a1;
			*(float *)(a1 + 28) = *(float *)(a1 + 36);
		}
		else
		{
			*(float *)(a1 + 36) = (double)a3 - *(float *)(a1 + 92);
			*(float *)(a1 + 28) = *(float *)(a1 + 36);
			*(float *)(a1 + 44) = *(float *)(a1 + 28) + v7;
			result = a1;
			*(float *)(a1 + 52) = *(float *)(a1 + 44);
		}
	}
	if (a5 & 2)
	{
		v6 = *(float *)(a1 + 32) - *(float *)(a1 + 40);
		if (*(DWORD *)(a1 + 156) & 1)
		{
			*(float *)(a1 + 48) = *(float *)(a1 + 8) - (double)a4 - *(float *)(a1 + 24) + *(float *)(a1 + 96);
			*(float *)(a1 + 40) = *(float *)(a1 + 48);
			*(float *)(a1 + 56) = *(float *)(a1 + 40) + v6;
			result = a1;
			*(float *)(a1 + 32) = *(float *)(a1 + 56);
		}
		else
		{
			*(float *)(a1 + 56) = *(float *)(a1 + 8) - (double)a4 + *(float *)(a1 + 96);
			*(float *)(a1 + 32) = *(float *)(a1 + 56);
			*(float *)(a1 + 48) = *(float *)(a1 + 32) - v6;
			result = a1;
			*(float *)(a1 + 40) = *(float *)(a1 + 48);
		}
	}
	return result;
}

//----- (00401C20) --------------------------------------------------------
signed int  sub_401C20(int _this)
{
	return (int)(*(float *)(_this + 28));
}

//----- (00401C40) --------------------------------------------------------
signed int sub_401C40(int _this)
{
	return (int)(*(float *)(_this + 8) - *(float *)(_this + 32));
}

//----- (00401C60) --------------------------------------------------------
signed int sub_401C60(int _this)
{
	return (int)(*(float *)(_this + 52) - *(float *)(_this + 28));
}

//----- (00401C80) --------------------------------------------------------
signed int sub_401C80(int _this)
{
	return (int)(*(float *)(_this + 32) - *(float *)(_this + 40));
}

void JCSetTexture(int _this, int textura)
{
	*(DWORD *)(_this + 16) = textura;
}

__declspec(naked) void ScaleModelLogo()
{
	static DWORD Addr_JMP = 0x004045CF;
	static float Scale = -600.0;
	static float movedown = 46.0;

	if (pWinWidth > 1024)
	{
		Scale = -600.0;
	}
	else
	{
		Scale = -750.0;
	}

	_asm
	{
		FLD DWORD PTR DS : [0xD22C14]
			FSTP DWORD PTR SS : [EBP - 0x18]
			FLD DWORD PTR DS : [Scale]
			FSTP DWORD PTR SS : [EBP - 0x14]
			FLD DWORD PTR DS : [movedown]
			FSTP DWORD PTR SS : [EBP - 0x10]
			FLD DWORD PTR DS : [0xD22C08]
			FSTP DWORD PTR SS : [EBP - 0xC]
			FLDZ
			FSTP DWORD PTR SS : [EBP - 0x8]
			FLDZ
			FSTP DWORD PTR SS : [EBP - 0x4]
			JMP[Addr_JMP]
	}
}

//----- (00403320) --------------------------------------------------------
void sub_403320(int _this, signed int x, int y)
{
	int v3; // edx@1
	int v4; // edx@7
	signed int v5; // eax@8
	int v6; // ST08_4@8
	signed int v7; // eax@8
	int v8; // eax@8
	int v10; // [sp+8h] [bp-14h]@1
	int v11; // [sp+Ch] [bp-10h]@1
	signed int v12; // [sp+10h] [bp-Ch]@1
	signed int i; // [sp+14h] [bp-8h]@1
	signed int v14; // [sp+18h] [bp-4h]@1

	v10 = _this;
	//-- Logo modelo
	if (pWinWidth > 1024)
	{
		(*(void(__thiscall **)(int, signed int, int))(*(DWORD *)(_this + 60) + 8))(_this + 60, x - 50, y - 50);
	}
	else
	{
		(*(void(__thiscall **)(int, signed int, int))(*(DWORD *)(_this + 60) + 8))(_this + 60, x /*- 150*/, y - 50);
	}
	if (pWinWidth > 800)
	{
		v12 = x + 466;
		v11 = y - 35;
		//-- estadisticas del personaje
		sub_416210(v10 + 288, 108, 100, 51522);
		sub_416640(v10 + 288, x + 333, x + 334, v11 + 3, 3);
		//v14 = sub_401C80(v10 + 624);
		for (i = 0; i < 7; ++i)
		{
			//-- boton para elegir personaje a crear
			sub_416210(v10 + 224 * i + 624, 150, 26, 51522);
			sub_416640(v10 + 224 * i + 624, v10, v12, v11 + 29 * i, 3);
		}

		sub_416210(v10 + 456, 454, 51, 51522);
		sub_416640(v10 + 456, y + 265, x, y + 265, 3); //-- texto informativo del personaje

		sub_416210(v10 + 2192, 72, 26, 51522);
		sub_416640(v10 + 2192, y + 255, x + 377, y + 236, 3); //-- boton ok crear

		sub_416210(v10 + 2416, 72, 26, 51522);
		sub_416640(v10 + 2416, x + 335, x + 377, y + 270, 3); //-- boton cancelar

		JCSetTexture(v10 + 120, 51522);
		sub_416640(v10 + 120, v4, x, y + 220, 3); //-- cha_id
	}
	else
	{
		v12 = x + 416;
		v11 = y + 16;
		//-- estadisticas del personaje
		sub_416210(v10 + 288, 108, 100, 51522);
		sub_416640(v10 + 288, x + 304, x + 304, y + 15, 3);
		//v14 = sub_401C80(v10 + 624);
		for (i = 0; i < 7; ++i)
		{
			//-- boton para elegir personaje a crear
			sub_416210(v10 + 224 * i + 624, 108, 25, 51522);
			sub_416640(v10 + 224 * i + 624, v10, v12, v11 + 22 * i, 3);
		}

		sub_416210(v10 + 456, 254, 51, 51522);
		sub_416640(v10 + 456, y + 265, x + 45, y + 245, 3); //-- texto informativo del personaje

		sub_416210(v10 + 2192, 54, 24, 51522);
		sub_416640(v10 + 2192, y + 255, x + 347, y + 230, 3); //-- boton ok crear

		sub_416210(v10 + 2416, 54, 24, 51522);
		sub_416640(v10 + 2416, x + 335, x + 347, y + 254, 3); //-- boton cancelar

		JCSetTexture(v10 + 120, 51522);
		sub_416640(v10 + 120, v4, x + 30, y + 210, 3); //-- cha_id
	}

	if (*(DWORD*)0xE60960 == 1)
	{
		v5 = sub_401C40(v10 + 120);
		v6 = (int)((double)(v5 + 21) / *(float*)0xE7C3D8);
		v7 = sub_401C20(v10 + 120);
		v8 = (int)((double)(v7 + 65) / *(float*)0xE7C3D4);
		//--
		SetBoundInputField(*(DWORD*)0xE8C544, v8, v6); //-- textbox
	}
}

__declspec(naked) void SetLocationButtonChar()
{
	static DWORD Addr_JMP = 0x00403516;
	static DWORD _this = 0x004033C7;
	static DWORD a2 = 0x004033C7;
	static DWORD a3 = 0x004033C7;

	_asm
	{
		MOV DWORD PTR SS : [EBP - 0x14], ECX
			MOV ECX, DWORD PTR SS : [EBP - 0x14]
			MOV _this, ECX
			MOV ECX, DWORD PTR SS : [EBP + 0x8]
			MOV a2, ECX
			MOV ECX, DWORD PTR SS : [EBP + 0xC]
			MOV a3, ECX
	}

	sub_403320(_this, a2, a3);

	_asm
	{
		JMP[Addr_JMP]
	}
}

//----- (00403FA0) --------------------------------------------------------
void initCharacterScene(BYTE JCByte)
{
	double JCBotonPush = 0.714400053;
	double JCBotonOnPush = 0.5710000992;
	double JCBotonBlocked = 0.8572000861;
	double JCRangeX = 223.0;
	double JCRangeY = 70.0;
	int GetCharactername[8] = { 20, 21, 22, 23, 24, 1687, 3150, 3175 };

	JCRangeX = pWinWidth / pWinHeightReal / 2 - 185.93749294125;

	EnableAlphaTest(1);
	glColor3f(1.0, 1.0, 1.0);

	if (pWinWidth == 1360)
	{
		RenderBitmap(98000, Return2X(JCRangeX + TransForX(353.0)), JCRangeY + 18.0, Return2X(TransForX(73.21875)), 174.39375, 0.0, 0.0, 0.1198597625, 0.3259598017, 1, 1, 0.0); //-- fondo de guerra

		RenderBitmap(98000, Return2X(JCRangeX + TransForX(333.0)), JCRangeY, Return2X(TransForX(195.625009974375)), 223.12500372375, 0.0, 0.5699999928, 0.3048597574, 0.3519598544, 1, 1, 0.0); //-- marco de botones

		RenderBitmap(98000, Return2X(TransForX(JCRangeX)), JCRangeY + 142.0, Return2X(TransForX(371.8749858825)), 211.249992133125, 0.3125000298, 0.5682999492, 0.5599597692, 0.3250873685, 1, 1, 0.0); //-- estilo del personaje

		pSetFont(pTextThis(), *(DWORD*)0xE8C58C);

		for (int i = 0; i < 10; i++)
		{
			if (i < 7)
			{
				if (JCCharEventButton((int)(Return2X(JCRangeX + TransForX(436.0))), (int)(JCRangeY + (i * 18.1) + 21.0), Return2X(TransForX((int)93.0)), (int)17.0))
				{
					RenderBitmap(98000, Return2X(JCRangeX + TransForX(436.0)), JCRangeY + (i * 18.1) + 21.0, Return2X(TransForX(93.0)), 17.0, JCBotonOnPush, 0.8979994655, 0.1432961673, 0.02558737807, 1, 1, 0.0);
				}
				else
				{
					RenderBitmap(98000, Return2X(JCRangeX + TransForX(436.0)), JCRangeY + (i * 18.1) + 21.0, Return2X(TransForX(93.0)), 17.0, (*(BYTE*)0x7BD0483 == i) ? JCBotonOnPush : JCBotonPush, 0.8979994655, 0.1432961673, 0.02558737807, 1, 1, 0.0);
					if (*(BYTE*)0x7BD0483 != i)
					{
						RenderBitmap(98000, Return2X(JCRangeX + TransForX(436.0)), JCRangeY + (i * 18.1) + 21.0, Return2X(TransForX(93.0)), 17.0, JCBotonBlocked, 0.8979994655, 0.1432961673, 0.02558737807, 1, 1, 0.0);
					}
				}

			}
			else
			{
				//RenderBitmap(98000, JCRangeX + 336.0, JCRangeY + ( i * 18.1 ) + 21.0, 93.0, 17.0, JCBotonPush, 0.8979994655, 0.1432961673, 0.02558737807, 1, 1, 0.0);
				RenderBitmap(98000, Return2X(JCRangeX + TransForX(436.0)), JCRangeY + (i * 18.1) + 21.0, Return2X(TransForX(93.0)), 17.0, JCBotonBlocked, 0.8979994655, 0.1432961673, 0.02558737807, 1, 1, 0.0);
				RenderBitmap(98000, Return2X(JCRangeX + TransForX(436.0)), JCRangeY + (i * 18.1) + 21.0, Return2X(TransForX(93.0)), 17.0, JCBotonBlocked, 0.8979994655, 0.1432961673, 0.02558737807, 1, 1, 0.0);
				pSetTextColor(pTextThis(), 0xFFu, 0xFFu, 0xFFu, 0xFFu);
				pDrawText(pTextThis(), Return2X(JCRangeX + TransForX(406.0)), (int)(JCRangeY + (i * 18.1) + 27.0), "Locked", 93.0, 0, (LPINT)3, 0);
			}
		}

		if (pCheckMouseOver(Return2X(JCRangeX + TransForX(360)), (int)(JCRangeY + 190), Return2X(TransForX(46)), (int)20))
		{
			if (*(BYTE*)0x8793386)
			{
				RenderBitmap(98000, Return2X(JCRangeX + TransForX(360)), JCRangeY + 190, Return2X(TransForX(46)), 20, 0.200000003, 0.004999999888, 0.06975978613, 0.03259783983, 1, 1, 0.0); //-- estilo del personaje
			}
			else
			{
				RenderBitmap(98000, Return2X(JCRangeX + TransForX(360)), JCRangeY + 190, Return2X(TransForX(46)), 20, 0.1250000298, 0.004999999888, 0.06975978613, 0.03259783983, 1, 1, 0.0); //-- estilo del personaje
			}
		}
		else
		{
			RenderBitmap(98000, Return2X(JCRangeX + TransForX(360)), JCRangeY + 190, Return2X(TransForX(46)), 20, 0.2760000527, 0.004999999888, 0.06975978613, 0.03259783983, 1, 1, 0.0); //-- estilo del personaje
		}

		if (pCheckMouseOver(Return2X(JCRangeX + TransForX(360)), (int)(JCRangeY + 211), Return2X(TransForX(46)), (int)20))
		{
			if (*(BYTE*)0x8793386)
			{
				RenderBitmap(98000, Return2X(JCRangeX + TransForX(360)), JCRangeY + 211, Return2X(TransForX(46)), 20, 0.200000003, 0.004999999888, 0.06975978613, 0.03259783983, 1, 1, 0.0); //-- estilo del personaje
			}
			else
			{
				RenderBitmap(98000, Return2X(JCRangeX + TransForX(360)), JCRangeY + 211, Return2X(TransForX(46)), 20, 0.1250000298, 0.004999999888, 0.06975978613, 0.03259783983, 1, 1, 0.0); //-- estilo del personaje
			}
		}
		else
		{
			RenderBitmap(98000, Return2X(JCRangeX + TransForX(360)), JCRangeY + 211, Return2X(TransForX(46)), 20, 0.2760000527, 0.004999999888, 0.06975978613, 0.03259783983, 1, 1, 0.0); //-- estilo del personaje
		}

		pSetTextColor(pTextThis(), 0xFFu, 0xFFu, 0xFFu, 0xFFu);
		pDrawText(pTextThis(), Return2X(JCRangeX + TransForX(350)), (int)(JCRangeY + 195), pGetTextLine(pTextLineThis, 1412), 46, 0, (LPINT)3, 0);
		pDrawText(pTextThis(), Return2X(JCRangeX + TransForX(350)), (int)(JCRangeY + 216), pGetTextLine(pTextLineThis, 229), 46, 0, (LPINT)3, 0);

		pDrawText(pTextThis(), Return2X(JCRangeX + TransForX(80.0)), (int)(JCRangeY + 192.0), "Character N", 70, 0, (LPINT)3, 0);

		pSetTextColor(pTextThis(), 0xFFu, 0xBDu, 0x19u, 0xFFu);
		pDrawText(pTextThis(), Return2X(JCRangeX + TransForX(340.0)), (int)(JCRangeY + 7.0), pGetTextLine(pTextLineThis, GetCharactername[*(BYTE*)0x7BD0483]), 70, 0, (LPINT)3, 0);
		pSetFont(pTextThis(), *(DWORD*)0xE8C588);
	}

	if (pWinWidth >= 800 && pWinWidth <= 1024)
	{
		RenderBitmap(98000, JCRangeX + 257.0, JCRangeY + 18.0, 73.21875, 174.39375, 0.0, 0.0, 0.1198597625, 0.3259598017, 1, 1, 0.0); //-- fondo de guerra

		RenderBitmap(98000, JCRangeX + 235.0, JCRangeY, 195.625009974375, 223.12500372375, 0.0, 0.5699999928, 0.3048597574, 0.3519598544, 1, 1, 0.0); //-- marco de botones

		RenderBitmap(98000, JCRangeX, JCRangeY + 142.0, 371.8749858825, 211.249992133125, 0.3125000298, 0.5682999492, 0.5599597692, 0.3250873685, 1, 1, 0.0); //-- estilo del personaje

		pSetFont(pTextThis(), *(DWORD*)0xE8C58C);

		for (int i = 0; i < 10; i++)
		{
			if (i < 7)
			{
				if (JCCharEventButton((int)(JCRangeX + 336.0), (int)(JCRangeY + (i * 18.1) + 21.0), (int)93.0, (int)17.0))
				{
					RenderBitmap(98000, JCRangeX + 336.0, JCRangeY + (i * 18.1) + 21.0, 93.0, 17.0, JCBotonOnPush, 0.8979994655, 0.1432961673, 0.02558737807, 1, 1, 0.0);
				}
				else
				{
					RenderBitmap(98000, JCRangeX + 336.0, JCRangeY + (i * 18.1) + 21.0, 93.0, 17.0, (*(BYTE*)0x7BD0483 == i) ? JCBotonOnPush : JCBotonPush, 0.8979994655, 0.1432961673, 0.02558737807, 1, 1, 0.0);
					if (*(BYTE*)0x7BD0483 != i)
					{
						RenderBitmap(98000, JCRangeX + 336.0, JCRangeY + (i * 18.1) + 21.0, 93.0, 17.0, JCBotonBlocked, 0.8979994655, 0.1432961673, 0.02558737807, 1, 1, 0.0);
					}
				}

			}
			else
			{
				//RenderBitmap(98000, JCRangeX + 336.0, JCRangeY + ( i * 18.1 ) + 21.0, 93.0, 17.0, JCBotonPush, 0.8979994655, 0.1432961673, 0.02558737807, 1, 1, 0.0);
				RenderBitmap(98000, JCRangeX + 336.0, JCRangeY + (i * 18.1) + 21.0, 93.0, 17.0, JCBotonBlocked, 0.8979994655, 0.1432961673, 0.02558737807, 1, 1, 0.0);
				RenderBitmap(98000, JCRangeX + 336.0, JCRangeY + (i * 18.1) + 21.0, 93.0, 17.0, JCBotonBlocked, 0.8979994655, 0.1432961673, 0.02558737807, 1, 1, 0.0);
				pSetTextColor(pTextThis(), 0xFFu, 0xFFu, 0xFFu, 0xFFu);
				pDrawText(pTextThis(), (int)(JCRangeX + 336.0), (int)(JCRangeY + (i * 18.1) + 27.0), "Locked", (int)93.0, 0, (LPINT)3, 0);
			}
		}

		if (pCheckMouseOver((int)(JCRangeX + 280), (int)(JCRangeY + 190), (int)46, (int)20))
		{
			if (*(BYTE*)0x8793386)
			{
				RenderBitmap(98000, JCRangeX + 280, JCRangeY + 190, 46, 20, 0.200000003, 0.004999999888, 0.06975978613, 0.03259783983, 1, 1, 0.0); //-- estilo del personaje
			}
			else
			{
				RenderBitmap(98000, JCRangeX + 280, JCRangeY + 190, 46, 20, 0.1250000298, 0.004999999888, 0.06975978613, 0.03259783983, 1, 1, 0.0); //-- estilo del personaje
			}
		}
		else
		{
			RenderBitmap(98000, JCRangeX + 280, JCRangeY + 190, 46, 20, 0.2760000527, 0.004999999888, 0.06975978613, 0.03259783983, 1, 1, 0.0); //-- estilo del personaje
		}

		if (pCheckMouseOver((int)(JCRangeX + 280), (int)(JCRangeY + 211), (int)46, (int)20))
		{
			if (*(BYTE*)0x8793386)
			{
				RenderBitmap(98000, JCRangeX + 280, JCRangeY + 211, 46, 20, 0.200000003, 0.004999999888, 0.06975978613, 0.03259783983, 1, 1, 0.0); //-- estilo del personaje
			}
			else
			{
				RenderBitmap(98000, JCRangeX + 280, JCRangeY + 211, 46, 20, 0.1250000298, 0.004999999888, 0.06975978613, 0.03259783983, 1, 1, 0.0); //-- estilo del personaje
			}
		}
		else
		{
			RenderBitmap(98000, JCRangeX + 280, JCRangeY + 211, 46, 20, 0.2760000527, 0.004999999888, 0.06975978613, 0.03259783983, 1, 1, 0.0); //-- estilo del personaje
		}

		pSetTextColor(pTextThis(), 0xFFu, 0xFFu, 0xFFu, 0xFFu);
		pDrawText(pTextThis(), (int)(JCRangeX + 280), (int)(JCRangeY + 195), pGetTextLine(pTextLineThis, 1412), 46, 0, (LPINT)3, 0);
		pDrawText(pTextThis(), (int)(JCRangeX + 280), (int)(JCRangeY + 216), pGetTextLine(pTextLineThis, 229), 46, 0, (LPINT)3, 0);

		pDrawText(pTextThis(), (int)(JCRangeX + 1.0), (int)(JCRangeY + 192.0), "Character N", 70, 0, (LPINT)3, 0);

		pSetTextColor(pTextThis(), 0xFFu, 0xBDu, 0x19u, 0xFFu);
		pDrawText(pTextThis(), (int)(JCRangeX + 259.0), (int)(JCRangeY + 7.0), pGetTextLine(pTextLineThis, GetCharactername[*(BYTE*)0x7BD0483]), 70, 0, (LPINT)3, 0);
		pSetFont(pTextThis(), *(DWORD*)0xE8C588);
	}

	EnableAlphaTest(JCByte);
	glColor3f(1.0, 1.0, 1.0);
}

signed int sub_9CEBF0(double a1)
{
	return (signed int)a1;
}
//----- (00403FA0) --------------------------------------------------------
void sub_403FA0(int _this)
{
	signed int v8; // eax@11
	int v11; // ST04_4@11
	int v12; // ST00_4@11
	int v17; // ST00_4@11
	int v48; // [sp+2Ch] [bp-7Ch]@7
	int i; // [sp+A4h] [bp-4h]@1

	LPCTSTR GetCharacterInfo[40] =
	{
		//-- DW
		(LPCTSTR)&*(LPVOID*)0xD22AE0,
		(LPCTSTR)&*(LPVOID*)0xD22AE4,
		(LPCTSTR)&*(LPVOID*)0xD22AE8,
		(LPCTSTR)&*(LPVOID*)0xD22AEC, "0",
		//-- DK
		(LPCTSTR)&*(LPVOID*)0xD22AF0,
		(LPCTSTR)&*(LPVOID*)0xD22AF4,
		(LPCTSTR)&*(LPVOID*)0xD22AF8,
		(LPCTSTR)&*(LPVOID*)0xD22AFC, "0",
		//-- ELF
		(LPCTSTR)&*(LPVOID*)0xD22B00,
		(LPCTSTR)&*(LPVOID*)0xD22B04,
		(LPCTSTR)&*(LPVOID*)0xD22B08,
		(LPCTSTR)&*(LPVOID*)0xD22B0C, "0",
		//-- MG
		(LPCTSTR)&*(LPVOID*)0xD22B10,
		(LPCTSTR)&*(LPVOID*)0xD22B14,
		(LPCTSTR)&*(LPVOID*)0xD22B18,
		(LPCTSTR)&*(LPVOID*)0xD22B1C, "0",
		//-- DL
		(LPCTSTR)&*(LPVOID*)0xD22B20,
		(LPCTSTR)&*(LPVOID*)0xD22B24,
		(LPCTSTR)&*(LPVOID*)0xD22B28,
		(LPCTSTR)&*(LPVOID*)0xD22B2C,
		(LPCTSTR)&*(LPVOID*)0xD22B50,
		//-- SUM
		(LPCTSTR)&*(LPVOID*)0xD22B30,
		(LPCTSTR)&*(LPVOID*)0xD22B34,
		(LPCTSTR)&*(LPVOID*)0xD22B38,
		(LPCTSTR)&*(LPVOID*)0xD22B3C, "0",
		//-- RF
		(LPCTSTR)&*(LPVOID*)0xD22B40,
		(LPCTSTR)&*(LPVOID*)0xD22B44,
		(LPCTSTR)&*(LPVOID*)0xD22B48,
		(LPCTSTR)&*(LPVOID*)0xD22B4C, "0"
	};

	v48 = sub_401C20(_this + 288) + 22;

	pSetFont(pTextThis(), *(DWORD*)0xE8C58C);

	if (*(BYTE *)(_this + 2800) != 1)
	{
		v8 = sub_401C40(_this + 288);
		v17 = sub_9CEBF0((double)v48 / *(float*)0xE7C3D4);

		if (pWinWidth <= 1024)
		{
			v12 = sub_9CEBF0((double)(v48 + 60) / *(float*)0xE7C3D4);
			//-- informacion
			SetTextColorByHDC(pTextThis(), -16730881);

			v11 = sub_9CEBF0((double)(v8 + 8) / *(float*)0xE7C3D8);
			pDrawText(pTextThis(), v12, v11 + 5, GetCharacterInfo[*(BYTE*)0x7BD0483 * 5], 0, 0, (LPINT)1, 0);

			v11 = sub_9CEBF0((double)(v8 + 36) / *(float*)0xE7C3D8);
			pDrawText(pTextThis(), v12, v11 + 5, GetCharacterInfo[*(BYTE*)0x7BD0483 * 5 + 1], 0, 0, (LPINT)1, 0);

			v11 = sub_9CEBF0((double)(v8 + 62) / *(float*)0xE7C3D8);
			pDrawText(pTextThis(), v12, v11 + 5, GetCharacterInfo[*(BYTE*)0x7BD0483 * 5 + 2], 0, 0, (LPINT)1, 0);

			v11 = sub_9CEBF0((double)(v8 + 88) / *(float*)0xE7C3D8);
			pDrawText(pTextThis(), v12, v11 + 5, GetCharacterInfo[*(BYTE*)0x7BD0483 * 5 + 3], 0, 0, (LPINT)1, 0);
			//-- titulo
			SetTextColorByHDC(pTextThis(), eGray100);

			v11 = sub_9CEBF0((double)(v8 + 8) / *(float*)0xE7C3D8);
			pDrawText(pTextThis(), v17, v11, pGetTextLine(pTextLineThis, 1701), 0, 0, (LPINT)1, 0);

			v11 = sub_9CEBF0((double)(v8 + 36) / *(float*)0xE7C3D8);
			pDrawText(pTextThis(), v17, v11, pGetTextLine(pTextLineThis, 1702), 0, 0, (LPINT)1, 0);

			v11 = sub_9CEBF0((double)(v8 + 62) / *(float*)0xE7C3D8);
			pDrawText(pTextThis(), v17, v11, pGetTextLine(pTextLineThis, 1703), 0, 0, (LPINT)1, 0);

			v11 = sub_9CEBF0((double)(v8 + 88) / *(float*)0xE7C3D8);
			pDrawText(pTextThis(), v17, v11, pGetTextLine(pTextLineThis, 1704), 0, 0, (LPINT)1, 0);
		}

		if (pWinWidth == 1360)
		{
			v12 = sub_9CEBF0((double)(v48 + 376) / *(float*)0xE7C3D4);

			//-- informacion
			SetTextColorByHDC(pTextThis(), -16730881);

			v11 = sub_9CEBF0((double)(v8 + 8) / *(float*)0xE7C3D8);
			pDrawText(pTextThis(), Return2X(TransForX(v12)), v11 + 5, GetCharacterInfo[*(BYTE*)0x7BD0483 * 5], 0, 0, (LPINT)1, 0);

			v11 = sub_9CEBF0((double)(v8 + 42) / *(float*)0xE7C3D8);
			pDrawText(pTextThis(), Return2X(TransForX(v12)), v11 + 5, GetCharacterInfo[*(BYTE*)0x7BD0483 * 5 + 1], 0, 0, (LPINT)1, 0);

			v11 = sub_9CEBF0((double)(v8 + 74) / *(float*)0xE7C3D8);
			pDrawText(pTextThis(), Return2X(TransForX(v12)), v11 + 5, GetCharacterInfo[*(BYTE*)0x7BD0483 * 5 + 2], 0, 0, (LPINT)1, 0);

			v11 = sub_9CEBF0((double)(v8 + 108) / *(float*)0xE7C3D8);
			pDrawText(pTextThis(), Return2X(TransForX(v12)), v11 + 5, GetCharacterInfo[*(BYTE*)0x7BD0483 * 5 + 3], 0, 0, (LPINT)1, 0);
			//-- titulo
			SetTextColorByHDC(pTextThis(), eGray100);

			v11 = sub_9CEBF0((double)(v8 + 8) / *(float*)0xE7C3D8);
			pDrawText(pTextThis(), Return2X(TransForX(v17 + 130)), v11, pGetTextLine(pTextLineThis, 1701), 0, 0, (LPINT)1, 0);

			v11 = sub_9CEBF0((double)(v8 + 42) / *(float*)0xE7C3D8);
			pDrawText(pTextThis(), Return2X(TransForX(v17 + 130)), v11, pGetTextLine(pTextLineThis, 1702), 0, 0, (LPINT)1, 0);

			v11 = sub_9CEBF0((double)(v8 + 74) / *(float*)0xE7C3D8);
			pDrawText(pTextThis(), Return2X(TransForX(v17 + 130)), v11, pGetTextLine(pTextLineThis, 1703), 0, 0, (LPINT)1, 0);

			v11 = sub_9CEBF0((double)(v8 + 108) / *(float*)0xE7C3D8);
			pDrawText(pTextThis(), Return2X(TransForX(v17 + 130)), v11, pGetTextLine(pTextLineThis, 1704), 0, 0, (LPINT)1, 0);
		}
	}

	if (*(DWORD *)(_this + 2640) == 4 && !*(BYTE *)(_this + 2800))
	{
		v8 = sub_401C40(_this + 288);
		v17 = sub_9CEBF0((double)v48 / *(float*)0xE7C3D4);
		if (pWinWidth < 1024)
		{
			v12 = sub_9CEBF0((double)(v48 + 60) / *(float*)0xE7C3D4);
			v11 = sub_9CEBF0((double)(v8 + 114) / *(float*)0xE7C3D8);
		}
		else
		{
			v12 = sub_9CEBF0((double)(v48 + 376) / *(float*)0xE7C3D4);
			v11 = sub_9CEBF0((double)(v8 + 142) / *(float*)0xE7C3D8);
		}

		SetTextColorByHDC(pTextThis(), -16730881);
		pDrawText(pTextThis(), Return2X(TransForX(v12)), v11 + 5, GetCharacterInfo[*(BYTE*)0x7BD0483 * 5 + 4], 0, 0, (LPINT)1, 0);

		SetTextColorByHDC(pTextThis(), eGray100);
		if (pWinWidth == 1360)
		{
			pDrawText(pTextThis(), Return2X(TransForX(v17 + 130)), v11, pGetTextLine(pTextLineThis, 1738), 0, 0, (LPINT)1, 0);
		}
		if (pWinWidth >= 800 && pWinWidth <= 1024)
		{
			pDrawText(pTextThis(), v17, v11, pGetTextLine(pTextLineThis, 1738), 0, 0, (LPINT)1, 0);
		}
	}

	pSetFont(pTextThis(), *(DWORD*)0xE8C588);

}

__declspec(naked) void JCSetBoundsInformation()
{
	static DWORD Addr_JMP = 0x004042FD;
	static DWORD Addr_Call = 0x00401C20;
	static DWORD _this;

	_asm
	{
		MOV ECX, DWORD PTR SS : [EBP - 0x80]
			MOV _this, ECX
			ADD ECX, 0x120
			CALL Addr_Call
			ADD EAX, 0x16
			MOV DWORD PTR SS : [EBP - 0x7C], EAX
	}

	sub_403FA0(_this);

	_asm
	{
		JMP[Addr_JMP]
	}
}

void CSCharacterS13::Load()
{
	

	gInterface.BindObject(CharacterSelect, 51522, 85, 150, 219, 178);
	gInterface.BindObject(CharacterSelect_Button1, 51519, 150, 35, -1, -1);
	gInterface.BindObject(CharacterSelect_Button2, 51519, 150, 35, -1, -1);
	gInterface.BindObject(CharacterSelect_Button3, 51519, 150, 35, -1, -1);
	gInterface.BindObject(CharacterSelect_Button4, 51519, 150, 35, -1, -1);
	gInterface.BindObject(CharacterSelect_Button5, 51519, 150, 35, -1, -1);

	SetDword((PVOID)(0x004D752F + 1), 51522);
	SetDword((PVOID)(0x004D7563 + 1), 51522);


	SetCompleteHook(0xE8, 0x004D6C3E, this->OpenCharacterSceneData);

	SetDouble((PVOID)(0xD25508), 1);
	SetDword((PVOID)(0x004D6C73), 0);
	SetByte((PVOID)(0x00402106), 0);
}


void CSCharacterS13::OpenCharacterSceneData()
{
	LoadBitmapA("Interface\\GFx\\CharacterSelect_Button.tga", 51519, 0x2601, 0x2901, 1, 0);
	LoadBitmapA("Interface\\GFx\\none.tga", 51522, 0x2601, 0x2901, 1, 0);
	//
	LoadBitmapA("Interface\\GFx\\CharacterSelect_I10.tga", 98000, GL_LINEAR, GL_CLAMP, 1, 0);

	if (gProtect.m_MainInfo.CreateCharacterS13 == 1)
	{
		if (pWinWidth != 1280 && pWinWidth <= 1360)
		{
			SetCompleteHook(0xE9, 0x004040FF, JCSetBoundsInformation);
			SetCompleteHook(0xE9, 0x00403326, SetLocationButtonChar);
			SetCompleteHook(0xE8, 0x00403FB6, initCharacterScene);
			SetCompleteHook(0xE9, 0x004045A1, ScaleModelLogo);
		}
	}

	((void(__cdecl*)())0x006312E0)();
}

void CharacterSelect360()
{
	for (int i = 0; i < 5; i++)
	{
		int v5 = pGetPreviewStruct(pPreviewThis(), i);

		int v8 = v5 + 776;

		if (gInterface.IsWorkZone(CharacterSelect))
		{
			*(float *)(v8 + 272) = *(float *)(v8 + 272) + 5.0;
		}
		else
		{
			*(float *)(v8 + 272) = 90;
		}
	}
}

void CharacterCharacteristics(int a1, float a2)
{
	char* Name;
	char* Status;
	int Class;
	char Level[256];
	float X = 471;
	float Y = 51;
	int This = (int)sub_482B70() + 36744;
	int Hero00 = This;
	Hero00 = *(DWORD *)(This + 4) + 368 * a1;
	//
	Name = strcpy((char *)Hero00 + 176, (const char *)(*((DWORD *)Hero00 + 42) + 56));
	Status = (char *)Hero00 + 240;
	Class = sub_587620(*(BYTE *)(*(DWORD *)(Hero00 + 168) + 19));
	gInterface.DrawFormat(eGold, X + 35, Y + 20 + a2, 190, 2, (const char *)Name);
	gInterface.DrawFormat(eWhite180, X + 11, Y + 7 + a2, 190, 0, (const char *)Class);
	gInterface.DrawFormat(eWhite180, X - 50, Y + 7 + a2, 190, 4, (const char *)Status);
	wsprintf(Level, "Level: %d", *(WORD *)(*(DWORD *)(Hero00 + 168) + 130));
	pSetTextColor(pTextThis(), 255, 189, 25, 0xFF);
	pDrawText(pTextThis(), X - 50, Y + 20 + a2, Level, 190, 0, (LPINT)4, 0);
}

void CharacterTeleport(int a1, float a2, float a3, float a4)
{
	if (*(DWORD*)(MAIN_SCREEN_STATE) == ObjState::SwitchCharacter)
	{
		int v5 = pGetPreviewStruct(pPreviewThis(), a1);
		int v8 = v5 + 776;
		if (v5)
		{
			*(float *)(v8 + 156) = 0.30000001;
			*(float *)(v8 + 160) = 0.30000001;
			*(float *)(v8 + 164) = 0.30000001;
			*(float *)(v8 + 252) = a2;
			*(float *)(v8 + 256) = a3;
			*(float *)(v8 + 272) = a4;
		}
	}
}

void CSCharacterS13::SelectChar()
{
	float X = 471;
	float Y = 51;
	//
	if (*(BYTE *)((int)sub_482B70() + 33948))
	{
		//loadcharcreate();
	}
	else
	{
		//Create Select
		//-- 0
		if (!*(BYTE *)(pGetPreviewStruct(pPreviewThis(), 0) + 780))
		{
			if (gInterface.IsWorkZone(CharacterSelect_Button1))
			{
				if (gInterface.Data[CharacterSelect_Button1].OnClick)
				{
					gInterface.DrawButton(CharacterSelect_Button1, 471, 51, 0, 70);
					sub_483B20((int)sub_482B70(), (int)sub_482B70() + 33936);
				}
				else
				{
					gInterface.DrawButton(CharacterSelect_Button1, 471, 51, 0, 35);
				}
			}
			else
			{
				gInterface.DrawButton(CharacterSelect_Button1, 471, 51, 0, 0);
			}
			gInterface.DrawFormat(eWhite180, X - 29, Y + 13, 210, 3, "Empty Character Slot");
		}
		//-- 1
		if (!*(BYTE *)(pGetPreviewStruct(pPreviewThis(), 1) + 780))
		{
			if (gInterface.IsWorkZone(CharacterSelect_Button2))
			{
				if (gInterface.Data[CharacterSelect_Button2].OnClick)
				{
					gInterface.DrawButton(CharacterSelect_Button2, 471, 88, 0, 70);
					sub_483B20((int)sub_482B70(), (int)sub_482B70() + 33936);
				}
				else
				{
					gInterface.DrawButton(CharacterSelect_Button2, 471, 88, 0, 35);
				}
			}
			else
			{
				gInterface.DrawButton(CharacterSelect_Button2, 471, 88, 0, 0);
			}
			gInterface.DrawFormat(eWhite180, X - 29, 88 + 13, 210, 3, "Empty Character Slot");
		}
		//-- 2
		if (!*(BYTE *)(pGetPreviewStruct(pPreviewThis(), 2) + 780))
		{
			if (gInterface.IsWorkZone(CharacterSelect_Button3))
			{
				if (gInterface.Data[CharacterSelect_Button3].OnClick)
				{
					gInterface.DrawButton(CharacterSelect_Button3, 471, 125, 0, 70);
					sub_483B20((int)sub_482B70(), (int)sub_482B70() + 33936);
				}
				else
				{
					gInterface.DrawButton(CharacterSelect_Button3, 471, 125, 0, 35);
				}
			}
			else
			{
				gInterface.DrawButton(CharacterSelect_Button3, 471, 125, 0, 0);
			}
			gInterface.DrawFormat(eWhite180, X - 29, 125 + 13, 210, 3, "Empty Character Slot");
		}
		//-- 3
		if (!*(BYTE *)(pGetPreviewStruct(pPreviewThis(), 3) + 780))
		{
			if (gInterface.IsWorkZone(CharacterSelect_Button4))
			{
				if (gInterface.Data[CharacterSelect_Button4].OnClick)
				{
					gInterface.DrawButton(CharacterSelect_Button4, 471, 162, 0, 70);
					sub_483B20((int)sub_482B70(), (int)sub_482B70() + 33936);
				}
				else
				{
					gInterface.DrawButton(CharacterSelect_Button4, 471, 162, 0, 35);
				}
			}
			else
			{
				gInterface.DrawButton(CharacterSelect_Button4, 471, 162, 0, 0);
			}
			gInterface.DrawFormat(eWhite180, X - 29, 162 + 13, 210, 3, "Empty Character Slot");
		}
		//-- 4
		if (!*(BYTE *)(pGetPreviewStruct(pPreviewThis(), 4) + 780))
		{
			if (gInterface.IsWorkZone(CharacterSelect_Button5))
			{
				if (gInterface.Data[CharacterSelect_Button5].OnClick)
				{
					gInterface.DrawButton(CharacterSelect_Button5, 471, 199, 0, 70);
					sub_483B20((int)sub_482B70(), (int)sub_482B70() + 33936);
				}
				else
				{
					gInterface.DrawButton(CharacterSelect_Button5, 471, 199, 0, 35);
				}
			}
			else
			{
				gInterface.DrawButton(CharacterSelect_Button5, 471, 199, 0, 0);
			}
			gInterface.DrawFormat(eWhite180, X - 29, 199 + 13, 210, 3, "Empty Character Slot");
		}

		//Character Select
		CharacterSelect360();
		//-- 0
		if (*(BYTE *)(pGetPreviewStruct(pPreviewThis(), 0) + 780))
		{
			if (gInterface.IsWorkZone(CharacterSelect_Button1))
			{

				if (gInterface.Data[CharacterSelect_Button1].OnClick)
				{
					PlayBuffer(25, 0, 0);
					SelectedHero = 0;
					for (int m = 0; m < 5; m++)
					{
						if (m == SelectedHero)
						{
							CharacterTeleport(SelectedHero, gSelectCharRamdon.RenderSelect.PJ[0].Coordenada1.CoordX, gSelectCharRamdon.RenderSelect.PJ[0].Coordenada1.CoordY, gSelectCharRamdon.RenderSelect.PJ[0].Coordenada1.Rotate);
						}
						else
						{
							CharacterTeleport(m, gSelectCharRamdon.RenderSelect.PJ[1].Coordenada1.CoordX, gSelectCharRamdon.RenderSelect.PJ[1].Coordenada1.CoordY, gSelectCharRamdon.RenderSelect.PJ[1].Coordenada1.Rotate);
						}
					}
					gInterface.DrawButton(CharacterSelect_Button1, 471, Y, 0, 70);
				}
				else
				{
					if (SelectedHero == 0)
					{
						gInterface.DrawButton(CharacterSelect_Button1, 471, Y, 0, 70);
					}
					else
					{
						gInterface.DrawButton(CharacterSelect_Button1, 471, Y, 0, 35);
					}
				}

				SelectedCharacter = SelectedHero;
			}
			else
			{
				if (SelectedHero == 0)
				{
					gInterface.DrawButton(CharacterSelect_Button1, 471, Y, 0, 70);
				}
				else
				{
					gInterface.DrawButton(CharacterSelect_Button1, 471, Y, 0, 0);
				}
			}
			CharacterCharacteristics(0, 0);
		}
		//-- 1
		if (*(BYTE *)(pGetPreviewStruct(pPreviewThis(), 1) + 780))
		{
			if (gInterface.IsWorkZone(CharacterSelect_Button2))
			{

				if (gInterface.Data[CharacterSelect_Button2].OnClick)
				{
					PlayBuffer(25, 0, 0);
					SelectedHero = 1;
					for (int m = 0; m < 5; m++)
					{
						if (m == SelectedHero)
						{
							CharacterTeleport(SelectedHero, gSelectCharRamdon.RenderSelect.PJ[0].Coordenada1.CoordX, gSelectCharRamdon.RenderSelect.PJ[0].Coordenada1.CoordY, gSelectCharRamdon.RenderSelect.PJ[0].Coordenada1.Rotate);
						}
						else
						{
							CharacterTeleport(m, gSelectCharRamdon.RenderSelect.PJ[1].Coordenada1.CoordX, gSelectCharRamdon.RenderSelect.PJ[1].Coordenada1.CoordY, gSelectCharRamdon.RenderSelect.PJ[1].Coordenada1.Rotate);
						}
					}
					gInterface.DrawButton(CharacterSelect_Button2, 471, Y + 37, 0, 70);
				}
				else
				{
					if (SelectedHero == 1)
					{
						gInterface.DrawButton(CharacterSelect_Button2, 471, Y + 37, 0, 70);
					}
					else
					{
						gInterface.DrawButton(CharacterSelect_Button2, 471, Y + 37, 0, 35);
					}
				}
				SelectedCharacter = SelectedHero;
			}
			else
			{
				if (SelectedHero == 1)
				{
					gInterface.DrawButton(CharacterSelect_Button2, 471, Y + 37, 0, 70);
				}
				else
				{
					gInterface.DrawButton(CharacterSelect_Button2, 471, Y + 37, 0, 0);
				}
			}
			CharacterCharacteristics(1, 37);
		}
		//-- 2
		if (*(BYTE *)(pGetPreviewStruct(pPreviewThis(), 2) + 780))
		{
			if (gInterface.IsWorkZone(CharacterSelect_Button3))
			{

				if (gInterface.Data[CharacterSelect_Button3].OnClick)
				{
					PlayBuffer(25, 0, 0);
					SelectedHero = 2;
					for (int m = 0; m < 5; m++)
					{
						if (m == SelectedHero)
						{
							CharacterTeleport(SelectedHero, gSelectCharRamdon.RenderSelect.PJ[0].Coordenada1.CoordX, gSelectCharRamdon.RenderSelect.PJ[0].Coordenada1.CoordY, gSelectCharRamdon.RenderSelect.PJ[0].Coordenada1.Rotate);
						}
						else
						{
							CharacterTeleport(m, gSelectCharRamdon.RenderSelect.PJ[1].Coordenada1.CoordX, gSelectCharRamdon.RenderSelect.PJ[1].Coordenada1.CoordY, gSelectCharRamdon.RenderSelect.PJ[1].Coordenada1.Rotate);
						}
					}
					gInterface.DrawButton(CharacterSelect_Button3, 471, Y + 74, 0, 70);
				}
				else
				{
					if (SelectedHero == 2)
					{
						gInterface.DrawButton(CharacterSelect_Button3, 471, Y + 74, 0, 70);
					}
					else
					{
						gInterface.DrawButton(CharacterSelect_Button3, 471, Y + 74, 0, 35);
					}
				}

				SelectedCharacter = SelectedHero;
			}
			else
			{
				if (SelectedHero == 2)
				{
					gInterface.DrawButton(CharacterSelect_Button3, 471, Y + 74, 0, 70);
				}
				else
				{
					gInterface.DrawButton(CharacterSelect_Button3, 471, Y + 74, 0, 0);
				}
			}
			CharacterCharacteristics(2, 74);
		}
		//-- 3
		if (*(BYTE *)(pGetPreviewStruct(pPreviewThis(), 3) + 780))
		{
			if (gInterface.IsWorkZone(CharacterSelect_Button4))
			{

				if (gInterface.Data[CharacterSelect_Button4].OnClick)
				{
					PlayBuffer(25, 0, 0);
					SelectedHero = 3;
					for (int m = 0; m < 5; m++)
					{
						if (m == SelectedHero)
						{
							CharacterTeleport(SelectedHero, gSelectCharRamdon.RenderSelect.PJ[0].Coordenada1.CoordX, gSelectCharRamdon.RenderSelect.PJ[0].Coordenada1.CoordY, gSelectCharRamdon.RenderSelect.PJ[0].Coordenada1.Rotate);
						}
						else
						{
							CharacterTeleport(m, gSelectCharRamdon.RenderSelect.PJ[1].Coordenada1.CoordX, gSelectCharRamdon.RenderSelect.PJ[1].Coordenada1.CoordY, gSelectCharRamdon.RenderSelect.PJ[1].Coordenada1.Rotate);
						}
					}
					gInterface.DrawButton(CharacterSelect_Button4, 471, Y + 111, 0, 70);
				}
				else
				{
					if (SelectedHero == 3)
					{
						gInterface.DrawButton(CharacterSelect_Button4, 471, Y + 111, 0, 70);
					}
					else
					{
						gInterface.DrawButton(CharacterSelect_Button4, 471, Y + 111, 0, 35);
					}
				}
				SelectedCharacter = SelectedHero;
			}
			else
			{
				if (SelectedHero == 3)
				{
					gInterface.DrawButton(CharacterSelect_Button4, 471, Y + 111, 0, 70);
				}
				else
				{
					gInterface.DrawButton(CharacterSelect_Button4, 471, Y + 111, 0, 0);
				}
			}

			CharacterCharacteristics(3, 111);
		}
		//-- 4
		if (*(BYTE *)(pGetPreviewStruct(pPreviewThis(), 4) + 780))
		{
			if (gInterface.IsWorkZone(CharacterSelect_Button5))
			{

				if (gInterface.Data[CharacterSelect_Button5].OnClick)
				{
					PlayBuffer(25, 0, 0);
					SelectedHero = 4;
					for (int m = 0; m < 5; m++)
					{
						if (m == SelectedHero)
						{
							CharacterTeleport(SelectedHero, gSelectCharRamdon.RenderSelect.PJ[0].Coordenada1.CoordX, gSelectCharRamdon.RenderSelect.PJ[0].Coordenada1.CoordY, gSelectCharRamdon.RenderSelect.PJ[0].Coordenada1.Rotate);
						}
						else
						{
							CharacterTeleport(m, gSelectCharRamdon.RenderSelect.PJ[1].Coordenada1.CoordX, gSelectCharRamdon.RenderSelect.PJ[1].Coordenada1.CoordY, gSelectCharRamdon.RenderSelect.PJ[1].Coordenada1.Rotate);
						}
					}
					gInterface.DrawButton(CharacterSelect_Button5, 471, Y + 148, 0, 70);
				}
				else
				{
					if (SelectedHero == 4)
					{
						gInterface.DrawButton(CharacterSelect_Button5, 471, Y + 148, 0, 70);
					}
					else
					{
						gInterface.DrawButton(CharacterSelect_Button5, 471, Y + 148, 0, 35);
					}
				}

				SelectedCharacter = SelectedHero;
			}
			else
			{
				if (SelectedHero == 4)
				{
					gInterface.DrawButton(CharacterSelect_Button5, 471, Y + 148, 0, 70);
				}
				else
				{
					gInterface.DrawButton(CharacterSelect_Button5, 471, Y + 148, 0, 0);
				}
			}

			CharacterCharacteristics(4, 148);
		}
	}
}

void CSCharacterS13::SelectCharButton(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	// ----
	if (*(DWORD*)(MAIN_SCREEN_STATE) != ObjState::SwitchCharacter)
	{
		return;
	}

	if (gInterface.IsWorkZone(CharacterSelect_Button1))
	{
		DWORD Delay = (CurrentTick - gInterface.Data[CharacterSelect_Button1].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			gInterface.Data[CharacterSelect_Button1].OnClick = true;
			return;
		}
		// ----
		gInterface.Data[CharacterSelect_Button1].OnClick = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		gInterface.Data[CharacterSelect_Button1].EventTick = GetTickCount();
		// ----
	}
	else if (gInterface.IsWorkZone(CharacterSelect_Button2))
	{
		DWORD Delay = (CurrentTick - gInterface.Data[CharacterSelect_Button2].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			gInterface.Data[CharacterSelect_Button2].OnClick = true;
			return;
		}
		// ----
		gInterface.Data[CharacterSelect_Button2].OnClick = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		gInterface.Data[CharacterSelect_Button2].EventTick = GetTickCount();
		// ----
	}
	else if (gInterface.IsWorkZone(CharacterSelect_Button3))
	{
		DWORD Delay = (CurrentTick - gInterface.Data[CharacterSelect_Button3].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			gInterface.Data[CharacterSelect_Button3].OnClick = true;
			return;
		}
		// ----
		gInterface.Data[CharacterSelect_Button3].OnClick = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		gInterface.Data[CharacterSelect_Button3].EventTick = GetTickCount();
		// ----
	}
	else if (gInterface.IsWorkZone(CharacterSelect_Button4))
	{
		DWORD Delay = (CurrentTick - gInterface.Data[CharacterSelect_Button4].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			gInterface.Data[CharacterSelect_Button4].OnClick = true;
			return;
		}
		// ----
		gInterface.Data[CharacterSelect_Button4].OnClick = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		gInterface.Data[CharacterSelect_Button4].EventTick = GetTickCount();
		// ----
	}
	else if (gInterface.IsWorkZone(CharacterSelect_Button5))
	{
		DWORD Delay = (CurrentTick - gInterface.Data[CharacterSelect_Button5].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			gInterface.Data[CharacterSelect_Button5].OnClick = true;
			return;
		}
		// ----
		gInterface.Data[CharacterSelect_Button5].OnClick = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		gInterface.Data[CharacterSelect_Button5].EventTick = GetTickCount();
		// ----
	}
}