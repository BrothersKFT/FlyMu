#include "StdAfx.h"
#include "PartyBar.h"
#include "Util.h"
#include "TMemory.h"
#include "Import.h"
#include "Object.h"
#include "Defines.h"
#include "Offset.h"
#include "WindowsStruct.h"
#include "PartyBuffs.h"
#include "Protect.h"
#include "MiniMapInfo.h"
#include "PrintPlayer.h"
#include "Interface.h"
#include "Common.h"
#include "User.h"

PartyBar GetPartyBar;
int eventillo;

PartyBar::PartyBar()
{
	this->PartyMemberCount = 0;

	this->ClickTick = 0;
	this->OnClick = -1;
	this->OnClickD = -1;
	this->Page = 0;
	this->PartyShow = true;

	ZeroMemory(&this->JCPartyDB, sizeof(JCPartyDB));
	ZeroMemory(&this->LifePercent, sizeof(LifePercent));
	ZeroMemory(&this->ViewportID, sizeof(ViewportID));
}

PartyBar::~PartyBar()
{
}


void PartyBar::JCGCPartyListAll(LPBYTE aRecv)
{
	signed int i; // [sp+8h] [bp-Ch]@1
	int datasize = 0; // [sp+10h] [bp-4h]@1
	char * v2; // ST10_4@3

	PMSG_PARTYLISTCOUNT pCount;
	memcpy(&pCount, &aRecv[datasize], sizeof(pCount));

	GetPartyBar.PartyMemberCount = pCount.Count;

	datasize = 5;

	for (i = 0; i < GetPartyBar.PartyMemberCount; ++i)
	{
		PMSG_PARTYLIST pList;
		memcpy(&pList, &aRecv[datasize], sizeof(pList));

		strncpy(GetPartyBar.JCPartyDB[i].Name, pList.szId, 10);
		GetPartyBar.JCPartyDB[i].Unknown10 = 0;
		GetPartyBar.JCPartyDB[i].Unknown11 = pList.Number;
		GetPartyBar.JCPartyDB[i].MapNumber = pList.MapNumber;
		GetPartyBar.JCPartyDB[i].PosX = pList.X;
		GetPartyBar.JCPartyDB[i].PosY = pList.Y;
		GetPartyBar.JCPartyDB[i].Life = pList.Life;
		GetPartyBar.JCPartyDB[i].MaxLife = pList.MaxLife;
		//--
		datasize += 24;
	}
	//sub_64E120((int)aRecv);
}

int PartyBar::PartyMemberLifeRecv(LPBYTE aRecv)
{
	int datasize = 0;
	char v2;
	char v3;
	signed int v4;
	char v5;
	PMSG_DEFAULT_COUNT pCount;
	memcpy(&pCount, &aRecv[datasize], sizeof(pCount));
	datasize = 4;
	int result = pCount.Count;

	for (int i = 0; i < result; ++i)
	{
		PMSG_PARTYLIFEALL pList;
		memcpy(&pList, &aRecv[datasize], sizeof(pList));

		v5 = pList.Number & 0xF;
		if (v5 >= 0)
			v4 = v5;
		else
			v4 = 0;
		if (v4 <= 10)
		{
			if (v5 >= 0)
				v2 = pList.Number & 0xF;
			else
				v2 = 0;
			v3 = v2;
		}
		else
		{
			v3 = 10;
		}

		GetPartyBar.JCPartyDB[i].LifePercent = v3;
		datasize++;
	}

	//sub_64E1F0((int)aRecv);
	return result;
}

DWORD PartyBar::SendPacked(const LPVOID dwEnterFunction, const LPVOID dwJMPAddress, const BYTE cmd)
{
	BYTE btBuf[5];
	// ----
	btBuf[0] = cmd;
	memcpy((LPVOID)& btBuf[1], (LPVOID)dwJMPAddress, sizeof(ULONG_PTR));
	// ----
	return WriteMemory(dwEnterFunction, (LPVOID)btBuf, sizeof(btBuf));
}

DWORD PartyBar::SendPacked(const LPVOID dwEnterFunction, const LPVOID dwJMPAddress, const BYTE cmd, const BYTE cmd2)
{
	BYTE btBuf[6];
	// ----
	btBuf[0] = cmd;
	btBuf[1] = cmd2;
	memcpy((LPVOID)& btBuf[2], (LPVOID)dwJMPAddress, sizeof(ULONG_PTR));
	// ----
	return WriteMemory(dwEnterFunction, (LPVOID)btBuf, sizeof(btBuf));
}

DWORD PartyBar::SendPacked(const LPVOID dwEnterFunction, const LPVOID dwJMPAddress, const BYTE cmd, const BYTE cmd2, const BYTE cmd3)
{
	BYTE btBuf[7];
	// ----
	btBuf[0] = cmd;
	btBuf[1] = cmd2;
	btBuf[2] = cmd3;
	memcpy((LPVOID)& btBuf[3], (LPVOID)dwJMPAddress, sizeof(ULONG_PTR));
	// ----
	return WriteMemory(dwEnterFunction, (LPVOID)btBuf, sizeof(btBuf));
}

int PartyBar::JCPartStructID()
{
	int v49; // [sp+74h] [bp-10h]@18
	signed int v20; // [sp-4h] [bp-88h]@21
	signed int v24; // [sp+10h] [bp-74h]@75
	signed int v27; // [sp+1Ch] [bp-68h]@33
	int v6; // esi@59

	for (int i = 0; i<this->PartyMemberCount; i++)
	{
		this->LifePercent[32 * i] = this->JCPartyDB[i].LifePercent;
		this->ViewportID[8 * i] = this->JCPartyDB[i].ViewportID;
		this->JCPartyDB[i].ViewportID = -2;
	}

	for (int i = 0; i < 400; ++i)
	{
		int v12 = pGetPreviewStruct(pPreviewThis(), i);
		if (*(DWORD *)(v12 + 824) == 1163 && *(BYTE *)(v12 + 800) == 1
			&& *(BYTE *)(v12 + 780) && *(BYTE *)(v12 + 788)
			&& *(float *)(v12 + 928) > 0.0 && !*(BYTE *)(v12 + 36))
		{
			for (int j = 0; j < this->PartyMemberCount; j++)
			{
				int v10 = (int)&this->JCPartyDB[j];
				if (this->JCPartyDB[j].ViewportID == -2 && this->JCPartyDB[j].ViewportID <= -1)
				{
					unsigned int v7 = sub_9CF130(v12 + 56) >= 1 ? sub_9CF130(v12 + 56) : 1;
					if (sub_9CF130(v10) <= v7)
					{
						int v5 = sub_9CF130(v12 + 56) >= 1 ? sub_9CF130(v12 + 56) : 1;
						v6 = v5;
					}
					else
					{
						v6 = sub_9CF130(v10);
					}
					lpViewObj lpUser = &*(ObjectPreview*)pGetPreviewStruct(pPreviewThis(), i);
					PartyUser* lpParty = &this->JCPartyDB[j];
					if (!this->FilterPartyNumberEx(lpParty, lpUser->Name, v6))
					{
						this->JCPartyDB[j].ViewportID = i;
						break;
					}
				}
			}
		}
		v49 = i + 1;
	}

	for (int k = 0; k < this->PartyMemberCount; k++)
		//for (int k = 0; k < gMiniMap.ListsCount; k++)
	{
		int v8 = (int)&this->JCPartyDB[k];
		if (this->JCPartyDB[k].ViewportID < 0)
		{
			if (sub_9CF130(LODWORD(oUserPreviewStruct) + 56) >= 1)
				v27 = sub_9CF130(LODWORD(oUserPreviewStruct) + 56);
			else
				v27 = 1;
			if (sub_9CF130(v8) <= (unsigned int)v27)
			{
				if (sub_9CF130(LODWORD(oUserPreviewStruct) + 56) >= 1)
					v20 = sub_9CF130(LODWORD(oUserPreviewStruct) + 56);
				else
					v20 = 1;
				v24 = v20;
			}
			else
			{
				v24 = sub_9CF130(v8);
			}

			PartyUser* JCPartStruct = &this->JCPartyDB[k];

			v49 = this->FilterPartyNumberEx(JCPartStruct, (char *)(*(DWORD *)0x7BC4F04 + 56), v24);
			if (v49)
				this->JCPartyDB[k].ViewportID = -1;
			else
				this->JCPartyDB[k].ViewportID = -3;
		}
	}

	return v49;
}

void DeletObjParty(int member)
{
	PlayBuffer(25, 0, 0);
	PMSG_PARTYDELUSER pRequest;
	pRequest.h.set(0x43, sizeof(pRequest));
	pRequest.Number = GetPartyBar.JCPartyDB[member].Unknown11;
	DataSend((LPBYTE)&pRequest, pRequest.h.size);
}

void PartyBar::GetCoordPanelD(int a1, float a2, float a3, float a4, float a5)
{
	float y; // ST10_4@1
	float x; // ST0C_4@1
	int v58; // [sp+20h] [bp-18h]@1
	char v59; // [sp+2Bh] [bp-Dh]@4

	v58 = *(DWORD *)(GetInstance() + 100);

	pDrawGUI(a1, a2, a3, a4, a5);

	y = (double)*(signed int *)(v58 + 20) + 123;
	x = (double)*(signed int *)(v58 + 16) - 10;

	pDrawGUI(0x7BAA, x + 70, y + 275, 16, 20);

	if (pCheckMouseOver(x + 70, y + 275, 16, 20))
	{
		pDrawColorButton(0x7BAA, x + 70, y + 275, 16, 20, 0, 0, pMakeColor(255, 204, 20, 130));

		if (*(BYTE*)0x8793386 && GetTickCount() >= GetPartyBar.OnClickD + 300)
		{
			GetPartyBar.Page = 0;
			GetPartyBar.OnClickD = GetTickCount();
		}
	}

	pDrawGUI(0x7BAB, x + 133, y + 275, 16, 20);

	if (pCheckMouseOver(x + 133, y + 275, 16, 20))
	{
		pDrawColorButton(0x7BAB, x + 133, y + 275, 16, 20, 0, 0, pMakeColor(255, 204, 20, 130));
		if (*(BYTE*)0x8793386 && GetTickCount() >= GetPartyBar.OnClickD + 300)
		{
			GetPartyBar.Page = (GetPartyBar.PartyMemberCount > 5) ? 1 : 0;
			GetPartyBar.OnClickD = GetTickCount();
		}
	}
}

void PartyBar::DrawPanelD()
{
	int v58; // [sp+20h] [bp-18h]@1
	char v59; // [sp+2Bh] [bp-Dh]@4

	v58 = *(DWORD *)(GetInstance() + 100);

	for (int i = 0; i < GetPartyBar.PartyMemberCount; i++)
	{
		if (i < 5 && GetPartyBar.Page == 0)
		{
			v59 = 0;
			if (!strcmp(GetPartyBar.JCPartyDB[0].Name, (char *)(*(DWORD *)0x7BC4F04 + 56))
				|| !strcmp(GetPartyBar.JCPartyDB[i].Name, (char *)(*(DWORD *)0x7BC4F04 + 56)))
			{
				v59 = 1;
			}

			sub_84AD10(v58, i, (int)&GetPartyBar.JCPartyDB[i], v59);

			if (pCheckMouseOver(*(DWORD *)(v58 + 16) + 159, *(DWORD *)(v58 + 20) + 71 * i + 63, 11, 11))
			{
				if (*(BYTE*)0x8793386 && GetTickCount() >= eventillo + 300)
				{
					eventillo = GetTickCount();
					DeletObjParty(i);
				}
			}
		}
		else if (i >= 5 && GetPartyBar.Page == 1)
		{
			v59 = 1;
			sub_84AD10(v58, i - 5, (int)&GetPartyBar.JCPartyDB[i], v59);

			if (pCheckMouseOver(*(DWORD *)(v58 + 16) + 159, *(DWORD *)(v58 + 20) + 71 * (i - 5) + 63, 11, 11))
			{
				if (*(BYTE*)0x8793386 && GetTickCount() >= eventillo + 300)
				{
					eventillo = GetTickCount();
					DeletObjParty(i);
				}
			}
		}
	}
}


int PartyBar::FilterPartyNumber(int a1, int a2, unsigned int a3)
{
	int result;
	int v4;
	int v5;
	char v6;
	char v7;
	char v8;
	char v9;
	int v10;
	int v11;
	unsigned int v12;

	char v13;
	char v14;
	char v15;
	char v16;
	char v17;

	v12 = 0;
	if (a3)
	{
		if (a3 < 9 || a3 == 9)
		{
			v4 = a2;
			v5 = a1;
			goto LABEL_24;
		}
		v4 = a2;
		v5 = a1;
		do
		{
			v13 = *(BYTE *)v5;
			v5 += 9;
			v4 += 9;
			//---
			int  mins = 9;
			if (!v13 || v13 != *(BYTE *)(v4 - mins))
			{
				v10 = *(BYTE *)(v5 - mins);
				v11 = *(BYTE *)(v4 - mins);
				goto LABEL_28;
			}
			v14 = *(BYTE *)(v5 - mins - 1);
			// ---
			mins = 8;
			if (!v14 || v14 != *(BYTE *)(v4 - mins))
			{
				v10 = *(BYTE *)(v5 - mins);
				v11 = *(BYTE *)(v4 - mins);
				goto LABEL_28;
			}
			v15 = *(BYTE *)(v5 - mins - 1);
			// ---
			mins = 7;
			if (!v15 || v15 != *(BYTE *)(v4 - mins))
			{
				v10 = *(BYTE *)(v5 - mins);
				v11 = *(BYTE *)(v4 - mins);
				goto LABEL_28;
			}
			v16 = *(BYTE *)(v5 - mins - 1);
			// ---
			mins = 6;
			if (!v16 || v16 != *(BYTE *)(v4 - mins))
			{
				v10 = *(BYTE *)(v5 - mins);
				v11 = *(BYTE *)(v4 - mins);
				goto LABEL_28;
			}
			v7 = *(BYTE *)(v5 - mins - 1);
			// ---
			mins = 5;
			if (!v13 || v13 != *(BYTE *)(v4 - mins))
			{
				v10 = *(BYTE *)(v5 - mins);
				v11 = *(BYTE *)(v4 - mins);
				goto LABEL_28;
			}
			v13 = *(BYTE *)(v5 - mins - 1);
			// ---
			if (!v6 || v6 != *(BYTE *)(v4 - 4))
			{
				v10 = *(BYTE *)(v5 - 4);
				v11 = *(BYTE *)(v4 - 4);
				goto LABEL_28;
			}
			v17 = *(BYTE *)(v5 - 3);
			if (!v17 || v17 != *(BYTE *)(v4 - 3))
			{
				v10 = *(BYTE *)(v5 - 3);
				v11 = *(BYTE *)(v4 - 3);
				goto LABEL_28;
			}
			v8 = *(BYTE *)(v5 - 2);
			if (!v8 || v8 != *(BYTE *)(v4 - 2))
			{
				v10 = *(BYTE *)(v5 - 2);
				v11 = *(BYTE *)(v4 - 2);
				goto LABEL_28;
			}
			v9 = *(BYTE *)(v5 - 1);
			if (!v9 || v9 != *(BYTE *)(v4 - 1))
			{
				v10 = *(BYTE *)(v5 - 1);
				v11 = *(BYTE *)(v4 - 1);
				goto LABEL_28;
			}
			v12 += 4;
		} while (v12 < a3 - 9);
		while (1)
		{
		LABEL_24:
			if (v12 >= a3)
				return 0;
			if (!*(BYTE *)v5 || *(BYTE *)v5 != *(BYTE *)v4)
				break;
			++v5;
			++v4;
			++v12;
		}
		v10 = *(BYTE *)v5;
		v11 = *(BYTE *)v4;
	LABEL_28:
		result = v10 - v11;
	}
	else
	{
		result = 0;
	}
	return result;
}

int PartyBar::FilterPartyNumberEx(PartyUser* lpUser, char* Name, unsigned int a3)
{
	if (!strcmp(lpUser->Name, Name))
	{
		return false;
	}

	return true;

}

int PartyBar::MainPartyVieweID()
{
	return GetPartyBar.JCPartStructID();
}

int PartyBar::JCGetViewID(unsigned __int8 This)
{
	int v49; // [sp+74h] [bp-10h]@18

	v49 = sub_5B7900(This);

	GetPartyBar.JCPartStructID();

	return v49;
}

void JCPartStructBar(float PosX, float PosY, float Width, float Height, float Arg5, int Arg6)
{
	char result; // al@2
	float x; // ST08_4@5
	float y; // ST04_4@5
	HGDIOBJ alpha; // ST18_4@3
	float lifecurrent; // ST64_4@25
	float manacurrent; // ST10_4@25
	int AddrPart; // [sp+54h] [bp-1Ch]@1
	int v44; // [sp+5Ch] [bp-14h]@7
	int Salto; // [sp+68h] [bp-8h]@5
	int i; // [sp+6Ch] [bp-4h]@3

	AddrPart = *(DWORD *)(GetInstance() + 104);

	pSetBlend(1);
	glColor4f(1.0, 1.0, 1.0, 1.0);
	alpha = pFontNormal;
	pSetFont(pTextThis(), (int)alpha);
	pSetTextColor(pTextThis(), 0xFFu, 0xFFu, 0xFFu, 0xFFu);
	pSetBackgroundTextColor(pTextThis(), 0, 0, 0, 0);
	*(DWORD *)(AddrPart + 920) = 32;

	for (i = 0; i < GetPartyBar.PartyMemberCount; ++i)
	{
		x = (double)(*(DWORD *)(AddrPart + 16) + *(DWORD *)(AddrPart + 24));
		y = (double)(*(DWORD *)(AddrPart + 28) + *(DWORD *)(AddrPart + 20));

		Salto = (30 + 2) * i;
		glColor4f(0.0, 0.0, 0.0, 0.89999998);

		pDrawBarForm(x + 2, (double)(y + Salto + 2), 74.0, 17.0, 0.0, 0);

		EnableAlphaTest(1);

		if (GetPartyBar.JCPartyDB[i].ViewportID == -1)
		{
			glColor4f(0.30000001, 0.0, 0.0, 0.5);
			pDrawBarForm(x + 2, y + Salto + 2, 74.0, 17.0, 0.0, 0);
			EnableAlphaTest(1);
		}
		else
		{
			v44 = pGetPreviewStruct(pPreviewThis(), GetPartyBar.JCPartyDB[i].ViewportID);

			if (v44 && pCheckEffectPlayer((DWORD *)(v44 + 1260), 2) == 1)
			{
				glColor4f(0.2, 1.0, 0.2, 0.2);
				pDrawBarForm(x + 2, y + Salto + 2, 74.0, 17.0, 0.0, 0);
				EnableAlphaTest(1);
			}
			if (*(DWORD *)(AddrPart + 924) != -1 && *(DWORD *)(AddrPart + 924) == i)
			{
				glColor4f(0.40000001, 0.40000001, 0.40000001, 0.69999999);
				pDrawBarForm(x + 2, y + Salto + 2, 74.0, 17.0, 0.0, 0);
				EnableAlphaTest(1);
			}
		}
		pGLSupremo();
		//-- Back
		//
		if (gProtect.m_MainInfo.CustomInterfaceType == 3 || gProtect.m_MainInfo.CustomInterfaceType == 4)
		{
			pDrawGUI(31557, x, (double)(y + Salto), 77.0, 30.0);
		}
		else{
			pDrawGUI(81525, x, (double)(y + Salto), 77.0, 30.0);
		}

		if (i)
		{
			if (GetPartyBar.JCPartyDB[i].ViewportID == -1)
				SetTextColorByHDC(pTextThis(), pMakeColor(0x80u, 0x80u, 0x80u, 0xFFu));
			else
				SetTextColorByHDC(pTextThis(), pMakeColor(0xFFu, 0xFFu, 0xFFu, 0xFFu));
			//--
			pDrawText(pTextThis(), x + 4, y + Salto + 4, GetPartyBar.JCPartyDB[i].Name, 77, 0, (PINT)1, 0);


		}
		else
		{
			if (GetPartyBar.JCPartyDB[i].ViewportID == -1)
				SetTextColorByHDC(pTextThis(), pMakeColor(0x80u, 0x4Bu, 0xBu, 0xFFu));
			else
				SetTextColorByHDC(pTextThis(), pMakeColor(0xFFu, 0x94u, 0x16u, 0xFFu));
			//-- Flag
			if (gProtect.m_MainInfo.CustomInterfaceType == 3 || gProtect.m_MainInfo.CustomInterfaceType == 4)
			{
				pDrawGUI(31553, (double)(x + 53), (double)(y + 3), 9.0, 10.0);
			}
			else
			{
				pDrawGUI(81521, (double)(x + 53), (double)(y + 3), 9.0, 10.0);
			}
			//--
			pDrawText(pTextThis(), x + 4, y + Salto + 4, GetPartyBar.JCPartyDB[i].Name, 77, 0, (PINT)1, 0);


		}


		//-- vida Concurrent
		if ((signed int)GetPartyBar.JCPartyDB[i].LifePercent <= 10)
			lifecurrent = GetPartyBar.JCPartyDB[i].LifePercent;
		else
			lifecurrent = 10;
		if (gProtect.m_MainInfo.CustomInterfaceType == 3 || gProtect.m_MainInfo.CustomInterfaceType == 4)
		{
			pDrawGUI(31558, x + 4, y + Salto + 16, (double)lifecurrent / 10.0 * 69.0, 3.0);
		}
		else
		{
			pDrawGUI(81522, x + 4, y + Salto + 16, (double)lifecurrent / 10.0 * 69.0, 3.0);
		}
		//


		if (!strcmp(GetPartyBar.JCPartyDB[0].Name, (char *)(*(DWORD *)0x7BC4F04 + 56))
			|| !strcmp(GetPartyBar.JCPartyDB[i].Name, (char *)(*(DWORD *)0x7BC4F04 + 56)))
		{
			if (pCheckMouseOver(x + 63, y + Salto + 3, 11, 11))
			{
				if (*(BYTE*)0x8793386)
				{
					if (gProtect.m_MainInfo.CustomInterfaceType == 3 || gProtect.m_MainInfo.CustomInterfaceType == 4)
					{
						pDrawButton(31554, x + 63, y + Salto + 3, 11.0, 11.0, 0.0, 11.0);
					}
					else{
						pDrawButton(81524, x + 63, y + Salto + 3, 11.0, 11.0, 0.0, 11.0);
					}


				}
				else
				{
					if (gProtect.m_MainInfo.CustomInterfaceType == 3 || gProtect.m_MainInfo.CustomInterfaceType == 4)
					{
						pDrawButton(31554, x + 63, y + Salto + 3, 11.0, 11.0, 0.0, 0.0);
					}
					else
					{
						pDrawButton(81524, x + 63, y + Salto + 3, 11.0, 11.0, 0.0, 0.0);
					}
					//


				}
			}
			else
			{
				if (gProtect.m_MainInfo.CustomInterfaceType == 3 || gProtect.m_MainInfo.CustomInterfaceType == 4)
				{
					pDrawButton(31554, x + 63, y + Salto + 3, 11.0, 11.0, 0.0, 0.0);
				}
				else
				{
					pDrawButton(81524, x + 63, y + Salto + 3, 11.0, 11.0, 0.0, 0.0);
				}
				//

			}
		}
		gPartyBuffs.DrawPartyBuffs((double)x, (double)y + Salto + 21.0, GetPartyBar.JCPartyDB[i].Name);
	}
	glEnable(0xDE1u);
	pGLSwitch();
}

char CheckStatusParty(int a1)
{
	char result; // al@2
	int v9; // [sp+0h] [bp-10h]@1
	int i; // [sp+4h] [bp-4h]@3

	v9 = *(DWORD *)(GetInstance() + 104);

	if (GetPartyBar.PartyMemberCount > 0)
	{
		*(BYTE *)(v9 + 917) = 1;
		for (i = 0; i < GetPartyBar.PartyMemberCount; ++i)
			GetPartyBar.JCPartyDB[i].ViewportID = -2;
		result = 1;
	}
	else
	{
		*(BYTE *)(v9 + 917) = 0;
		result = 1;
	}
	return result;
}
// 81CB504: using guessed type int dword_81CB504[];
// 81F6B6C: using guessed type int dword_81F6B6C;

DWORD VKBUTTON_DELAY2;
void Interface::BarPartyNew()
{
	if (gInterface.CheckWindow(ObjWindow::CashShop)
		|| gInterface.CheckWindow(ObjWindow::Party)
		|| gInterface.CheckWindow(ObjWindow::Quest)
		|| gInterface.CheckWindow(ObjWindow::NPC_Devin)
		|| gInterface.CheckWindow(ObjWindow::Guild)
		|| gInterface.CheckWindow(ObjWindow::Trade)
		|| gInterface.CheckWindow(ObjWindow::Warehouse)
		|| gInterface.CheckWindow(ObjWindow::ChaosBox)
		|| gInterface.CheckWindow(ObjWindow::CommandWindow)
		|| gInterface.CheckWindow(ObjWindow::PetInfo)
		|| gInterface.CheckWindow(ObjWindow::Shop)
		|| gInterface.CheckWindow(ObjWindow::Inventory)
		|| gInterface.CheckWindow(ObjWindow::Store)
		|| gInterface.CheckWindow(ObjWindow::OtherStore)
		|| gInterface.CheckWindow(ObjWindow::Character)
		|| gInterface.CheckWindow(ObjWindow::DevilSquare)
		|| gInterface.CheckWindow(ObjWindow::BloodCastle)
		|| gInterface.CheckWindow(ObjWindow::CreateGuild)
		|| gInterface.CheckWindow(ObjWindow::GuardNPC)
		|| gInterface.CheckWindow(ObjWindow::SeniorNPC)
		|| gInterface.CheckWindow(ObjWindow::GuardNPC2)
		|| gInterface.CheckWindow(ObjWindow::CastleGateSwitch)
		|| gInterface.CheckWindow(ObjWindow::CatapultNPC)
		|| gInterface.CheckWindow(ObjWindow::CrywolfGate)
		|| gInterface.CheckWindow(ObjWindow::IllusionTemple)
		|| gInterface.CheckWindow(ObjWindow::HeroList)
		|| gInterface.CheckWindow(ObjWindow::FastDial)
		|| gInterface.CheckWindow(ObjWindow::SkillTree)
		|| gInterface.CheckWindow(ObjWindow::GoldenArcher1)
		|| gInterface.CheckWindow(ObjWindow::GoldenArcher2)
		|| gInterface.CheckWindow(ObjWindow::LuckyCoin1)
		|| gInterface.CheckWindow(ObjWindow::LuckyCoin2)
		|| gInterface.CheckWindow(ObjWindow::NPC_Duel)
		|| gInterface.CheckWindow(ObjWindow::NPC_Titus)
		|| gInterface.CheckWindow(ObjWindow::CashShop)
		|| gInterface.CheckWindow(ObjWindow::Lugard)
		|| gInterface.CheckWindow(ObjWindow::QuestList1)
		|| gInterface.CheckWindow(ObjWindow::QuestList2)
		|| gInterface.CheckWindow(ObjWindow::Jerint)
		|| gInterface.CheckWindow(ObjWindow::FullMap)
		|| gInterface.CheckWindow(ObjWindow::NPC_Dialog)
		|| gInterface.CheckWindow(ObjWindow::GensInfo)
		|| gInterface.CheckWindow(ObjWindow::NPC_Julia)
		|| gInterface.CheckWindow(ObjWindow::NPC_ChaosMix)
		|| gInterface.CheckWindow(ObjWindow::ExpandInventory)
		|| gInterface.CheckWindow(ObjWindow::ExpandWarehouse)
		|| gInterface.CheckWindow(ObjWindow::MuHelper))
	{
		return;
	}

	if (gProtect.m_MainInfo.CustomInterfaceType == 3 || gProtect.m_MainInfo.CustomInterfaceType == 4)
	{
		int y = 13;
		int x = 560;

		RenderBitmap(81525, x + ReturnX(TransForX(1)), y + ReturnY(TransForY(-2)), ReturnX(TransForX(65)), ReturnY(TransForY(20)), 0.0, 0.0, 0.75, 0.1678999364, 1, 1, 0); //-- Barra
		//-- TitleName
		pSetFont(pTextThis(), (int)pFontBold);
		pSetBackgroundTextColor(pTextThis(), 0, 0, 0, 0);
		pSetTextColor(pTextThis(), 240, 240, 240, 255);
		pDrawText(pTextThis(), x + ReturnX(TransForX(30)), y + ReturnY(TransForY(1)), "Party", 148.0, 0, (LPINT)1, 0);

		if (pCheckMouseOver(x + ReturnX(TransForX(66)), y + ReturnY(TransForY(-2)), ReturnX(TransForX(14)), ReturnY(TransForY(14))))
		{
			if (pCursorX >= x + ReturnX(TransForX(66)))
			{
				pSetCursorFocus = true;
			}
		}
		if (MinimizarParty == 0)
		{
			if (CheckButtonPressed(x + ReturnX(TransForX(66)), y + ReturnY(TransForY(-2)), ReturnX(TransForX(14)), ReturnY(TransForY(14))))
			{
				RenderBitmap(61545, x + ReturnX(TransForX(66)), y + ReturnY(TransForY(-2)), ReturnX(TransForX(14)), ReturnY(TransForY(14)), 0.6000000238, 0.4131799936, 0.1090999693, 0.09779000282, 1, 1, 0); //-- Boton Minimizar
				if (GetTickCount() >= VKBUTTON_DELAY2 + 200)
				{
					MinimizarParty = 1;
					VKBUTTON_DELAY2 = GetTickCount();
				}
			}
			else
			{
				RenderBitmap(61545, x + ReturnX(TransForX(66)), y + ReturnY(TransForY(-2)), ReturnX(TransForX(14)), ReturnY(TransForY(14)), 0.4829999804, 0.4131799936, 0.1090999693, 0.09779000282, 1, 1, 0); //-- Boton Minimizar
			}
		}
		else
		{
			if (CheckButtonPressed(x + ReturnX(TransForX(66)), y + ReturnY(TransForY(-2)), ReturnX(TransForX(14)), ReturnY(TransForY(14))))
			{
				RenderBitmap(61545, x + ReturnX(TransForX(66)), y + ReturnY(TransForY(-2)), ReturnX(TransForX(14)), ReturnY(TransForY(14)), 0.1289999783, 0.4131799936, 0.1090999693, 0.09779000282, 1, 1, 0); //-- Boton Minimizar
				if (GetTickCount() >= VKBUTTON_DELAY2 + 200)
				{
					MinimizarParty = 0;
					VKBUTTON_DELAY2 = GetTickCount();
				}
			}
			else
			{
				RenderBitmap(61545, x + ReturnX(TransForX(66)), y + ReturnY(TransForY(-2)), ReturnX(TransForX(14)), ReturnY(TransForY(14)), 0.01299999934, 0.4131799936, 0.1090999693, 0.09779000282, 1, 1, 0); //-- Boton Minimizar
			}
		}
	}
	else if (gProtect.m_MainInfo.CustomInterfaceType == 0 || gProtect.m_MainInfo.CustomInterfaceType == 1 || gProtect.m_MainInfo.CustomInterfaceType == 2)
	{
		int y = 13;
		int x = 560;

		RenderBitmap(81525, x + ReturnX(TransForX(2)), y + ReturnY(TransForY(-12)), ReturnX(TransForX(64)), ReturnY(TransForY(20)), 0.0, 0.0, 0.75, 0.1678999364, 1, 1, 0); //-- Barra
		//-- TitleName
		pSetFont(pTextThis(), (int)pFontBold);
		pSetBackgroundTextColor(pTextThis(), 0, 0, 0, 0);
		pSetTextColor(pTextThis(), 240, 240, 240, 255);
		pDrawText(pTextThis(), x + ReturnX(TransForX(30)), y + ReturnY(TransForY(-9)), "Party", 148.0, 0, (LPINT)1, 0);

		if (pCheckMouseOver(x + ReturnX(TransForX(66)), y + ReturnY(TransForY(-12)), ReturnX(TransForX(14)), ReturnY(TransForY(14))))
		{
			if (pCursorX >= x + ReturnX(TransForX(66)))
			{
				pSetCursorFocus = true;
			}
		}
		if (MinimizarParty == 0)
		{
			if (CheckButtonPressed(x + ReturnX(TransForX(66)), y + ReturnY(TransForY(-12)), ReturnX(TransForX(14)), ReturnY(TransForY(14))))
			{
				RenderBitmap(61545, x + ReturnX(TransForX(66)), y + ReturnY(TransForY(-12)), ReturnX(TransForX(14)), ReturnY(TransForY(14)), 0.6000000238, 0.4131799936, 0.1090999693, 0.09779000282, 1, 1, 0); //-- Boton Minimizar
				if (GetTickCount() >= VKBUTTON_DELAY2 + 200)
				{
					MinimizarParty = 1;
					VKBUTTON_DELAY2 = GetTickCount();
				}
			}
			else
			{
				RenderBitmap(61545, x + ReturnX(TransForX(66)), y + ReturnY(TransForY(-12)), ReturnX(TransForX(14)), ReturnY(TransForY(14)), 0.4829999804, 0.4131799936, 0.1090999693, 0.09779000282, 1, 1, 0); //-- Boton Minimizar
			}
		}
		else
		{
			if (CheckButtonPressed(x + ReturnX(TransForX(66)), y + ReturnY(TransForY(-12)), ReturnX(TransForX(14)), ReturnY(TransForY(14))))
			{
				RenderBitmap(61545, x + ReturnX(TransForX(66)), y + ReturnY(TransForY(-12)), ReturnX(TransForX(14)), ReturnY(TransForY(14)), 0.1289999783, 0.4131799936, 0.1090999693, 0.09779000282, 1, 1, 0); //-- Boton Minimizar
				if (GetTickCount() >= VKBUTTON_DELAY2 + 200)
				{
					MinimizarParty = 0;
					VKBUTTON_DELAY2 = GetTickCount();
				}
			}
			else
			{
				RenderBitmap(61545, x + ReturnX(TransForX(66)), y + ReturnY(TransForY(-12)), ReturnX(TransForX(14)), ReturnY(TransForY(14)), 0.01299999934, 0.4131799936, 0.1090999693, 0.09779000282, 1, 1, 0); //-- Boton Minimizar
			}
		}
	}
}

char PrintfPartyBar(int a1)
{
	char result; // al@2
	float y; // ST08_4@5
	float x; // ST04_4@5
	signed int v13; // ST18_4@7
	float v39; // ST64_4@25
	signed int v42; // [sp+20h] [bp-50h]@23
	int v43; // [sp+54h] [bp-1Ch]@1
	int v44; // [sp+5Ch] [bp-14h]@7
	int v45; // [sp+68h] [bp-8h]@5
	int i; // [sp+6Ch] [bp-4h]@3

	v43 = *(DWORD *)(GetInstance() + 104);

	if (gProtect.m_MainInfo.CustomInterfaceType == 0 || gProtect.m_MainInfo.CustomInterfaceType == 1 || gProtect.m_MainInfo.CustomInterfaceType == 2 || gProtect.m_MainInfo.CustomInterfaceType == 3 || gProtect.m_MainInfo.CustomInterfaceType == 4)
	{
		if (*(BYTE *)(v43 + 917))
		{
			gInterface.BarPartyNew();
		}
	}

	if (MinimizarParty == 0)
	{
		if (*(BYTE *)(v43 + 917))
		{
			EnableAlphaTest(1);
			glColor4f(1.0, 1.0, 1.0, 1.0);

			sub_420120(pTextThis(), (int)pFontNormal);
			pSetTextColor(pTextThis(), 0xFFu, 0xFFu, 0xFFu, 0xFFu);
			pSetBackgroundTextColor(pTextThis(), 0, 0, 0, 0);

			for (i = 0; i < GetPartyBar.PartyMemberCount; ++i)
			{
				v45 = (30 + 2) * i;//*(DWORD *)(v43 + 920) * i;

				v13 = GetPartyBar.JCPartyDB[i].ViewportID;

				y = (double)(*(DWORD *)(v43 + 28) + *(DWORD *)(v43 + 20) + v45);
				x = (double)(*(DWORD *)(v43 + 16) + *(DWORD *)(v43 + 24));

				glColor4f(0.0, 0.0, 0.0, 0.89999998);
				pDrawBarForm(x + 2, y + 2, 74.0, 17.0, 0.0, 0);

				EnableAlphaTest(1);
				if (GetPartyBar.JCPartyDB[i].ViewportID == -1)
				{
					glColor4f(0.30000001, 0.0, 0.0, 0.5);
					pDrawBarForm(x, y, 74.0, 17.0, 0.0, 0);
					EnableAlphaTest(1);
				}
				else
				{

					v44 = pGetPreviewStruct(pPreviewThis(), v13);
					if (v44 && pCheckEffectPlayer((DWORD *)(v44 + 1260), 2) == 1)
					{
						glColor4f(0.2, 1.0, 0.2, 0.2);
						pDrawBarForm(x + 2, y + 2, 74.0, 17.0, 0.0, 0);
						EnableAlphaTest(1);
					}
					if (*(DWORD *)(v43 + 924) != -1 && *(DWORD *)(v43 + 924) == i)
					{
						glColor4f(0.40000001, 0.40000001, 0.40000001, 0.69999999);
						pDrawBarForm(x + 2, y + 2, 74.0, 17.0, 0.0, 0);
						EnableAlphaTest(1);
					}
				}
				pGLSupremo();

				pDrawGUI(31557, x, y, 77.0, 23.0);

				if (i)
				{
					if (v13 == -1)
					{
						sub_420080(pTextThis(), pMakeColor(0x80u, 0x80u, 0x80u, 0xFFu));
					}
					else
					{
						sub_420080(pTextThis(), pMakeColor(0xFFu, 0xFFu, 0xFFu, 0xFFu));
					}


					pDrawText(pTextThis(), (int)x + 4, (int)y + 4, GetPartyBar.JCPartyDB[i].Name, *(DWORD *)(v43 + 932), 0, (LPINT)1, 0);
				}
				else
				{
					if (GetPartyBar.JCPartyDB[0].ViewportID == -1)
					{
						sub_420080(pTextThis(), pMakeColor(0x80u, 0x4Bu, 0xBu, 0xFFu));
					}
					else
					{
						sub_420080(pTextThis(), pMakeColor(0xFFu, 0x94u, 0x16u, 0xFFu));
					}
					pDrawGUI(31553, x + 53, y + 3, 9.0, 10.0);

					pDrawText(pTextThis(), (int)x + 4, (int)y + 4, GetPartyBar.JCPartyDB[0].Name, *(DWORD *)(v43 + 932), 0, (LPINT)1, 0);
				}

				if ((signed int)(unsigned __int8)GetPartyBar.JCPartyDB[i].LifePercent <= 10)
					v42 = (unsigned __int8)GetPartyBar.JCPartyDB[i].LifePercent;
				else
					v42 = 10;
				v39 = (double)v42 / 10.0 * 69.0;

				pDrawGUI(31558, x + 4, y + 16, v39, 3.0);

				if (!strcmp(GetPartyBar.JCPartyDB[0].Name, (char *)(*(DWORD *)0x7BC4F04 + 56))
					|| !strcmp(GetPartyBar.JCPartyDB[i].Name, (char *)(*(DWORD *)0x7BC4F04 + 56)))
				{
					if (pCheckMouseOver(x + 63, y + 3, 11, 11) && *(BYTE*)0x8793386)
					{
						pDrawButton(31554, x + 63, y + 3, 11.0, 11.0, 0.0, 11.0);
					}
					else
					{
						pDrawButton(31554, x + 63, y + 3, 11.0, 11.0, 0.0, 0.0);
					}
				}

				gPartyBuffs.DrawPartyBuffs((double)x, (double)y + 21.0, GetPartyBar.JCPartyDB[i].Name);
			}
			pGLSwitch();
			result = 1;
		}
		else
		{
			result = 1;
		}
	}
	return result;
}
// 7BC4F04: using guessed type int dword_7BC4F04;
// 81CB504: using guessed type int dword_81CB504[];
// 81F6B6C: using guessed type int dword_81F6B6C;

void ObjPartyDelect(int member)
{
	//if ( !sub_4DB1F0( ) )
	//{
	PlayBuffer(25, 0, 0);
	PMSG_PARTYDELUSER pRequest;
	pRequest.h.set(0x43, sizeof(pRequest));
	pRequest.Number = GetPartyBar.JCPartyDB[member].Unknown11;
	DataSend((LPBYTE)&pRequest, pRequest.h.size);
	GetPartyBar.Page = 0;
	//}
}

//----- (0084BB30) --------------------------------------------------------
char sub_84BB30(int a1)
{
	void *v4; // eax@6
	int v5; // eax@6
	int v9; // [sp+0h] [bp-10h]@1
	int v10; // [sp+4h] [bp-Ch]@9
	int v11; // [sp+8h] [bp-8h]@3
	int i; // [sp+Ch] [bp-4h]@1

	v9 = a1;

	*(DWORD *)(a1 + 924) = -1;

	for (i = 0; i < GetPartyBar.PartyMemberCount; ++i)
	{
		v11 = (30 + 2) * i;//*(DWORD *)(v9 + 920) * i;
		if (!strcmp(GetPartyBar.JCPartyDB[0].Name, (char *)(*(DWORD *)0x7BC4F04 + 56))
			|| !strcmp(GetPartyBar.JCPartyDB[i].Name, (char *)(*(DWORD *)0x7BC4F04 + 56)))
		{
			if (pCheckMouseOver(*(DWORD *)(v9 + 24) + *(DWORD *)(v9 + 16) + 63,
				v11 + *(DWORD *)(v9 + 28) + *(DWORD *)(v9 + 20) + 3,
				11, 11) && *(BYTE*)0x8793386)
			{
				ObjPartyDelect(i);
				return 1;
			}
		}
		if (pCheckMouseOver(
			*(DWORD *)(v9 + 24) + *(DWORD *)(v9 + 16),
			v11 + *(DWORD *)(v9 + 28) + *(DWORD *)(v9 + 20),
			77,
			23))
		{
			*(DWORD *)(v9 + 924) = i;
			if (*(DWORD *)0xE61730 == -1)
			{
				v10 = pGetPreviewStruct(pPreviewThis(), GetPartyBar.JCPartyDB[i].ViewportID);
				if (v10)
				{
					if (v10 != dword_7BC4F04)
						sub_5996A0(v10 + 56, (const CHAR *)&*(LPVOID*)0xD47C9C, v10, 0, -1);
				}
			}
			if (sub_84C8B0((int)&GetPartyBar.JCPartyDB[i]))
				return 1;
		}
	}
	return 0;
}
// E61730: using guessed type int dword_E61730;
// 7BC4F04: using guessed type int dword_7BC4F04;
// 81CB504: using guessed type int dword_81CB504[];
// 81F6B6C: using guessed type int dword_81F6B6C;

//----- (0084BCB0) --------------------------------------------------------
bool GetTargetMember(int a1)
{
	bool result; // al@2
	int v5; // [sp+0h] [bp-8h]@1

	v5 = *(DWORD *)(GetInstance() + 104);

	if (*(BYTE *)(v5 + 917))
	{
		if (sub_84BB30(v5) == 1)
		{
			result = 0;
		}
		else
		{
			result = GetPartyBar.PartyMemberCount <= 0 || !pCheckMouseOver(
				*(DWORD *)(v5 + 24) + *(DWORD *)(v5 + 16),
				*(DWORD *)(v5 + 28) + *(DWORD *)(v5 + 20),
				77, 30 * GetPartyBar.PartyMemberCount);
		}
	}
	else
	{
		result = 1;
	}
	return result;
}
// 81F6B6C: using guessed type int dword_81F6B6C;

void DeleteButton(int v58, int num, int lpObj)
{
	if (pCheckMouseOver(*(DWORD *)(v58 + 16) + 159, *(DWORD *)(v58 + 20) + 71 * num + 63, 11, 11)
		&& *(BYTE*)0x8793386)
	{
		pDrawButton(31554, *(DWORD *)(v58 + 16) + 159, *(DWORD *)(v58 + 20) + 71 * num + 63, 11.0, 11.0, 0.0, 11.0);
		ObjPartyDelect(lpObj);
		return;
	}
	else
	{
		pDrawButton(31554, *(DWORD *)(v58 + 16) + 159, *(DWORD *)(v58 + 20) + 71 * num + 63, 11.0, 11.0, 0.0, 0.0);
	}
}
//----- (0084A4A0) --------------------------------------------------------
void sub_84A4A0()
{
	int v58; // [sp+20h] [bp-18h]@1
	int num; // [sp+8h] [bp-4h]@1
	int i; // [sp+30h] [bp-8h]@2

	v58 = *(DWORD*)(GetInstance() + 100);

	for (i = 0; i < GetPartyBar.PartyMemberCount; i++)
	{
		if (i < 5 && GetPartyBar.Page == 0)
		{
			num = i;
			sub_84AD10(v58, num, (int)&GetPartyBar.JCPartyDB[num], 0);

			if (!strcmp(GetPartyBar.JCPartyDB[0].Name, (char *)(*(DWORD *)0x7BC4F04 + 56))
				|| !strcmp(GetPartyBar.JCPartyDB[i].Name, (char *)(*(DWORD *)0x7BC4F04 + 56)))
			{
				DeleteButton(v58, num, i);
			}
		}
		else if (i > 4 && GetPartyBar.Page == 1)
		{
			num = i - 5;
			sub_84AD10(v58, num, (int)&GetPartyBar.JCPartyDB[i], 0);

			if (!strcmp(GetPartyBar.JCPartyDB[0].Name, (char *)(*(DWORD *)0x7BC4F04 + 56))
				|| !strcmp(GetPartyBar.JCPartyDB[i].Name, (char *)(*(DWORD *)0x7BC4F04 + 56)))
			{
				DeleteButton(v58, num, i);
			}
		}
	}
}
// 7BC4F04: using guessed type int dword_7BC4F04;
// 81F6B6C: using guessed type int dword_81F6B6C;

__declspec(naked) void PartyWindows()
{
	static DWORD Addr_JMP = 0x0084A90A;

	sub_84A4A0();

	_asm
	{
		JMP[Addr_JMP]
	}
}

void GetButtonMembers()
{
	float y; // ST10_4@1
	float x; // ST0C_4@1
	int v58; // [sp+20h] [bp-18h]@1
	char v59; // [sp+2Bh] [bp-Dh]@4

	v58 = *(DWORD *)(GetInstance() + 100);
	if (*(BYTE *)(v58 + 1060))
	{
		y = (double)*(signed int *)(v58 + 20) + 123;
		x = (double)*(signed int *)(v58 + 16) - 10;

		pDrawGUI(0x7BAA, x + 70, y + 275, 16, 20);

		if (pCheckMouseOver(x + 70, y + 275, 16, 20))
		{
			pDrawColorButton(0x7BAA, x + 70, y + 275, 16, 20, 0, 0, pMakeColor(255, 204, 20, 130));

			if (*(BYTE*)0x8793386 && GetTickCount() >= GetPartyBar.OnClickD + 300)
			{
				GetPartyBar.Page = 0;
				GetPartyBar.OnClickD = GetTickCount();
			}
		}
		pDrawGUI(0x7BAB, x + 133, y + 275, 16, 20);

		if (pCheckMouseOver(x + 133, y + 275, 16, 20))
		{
			pDrawColorButton(0x7BAB, x + 133, y + 275, 16, 20, 0, 0, pMakeColor(255, 204, 20, 130));
			if (*(BYTE*)0x8793386 && GetTickCount() >= GetPartyBar.OnClickD + 300)
			{
				GetPartyBar.Page = (GetPartyBar.PartyMemberCount > 5) ? 1 : 0;
				GetPartyBar.OnClickD = GetTickCount();
			}
		}
	}
	pGLSwitch();
}

void PartyBar::Load()
{
	SetCompleteHook(0xE8, 0x0084A91A, &GetButtonMembers);
	SetCompleteHook(0xE9, 0x0084A6D7, &PartyWindows);
	//--
	SetCompleteHook(0xE9, 0x0084BCB0, &GetTargetMember);
	SetCompleteHook(0xE9, 0x0084BDB0, &PrintfPartyBar);
	SetCompleteHook(0xE9, 0x0084BD50, &CheckStatusParty);
	//--
	SetCompleteHook(0xE8, 0x00664568, this->JCGCPartyListAll);
	SetOp((LPVOID)0x0066458A, this->PartyMemberLifeRecv, ASM::CALL);
	//--
	DWORD PartyMemberDB = (DWORD)&this->JCPartyDB;
	SendPacked((LPVOID)0x0051C629, &PartyMemberDB, 0x81, 0xC2);
	SendPacked((LPVOID)0x0078F28A, &PartyMemberDB, 0x68);
	//--
	DWORD AddressLifePercent = (DWORD)&this->LifePercent;
	SendPacked((LPVOID)0x0095FED9, &AddressLifePercent, 0x0F, 0xB6, 0x89); //-- Check Healing Elf
	//--
	DWORD AddressViewportID = (DWORD)&this->ViewportID;
	SendPacked((LPVOID)0x0095FF91, &AddressViewportID, 0x8B, 0x91); //-- Skill Healing Elf
	//--
	DWORD AddressPartyMemberCount = (DWORD)&this->PartyMemberCount;
	SendPacked((LPVOID)0x0095E6B7, &AddressPartyMemberCount, 0x83, 0x3D); //-- Skill Healing Elf
	SendPacked((LPVOID)0x0095E70D, &AddressPartyMemberCount, 0x83, 0x05); //-- Skill Healing Elf
	SendPacked((LPVOID)0x0095FE98, &AddressPartyMemberCount, 0x3B, 0x05); //-- Skill Healing Elf
	SendPacked((LPVOID)0x0095FF7F, &AddressPartyMemberCount, 0x3B, 0x05); //-- Skill Healing Elf
	//--
	SendPacked((LPVOID)0x0051C61B, &AddressPartyMemberCount, 0x3B, 0x0D); //--
	SendPacked((LPVOID)0x0064E2CC, &AddressPartyMemberCount, 0xC7, 0x05); //--
	SendPacked((LPVOID)0x005C60CB, &AddressPartyMemberCount, 0x83, 0x3D); //Skill DL Summon
	SendPacked((LPVOID)0x00814033, &AddressPartyMemberCount, 0x83, 0x3D); //Skill DL Summon 
	SendPacked((LPVOID)0x005AD1B2, &AddressPartyMemberCount, 0x83, 0x3D); //Skill DL Summon
	SendPacked((LPVOID)0x0078F274, &AddressPartyMemberCount, 0x83, 0x3D); //--
	SendPacked((LPVOID)0x0084BA51, &AddressPartyMemberCount, 0x0F, 0xAF, 0x0D);
	SendPacked((LPVOID)0x0084A47B, &AddressPartyMemberCount, 0x83, 0x3D);
	//--
	SetCompleteHook(0xE8, 0x005B8395, this->JCGetViewID); //-- partybar
	SetCompleteHook(0xE8, 0x005B83AD, this->JCGetViewID); //-- partybar
	SetCompleteHook(0xE8, 0x005B83C5, this->JCGetViewID); //-- partybar
	SetCompleteHook(0xE8, 0x005B84EB, this->JCGetViewID); //-- partybar
	SetCompleteHook(0xE8, 0x005B8506, this->JCGetViewID); //-- partybar
	SetCompleteHook(0xE8, 0x005B851E, this->JCGetViewID); //-- partybar
	//--
	SetCompleteHook(0xE8, 0x005B83EE, this->MainPartyVieweID); //-- partybar
	SetCompleteHook(0xE8, 0x005B84D3, this->MainPartyVieweID); //-- partybar
	SetCompleteHook(0xE8, 0x005B856C, this->MainPartyVieweID); //-- partybar
	SetCompleteHook(0xE8, 0x005B857A, this->MainPartyVieweID); //-- partybar
}