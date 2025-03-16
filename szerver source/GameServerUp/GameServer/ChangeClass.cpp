// CustomItem.cpp: implementation of the CCustomItem class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#if (CHANGECLASS==1)
#include "CashShop.h"
#include "ChangeClass.h"
#include "DSProtocol.h"
#include "JSProtocol.h"
#include "Util.h"
#include "MemScript.h"
#include "ReadScript2.h"
#include "Message.h"
#include "Notice.h"
#include "Util.h"
#include "ObjectManager.h"
#include "Map.h"
#include "CommandManager.h"
#include "ServerInfo.h"

CChangeClass gChangeClass;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CChangeClass::CChangeClass() // OK
{
}

CChangeClass::~CChangeClass() // OK
{

}

void CChangeClass::SelectClass(int aIndex, CHANGE_REQ* lpMsg)
{
#if (GAMESERVER_CLIENTE_UPDATE >= 9)
	LPOBJ lpObj = &gObj[aIndex];

	if (gObjIsConnectedGP(aIndex) == 0)
	{
		return;
	}

	if (lpMsg->numclass < 0 || lpMsg->numclass > 7)
	{
		return;
	}

	switch (lpMsg->numclass)
	{
	case 0:
		gCommandManager.CommandChangeClass(lpObj, "dw", -1);
		break;
	case 1:
		gCommandManager.CommandChangeClass(lpObj, "dk", -1);
		break;
	case 2:
		gCommandManager.CommandChangeClass(lpObj, "elf", -1);
		break;
	case 3:
		gCommandManager.CommandChangeClass(lpObj, "mg", -1);
		break;
	case 4:
		gCommandManager.CommandChangeClass(lpObj, "dl", -1);
		break;
	case 5:
		gCommandManager.CommandChangeClass(lpObj, "su", -1);
		break;
	case 6:
		gCommandManager.CommandChangeClass(lpObj, "rf", -1);
		break;
	}

#endif
}

#endif