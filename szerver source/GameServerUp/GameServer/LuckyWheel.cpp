// CustomPet.cpp: implementation of the CLuckyWheel class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#if (LUCKYWHEEL == 1)
#include "LuckyWheel.h"
#include "MemScript.h"
#include "ReadScript2.h"
#include "DSProtocol.h"
#include "Util.h"
#include "ItemManager.h"
#include "CashShop.h"
#include "User.h"
#include "Notice.h"
#include "Message.h"
#include "ServerInfo.h"

#define LUCKYWHEEL_COOLDOWN 30000 // 30 másodperc (ms)

CLuckyWheel gLuckyWheel;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLuckyWheel::CLuckyWheel() // OK
{
	this->Init();
}

CLuckyWheel::~CLuckyWheel() // OK
{

}

void CLuckyWheel::Init() // OK
{
	for(int n=0;n < MAX_LUCKYWHEEL_ITEM;n++)
	{
		this->m_LuckyWheelInfo[n].Index = -1;
	}
}


void CLuckyWheel::Load(char* path) // OK
{

	CMemScript* lpMemScript = new CMemScript;

	if (lpMemScript == 0)
	{
		ErrorMessageBox(MEM_SCRIPT_ALLOC_ERROR, path);
		return;
	}

	if (lpMemScript->SetBuffer(path) == 0)
	{
		ErrorMessageBox(lpMemScript->GetLastError());
		delete lpMemScript;
		return;
	}

	this->Init();

	try
	{
		while (true)
		{
			if (lpMemScript->GetToken() == TOKEN_END)
			{
				break;
			}

			int section = lpMemScript->GetNumber();

			while (true)
			{
				if (section == 0)
				{
					if (strcmp("end", lpMemScript->GetAsString()) == 0)
					{
						break;
					}


					this->WcoinLucky = lpMemScript->GetNumber();

					this->WcoinPLucky = lpMemScript->GetAsNumber();

					this->goblinCoinLucky = lpMemScript->GetAsNumber();
				}
				else if (section == 1)
				{
					if (strcmp("end", lpMemScript->GetAsString()) == 0)
					{
						break;
					}

					LUCKYWHEEL_INFO info;

					memset(&info, 0, sizeof(info));

					info.Index = lpMemScript->GetNumber();

					info.ItemType = lpMemScript->GetAsNumber();

					info.ItemIndex = lpMemScript->GetAsNumber();

					info.Level = lpMemScript->GetAsNumber();

					info.Skill = lpMemScript->GetAsNumber();

					info.Luck = lpMemScript->GetAsNumber();

					info.Option = lpMemScript->GetAsNumber();

					info.Exc = lpMemScript->GetAsNumber();

					this->SetInfo(info);
				}
				else
				{
					break;
				}
			}
		}
	}
	catch (...)
	{
		ErrorMessageBox(lpMemScript->GetLastError());
	}

	delete lpMemScript;
}

void CLuckyWheel::SetInfo(LUCKYWHEEL_INFO info) // OK
{
	if(info.Index < 0 || info.Index >= MAX_LUCKYWHEEL_ITEM)
	{
		return;
	}

	this->m_LuckyWheelInfo[info.Index] = info;
}

void CLuckyWheel::Start(LPOBJ lpUser)
{
	DWORD currentTime = GetTickCount(); // Aktuális idő

	// Ellenőrizzük, hogy eltelt-e elég idő az utolsó pörgetés óta
	if (lpUser->LastLuckyWheelRollTime != 0 && (currentTime - lpUser->LastLuckyWheelRollTime) < LUCKYWHEEL_COOLDOWN)
	{
		// Még nem telt le a cooldown
		DWORD remainingTimeMs = LUCKYWHEEL_COOLDOWN - (currentTime - lpUser->LastLuckyWheelRollTime);
		int remainingSeconds = (remainingTimeMs / 1000) + 1; // Másodpercre kerekítve felfelé

		// Üzenet küldése a játékosnak (dinamikusan)
		char szMsg[128];
		wsprintf(szMsg, "You must wait %d seconds to roll again.", remainingSeconds);
		gNotice.GCNoticeSend(lpUser->Index, 1, 0, 0, 0, 0, 0, szMsg);

		return; // Kilépünk a függvényből, nem engedjük pörgetni
	}

	if (WcoinLucky > 0)
	{
		if (lpUser->Coin1 < WcoinLucky)
		{
			gNotice.GCNoticeSend(lpUser->Index, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(540), WcoinLucky);
			return;
		}
	}

	if (WcoinPLucky > 0)
	{
		if (lpUser->Coin2 < WcoinPLucky)
		{
			gNotice.GCNoticeSend(lpUser->Index, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(541), WcoinPLucky);
			return;
		}
	}

	if (goblinCoinLucky > 0)
	{
		if (lpUser->Coin2 < goblinCoinLucky)
		{
			gNotice.GCNoticeSend(lpUser->Index, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(542), goblinCoinLucky);
			return;
		}
	}

	GDSetCoinSend(lpUser->Index, -(WcoinLucky), -(WcoinPLucky), -(goblinCoinLucky), 0, "LuckyWheel");

	Sleep(3000);
	srand(time((NULL)));
	int number = rand() % 12;
	GDCreateItemSend(lpUser->Index,0xEB,0,0,GET_ITEM(m_LuckyWheelInfo[number].ItemType,m_LuckyWheelInfo[number].ItemIndex),m_LuckyWheelInfo[number].Level,0,m_LuckyWheelInfo[number].Skill,m_LuckyWheelInfo[number].Luck,m_LuckyWheelInfo[number].Option,-1,m_LuckyWheelInfo[number].Exc,0,0,0,0,0xFF,0);
	gNotice.GCNoticeSend(lpUser->Index, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(543));
	
	lpUser->LastLuckyWheelRollTime = currentTime; // Elmentjük az aktuális időt, mint az utolsó pörgetés idejét

	ITEM_WIN_SEND pMsg;
	pMsg.header.set(0xFB,0x23,sizeof(pMsg));
	pMsg.number = number;
	DataSend(lpUser->Index,(BYTE*)&pMsg,pMsg.header.size);
}

void CLuckyWheel::EnvioCostoWheel(int aIndex)
{

	if (gObjIsConnected(aIndex) == false)
	{
		return;
	}
	// ---
	LPOBJ lpObj = &gObj[aIndex];
	// ---
	PMSG_LUCKY_WHEEL pMsg = { 0 };
	// ---
	pMsg.h.set(0xFB, 0xE7, sizeof(pMsg));
	// ---
	pMsg.CostWcoinC = this->WcoinLucky;
	pMsg.CostWcoinP = this->WcoinPLucky;
	pMsg.CostGoblin = this->goblinCoinLucky;
	// ---
	DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
}

#endif