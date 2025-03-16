#pragma once
//--/TAP FULLMAP
//----- (00790DF0) --------------------------------------------------------
//----- (00638130) --------------------------------------------------------
#include "Object.h"

class CMinimap
{
public:
	CMinimap();
	virtual ~CMinimap();
	void initClassic();
	void initRadar();
	void MiniMapload();
	char MapRender(int a1);
public:
	LoadTypeMap DataMap;
}; extern CMinimap gRenderMap;