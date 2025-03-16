// GLFont.h: interface for the CUIPaintText class.
#pragma once

class CUIPaintText
{
public:
	CUIPaintText();
	virtual ~CUIPaintText();
	void Load();
	void ClearFontHdc();
	void CUIPreparedText();
	void SetFontHdc(HFONT font);
	void SetFontColor(GLfloat R, GLfloat G, GLfloat B, GLfloat Alpha);
	void CUIPaintFont(int DirPathX, int DirPathY, LPCSTR lpString, int DirPathW, int DirPathType);
public:
	HFONT hFont;
	HFONT hFontDefault;
	HFONT hFontBold;
	GLfloat ColorFont[4];
public:
	static int __thiscall CNewUIChatFontColor(int thisa, unsigned __int8 a2, unsigned __int8 a3, unsigned __int8 a4, unsigned __int8 a5);
	//static BYTE __thiscall CNewUIChatPrinft(int thisa);
	static int __thiscall CNewUIChatFontColor1(int thisa, unsigned __int8 a2, unsigned __int8 a3, unsigned __int8 a4, unsigned __int8 a5);
	static int __thiscall CNewUIChatFontColor2(int thisa, unsigned __int8 a2, unsigned __int8 a3, unsigned __int8 a4, unsigned __int8 a5);
	static int __thiscall CNewUIChatFontColor3(int thisa, unsigned __int8 a2, unsigned __int8 a3, unsigned __int8 a4, unsigned __int8 a5);
	static int __thiscall CNewUIChatFontColor4(int thisa, unsigned __int8 a2, unsigned __int8 a3, unsigned __int8 a4, unsigned __int8 a5);
	static int __thiscall CNewUIChatFontColor5(int thisa, unsigned __int8 a2, unsigned __int8 a3, unsigned __int8 a4, unsigned __int8 a5);
	static int __thiscall CNewUIChatFontColor6(int thisa, unsigned __int8 a2, unsigned __int8 a3, unsigned __int8 a4, unsigned __int8 a5);
	static int __thiscall CNewUIChatFontColor7(int thisa, unsigned __int8 a2, unsigned __int8 a3, unsigned __int8 a4, unsigned __int8 a5);
	static int __thiscall CNewUIChatFontColor8(int thisa, unsigned __int8 a2, unsigned __int8 a3, unsigned __int8 a4, unsigned __int8 a5);
	static int __thiscall CNewUIChatFontColor9(int thisa, unsigned __int8 a2, unsigned __int8 a3, unsigned __int8 a4, unsigned __int8 a5);

	static int __thiscall CNewUIChatPaintFont(int thisa, int PosX, int PosY, LPCTSTR Text, int nCount, int nTabPositions, int lpnTabStopPositions, int nTabOrigin);
};
extern CUIPaintText CFont;
