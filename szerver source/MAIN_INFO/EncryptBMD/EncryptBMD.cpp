#include "stdafx.h"
#include "..\..\Util\CCRC32.H"
#include "ThemidaSDK.h"
#include "CustomEffectDynamic.h"
#include "CustomWIngEffect.h"
#include "CustomPetEffect.h"
#include "tooltipbuff.h"
#include "cCPetRenderMesh.h"
#include "MultiSelect.h"
#include "CustomMonsterGlow.h"
#include "MonsterEffect.h"
#include "ItemTooltip.h"

#include "CustomBuyVip.h"
#include "CustomCommandInfo.h"
#include "CustomEventTimeText.h"
#include "CustomItem.h"
#include "CustomJewel.h"
#include "CustomMessage.h"
#include "CustomMonster.h"
#include "CustomNpcName.h"
#include "CustomWing.h"
#include "SmokeEffect.h"
#include "CustomGloves.h"
#include "CustomCrossBow.h"
#include "CustomPet.h"
#include "CustomCloak.h"
#include "Fog.h"
#include "CustomItemPosition.h"
#include "CustomEffectRemake.h"
#include "ItemManager.h"
#include "ItemValue.h"
#include "ModelEffect.h"
#include "LuckyWheel.h"
#include "CSmithItem.h"
#include "EarthQuake.h"
#include "MonsterHpBar.h"
#include "NoShadow.h"

struct MAIN_FILE_INFO
{
	BYTE LauncherType;
	char LauncherName[32];
	char CustomerName[32];
	char IpAddress[32];
	WORD IpAddressPort;
	char ClientVersion[8];
	char ClientSerial[17];
	char WindowName[32];
	char ScreenShotPath[50];
	char ClientName[32];
	char HackName[32];
	char PluginName5[32];
	char PluginName1[32];
	char PluginName2[32];
	char PluginName3[32];
	char PluginName4[32];
	char CameraName[32];
	char ServerName1[32];
	char ServerName2[32];
	char ServerName3[32];
	char ServerName4[32];
	DWORD ClientCRC32;
	DWORD HackCRC32;
	DWORD Plugin5CRC32;
	DWORD Plugin1CRC32;
	DWORD Plugin2CRC32;
	DWORD Plugin3CRC32;
	DWORD Plugin4CRC32;
	DWORD CameraCRC32;
	DWORD HelperActiveAlert;
	DWORD HelperActiveLevel;
	DWORD DWMaxAttackSpeed;
	DWORD DKMaxAttackSpeed;
	DWORD FEMaxAttackSpeed;
	DWORD MGMaxAttackSpeed;
	DWORD DLMaxAttackSpeed;
	DWORD SUMaxAttackSpeed;
	DWORD RFMaxAttackSpeed;
	DWORD ReconnectTime;
	DWORD ReduceMemory;
	DWORD RemoveClass;
	DWORD RankUserType;
	DWORD DisableTree;
	DWORD CsSkill;
	DWORD DisableReflectEffect;
	DWORD EnableVipShop;
	DWORD VipTypes;
	DWORD PrintLogo;
	DWORD CustomMenuSwitch;
	DWORD CustomMenuType;
	DWORD EnableCoinStatus;
	DWORD EnableShopValueSystem;
	DWORD CustomStoreEnableJoB;
	DWORD CustomStoreEnableJoS;
	DWORD CustomStoreEnableJoC;
	DWORD CustomStoreEnableCoin1;
	DWORD CustomStoreEnableCoin2;
	DWORD CustomStoreEnableCoin3;
	DWORD CustomOffStoreEnable;
	DWORD CustomMonsterEnable;
	DWORD DisablePartyHpBar;
	DWORD RankUserShowOverHead;
	DWORD RankUserOnlyOnSafeZone;
	DWORD RankUserShowReset;
	DWORD RankUserShowMasterReset;
	DWORD RankUserNeedAltKey;
	//---
	DWORD CustomInterfaceType;
	DWORD TIME_GMT;
	DWORD MonitorFPS;
	DWORD MonitorMS;
	DWORD LimitFPS;
	DWORD EffectPlus15;
	DWORD DisableGens;
	DWORD DisableTabMap;
	DWORD DisableHelper;
	DWORD DisableHelperKeyHome;
	DWORD DisableHelperKeyZ;
	DWORD DisableAdvance;
	DWORD DisableEffectRemake;
	DWORD DisableCustomClaws;
	DWORD DisableCustomBow;
	DWORD DisableCustomCloack;
	DWORD DisableCustomPosition;
	DWORD DisableCustomPet;
	DWORD DisableSocketInventory;
	DWORD DisableAccInventory;
	DWORD DisableRepeirInInventory;
	DWORD DisableButtonOpenStore;
	DWORD DisableButtonInventoryExt;
	DWORD DisableButtonQuestInStats;
	DWORD DisableButtonPetsInStats;
	DWORD DisableButtonSkillMaster;
	DWORD SelectCharAnimate;
	DWORD SelectCharS13;
	DWORD InventoryUPGRADE;
	DWORD CameraZoom;
	//--
	DWORD DisableKeyS;
	DWORD DisableKeyF;
	DWORD DisableKeyT;
	DWORD DisableVaultExp;
	DWORD DisableButton380;
	DWORD LimitTransferZen;
	DWORD CustomDowngradeXshop;
	DWORD DisableKeyU;
	DWORD CustomDowngradeLuckyItem;
	DWORD CustomDowngradeListMap;
	DWORD CustomDowngradeButtonD;
	DWORD CustomDowngradeExpInventory;
	DWORD RemoveClickEffect;
	DWORD MenuEscTransp;
	DWORD CustomDowngradeBattleZoneWindowsMove;
	DWORD RemoveButtonMenuCredits;
	DWORD ReducirRam;
	DWORD TooltipS15;
	DWORD SocketItemAcceptHarmonySwitch;
	DWORD CustomEffectEarthQuake;
	DWORD CreateCharacterS13;
	DWORD DisableButtonExVault;
	DWORD MiniMapType;
	DWORD NewPanelCharacterS10;
	DWORD MiniAH;
	DWORD MapAtlasAbyss;
	DWORD CustomTypeSmithItem;
	DWORD LogoRank;
	DWORD LogoVip;
//	DWORD MiniBuff;
	//--
	CUSTOM_MESSAGE_INFO EngCustomMessageInfo[MAX_CUSTOM_MESSAGE];
	CUSTOM_MESSAGE_INFO PorCustomMessageInfo[MAX_CUSTOM_MESSAGE];
	CUSTOM_MESSAGE_INFO SpnCustomMessageInfo[MAX_CUSTOM_MESSAGE];
	CUSTOM_JEWEL_INFO CustomJewelInfo[MAX_CUSTOM_JEWEL];
	CUSTOM_WING_INFO CustomWingInfo[MAX_CUSTOM_WING];
	CUSTOM_ITEM_INFO CustomItemInfo[MAX_CUSTOM_ITEM];
	CUSTOM_BUYVIP_INFO CustomBuyVipInfo[MAX_CUSTOM_BUYVIP];
	CUSTOM_COMMAND_INFO CustomCommandInfo[MAX_CUSTOM_COMMAND];
	CUSTOM_EVENT_INFO CustomEventInfo[MAX_EVENTTIME];
	CUSTOM_SMOKEEFFECT CustomSmokeEffect[MAX_SMOKE_ITEMS];
	CUSTOM_FOG CustomFog[MAX_FOG];
	CUSTOMMONSTER_DATA CustomMonsters[MAX_CUSTOMMONSTER];
	NPCNAME_DATA CustomNPCName[MAX_CUSTOM_NPCNAME];
	//--
	CUSTOM_BOW_INFO CustomBowInfo[MAX_CUSTOM_BOW];
	CUSTOM_RF_GLOVES CustomGloves[MAX_CUSTOM_GLOVES];
	CUSTOM_PET_INFO CustomPetInfo[MAX_PET_ITEM];
	CUSTOMCLOAK_DATA m_CustomCloak[MAX_CUSTOMCLOAK];
	CUSTOM_POSITION_INFO CustomPosition[MAX_POSITION_ITEM];
	REMAKE_EFFECT CustomRemake[MAX_REMAKE_EFFECT];
	//--
	ITEM_INFO m_ItemInfoEx[MAX_ITEM2];
	CUSTOM_MODEL_EFFECT_INFO m_CustomModelInfo[MAX_MODEL_EFFECT];
	LUCKYWHEEL_INFO CustomLuckyWheel[MAX_ITEM];
	//--
	CUSTOM_SMITH_INFO SmithSwordInfo[MAX_SMITH_ITEM];
	CUSTOM_SMITH_INFO SmithAxeInfo[MAX_SMITH_ITEM];
	CUSTOM_SMITH_INFO SmithMaceInfo[MAX_SMITH_ITEM];
	CUSTOM_SMITH_INFO SmithSpearInfo[MAX_SMITH_ITEM];
	CUSTOM_SMITH_INFO SmithBowInfo[MAX_SMITH_ITEM];
	CUSTOM_SMITH_INFO SmithStaffInfo[MAX_SMITH_ITEM];
	CUSTOM_SMITH_INFO SmithShieldInfo[MAX_SMITH_ITEM];
	CUSTOM_SMITH_INFO SmithHelmInfo[MAX_SMITH_ITEM];
	CUSTOM_SMITH_INFO SmithArmorInfo[MAX_SMITH_ITEM];
	CUSTOM_SMITH_INFO SmithPantInfo[MAX_SMITH_ITEM];
	CUSTOM_SMITH_INFO SmithGloveInfo[MAX_SMITH_ITEM];
	CUSTOM_SMITH_INFO SmithBootInfo[MAX_SMITH_ITEM];

	CUSTOM_HPBAR CustomHpBar[MAX_CUSTOM_HPBAR];
};

struct PETEFFECT_BMD
{
	PET_EFFECT_CUSTOM m_PetCEffectBMD[max_ceffect];
	CUSTOM_WING_EFFECT_INFO CustomWingEffectInfo[MAX_CUSTOM_WING_EFFECT];
	DYNAMIC_WING_EFFECT_INFO DynamicWingEffectInfo[MAX_DYNAMIC_WING_EFFECT];
	RENDER_MESH RenderMeshPet[MAX_RENDER_MESH];

	CUSTOM_MONSTERGLOW_INFO m_CustomMonsterGlow[MAX_CUSTOM_MONSTERGLOW];
	CUSTOM_GLOW_INFO m_CustomMonsterbrightness[MAX_CUSTOM_MONSTERGLOW];
	xMonsterEffect m_CustomMonsterEffect[MAX_EFFECT_MONSTER];

	HORSE_EARTH_QUAKE m_EarthQuakeLoad[MAX_EARTH_QUAKE];
	ITEM_NO_SHADOW_INFO m_ShadowInfo[MAX_NO_SHADOW];
};

struct TOOLTIP_BMD
{
	RenderTooltipBuff m_TooltipTRSDataEng[256];
	RenderTooltipBuff m_TooltipTRSDataSpn[256];
	RenderTooltipBuff m_TooltipTRSDataPor[256];

	nInformation m_TRSTooltipData[MaxLine];
	nText m_TRSTooltipText[MaxLine];
};

struct RENDER_MAKE_VIEW
{
	#if UPDATE >= 15
	SelectChar m_RenderSelect[MAX_WORLD_SETTINGS];
	#endif
};


int encryptMainInfo()
{
	CLEAR_START

		ENCODE_START

		int encryptMainInfo;

	encryptMainInfo = GetPrivateProfileIntA("Encrypt", "EncryptMainInfo", 0, ".\\Settings.ini");

	if (encryptMainInfo == 0)
	{
		return 0;
	}

	MAIN_FILE_INFO info;

	memset(&info, 0, sizeof(info));

	GetPrivateProfileString("CONEXION", "CustomerName", "", info.CustomerName, sizeof(info.CustomerName), ".\\MainInfo.ini");

	info.LauncherType = GetPrivateProfileInt("CONEXION", "LauncherType", 0, ".\\MainInfo.ini");

	GetPrivateProfileString("CONEXION", "LauncherName", "XTLauncherExecutable", info.LauncherName, sizeof(info.LauncherName), ".\\MainInfo.ini");

	GetPrivateProfileString("CONEXION", "IpAddress", "", info.IpAddress, sizeof(info.IpAddress), ".\\MainInfo.ini");

	info.IpAddressPort = GetPrivateProfileInt("CONEXION", "IpAddressPort", 44405, ".\\MainInfo.ini");

	GetPrivateProfileString("CONEXION", "ClientVersion", "", info.ClientVersion, sizeof(info.ClientVersion), ".\\MainInfo.ini");

	GetPrivateProfileString("CONEXION", "ClientSerial", "", info.ClientSerial, sizeof(info.ClientSerial), ".\\MainInfo.ini");

	GetPrivateProfileString("CONEXION", "WindowName", "[MU]", info.WindowName, sizeof(info.WindowName), ".\\MainInfo.ini");

	GetPrivateProfileString("CONEXION", "ScreenShotPath", "", info.ScreenShotPath, sizeof(info.ScreenShotPath), ".\\MainInfo.ini");

	GetPrivateProfileString("CONEXION", "ClientName", "", info.ClientName, sizeof(info.ClientName), ".\\MainInfo.ini");
	//-------------------

	info.MiniAH = GetPrivateProfileInt("ANTIHACK", "AH_Interno", 0, ".\\MainInfo.ini");

	GetPrivateProfileString("ANTIHACK", "AntiHackName", "", info.HackName, sizeof(info.HackName), ".\\MainInfo.ini");

	//-------------------

	GetPrivateProfileString("PLUGINS", "PluginName1", "", info.PluginName1, sizeof(info.PluginName1), ".\\MainInfo.ini");

	GetPrivateProfileString("PLUGINS", "PluginName2", "", info.PluginName2, sizeof(info.PluginName2), ".\\MainInfo.ini");

	GetPrivateProfileString("PLUGINS", "PluginName3", "", info.PluginName3, sizeof(info.PluginName3), ".\\MainInfo.ini");

	GetPrivateProfileString("PLUGINS", "PluginName4", "", info.PluginName4, sizeof(info.PluginName4), ".\\MainInfo.ini");

	GetPrivateProfileString("PLUGINS", "PluginName5", "", info.PluginName5, sizeof(info.PluginName5), ".\\MainInfo.ini");

	GetPrivateProfileString("PLUGINS", "PluginName6", "", info.CameraName, sizeof(info.CameraName), ".\\MainInfo.ini");

	//--------------------

	GetPrivateProfileString("SERVER", "ServerName1", "", info.ServerName1, sizeof(info.ServerName1), ".\\MainInfo.ini");

	GetPrivateProfileString("SERVER", "ServerName2", "", info.ServerName2, sizeof(info.ServerName2), ".\\MainInfo.ini");

	GetPrivateProfileString("SERVER", "ServerName3", "", info.ServerName3, sizeof(info.ServerName3), ".\\MainInfo.ini");

	GetPrivateProfileString("SERVER", "ServerName4", "", info.ServerName4, sizeof(info.ServerName4), ".\\MainInfo.ini");

	//-------------------

	info.HelperActiveAlert = GetPrivateProfileInt("HELPER", "HelperActiveAlert", 0, ".\\MainInfo.ini");

	info.HelperActiveLevel = GetPrivateProfileInt("HELPER", "HelperActiveLevel", 80, ".\\MainInfo.ini");

	//-------------------

	info.DWMaxAttackSpeed = GetPrivateProfileInt("CHARACTER", "DWMaxAttackSpeed", 65535, ".\\MainInfo.ini");

	info.DKMaxAttackSpeed = GetPrivateProfileInt("CHARACTER", "DKMaxAttackSpeed", 65535, ".\\MainInfo.ini");

	info.FEMaxAttackSpeed = GetPrivateProfileInt("CHARACTER", "FEMaxAttackSpeed", 65535, ".\\MainInfo.ini");

	info.MGMaxAttackSpeed = GetPrivateProfileInt("CHARACTER", "MGMaxAttackSpeed", 65535, ".\\MainInfo.ini");

	info.DLMaxAttackSpeed = GetPrivateProfileInt("CHARACTER", "DLMaxAttackSpeed", 65535, ".\\MainInfo.ini");

	info.SUMaxAttackSpeed = GetPrivateProfileInt("CHARACTER", "SUMaxAttackSpeed", 65535, ".\\MainInfo.ini");

	info.RFMaxAttackSpeed = GetPrivateProfileInt("CHARACTER", "RFMaxAttackSpeed", 65535, ".\\MainInfo.ini");

	//-------------------

	info.ReconnectTime = GetPrivateProfileInt("RECCONECT", "ReconnectTime", 0, ".\\MainInfo.ini");

	//------------------

	info.LimitTransferZen = GetPrivateProfileInt("CUSTOM", "LimitTransferZen", 0, ".\\MainInfo.ini");

	info.ReduceMemory = GetPrivateProfileInt("CUSTOM", "DelectCharacter", 300, ".\\MainInfo.ini");

	info.ReducirRam = GetPrivateProfileInt("CUSTOM", "ReduceRam", 0, ".\\MainInfo.ini");

	info.RankUserType = GetPrivateProfileInt("CUSTOM", "RankUserType", 0, ".\\MainInfo.ini");

	info.CsSkill = GetPrivateProfileInt("CUSTOM", "EnableCsSkillsAllMaps", 0, ".\\MainInfo.ini");

	info.DisableReflectEffect = GetPrivateProfileInt("CUSTOM", "DisableReflectEffect", 0, ".\\MainInfo.ini");

	info.RankUserShowOverHead = GetPrivateProfileInt("CUSTOM", "RankUserShowOverHead", 0, ".\\MainInfo.ini");

	info.RankUserOnlyOnSafeZone = GetPrivateProfileInt("CUSTOM", "RankUserOnlyOnSafeZone", 1, ".\\MainInfo.ini");

	info.RankUserShowReset = GetPrivateProfileInt("CUSTOM", "RankUserShowReset", 1, ".\\MainInfo.ini");

	info.RankUserShowMasterReset = GetPrivateProfileInt("CUSTOM", "RankUserShowMasterReset", 1, ".\\MainInfo.ini");

	info.RankUserNeedAltKey = GetPrivateProfileInt("CUSTOM", "RankUserNeedAltKey", 0, ".\\MainInfo.ini");

	info.EnableVipShop = GetPrivateProfileInt("CUSTOM", "EnableVipShop", 0, ".\\MainInfo.ini");

	info.VipTypes = GetPrivateProfileInt("CUSTOM", "VipTypes", 3, ".\\MainInfo.ini");

	info.PrintLogo = GetPrivateProfileInt("CUSTOM", "PrintLogo", 0, ".\\MainInfo.ini");

	info.CustomMenuSwitch = GetPrivateProfileInt("CUSTOM", "CustomMenuSwitch", 0, ".\\MainInfo.ini");

	info.CustomMenuType = GetPrivateProfileInt("CUSTOM", "CustomMenuType", 0, ".\\MainInfo.ini");

	info.EnableCoinStatus = GetPrivateProfileInt("CUSTOM", "EnableCoinStatus", 0, ".\\MainInfo.ini");

	info.EnableShopValueSystem = GetPrivateProfileInt("CUSTOM", "EnableShopValueSystem", 0, ".\\MainInfo.ini");

	info.CustomStoreEnableJoB = GetPrivateProfileInt("CUSTOM", "EnableStoreBlessButtom", 0, ".\\MainInfo.ini");

	info.CustomStoreEnableJoS = GetPrivateProfileInt("CUSTOM", "EnableStoreSoulButtom", 0, ".\\MainInfo.ini");

	info.CustomStoreEnableJoC = GetPrivateProfileInt("CUSTOM", "EnableStoreChaosButtom", 0, ".\\MainInfo.ini");

	info.CustomStoreEnableCoin1 = GetPrivateProfileInt("CUSTOM", "EnableStoreCoin1Buttom", 0, ".\\MainInfo.ini");

	info.CustomStoreEnableCoin2 = GetPrivateProfileInt("CUSTOM", "EnableStoreCoin2Buttom", 0, ".\\MainInfo.ini");

	info.CustomStoreEnableCoin3 = GetPrivateProfileInt("CUSTOM", "EnableStoreCoin3Buttom", 0, ".\\MainInfo.ini");

	info.CustomOffStoreEnable = GetPrivateProfileInt("CUSTOM", "EnableOffStoreButtom", 0, ".\\MainInfo.ini");

	info.CustomMonsterEnable = GetPrivateProfileInt("CUSTOM", "CustomMonsterEnable", 0, ".\\MainInfo.ini");

	info.LogoRank = GetPrivateProfileInt("CUSTOM", "RankLogoInHead", 0, ".\\MainInfo.ini");

	info.LogoVip = GetPrivateProfileInt("CUSTOM", "VipLogoInHead", 0, ".\\MainInfo.ini");

	info.MonitorFPS = GetPrivateProfileInt("CUSTOM", "MonitorFPS", 0, ".\\MainInfo.ini");

	info.MonitorMS = GetPrivateProfileInt("CUSTOM", "MonitorMS", 0, ".\\MainInfo.ini");

	info.LimitFPS = GetPrivateProfileInt("CUSTOM", "LimitFPS", 0, ".\\MainInfo.ini");

	info.EffectPlus15 = GetPrivateProfileInt("CUSTOM", "EffectPlus15", 0, ".\\MainInfo.ini");

	info.SocketItemAcceptHarmonySwitch = GetPrivateProfileInt("CUSTOM", "SocketItemAcceptHarmonySwitch", 0, ".\\MainInfo.ini");

	info.CustomEffectEarthQuake = GetPrivateProfileInt("CUSTOM", "RenderEffectDarhorseSkill", 0, ".\\MainInfo.ini");

	info.MiniMapType = GetPrivateProfileInt("CUSTOM", "MiniMapType", 1, ".\\MainInfo.ini");

	info.MapAtlasAbyss = GetPrivateProfileInt("CUSTOM", "MapAtlansAbyss", 0, ".\\MainInfo.ini");

	info.CustomTypeSmithItem = GetPrivateProfileInt("CUSTOM", "CustomTypeSmithItem", 0, ".\\MainInfo.ini");

	//---------------------

	info.CustomInterfaceType = GetPrivateProfileInt("INTERFACE", "CustomInterfaceType", 0, ".\\MainInfo.ini");

	//---------------------

	info.TIME_GMT = GetPrivateProfileInt("TIMEZONE", "TIME_GMT", 0, ".\\MainInfo.ini");

	//---------------------

	info.DisablePartyHpBar = GetPrivateProfileInt("DOWNGRADE_UPGRADE", "DisablePartyHpBar", 0, ".\\MainInfo.ini");

	info.DisableGens = GetPrivateProfileInt("DOWNGRADE_UPGRADE", "DisableGens", 0, ".\\MainInfo.ini");

	info.DisableTabMap = GetPrivateProfileInt("DOWNGRADE_UPGRADE", "DisableTabMap", 0, ".\\MainInfo.ini");

	info.DisableHelper = GetPrivateProfileInt("DOWNGRADE_UPGRADE", "DisableHelper", 0, ".\\MainInfo.ini");

	info.DisableHelperKeyHome = GetPrivateProfileInt("DOWNGRADE_UPGRADE", "DisableHelperKeyHome", 0, ".\\MainInfo.ini");

	info.DisableHelperKeyZ = GetPrivateProfileInt("DOWNGRADE_UPGRADE", "DisableHelperKeyZ", 0, ".\\MainInfo.ini");

	info.DisableAdvance = GetPrivateProfileInt("DOWNGRADE_UPGRADE", "DisableAdvance", 0, ".\\MainInfo.ini");

	info.DisableCustomClaws = GetPrivateProfileInt("DOWNGRADE_UPGRADE", "DisableCustomClaws", 0, ".\\MainInfo.ini");

	info.DisableCustomBow = GetPrivateProfileInt("DOWNGRADE_UPGRADE", "DisableCustomBow", 0, ".\\MainInfo.ini");

	info.DisableCustomCloack = GetPrivateProfileInt("DOWNGRADE_UPGRADE", "DisableCustomCloack", 0, ".\\MainInfo.ini");

	info.DisableCustomPosition = GetPrivateProfileInt("DOWNGRADE_UPGRADE", "DisableCustomPosition", 0, ".\\MainInfo.ini");

	info.DisableCustomPet = GetPrivateProfileInt("DOWNGRADE_UPGRADE", "DisableCustomPet", 0, ".\\MainInfo.ini");

	info.DisableEffectRemake = GetPrivateProfileInt("DOWNGRADE_UPGRADE", "DisableEffectRemake", 0, ".\\MainInfo.ini");

	info.DisableSocketInventory = GetPrivateProfileInt("DOWNGRADE_UPGRADE", "DisableSocketInventory", 0, ".\\MainInfo.ini");

	info.DisableAccInventory = GetPrivateProfileInt("DOWNGRADE_UPGRADE", "DisableAccInventory", 0, ".\\MainInfo.ini");

	info.DisableRepeirInInventory = GetPrivateProfileInt("DOWNGRADE_UPGRADE", "DisableRepeirInInventory", 0, ".\\MainInfo.ini");

	info.DisableButtonOpenStore = GetPrivateProfileInt("DOWNGRADE_UPGRADE", "DisableButtonOpenStore", 0, ".\\MainInfo.ini");

	info.DisableButtonInventoryExt = GetPrivateProfileInt("DOWNGRADE_UPGRADE", "DisableButtonInventoryExt", 0, ".\\MainInfo.ini");

	info.DisableButtonQuestInStats = GetPrivateProfileInt("DOWNGRADE_UPGRADE", "DisableButtonQuestInStats", 0, ".\\MainInfo.ini");

	info.DisableButtonPetsInStats = GetPrivateProfileInt("DOWNGRADE_UPGRADE", "DisableButtonPetsInStats", 0, ".\\MainInfo.ini");

	info.DisableButtonSkillMaster = GetPrivateProfileInt("DOWNGRADE_UPGRADE", "DisableButtonSkillMaster", 0, ".\\MainInfo.ini");

	info.SelectCharAnimate = GetPrivateProfileInt("DOWNGRADE_UPGRADE", "SelectCharAnimate", 0, ".\\MainInfo.ini");

	info.SelectCharS13 = GetPrivateProfileInt("DOWNGRADE_UPGRADE", "SelectCharS13", 0, ".\\MainInfo.ini");

	info.InventoryUPGRADE = GetPrivateProfileInt("DOWNGRADE_UPGRADE", "InventoryUPGRADE", 0, ".\\MainInfo.ini");

	info.CameraZoom = GetPrivateProfileInt("DOWNGRADE_UPGRADE", "CameraZoom", 0, ".\\MainInfo.ini");

	info.DisableKeyS = GetPrivateProfileInt("DOWNGRADE_UPGRADE", "DisableKey_S", 0, ".\\MainInfo.ini");

	info.DisableKeyF = GetPrivateProfileInt("DOWNGRADE_UPGRADE", "DisableKey_F", 0, ".\\MainInfo.ini");

	info.DisableKeyT = GetPrivateProfileInt("DOWNGRADE_UPGRADE", "DisableKey_T", 0, ".\\MainInfo.ini");

	info.DisableVaultExp = GetPrivateProfileInt("DOWNGRADE_UPGRADE", "DisableVaultExp", 0, ".\\MainInfo.ini");

	info.DisableButton380 = GetPrivateProfileInt("DOWNGRADE_UPGRADE", "DisableButton380", 0, ".\\MainInfo.ini");

	info.DisableTree = GetPrivateProfileInt("DOWNGRADE_UPGRADE", "DisableMasterSkillTree", 0, ".\\MainInfo.ini");

	info.RemoveClass = GetPrivateProfileInt("DOWNGRADE_UPGRADE", "RemoveClass", 0, ".\\MainInfo.ini");

	info.CustomDowngradeXshop = GetPrivateProfileInt("DOWNGRADE_UPGRADE", "DisableShopX", 0, ".\\MainInfo.ini");

	info.DisableKeyU = GetPrivateProfileInt("DOWNGRADE_UPGRADE", "DisableKey_U", 0, ".\\MainInfo.ini");

	info.CustomDowngradeLuckyItem = GetPrivateProfileInt("DOWNGRADE_UPGRADE", "LuckyItem", 0, ".\\MainInfo.ini");

	info.CustomDowngradeListMap = GetPrivateProfileInt("DOWNGRADE_UPGRADE", "ListMap", 0, ".\\MainInfo.ini");

	info.CustomDowngradeButtonD = GetPrivateProfileInt("DOWNGRADE_UPGRADE", "DisableKey_D", 0, ".\\MainInfo.ini");

	info.CustomDowngradeExpInventory = GetPrivateProfileInt("DOWNGRADE_UPGRADE", "ExpInventory", 0, ".\\MainInfo.ini");

	info.RemoveClickEffect = GetPrivateProfileInt("DOWNGRADE_UPGRADE", "RemoveClickEffect", 0, ".\\MainInfo.ini");

	info.MenuEscTransp = GetPrivateProfileInt("DOWNGRADE_UPGRADE", "MenuEscTransp", 0, ".\\MainInfo.ini");

	info.CustomDowngradeBattleZoneWindowsMove = GetPrivateProfileInt("DOWNGRADE_UPGRADE", "BattleZoneWindowsMove", 0, ".\\MainInfo.ini");

	info.RemoveButtonMenuCredits = GetPrivateProfileInt("DOWNGRADE_UPGRADE", "RemoveButtonMenuCredits", 0, ".\\MainInfo.ini");

	info.TooltipS15 = GetPrivateProfileInt("DOWNGRADE_UPGRADE", "RenderTooltipS15", 0, ".\\MainInfo.ini");

	info.CreateCharacterS13 = GetPrivateProfileInt("DOWNGRADE_UPGRADE", "CreateCharacterS13", 0, ".\\MainInfo.ini");

	info.DisableButtonExVault = GetPrivateProfileInt("DOWNGRADE_UPGRADE", "DisableButtonExVault", 0, ".\\MainInfo.ini");

	info.NewPanelCharacterS10 = GetPrivateProfileInt("DOWNGRADE_UPGRADE", "NewPanelCharacterS10", 0, ".\\MainInfo.ini");

	gCustomMessage.Load("Messages/CustomMessage.txt");

	gCustomJewel.Load("Items/CustomJewel.txt");

	gCustomWing.Load("Items/CustomWing.txt");

	gCustomItem.Load("Items/CustomItem.txt");

	gCustomBuyVip.Load("Customs/CustomBuyVip.txt");

	gCustomCommandInfo.Load("Customs/CustomCommandInfo.txt");

	gCustomEventTimeText.Load("Customs/CustomEventTimeText.txt");

	gSmokeEffect.Load("Effects/CustomSmokeEffect.txt");

	gFog.Load("Effects/CustomFog.txt");

	gMonsters.Load("Monsters/CustomMonster.txt");

	gNPCName.Load("Monsters/CustomNPCName.txt");
	//--
	gCustomGloves.Load("Items/CustomGloves.txt");

	gCustomCrossBow.Load("Items/CustomCrossbow.txt");

	gCustomPet2.Load("Items/CustomPet.txt");

	gCloak.Load("Items/CustomCloak.txt");

	gCustomPosition.Load("Items/CustomItemPosition.txt");

	gCustomRemake.Load("Effects/CustomEffectRemake.txt");

	gItemManager.Load("Items/Item.txt");

	gCustomModelEffect.Load("Effects/ModelEffect.txt");

	gLuckyWheel.Load("Customs/LuckyWheel.txt");

	gCustomSmith.Load("SmithyShop/CustomSmithItem.txt");

	gMonster.Load("Monsters/MonsterHpBar.txt");

	memcpy(info.EngCustomMessageInfo, gCustomMessage.m_EngCustomMessageInfo, sizeof(info.EngCustomMessageInfo));

	memcpy(info.PorCustomMessageInfo, gCustomMessage.m_PorCustomMessageInfo, sizeof(info.PorCustomMessageInfo));

	memcpy(info.SpnCustomMessageInfo, gCustomMessage.m_SpnCustomMessageInfo, sizeof(info.SpnCustomMessageInfo));

	memcpy(info.CustomJewelInfo, gCustomJewel.m_CustomJewelInfo, sizeof(info.CustomJewelInfo));

	memcpy(info.CustomWingInfo, gCustomWing.m_CustomWingInfo, sizeof(info.CustomWingInfo));

	memcpy(info.CustomItemInfo, gCustomItem.m_CustomItemInfo, sizeof(info.CustomItemInfo));

	memcpy(info.CustomBuyVipInfo, gCustomBuyVip.m_CustomBuyVipInfo, sizeof(info.CustomBuyVipInfo));

	memcpy(info.CustomCommandInfo, gCustomCommandInfo.m_CustomCommandInfo, sizeof(info.CustomCommandInfo));

	memcpy(info.CustomEventInfo, gCustomEventTimeText.m_CustomEventInfo, sizeof(info.CustomEventInfo));

	memcpy(info.CustomSmokeEffect, gSmokeEffect.m_CustomSmokeEffect, sizeof(info.CustomSmokeEffect));

	memcpy(info.CustomFog, gFog.m_CustomFog, sizeof(info.CustomFog));

	memcpy(info.CustomMonsters, gMonsters.m_Monsters, sizeof(info.CustomMonsters));

	memcpy(info.CustomNPCName, gNPCName.m_CustomNpcName, sizeof(info.CustomNPCName));
	//-----
	memcpy(info.CustomGloves, gCustomGloves.m_CustomGlovesInfo, sizeof(info.CustomGloves));

	memcpy(info.CustomBowInfo, gCustomCrossBow.m_CustomBowInfo, sizeof(info.CustomBowInfo));

	memcpy(info.CustomPetInfo, gCustomPet2.m_CustomPetInfo, sizeof(info.CustomPetInfo));

	memcpy(info.m_CustomCloak, gCloak.m_Cloak, sizeof(info.m_CustomCloak));

	memcpy(info.CustomPosition, gCustomPosition.m_CustomPositionInfo, sizeof(info.CustomPosition));

	memcpy(info.CustomRemake, gCustomRemake.m_CustomRemake, sizeof(info.CustomRemake));

	memcpy(info.m_ItemInfoEx, gItemManager.m_ItemInfo, sizeof(info.m_ItemInfoEx));

	memcpy(info.m_CustomModelInfo, gCustomModelEffect.m_CustomModelEffectInfo, sizeof(info.m_CustomModelInfo));

	memcpy(info.CustomLuckyWheel, gLuckyWheel.m_LuckyWheelInfo, sizeof(info.CustomLuckyWheel));

	memcpy(info.SmithSwordInfo, gCustomSmith.m_SmithSwordInfo, sizeof(info.SmithSwordInfo));
	memcpy(info.SmithAxeInfo, gCustomSmith.m_SmithAxeInfo, sizeof(info.SmithAxeInfo));
	memcpy(info.SmithMaceInfo, gCustomSmith.m_SmithMaceInfo, sizeof(info.SmithMaceInfo));
	memcpy(info.SmithSpearInfo, gCustomSmith.m_SmithSpearInfo, sizeof(info.SmithSpearInfo));
	memcpy(info.SmithBowInfo, gCustomSmith.m_SmithBowInfo, sizeof(info.SmithBowInfo));
	memcpy(info.SmithStaffInfo, gCustomSmith.m_SmithStaffInfo, sizeof(info.SmithStaffInfo));
	memcpy(info.SmithHelmInfo, gCustomSmith.m_SmithHelmInfo, sizeof(info.SmithHelmInfo));
	memcpy(info.SmithArmorInfo, gCustomSmith.m_SmithArmorInfo, sizeof(info.SmithArmorInfo));
	memcpy(info.SmithPantInfo, gCustomSmith.m_SmithPantInfo, sizeof(info.SmithPantInfo));
	memcpy(info.SmithGloveInfo, gCustomSmith.m_SmithGloveInfo, sizeof(info.SmithGloveInfo));
	memcpy(info.SmithBootInfo, gCustomSmith.m_SmithBootInfo, sizeof(info.SmithBootInfo));

	memcpy(info.CustomHpBar, gMonster.m_CustomHpBar, sizeof(info.CustomHpBar));

	CCRC32 CRC32;

	if (CRC32.FileCRC(info.ClientName, &info.ClientCRC32, 1024) == 0)
	{
		info.ClientCRC32 = 0;
	}

	if (CRC32.FileCRC(info.HackName, &info.HackCRC32, 1024) == 0)
	{
		info.HackCRC32 = 0;
	}

	if (CRC32.FileCRC(info.PluginName1, &info.Plugin1CRC32, 1024) == 0)
	{
		info.Plugin1CRC32 = 0;
	}

	if (CRC32.FileCRC(info.PluginName2, &info.Plugin2CRC32, 1024) == 0)
	{
		info.Plugin2CRC32 = 0;
	}

	if (CRC32.FileCRC(info.PluginName3, &info.Plugin3CRC32, 1024) == 0)
	{
		info.Plugin3CRC32 = 0;
	}

	if (CRC32.FileCRC(info.PluginName4, &info.Plugin4CRC32, 1024) == 0)
	{
		info.Plugin4CRC32 = 0;
	}

	if (CRC32.FileCRC(info.PluginName5, &info.Plugin5CRC32, 1024) == 0)
	{
		info.Plugin5CRC32 = 0;
	}

	if (CRC32.FileCRC(info.CameraName, &info.CameraCRC32, 1024) == 0)
	{
		info.CameraCRC32 = 0;
	}

	for (int n = 0; n < sizeof(MAIN_FILE_INFO); n++)
	{
		((BYTE*)&info)[n] ^= (BYTE)(0xFA ^ LOBYTE(n));
		((BYTE*)&info)[n] -= (BYTE)(0x64 ^ HIBYTE(n));
	}

	HANDLE file = CreateFile("ZxRelease/system.zx", GENERIC_WRITE, FILE_SHARE_READ, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_ARCHIVE, 0);

	if (file == INVALID_HANDLE_VALUE)
	{
		return 0;
	}

	DWORD OutSize = 0;

	if (WriteFile(file, &info, sizeof(MAIN_FILE_INFO), &OutSize, 0) == 0)
	{
		CloseHandle(file);

		return 0;
	}

	CloseHandle(file);

	ENCODE_END

		CLEAR_END
}

int encryptEffect()
{
	CLEAR_START

	ENCODE_START
	
	int EncryptEffect;

	EncryptEffect = GetPrivateProfileIntA("Encrypt", "EncryptEffect", 0, ".\\Settings.ini");

	if(EncryptEffect == 0)
	{
		return 0;
	}
	
	PETEFFECT_BMD info;

	memset(&info,0,sizeof(info));

	gCustomCEffectPet.Load("Effects/CustomPetEffect.txt");

	gCustomWingEffect.Load("Effects/CustomEffectStatic.txt");

	gDynamicWingEffect.Load("Effects/CustomEffectDynamic.txt");

	cRender.Load("Effects/CustomPetGlow.txt");

	JCEffectMonster.Load("Effects/CustomMonsterEffects.txt");

	gCustomMonsterGlow.Load("Effects/CustomMonsterGlow.txt");

	gCustomEarthQuake.Load("Effects/RenderDarkhorseSkill.txt");

	gNoShadow.Load("Effects/ItemDontShadow.txt");

	memcpy(info.m_PetCEffectBMD, gCustomCEffectPet.m_PetCEffect, sizeof(info.m_PetCEffectBMD));

	memcpy(info.CustomWingEffectInfo, gCustomWingEffect.m_CustomWingEffectInfo,sizeof(info.CustomWingEffectInfo));

	memcpy(info.DynamicWingEffectInfo,gDynamicWingEffect.m_DynamicWingEffectInfo,sizeof(info.DynamicWingEffectInfo));

	memcpy(info.m_CustomMonsterGlow, gCustomMonsterGlow.m_CustomGlowInfo, sizeof(info.m_CustomMonsterGlow));

	memcpy(info.m_CustomMonsterbrightness, gCustomMonsterGlow.m_CustombrightnessInfo, sizeof(info.m_CustomMonsterbrightness));

	memcpy(info.m_CustomMonsterEffect, JCEffectMonster.m_MonsterEffect, sizeof(info.m_CustomMonsterEffect));

	memcpy(info.RenderMeshPet, cRender.m_RenderMeshPet, sizeof(info.RenderMeshPet));

	memcpy(info.m_EarthQuakeLoad, gCustomEarthQuake.m_EarthQuake, sizeof(info.m_EarthQuakeLoad));

	memcpy(info.m_ShadowInfo, gNoShadow.m_NoShadowInfo, sizeof(info.m_ShadowInfo));

	for(int n=0;n < sizeof(PETEFFECT_BMD);n++)
	{
		((BYTE*)&info)[n] ^= (BYTE)(0xFA^LOBYTE(n));
		((BYTE*)&info)[n] -= (BYTE)(0x85^HIBYTE(n));
	}

	HANDLE file = CreateFile("ZxRelease/EffectTRSData.bmd", GENERIC_WRITE, FILE_SHARE_READ, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_ARCHIVE, 0 );

	if(file == INVALID_HANDLE_VALUE)
	{
		return 0;
	}

	DWORD OutSize = 0;

	if( WriteFile(file, &info, sizeof(PETEFFECT_BMD), &OutSize, 0) == 0 )
	{
		CloseHandle( file );

		return 0;
	}

	CloseHandle( file );

	ENCODE_END

	CLEAR_END
}

int encryptTooltip()
{
	CLEAR_START

	ENCODE_START

	int EncryptTooltip;

	EncryptTooltip = GetPrivateProfileIntA("Encrypt", "EncryptTooltip", 0, ".\\Settings.ini");

	if(EncryptTooltip == 0)
	{
		return 0;
	}

	TOOLTIP_BMD info;

	memset(&info,0,sizeof(info));

	gCBuffIcon.Load("Messages/BuffEffect_eng.txt", 0);

	gCBuffIcon.Load("Messages/BuffEffect_spn.txt", 1);
	
	gCBuffIcon.Load("Messages/BuffEffect_por.txt", 2);

	GInfo.Load("Items/JCItemToolTip.txt", 1);

	GInfo.Load("Messages/JCTextTooltip.txt", 2);

	memcpy(info.m_TooltipTRSDataEng, gCBuffIcon.m_TooltipENG, sizeof(info.m_TooltipTRSDataEng));
	memcpy(info.m_TooltipTRSDataSpn, gCBuffIcon.m_TooltipSPN, sizeof(info.m_TooltipTRSDataSpn));
	memcpy(info.m_TooltipTRSDataPor, gCBuffIcon.m_TooltipPOR, sizeof(info.m_TooltipTRSDataPor));
	memcpy(info.m_TRSTooltipData, GInfo.n_TRSTooltipData, sizeof(info.m_TRSTooltipData));
	memcpy(info.m_TRSTooltipText, GInfo.n_TRSTooltipText, sizeof(info.m_TRSTooltipText));

	for(int n = 0;n < sizeof(TOOLTIP_BMD);n++)
	{
		((BYTE*)&info)[n] ^= (BYTE)(0xFA^LOBYTE(n));
		((BYTE*)&info)[n] -= (BYTE)(0x85^HIBYTE(n));
	}

	HANDLE file = CreateFile("ZxRelease/TooltipTRSData.bmd", GENERIC_WRITE, FILE_SHARE_READ, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_ARCHIVE, 0 );

	if(file == INVALID_HANDLE_VALUE)
	{
		return 0;
	}

	DWORD OutSize = 0;

	if( WriteFile(file, &info, sizeof(TOOLTIP_BMD), &OutSize, 0) == 0 )
	{
		CloseHandle( file );

		return 0;
	}

	CloseHandle( file );

	ENCODE_END

	CLEAR_END
}

int encryptSelectChar()
{
	CLEAR_START

	ENCODE_START

	int EncryptMakeWorld;

	EncryptMakeWorld = GetPrivateProfileIntA("Encrypt", "EncryptMakeWorld", 0, ".\\Settings.ini");

	if(EncryptMakeWorld == 0)
	{
		return 0;
	}

	RENDER_MAKE_VIEW info;

	memset(&info,0,sizeof(info));

	gSelectCharRamdon.Load("SelectCharWorld/MakeSelectChar.txt");

	memcpy(info.m_RenderSelect, gSelectCharRamdon.RenderSelect, sizeof(info.m_RenderSelect));

	for(int n = 0;n < sizeof(RENDER_MAKE_VIEW); n++)
	{
		((BYTE*)&info)[n] ^= (BYTE) (0xFA^LOBYTE( n ));
		((BYTE*)&info)[n] -= (BYTE) (0x85^HIBYTE( n ));
	}

	HANDLE file = CreateFile("ZxRelease/MakeWorldTRSData.bmd", GENERIC_WRITE, FILE_SHARE_READ, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_ARCHIVE, 0 );

	if(file == INVALID_HANDLE_VALUE)
	{
		return 0;
	}

	DWORD OutSize = 0;

	if( WriteFile(file, &info, sizeof(RENDER_MAKE_VIEW), &OutSize, 0) == 0 )
	{
		CloseHandle( file );

		return 0;
	}

	CloseHandle( file );

	ENCODE_END

	CLEAR_END
}

int _tmain(int argc, _TCHAR* argv[]) // OK
{
	CreateDirectory("ZxRelease", 0);

	encryptMainInfo();

	encryptEffect();

	encryptTooltip();

	encryptSelectChar();

	return 0;
}
