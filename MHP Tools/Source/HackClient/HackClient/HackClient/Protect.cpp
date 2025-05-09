// Protect.cpp: implementation of the CProtect class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Protect.h"
#include "CCRC32.H"
#include "Log.h"
#include "Util.h"

CProtect gProtect;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CProtect::CProtect() // OK
{

}

CProtect::~CProtect() // OK
{

}

void SaveFile()
{
	HANDLE file = CreateFile("lol.txt",GENERIC_WRITE,FILE_SHARE_READ,0,CREATE_ALWAYS,FILE_ATTRIBUTE_ARCHIVE,0);

	if(file == INVALID_HANDLE_VALUE)
	{
		MessageBox(0,"Error create file 0",0,0);
		return;
	}

	DWORD OutSize = 0;

	if(WriteFile(file,&gProtect.m_MainInfo,sizeof(MAIN_FILE_INFO),&OutSize,0) == 0)
	{
		MessageBox(0,"Error create file",0,0);
		CloseHandle(file);
		return;
	}

	CloseHandle(file);
}

bool Is64bitWindows()
{
    auto is_64_bit = true;
    if(FALSE == GetSystemWow64DirectoryW(nullptr, 0u))
    {
        auto const last_error = ::GetLastError();
        if(ERROR_CALL_NOT_IMPLEMENTED == last_error)
        {
            is_64_bit = false;
        }
    }
    return(is_64_bit);
}

bool CProtect::ReadMainFile(char* name) // OK
{
	CCRC32 CRC32;

	if(CRC32.FileCRC(name,(DWORD*)&this->m_ClientFileCRC,1024) == 0)
	{
		//MessageBox(0,"ERR1",0,0);
		return 0;
	}

	HANDLE file = CreateFile(name,GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,FILE_ATTRIBUTE_ARCHIVE,0);

	if(file == INVALID_HANDLE_VALUE)
	{
		//MessageBox(0,"ERR2",0,0);
		return 0;
	}

	if(GetFileSize(file,0) != sizeof(MAIN_FILE_INFO))
	{
		//MessageBox(0,"ERR3",0,0);
		CloseHandle(file);
		return 0;
	}

	DWORD OutSize = 0;

	if(ReadFile(file,&this->m_MainInfo,sizeof(MAIN_FILE_INFO),&OutSize,0) == 0)
	{
		//MessageBox(0,"ERR4",0,0);
		CloseHandle(file);
		return 0;
	}

	for(int n=0;n < sizeof(MAIN_FILE_INFO);n++)
	{
		((BYTE*)&this->m_MainInfo)[n] += 0x78;
		((BYTE*)&this->m_MainInfo)[n] ^= 0xB3;
	}

	//SaveFile();

	gMessage.GetLanguage();

	gMessage.LoadEng(this->m_MainInfo.EngMessageInfo);

	gMessage.LoadPor(this->m_MainInfo.PorMessageInfo);

	gMessage.LoadSpn(this->m_MainInfo.SpnMessageInfo);

	CloseHandle(file);

	this->is_x64 = false;
	this->x64_library = nullptr;

	

	//if (Is64bitWindows())
	//{
	//	//MessageBox(0,"dada","dada",0);		
	//	this->is_x64 = true;

	//	this->x64_library = LoadLibrary("MHPx64.dll");
	//	/*if (this->x64_library == nullptr)
	//	{
	//		gLog.Output(LOG_DEBUG,"Can't load x64 library");
	//		SafeExitProcess();
	//	}*/
	//}
	
	
	return 1;
}

void CProtect::CheckClientFile() // OK
{
	if(this->m_MainInfo.ClientCRC32 == 0)
	{
		return;
	}

	char name[MAX_PATH] = {0};

	if(GetModuleFileName(0,name,sizeof(name)) == 0)
	{
		gLog.Output(LOG_DEBUG,GetEncryptedString(33));
		SafeExitProcess();
	}

	if(_stricmp(ConvertModuleFileName(name),this->m_MainInfo.ClientName) != 0)
	{
		gLog.Output(LOG_DEBUG,GetEncryptedString(34));
		SafeExitProcess();
	}

	CCRC32 CRC32;

	DWORD ClientCRC32;

	if(CRC32.FileCRC(this->m_MainInfo.ClientName,&ClientCRC32,1024) == 0)
	{
		gLog.Output(LOG_DEBUG,GetEncryptedString(35));
		SafeExitProcess();
	}

	if(this->m_MainInfo.ClientCRC32 != ClientCRC32)
	{
		gLog.Output(LOG_DEBUG,GetEncryptedString(36));
		SafeExitProcess();
	}
}

void CProtect::CheckPluginFile() // OK
{
	if(this->m_MainInfo.PluginCRC32 == 0)
	{
		return;
	}

	CCRC32 CRC32;

	DWORD PluginCRC32;

	if(CRC32.FileCRC(this->m_MainInfo.PluginName,&PluginCRC32,1024) == 0)
	{
		gLog.Output(LOG_DEBUG,GetEncryptedString(37));
		SafeExitProcess();
	}

	if(this->m_MainInfo.PluginCRC32 != PluginCRC32)
	{
		gLog.Output(LOG_DEBUG,GetEncryptedString(38));
		SafeExitProcess();
	}

	HMODULE module = LoadLibrary(this->m_MainInfo.PluginName);

	if(module == 0)
	{
		gLog.Output(LOG_DEBUG,GetEncryptedString(39));
		SafeExitProcess();
	}

	void (*EntryProc)() = (void(*)())GetProcAddress(module,"EntryProc");

	if(EntryProc != 0){EntryProc();}
}

void CProtect::CheckVerifyFile() // OK
{
	if(this->m_MainInfo.VerifyCRC32 == 0)
	{
		return;
	}

	CCRC32 CRC32;

	DWORD VerifyCRC32;

	if(CRC32.FileCRC(this->m_MainInfo.VerifyName,&VerifyCRC32,1024) == 0)
	{
		gLog.Output(LOG_DEBUG,GetEncryptedString(40));
		SafeExitProcess();
	}

	if(this->m_MainInfo.VerifyCRC32 != VerifyCRC32)
	{
		gLog.Output(LOG_DEBUG,GetEncryptedString(41));
		SafeExitProcess();
	}
}
