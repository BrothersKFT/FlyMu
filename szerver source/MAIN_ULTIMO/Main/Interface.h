#pragma once

#include "stdafx.h"
#include "import.h"
#include "Protect.h"

#define MAX_OBJECT 	400
#define MAX_WIN_WIDTH 640
#define MAX_WIN_HEIGHT 480
#define MAX_WINDOW_EX 100

#define pDrawInterfaceNumBer   ((double(__stdcall*)(float X, float Y, int num, float size)) 0x854FE0)

#define GMT (24 + (gProtect.m_MainInfo.TIME_GMT))

enum ObjectID
{
	eFlag01=1,
	eFlag02,
	eFlag03,
	eFlag04,
	eFlag05,
	eFlag06,
	eFlag07,
	eFlag08,
	eFlag09,
	eFlag10,
	eFlag11,
	eFlag12,
	eFlag13,
	eFlag14,
	eFlag15,
	eFlag16,
	eFlag17,
	eFlag18,
	eFlag19,
	eFlag20,
	eFlag21,
	eFlag22,
	eTIME,
	eRankPANEL_MAIN,
	eRanking,
	eSAMPLEBUTTON,
	eSAMPLEBUTTON2,
	eVip_MAIN,
	eVip_TITLE,
	eVip_FRAME,
	eVip_FOOTER,
	eVip_DIV,
	eVip_CLOSE,
	eVip_BRONZE,
	eVip_SILVER,
	eVip_GOLD,
	eVip_PLATINUM,
	eVip_STATUS,
	//--
	eMAIN_RANKING,
	//--
	eLogo,
	eEventTimePANEL_MAIN,
	eEventTime_MAIN,
	eEventTime_TITLE,
	eEventTime_CLOSE,
	eEventTime_FRAME,
	eEventTime_FOOTER,
	eMenu,
	eMenuBG,
	eMenu_MAIN,
	eMenu_MAIN2,
	eMenu_CLOSE,
	eMenu_OPT1,
	eMenu_OPT2,
	eMenu_OPT3,
	eMenu_OPT4,
	eMenu_OPT5,
	eMenu_OPT6,
	eMenu_OPT7,
	eMenu_OPT8,
	eMenu_OPT9,
	eMenu_OPT10,
	eMenu_OPT11,
	eCommand_MAIN,
	eCommand_TITLE,
	eCommand_FRAME,
	eCommand_FOOTER,
	eCommand_DIV,
	eCommand_CLOSE,
	eOFFTRADE_JoB,
	eOFFTRADE_JoS,
	eOFFTRADE_JoC,
	eOFFTRADE_WCC,
	eOFFTRADE_WCP,
	eOFFTRADE_WCG,
	eOFFTRADE_OPEN,
	//Minimap
	eNULL_MAP,
	ePLAYER_POINT,
	eCONFIRM_MAIN,
	eCONFIRM_BTN_OK,
	eCONFIRM_BTN_CANCEL,
	eCONFIRM_TITLE,
	eCONFIRM_FRAME,
	eCONFIRM_FOOTER,
	eCONFIRM_DIV,
	eNextCommand,
	ePrevCommand,
	eNextEvent,
	ePrevEvent,
//Ex700
	eMainEx700,
	eQuest,
	eCommunity,
	eSystem,
	//--custom
	eSTORE_CLOSE,
	ex_INFO_2,
	ex_INFO_3,
	eADVANCE_STAT_INFO,
	//--s2
	eMainS2right,
	eMainS2middle,
	eMainS2left,
	eSkillBox,
	eDragonLeft,
	eDragonRight,
	eCharacter,
	eInventory,
	eParty,
	eFriend,
	eFastMenu,
	eShop,
	eGuild,
	//--custom money
	eMoney1,
	eMoney2,
	CharacterSelect,
	CharacterSelect_Button1,
	CharacterSelect_Button2,
	CharacterSelect_Button3,
	CharacterSelect_Button4,
	CharacterSelect_Button5,
	CharacterSelect_Button6,
	CharacterSelect_Button7,
	CharacterCreate_Button1,
	CharacterCreate_Button2,
	CharacterCreate_Button3,
	CharacterCreate_Button4,
	CharacterCreate_Button5,
	CharacterCreate_Button6,
	CharacterCreate_Button7,
	CharacterCreate_SEND,
	CharacterCreate_CANCEL,
	//chat
	chatbackground,
	MINIMAP_FRAME,
	MINIMAP_TIME_FRAME,
	MINIMAP_BUTTOM,
	ButtonSettings,
	ButtonStart,
	ButtonStop,
	ButtonStartAttack,
	ButtonZenOff,
	ButtonCamera,
	eCamera3DInit,
	eCamera3DSwitch,
	strucMoveInv,
	eMainEx700Exp,
	RuudShopListIzq,
	RuudShopListDer,
	RuudShopWindow,
	RuudShopExit,
	eButtonRepair,
	eButtonAncient,
	eButtonSocket,
	eButtonRepairAll,
	eButtonRepairShop,
	eButtonStorage,
	eButtonInvExt,
	eButton1,
	eButton2,
	eButton3,
	eButton4,
	eButton5,
	//-- Button Option New
	eButtonOption1,
	eButtonOption2,
	eButtonOption3,
	eButtonOption4,
	eButtonOption5,
	eButtonOption6,
	eButtonOption7,
	eButtonOption8,
	eButtonOption9,
eCloseOption,
eJewelOfBank,
eJewelOfBankPush,
eJewelOfBankRemove,
eJewelOfBankClose,
#if (WARE==1)
eWAREHOUSE_MAIN,
eWAREHOUSE_CLOSE,
eWAREHOUSE_NUM1,
eWAREHOUSE_NUM2,
eWAREHOUSE_NUM3,
eWAREHOUSE_NUM4,
eWAREHOUSE_NUM5,
eWAREHOUSE_NUM6,
eWAREHOUSE_NUM7,
eWAREHOUSE_NUM8,
#endif
#if (JEWEL_BANK == 1)
eJEWELBANK_MAIN,
eJEWELBANK_TITLE,
eJEWELBANK_FRAME,
eJEWELBANK_FOOTER,
eJEWELBANK_POINT,
eJEWELBANK_LINE,
eJEWELBANK_DIV,
eJEWELBANK_CLOSE,
eJEWELBANK_PAGEUP1,
eJEWELBANK_PAGEUP2,
eJEWELBANK_PAGEUP3,
eJEWELBANK_PAGEUP4,
eJEWELBANK_PAGEUP5,
eJEWELBANK_PAGEUP6,
eJEWELBANK_PAGEUP7,
eJEWELBANK_PAGEUP8,
eJEWELBANK_PAGEUP9,
eJEWELBANK_PAGEUP10,
eJEWELBANK_PAGEUP11,
eJEWELBANK_PAGEDN1,
eJEWELBANK_PAGEDN2,
eJEWELBANK_PAGEDN3,
eJEWELBANK_PAGEDN4,
eJEWELBANK_PAGEDN5,
eJEWELBANK_PAGEDN6,
eJEWELBANK_PAGEDN7,
eJEWELBANK_PAGEDN8,
eJEWELBANK_PAGEDN9,
eJEWELBANK_PAGEDN10,
eJEWELBANK_PAGEDN11,
#endif
//party search
ePARTYSETTINGS_MAIN,
ePARTYSETTINGS_TITLE,
ePARTYSETTINGS_FRAME,
ePARTYSETTINGS_FOOTER,
ePARTYSETTINGS_DIV,
ePARTYSETTINGS_CLOSE,
ePARTYSETTINGS_SYSTEM_ACTIVE,
ePARTYSETTINGS_ONLY_GUILD,
ePARTYSETTINGS_ONE_CLASS,
ePARTYSETTINGS_DARK_WIZARD,
ePARTYSETTINGS_DARK_KNIGHT,
ePARTYSETTINGS_ELF,
ePARTYSETTINGS_MAGIC_GLADIATOR,
ePARTYSETTINGS_DARK_LORD,
ePARTYSETTINGS_SUMMONER,
ePARTYSETTINGS_RAGE_FIGHTER,
ePARTYSETTINGS_LEVEL_MINUS,
ePARTYSETTINGS_LEVEL_PLUS,
ePARTYSETTINGS_OK,
ePARTYSEARCH_LEFT,
ePARTYSEARCH_RIGHT,
ePARTYSEARCH_MAIN,
ePARTYSEARCH_TITLE,
ePARTYSEARCH_FRAME,
ePARTYSEARCH_FOOTER,
ePARTYSEARCH_DIV,
ePARTYSEARCH_CLOSE,
// change class
eCHANGE_MAIN,
eCHANGEDW_FINISH,
eCHANGEDK_FINISH,
eCHANGEELF_FINISH,
eCHANGEMG_FINISH,
eCHANGEDL_FINISH,
eCHANGESU_FINISH,
eCHANGERF_FINISH,
#if (RESETCHANGE == 1)
eRESETCHANGE,
eBOTON1,
eBOTON2,
eBOTON3,
eBOTON4,
eBOTON5,
#endif
eLuckyWheelMain,
eLuckyWheelStart,
eLuckyWheelPanel,
eLuckyWheel_CLOSE,
//--
ePT_PERSONAL_SEARCH_MAIN,
ePT_PERSONAL_SEARCH_TITLE,
ePT_PERSONAL_SEARCH_FRAME,
ePT_PERSONAL_SEARCH_FOOTER,
ePT_PERSONAL_SEARCH_DIV,
ePT_PERSONAL_SEARCH_CLOSE,
ePT_PERSONAL_SEARCH_L,
ePT_PERSONAL_SEARCH_R,
ePT_PERSONAL_SEARCH_PAGEUP1,
ePT_PERSONAL_SEARCH_PAGEUP2,
ePT_PERSONAL_SEARCH_PAGEUP3,
ePT_PERSONAL_SEARCH_PAGEUP4,
ePT_PERSONAL_SEARCH_PAGEUP5,
ePT_PERSONAL_SEARCH_PAGEUP6,
ePT_PERSONAL_SEARCH_PAGEUP7,
ePT_PERSONAL_SEARCH_PAGEUP8,
ePT_PERSONAL_SEARCH_PAGEUP9,
ePT_PERSONAL_SEARCH_PAGEUP10,
//--
#if (ARCHIVEMENT == 1)
OBJECT_ACHIEVEMENTS_MAIN,
OBJECT_ACHIEVEMENTS_PROGRESS_BG,
OBJECT_ACHIEVEMENTS_PANEL,
OBJECT_ACHIEVEMENTS_CLOSE,
OBJECT_ACHIEVEMENTS_MISSIONS,
OBJECT_ACHIEVEMENTS_DAMAGE,
OBJECT_ACHIEVEMENTS_DEFENSE,
OBJECT_ACHIEVEMENTS_LIFE,
OBJECT_ACHIEVEMENTS_EXCELLENT,
OBJECT_ACHIEVEMENTS_CRITICAL,
#endif
//Smith
eSMITH_MAIN,
eSMITH_TITLE,
eSMITH_FRAME,
eSMITH_FOOTER,
eSMITH_DIV,
eSMITH_CLOSE,
eSMITH_BUY,
//controll -
eSMITH_ITEMTYPE,
eSMITH_ITEMINDEX,
eSMITH_LEVEL,
eSMITH_SKILL,
eSMITH_LUCK,
eSMITH_OPT,
eSMITH_EXC,
eSMITH_EXC1,
eSMITH_EXC2,
eSMITH_EXC3,
eSMITH_EXC4,
eSMITH_EXC5,
eSMITH_DAYS,
//controll +
eSMITH_ITEMTYPE_1,
eSMITH_ITEMINDEX_1,
eSMITH_LEVEL_1,
eSMITH_SKILL_1,
eSMITH_LUCK_1,
eSMITH_OPT_1,
eSMITH_EXC_1,
eSMITH_EXC1_1,
eSMITH_EXC2_1,
eSMITH_EXC3_1,
eSMITH_EXC4_1,
eSMITH_EXC5_1,
eSMITH_DAYS_1,
eUNCHECK_1,
eUNCHECK_2,
eUNCHECK_3,
eUNCHECK_4,
eUNCHECK_5,
eUNCHECK_6,
eCHECKED_1,
eCHECKED_2,
eCHECKED_3,
eCHECKED_4,
eCHECKED_5,
eCHECKED_6,
// ---
OBJECT_WIN_QUEST_MAIN,
OBJECT_WIN_QUEST_TITLE,
OBJECT_WIN_QUEST_FRAME,
OBJECT_WIN_QUEST_FOOTER,
OBJECT_WIN_QUEST_DIV,
OBJECT_WIN_QUEST_CLOSE,
OBJECT_WIN_QUEST_TAB,
OBJECT_WIN_QUEST_TAB1,
OBJECT_WIN_QUEST_TAB2,
OBJECT_WIN_QUEST_TAB3,
OBJECT_WIN_QUEST_FINISH,
OBJECT_WIN_QUEST_COUNT1,
OBJECT_WIN_QUEST_COUNT2,
OBJECT_WIN_QUEST_COUNT3,
OBJECT_WIN_QUEST_INFOBG,
OBJECT_WIN_QUEST_INFOBG2,
OBJECT_WIN_QUEST_LINE1,
OBJECT_WIN_QUEST_POINT1,
OBJECT_WIN_QUEST_INFO,
OBJECT_WIN_QUEST_INFOBG3,
OPEN_QUEST,

OBJECT_RESET_MAIN,
OBJECT_RESET_TITLE,
OBJECT_RESET_FRAME,
OBJECT_RESET_FOOTER,
OBJECT_RESET_DIV,
OBJECT_RESET_INFO_BG,
OBJECT_RESET_MONEY_BG,
OBJECT_RESET_CLOSE,
OBJECT_RESET_FINISH,
OBJECT_GRESET_MAIN,
OBJECT_GRESET_TITLE,
OBJECT_GRESET_FRAME,
OBJECT_GRESET_FOOTER,
OBJECT_GRESET_DIV,
OBJECT_GRESET_INFO_BG,
OBJECT_GRESET_MONEY_BG,
OBJECT_GRESET_CLOSE,
OBJECT_GRESET_FINISH,
};

enum InterfaceID
{
	iOptionDot = 0x7B68,
	iOptionCheck = 0x7B69,
};

struct InterfaceElement
{
	DWORD	ModelID;
	float	Width;
	float	Height;
	float	X;
	float	Y;
	float	MaxX;
	float	MaxY;
	DWORD	EventTick;
	bool	OnClick;
	bool	OnShow;
	BYTE	Attribute;
	long	OpenedValue;
	BYTE	Speed;
	char	StatValue[20];
	bool	ByClose;
	bool	FirstLoad;

	void Open()
	{
		this->OnShow = true; pSetCursorFocus = true;
		this->ByClose = false;
	};

	void Open(int Value, int Speed)
	{
		this->OnShow = true; pSetCursorFocus = true;
		this->OpenedValue = Value;
		this->Speed = Speed;
		this->ByClose = false;
		this->FirstLoad = true;
	};

	void Close()
	{
		this->OnShow = false;
		pSetCursorFocus = false;
		this->ByClose = false;
	};

	void Close(int Value, int Speed)
	{
		this->OnShow = false; pSetCursorFocus = false;
		this->OpenedValue = Value;
		this->Speed = Speed;
		this->ByClose = false;
	}

	void CloseAnimated(int Speed)
	{
		pSetCursorFocus = false;
		this->Speed = Speed;
		this->ByClose = true;
	}

	bool Check()
	{
		return this->OnShow;
	}
};

class Interface
{
public:
	int ConfirmSlot;
	float PetY;
	float PetX;
	int lastReport;
	int frameCount;
	int frameRate;
	char FPS_REAL[30];
	void UPDATE_FPS();
	void guiMonitore();
	int iniciador;
	int msPing;
	int lastSend;
	int validar;
	char ServerPing[50];
	char ultimoPing[50];
	int ultimo_Ping;
	char ServerRTT[50];
	char ultimoRTT[50];
	int ultimo_RTT;
	DWORD  ClickTime;
	InterfaceElement Data[MAX_OBJECT];
public:
	Interface();
	virtual ~Interface();
	void RenderObjectSystem();
	static void LoadImages();
	static void LoadModels();
	static void Work();
//-- System Windows
	void OpenVipWindow(){ this->Data[eVip_MAIN].OnShow = true; };
	void CloseVipWindow() { this->Data[eVip_MAIN].OnShow = false; }
	bool CheckVipWindow() { return this->Data[eVip_MAIN].OnShow; };
	void DrawVipWindow();
	bool EventVipWindow_Main(DWORD Event);
	bool EventVipWindow_Close(DWORD Event);
	bool EventVipWindow_Bronze(DWORD Event);
	bool EventVipWindow_Silver(DWORD Event);
	bool EventVipWindow_Gold(DWORD Event);
	bool EventVipWindow_Platinum(DWORD Event);
	bool EventVipWindow_StatusVip(DWORD Event);
	//--
	void DrawMenu();
	bool EventDrawMenu_Open(DWORD Event);
	void OpenMenuWindow() { this->Data[eMenu_MAIN].OnShow = true; };
	void CloseMenuWindow() {this->Data[eMenu_MAIN].OnShow = false; };
	bool CheckMenuWindow() { return this->Data[eMenu_MAIN].OnShow; };
	void OpenMenu2Window() { this->Data[eMenu_MAIN2].OnShow = true; };
	void CloseMenu2Window() { this->Data[eMenu_MAIN2].OnShow = false; };
	bool CheckMenu2Window() { return this->Data[eMenu_MAIN2].OnShow; };
	void DrawMenuOpen();
	void DrawMenu2Open();
	bool EventDrawMenu_Close(DWORD Event);
	bool EventDrawMenu2_Close(DWORD Event);
	bool EventDrawMenu_Next(DWORD Event);
	bool EventDrawMenu_Back(DWORD Event);
	bool EventDrawMenu_Op1(DWORD Event);
	bool EventDrawMenu_Op2(DWORD Event);
	bool EventDrawMenu_Op3(DWORD Event);
	bool EventDrawMenu_Op4(DWORD Event);
	bool EventDrawMenu_Op20(DWORD Event);
	bool EventDrawMenu_Op6(DWORD Event);
	bool EventDrawMenu_Op7(DWORD Event);
	bool EventDrawMenu_Op8(DWORD Event);
	bool EventDrawMenu_Op9(DWORD Event);
	bool EventDrawMenu_Op10(DWORD Event);
	bool EventDrawMenu_Op11(DWORD Event);
	//--
	void DrawConfirmOpen();
	bool EventConfirm_OK(DWORD Event);
	bool EventConfirm_CANCEL(DWORD Event);
//-- Funtions
	void BindObject(short ObjectID, DWORD ModelID, float Width, float Height, float X, float Y);
	void DrawGUI(short ObjectID, float PosX, float PosY);
	void DrawGUI2(short ObjectID, float PosX, float PosY);
	void DrawGUI3(short ObjectID, float PosX, float PosY, float ScaleX, float ScaleY);
	void DrawTimeUI();
	int DrawFormat(DWORD Color, int PosX, int PosY, int Width, int Align, LPCSTR Text, ...);
	void DrawIMG(short ObjectID, float PosX, float PosY, float ScaleX, float ScaleY);
	void DrawWindow(int ObjMain, int ObjTitle, int ObjFrame, int ObjFooter, int Repeat, float X, float Y, char* Text);
	bool ButtonEx(DWORD Event, int ButtonID, bool Type);
	void ResetDrawIMG(short ObjectID);
	int DrawMessage(int Mode, LPCSTR Text, ...);
	void DrawItemIMG(float PosX, float PosY, float Width, float Height, int ItemID, int Level, int Excl, int Anc, bool OnMouse);
	bool CheckWindow(int WindowID);
	bool CheckWindowzx(int WindowID);
	int CloseWindow(int WindowID);
	int OpenWindow(int WindowID);
	bool IsWorkZone2(float X, float Y, float MaxX, float MaxY);
	bool IsWorkZone(short ObjectID);
	bool	IsWorkZone(float X, float Y, float MaxX, float MaxY, bool a5 = false);
	float GetResizeX(short ObjectID);
	int DrawToolTip(int X, int Y, LPCSTR Text, ...);
	float DrawRepeatGUI(short MonsterID, float X, float Y, int Count);
	float DrawRepeatGUIScale(short MonsterID, float X, float Y,float ScaleX, float ScaleY, int Count);
	void DrawColoredGUI(short ObjectID, float X, float Y, DWORD Color);
	void DrawButton(short ObjectID, float PosX, float PosY, float ScaleX, float ScaleY);
	void DrawButtonRender(short ObjectID, float PosX, float PosY, float ScaleX, float ScaleY);
	void DrawColoredButton(short ObjectID, float PosX, float PosY, float ScaleX, float ScaleY, DWORD Color);
	int  DrawFormatx(DWORD Color, int PosX, int PosY, int Width, int Align, LPCSTR Text, ...);
	void	PartUPandDNEx(int PointID, int UpID, int DownID, int LineID, float X, float Y, DWORD Color, int Value, char* Text);
	void TextDraw(int PosX, int PosY, int Width, int Arg5, int Color, int Arg7, int Align, HGDIOBJ Font, LPCTSTR Format, ...);
	void	DrawCheckLineEx(bool isChecked, int PointID, int CheckID, int LineID, float X, float Y, DWORD Color, char* Text);
	void	MiniButtonDraw(int BtnID, float X, float Y, bool isHover, char* Text);
	void DrawLogo(bool active);
	void CloseCustomWindow();
	//Mini Map
	void DrawMiniMap();
//	void DrawRadar();
	bool MiniMapCheck();
	bool CombinedChecks();
	bool CheckMap();
	void SwitchMiniMap();
	void		RadarMini();
	// ex700
	void DrawInterfaceCustom();
	// s2
	void DrawInterfaceS2Menu();
	void DrawInterface97Menu();
	void EventNewInterface_All(DWORD Event);
	void EventNewInterface97_All(DWORD Event);
	void DrawCoord();
	void DrawInterfaceDragonLS3();
	void DrawInterfaceDragonRS3();
	// Advanced Stats
	bool WindowEx[MAX_WINDOW_EX];
	bool CheckWindowEx(int WindowID);
	void		OpenWindowEx(int WindowID);
	bool CheckWindowEx2(int WindowID);
	void		CloseWindowEx(int WindowID);
	void DrawBarForm(float PosX,float PosY,float Width,float Height,GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
	//--
	void OpenConfig(int type);
	void SwitchCamera();
	void SwitchChatExpand();
	void CameraInit();
	bool Button(DWORD Event, int WinID, int ButtonID, bool Type);
	void DrawPing();
	void SendPingRecv();

	static void DrawZenAndRud(int a1, int a2, int a3, int a4);

	// party search
	void		DrawPartySettingsWindow();
	void		SwitchPartySettingsWindowState() { (Data[ePARTYSETTINGS_MAIN].OnShow == true) ? Data[ePARTYSETTINGS_MAIN].Close() : Data[ePARTYSETTINGS_MAIN].Open(); };
	bool		EventPartySettingsWindow_Main(DWORD Event);
	bool		EventPartySettingsWindow_Close(DWORD Event);
	bool		EventPartySettingsWindow_All(DWORD Event);
	void		DrawPartySearchWindow();
	void		SwitchPartySearchWindowState() { (Data[ePARTYSEARCH_MAIN].OnShow == true) ? Data[ePARTYSEARCH_MAIN].Close() : Data[ePARTYSEARCH_MAIN].Open(); };
	void		EventPartySearchWindow_All(DWORD Event);
	//Lucky Wheel
	void		DrawLuckyWheel();
	void		EventLuckyWheel_Main(DWORD Event);
	void        EventLuckyWheelWindow_Close(DWORD Event);
	void		LuckyWheelState(){ (Data[eLuckyWheelMain].OnShow == true) ? Data[eLuckyWheelMain].Close() : Data[eLuckyWheelMain].Open(); };
	void		LuckyWheelStateclose() { Data[eLuckyWheelMain].OnShow = false; pSetCursorFocus = false; };
	int			LuckyWheelNumber;
	DWORD		LuckyWheelTime;
	int			StartRoll;

	void		DrawText(DWORD Color, int PosX, int PosY, int Width, int Align, LPCSTR Text, ...);
	void TextDrawx(int PosX, int PosY, int Width, int Arg5, int Color, int Arg7, int Align, HGDIOBJ Font, LPCTSTR Format, ...);
	void		DrawMessageBox(LPCSTR Text, ...);
	//-- Party Bar ex700
	void		BarPartyNew();

private:
	
};
extern Interface gInterface;
