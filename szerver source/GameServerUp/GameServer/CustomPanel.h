#pragma once

#include "Protocol.h"

struct PANEL_MENU
{
#pragma pack(1)
	PSBMSG_HEAD h;
	int Menu;
	int PanelButtons[7];
	int Panel2Buttons[4];
#pragma pack()
};

class CPanelMenu
{
public:
	void Load(char* path);
	void EnvioPanelMenu(int aIndex);
	int Menu;
	int PanelButtons[7];
	int Panel2Buttons[4];
};

extern CPanelMenu gPanelMenu;