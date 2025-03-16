#include "stdafx.h"
#include "CustomPanel.h"
#include "ReadScript2.h"
#include "user.h"
#include "Protect.h"
#include "Message.h"
#include "DSProtocol.h"
#include "Notice.h"
#include "Util.h"


CPanelMenu gPanelMenu;



void CPanelMenu::Load(char * File)
{
#if (PROTECT_STATE ==1)
	SMDToken Token;
	SMDFile = fopen(File, "r");
	// ----
	if (!SMDFile)
	{
		MessageBox(NULL, "file not found", "[PanelMenu]", ERROR);
		return;
	}
	// ----
	while (true)
	{
		Token = GetToken();
		int Category;
		// ----
		if (Token == END)
		{
			break;
		}
		// ----
		Category = TokenNumber;
		// ----
		while (true)
		{
			if (Category == 0)
			{
				Token = GetToken();
				// ----
				if (strcmp("end", TokenString) == 0)
				{
					break;
				}
				// ----
				this->Menu = TokenNumber;
			}
			else if (Category == 1)
			{
				Token = GetToken();
				// ----
				if (strcmp("end", TokenString) == 0)
				{
					break;
				}
				// ----
				this->PanelButtons[0] = TokenNumber;
				Token = GetToken();
				this->PanelButtons[1] = TokenNumber;
				Token = GetToken();
				this->PanelButtons[2] = TokenNumber;
				Token = GetToken();
				this->PanelButtons[3] = TokenNumber;
				Token = GetToken();
				this->PanelButtons[4] = TokenNumber;
				Token = GetToken();
				this->PanelButtons[5] = TokenNumber;
				Token = GetToken();
				this->PanelButtons[6] = TokenNumber;
			}
			else if (Category == 2)
			{
				Token = GetToken();
				// ----
				if (strcmp("end", TokenString) == 0)
				{
					break;
				}
				// ----
				this->Panel2Buttons[0] = TokenNumber;
				Token = GetToken();
				this->Panel2Buttons[1] = TokenNumber;
				Token = GetToken();
				this->Panel2Buttons[2] = TokenNumber;
				Token = GetToken();
				this->Panel2Buttons[3] = TokenNumber;
			}
		}
	}
	// ----
	fclose(SMDFile);
	// ----
#endif
}

void CPanelMenu::EnvioPanelMenu(int aIndex)
{

	if (gObjIsConnected(aIndex) == false)
	{
		return;
	}
	// ---
	LPOBJ lpObj = &gObj[aIndex];
	// ---
	PANEL_MENU pMsg = { 0 };
	// ---
	pMsg.h.set(0xFB, 0xE8, sizeof(pMsg));
	// ---
	pMsg.Menu = this->Menu;
	pMsg.PanelButtons[0] = PanelButtons[0];
	pMsg.PanelButtons[1] = PanelButtons[1];
	pMsg.PanelButtons[2] = PanelButtons[2];
	pMsg.PanelButtons[3] = PanelButtons[3];
	pMsg.PanelButtons[4] = PanelButtons[4];
	pMsg.PanelButtons[5] = PanelButtons[5];
	pMsg.PanelButtons[6] = PanelButtons[6];
	// ---
	pMsg.Panel2Buttons[0] = Panel2Buttons[0];
	pMsg.Panel2Buttons[1] = Panel2Buttons[1];
	pMsg.Panel2Buttons[2] = Panel2Buttons[2];
	pMsg.Panel2Buttons[3] = Panel2Buttons[3];
	// ---
	DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
}