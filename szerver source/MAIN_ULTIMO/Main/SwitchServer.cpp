#include "stdafx.h"
#if(IN_DEV == 1)
#include "Protocol.h"
#include "SwitchServer.h"
#include "WindowsStruct.h"
#include "CMacroUIEx.h"

cSwitchServer SwitchServer;

cSwitchServer::cSwitchServer()
{
}

cSwitchServer::~cSwitchServer()
{
}


void cSwitchServer::switchServer(WORD subcode){
	ECCG_SWITCHSERVER_REQ pMsg;
	pMsg.header.set(0xBF, 0xFF, sizeof(pMsg));
	pMsg.subcode = subcode;
	DataSend((BYTE*)&pMsg, pMsg.header.size);
}
#endif