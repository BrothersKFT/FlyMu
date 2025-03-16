#include "stdafx.h"
#include "Ruud.h"
#include "Import.h"
#include "Object.h"
#include "ItemInfoEx.h"
#include "Offset.h"
#include "Util.h"
#include "WindowsStruct.h"
#include "postInterface.h"
#include "Protocol.h"
#include "Central.h"
#include "Defines.h"
#include "InfoLog.h"

cRenderRuud jCRenderRuud;



cRenderRuud::cRenderRuud()
{
	this->JCMoveX = 1.0;
	this->JCMoveY = 0.0;
	this->OpeningRuud = false;
	this->OpenWindowConfirm = false;
	this->JCSlot = -1;
	this->JCPage = -1;
	this->Page = 1;
	this->ClearRuudInfo();
}

cRenderRuud::~cRenderRuud()
{
}

bool cRenderRuud::isOpen()
{
	return this->OpeningRuud;
}

void cRenderRuud::MoverWinRuud(int x, int y)
{
	if (x < 0 || y < 0 || y + 430 > 480)
	{
		return;
	}

	this->JCMoveX = x;
	this->JCMoveY = y;
}

bool cRenderRuud::CheckMouseOver()
{
	if (pCheckMouseOver(this->JCMoveX, this->JCMoveY, 190, 430) && this->OpeningRuud || this->OpenWindowConfirm)
	{
		return true;
	}

	return false;
}

bool cRenderRuud::EventPressButton(int x, int y, int h, int w)
{
	if (pCheckMouseOver(x, y, w, h))
	{
		if (CursorPress)
		{
			if (GetTickCount() >= this->TimerEvent + 200)
			{
				this->TimerEvent = GetTickCount();
				return true;
			}
		}
	}
	return false;
}

void cRenderRuud::ClosedRuud()
{
	PMSG_NPC_TALK_SEND pMsg;
	pMsg.header.set(0x31, sizeof(pMsg));
	DataSend((BYTE*)&pMsg, sizeof(pMsg));
	this->JCSlot = -1;
	this->JCPage = -1;
	this->OpenWindowConfirm = false;

	if (pCheckWindow(pWindowThis(), 13))
	{
		pCloseWindow(pWindowThis(), 13);
	}
}

void cRenderRuud::InsertRuudInfo(PMSG_RUUD_ITEM_LIST * lpInfo)
{
	this->m_RuudInfo[Enter].slot = lpInfo->slot;

	this->m_RuudInfo[Enter].dwRuudSell = lpInfo->dwRuudSell;

	memcpy(this->m_RuudInfo[Enter].ItemInfo, lpInfo->ItemInfo, sizeof(lpInfo->ItemInfo));
}

void cRenderRuud::ClearRuudInfo()
{
	for (int i = 0; i < MAX_RUUDTOKENSELL_INFO; i++)
	{
		this->m_RuudInfo[i].slot = -1;

		for (int k = 0; k < 12; k++)
		{
			this->m_RuudInfo[Enter].ItemInfo[k] = -1;
		}

		//this->m_RuudInfo[i].dwRuudSell = -1;
	}
	this->Page = 1;
	this->Enter = 0;
}

void cRenderRuud::LoadRuudShop_Recv(PMSG_RUUD_ITEM_LIST_RECV * lpMsg)
{
	this->ClearRuudInfo();

	for (int n = 0; n < lpMsg->count; n++)
	{
		PMSG_RUUD_ITEM_LIST * lpInfo = (PMSG_RUUD_ITEM_LIST*)(((BYTE*)lpMsg) + sizeof(PMSG_RUUD_ITEM_LIST_RECV) + (sizeof(PMSG_RUUD_ITEM_LIST) * n));

		this->InsertRuudInfo(lpInfo);

		this->Enter++;
	}
}

PMSG_RUUD_ITEM_LIST * cRenderRuud::JCGetInfoRuud(int Page, int Slot)
{
	int nSlot = (((Page - 1) * 5) + Slot - 1);

	if (this->m_RuudInfo[nSlot].slot != -1)
	{
		return &this->m_RuudInfo[nSlot];
	}
	return 0;
}

void cRenderRuud::CheckOpen()
{
//	if (this->OpeningRuud)
//	{
//		if (!pCheckWindow(pWindowThis(), 13))
//		{
//			this->OpeningRuud = false;
//			this->ClosedRuud();
//		}

//		if (this->OpeningRuud &&
//			(this->Coordenada[1] != pGetUserCoorX
//			|| this->Coordenada[2] != pGetUserCoorY
//			|| this->Coordenada[0] != pMapNumber))
//		{
//			this->OpeningRuud = false;
//			this->ClosedRuud();
//		}
//	}
//	else
//	{
//		this->Coordenada[0] = pMapNumber;
//		this->Coordenada[1] = pGetUserCoorX;
//		this->Coordenada[2] = pGetUserCoorY;
//	}
}

void cRenderRuud::OpenRuudShop_Recv(PMSG_NPC_TALK_RECV * lpMsg)
{
	if (lpMsg->result == 100)
	{
		this->OpeningRuud = true;

		if (!pCheckWindow(pWindowThis(), 13))
		{
			pOpenWindow(pWindowThis(), 13);
		}
	}
}


int TimerPush;
int cerrar = 0;

void cRenderRuud::WindowConfirm(int Page, int Slot)
{
	float JCWindowX; // ST08_4@1
	float JCWindowY; // ST04_4@1
	int JCLoadItem; // [sp+8Ch] [bp-ACh]@14
	int JCItemStruct; // [sp+5Ch] [bp-Ch]@3
	float v9; // [sp+48h] [bp-20h]@3
	float v10; // [sp+4Ch] [bp-1Ch]@3
	float v12; // [sp+54h] [bp-14h]@3
	float v13; // [sp+58h] [bp-10h]@3
	int JCResto = pWinWidth / pWinHeightReal / 2 - 320;

	if (this->OpenWindowConfirm && Page != -1 && Slot != -1)
	{
		JCWindowX = 205.0f + JCResto;
		JCWindowY = 100.0f;

		gCentral.PrintDropBox(JCWindowX, JCWindowY, 230, 150, 0, 0);

		PMSG_RUUD_ITEM_LIST * JCLoadInfo = this->JCGetInfoRuud(Page, Slot);

		JCLoadItem = JCConvertByteItem(*(DWORD *)(GetInstance() + 36), JCLoadInfo->ItemInfo);

		JCItemStruct = sub_4E10D0(*(WORD *)JCLoadItem);

		v9 = (double)(20 * *(BYTE *)(JCItemStruct + 38));
		v10 = (double)(20 * *(BYTE *)(JCItemStruct + 39));

		v12 = (double)((JCWindowX + 115) - v9 / 2);
		v13 = (double)((JCWindowY + 20) - v10 / 2);

		gPostInterface.DrawItemIMG(
			v12,
			v13,
			v9,
			v10,
			*(WORD *)JCLoadItem,
			*(DWORD *)(JCLoadItem + 2),
			*(BYTE *)(JCLoadItem + 23),
			*(BYTE *)(JCLoadItem + 24),
			0);

		pSetFont(pTextThis(), (int)pFontBold);
		pSetTextColor(pTextThis(), 0xFFu, 0xFFu, 0xFFu, 0xFFu);
		pDrawText(pTextThis(), JCWindowX, 175, "Mastery", 230, 0, (LPINT)3, 0);

		pDrawText(pTextThis(), JCWindowX, 190, (const char*)pGetItemAtt(*(WORD *)JCLoadItem, 0), 230, 0, (LPINT)3, 0);
		//-- 0.4359999299 push
		if (pCheckMouseOver((int)JCWindowX + 35, (int)JCWindowY + 119, 43, 17))
		{
			if (*(BYTE*)0x8793386 && cerrar == 0)
			{
				RenderBitmap(71521, (int)JCWindowX + 35, (int)JCWindowY + 119, 43, 17, 0.0013, 0.4359999299, 0.8805001974, 0.3845001459, 1, 1, 0.0);
				if (GetTickCount() >= TimerPush + 300)
				{
					this->JCSlot = -1;
					this->JCPage = -1;

					PMSG_BUY_ITEMRUUD_SEND pMsg;
					pMsg.header.set(0xAD, sizeof(pMsg));
					pMsg.PAGE = Page;
					pMsg.SLOT = Slot;
					DataSend((BYTE*)&pMsg, pMsg.header.size);
					cerrar = 1;
					TimerPush = GetTickCount();
				}
			}
			else
			{
				RenderBitmap(71521, (int)JCWindowX + 35, (int)JCWindowY + 119, 43, 17, 0.0013, 0.013, 0.8805001974, 0.3845001459, 1, 1, 0.0);
			}
		}
		else
		{
			RenderBitmap(71521, (int)JCWindowX + 35, (int)JCWindowY + 119, 43, 17, 0.0013, 0.013, 0.8805001974, 0.3845001459, 1, 1, 0.0);
		}

		if (pCheckMouseOver((int)JCWindowX + 151, (int)JCWindowY + 119, 43, 17))
		{

			if (*(BYTE*)0x8793386 && cerrar == 0)
			{
				RenderBitmap(71521, (int)JCWindowX + 151, (int)JCWindowY + 119, 43, 17, 0.0013, 0.4359999299, 0.8805001974, 0.3845001459, 1, 1, 0.0);
				if (GetTickCount() >= TimerPush + 300)
				{
					this->JCSlot = -1;
					this->JCPage = -1;
					cerrar = 1;
					TimerPush = GetTickCount();
				}
			}
			else
			{
				RenderBitmap(71521, (int)JCWindowX + 151, (int)JCWindowY + 119, 43, 17, 0.0013, 0.013, 0.8805001974, 0.3845001459, 1, 1, 0.0);
			}
		}
		else
		{
			RenderBitmap(71521, (int)JCWindowX + 151, (int)JCWindowY + 119, 43, 17, 0.0013, 0.013, 0.8805001974, 0.3845001459, 1, 1, 0.0);
		}
		//RenderBitmap(71521, 445, 270, TransForX( 43 ), TransForY( 17 ), 0.0013, 0.013, 0.8805001974, 0.3845001459, 0, 0, 0);
		pDrawText(pTextThis(), (int)JCWindowX + 35, (int)JCWindowY + 122, pGetTextLine(pTextLineThis, 228), 43, 0, (LPINT)3, 0);
		pDrawText(pTextThis(), (int)JCWindowX + 151, (int)JCWindowY + 122, pGetTextLine(pTextLineThis, 229), 43, 0, (LPINT)3, 0);
	}

	if (cerrar == 1 && !*(BYTE*)0x8793386)
	{
		cerrar = 0;
		this->OpenWindowConfirm = false;
	}
}

void JCRuudShopText(int x, int y, int Width)
{
	float v16; // ST34_4@1
	unsigned __int8 v17; // ST18_1@1
	unsigned __int8 v22; // ST18_1@1
	float v35; // [sp+338h] [bp-4h]@1

	v16 = *(float*)0x5EF5A1C * 0.001000000047497451;
	v35 = Convert(v16) + 1.0;
	v17 = (signed int)((2.0 - v35) * 127.0);

	pSetFont(pTextThis(), (int)pFontBold);
	//-- TitleName 1
	pSetTextColor(pTextThis(), 0xFFu, 0xBDu, 0x19u, v17);
	pDrawText(pTextThis(), x, y + 29, "NPC Ruud", Width, 0, (LPINT)3, 0);
	//-- TitleName 2
	v22 = (signed int)(v35 * 127.0);
	pSetTextColor(pTextThis(), 0xFFu, 0xBDu, 0x19u, v22);
	pDrawText(pTextThis(), x, y + 29, "Priest James", Width, 0, (LPINT)3, 0);

	pSetFont(pTextThis(), (int)pFontNormal);
	pSetTextColor(pTextThis(), 0xFFu, 0xFFu, 0xFFu, 0xFFu);
	pDrawText(pTextThis(), x + 15, y + 58, "You can use Ruud to purchase Selaed Mastery", 166, 0, (LPINT)1, 0);
	pDrawText(pTextThis(), x + 15, y + 68, "Set Items.", 166, 0, (LPINT)1, 0);
	pDrawText(pTextThis(), x + 15, y + 78, "You can unseal Sealed Sets by combining", 166, 0, (LPINT)1, 0);
	pDrawText(pTextThis(), x + 15, y + 88, "Ancient Hero's souls via Chaos Goblin.", 166, 0, (LPINT)1, 0);
}

void cRenderRuud::OpenRuud()
{
	if (this->OpeningRuud == false)
	{
		return;
	}

	float JCWindowX; // ST08_4@1
	float JCWindowY; // ST04_4@1
	float Width; // ST08_4@1
	float Heigth; // ST08_4@1
	int JCLoadItem; // [sp+8Ch] [bp-ACh]@14
	int JCItemStruct; // [sp+5Ch] [bp-Ch]@3

	//--
	
	float RuudH = 55.0f;
	char Precio[50];

	Width = 190.0f;
	Heigth = 429.0f;

	JCWindowX = (double)this->JCMoveX;
	JCWindowY = (double)this->JCMoveY;

	float RuudY = JCWindowY + 109.5f;

	RenderBitmap(61560, JCWindowX, JCWindowY, Width, Heigth, 0.0, 0.0, 0.6319999695, 0.6218001246, 1, 1, 0.0);

	JCRuudShopText((int)JCWindowX, (int)JCWindowY, (int)Width);

	for (int i = 0; i < 5; i++)
	{
		PMSG_RUUD_ITEM_LIST * JCLoadInfo = this->JCGetInfoRuud(this->Page, i + 1);

		if (JCLoadInfo)
		{
			RenderBitmap(61561, JCWindowX + 10, RuudY + 1.0f + (RuudH * i), 166, RuudH, 0.0, 0.0, 0.5450001955, 0.6800000072, 1, 1, 0.0);

			JCLoadItem = JCConvertByteItem(*(DWORD *)(GetInstance() + 36), JCLoadInfo->ItemInfo);

			pSetFont(pTextThis(), (int)pFontNormal);

			//-- evento comprar
			if (CheckButtonPressed((int)JCWindowX + 135, RuudY + 5.0f + (RuudH * i), 38, 17) && !this->OpenWindowConfirm)
			{
				RenderBitmap(61542, (int)JCWindowX + 135, RuudY + 5.0f + (RuudH * i), 38, 17, 0.0, 0.268338412, 0.7135385275, 0.2283384204, 1, 1, 0);
				this->OpenWindowConfirm = true;
				this->JCSlot = i + 1;
				this->JCPage = this->Page;
			}
			else
			{
				RenderBitmap(61542, (int)JCWindowX + 135, RuudY + 5.0f + (RuudH * i), 38, 17, 0.0, 0.02, 0.7135385275, 0.2283384204, 1, 1, 0);
			}

			//-- Titulo del Item
			//pSetTextColor(pTextThis(), 0xE6u, 0xE6u, 0, 0xFFu);
			//pDrawText(pTextThis(), x + 65, RuudY + 8.0f + ( RuudH * i ), "Mastery", 70, 0, (LPINT)3, 0);
			//-- Titulo del Item
			pSetTextColor(pTextThis(), 0xE6u, 0xE6u, 0, 0xFFu);
			pDrawText(pTextThis(), (int)JCWindowX + Return2X(TransForX(65)), RuudY + 8.0f + (RuudH * i), "Mastery", Return2X(TransForX(70)), 0, (LPINT)3, 0);
			//-- Nombre del Item
			pSetTextColor(pTextThis(), 0xFFu, 0xFFu, 0xFFu, 0xFFu);
			pDrawText(pTextThis(), (int)JCWindowX + 68, RuudY + 28 + (RuudH * i), (const char*)pGetItemAtt(*(WORD *)JCLoadItem, 0), 105, 0, (LPINT)1, 0);
			//-- Precio del Item
			pGetMoneyFormat(JCLoadInfo->dwRuudSell, Precio, 0);
			pDrawText(pTextThis(), (int)JCWindowX + 90, RuudY + 43 + (RuudH * i), Precio, 100, 0, (LPINT)3, 0);
			//-- Buy
			pSetTextColor(pTextThis(), 0xFFu, 0xBDu, 0x19u, 0xFFu);
			pDrawText(pTextThis(), (int)JCWindowX + 135, RuudY + 8.0f + (RuudH * i), pGetTextLine(pTextLineThis, 1124), 38, 0, (LPINT)3, 0);
		}
	}

	this->WindowConfirm(this->JCPage, this->JCSlot);

	//-- Imprime Item
	float v9; // [sp+48h] [bp-20h]@3
	float v10; // [sp+4Ch] [bp-1Ch]@3
	float v12; // [sp+54h] [bp-14h]@3
	float v13; // [sp+58h] [bp-10h]@3

	for (int i = 0; i < 5; i++)
	{
		PMSG_RUUD_ITEM_LIST * JCLoadInfo = this->JCGetInfoRuud(this->Page, i + 1);

		if (JCLoadInfo)
		{
			JCLoadItem = JCConvertByteItem(*(DWORD *)(GetInstance() + 36), JCLoadInfo->ItemInfo);

			JCItemStruct = sub_4E10D0(*(WORD *)JCLoadItem);

			v9 = (double)(20 * *(BYTE *)(JCItemStruct + 38));
			v10 = (double)(20 * *(BYTE *)(JCItemStruct + 39));

			v12 = (double)((JCWindowX + 13) + 25 - v9 / 2);
			v13 = (double)(RuudY + 1.0f + (RuudH * i) + 5 - v10 / 2);

		//	gPostInterface.DrawItemIMG(x + Return2X(TransForX(10)), 84 + 0.5f + (RuudH * i), Return2X(TransForX(50)), 50, ItemID, 0, 0, 0, 0);

			gPostInterface.DrawItemIMG(v12,v13,v9,v10,*(WORD *)JCLoadItem,*(DWORD *)(JCLoadItem + 2),*(BYTE *)(JCLoadItem + 23),*(BYTE *)(JCLoadItem + 24),0);

			if (pCheckMouseOver((int)(JCWindowX + 13), (int)(RuudY + 1.0f + (RuudH * i)), 50, 50))
			{
				JCCoord B;
				B.X = (int)JCWindowX + 10;
				B.Y = (int)84 + 0.5f + (RuudH * i);

				sub_7E3E30(*(DWORD *)(GetInstance() + 308), B, JCLoadItem, 0, 0, 0);

				pSetBlend(false);
			}
		}
	}

	//-- Solo 1 lista 0.4549999833
	if (EventPressButton((int)(JCWindowX + 65), (int)JCWindowY + 400, 10, 10) && !this->OpenWindowConfirm)
	{
		if (this->Page > 1) { this->Page--; }
		RenderBitmap(61562, (int)JCWindowX + 65, (int)JCWindowY + 400, 10, 10, 0.02999999747, (this->Page == 1) ? 0.4549999833 : 0.3069999814, 0.2610003054, 0.1405000836, 0, 0, 0);
	}
	else
	{
		RenderBitmap(61562, (int)JCWindowX + 65, (int)JCWindowY + 400, 10, 10, 0.02999999747, (this->Page == 1) ? 0.4549999833 : 0.00800000038, 0.2610003054, 0.1405000836, 1, 1, 0.0);
	}

	if (EventPressButton((int)JCWindowX + 115, (int)JCWindowY + 400, 10, 10) && !this->OpenWindowConfirm)
	{
		if (this->Page < 5) { this->Page++; }
		RenderBitmap(61562, (int)JCWindowX + 115, (int)JCWindowY + 400, 10, 10, 0.319999963, (this->Page == 5) ? 0.4549999833 : 0.3069999814, 0.2610003054, 0.1405000836, 1, 1, 0.0);
	}
	else
	{
		RenderBitmap(61562, (int)JCWindowX + 115, (int)JCWindowY + 400, 10, 10, 0.319999963, (this->Page == 5) ? 0.4549999833 : 0.00800000038, 0.2610003054, 0.1405000836, 1, 1, 0.0);
	}
	char nPage[10];
	ZeroMemory(nPage, sizeof(nPage));
	wsprintf(nPage, pGetTextLine(pTextLineThis, 1181), this->Page, 5);

	pSetTextColor(pTextThis(), 0xFFu, 0xBDu, 0x19u, 0xFFu);
//	pSetFont(pTextThis(), (int)pFontNormal);

	pDrawText(pTextThis(), (int)JCWindowX + 85, (int)JCWindowY + 400, nPage, 20, 0, (LPINT)3, 0);
}