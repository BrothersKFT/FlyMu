#include "stdafx.h"
#include "resource.h"
#include "Main.h"
#include "..\\..\\Util\\CCRC32.H"
#include "Common.h"
#include "Controller.h"
#include "CustomBuyVip.h"
#include "CustomCommandInfo.h"
#include "CustomEventTime.h"
#include "CustomItem.h"
#include "CustomJewel.h"
#include "CustomMap.h"
#include "CustomMonster.h"
#include "CustomNpcName.h"
#include "CustomWing.h"
#include "Fix.h"
#include "StaticEffect.h"
#include "DynamicEffect.h"
#include "HackCheck.h"
#include "HealthBar.h"
#include "Item.h"
#include "ItemShopValue.h" 
#include "ItemSmoke.h"
#include "Interface.h"
#include "OffTrade.h"
#include "PacketManager.h"
#include "PrintPlayer.h"
#include "Protect.h"
#include "Protocol.h"
#include "Reconnect.h"
#include "Resolution.h"
#include "User.h"
#include "Util.h"
#include "TMemory.h"
//--
#include "InterEx.h"
#include "SelectChar.h"
#include "postInterface.h"
#include "StatsAdvance.h"
#include "CustomBow.h"
#include "CustomGloves.h"
#include "CustomPet.h"
#include "Pet.h"
#include "PetHook.h"
#include "CustomCloak.h"
#include "cape.h"
#include "ItemTRSData.h"
#include "CustomEffectRemake.h"
#include "ItemRemake.h"
#include "ItemManager.h"
#include "ItemInfoEx.h"
#include "CSCharacterS13.h"
#include "CustomItemPrice.h"
#include "MonsterGlow.h"
#include "CustomMonsterGlow.h"
#include "ModelEffect.h"
#include "CChatEx.h"
#include "CustomPetEffect.h"
#include "CChatClassic.h"
#include "CMacroUIEx.h"
#include "TrayModeNew.h"
#include "MiniMap.h"
#include "Radar.h"
#include "WindowsStruct.h"
#include "SItemOption.h"
#include "ItemTooltip.h"
#include "PetMontura.h"
#include "Central.h"
#include "BuffIcon.h"
#include "MuHelper.h"
#include "PartyBar.h"
//--
//#include "Ruud.h"
#include "Inter3.h"
#include "CChatClassic.h"
#include "cCPetRenderMesh.h"
#include "MultiSelect.h"
#include "InfoLog.h"
#include "ItemTooltip.h"
#include "RenderSkillDarkhorse.h"

#include "ConnectServer.h"
#include "ServerInfo.h"
#include "GetBarChat.h"
#include "GLFont.h"
#include "SmithItem.h"

#include "test.h"
#include "proah..h"
#include "SceneCreate.h"

HINSTANCE hins;

void StartAddress(LPVOID lpThreadParameter)
{
	HANDLE v1;
	HANDLE v2;

	while ( TRUE )
	{
		Sleep(5000);

		v1 = GetCurrentProcess();
		SetProcessWorkingSetSize(v1, 0xFFFFFFFF, 0xFFFFFFFF);

		v2 = GetCurrentProcess();
		SetThreadPriority(v2, -2);
	}
}

__declspec(naked) void OffButtonQuestInStats()
{
	static DWORD ButtonAddress = 0x0077EBB5;
	_asm{jmp ButtonAddress}
}

__declspec(naked) void OffButtonPetsInStats()
{
	static DWORD ButtonAddress = 0x0077EC5E;
	_asm{jmp ButtonAddress}
}

__declspec(naked) void OffButtonSkillMasterInStats()
{
	static DWORD ButtonAddress = 0x0077ECE7;
	_asm{jmp ButtonAddress}
}

__declspec(naked) void OffButtonInventoryExt()
{
	static DWORD ButtonAddress = 0x00836A28;
	_asm{jmp ButtonAddress}
}

__declspec(naked) void OffButtonOpenStore()
{
	static DWORD ButtonAddress = 0x008369B4;
	_asm{jmp ButtonAddress}
}
__declspec(naked) void OffButtonRepeirInInventory()
{
	static DWORD ButtonAddress = 0x00836941;
	_asm{jmp ButtonAddress}
}

extern "C" _declspec(dllexport) void EntryProc() // OK
{
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)StartAddress, 0, 0, 0);

	if(gProtect.ReadMainFile("Data\\Local\\system.zx") == 0)
	{
		MessageBox(0,"Data\\Local\\system.zx corrupt!","Error",MB_OK | MB_ICONERROR);
		ExitProcess(0);
	}

	if(gProtect.ReadTooltipTRSData( "Data\\Local\\TooltipTRSData.bmd" ) == 0)
	{
		MessageBox(0, "Data\\Local\\TooltipTRSData.bmd missing or File corrupt!" ,"Error", MB_OK | MB_ICONERROR);
		ExitProcess(0);
	}

	if(gProtect.ReadMakeViewTRSData("Data\\Local\\MakeWorldTRSData.bmd") == 0)
	{
		MessageBox(0,"Data\\Local\\MakeWorldTRSData.bmd missing or File corrupt!","Error", MB_OK | MB_ICONERROR);
		ExitProcess(0);
	}

	if(gProtect.ReadPetEffectBMD("Data\\Local\\EffectTRSData.bmd") == 0)
	{
		MessageBox(0,"Data\\Local\\EffectTRSData.bmd missing or File corrupt!","Error", MB_OK | MB_ICONERROR);
		ExitProcess(0);
	}


//	gInfoLog.Load();
	SetByte(0x00E61144,0xA0); // Accent
	SetByte(0x004D1E69,0xEB); // Crack (mu.exe)
	SetByte(0x004D228D,0xE9); // Crack (GameGuard)
	SetByte(0x004D228E,0x8B); // Crack (GameGuard)
	SetByte(0x004D228F,0x00); // Crack (GameGuard)
	SetByte(0x004D2290,0x00); // Crack (GameGuard)
	SetByte(0x004D2291,0x00); // Crack (GameGuard)
	SetByte(0x004D559C,0xEB); // Crack (ResourceGuard)
	SetByte(0x00633F7A,0xEB); // Crack (ResourceGuard)
	SetByte(0x00634403,0xEB); // Crack (ResourceGuard)
	SetByte(0x0063E6C4,0xEB); // Crack (ResourceGuard)
	SetByte(0x004D2246,0xEB); // Crack (ResourceGuard)
	SetByte(0x00501163,0xEB); // Crack (ResourceGuard)
	SetByte(0x0040AF0A,0x00); // Crack (ResourceGuard)
	SetByte(0x0040B4BC,0x50); // Login Screen
	SetByte(0x0040B4C5,0x50); // Login Screen
	SetByte(0x0040B4CF,0x18); // Login Screen
	SetByte(0x0040AF0A,0x00); // Login Screen
	SetByte(0x0040AFD5,0xEB); // Login Screen
	SetByte(0x00777FD6,0x70); // Item Text Limit
	SetByte(0x00777FD7,0x17); // Item Text Limit
	SetByte(0x004EBEC7,0x3C); // Item Text Limit
	SetByte(0x005C4004,0x3C); // Item Text Limit
	SetByte(0x007E40BB,0x3C); // Item Text Limit
	SetByte(0x0081B546,0x3C); // Item Text Limit
	SetByte(0x0081B58D,0x3C); // Item Text Limit
	SetByte(0x0086E284,0x3C); // Item Text Limit
	SetByte(0x0086E44C,0x3C); // Item Text Limit
	SetByte(0x0086E573,0x3C); // Item Text Limit
	SetByte(0x0086F8FC,0x3C); // Item Text Limit
	SetByte(0x007DA373,0xB7); // Item Type Limit
	SetByte(0x007E1C44,0xB7); // Item Type Limit
	SetByte(0x0052100D,0xEB); // Ctrl Fix
	SetByte(0x009543C4,0x00); // Move Vulcanus
	SetCompleteHook(0xE9, 0x004D1CF0, 0x004D1DC2); //-- Remoce MuError.DMP
	MemorySet(0x00D20170, 0x90, 0x1B); //-- Remove Creation MuError.log
	SetByte(0x0064CBD1,((gProtect.m_MainInfo.HelperActiveAlert==0) ? 0xEB : 0x75)); //-- Helper Message Box
	SetByte(0x0064CBD0,(BYTE)gProtect.m_MainInfo.HelperActiveLevel); //-- Helper Active Level
	SetByte(0x0095CEEF,(BYTE)gProtect.m_MainInfo.HelperActiveLevel); //-- Helper Active Level
	SetByte(0x0095CF14,(BYTE)gProtect.m_MainInfo.HelperActiveLevel); //-- Helper Active Level
	SetByte(0x00E61F68,(gProtect.m_MainInfo.ClientVersion[0]+1)); //-- Version
	SetByte(0x00E61F69,(gProtect.m_MainInfo.ClientVersion[2]+2)); //-- Version
	SetByte(0x00E61F6A,(gProtect.m_MainInfo.ClientVersion[3]+3)); //-- Version
	SetByte(0x00E61F6B,(gProtect.m_MainInfo.ClientVersion[5]+4)); //-- Version
	SetByte(0x00E61F6C,(gProtect.m_MainInfo.ClientVersion[6]+5)); //-- Version
	SetWord(0x00E609E4,(gProtect.m_MainInfo.IpAddressPort)); //-- IpAddressPort
	SetDword(0x004D9D3B,(DWORD)&FrameValue);
	SetDword(0x004DAC60,(DWORD)&FrameValue);
	SetDword(0x7B55338,(DWORD)10);
	SetDword(0x004D597B,(DWORD)&MainTickCount);
	SetDword(0x004DA289,(DWORD)&MainTickCount);
	SetDword(0x004DA297,(DWORD)&MainTickCount);
	SetDword(0x004DA3A2,(DWORD)&MainTickCount);
	SetDword(0x004DA3CE,(DWORD)&MainTickCount);
	SetDword(0x004DA3D9,(DWORD)&MainTickCount);
	SetDword(0x0063D326,(DWORD)&MainTickCount);
	SetDword(0x00642112,(DWORD)&MainTickCount);
	SetDword(0x004D0E09,(DWORD)gProtect.m_MainInfo.WindowName);
	SetDword(0x004D9F55,(DWORD)gProtect.m_MainInfo.ScreenShotPath);

	SetDword(0x00954148 + 1, (DWORD)gProtect.m_MainInfo.ServerName1); //-> (Gold)
	SetDword(0x00954115 + 1, (DWORD)gProtect.m_MainInfo.ServerName2); //-> (Gold PVP)
	SetDword(0x009540E2 + 1, (DWORD)gProtect.m_MainInfo.ServerName3); //-> (Non-PVP)
	SetDword(0x009540AC + 1, (DWORD)gProtect.m_MainInfo.ServerName4); //-> Sem Nada

	SetCompleteHook(0xE9, 0x0095DFBE, 0x0095DFD3);

	MemorySet(0x0063E908,0x90,20); //-- C1:F3:04

	SetCompleteHook(0xE9,0x0064452A,0x00644537); //-- Fix montura

	SetCompleteHook(0xE9, 0x0071AE92, 0x00720894); //Fix RF Skill	SetCompleteHook(0xE9, 0x0071B1A3, 0x00720894); //Fix RF Skill

	SetCompleteHook(0xE9, 0x005880F0, 0x0058811F); //Fix gm wing on Blood castle
	SetDword(0x00588444 + 3, 4095);

	MemoryCpy(0x00E611B2,gProtect.m_MainInfo.IpAddress,sizeof(gProtect.m_MainInfo.IpAddress)); //-- IpAddress

	MemoryCpy(0x00E61F70,gProtect.m_MainInfo.ClientSerial,sizeof(gProtect.m_MainInfo.ClientSerial)); //-- ClientSerial

	SetCompleteHook(0xFF,0x0065FD79,&ProtocolCoreEx);

	SetCompleteHook(0xE9,0x004DA280,&CheckTickCount1);

	SetCompleteHook(0xE9,0x004DA3A1,&CheckTickCount2);
#if (HPTYPE==1)
	SetCompleteHook(0xE8, 0x005B96E8, &AllInOne);
#else
	SetCompleteHook(0xE8,0x005B96E8,&DrawNewHealthBar);
#endif
	VirtualizeOffset(0x004D9D39,12);

	VirtualizeOffset(0x004D9D45,7);

	VirtualizeOffset(0x004D9EFC,15);

	VirtualizeOffset(0x004DAC5C,8);

	VirtualizeOffset(0x005451F7,5);

	VirtualizeOffset(0x00545230,8);

	VirtualizeOffset(0x005A52E9,8);

	LoadReferenceAddressTable((HMODULE)hins, MAKEINTRESOURCE(IDR_BIN1),(DWORD)&NewAddressData1);

	LoadReferenceAddressTable((HMODULE)hins, MAKEINTRESOURCE(IDR_BIN2),(DWORD)&NewAddressData2);

	LoadReferenceAddressTable((HMODULE)hins, MAKEINTRESOURCE(IDR_BIN3),(DWORD)&NewAddressData3);

	gCustomMessage.LoadEng(gProtect.m_MainInfo.EngCustomMessageInfo);

	gCustomMessage.LoadPor(gProtect.m_MainInfo.PorCustomMessageInfo);

	gCustomMessage.LoadSpn(gProtect.m_MainInfo.SpnCustomMessageInfo);

	gCustomJewel.Load(gProtect.m_MainInfo.CustomJewelInfo);

	gCustomWing.Load(gProtect.m_MainInfo.CustomWingInfo);

	gCustomItem.Load(gProtect.m_MainInfo.CustomItemInfo);

	gCustomBuyVip.Load(gProtect.m_MainInfo.CustomBuyVipInfo);

	gCustomCommandInfo.Load(gProtect.m_MainInfo.CustomCommandInfo);

	gCustomEventTime.Load(gProtect.m_MainInfo.CustomEventInfo);

	gFog.Load(gProtect.m_MainInfo.CustomFog);

	gSmokeEffect.Load(gProtect.m_MainInfo.CustomSmokeEffect);

	gCustomMonster.Load(gProtect.m_MainInfo.CustomMonsters);

	gNPCName.Load(gProtect.m_MainInfo.CustomNPCName);
	//--
	gCustomBattleGloves.Load(gProtect.m_MainInfo.CustomGloves);

	gCustomBow.Load(gProtect.m_MainInfo.CustomBowInfo);

	gCustomPet2.Load(gProtect.m_MainInfo.CustomPetInfo);

	gCloak.Load(gProtect.m_MainInfo.m_CustomCloak);

	ItemTRSData.Load(gProtect.m_MainInfo.CustomPosition);

	gCustomRemake.Load(gProtect.m_MainInfo.CustomRemake);

	gItemManager.Load(gProtect.m_MainInfo.m_ItemInfoEx);

	gCustomModelEffect.Load(gProtect.m_MainInfo.m_CustomModelInfo);
	//--
	gCustomCEffectPet.Load(gProtect.m_ReadBMD.m_PetCEffectBMD);

	gCustomWingEffect.Load(gProtect.m_ReadBMD.CustomWingEffectInfo);

	gDynamicWingEffect.Load(gProtect.m_ReadBMD.DynamicWingEffectInfo);

	cRender.Load(gProtect.m_ReadBMD.RenderMeshPet);

	gCustomMonsterGlow.LoadGlow(gProtect.m_ReadBMD.m_CustomMonsterGlow);

	gCustomMonsterGlow.LoadBrightness(gProtect.m_ReadBMD.m_CustomMonsterbrightness);

	JCEffectMonster.Load(gProtect.m_ReadBMD.m_CustomMonsterEffect);
//--
	gIconBuff.LoadEng(gProtect.m_ReadTooltipTRSData.m_TooltipTRSDataEng);
	
	gIconBuff.LoadSpn(gProtect.m_ReadTooltipTRSData.m_TooltipTRSDataSpn);
	
	gIconBuff.LoadPor(gProtect.m_ReadTooltipTRSData.m_TooltipTRSDataPor);

	GInfo.loadnInformation( gProtect.m_ReadTooltipTRSData.m_TRSTooltipData );

	GInfo.loadnText( gProtect.m_ReadTooltipTRSData.m_TRSTooltipText );

	gLuckyWheel.Load(gProtect.m_MainInfo.CustomLuckyWheel);

	if (gProtect.m_MainInfo.CustomEffectEarthQuake == 1)
	{
		gCustomEarthQuake.Load(gProtect.m_ReadBMD.m_EarthQuakeLoad);
	}
//--
#if UPDATE >= 15
	gSelectCharRamdon.LoadMultiChar(gProtect.m_MakeViewTRSData.m_RenderSelect);
#endif

	gCustomSmith.LoadSword(gProtect.m_MainInfo.SmithSwordInfo);
	gCustomSmith.LoadAxe(gProtect.m_MainInfo.SmithAxeInfo);
	gCustomSmith.LoadMace(gProtect.m_MainInfo.SmithMaceInfo);
	gCustomSmith.LoadSpear(gProtect.m_MainInfo.SmithSpearInfo);
	gCustomSmith.LoadBow(gProtect.m_MainInfo.SmithBowInfo);
	gCustomSmith.LoadStaff(gProtect.m_MainInfo.SmithStaffInfo);
	gCustomSmith.LoadShield(gProtect.m_MainInfo.SmithShieldInfo);
	gCustomSmith.LoadHelm(gProtect.m_MainInfo.SmithHelmInfo);
	gCustomSmith.LoadArmor(gProtect.m_MainInfo.SmithArmorInfo);
	gCustomSmith.LoadPant(gProtect.m_MainInfo.SmithPantInfo);
	gCustomSmith.LoadGlove(gProtect.m_MainInfo.SmithGloveInfo);
	gCustomSmith.LoadBoot(gProtect.m_MainInfo.SmithBootInfo);

	gMonsterHpBar.Load(gProtect.m_MainInfo.CustomHpBar);
	gNoShadow.Load(gProtect.m_ReadBMD.m_ShadowInfo);
//--
	gPacketManager.LoadEncryptionKey("Data\\Enc1.dat");

	gPacketManager.LoadDecryptionKey("Data\\Dec2.dat");

	gProtect.CheckLauncher();

	gProtect.CheckInstance();

	gProtect.CheckClientFile();

	gProtect.CheckHackFile();

	gProtect.CheckPluginFile1();

	gProtect.CheckPluginFile2();

	gProtect.CheckPluginFile3();

	gProtect.CheckPluginFile4();

	gProtect.CheckPluginFile5();

	gProtect.CheckCameraFile();

	InitHackCheck();

	gTrayMode.Load();

	InitCommon();

	GetPartyBar.Load();

#if(IN_DEV ==1)
		ConnectServer.Load();
		g_ServerInfo.Load();
#endif

	gCentral.InitCentral();//-- Control: camara||mouse 

	gItemInfoEx.Load();

	if(gProtect.m_MainInfo.SelectCharAnimate == 1)
	{
		gSelectChar.Load();
	}

	#if UPDATE >= 15
	gSelectCharRamdon.InitMultiChar();
	#endif

	if(gProtect.m_MainInfo.SelectCharS13 == 1)
	{
		gCSCharacterS13.Load();
	}

	ItemTRSData.Init();

	if(gProtect.m_MainInfo.DisableCustomCloack == 0)
	{
		gCapeAnimation.Load();
	}

	if(gProtect.m_MainInfo.DisableCustomPet == 0)
	{
		gCustomPet.Load();

		gObjCreatePetExHook();

		gCustomCEffectPet.Init();

		initmontura();
	}

	if (gProtect.m_MainInfo.MiniMapType == 1)
	{
		gRenderMap.MiniMapload();
	}

	if (gProtect.m_MainInfo.MiniMapType == 2)
	{
		JCGetMinimap.Load();
	}

	InitItem();

	InitJewel();

	InitPrintPlayer();

	InitReconnect();

	InitResolution();

	gController.Load();

	InitWing();

	gObjUser.Load();

	gInterface.RenderObjectSystem();

	gCMacroUIEx.Load();

	gMuHelper.LoadHelper();

	switch(gProtect.m_MainInfo.CustomInterfaceType)
	{
		case 1:
		case 2:
			InitInter3();
			gCChatClassic.Load();
			break;
		case 3:
		case 4:
			InitSeason15();
			gCRenderEx700.Init();
			gCChatEx.Load();
			CFont.Load();
			break;
	}

	JCGetModelBarChat.Load();
	
	if(gProtect.m_MainInfo.DisableAdvance == 0)
	{
		g_StatsAdvance.Load();	//<-- Advanced
	}
	gOffTrade.Init();

	gFog.Init();

	if(gProtect.m_MainInfo.CustomMonsterEnable == 1)
	{
		gCustomMonster.InitMonster();
	}

	InitloadGlow();

	if(gProtect.m_MainInfo.DisableCustomBow == 0)
	{
		gCustomBow.Init();
	}

	if(gProtect.m_MainInfo.DisableCustomClaws == 0)
	{
		gCustomBattleGloves.Init();
	}

	gCustomMap.Load();

	if(gProtect.m_MainInfo.EnableShopValueSystem == 1)
	{
		gItemPrice.Init();
	}

	if (gProtect.m_MainInfo.CustomEffectEarthQuake == 1){
		gCustomEarthQuake.LoadRenderSkill();
	}

	gTest.InitTest();
#if OFF
	JCGetScene.Load();
#endif
	if(gProtect.m_MainInfo.CsSkill == 1)
	{
		//Liberar CS Skills
		SetByte((0x005B89C3+3), 0x00);
		SetByte((0x005B89C9+3), 0x00);
		SetByte((0x005B89CF+3), 0x00);
		SetByte((0x005B89D5+3), 0x00);
		SetByte((0x005B89DB+3), 0x00);
		SetByte((0x005B89E1+3), 0x00);
		SetWord((0x005B89E7+3), 0x00);
		SetByte((0x005C6314+2), 0x00);
		SetByte((0x005C6327+2), 0x00);
		SetByte((0x005C633A+2), 0x00);
		SetByte((0x005C634D+2), 0x00);
		SetByte((0x005C6360+2), 0x00);
		SetByte((0x005C6373+2), 0x00);
		SetWord((0x005C6386+2), 0x00);
	}

	SetByte((PVOID)(0x004030D1 + 3), gProtect.m_MainInfo.RemoveClass); // Create character max chars (default: 7)

	SetWord(0x00405B7C, gProtect.m_MainInfo.ReduceMemory);
	SetWord(0x0040CC40, gProtect.m_MainInfo.ReduceMemory);
	
	if (gProtect.m_MainInfo.DisableTree == 1)
	{
		MemorySet(0x008193F0, 0x90, 0xC8); //Remove Master Skill Tree Window(A Buttom)
	}

	if (gProtect.m_MainInfo.EffectPlus15 == 0)
	{
		MemorySet(0x006097B0, 0x90, 0x69D);
	}

	if (gProtect.m_MainInfo.DisableGens == 1)
	{
		MemorySet(0x007C5AD2, 0x90, 0x05);			//-> Disable Gens (Key B)
	}

	if (gProtect.m_MainInfo.DisableTabMap == 1)
	{
		MemorySet(0x0062F876, 0x90, 0x30);			//-> Disable ViewMap (Key TAB)
	}
	//-- disables
	if (gProtect.m_MainInfo.DisableRepeirInInventory == 1)
	{
		SetCompleteHook(0xE9, 0x0083693C, &OffButtonRepeirInInventory);
	}

	if (gProtect.m_MainInfo.DisableButtonOpenStore == 1)
	{
		SetCompleteHook(0xE9, 0x008369AF, &OffButtonOpenStore);
	}

	if (gProtect.m_MainInfo.DisableButtonInventoryExt == 1)
	{
		SetCompleteHook(0xE9, 0x00836A23, &OffButtonInventoryExt);
	}

	if (gProtect.m_MainInfo.DisableButtonQuestInStats == 1)
	{
		SetCompleteHook(0xE9, 0x0077EBB0, &OffButtonQuestInStats);
	}

	if (gProtect.m_MainInfo.DisableButtonPetsInStats == 1)
	{
		SetCompleteHook(0xE9, 0x0077EC59, &OffButtonPetsInStats);
	}

	if (gProtect.m_MainInfo.DisableButtonSkillMaster == 1)
	{
		SetCompleteHook(0xE9, 0x0077ECE2, &OffButtonSkillMasterInStats);
	}

	if (gProtect.m_MainInfo.DisableEffectRemake == 0)
	{
		gCreateEffect.Load();
	}

	//==============================================================================
	// Limite trade zen
	//==============================================================================
	if (gProtect.m_MainInfo.LimitTransferZen == 1)
	{
		SetByte((PVOID)(0x007AF175 + 1), 9);
		SetByte((PVOID)(0x007AF415 + 1), 9);
		SetByte((PVOID)(0x007AF795 + 1), 9);
		SetByte((PVOID)(0x007B0315 + 1), 9);
	}

	//==============================================================================
	// Disable Cash Shop
	//==============================================================================
	if (gProtect.m_MainInfo.CustomDowngradeXshop == 1)
	{
		MemorySet(0x00661700, 0x90, 0x43);			//-> Disable CashShop (Key X) SafeZone
		MemorySet(0x007D3D7A, 0x90, 0x05);			//-> Disable CashShop (Key X) MonsterZone
	}

	//==============================================================================
	// Disable text in Inventory
	//==============================================================================
	if (gProtect.m_MainInfo.DisableSocketInventory == 1)
	{
		//	SetRange((LPVOID)0x00D46C8C, 5, ASM::NOP);      //-> Remove Interface [Socket Option]
		RemoveSocket();
	}

	if (gProtect.m_MainInfo.DisableAccInventory == 1)
	{
		SetRange((LPVOID)0x00D46C84, 5, ASM::NOP);      //-> Remove Interface [Set Option]
	}

	//==============================================================================
	// Disable Helper
	//==============================================================================

	if (gProtect.m_MainInfo.DisableHelper == 1)
	{
		MemorySet(0x0085B6AC, 0x90, 0x05);			//-> Remove Helper Top Screen
	}

	if (gProtect.m_MainInfo.DisableHelperKeyZ == 1)
	{
		MemorySet(0x0085CC50, 0x90, 0x05);			//-> Disable Helper (Key Z)
	}

	if (gProtect.m_MainInfo.DisableHelperKeyHome == 1)
	{
		MemorySet(0x007D40A2, 0x90, 0x05);			//-> Disable Helper (Key Home)
	}

	if (gProtect.m_MainInfo.DisableKeyS == 1)
	{
		SetByte((PVOID)(0x00834E12 + 1), 0xFF);
	}

	if (gProtect.m_MainInfo.DisableKeyF == 1)
	{
		SetByte((PVOID)(0x007D37A1 + 1), 0xFF); //disable F Key
	}
	if (gProtect.m_MainInfo.DisableKeyU == 1)
	{
		MemorySet(0x008684F0, 0x90, 0x52);			//-> Disable FastMenu (Key U)
	}
	if (gProtect.m_MainInfo.DisableKeyT == 1)
	{
		//	SetByte((PVOID)(0x007D399F + 1), 0xFF); // Disable Key T
		SetCompleteHook(0xE9, 0x007D399F, 0x007D39D8); //Disable Quest (T)
		SetCompleteHook(0xE9, 0x0077EB65, 0x0077EC0E); //Disable Quest in character status
	}

	//==============================================================================
	// Disable Windows Move Key M
	//==============================================================================
	if (gProtect.m_MainInfo.CustomDowngradeListMap == 1)
	{
		MemorySet(0x00830BA6, 0x90, 0x05);
		MemorySet(0x00832ED8, 0x90, 0x05);
		MemorySet(0x0083279C, 0x90, 0x05);
		MemorySet(0x008329A2, 0x90, 0x05);
	}
	//==============================================================================
	// Lucky Item
	//==============================================================================
	if (gProtect.m_MainInfo.CustomDowngradeLuckyItem == 1)
	{
		MemorySet(0x008583F9, 0x90, 0x08);			//-> Disable Red Lucky Item Inv -> Trade
		MemorySet(0x00858752, 0x90, 0x08);			//-> Disable Red Lucky Item Inv -> Baul
		MemorySet(0x0085875F, 0x90, 0xF6);			//-> Allow Move Lucky Item Inv -> Baul

		SetByte(0x005C914B + 3, 0x00); //-- LuckItemmove
	}
	//==============================================================================
	// Disable Expanded Invtary
	//==============================================================================
	if (gProtect.m_MainInfo.CustomDowngradeExpInventory == 1)
	{
		MemorySet(0x7D4D60, 0x90, 0xA5);
	}
	//==============================================================================
	// Disable Key D
	//==============================================================================
	if (gProtect.m_MainInfo.CustomDowngradeButtonD == 1)
	{
		MemorySet(0x0078DC20, 0x90, 0x5A);
	}
	//==============================================================================
	// Disable vault Expanded
	//==============================================================================
	if (gProtect.m_MainInfo.DisableVaultExp == 1)
	{
		SetCompleteHook(0xE9, 0x00856FAA, 0x00856FD2); // Remove (H) Baú Aberto
		SetCompleteHook(0xE9, 0x007D371E, 0x007D3725); // Remove botão (H)
	}

	//==============================================================================
	// Disable BattleZone In windwos Move key M
	//==============================================================================
	if (gProtect.m_MainInfo.CustomDowngradeBattleZoneWindowsMove == 1)
	{
		SetCompleteHook(0xE9, 0x00832862, 0x00832897);
	}
	//==============================================================================
	// Disable Button 380 Chaos Machine
	//==============================================================================
	if (gProtect.m_MainInfo.DisableButton380 == 1)
	{
		MemorySet(0x007AA3BA, 0x90, 0x5);
		MemorySet(0x007AA39C, 0x90, 0x5);
		MemorySet(0x007AA9B3, 0x90, 0x5);
	}

	if (gProtect.m_MainInfo.RemoveButtonMenuCredits == 1)
	{
		//-- remove buttom menu & credit
		MemorySet(0x0040A7EF, 0x90, 0x5);
		MemorySet(0x0040A87E, 0x90, 0x5);
	}

	if (gProtect.m_MainInfo.RemoveClickEffect == 1)
	{
		//-- remove efect clic
		SetRange((LPVOID)0x006E899D, 5, ASM::NOP);
		SetRange((LPVOID)0x007126FA, 5, ASM::NOP);
		SetRange((LPVOID)0x005B768F, 5, ASM::NOP);
		SetRange((LPVOID)0x005B770C, 5, ASM::NOP);
	}

	if (gProtect.m_MainInfo.MenuEscTransp == 1)
	{
		//-- MENU ESC TRANSPARENTE
		MemorySet(0x007A8330, 0x90, 0x198);
	}

	//==============================================================================
	// Disable Button Expande vault
	//==============================================================================
	if (gProtect.m_MainInfo.DisableButtonExVault == 1)
	{
		SetCompleteHook(0xE9, 0x00856FAA, 0x00856FD2);
		SetCompleteHook(0xE9, 0x007D371E, 0x007D3725);
	}

	SetCompleteHook(0xE8, 0x0059AFFA, 0x0059B00E); // monster trabe

	gPostInterface.Load();	//<-- post item

	gCItemSetOption.Load();

	InitAttackSpeed(); //-- Fix Agilidad

	

	//GInfo.IniInformation();

}

BOOL APIENTRY DllMain(HMODULE hModule,DWORD ul_reason_for_call,LPVOID lpReserved) // OK
{
	switch(ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			hins = (HINSTANCE)hModule;
			gController.Instance = hModule;
			if (gProtect.m_MainInfo.MiniAH == 1)
			{
				DWORD OldProtect;
				if (VirtualProtect((LPVOID)(0x401000), 2834430, PAGE_EXECUTE_READWRITE, &OldProtect) == TRUE)
				{
					Initialize();
				}
			}
			break;
		case DLL_PROCESS_DETACH:
			break;
		case DLL_THREAD_ATTACH:
			break;
		case DLL_THREAD_DETACH:
			break;
	}

	return 1;
}