#pragma once
#if OFF
#include "Object.h"
#include "Protocol.h"

#define JCGetInstance				((int(*)()) 0x00482B70)
#define JCGetNewFace					((__int16(__thiscall*)(int a6)) 0x004044D0)
#define sub_4D5A40					((int(__cdecl*)(char *a3, char *a4, int a5, signed int a6)) 0x004D5A40)
#define JCSpiriteSetInfo					((int(__thiscall*)(int a1, int a5, int a6, int a7, int a8, signed int a9, signed int a10, int a11, int a12, signed int a13, signed int a14, int a15)) 0x00401370)
#define JCSpiriteSetPosition				((int(__fastcall*)(int a1, int a2, signed int a3, signed int a4, char a5)) 0x00416640)
#define JCButtonPush				((char(__thiscall*)(int a1 )) 0x00404AD0)
#define JCButtonShow				((__int16(__thiscall*)(int a1 )) 0x00403700)
#define JCSetText					((char *(__thiscall*)(int a1, char *a4, const void *a5 )) 0x00401AE0)
#define JCSetModelCoord					((int(__cdecl*)(int a1, int a2, char a3, float x, float y, float z)) 0x00586DA0)


int __fastcall sub_4167A0(int a1, int a2, signed int a3, signed int a4, char a5);


#define sub_63CB40			((int(*)(void)) 0x0063CB40)
#define sub_4D5130			((DWORD(__cdecl*)(char a1)) 0x004D5130)
#define sub_9CF1C0			((char *(__cdecl*)(char *a1, const void *a2, unsigned int a3)) 0x009CF1C0)
#define dword_87935A4		*(int*)0x87935A4
#define sub_861110			((int(__cdecl*)()) 0x00861110)
#define sub_861A80			((int(__thiscall*)(DWORD)) 0x00861A80)
#define sub_856BD0			((DWORD(__thiscall*)(char a1)) 0x00856BD0)
#define dword_E8CB30		*(int*)0xE8CB30
#define sub_57D760			((void(__cdecl*)(int a4)) 0x0057D760)
#define sub_668520			((int(__thiscall*)(char *a1)) 0x00668520)
#define sub_4057B0			((int(__thiscall*)(char *a1)) 0x004057B0)
#define sub_402AD0			((int(__thiscall*)(char *a1)) 0x00402AD0)
#define sub_484A10			((int(__thiscall*)(int This, int a2, char *a3)) 0x00484A10)
#define sub_587380			((DWORD(__cdecl*)(char)) 0x587380)
#define sub_482B70          ((int(*)()) 0x00482B70)

#define sub_586DA0			((int(__cdecl*)(int a1, int a2, char a3, float x, float y, float z)) 0x586DA0)
#define sub_63D130			((DWORD(__cdecl*)(int a1)) 0x63D130)
#define sub_5977E0          ((int(*)(void)) 0x005977E0)
#define sub_482B70          ((int(*)()) 0x00482B70)
#define sub_4849A0			((int(__thiscall*)(DWORD)) 0x004849A0)
#define sub_5BB0B0          ((int(*)()) 0x005BB0B0)
#define sub_4D5C60          ((int(*)()) 0x004D5C60)

struct PMSG_CHARACTER_LIST
{
	BYTE slot;
	char name[11];
	WORD level;
	BYTE Class;
	BYTE CtlCode;
	BYTE Inventory[60];
	BYTE GuildStatus;
	DWORD Reset;
	DWORD MasterReset;
};

struct PMSG_JCCHARACTER_LIST_RECV
{
	PSBMSG_HEAD header; // C1:F3:00
	BYTE ClassCode;
	BYTE MoveCnt;
	BYTE count;
	BYTE ExtWarehouse;
};

struct PMSG_CHARACTER_CREATE_RECV
{
	PSBMSG_HEAD header; // C1:F3:01
	BYTE result;
	char name[10];
	BYTE slot;
	WORD level;
	BYTE Class;
	BYTE equipment[24];
};

struct PMSG_CHARACTER_CREATE_SEND
{
	PSBMSG_HEAD header; // C1:F3:01
	char name[10];
	BYTE Class;
};

class JCSceneCreate
{
public:
	JCSceneCreate();
	~JCSceneCreate();
	void Load();

	static void OpenCharacterSceneData();
};

extern JCSceneCreate JCGetScene;

#endif