#include "StdAfx.h"
#include "Radar.h"
#include "Import.h"
#include "Util.h"
#include "Defines.h"
#include "User.h"
#include "Common.h"
#include "Protect.h"
#include "Interface.h"


JCMinimap JCGetMinimap;

JCMinimap::JCMinimap()
{
}


JCMinimap::~JCMinimap()
{
}


bool JCFileMapCheck(int map) // OK
{
	if (map - 1 == 30) { return 1; }

	char Path[64];

	wsprintf(Path, "Data\\Custom\\Maps\\World%d.ozt", map);

	FILE* file;

	if (fopen_s(&file, Path, "r") != 0)
	{
		return 0;
	}
	else
	{
		fclose(file);
		return 1;
	}
}

void MiniMapLoad() // OK
{
	if (pMapNumber < 100 && pMapNumber != 30)
	{
		char buff1[32];

		wsprintf(buff1, "Custom\\Maps\\World%d.tga", (pMapNumber + 1));
		MiniMap = 0;

		if (JCFileMapCheck((pMapNumber + 1)) != 0)
		{
			MiniMap = 1;
			LoadBitmapA(buff1, 550000, 0x2601, 0x2900, 1, 0);
		}
	}
}

void LoadObjectMapCore() // OK
{
	((void(*)())0x00629180)();

	MiniMapLoad();
}


DWORD CRadara1;
DWORD CRadara2;
DWORD CRadara3;

__declspec(naked) void JCMinimap::JCCreateRadar()
{
	static DWORD CReturn01 = 0x005FC88D;
	static DWORD CReturn02 = 0x005FC881;

	_asm
	{
		MOV EDX, DWORD PTR SS : [EBP + 0x8]
			MOV CRadara1, EDX
			// ----
			MOV EAX, DWORD PTR SS : [EBP + 0xC]
			MOV CRadara2, EAX
			// ----
			MOV EAX, DWORD PTR SS : [EBP + 0x10]
			MOV CRadara3, EAX
	}
	// ----
	if (CRadara3 == ITEM2(6, 65) || CRadara3 == ITEM2(6, 66) || CRadara3 == ITEM2(6, 67))
	{
		// ----
		glColor3fv((GLfloat*)(CRadara1 + 72));
		// ----
		RenderMesh(CRadara1,
			1,
			2,
			*(float *)(CRadara2 + 152),
			*(DWORD *)(CRadara2 + 68),
			*(float *)(CRadara2 + 100),
			*(float *)(CRadara2 + 104),
			*(float *)(CRadara2 + 108),
			-1);

		float FormulaX = (float)(pGetUserCoorX - 22.0f) / 512;
		float FormulaY = -(float)(pGetUserCoorY - 234.5f) / 512;

		RenderMesh(CRadara1,
			0,
			2,
			*(float *)(CRadara2 + 152),
			0,
			*(float *)(CRadara2 + 100),
			FormulaX,
			FormulaY,
			550000);
		//550000);
		// ----
		_asm
		{
			Jmp CReturn02
		}
	}
	// ----
	_asm
	{
		CMP DWORD PTR SS : [EBP + 0x10], 0x10A6//Flameberge
			Jmp CReturn01
	}
}

DWORD JCEvtKeyState;


//----- (0088E360) --------------------------------------------------------
char sub_88E360(int a4, int a5, int a6, int a7, float a8, float a9, float a10, float a11, int a12, int a13, int a14, float a15)
{
	int v15; // eax@1
	float v16; // ST10_4@1
	float v17; // ST0C_4@1
	float v18; // ST08_4@1
	float v19; // ST04_4@1

	glColor4f(1.0, 1.0, 1.0, a15);
	v15 = pMakeColor(0xFFu, 0xFFu, 0xFFu, 0xFFu);
	v16 = (double)a7;
	v17 = (double)a6;
	v18 = (double)a5;
	v19 = (double)a4;
	RenderBitMapColored(a12 + 31486, v19, v18, v17, v16, a8, a9, a10, a11, v15);
	return 1;
}
#define Convert ((double(__cdecl*)(float a1)) 0x004DB0C0)

void sub_88C680()
{
	int red; // ST20_4@14
	int v7; // ST20_4@16
	int v8; // ST00_4@16
	int *v10; // ST48_4@17
	int v11; // ST20_4@19
	int v12; // ST00_4@19
	char v155; // [sp+4Ch] [bp-26Ch]@17
	float v176; // [sp+9Ch] [bp-21Ch]@7
	int v177; // [sp+A0h] [bp-218h]@7
	int v233; // [sp+2B4h] [bp-4h]@17

	v176 = 0.0;
	float v35; // [sp+338h] [bp-4h]@1

	v177 = *(float*)0x5EF5A1C * 0.001000000047497451;
	v35 = Convert(v177) + 1.0;

	v176 = (signed int)((2.0 - v35) * 127.0) / 255;
	/*v177 = 2 * 0xE66DD8 % 140;
	if ( v177 <= 70 )
	v176 = (double)v177 * 0.009999999776482582 + 0.300000011920929;
	else
	v176 = 1.0 - (double)(v177 - 70) * 0.009999999776482582;*/

	if (*(DWORD*)0xE66DF8 > 0)
		*(DWORD*)0xE66DF8 -= 15;
	else
		*(DWORD*)0xE66DF8 = 0;
	if (15 * *(DWORD*)0xE66DD8 <= 479)
	{
		if (*(BYTE*)0xE66DD1)
		{
			v11 = *(DWORD*)0xE66DDC;
			v12 = 15 * *(DWORD*)0xE66DD8 - 329;
			*(DWORD *)(InstanceX() + 216);
			//sub_8613C0((int)InstanceX( ));
			sub_88E360(v12, 50, 329, 94, 0.0, 0.0, 0.640625, 0.7265625, v11, 0, 0, v176);
		}
		else
		{
			v7 = *(DWORD*)0xE66DDC;
			v8 = 15 * *(DWORD*)0xE66DD8 + 150;
			*(DWORD *)(InstanceX() + 216);
			//sub_8613C0((int)InstanceX( ));
			sub_88E360(v8, 50, 329, 94, 0.0, 0.0, 0.640625, 0.7265625, v7, 0, 0, v176);
			if (15 * ++*(DWORD*)0xE66DD8 > 479)
			{
				*(DWORD*)0xE66DD8 = 0;
				*(BYTE*)0xE66DD1 = -1;
				*(DWORD*)0xE66DF8 = 390;
				*(BYTE*)0x9867469 = 1;
				//v10 = (int *)sub_88ED40(&v155);
				v233 = 0;
				//sub_88EDD0((int)v10, v10);
				v233 = -1;
				//sub_88ED60(&v155);
			}
		}
	}
	else
	{
		red = *(DWORD*)0xE66DDC;
		*(DWORD *)(InstanceX() + 216);
		//sub_8613C0((int)InstanceX( ));
		sub_88E360(150, 50, 329, 94, 0.0, 0.0, 0.640625, 0.7265625, red, 0, 0, v176);
	}
}

void DataViewPortMapUser(float x, float y, float charx, float chary)
{
	int v4; // eax@4
	float v5; // ST34_4@16
	float v6; // ST38_4@16
	int v7; // [sp+24h] [bp-18h]@1
	int v8; // [sp+2Ch] [bp-10h]@4
	signed int i; // [sp+30h] [bp-Ch]@1

	for (i = 0; i < 400; ++i)
	{
		v8 = pGetPreviewStruct(pPreviewThis(), i);
		if (v8 && *(BYTE *)(v8 + 780) && v8 != dword_7BC4F04
			&& (*(BYTE *)(v8 + 800) == 1 || *(BYTE *)(v8 + 800) == 2 || *(BYTE *)(v8 + 800) == 4))
		{
			if (*(BYTE *)(v8 + 800) != 4 && (*(BYTE *)(v8 + 800) != 2 || *(DWORD *)(v8 + 824) != 730))
				glColor4f(0.80000001, 0.0, 0.0, 1.0);
			else
				glColor4f(1.0, 0.0, 1.0, 1.0);

			v5 = (double)(x + *(DWORD *)(v8 + 172) / 0.5 - charx) - 2.0;
			v6 = (double)(y + (256 - *(DWORD *)(v8 + 176)) / 0.5 - chary) - 4.0;
			pDrawBarForm(v5, v6, 4.0, 4.0, 0.0, 0);
			pGLSwitch();

			if (pCheckMouseOver((int)v5, (int)v6, (int) 4.0, (int) 4.0))
			{
				pDrawToolTip((int)v5, (int)v6 - 10, (char *)(v8 + 56));
			}
		}
	}
}
// 7BC4F04: using guessed type int dword_7BC4F04;


bool JGetCheckMapEvt(int x, int y, int w, int h)
{
	return 0;
}



void JCMinimap::Load()
{
	SetCompleteHook(0xFF, 0x0062EB26, &LoadObjectMapCore); //ok
	//-- tap map
	SetCompleteHook(0xE8, 0x0082B772, &JGetCheckMapEvt); //ok
//	SetCompleteHook(0xE9, 0x0082ABA0, &JGetFullMap);

}
