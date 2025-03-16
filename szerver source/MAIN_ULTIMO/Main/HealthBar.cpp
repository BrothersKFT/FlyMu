#include "stdafx.h"
#include "CustomRankUser.h"
#include "Defines.h"
#include "HealthBar.h"
#include "Interface.h"
#include "User.h"
#include "Util.h"
#include "Object.h"
#include "Protect.h"
#include "Import.h"
#include "Common.h"
#include "MonsterHpBar.h"

#if (HPTYPE ==1)
NEW_HEALTH_BAR gNewHealthBar[MAX_MAIN_VIEWPORT];

void ClearNewHealthBar() // OK
{
	for(int n=0;n < MAX_MAIN_VIEWPORT;n++)
	{
		gNewHealthBar[n].index = 0xFFFF;
		gNewHealthBar[n].type = 0;
		gNewHealthBar[n].rate = 0;
	}
}

void InsertNewHealthBar(PMSG_NEW_HEALTH_RECV* lpInfo) // OK
{
	for (int n = 0; n < MAX_MAIN_VIEWPORT; n++)
	{
		if (gNewHealthBar[n].index == 0xFFFF)
		{
			gNewHealthBar[n].index = lpInfo->index;
			gNewHealthBar[n].type = lpInfo->type;
			gNewHealthBar[n].rate = lpInfo->rate;
			gNewHealthBar[n].monsterid = lpInfo->monsterid;
			gNewHealthBar[n].Life = lpInfo->Life;
			gNewHealthBar[n].MaxLife = lpInfo->MaxLife;
			gNewHealthBar[n].Level = lpInfo->Level;
			gNewHealthBar[n].Reset = lpInfo->Reset;
			gNewHealthBar[n].Shield = lpInfo->Shield;
			gNewHealthBar[n].MaxShield = lpInfo->MaxShield;
			gNewHealthBar[n].SDrate = lpInfo->SDrate;
			gNewHealthBar[n].isSameGuild = lpInfo->isSameGuild;
			gNewHealthBar[n].HaveGuild = lpInfo->HaveGuild;

			if (lpInfo->type == emPlayer && lpInfo->HaveGuild)
			{
				memcpy(gNewHealthBar[n].GuildName, lpInfo->GuildName, sizeof(gNewHealthBar[n].GuildName));
				char kek[65];

				for (int i = 0; i < 32; i++)
				{
					sprintf(&kek[i * 2], "%02x", lpInfo->Mark[i]);
				}
				kek[64] = '\0';

				for (int i = 0; i < 64; i++)
				{
					if (kek[i] >= 97)
					{
						gNewHealthBar[n].Mark[i] = (int)kek[i] - 87;
					}
					else
					{
						gNewHealthBar[n].Mark[i] = (int)kek[i] - 48;
					}
				}
			}
			return;
		}
	}
}

NEW_HEALTH_BAR* GetNewHealthBar(WORD index,BYTE type) // OK
{
	for(int n=0;n < MAX_MAIN_VIEWPORT;n++)
	{
		if(gNewHealthBar[n].index != 0xFFFF)
		{
			if(gNewHealthBar[n].index == index && gNewHealthBar[n].type == type)
			{
				return &gNewHealthBar[n];
			}
		}
	}

	return 0;
}

void DrawHealthBar()
{

	int PosX, PosY;
	float LifeBarWidth = 66.95;
	VAngle Angle;

	for (int n = 0; n < MAX_MAIN_VIEWPORT; n++)
	{
		lpViewObj lpObj = &*(ObjectPreview*)pGetPreviewStruct(pPreviewThis(), n);
		lpViewObj lpTarget	= gObjUser.lpViewTarget;

		bool isTarget = 1;

		if (!lpTarget || (lpTarget->m_Model.ObjectType != emMonster && lpTarget->m_Model.ObjectType != emPlayer) || !lpTarget->m_Model.IsSetted || lpTarget->aIndex != lpObj->aIndex)
		{
			isTarget = 0;
		}

		if (!lpObj)
		{
			continue;
		}

		if (lpObj->m_Model.IsSetted == 0)
		{
			continue;
		}

		NEW_HEALTH_BAR* lpNewHealthBar = GetNewHealthBar(lpObj->aIndex, lpObj->m_Model.ObjectType);

		if (lpNewHealthBar == 0)
		{
			continue;
		}

		int LifePercent = lpNewHealthBar->rate / 10;
		float BarWidth = (((66.95 - 1) / 100.0f) * lpNewHealthBar->rate) - 1;
		float SDBarWidth = (((66.95 - 1) / 100.0f) * lpNewHealthBar->SDrate) - 1;

		Angle.X = lpObj->m_Model.VecPosX;
		Angle.Y = lpObj->m_Model.VecPosY;
		Angle.Z = lpObj->m_Model.VecPosZ + lpObj->m_Model.Unknown216.Z + 100.0;

		pGetPosFromAngle(&Angle, &PosX, &PosY);
		PosX -= (int)floor(LifeBarWidth / (double)2.0);

		pSetBlend(true);

		if (lpNewHealthBar->type == emPlayer/* && istarget*/)
		{
			if (HPMonsterName == 1)
			{
				bool isPartyMember = IsPartyMember(n);
				if (!isTarget && !isPartyMember && !lpNewHealthBar->isSameGuild)
				{
					continue;
				}

				if (isPartyMember)
				{
					glColor4f(RGBTOGLFLOAT(63), RGBTOGLFLOAT(124), RGBTOGLFLOAT(204), 0.9); // Цвет фона для имени
				}
				else if (lpNewHealthBar->isSameGuild)
				{
					glColor4f(RGBTOGLFLOAT(18), RGBTOGLFLOAT(226), RGBTOGLFLOAT(131), 0.9); // Цвет фона для имени
				}
				else
				{
					glColor4f(RGBTOGLFLOAT(0), RGBTOGLFLOAT(0), RGBTOGLFLOAT(0), 0.6); // Цвет фона для имени
				}

				if (!isTarget)
				{
					pDrawBarForm((float)(PosX - 1), (float)(PosY - 12), 66.95, 10, 0.0, 0); // Фон для имени
				}
				else
				{
					pDrawBarForm((float)(PosX - 1), (float)(PosY + 12), 66.95, 20, 0.0, 0); // Фон для имени
				}

				glColor4f(RGBTOGLFLOAT(0), RGBTOGLFLOAT(0), RGBTOGLFLOAT(0), 0.6); // Цвет фона для хпбара
				pDrawBarForm((float)(PosX - 1), (float)(PosY - 1.5), 66.95, 6, 0.0, 0); // Фон хпбара
				pDrawBarForm((float)(PosX - 1), (float)(PosY + 5), 66.95, 6, 0.0, 0); // Фон SD

				glColor4f(RGBTOGLFLOAT(255), RGBTOGLFLOAT(ABS(((255.0f / 100.0f) * lpNewHealthBar->rate) - 255.0f)), RGBTOGLFLOAT(0), 0.8); // Цвет ХП Бара

				pDrawBarForm((float)(PosX), (float)(PosY), BarWidth, 3, 0.0, 0); // ХпБар

				glColor4f(RGBTOGLFLOAT(255), RGBTOGLFLOAT((255.0f / 100.0f) * lpNewHealthBar->SDrate), RGBTOGLFLOAT(0), 0.8); // Цвет SD Бара

				pDrawBarForm((float)(PosX), (float)(PosY + 7), SDBarWidth, 2.5, 0.0, 0); // SD Бар

				if (!isTarget)
				{
					if (lpNewHealthBar->isSameGuild)
					{
						DrawInterfaceText(lpObj->Name, PosX - 1, PosY - 11, 66.95, 1, eBlack, 9, 3); // Драв имени
					}
					else
					{
						DrawInterfaceText(lpObj->Name, PosX - 1, PosY - 11, 66.95, 1, eWhite, 9, 3); // Драв имени
					}
				}
				else
				{
					char Text[100];
					sprintf(Text, "Lvl: %d R: %d HP: %s/%s", lpNewHealthBar->Level, lpNewHealthBar->Reset, ParseReducedValue((int)lpNewHealthBar->Life), ParseReducedValue((int)lpNewHealthBar->MaxLife));

					if (lpNewHealthBar->isSameGuild)
					{
						DrawInterfaceText(lpObj->Name, PosX - 1, PosY + 23, 67, 1, eBlack, 9, 3); // Драв имени
						DrawInterfaceText(Text, PosX - 1, PosY + 13, 67, 1, eBlack, 9, 3); // Драв инфы
					}
					else
					{
						DrawInterfaceText(lpObj->Name, PosX - 1, PosY + 23, 67, 1, eWhite, 9, 3); // Драв имени
						DrawInterfaceText(Text, PosX - 1, PosY + 13, 67, 1, eWhite, 9, 3); // Драв инфы
					}
				}
			}
		}
		else
		{
			if (!isTarget)
			{
				continue;
			}
			CUSTOM_HPBAR* HpBarEx = gMonsterHpBar.GetHpBar(lpNewHealthBar->monsterid);

			if (HpBarEx == 0)
			{
				if (HPMonsterName == 1)
				{
					glColor4f(RGBTOGLFLOAT(0), RGBTOGLFLOAT(0), RGBTOGLFLOAT(0), 0.6); // Цвет фона для имени

					if (!isTarget)
					{
						pDrawBarForm((float)(PosX - 1), (float)(PosY - 12), 66.95, 10, 0.0, 0); // Фон для имени
					}
					else
					{
						pDrawBarForm((float)(PosX - 1), (float)(PosY - 22), 66.95, 20, 0.0, 0); // Фон для имени
					}

					glColor4f(RGBTOGLFLOAT(0), RGBTOGLFLOAT(0), RGBTOGLFLOAT(0), 0.6); // Цвет фона для хпбара
					pDrawBarForm((float)(PosX - 1), (float)(PosY - 1.5), 66.95, 6, 0.0, 0); // Фон хпбара

					glColor4f(RGBTOGLFLOAT(255), RGBTOGLFLOAT(ABS(((255.0f / 100.0f) * lpNewHealthBar->rate) - 255.0f)), RGBTOGLFLOAT(0), 0.8); // Цвет ХП Бара

					pDrawBarForm((float)(PosX), (float)(PosY), BarWidth, 3, 0.0, 0); // ХпБар

					if (!isTarget)
					{
						DrawInterfaceText(lpObj->Name, PosX - 1, PosY - 11, 66.95, 1, eWhite, 9, 3); // Драв имени
					}
					else
					{
						char Text[100];
						sprintf(Text, "Lvl: %d HP: %s/%s", lpNewHealthBar->Level, ParseReducedValue((int)lpNewHealthBar->Life), ParseReducedValue((int)lpNewHealthBar->MaxLife));

						DrawInterfaceText(lpObj->Name, PosX - 1, PosY - 21, 67, 1, eWhite, 9, 3); // Драв имени
						DrawInterfaceText(Text, PosX - 1, PosY - 11, 67, 1, eWhite, 9, 3); // Драв инфы
					}
				}
			}
			else
			{
				if (HPMonsterName == 1)
				{
					glColor4f(RGBTOGLFLOAT(HpBarEx->Red), RGBTOGLFLOAT(HpBarEx->Green), RGBTOGLFLOAT(HpBarEx->Blue), HpBarEx->Opacity); // Цвет фона для имени

					if (!isTarget)
					{
						pDrawBarForm((float)(PosX - 1), (float)(PosY - 22), 66.95, 20, 0.0, 0); // Фон для имени
					}
					else
					{
						pDrawBarForm((float)(PosX - 1), (float)(PosY - 32), 66.95, 30, 0.0, 0); // Фон для имени
					}

					glColor4f(RGBTOGLFLOAT(0), RGBTOGLFLOAT(0), RGBTOGLFLOAT(0), 0.6); // Цвет фона для хпбара
					pDrawBarForm((float)(PosX - 1), (float)(PosY - 1.5), 66.95, 6, 0.0, 0); // Фон хпбара

					glColor4f(RGBTOGLFLOAT(255), RGBTOGLFLOAT(ABS(((255.0f / 100.0f) * lpNewHealthBar->rate) - 255.0f)), RGBTOGLFLOAT(0), 0.8); // Цвет ХП Бара

					pDrawBarForm((float)(PosX), (float)(PosY), BarWidth, 3, 0.0, 0); // ХпБар


					if (!isTarget)
					{

						DrawInterfaceText(lpObj->Name, PosX - 1, PosY - 11, 66.95, 1, eWhite, 9, 3); // Драв имени
						DrawInterfaceText(HpBarEx->Name, PosX - 1, PosY - 21, 66.95, 1, eWhite, 9, 3); // Драв имени

					}
					else
					{

						char Text[100];
						sprintf(Text, "Lvl: %d HP: %s/%s", lpNewHealthBar->Level, ParseReducedValue((int)lpNewHealthBar->Life), ParseReducedValue((int)lpNewHealthBar->MaxLife));

						DrawInterfaceText(HpBarEx->Name, PosX - 1, PosY - 31, 66.95, 1, eWhite, 9, 3); // Драв сабимени
						DrawInterfaceText(lpObj->Name, PosX - 1, PosY - 21, 66.95, 1, eWhite, 9, 3); // Драв имени
						DrawInterfaceText(Text, PosX - 1, PosY - 11, 66.95, 1, eWhite, 9, 3); // Драв инфы

					}
				}
			}
		}





		pGLSwitch();
	}

//	gCustomRankUser.DrawInfo();

	pGLSwitch();

	glColor3f(1.0, 1.0, 1.0);
}

void AllInOne()
{
	DrawHealthBar();
	gCustomRankUser.DrawInfo();
}

bool IsPartyMember(int ViewportID)
{
#if (_NEW_PARTY_SYSTEM_ == TRUE )
	for (int PartySlot = 0; PartySlot < g_Party.PartyMemberCount; PartySlot++)
#else
	for (int PartySlot = 0; PartySlot < pPartyMemberCount; PartySlot++)
#endif
	{
		PartyList PartyMember = *(PartyList*)((char*)&pPartyListStruct + sizeof(PartyList) * PartySlot);
		//lpViewObj lpPartyObj	= &*(ObjectPreview*)pGetPreviewStruct(pPreviewThis(), PartyMember.ViewportID);
		if (ViewportID == PartyMember.ViewportID)
		{
			return true;
		}
	}

	return false;
}
#else
NEW_HEALTH_BAR gNewHealthBar[MAX_MAIN_VIEWPORT];

void ClearNewHealthBar() // OK
{
	for (int n = 0; n < MAX_MAIN_VIEWPORT; n++)
	{
		gNewHealthBar[n].index = 0xFFFF;
		gNewHealthBar[n].type = 0;
		gNewHealthBar[n].rate = 0;
		gNewHealthBar[n].rate2 = 0;
	}
}

void InsertNewHealthBar(WORD index, BYTE type, BYTE rate, BYTE rate2) // OK
{
	for (int n = 0; n < MAX_MAIN_VIEWPORT; n++)
	{
		if (gNewHealthBar[n].index == 0xFFFF)
		{
			gNewHealthBar[n].index = index;
			gNewHealthBar[n].type = type;
			gNewHealthBar[n].rate = rate;
			gNewHealthBar[n].rate2 = rate2;
			return;
		}
	}
}

NEW_HEALTH_BAR* GetNewHealthBar(WORD index, BYTE type) // OK
{
	for (int n = 0; n < MAX_MAIN_VIEWPORT; n++)
	{
		if (gNewHealthBar[n].index != 0xFFFF)
		{
			if (gNewHealthBar[n].index == index && gNewHealthBar[n].type == type)
			{
				return &gNewHealthBar[n];
			}
		}
	}

	return 0;
}

void DrawNewHealthBar() // OK
{
	if (pPlayerState == 4) //Select Character
	{
		return;
	}

	int PosX, PosY, LifeProgress, ShieldProgress;

	float LifeBarWidth; // [sp+D4h] [bp-4h]@2

	LifeBarWidth = 38.0;

	char LifeDisplay[25];
	VAngle Angle;

	if (gProtect.m_MainInfo.DisablePartyHpBar == 1)
	{
		if (pPartyMemberCount > 0)
		{
			for (int j = 0; j < pPartyMemberCount; j++)
			{
				signed int PartyNummber = *((DWORD*)&pPartyListStruct + 8 * j + 7);

				DWORD ViewportAddress = ((DWORD(__thiscall*)(void*, DWORD))0x0096A4C0)(((void*(*)())0x00402BC0)(), PartyNummber);

				if (ViewportAddress)
				{
					Angle.X = *(float*)(ViewportAddress + 0x404);

					Angle.Y = *(float*)(ViewportAddress + 0x408);

					Angle.Z = *(float*)(ViewportAddress + 0x40C) + *(float*)(ViewportAddress + 0x3E8) + 100.0f;

					pGetPosFromAngle(&Angle, &PosX, &PosY);

					RenderBitmap(30019, (float)(PosX - 8), (float)(PosY - 32), 24.0, 24.0, 0.0, 0.40000001f, 1.4f, 1.4f, 1, 1, 0.0);
				}
			}
		}
	}
	else if (gProtect.m_MainInfo.DisablePartyHpBar == 0)
	{
		((void(*)())0x005BA770)();
	}

	EnableAlphaTest(1);
	glColor4f(1.0, 1.0, 1.0, 1.0);

	for (int n = 0; n < MAX_MAIN_VIEWPORT; ++n)
	{
		DWORD ViewPortAddr = pGetPreviewStruct(pPreviewThis(), n);

		if (ViewPortAddr)
		{
			if (*(BYTE*)(ViewPortAddr + 0x30C) == 0)
			{
				continue;
			}

			Angle.X = *(float*)(ViewPortAddr + 0x404);

			Angle.Y = *(float*)(ViewPortAddr + 0x408);

			Angle.Z = *(float*)(ViewPortAddr + 0x40C) + *(float*)(ViewPortAddr + 0x3E8) + 100.0f;

			pGetPosFromAngle(&Angle, &PosX, &PosY);

			if (*(BYTE*)(ViewPortAddr + 0x320) == 1) //Check User
			{
				gCustomRankUser.RenderShowLogRank(ViewPortAddr, *(WORD*)(ViewPortAddr + 0x7E), PosX - 42, PosY);
			}

			PosX -= (int)(LifeBarWidth / 2.0);

			PosY -= 16;

			NEW_HEALTH_BAR* lpNewHealthBar = GetNewHealthBar(*(WORD*)(ViewPortAddr + 0x7E), *(BYTE*)(ViewPortAddr + 0x320));

			char* name = (char*)(ViewPortAddr + 0x38);

			if (lpNewHealthBar == 0)
			{
				continue;
			}

			int LifePercent = lpNewHealthBar->rate / 10;
			int ShieldPercent = lpNewHealthBar->rate2 / 10;

			LifeProgress = (LifePercent > 10) ? 10 : LifePercent;
			ShieldProgress = (ShieldPercent > 10) ? 10 : ShieldPercent;

			if (*(BYTE*)(ViewPortAddr + 0x320) == 1) //Check User
			{
				glColor4f(0.0, 0.0, 0.0, 0.8);
				pDrawBarForm((double)PosX, (double)PosY, LifeBarWidth + 4.0, (gProtect.m_MainInfo.CustomInterfaceType != 1) ? 10.0 : 6.0, 0.0, 0);
				pGLSwitch();

				if (gProtect.m_MainInfo.CustomInterfaceType != 1)
				{
					glColor4f(0.19607843, 0.039215688, 0.0, 0.8);
					pDrawBarForm((double)(PosX + 2), (double)(PosY + 2), LifeBarWidth, 2.0, 0.0, 0);
					pGLSwitch();
					glColor3f(0.98039216f, 5.039215688f, 0.0);
					for (int i = 0; i < ShieldProgress; ++i)
					{
						pDrawBarForm((double)(PosX + 4 * i + 2), (double)(PosY + 6), 3.0, 2.0, 0.0, 0);
					}
					pGLSwitch();
				}
			}
			else
			{
				if (HPMonsterName == 1)
				{
					glColor4f(0.2, 0.0, 0.0, 0.8);
					pDrawBarForm((double)PosX, (double)PosY, LifeBarWidth + 4.0, 6.0, 0.0, 0);
					pGLSwitch();
				}
			}
			if (*(BYTE*)(ViewPortAddr + 0x320) == 1) //Check User
			{
				glColor4f(0.19607843, 0.039215688, 0.0, 0.8);
				pDrawBarForm((double)(PosX + 2), (double)(PosY + 2), LifeBarWidth, 2.0, 0.0, 0);
				pGLSwitch();

				glColor3f(0.98039216, 0.039215688, 0.0);

				for (int j = 0; j < LifeProgress; ++j)
				{
					pDrawBarForm((double)(PosX + 4 * j + 2), (double)(PosY + 2), 3.0, 2.0, 0.0, 0);
				}
				pGLSwitch();
			}
			else
			{
				if (HPMonsterName == 1)
				{
					glColor4f(0.19607843, 0.039215688, 0.0, 0.8);
					pDrawBarForm((double)(PosX + 2), (double)(PosY + 2), LifeBarWidth, 2.0, 0.0, 0);
					pGLSwitch();

					glColor3f(0.98039216, 0.039215688, 0.0);

					for (int j = 0; j < LifeProgress; ++j)
					{
						pDrawBarForm((double)(PosX + 4 * j + 2), (double)(PosY + 2), 3.0, 2.0, 0.0, 0);
					}
					pGLSwitch();
				}
			}

			if ((pCursorX >= PosX - 2) && ((float)pCursorX <= (float)PosX + LifeBarWidth + 2) && (pCursorY >= PosY - 2) && (pCursorY < PosY + 10))
			{
				if (*(BYTE*)(ViewPortAddr + 0x320) == 1) //Check User
				{
					if (gProtect.m_MainInfo.CustomInterfaceType != 1)
					{
						wsprintf(LifeDisplay, "HP : %d0%% | SD : %d0%%", LifePercent, ShieldPercent);
						pSetTextColor(pTextThis(), 0xFF, 0xE6, 0xD2, 0xFF);
						pDrawText(pTextThis(), PosX - 20, PosY - 10, LifeDisplay, 0, 0, (LPINT)3, 0);
					}
					else
					{
						wsprintf(LifeDisplay, "HP : %d0%%", LifePercent);
						pSetTextColor(pTextThis(), 0xFF, 0xE6, 0xD2, 0xFF);
						pDrawText(pTextThis(), PosX, PosY - 8, LifeDisplay, 0, 0, (LPINT)3, 0);
					}
				}
				else
				{
					if (HPMonsterName == 1)
					{
						wsprintf(LifeDisplay, "HP : %d0%%", LifePercent);
						pSetTextColor(pTextThis(), 0xFF, 0xE6, 0xD2, 0xFF);
						pDrawText(pTextThis(), PosX, PosY - 8, LifeDisplay, 0, 0, (LPINT)3, 0);
					}
				}
			}
		}
		pGLSwitch();
		EnableAlphaTest(0);
	}

	gCustomRankUser.DrawInfo();

	pGLSwitch();

	glColor3f(1.0, 1.0, 1.0);
}
#endif