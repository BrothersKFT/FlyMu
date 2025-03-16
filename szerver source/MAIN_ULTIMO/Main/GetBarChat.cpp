#include "StdAfx.h"
#include "GetBarChat.h"
#include "Import.h"
#include "Util.h"
#include "Offset.h"
#include "WindowsStruct.h"

JCGetBarChat JCGetModelBarChat;

JCGetBarChat::JCGetBarChat()
{
}

JCGetBarChat::~JCGetBarChat()
{
}

//----- (0057FB20) --------------------------------------------------------
signed int sub_57FB20(char a1)
{
	signed int v2; // [sp+0h] [bp-4h]@2

	if (a1)
	{
		if (a1 != 2 && a1 != 8)
			v2 = -16711736;
		else
			v2 = -16769281;
	}
	else
	{
		v2 = -6426;
	}
	return v2;
}

//----- (0057FB70) --------------------------------------------------------
signed int sub_57FB70(char a1)
{
	signed int v2; // [sp+0h] [bp-4h]@2

	if (a1)
	{
		if (a1 != 2 && a1 != 8)
			v2 = -1773129196;
		else
			v2 = -1778384896;
	}
	else
	{
		v2 = -1775100406;
	}
	return v2;
}

int LogoGenScale = 0;

//----- (005985F0) --------------------------------------------------------
void subs_5985F0(signed int a4, signed int a5, int a6)
{
	float v26; // ST18_4@38
	int v44; // ST18_4@47
	int v46; // ST18_4@47
	char v122; // [sp+28h] [bp-38h]@35
	signed int v123; // [sp+30h] [bp-30h]@35
	int v124; // [sp+34h] [bp-2Ch]@27
	int v125; // [sp+3Ch] [bp-24h]@26
	int v126; // [sp+40h] [bp-20h]@26
	char v127; // [sp+47h] [bp-19h]@40
	int v128; // [sp+48h] [bp-18h]@26
	int v129; // [sp+4Ch] [bp-14h]@26
	int v130; // [sp+50h] [bp-10h]@26
	int v131; // [sp+54h] [bp-Ch]@84
	int v132; // [sp+58h] [bp-8h]@84
	unsigned __int8 v133; // [sp+5Ch] [bp-4h]@77
	unsigned __int8 v134; // [sp+5Dh] [bp-3h]@77

	if (pCheckEffectPlayer((DWORD *)(*(DWORD *)(a6 + 668) + 1260), 27))
		return;
	if (*(DWORD *)(a6 + 668) != dword_7BC4F04
		&& *(BYTE*)0x9867233 == 1
		&& pCheckEffectPlayer((DWORD *)(*(DWORD *)(a6 + 668) + 1260), 18))
	{
		if (*(BYTE *)(dword_7BC4F04 + 23) != 9 && *(BYTE *)(dword_7BC4F04 + 23) != 6)
		{
			if (*(BYTE *)(dword_7BC4F04 + 23) != 10 && *(BYTE *)(dword_7BC4F04 + 23) != 7)
			{
				if (*(BYTE *)(dword_7BC4F04 + 23) != 11 && *(BYTE *)(dword_7BC4F04 + 23) != 8)
				{
					if ((*(BYTE *)(dword_7BC4F04 + 23) == 13 || *(BYTE *)(dword_7BC4F04 + 23) == 12)
						&& *(BYTE *)(*(DWORD *)(a6 + 668) + 23) != 13
						&& *(BYTE *)(*(DWORD *)(a6 + 668) + 23) != 12)
					{
						return;
					}
				}
				else if (*(BYTE *)(*(DWORD *)(a6 + 668) + 23) != 11 && *(BYTE *)(*(DWORD *)(a6 + 668) + 23) != 8)
				{
					return;
				}
			}
			else if (*(BYTE *)(*(DWORD *)(a6 + 668) + 23) != 10 && *(BYTE *)(*(DWORD *)(a6 + 668) + 23) != 7)
			{
				return;
			}
		}
		else if (*(BYTE *)(*(DWORD *)(a6 + 668) + 23) != 9 && *(BYTE *)(*(DWORD *)(a6 + 668) + 23) != 6)
		{
			return;
		}
	}
	EnableAlphaTest(1);
	glColor3f(1.0, 1.0, 1.0);

	if (pWinFontHeight > 32)
		pWinFontHeight = 32;
	v128 = a4;
	v129 = a5;
	v125 = *(DWORD *)(a6 + 680);
	v126 = *(DWORD *)(a6 + 684);
	v130 = sub_9CEBF0((double)pWinFontHeight / *(float*)0xE7C3D8);
	//-- Store
	if (sub_5BD3E0(*(DWORD *)(a6 + 668)))
	{
		pSetFont(pTextThis(), (int)pFontBold);

		sub_4200F0_Addr(pTextThis(), sub_5BD440(*(DWORD *)(a6 + 668)));
		SetTextColorByHDC(pTextThis(), (int)sub_5BD400(*(DWORD *)(a6 + 668)));
		pDrawText(pTextThis(), v128, v129, pGetTextLine(pTextLineThis, 1104), 0, v130, (LPINT)1, 0);

		v128 += v124;
		SetTextColorByHDC(pTextThis(), sub_5BD420(*(DWORD *)(a6 + 668)));

		pDrawText(pTextThis(), v128, v129, (char *)(a6 + 124), v125 - v124, v130, (LPINT)1, 0);
		pSetFont(pTextThis(), (int)pFontNormal);
		v128 = a4;
		v129 += v130;
	}
	//-- Fin store
	else if (sub_5D3030(*(DWORD *)0xE61E18)
		&& *(BYTE *)(dword_7BC4F04 + 31) != *(BYTE *)(*(DWORD *)(a6 + 668) + 31)
		&& !sub_5BCE80()
		&& *(BYTE *)(*(DWORD *)(a6 + 668) + 800) == 1)
	{
		if (!*(DWORD *)(*(DWORD *)(a6 + 668) + 1428))
			return;
		if (*(BYTE *)(*(DWORD *)(a6 + 668) + 800) == 1 && *(DWORD *)(*(DWORD *)(a6 + 668) + 824) == 1163)
		{
			v123 = sub_9CEBF0((double)*(signed int *)(a6 + 672) + (double)*(signed int *)(a6 + 680) * 0.5 + 20.0);
			v122 = *(BYTE *)(*(DWORD *)(a6 + 668) + 31);
			if (v122 == 1)
			{
				LogoGenScale = 1;
				JCGetModelGen(*(DWORD *)(GetInstance() + 288), (double)v123, (double)a5, *(BYTE *)(*(DWORD *)(a6 + 668) + 31), *(BYTE *)(*(DWORD *)(a6 + 668) + 1424), 1, v129);
				LogoGenScale = 0;
				return;
			}
			if (v122 == 2)
			{
				LogoGenScale = 1;
				JCGetModelGen(*(DWORD *)(GetInstance() + 288), (double)v123, (double)a5, *(BYTE *)(*(DWORD *)(a6 + 668) + 31), *(BYTE *)(*(DWORD *)(a6 + 668) + 1424), 1, v129);
				LogoGenScale = 0;
				return;
			}
		}
	}
	//--
	v127 = 0;
	if (pCheckEffectPlayer((DWORD *)(*(DWORD *)(a6 + 668) + 1260), 28)
		|| *(BYTE *)(*(DWORD *)(a6 + 668) + 21) == 32
		|| *(BYTE *)(*(DWORD *)(a6 + 668) + 21) == 8)
	{
		v127 = 1;
		pSetBackgroundTextColor(pTextThis(), 0x1Eu, 0x1Eu, 0x1Eu, 0xC8u);
		pSetTextColor(pTextThis(), 0xC8u, 0xFFu, 0xFFu, 0xFFu);
	}
	//--
	if (*(DWORD *)(a6 + 668) == dword_7BC4F04)
	{
		pSetBackgroundTextColor(pTextThis(), 0x3Cu, 0x64u, 0, 0x96u);
		pSetTextColor(pTextThis(), 0xC8u, 0xFFu, 0, 0xFFu);
	}
	else if (*(WORD *)(*(DWORD *)(a6 + 668) + 124) == *(WORD *)(dword_7BC4F04 + 124))
	{
		v44 = sub_57FB70(1);
		sub_4200F0_Addr(pTextThis(), v44);
		v46 = sub_57FB20(1);
		SetTextColorByHDC(pTextThis(), v46);
	}
	else
	{
		sub_4200F0_Addr(pTextThis(), sub_57FB70(*(BYTE *)(*(DWORD *)(a6 + 668) + 26)));
		SetTextColorByHDC(pTextThis(), sub_57FB20(*(BYTE *)(*(DWORD *)(a6 + 668) + 26)));
	}
	//--
	if (a6 != -64 && *(BYTE *)(a6 + 64))
	{
		pDrawText(pTextThis(), v128, v129, (char *)(a6 + 64), v125, v130, (LPINT)1, 0);
		v129 += v130;
	}
	if (a6 != -94 && *(BYTE *)(a6 + 94))
	{
		pDrawText(pTextThis(), v128, v129, (char *)(a6 + 94), v125, v130, (LPINT)1, 0);
		v129 += v130;
	}
	//--
	if (v127)
	{
		pSetTextColor(pTextThis(), 0x64u, 0xFAu, 0xFAu, 0xFFu);
	}
	else
	{
		sub_5984D0(*(BYTE *)(a6 + 140));
	}
	//--
	if (*(DWORD *)(a6 + 672) <= *(DWORD *)0x879340C
		&& *(DWORD *)0x879340C < (signed int)(*(DWORD *)(a6 + 672) + 640 * *(DWORD *)(a6 + 680) / (unsigned int)*(QWORD *)0xE61E58)
		&& *(DWORD *)(a6 + 676) <= *(DWORD *)0x8793410
		&& *(DWORD *)0x8793410 < (signed int)(*(DWORD *)(a6 + 676) + 480 * *(DWORD *)(a6 + 684) / (unsigned int)*(QWORD *)0xE61E5C)
		&& *(BYTE *)0xE61744
		&& *(BYTE *)(dword_7BC4F04 + 14)
		&& sub_9D09B0((BYTE *)a6, (BYTE *)(dword_7BC4F04 + 56))
		&& (unsigned int)(signed __int64)*(float*)0x5EF5A1C % 0x18 < 0xC)
	{
		sub_4200F0_Addr(pTextThis(), sub_41FFE0_Addr(pTextThis()));
		SetTextColorByHDC(pTextThis(), sub_420010_Addr(pTextThis()));
	}
	if (v127)
	{
		pSetFont(pTextThis(), (int)pFontBold);
		pDrawText(pTextThis(), v128, v129, (char *)a6, v125, v130, (LPINT)1, 0);
		v129 += v130;
		pSetFont(pTextThis(), (int)pFontNormal);
	}
	else
	{
		pDrawText(pTextThis(), v128, v129, (char *)a6, v125, v130, (LPINT)1, 0);
		v129 += v130;
	}
	if (*(BYTE *)(a6 + 141))
	{
		if (*(BYTE *)(a6 + 141) == 1)
		{
			pSetBackgroundTextColor(pTextThis(), 0x1Eu, 0x32u, 0, 0x96u);
		}
		else if (v127)
		{
			pSetBackgroundTextColor(pTextThis(), 0x1Eu, 0x1Eu, 0x1Eu, 0xC8u);
		}
		else
		{
			pSetBackgroundTextColor(pTextThis(), 0x32u, 0, 0, 0x96u);
		}
	}
	else
	{
		pSetBackgroundTextColor(pTextThis(), 0xAu, 0x1Eu, 0x32u, 0x96u);
	}
	v133 = -1;
	v134 = -1;
	if (*(DWORD *)(a6 + 660) > 0 && *(DWORD *)(a6 + 660) < 10)
		v133 = -128;
	if (*(DWORD *)(a6 + 664) > 0 && *(DWORD *)(a6 + 664) < 10)
		v134 = -128;
	if (v127)
	{
		v131 = pMakeColor(0xFAu, 0xC8u, 0x32u, v133);
		v132 = pMakeColor(0xFAu, 0xC8u, 0x32u, v134);
	}
	else
	{
		v131 = pMakeColor(0xE6u, 0xDCu, 0xC8u, v133);
		v132 = pMakeColor(0xE6u, 0xDCu, 0xC8u, v134);
	}
	//--
	if (*(DWORD *)(a6 + 664) <= 0)
	{
		if (*(DWORD *)(a6 + 660) > 0)
		{
			SetTextColorByHDC(pTextThis(), v131);
			pDrawText(pTextThis(), v128, v129, (char *)(a6 + 148), v125, v130, (LPINT)1, 0);
		}
	}
	else
	{
		SetTextColorByHDC(pTextThis(), v132);
		pDrawText(pTextThis(), v128, v129, (char *)(a6 + 404), v125, v130, (LPINT)1, 0);
		v129 += v130;
		SetTextColorByHDC(pTextThis(), v131);
		pDrawText(pTextThis(), v128, v129, (char *)(a6 + 148), v125, v130, (LPINT)1, 0);
	}
	//-- revisa si tiene guild
	if (*(BYTE *)(*(DWORD *)(a6 + 668) + 24) == 255)
	{
		v26 = 0.0;
	}
	else
	{
		v26 = 18.0;
		JCGetMarkGuild(*(WORD *)(*(DWORD *)(a6 + 668) + 124), 1);
		RenderBitmap(31740, (double)a4 - v26, (double)a5, 16.0, 16.0, 0.0, 0.0, 1.0, 1.0, 1, 1, 0.0);
	}
	//--
	if (*(BYTE *)(*(DWORD *)(a6 + 668) + 800) == 1 && *(DWORD *)(*(DWORD *)(a6 + 668) + 824) == 1163)
	{
		if (*(DWORD *)(a6 + 664) > 0)
			v129 -= v130;
		if (*(BYTE *)(*(DWORD *)(a6 + 668) + 31) == 1)
		{
			LogoGenScale = 1;
			JCGetModelGen(*(DWORD *)(GetInstance() + 288), (double)a4 - v26, (double)a5, *(BYTE *)(*(DWORD *)(a6 + 668) + 31), *(BYTE *)(*(DWORD *)(a6 + 668) + 1424), 1, (double)v129);
			LogoGenScale = 0;
		}
		else if (*(BYTE *)(*(DWORD *)(a6 + 668) + 31) == 2)
		{
			LogoGenScale = 1;
			JCGetModelGen(*(DWORD *)(GetInstance() + 288), (double)a4 - v26, (double)a5, *(BYTE *)(*(DWORD *)(a6 + 668) + 31), *(BYTE *)(*(DWORD *)(a6 + 668) + 1424), 1, (double)v129);
			LogoGenScale = 0;
		}
	}


}
// E61744: using guessed type char byte_E61744;
// E61E18: using guessed type int dword_E61E18;
// E7C3D8: using guessed type float flt_E7C3D8;
// 5EF5A1C: using guessed type float flt_5EF5A1C;
// 7BC4F04: using guessed type int dword_7BC4F04;
// 81C0380: using guessed type int pWinFontHeight;
// 879340C: using guessed type int dword_879340C;
// 8793410: using guessed type int dword_8793410;


void JCGenScaleLogo(int ImageID, float PosX, float PosY, float Width, float Height, float CurrentMoveX, float CurrentMoveY, float ScaleX, float ScaleY, bool ScaleSize, bool ScalePosition, bool ScaleAlpha)
{
	if (LogoGenScale == 1)
	{
		RenderBitmap(ImageID, PosX + 10.0, PosY + 5.0, Width - 10.0, Height - 10.0, CurrentMoveX, CurrentMoveY, ScaleX, ScaleY, ScaleSize, ScalePosition, ScaleAlpha);
	}
	else
	{
		RenderBitmap(ImageID, PosX, PosY, Width, Height, CurrentMoveX, CurrentMoveY, ScaleX, ScaleY, ScaleSize, ScalePosition, ScaleAlpha);
	}
}

void JCGetBarChat::Load()
{
	SetCompleteHook(0xE8, 0x005BAFAB, &subs_5985F0);
	SetCompleteHook(0xE8, 0x007C5DB0, &JCGenScaleLogo);
}