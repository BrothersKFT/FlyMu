#include "StdAfx.h"
#if OFF
#include "SceneCreate.h"
#include "Import.h"
#include "Offset.h"
#include "Defines.h"
#include "Util.h"
#include "Object.h"
#include "Pet.h"
#include "InfoLog.h"

JCSceneCreate JCGetScene;

JCSceneCreate::JCSceneCreate()
{
}


JCSceneCreate::~JCSceneCreate()
{
}

void JCSceneCreate::OpenCharacterSceneData()
{
	LoadBitmapA("Interface\\GFx\\CharacterSelect_Button.tga", 51519, 0x2601, 0x2901, 1, 0);
	LoadBitmapA("Interface\\GFx\\none.tga", 51522, 0x2601, 0x2901, 1, 0);
	//
	LoadBitmapA("Interface\\GFx\\CharacterSelect_I10.tga", 98000, GL_LINEAR, GL_CLAMP, 1, 0);
	((void(__cdecl*)())0x006312E0)();
}

int MAINCHAR; // [sp+8h] [bp-C0h]@1
int JCSelectCharCreateEvt; // [sp+8h] [bp-C0h]@1

bool JCCharEventButton(int x, int y, int w, int h)
{
	return pCheckMouseOver(x, y, w, h) && *(BYTE*)0x8793386;
}

//----- (004048E0) --------------------------------------------------------
int sub_4048E0(int This, char a2)
{
	int result; // eax@1

	result = This;
	*(BYTE *)(This + 168) = a2;
	return result;
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
	int v19[8]; // [sp+94h] [bp-34h]@4
	int v20[7]; // [sp+98h] [bp-30h]@4
	v10 = _this;
	//-- Logo modelo

	(*(void(__thiscall **)(int, signed int, int))(*(DWORD *)(_this + 60) + 8))(_this + 60, x, y - 50);

	if (pWinWidth > 800)
	{
		v12 = x + 466;
		v11 = y - 35;
		//-- estadisticas del personaje
		sub_416210(v10 + 288, 108, 100, 31003);
		sub_416640(v10 + 288, x + 333, x + 334, v11 + 3, 3);

		v19[0] = 0xFFE2E2E2;
		v19[1] = 0xFFE2E2E2;
		v19[2] = -1;
		v19[3] = 0xFF777777;
		v19[4] = 0xFFE2E2E2;
		v19[5] = 0xFFE2E2E2;
		v19[6] = -1;
		v19[7] = 0xFF777777;

		v20[0] = 20;
		v20[1] = 21;
		v20[2] = 22;
		v20[3] = 23;
		v20[4] = 24;
		v20[5] = 1687;
		v20[6] = 3150;

		for (i = 0; i < 7; ++i)
		{
			JCSpiriteSetInfo(v10 + 224 * i + 624, 150, 26, 51522, 4, 2, 1, 0, 3, 3, 3, 0);
			JCSpiriteSetPosition(v10 + 224 * i + 624, v10, v12, v11 + 29 * i, 3);
			JCSetText(v10 + 224 * i + 624, pGetTextLine(pTextLineThis, v20[i]), &v19);
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

	RenderBitmap(98000, JCRangeX + 257.0, JCRangeY + 18.0, 73.21875, 174.39375, 0.0, 0.0, 0.1198597625, 0.3259598017, 1, 1, 0.0); //-- fondo de guerra

	RenderBitmap(98000, JCRangeX + 235.0, JCRangeY, 195.625009974375, 223.12500372375, 0.0, 0.5699999928, 0.3048597574, 0.3519598544, 1, 1, 0.0); //-- marco de botones

	RenderBitmap(98000, JCRangeX, JCRangeY + 142.0, 371.8749858825, 211.249992133125, 0.3125000298, 0.5682999492, 0.5599597692, 0.3250873685, 1, 1, 0.0); //-- estilo del personaje

	pSetFont(pTextThis(), *(DWORD*)0xE8C58C);

	for (int i = 0; i < 10; i++)
	{
		if (i < 8)
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

	EnableAlphaTest(JCByte);
	glColor3f(1.0, 1.0, 1.0);
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
		if (pWinWidth < 1024)
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
		else
		{
			v12 = sub_9CEBF0((double)(v48 + 76) / *(float*)0xE7C3D4);

			//-- informacion
			SetTextColorByHDC(pTextThis(), -16730881);

			v11 = sub_9CEBF0((double)(v8 + 8) / *(float*)0xE7C3D8);
			pDrawText(pTextThis(), v12, v11 + 5, GetCharacterInfo[*(BYTE*)0x7BD0483 * 5], 0, 0, (LPINT)1, 0);

			v11 = sub_9CEBF0((double)(v8 + 42) / *(float*)0xE7C3D8);
			pDrawText(pTextThis(), v12, v11 + 5, GetCharacterInfo[*(BYTE*)0x7BD0483 * 5 + 1], 0, 0, (LPINT)1, 0);

			v11 = sub_9CEBF0((double)(v8 + 74) / *(float*)0xE7C3D8);
			pDrawText(pTextThis(), v12, v11 + 5, GetCharacterInfo[*(BYTE*)0x7BD0483 * 5 + 2], 0, 0, (LPINT)1, 0);

			v11 = sub_9CEBF0((double)(v8 + 108) / *(float*)0xE7C3D8);
			pDrawText(pTextThis(), v12, v11 + 5, GetCharacterInfo[*(BYTE*)0x7BD0483 * 5 + 3], 0, 0, (LPINT)1, 0);
			//-- titulo
			SetTextColorByHDC(pTextThis(), eGray100);

			v11 = sub_9CEBF0((double)(v8 + 8) / *(float*)0xE7C3D8);
			pDrawText(pTextThis(), v17, v11, pGetTextLine(pTextLineThis, 1701), 0, 0, (LPINT)1, 0);

			v11 = sub_9CEBF0((double)(v8 + 42) / *(float*)0xE7C3D8);
			pDrawText(pTextThis(), v17, v11, pGetTextLine(pTextLineThis, 1702), 0, 0, (LPINT)1, 0);

			v11 = sub_9CEBF0((double)(v8 + 74) / *(float*)0xE7C3D8);
			pDrawText(pTextThis(), v17, v11, pGetTextLine(pTextLineThis, 1703), 0, 0, (LPINT)1, 0);

			v11 = sub_9CEBF0((double)(v8 + 108) / *(float*)0xE7C3D8);
			pDrawText(pTextThis(), v17, v11, pGetTextLine(pTextLineThis, 1704), 0, 0, (LPINT)1, 0);
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
			v12 = sub_9CEBF0((double)(v48 + 76) / *(float*)0xE7C3D4);
			v11 = sub_9CEBF0((double)(v8 + 142) / *(float*)0xE7C3D8);
		}

		SetTextColorByHDC(pTextThis(), -16730881);
		pDrawText(pTextThis(), v12, v11 + 5, GetCharacterInfo[*(BYTE*)0x7BD0483 * 5 + 4], 0, 0, (LPINT)1, 0);

		SetTextColorByHDC(pTextThis(), eGray100);
		pDrawText(pTextThis(), v17, v11, pGetTextLine(pTextLineThis, 1738), 0, 0, (LPINT)1, 0);
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

//----- (00636480) --------------------------------------------------------
void CreateLogoChar(GLint a1, int a2, GLsizei width, GLsizei height)
{
	float JCWinWidth; // ST04_4@3
	unsigned int x; // [sp+20h] [bp+8h]@1

	JCWinWidth = (double)(unsigned int)pWinWidth / 640.0;

	x = (a1 * pWinWidthReal) / JCWinWidth;
	width = 410.0 / JCWinWidth;

	if (*(BYTE*)0x7BD0483)
	{
		switch (*(BYTE*)0x7BD0483)
		{
		case 7:
			*((float *)&*(LPVOID*)0x7BD0778 + 66) = 8.0;
			*((float *)&*(LPVOID*)0x7BD0778 + 67) = 0.0;
			*((float *)&*(LPVOID*)0x7BD0778 + 68) = -2.0;
			*((float *)&*(LPVOID*)0x7BD0778 + 24) = 8.8000002;
			*(float*)0x7BD0874 = *(float*)0x7BD0874 + 4.800000190734863;
			*(float*)0x7BD087C = *(float*)0x7BD087C - 2.0;
			break;
		}
	}
	else
	{
		*((float *)&*(LPVOID*)0x7BD0778 + 66) = 0.0;
		*((float *)&*(LPVOID*)0x7BD0778 + 67) = 0.0;
		*((float *)&*(LPVOID*)0x7BD0778 + 68) = -40.0;
		*((float *)&*(LPVOID*)0x7BD0778 + 24) = 5.9000001;
	}

	BeginOpengl(x, a2, width, height);
}

//----- (0095A270) --------------------------------------------------------
int __cdecl JCSetScaleLogo(int a1, int a2, int a3)
{
	int v10; // eax@1
	float v11; // [sp+10h] [bp-18h]@1
	float v12; // [sp+14h] [bp-14h]@1
	float v13; // [sp+18h] [bp-10h]@1

	v10 = a1;
	v11 = 10.0;
	v12 = -600.0;
	v13 = 46.0;

	*(float *)a3 = v11 * *(float *)a2 + v12 * *(float *)(a2 + 16) + v13 * *(float *)(a2 + 32);

	*(float *)(a3 + 4) = v11 * *(float *)(a2 + 4) + v12 * *(float *)(a2 + 20) + v13 * *(float *)(a2 + 36);

	*(float *)(a3 + 8) = v11 * *(float *)(a2 + 8) + v12 * *(float *)(a2 + 24) + v13 * *(float *)(a2 + 40);

	return v10;
}

void JCSelectPJC(int JCThis)
{
	lpButtonChar v21; // [sp+80Ch] [bp-82Ch]@46
	lpButtonChar v22; // [sp+80Ch] [bp-82Ch]@46

	double JCRangeX = 223.0;
	double JCRangeY = 70.0;
	int i; // [sp+1028h] [bp-10h]@3
	int j; // [sp+1024h] [bp-14h]@6

	JCRangeX = pWinWidth / pWinHeightReal / 2 - 185.93749294125;

	if (!*(BYTE *)(JCThis + 2800))
	{
		for (i = 0; i < 7; ++i)
			{
				v21 = &*(ButtonChar*)(JCThis + 224 * i + 624);

				if (JCButtonPush(JCThis + 224 * i + 624))
				{
					for (j = 0; j < 7; ++j)
					{
						v22 = &*(ButtonChar*)(JCThis + 224 * j + 624);
						v22->JoinPush = 0;
					}
					v21->JoinPush = 1;
					if (*(DWORD *)(JCThis + 2640) != i)
					{
						*(DWORD *)(JCThis + 2640) = i;
						JCButtonShow(JCThis);
					}
					break;
				}
			}
	}
}

__declspec(naked) void JCSelectChar()
{
	static DWORD Addr_JMP = 0x004039B8;
	static DWORD JCThis;

	_asm
	{
		MOV EAX, DWORD PTR SS : [EBP - 0x1038]
			MOV JCThis, EAX
	}

	JCSelectPJC(JCThis);

	_asm
	{
		JMP[Addr_JMP]
	}
}

//----- (0063D130)
DWORD JCCHARACTERLIST(LPBYTE aRecv)
{
	int v4; // ST1C_4@11
	DWORD result; // eax@12
	int v9; // [sp+14h] [bp-20h]@5
	int v10; // [sp+18h] [bp-1Ch]@5
	float v11; // [sp+1Ch] [bp-18h]@5
	float v12; // [sp+20h] [bp-14h]@0
	float v13; // [sp+24h] [bp-10h]@0
	signed int i; // [sp+28h] [bp-Ch]@3
	signed int datasize; // [sp+30h] [bp-4h]@3

	PMSG_JCCHARACTER_LIST_RECV JCCount;
	datasize = 0;
	memcpy(&JCCount, &aRecv[datasize], sizeof(JCCount));

	sub_63CB40();
	sub_4D5130(JCCount.ClassCode);

	if (pPlayerState == 4)
		*(DWORD*)0xE61E18 = 74;

	datasize = 8;

	for (i = 0; i < JCCount.count; ++i)
	{
		PMSG_CHARACTER_LIST JCList;
		memcpy(&JCList, &aRecv[datasize], sizeof(JCList));
		//--
		v9 = (int)&JCList;
		v10 = (unsigned __int8)sub_587380(*(BYTE *)(v9 + 15));
		v11 = 0.0;

		switch (*(BYTE *)v9)
		{
		case 0:
			v12 = 8008.0;
			v13 = 18885.0;
			v11 = 115.0;
			break;
		case 1:
			v12 = 7986.0;
			v13 = 19145.0;
			v11 = 90.0;
			break;
		case 2:
			v12 = 8046.0;
			v13 = 19400.0;
			v11 = 75.0;
			break;
		case 3:
			v12 = 8133.0;
			v13 = 19645.0;
			v11 = 60.0;
			break;
		case 4:
			v12 = 8282.0;
			v13 = 19845.0;
			v11 = 35.0;
			break;
		case 5:
			v12 = 8431.0;
			v13 = 19845.0;
			v11 = 55.0;
			break;
		case 6:
			v12 = 7859.0;
			v13 = 18885.0;
			v11 = 15.0;
			break;
		default:
			break;
		}

		v4 = JCSetModelCoord(*(BYTE *)v9, v10, 0, v12, v13, v11);//-- Agrega Personaje con Coordenada

		*(WORD *)(v4 + 130) = *(WORD *)(v9 + 12);

		*(BYTE *)(v4 + 21) = *(BYTE *)(v9 + 14);

		sub_9CF1C0((char *)(v4 + 56), (const void *)(v9 + 1), 0xAu);

		*(BYTE *)(v4 + 66) = 0;

		gCustomPet.PreviewCharSet(*(BYTE *)v9, (BYTE *)(v9 + 16), 0, 0);//-- Mostrar Equipamiento

		*(BYTE *)(v4 + 24) = *(BYTE *)(v9 + 33);

		datasize += 34;
	}

	*(DWORD*)0x87935A4 = 51;

	pWarehouseExSet(pWarehouseExThis(pWindowThis()), *(BYTE *)(((int)&JCCount) + 7));

	result = GetTickCount();
	*(DWORD*)0xE8CB30 = result;
	return result;
}

signed int JCCREATECHARACTERLIST(int JCCHARACTER)
{
	float v4; // ST14_4@8
	signed int result; // eax@10
	float v10; // [sp+1Ch] [bp-14h]@2
	DWORD v11; // [sp+20h] [bp-10h]@8
	float v12; // [sp+24h] [bp-Ch]@0
	float v13; // [sp+28h] [bp-8h]@0
	int v14; // [sp+28h] [bp-8h]@0

	v14 = JCCHARACTER;

	if (*(BYTE *)(JCCHARACTER + 4) == 1)
	{
		v10 = 0.0;
		switch (*(BYTE *)(JCCHARACTER + 15))
		{
		case 0:
			v12 = 8008.0;
			v13 = 18885.0;
			v11 = 115.0;
			break;
		case 1:
			v12 = 7986.0;
			v13 = 19145.0;
			v11 = 90.0;
			break;
		case 2:
			v12 = 8046.0;
			v13 = 19400.0;
			v11 = 75.0;
			break;
		case 3:
			v12 = 8133.0;
			v13 = 19645.0;
			v11 = 60.0;
			break;
		case 4:
			v12 = 8282.0;
			v13 = 19845.0;
			v11 = 35.0;
			break;
		case 5:
			v12 = 8431.0;
			v13 = 19845.0;
			v11 = 55.0;
			break;
		case 6:
			v12 = 7859.0;
			v13 = 18885.0;
			v11 = 15.0;
			break;
		default:
			break;
		}

		sub_57D760(*(BYTE *)(JCCHARACTER + 15));
		JCSetModelCoord(*(BYTE *)(JCCHARACTER + 15), (unsigned __int8)*(BYTE*)0x7BD0483, *(BYTE*)0x7BD0484, v12, v13, v10);

		v11 = pGetPreviewStruct(pPreviewThis(), *(BYTE *)(JCCHARACTER + 15));

		if (v11)
		{
			*(WORD *)(v11 + 130) = *(WORD *)(JCCHARACTER + 16);
			*(BYTE *)(v11 + 19) = sub_587380(*(BYTE *)(JCCHARACTER + 18));
			sub_9CF1C0((char *)(v11 + 56), (const void *)(JCCHARACTER + 5), 0xAu);
			*(BYTE *)(v11 + 66) = 0;
		}

		*(DWORD*)0x87935A4 = 53;

		sub_668520((char *)sub_482B70());
		sub_4057B0((char *)sub_482B70() + 32632);
		result = sub_402AD0((char *)sub_482B70() + 36744);
	}
	else
	{
		result = *(BYTE *)(v14 + 4);
		if (*(BYTE *)(v14 + 4))
		{
			if (*(BYTE *)(v14 + 4) == 2)
			{
				result = sub_484A10(sub_482B70(), 55, 0);
			}
		}
		else
		{
			result = sub_484A10(sub_482B70(), 54, 0);
		}
	}
	return result;
}

void JCSceneCreate::Load()
{
	//-- ampliar más personajes
	SetByte(0x004057E5, 0x7);
	SetByte(0x00405881, 0x7);
	SetByte(0x004D6F66, 0x7);
	SetByte(0x004D7075, 0x6);
	SetByte(0x004D70B0, 0x6);
	SetByte(0x004D71E0, 0x7);
	SetByte(0x004D72C7, 0x7);
	SetCompleteHook(0xE9, 0x0063D3D0, &JCCREATECHARACTERLIST);
	SetCompleteHook(0xE9, 0x0063D130, &JCCHARACTERLIST); //-- Coord1 PJ

	//-- cargar logo de nuevo personaje
	SetByte(0x00631489, 0x8);
	//--
	SetCompleteHook(0xE9, 0x004038D9, &JCSelectChar);
	//--
	SetCompleteHook(0xE8, 0x004D66FF, &JCSetScaleLogo);
	SetCompleteHook(0xE8, 0x0040464E, &CreateLogoChar);
	SetCompleteHook(0xE9, 0x004040FF, &JCSetBoundsInformation);
	SetCompleteHook(0xE9, 0x00403326, &SetLocationButtonChar);
	SetCompleteHook(0xE8, 0x00403FB6, &initCharacterScene);
	//--
	SetCompleteHook(0xE8, 0x004D6C3E, this->OpenCharacterSceneData);
}
#endif