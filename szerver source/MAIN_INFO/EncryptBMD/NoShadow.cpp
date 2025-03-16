#include "stdafx.h"
#include "NoShadow.h"
#include "MemScript.h"
#include "InfoLog.h"

cNoShadow gNoShadow;

cNoShadow::cNoShadow() // OK
{
	this->Init();
}

cNoShadow::~cNoShadow() // OK
{

}

void cNoShadow::Init() // OK
{
	for (int n = 0; n < MAX_NO_SHADOW; n++)
	{
		this->m_NoShadowInfo[n].Index = -1;
	}
}

void cNoShadow::Load(char* path) // OK
{
	CMemScript* lpMemScript = new CMemScript;

	if (lpMemScript == 0)
	{
		printf(MEM_SCRIPT_ALLOC_ERROR, path);
		return;
	}

	if (lpMemScript->SetBuffer(path) == 0)
	{
		printf(lpMemScript->GetLastError());
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

			if (strcmp("end", lpMemScript->GetString()) == 0)
			{
				break;
			}

			ITEM_NO_SHADOW_INFO info;

			memset(&info, 0, sizeof(info));

			static int CustomItemIndexCount = 0;

			info.Index = CustomItemIndexCount++;

			info.ItemType = lpMemScript->GetNumber();

			info.ItemIndex = lpMemScript->GetAsNumber();

			this->SetInfo(info);
		}
	}
	catch (...)
	{
		printf(lpMemScript->GetLastError());
	}

	delete lpMemScript;
}

void cNoShadow::SetInfo(ITEM_NO_SHADOW_INFO info) // OK
{
	if (info.Index < 0 || info.Index >= MAX_NO_SHADOW)
	{
		return;
	}

	this->m_NoShadowInfo[info.Index] = info;
}