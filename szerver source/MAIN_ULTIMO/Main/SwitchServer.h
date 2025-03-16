#pragma once
#if(IN_DEV == 1)
struct ECCG_SWITCHSERVER_REQ{
	PSBMSG_HEAD header; // C1:29:06
	WORD subcode;
};

class cSwitchServer
{
public:
	cSwitchServer();
	~cSwitchServer();
	void switchServer(WORD subcode);

};extern cSwitchServer SwitchServer;
#endif