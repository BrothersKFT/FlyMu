#pragma once
#define sub_82B7A0							((char(__thiscall*)(int a1, signed int a4, signed int a5))0x0082B7A0)
#define AccessModel							((void(__cdecl*)(int ResourceID, char * Path, char * File, int Arg4)) 0x00614D10)
#define OpenTexture							((void(__cdecl*)(int TextureID, char * Folder, int GLREPEAT, int GLNEAREST, int GLTRUE)) 0x00614710)
#define IsPress								((int(__cdecl*)(int VKBUTTON)) 0x00791070)
#define ErrorMessage						*(DWORD*)0xE8CB3C
#define sub_888290							((int(__thiscall*)(int This)) 0x00888290)
#define sub_8898E0							((void(__thiscall*)(int This)) 0x008898E0)
#define GetSingleton						((int(*)())0x004CDA10)
#define GetPlayerModelAction				((int(__thiscall*)(int This, signed int a2)) 0x0051A220)
#define sub_639CD0							((int(__cdecl*)(int a1, float a2, float a3)) 0x00639CD0)

typedef struct
{
	BYTE gap1[4];
	DWORD UNONK4;
	DWORD UNONK8;
	DWORD x;
	DWORD y;
	DWORD UNONK20;
	DWORD UNONK24;
	DWORD UNONK28;
	DWORD UNONK32;
	BYTE gap2[63];
	DWORD UNONK96;
	DWORD UNONK100;
	DWORD UNONK104;
	DWORD UNONK108;
	DWORD UNONK112;
	float CurrentX;
	float CurrentY;
	DWORD Scale;
	float UNONK128;
	BYTE gap3[2];
	BYTE UNONK134;
	BYTE gap4[5];
	DWORD UNONK140;
	float UNONK144;
}JCMapStruct, *lpMapStruct;

class JCMinimap
{
public:
	JCMinimap();
	~JCMinimap();
	int 			CRadarZoom;
	void Load();
	void JCCreateRadar();
	void RenderFrame();
	void ButtonEventZoom();
};

extern JCMinimap JCGetMinimap;