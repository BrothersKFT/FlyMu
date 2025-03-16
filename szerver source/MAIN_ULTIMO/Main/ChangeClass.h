#pragma once
// -------------------------------------------------------------------------------

#include "Protocol.h"
#include "Interface.h"
// -------------------------------------------------------------------------------

struct CHANGE_REQ
{
	PSBMSG_HEAD h;
	int	numclass;
};
// -------------------------------------------------------------------------------
class CChangeClass
{
public:
	CChangeClass();
	~CChangeClass();
	// ----
	void		DrawChangeWindow();
	bool		EventChangeWindow_Close(DWORD Event);
	bool        EventChange_SelectAll(DWORD Event);
	bool		EventChangeWindow_DW(DWORD Event);
	bool		EventChangeWindow_DK(DWORD Event);
	bool		EventChangeWindow_EL(DWORD Event);
	bool		EventChangeWindow_MG(DWORD Event);
	bool		EventChangeWindow_DL(DWORD Event);
	bool		EventChangeWindow_SU(DWORD Event);
	bool		EventChangeWindow_RF(DWORD Event);

	void OpenChangeWindow() { gInterface.Data[eCHANGE_MAIN].OnShow = true; };
	void CloseChangeWindow() { gInterface.Data[eCHANGE_MAIN].OnShow = false; };
	// ----
	void SelectClass(int numclass);
	int ChangeButtons[7];
public:
	// ----
}; extern CChangeClass gChangeClass;
// -------------------------------------------------------------------------------