#include "stdafx.h"
#include "GLFont.h"
#include "Offset.h"
#include "Import.h"
#include "Util.h"

CUIPaintText CFont;

CUIPaintText::CUIPaintText()
{
	this->ColorFont[0] = 1.0;
	this->ColorFont[1] = 1.0;
	this->ColorFont[2] = 1.0;
	this->ColorFont[3] = 1.0;
	this->hFont = CreateFontA ( 14, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, HANGEUL_CHARSET, OUT_TT_ONLY_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH, "Arial" ); // Creamos la Font
	this->hFontDefault = CreateFontA ( 14, 0, 0, 0, FW_SEMIBOLD, FALSE, FALSE, FALSE, HANGEUL_CHARSET, OUT_TT_ONLY_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH, "Arial" ); // Creamos la Font
	this->hFontBold = CreateFontA ( 14, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, HANGEUL_CHARSET, OUT_TT_ONLY_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH, "Arial" ); // Creamos la Font
}

void CUIPaintText::CUIPreparedText()
{
	int cHeight; // [sp+E74h] [bp-ECh]@76

	switch (*(QWORD*)0xE61E58)
	{
	case 800:
		cHeight = 12;
		break;
	case 1024:
		cHeight = 13;
		break;
	default:
		cHeight = 14;
		break;
	}

	this->hFontDefault = CreateFontA(cHeight - 1, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, CLIP_DEFAULT_PRECIS, 3u, 0, "Tahoma");
	this->hFontBold = CreateFontA(cHeight - 1, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, CLIP_DEFAULT_PRECIS, 3u, 0, "Tahoma");
	this->hFont = CreateFontA(cHeight - 1, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, CLIP_DEFAULT_PRECIS, 3u, DEFAULT_PITCH, "Tahoma");
	//this->hFontBold = CreateFontA ( 14, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, HANGEUL_CHARSET, OUT_TT_ONLY_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH, "Arial" ); // Creamos la Font
}

CUIPaintText::~CUIPaintText()
{

}

void CUIPaintText::ClearFontHdc()
{
	this->hFont = CreateFontA(14, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, HANGEUL_CHARSET, OUT_TT_ONLY_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH, "Arial"); // Creamos la Font
}

void CUIPaintText::SetFontHdc(HFONT font)
{
	this->hFont = font;
}

void CUIPaintText::SetFontColor(GLfloat R, GLfloat G, GLfloat B, GLfloat Alpha)
{
	this->ColorFont[0] = R / 255;
	this->ColorFont[1] = G / 255;
	this->ColorFont[2] = B / 255;
	this->ColorFont[3] = Alpha / 255;
}

void CUIPaintText::CUIPaintFont(int DirPathX, int DirPathY, LPCSTR lpString, int DirPathW, int DirPathAling)
{
	glDisable(GL_TEXTURE_2D);
	glPushAttrib(GL_CURRENT_BIT);

	HDC hDC = GetDC(pGameWindow);
	struct tagSIZE psizl;
	static SHORT FontWidth[255];
	static UINT FontListID;

	if (!FontListID)
	{
		FontListID = glGenLists(256);

		while (!wglUseFontBitmapsA(hDC, 0, 255, FontListID))
			Sleep(1);
	}

	SelectObject(hDC, this->hFont);
	GetTextExtentPoint32(hDC, lpString, strlen(lpString), &psizl);

	float PosX = (double)DirPathX * pWinWidthReal;
	float PosY = (double)DirPathY * pWinHeightReal;
	float Width = (double)DirPathW * pWinWidthReal;

	float v34 = (double)(signed int)psizl.cx;
	float v35 = (double)(signed int)psizl.cy;

	if (Width == 0.0)
		Width = (double)(signed int)psizl.cx;

	signed int v36 = 0;
	signed int v30 = 0;

	switch (DirPathAling)
	{
	case 2:
		if (Width < (double)v34)
		{
			v30 = (signed int)(v34 - Width);
			v34 = Width;
		}
		break;
	case 1:
		if (Width < (double)v34)
			v34 = Width;
		break;
	case 3:
		if (Width >= (double)v34)
		{
			v36 = (signed int)((Width - v34) / 2.0);
		}
		else
		{
			v30 = (signed int)((v34 - Width) / 2.0);
			v34 = Width;
		}
		break;
	case 4:
		if (Width >= (double)v34)
		{
			v36 = (signed int)(Width - v34);
		}
		else
		{
			v30 = (signed int)(v34 - Width);
			v34 = Width;
		}
		break;
	case 7:
		if (Width >= (double)v34)
		{
			v36 = (signed int)(Width - v34);
		}
		else
		{
			v30 = (signed int)(v34 - Width);
			v34 = Width;
		}
		PosX = PosX - Width;
		break;
	case 8:
		if (Width >= (double)v34)
		{
			v36 = (signed int)((Width - v34) / 2.0);
		}
		else
		{
			v30 = (signed int)((v34 - Width) / 2.0);
			v34 = Width;
		}
		PosX = PosX - Width / 2.0;
		break;
	}

	float v33 = (double)pWinHeight - PosY;

	GLfloat ColorFont[4];
	glGetFloatv(GL_CURRENT_COLOR, ColorFont);

	glListBase(FontListID);

	glColor4f(0.0, 0.0, 0.0, 0.8);

	glRasterPos2f(PosX - 0.5, v33 - 0.5);
	glCallLists(strlen(lpString), GL_UNSIGNED_BYTE, lpString);

	glRasterPos2f(PosX + 0.5, v33 - 0.5);
	glCallLists(strlen(lpString), GL_UNSIGNED_BYTE, lpString);

	glRasterPos2f(PosX + 0.5, v33 + 0.5);
	glCallLists(strlen(lpString), GL_UNSIGNED_BYTE, lpString);

	glRasterPos2f(PosX - 0.5, v33 + 0.5);
	glCallLists(strlen(lpString), GL_UNSIGNED_BYTE, lpString);

	glColor4fv(this->ColorFont);

	glRasterPos2f(PosX, v33);
	glCallLists(strlen(lpString), GL_UNSIGNED_BYTE, lpString);

	glColor4fv(ColorFont);

	glEnable(GL_TEXTURE_2D);

}

int __thiscall CUIPaintText::CNewUIChatFontColor1(int thisa, unsigned __int8 a2, unsigned __int8 a3, unsigned __int8 a4, unsigned __int8 a5)
{
	CFont.SetFontColor(a2, a3, a4, a5);
	return 1;
}

int __thiscall CUIPaintText::CNewUIChatFontColor2(int thisa, unsigned __int8 a2, unsigned __int8 a3, unsigned __int8 a4, unsigned __int8 a5)
{
	CFont.SetFontColor(0x99u, 0xCCu, 0xFFu, a5);
	return 1;
}

int __thiscall CUIPaintText::CNewUIChatFontColor3(int thisa, unsigned __int8 a2, unsigned __int8 a3, unsigned __int8 a4, unsigned __int8 a5)
{
	CFont.SetFontColor(0x99u, 0xCCu, 0xFFu, a5);
	return 1;
}

int __thiscall CUIPaintText::CNewUIChatFontColor4(int thisa, unsigned __int8 a2, unsigned __int8 a3, unsigned __int8 a4, unsigned __int8 a5)
{
	//-- warning
	CFont.SetFontColor(a2, a3, a4, 0xEBu);
	return 1;
}

int __thiscall CUIPaintText::CNewUIChatFontColor5(int thisa, unsigned __int8 a2, unsigned __int8 a3, unsigned __int8 a4, unsigned __int8 a5)
{
	CFont.SetFontColor(0x99u, 0xCCu, 0xFFu, a5);
	return 1;
}

int __thiscall CUIPaintText::CNewUIChatFontColor6(int thisa, unsigned __int8 a2, unsigned __int8 a3, unsigned __int8 a4, unsigned __int8 a5)
{
	CFont.SetFontColor(0x02u, 0x7Cu, 0x57u, 0xF5u);
	return 1;
}

int __thiscall CUIPaintText::CNewUIChatFontColor7(int thisa, unsigned __int8 a2, unsigned __int8 a3, unsigned __int8 a4, unsigned __int8 a5)
{
	CFont.SetFontColor(248, 253, 7, 0xF5u);
	return 1;
}

int __thiscall CUIPaintText::CNewUIChatFontColor8(int thisa, unsigned __int8 a2, unsigned __int8 a3, unsigned __int8 a4, unsigned __int8 a5)
{
	CFont.SetFontColor(a2, a3, a4, a5);
	return 1;
}

int __thiscall CUIPaintText::CNewUIChatFontColor9(int thisa, unsigned __int8 a2, unsigned __int8 a3, unsigned __int8 a4, unsigned __int8 a5)
{
	//-- gens
	CFont.SetFontColor(0x99u, 0xCCu, 0, 0xF5u);
	return 1;
}

int __thiscall CUIPaintText::CNewUIChatPaintFont(int thisa, int PosX, int PosY, LPCTSTR Text, int nCount, int nTabPositions, int lpnTabStopPositions, int nTabOrigin)
{
	CFont.CUIPaintFont(PosX, PosY, Text, nCount, lpnTabStopPositions);
	return 1;
}

int __thiscall CUIPaintText::CNewUIChatFontColor(int thisa, unsigned __int8 a2, unsigned __int8 a3, unsigned __int8 a4, unsigned __int8 a5)
{
	CFont.SetFontColor(a2, a3, a4, a5);
	return 1;
}

void CUIPaintText::Load()
{
	SetCompleteHook(0xE8, 0x005978B2, &CNewUIChatFontColor); //-- FontChat
	SetCompleteHook(0xE8, 0x005978D1, &CNewUIChatFontColor); //-- FontChat
	SetCompleteHook(0xE8, 0x005978F0, &CNewUIChatFontColor); //-- FontChat

	SetCompleteHook(0xE8, 0x00597939, &CNewUIChatPaintFont); //-- Font Notice
	SetCompleteHook(0xE8, 0x00597965, &CNewUIChatPaintFont); //-- Font Notice

	SetCompleteHook(0xE8, 0x00788C95, &CNewUIChatFontColor2); //-- FontColor 2
	SetCompleteHook(0xE8, 0x00788CDB, &CNewUIChatFontColor3); //-- FontColor 3
	SetCompleteHook(0xE8, 0x00788D1E, &CNewUIChatFontColor4); //-- FontColor 4
	SetCompleteHook(0xE8, 0x00788D67, &CNewUIChatFontColor1); //-- FontColor 1
	SetCompleteHook(0xE8, 0x00788DAD, &CNewUIChatFontColor5); //-- FontColor Party
	SetCompleteHook(0xE8, 0x00788DDC, &CNewUIChatFontColor6); //-- FontColor Guild
	SetCompleteHook(0xE8, 0x00788E22, &CNewUIChatFontColor6); //-- FontColor Guild
	SetCompleteHook(0xE8, 0x00788E68, &CNewUIChatFontColor7); //-- FontColor Alianza
	SetCompleteHook(0xE8, 0x00788EC5, &CNewUIChatFontColor8); //-- FontColor 8
	SetCompleteHook(0xE8, 0x00788EFE, &CNewUIChatFontColor9); //-- FontColor Gens
	SetCompleteHook(0xE8, 0x00788FF2, &CNewUIChatFontColor1); //-- FontColor default

	SetCompleteHook(0xE8, 0x007890ED, &CNewUIChatPaintFont); //-- FontChat system
	SetCompleteHook(0xE8, 0x007890A4, &CNewUIChatPaintFont); //-- FontChat normal
}