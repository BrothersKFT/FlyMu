#include "stdafx.h"
#include "test.h"
#include "Import.h"
#include "Util.h"
#include "TMemory.h"
#include "Defines.h"
#include "Pet.h"
#include "CustomPet.h"
#include "Protect.h"
#include "Reconnect.h"
#include "InfoLog.h"
#include "Common.h"
#include "User.h"


Test gTest;


int __cdecl GameModelScale(int a1)
{
	int result; // eax@1
	float RenderSize; // eax@2
	float RenderMonk; // eax@3

	result = a1;

	lpViewObj lpPreview = &*(ObjectPreview*)result;

	if (!*(BYTE *)(a1 + 15))
	{
		if (*(WORD *)(a1 + 268) != 4755
			&& *(WORD *)(a1 + 268) != 4757
			&& *(WORD *)(a1 + 268) != 4818
			&& *(WORD *)(a1 + 268) != 4823
			&& *(WORD *)(a1 + 268) != 4820
			&& *(WORD *)(a1 + 268) != 4825
			&& ((signed int)*(WORD *)(a1 + 268) < 4765 || (signed int)*(WORD *)(a1 + 268) > 4768))
		{
			*(WORD *)(a1 + 232) = -1;
		}
		else
		{
			*(WORD *)(a1 + 232) = (unsigned __int8)sub_587500(*(BYTE *)(a1 + 19)) + 9389;
		}

		if (*(DWORD*)(MAIN_SCREEN_STATE) == 4)
		{
			return 0;
		}

		if (*(DWORD*)(MAIN_SCREEN_STATE) == 5)
		{

			if (Encoger ==1)
				{
					RenderSize = (40.0 > 0) ? ((double)((1.2f / 100) * 40.0)) : 1.2f;
					RenderMonk = (40.0 > 0) ? ((double)((1.35f / 100) * 40.0)) : 1.35f;
				}
				else
				{
					RenderSize = (80.0 > 0) ? ((double)((1.2f / 100) * 80.0)) : 1.2f;
					RenderMonk = (80.0 > 0) ? ((double)((1.35f / 100) * 80.0)) : 1.35f;
				}

				if (*(BYTE *)(a1 + 20))
				{
					result = sub_405230(*(BYTE *)(a1 + 19));
					switch (result)
					{
					case CLASS_WIZARD:
						result = a1;
						*(float *)(a1 + 872) = RenderSize;
						break;
					case CLASS_KNIGHT:
						*(float *)(a1 + 872) = RenderSize;
						break;
					case CLASS_ELF:
						*(float *)(a1 + 872) = RenderSize;
						break;
					case CLASS_MAGUMSA:
						result = a1;
						*(float *)(a1 + 872) = RenderSize;
						break;
					case CLASS_DARKLORD:
						*(float *)(a1 + 872) = RenderSize;
						break;
					case CLASS_SUMMONER:
						*(float *)(a1 + 872) = RenderSize;
						break;
					case CLASS_MONK:
						result = a1;
						*(float *)(a1 + 872) = RenderMonk;
						break;
					default:
						return result;
					}
				}
				else
				{
					result = sub_405230(*(BYTE *)(a1 + 19));
					switch (result)
					{
					case CLASS_WIZARD:
						*(float *)(a1 + 872) = RenderSize;
						break;
					case CLASS_KNIGHT:
						result = a1;
						*(float *)(a1 + 872) = RenderSize;
						break;
					case CLASS_ELF:
						*(float *)(a1 + 872) = RenderSize;
						break;
					case CLASS_MAGUMSA:
						*(float *)(a1 + 872) = RenderSize;
						break;
					case CLASS_DARKLORD:
						result = a1;
						*(float *)(a1 + 872) = RenderSize;
						break;
					case CLASS_SUMMONER:
						*(float *)(a1 + 872) = RenderSize;
						break;
					case CLASS_MONK:
						*(float *)(a1 + 872) = RenderMonk;
						break;
					default:
						return result;
					}
				}
		}
	}
	return result;
}


// TEST NADAR EN MAP
void __declspec(naked) CSetPlayerSwimStop()
{
	static DWORD CReturn = 0x0054EE7F;
	if (gProtect.m_MainInfo.MapAtlasAbyss == 82)
	{
		_asm
		{
			CMP DWORD PTR DS : [0xE61E18], 7
				je ReturnLoad
				CMP DWORD PTR DS : [0xE61E18], 82 //ID del Mapa
				je ReturnLoad
				// ---

		}
	}
	if (gProtect.m_MainInfo.MapAtlasAbyss == 83)
	{
		_asm
		{
			CMP DWORD PTR DS : [0xE61E18], 7
				je ReturnLoad
				CMP DWORD PTR DS : [0xE61E18], 83 //ID del Mapa
				je ReturnLoad
				// ---
		}
	}
	if (gProtect.m_MainInfo.MapAtlasAbyss == 84)
	{
		_asm
		{
			CMP DWORD PTR DS : [0xE61E18], 7
				je ReturnLoad
				CMP DWORD PTR DS : [0xE61E18], 84 //ID del Mapa
				je ReturnLoad
				// ---
		}
	}
	if (gProtect.m_MainInfo.MapAtlasAbyss == 85)
	{
		_asm
		{
			CMP DWORD PTR DS : [0xE61E18], 7
				je ReturnLoad
				CMP DWORD PTR DS : [0xE61E18], 85 //ID del Mapa
				je ReturnLoad
				// ---
		}
	}
	if (gProtect.m_MainInfo.MapAtlasAbyss == 86)
	{
		_asm
		{
			CMP DWORD PTR DS : [0xE61E18], 7
				je ReturnLoad
				CMP DWORD PTR DS : [0xE61E18], 86 //ID del Mapa
				je ReturnLoad
				// ---
		}
	}
	if (gProtect.m_MainInfo.MapAtlasAbyss == 87)
	{
		_asm
		{
			CMP DWORD PTR DS : [0xE61E18], 7
				je ReturnLoad
				CMP DWORD PTR DS : [0xE61E18], 87 //ID del Mapa
				je ReturnLoad
				// ---
		}
	}
	if (gProtect.m_MainInfo.MapAtlasAbyss == 88)
	{
		_asm
		{
			CMP DWORD PTR DS : [0xE61E18], 7
				je ReturnLoad
				CMP DWORD PTR DS : [0xE61E18], 88 //ID del Mapa
				je ReturnLoad
				// ---
		}
	}
	if (gProtect.m_MainInfo.MapAtlasAbyss == 89)
	{
		_asm
		{
			CMP DWORD PTR DS : [0xE61E18], 7
				je ReturnLoad
				CMP DWORD PTR DS : [0xE61E18], 89 //ID del Mapa
				je ReturnLoad
				// ---
		}
	}
	if (gProtect.m_MainInfo.MapAtlasAbyss == 90)
	{
		_asm
		{
			CMP DWORD PTR DS : [0xE61E18], 7
				je ReturnLoad
				CMP DWORD PTR DS : [0xE61E18], 90 //ID del Mapa
				je ReturnLoad
				// ---
		}
	}
	if (gProtect.m_MainInfo.MapAtlasAbyss == 91)
	{
		_asm
		{
			CMP DWORD PTR DS : [0xE61E18], 7
				je ReturnLoad
				CMP DWORD PTR DS : [0xE61E18], 91 //ID del Mapa
				je ReturnLoad
				// ---
		}
	}
	if (gProtect.m_MainInfo.MapAtlasAbyss == 92)
	{
		_asm
		{
			CMP DWORD PTR DS : [0xE61E18], 7
				je ReturnLoad
				CMP DWORD PTR DS : [0xE61E18], 92 //ID del Mapa
				je ReturnLoad
				// ---
		}
	}
	if (gProtect.m_MainInfo.MapAtlasAbyss == 93)
	{
		_asm
		{
			CMP DWORD PTR DS : [0xE61E18], 7
				je ReturnLoad
				CMP DWORD PTR DS : [0xE61E18], 93 //ID del Mapa
				je ReturnLoad
				// ---
		}
	}
	if (gProtect.m_MainInfo.MapAtlasAbyss == 94)
	{
		_asm
		{
			CMP DWORD PTR DS : [0xE61E18], 7
				je ReturnLoad
				CMP DWORD PTR DS : [0xE61E18], 94 //ID del Mapa
				je ReturnLoad
				// ---
		}
	}
	if (gProtect.m_MainInfo.MapAtlasAbyss == 95)
	{
		_asm
		{
			CMP DWORD PTR DS : [0xE61E18], 7
				je ReturnLoad
				CMP DWORD PTR DS : [0xE61E18], 95 //ID del Mapa
				je ReturnLoad
				// ---
		}
	}
	if (gProtect.m_MainInfo.MapAtlasAbyss == 96)
	{
		_asm
		{
			CMP DWORD PTR DS : [0xE61E18], 7
				je ReturnLoad
				CMP DWORD PTR DS : [0xE61E18], 96 //ID del Mapa
				je ReturnLoad
				// ---
		}
	}
	if (gProtect.m_MainInfo.MapAtlasAbyss == 97)
	{
		_asm
		{
			CMP DWORD PTR DS : [0xE61E18], 7
				je ReturnLoad
				CMP DWORD PTR DS : [0xE61E18], 97 //ID del Mapa
				je ReturnLoad
				// ---
		}
	}
	if (gProtect.m_MainInfo.MapAtlasAbyss == 98)
	{
		_asm
		{
			CMP DWORD PTR DS : [0xE61E18], 7
				je ReturnLoad
				CMP DWORD PTR DS : [0xE61E18], 98 //ID del Mapa
				je ReturnLoad
				// ---
		}
	}
	if (gProtect.m_MainInfo.MapAtlasAbyss == 99)
	{
		_asm
		{
			CMP DWORD PTR DS : [0xE61E18], 7
				je ReturnLoad
				CMP DWORD PTR DS : [0xE61E18], 99 //ID del Mapa
				je ReturnLoad
				// ---
		}
	}

	_asm
	{
	ReturnLoad:
		// ---
		jmp CReturn
	}
}

void __declspec(naked) CSetPlayerSwimWalk()
{
	static DWORD CReturn = 0x0054FFBE;
	if (gProtect.m_MainInfo.MapAtlasAbyss == 82)
	{
		_asm
		{
			CMP DWORD PTR DS : [0xE61E18], 7
				je ReturnLoad
				CMP DWORD PTR DS : [0xE61E18], 82 //ID del Mapa
				je ReturnLoad
				// ---

		}
	}
	if (gProtect.m_MainInfo.MapAtlasAbyss == 83)
	{
		_asm
		{
			CMP DWORD PTR DS : [0xE61E18], 7
				je ReturnLoad
				CMP DWORD PTR DS : [0xE61E18], 83 //ID del Mapa
				je ReturnLoad
				// ---
		}
	}
	if (gProtect.m_MainInfo.MapAtlasAbyss == 84)
	{
		_asm
		{
			CMP DWORD PTR DS : [0xE61E18], 7
				je ReturnLoad
				CMP DWORD PTR DS : [0xE61E18], 84 //ID del Mapa
				je ReturnLoad
				// ---
		}
	}
	if (gProtect.m_MainInfo.MapAtlasAbyss == 85)
	{
		_asm
		{
			CMP DWORD PTR DS : [0xE61E18], 7
				je ReturnLoad
				CMP DWORD PTR DS : [0xE61E18], 85 //ID del Mapa
				je ReturnLoad
				// ---
		}
	}
	if (gProtect.m_MainInfo.MapAtlasAbyss == 86)
	{
		_asm
		{
			CMP DWORD PTR DS : [0xE61E18], 7
				je ReturnLoad
				CMP DWORD PTR DS : [0xE61E18], 86 //ID del Mapa
				je ReturnLoad
				// ---
		}
	}
	if (gProtect.m_MainInfo.MapAtlasAbyss == 87)
	{
		_asm
		{
			CMP DWORD PTR DS : [0xE61E18], 7
				je ReturnLoad
				CMP DWORD PTR DS : [0xE61E18], 87 //ID del Mapa
				je ReturnLoad
				// ---
		}
	}
	if (gProtect.m_MainInfo.MapAtlasAbyss == 88)
	{
		_asm
		{
			CMP DWORD PTR DS : [0xE61E18], 7
				je ReturnLoad
				CMP DWORD PTR DS : [0xE61E18], 88 //ID del Mapa
				je ReturnLoad
				// ---
		}
	}
	if (gProtect.m_MainInfo.MapAtlasAbyss == 89)
	{
		_asm
		{
			CMP DWORD PTR DS : [0xE61E18], 7
				je ReturnLoad
				CMP DWORD PTR DS : [0xE61E18], 89 //ID del Mapa
				je ReturnLoad
				// ---
		}
	}
	if (gProtect.m_MainInfo.MapAtlasAbyss == 90)
	{
		_asm
		{
			CMP DWORD PTR DS : [0xE61E18], 7
				je ReturnLoad
				CMP DWORD PTR DS : [0xE61E18], 90 //ID del Mapa
				je ReturnLoad
				// ---
		}
	}
	if (gProtect.m_MainInfo.MapAtlasAbyss == 91)
	{
		_asm
		{
			CMP DWORD PTR DS : [0xE61E18], 7
				je ReturnLoad
				CMP DWORD PTR DS : [0xE61E18], 91 //ID del Mapa
				je ReturnLoad
				// ---
		}
	}
	if (gProtect.m_MainInfo.MapAtlasAbyss == 92)
	{
		_asm
		{
			CMP DWORD PTR DS : [0xE61E18], 7
				je ReturnLoad
				CMP DWORD PTR DS : [0xE61E18], 92 //ID del Mapa
				je ReturnLoad
				// ---
		}
	}
	if (gProtect.m_MainInfo.MapAtlasAbyss == 93)
	{
		_asm
		{
			CMP DWORD PTR DS : [0xE61E18], 7
				je ReturnLoad
				CMP DWORD PTR DS : [0xE61E18], 93 //ID del Mapa
				je ReturnLoad
				// ---
		}
	}
	if (gProtect.m_MainInfo.MapAtlasAbyss == 94)
	{
		_asm
		{
			CMP DWORD PTR DS : [0xE61E18], 7
				je ReturnLoad
				CMP DWORD PTR DS : [0xE61E18], 94 //ID del Mapa
				je ReturnLoad
				// ---
		}
	}
	if (gProtect.m_MainInfo.MapAtlasAbyss == 95)
	{
		_asm
		{
			CMP DWORD PTR DS : [0xE61E18], 7
				je ReturnLoad
				CMP DWORD PTR DS : [0xE61E18], 95 //ID del Mapa
				je ReturnLoad
				// ---
		}
	}
	if (gProtect.m_MainInfo.MapAtlasAbyss == 96)
	{
		_asm
		{
			CMP DWORD PTR DS : [0xE61E18], 7
				je ReturnLoad
				CMP DWORD PTR DS : [0xE61E18], 96 //ID del Mapa
				je ReturnLoad
				// ---
		}
	}
	if (gProtect.m_MainInfo.MapAtlasAbyss == 97)
	{
		_asm
		{
			CMP DWORD PTR DS : [0xE61E18], 7
				je ReturnLoad
				CMP DWORD PTR DS : [0xE61E18], 97 //ID del Mapa
				je ReturnLoad
				// ---
		}
	}
	if (gProtect.m_MainInfo.MapAtlasAbyss == 98)
	{
		_asm
		{
			CMP DWORD PTR DS : [0xE61E18], 7
				je ReturnLoad
				CMP DWORD PTR DS : [0xE61E18], 98 //ID del Mapa
				je ReturnLoad
				// ---
		}
	}
	if (gProtect.m_MainInfo.MapAtlasAbyss == 99)
	{
		_asm
		{
			CMP DWORD PTR DS : [0xE61E18], 7
				je ReturnLoad
				CMP DWORD PTR DS : [0xE61E18], 99 //ID del Mapa
				je ReturnLoad
				// ---
		}
	}

	_asm
	{
	ReturnLoad:
		// ---
		jmp CReturn
	}
}

void __declspec(naked) CRenderCharacterBackItem_Swim()
{
	static DWORD CReturn = 0x005880B4;
	if (gProtect.m_MainInfo.MapAtlasAbyss == 82)
	{
		_asm
		{
			CMP DWORD PTR DS : [0xE61E18], 7
				je ReturnLoad
				CMP DWORD PTR DS : [0xE61E18], 82 //ID del Mapa
				je ReturnLoad
				// ---

		}
	}
	if (gProtect.m_MainInfo.MapAtlasAbyss == 83)
	{
		_asm
		{
			CMP DWORD PTR DS : [0xE61E18], 7
				je ReturnLoad
				CMP DWORD PTR DS : [0xE61E18], 83 //ID del Mapa
				je ReturnLoad
				// ---
		}
	}
	if (gProtect.m_MainInfo.MapAtlasAbyss == 84)
	{
		_asm
		{
			CMP DWORD PTR DS : [0xE61E18], 7
				je ReturnLoad
				CMP DWORD PTR DS : [0xE61E18], 84 //ID del Mapa
				je ReturnLoad
				// ---
		}
	}
	if (gProtect.m_MainInfo.MapAtlasAbyss == 85)
	{
		_asm
		{
			CMP DWORD PTR DS : [0xE61E18], 7
				je ReturnLoad
				CMP DWORD PTR DS : [0xE61E18], 85 //ID del Mapa
				je ReturnLoad
				// ---
		}
	}
	if (gProtect.m_MainInfo.MapAtlasAbyss == 86)
	{
		_asm
		{
			CMP DWORD PTR DS : [0xE61E18], 7
				je ReturnLoad
				CMP DWORD PTR DS : [0xE61E18], 86 //ID del Mapa
				je ReturnLoad
				// ---
		}
	}
	if (gProtect.m_MainInfo.MapAtlasAbyss == 87)
	{
		_asm
		{
			CMP DWORD PTR DS : [0xE61E18], 7
				je ReturnLoad
				CMP DWORD PTR DS : [0xE61E18], 87 //ID del Mapa
				je ReturnLoad
				// ---
		}
	}
	if (gProtect.m_MainInfo.MapAtlasAbyss == 88)
	{
		_asm
		{
			CMP DWORD PTR DS : [0xE61E18], 7
				je ReturnLoad
				CMP DWORD PTR DS : [0xE61E18], 88 //ID del Mapa
				je ReturnLoad
				// ---
		}
	}
	if (gProtect.m_MainInfo.MapAtlasAbyss == 89)
	{
		_asm
		{
			CMP DWORD PTR DS : [0xE61E18], 7
				je ReturnLoad
				CMP DWORD PTR DS : [0xE61E18], 89 //ID del Mapa
				je ReturnLoad
				// ---
		}
	}
	if (gProtect.m_MainInfo.MapAtlasAbyss == 90)
	{
		_asm
		{
			CMP DWORD PTR DS : [0xE61E18], 7
				je ReturnLoad
				CMP DWORD PTR DS : [0xE61E18], 90 //ID del Mapa
				je ReturnLoad
				// ---
		}
	}
	if (gProtect.m_MainInfo.MapAtlasAbyss == 91)
	{
		_asm
		{
			CMP DWORD PTR DS : [0xE61E18], 7
				je ReturnLoad
				CMP DWORD PTR DS : [0xE61E18], 91 //ID del Mapa
				je ReturnLoad
				// ---
		}
	}
	if (gProtect.m_MainInfo.MapAtlasAbyss == 92)
	{
		_asm
		{
			CMP DWORD PTR DS : [0xE61E18], 7
				je ReturnLoad
				CMP DWORD PTR DS : [0xE61E18], 92 //ID del Mapa
				je ReturnLoad
				// ---
		}
	}
	if (gProtect.m_MainInfo.MapAtlasAbyss == 93)
	{
		_asm
		{
			CMP DWORD PTR DS : [0xE61E18], 7
				je ReturnLoad
				CMP DWORD PTR DS : [0xE61E18], 93 //ID del Mapa
				je ReturnLoad
				// ---
		}
	}
	if (gProtect.m_MainInfo.MapAtlasAbyss == 94)
	{
		_asm
		{
			CMP DWORD PTR DS : [0xE61E18], 7
				je ReturnLoad
				CMP DWORD PTR DS : [0xE61E18], 94 //ID del Mapa
				je ReturnLoad
				// ---
		}
	}
	if (gProtect.m_MainInfo.MapAtlasAbyss == 95)
	{
		_asm
		{
			CMP DWORD PTR DS : [0xE61E18], 7
				je ReturnLoad
				CMP DWORD PTR DS : [0xE61E18], 95 //ID del Mapa
				je ReturnLoad
				// ---
		}
	}
	if (gProtect.m_MainInfo.MapAtlasAbyss == 96)
	{
		_asm
		{
			CMP DWORD PTR DS : [0xE61E18], 7
				je ReturnLoad
				CMP DWORD PTR DS : [0xE61E18], 96 //ID del Mapa
				je ReturnLoad
				// ---
		}
	}
	if (gProtect.m_MainInfo.MapAtlasAbyss == 97)
	{
		_asm
		{
			CMP DWORD PTR DS : [0xE61E18], 7
				je ReturnLoad
				CMP DWORD PTR DS : [0xE61E18], 97 //ID del Mapa
				je ReturnLoad
				// ---
		}
	}
	if (gProtect.m_MainInfo.MapAtlasAbyss == 98)
	{
		_asm
		{
			CMP DWORD PTR DS : [0xE61E18], 7
				je ReturnLoad
				CMP DWORD PTR DS : [0xE61E18], 98 //ID del Mapa
				je ReturnLoad
				// ---
		}
	}
	if (gProtect.m_MainInfo.MapAtlasAbyss == 99)
	{
		_asm
		{
			CMP DWORD PTR DS : [0xE61E18], 7
				je ReturnLoad
				CMP DWORD PTR DS : [0xE61E18], 99 //ID del Mapa
				je ReturnLoad
				// ---
		}
	}

	_asm
	{
	ReturnLoad:
		// ---
		jmp CReturn
	}
}

void __declspec(naked) CPlayWalkSound_Swim()
{
	static DWORD CReturn = 0x00560CED;
	if (gProtect.m_MainInfo.MapAtlasAbyss == 82)
	{
		_asm
		{
			CMP DWORD PTR DS : [0xE61E18], 7
				je ReturnLoad
				CMP DWORD PTR DS : [0xE61E18], 82 //ID del Mapa
				je ReturnLoad
				// ---

		}
	}
	if (gProtect.m_MainInfo.MapAtlasAbyss == 83)
	{
		_asm
		{
			CMP DWORD PTR DS : [0xE61E18], 7
				je ReturnLoad
				CMP DWORD PTR DS : [0xE61E18], 83 //ID del Mapa
				je ReturnLoad
				// ---
		}
	}
	if (gProtect.m_MainInfo.MapAtlasAbyss == 84)
	{
		_asm
		{
			CMP DWORD PTR DS : [0xE61E18], 7
				je ReturnLoad
				CMP DWORD PTR DS : [0xE61E18], 84 //ID del Mapa
				je ReturnLoad
				// ---
		}
	}
	if (gProtect.m_MainInfo.MapAtlasAbyss == 85)
	{
		_asm
		{
			CMP DWORD PTR DS : [0xE61E18], 7
				je ReturnLoad
				CMP DWORD PTR DS : [0xE61E18], 85 //ID del Mapa
				je ReturnLoad
				// ---
		}
	}
	if (gProtect.m_MainInfo.MapAtlasAbyss == 86)
	{
		_asm
		{
			CMP DWORD PTR DS : [0xE61E18], 7
				je ReturnLoad
				CMP DWORD PTR DS : [0xE61E18], 86 //ID del Mapa
				je ReturnLoad
				// ---
		}
	}
	if (gProtect.m_MainInfo.MapAtlasAbyss == 87)
	{
		_asm
		{
			CMP DWORD PTR DS : [0xE61E18], 7
				je ReturnLoad
				CMP DWORD PTR DS : [0xE61E18], 87 //ID del Mapa
				je ReturnLoad
				// ---
		}
	}
	if (gProtect.m_MainInfo.MapAtlasAbyss == 88)
	{
		_asm
		{
			CMP DWORD PTR DS : [0xE61E18], 7
				je ReturnLoad
				CMP DWORD PTR DS : [0xE61E18], 88 //ID del Mapa
				je ReturnLoad
				// ---
		}
	}
	if (gProtect.m_MainInfo.MapAtlasAbyss == 89)
	{
		_asm
		{
			CMP DWORD PTR DS : [0xE61E18], 7
				je ReturnLoad
				CMP DWORD PTR DS : [0xE61E18], 89 //ID del Mapa
				je ReturnLoad
				// ---
		}
	}
	if (gProtect.m_MainInfo.MapAtlasAbyss == 90)
	{
		_asm
		{
			CMP DWORD PTR DS : [0xE61E18], 7
				je ReturnLoad
				CMP DWORD PTR DS : [0xE61E18], 90 //ID del Mapa
				je ReturnLoad
				// ---
		}
	}
	if (gProtect.m_MainInfo.MapAtlasAbyss == 91)
	{
		_asm
		{
			CMP DWORD PTR DS : [0xE61E18], 7
				je ReturnLoad
				CMP DWORD PTR DS : [0xE61E18], 91 //ID del Mapa
				je ReturnLoad
				// ---
		}
	}
	if (gProtect.m_MainInfo.MapAtlasAbyss == 92)
	{
		_asm
		{
			CMP DWORD PTR DS : [0xE61E18], 7
				je ReturnLoad
				CMP DWORD PTR DS : [0xE61E18], 92 //ID del Mapa
				je ReturnLoad
				// ---
		}
	}
	if (gProtect.m_MainInfo.MapAtlasAbyss == 93)
	{
		_asm
		{
			CMP DWORD PTR DS : [0xE61E18], 7
				je ReturnLoad
				CMP DWORD PTR DS : [0xE61E18], 93 //ID del Mapa
				je ReturnLoad
				// ---
		}
	}
	if (gProtect.m_MainInfo.MapAtlasAbyss == 94)
	{
		_asm
		{
			CMP DWORD PTR DS : [0xE61E18], 7
				je ReturnLoad
				CMP DWORD PTR DS : [0xE61E18], 94 //ID del Mapa
				je ReturnLoad
				// ---
		}
	}
	if (gProtect.m_MainInfo.MapAtlasAbyss == 95)
	{
		_asm
		{
			CMP DWORD PTR DS : [0xE61E18], 7
				je ReturnLoad
				CMP DWORD PTR DS : [0xE61E18], 95 //ID del Mapa
				je ReturnLoad
				// ---
		}
	}
	if (gProtect.m_MainInfo.MapAtlasAbyss == 96)
	{
		_asm
		{
			CMP DWORD PTR DS : [0xE61E18], 7
				je ReturnLoad
				CMP DWORD PTR DS : [0xE61E18], 96 //ID del Mapa
				je ReturnLoad
				// ---
		}
	}
	if (gProtect.m_MainInfo.MapAtlasAbyss == 97)
	{
		_asm
		{
			CMP DWORD PTR DS : [0xE61E18], 7
				je ReturnLoad
				CMP DWORD PTR DS : [0xE61E18], 97 //ID del Mapa
				je ReturnLoad
				// ---
		}
	}
	if (gProtect.m_MainInfo.MapAtlasAbyss == 98)
	{
		_asm
		{
			CMP DWORD PTR DS : [0xE61E18], 7
				je ReturnLoad
				CMP DWORD PTR DS : [0xE61E18], 98 //ID del Mapa
				je ReturnLoad
				// ---
		}
	}
	if (gProtect.m_MainInfo.MapAtlasAbyss == 99)
	{
		_asm
		{
			CMP DWORD PTR DS : [0xE61E18], 7
				je ReturnLoad
				CMP DWORD PTR DS : [0xE61E18], 99 //ID del Mapa
				je ReturnLoad
				// ---
		}
	}

	_asm
	{
	ReturnLoad:
		// ---
		jmp CReturn
	}
}
// END TEST NADAR EN MAP

__declspec(naked) void FixEffects()
{
	static DWORD Address1 = 0x0062F6CE;
	static DWORD Address2 = 0x0062F69F;

	if (pMapNumber == 0 || pMapNumber == 3)
	{
		_asm{jmp Address1}
	}
	else
	{
		_asm{jmp Address2}
	}
}

void RenderCharacter(lpViewObj lpObj, Object* lpObject, int a3)
{
	if (isHiddenPlayer && lpObj->m_Model.ObjectType == emPlayer && lpObj->aIndex != gObjUser.lpViewPlayer->aIndex)
	{
		return;
	}

	return pRenderCharacter(lpObj, lpObject, a3);
}

void Test::InitTest()
{
//	SetCompleteHook(0xE9, 0x0057F020, &GameModelScale);

	// HIDE CHARACTER
	SetCompleteHook(0xE8, 0x0057D4FF, &RenderCharacter);
	SetCompleteHook(0xE8, 0x0057D513, &RenderCharacter);

	// TEST NADAR EN MAP
	SetCompleteHook(0xE9, 0x0054EE78, &CSetPlayerSwimStop);
	SetCompleteHook(0xE9, 0x0054FFB7, &CSetPlayerSwimWalk);
	SetCompleteHook(0xE9, 0x005880AD, &CRenderCharacterBackItem_Swim);
	SetCompleteHook(0xE9, 0x00560CE6, &CPlayWalkSound_Swim);
	// END TEST NADAR EN MAP

	SetCompleteHook(0xE9, 0x0062F69A, &FixEffects);

	// FIX EVOLUTION TEXTURES WHITE
	SetDword(0x0057F9FA + 3, 304); //-- slot armor
	SetDword(0x0057FA3D + 3, 340); //-- slot pants
	SetDword(0x0057FA7F + 3, 376); //-- slot glove
	SetDword(0x0057FAC1 + 3, 412); //-- slot boot
}