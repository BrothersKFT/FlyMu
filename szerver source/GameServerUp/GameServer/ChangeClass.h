// CustomItem.h: interface for the CCustomItem class.
//
//////////////////////////////////////////////////////////////////////

#pragma once
#if (CHANGECLASS==1)
#include "Protocol.h"

struct CHANGE_REQ
{
	PSBMSG_HEAD h;
	int	numclass;
};


class CChangeClass
{
public:
	CChangeClass();
	virtual ~CChangeClass();
	void SelectClass(int aIndex, CHANGE_REQ* lpMsg);
};

extern CChangeClass gChangeClass;

#endif