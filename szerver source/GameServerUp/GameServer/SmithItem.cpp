#include "stdafx.h"
#include "User.h"
#include "Log.h"
#include "SmithItem.h"
#include "CashShop.h"
#include "Notice.h"
#include "DSProtocol.h"
#include "ItemManager.h"
#include "Util.h"
#include "Message.h"
#include "MemScript.h"

SCFVipShop SVShop;

void SCFVipShop::Read(char * FilePath){
	pugi::xml_document file;
	pugi::xml_parse_result res = file.load_file(FilePath);
	if (res.status != pugi::status_ok){
		ErrorMessageBox("File %s load fail. Error: %s", FilePath, res.description());
		return;
	}
	pugi::xml_node oSmithItem = file.child("SmithItem");
	pugi::xml_node ConfigSmith = oSmithItem.child("ConfigSystem");
	this->Enabled = ConfigSmith.attribute("Enabled").as_int();
	this->FunctionKG = ConfigSmith.attribute("TypeShop").as_int();
	pugi::xml_node UseSmith = oSmithItem.child("CostSystem");
	this->pLevel = UseSmith.attribute("ItemLevel").as_int();
	this->pOpt = UseSmith.attribute("ItemOption").as_int();
	this->pLuck = UseSmith.attribute("ItemLuck").as_int();
	this->pSkill = UseSmith.attribute("ItemSkill").as_int();
	this->pExc = UseSmith.attribute("ItemExcOption").as_int();
	this->pExc1 = UseSmith.attribute("ItemExcOption1").as_int();
	this->pExc2 = UseSmith.attribute("ItemExcOption2").as_int();
	this->pExc3 = UseSmith.attribute("ItemExcOption3").as_int();
	this->pExc4 = UseSmith.attribute("ItemExcOption4").as_int();
	this->pExc5 = UseSmith.attribute("ItemExcOption5").as_int();
	pugi::xml_node MaxSmith = oSmithItem.child("MaxSystem");
	this->MaxLevel = MaxSmith.attribute("ItemMaxLevel").as_int();
	this->MaxOpt = MaxSmith.attribute("ItemMaxOption").as_int();
	this->MaxExc = MaxSmith.attribute("ItemMaxExcOption").as_int();
	this->MaxLuck = MaxSmith.attribute("ItemMaxLuck").as_int();
	this->MaxSkill = MaxSmith.attribute("ItemMaxSkill").as_int();
	this->TypeCount = 0;
	for (int i = 0; i<(MAX_TYPE_ITEMS*MAX_SUBTYPE_ITEMS); i++){
		this->item[i].Enabled = false;
	}
	if (this->Enabled == 1){
		for (pugi::xml_node eSmithItem = oSmithItem.child("Items"); eSmithItem; eSmithItem = eSmithItem.next_sibling()){
			int type = eSmithItem.attribute("TypeItem").as_int();
			int Index = eSmithItem.attribute("IndexItem").as_int();
			if (type >= 12){
				ErrorMessageBox("SMITHITEM MAX TYPE = 11");
				exit(1);
			}
			if (type >= 512){
				ErrorMessageBox("SMITHITEM MAX INDEX = 512");
				exit(1);
			}
			int ID = GET_ITEM(type, Index);
			this->item[ID].Enabled = true;
			this->item[ID].Price_1Day = eSmithItem.attribute("Price1DayItem").as_int();
			this->item[ID].Price_7Days = eSmithItem.attribute("Price7DaysItem").as_int();
			this->item[ID].Price_30Days = eSmithItem.attribute("Price30DaysItem").as_int();
		}
	}
}

void SCFVipShop::SendInfo(int aIndex){
	if (this->Enabled == 1){
		LPOBJ lpObj = &gObj[aIndex];
		SDHP_SENDSVSHOP pInfo;
		pInfo.h.set(0xFB, 0x19, sizeof(pInfo));
		pInfo.MaxLevel = this->MaxLevel;
		pInfo.MaxOpt = this->MaxOpt;
		pInfo.MaxExc = this->MaxExc;
		pInfo.MaxSkill = this->MaxSkill;
		pInfo.MaxLuck = this->MaxLuck;
		pInfo.pLevel = this->pLevel;
		pInfo.pOpt = this->pOpt;
		pInfo.pSkill = this->pSkill;
		pInfo.pLuck = this->pLuck;
		pInfo.pExc = this->pExc;
		pInfo.pExc1 = this->pExc1;
		pInfo.pExc2 = this->pExc2;
		pInfo.pExc3 = this->pExc3;
		pInfo.pExc4 = this->pExc4;
		pInfo.pExc5 = this->pExc5;
		pInfo.TotalPrice = this->TotalPrice;
		DataSend(aIndex, (BYTE*)&pInfo, pInfo.h.size);
	}
}

void SCFVipShop::RecvBuy(int aIndex, SDHP_BUYSVSHOP * lpMsg){
	if (gObjIsConnected(aIndex) == 0){
		return;
	}
	LPOBJ lpObj = &gObj[aIndex];

	int id = GET_ITEM(lpMsg->ItemType, lpMsg->ItemIndex);
	if (this->item[id].Enabled == true){
		if (lpMsg->mLevel > this->MaxLevel){
			//Hack attempt
			gLog.Output(LOG_SMITHITEM, "[SmithItem] Attempted Character-Buy item with Hack in LEVEL [%s][%s]", gObj[aIndex].Account, gObj[aIndex].Name);
			return;
		}
		if (lpMsg->mOpt > this->MaxOpt){
			//Hack attempt
			gLog.Output(LOG_SMITHITEM, "[SmithItem] Attempted Character-Buy item with Hack in OPT [%s][%s]", gObj[aIndex].Account, gObj[aIndex].Name);
			return;
		}
		if (lpMsg->mLuck > this->MaxLuck){
			gLog.Output(LOG_SMITHITEM, "[SmithItem] Attempted Character-Buy item with Hack in LUCK [%s][%s]", gObj[aIndex].Account, gObj[aIndex].Name);
			return;
		}
		if (lpMsg->mSkill > this->MaxSkill){
			//Hack attempt
			gLog.Output(LOG_SMITHITEM, "[SmithItem] Attempted Character-Buy item with Hack in SKILL [%s][%s]", gObj[aIndex].Account, gObj[aIndex].Name);
			return;
		}
		if (lpMsg->mExc > this->MaxExc)
		{
			//Hack attempt
			gNotice.GCNoticeSend(lpObj->Index, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(896), this->MaxExc);
			gLog.Output(LOG_SMITHITEM, "[SmithItem] Attempted Character-Buy item with Hack in EXCOPT [%s][%s]", gObj[aIndex].Account, gObj[aIndex].Name);
			return;
		}
		if (gItemManager.CheckItemInventorySpace(lpObj, lpMsg->ItemIndex) == 0){
			gNotice.GCNoticeSend(lpObj->Index, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(895));
			return;
		}

		int Val = 0;
		switch (lpMsg->Days){
		case 0:{
			Val = this->item[id].Price_1Day;
		}break;
		case 1:{
			Val = this->item[id].Price_7Days;
		}break;
		case 2:{
			Val = this->item[id].Price_30Days;
		}break;
		}
		int Total = Val;

		if (Val == 0){
			gNotice.GCNoticeSend(lpObj->Index, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(894));
			return;
		}

		if (lpMsg->ExcOption == 32){
			Total += this->pExc;
		}
		if (lpMsg->ExcOption1 == 16){
			Total += this->pExc1;
		}
		if (lpMsg->ExcOption2 == 8){
			Total += this->pExc2;
		}
		if (lpMsg->ExcOption3 == 4){
			Total += this->pExc3;
		}
		if (lpMsg->ExcOption4 == 2){
			Total += this->pExc4;
		}
		if (lpMsg->ExcOption5 == 1){
			Total += this->pExc5;
		}
		Total += (lpMsg->mLevel * this->pLevel);
		Total += (lpMsg->mLuck * this->pLuck);
		Total += (lpMsg->mOpt * this->pOpt);
		Total += (lpMsg->mSkill * this->pSkill);
		BYTE EXCARC = lpMsg->ExcOption + lpMsg->ExcOption1 + lpMsg->ExcOption2 + lpMsg->ExcOption3 + lpMsg->ExcOption4 + lpMsg->ExcOption5;
		TotalPrice = Total;
		if (lpObj->Coin1 >= Total){
			int Days = 1;
			switch (lpMsg->Days){
			case 0:{
				Days = 1;
			}break;
			case 1:{
				Days = 7;
			}break;
			case 2:{
				Days = 30;
			}break;
			}
			time_t t = time(NULL);
			localtime(&t);
			DWORD iTime = (DWORD)t + Days * 86400;
			if (this->FunctionKG == 0){
				GDCreateItemSend(lpObj->Index, 0xEB, 0, 0, id, lpMsg->mLevel, 0, lpMsg->mSkill, lpMsg->mLuck, lpMsg->mOpt, -1, EXCARC, 0, 0, 0, 0, 0xFF, iTime);
			}
			else{
				GDCreateItemSend(lpObj->Index, 0xEB, 0, 0, id, lpMsg->mLevel, 0, lpMsg->mSkill, lpMsg->mLuck, lpMsg->mOpt, -1, EXCARC, 0, 0, 0, 0, 0xFF, 0);
			}
			gCashShop.GDCashShopSubPointSaveSend(lpObj->Index, 0, Total, 0, 0, 0);
			gCashShop.CGCashShopPointRecv(lpObj->Index);
			gNotice.GCNoticeSend(lpObj->Index, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(891));
			gLog.Output(LOG_SMITHITEM, "[SmithItem](%s)(%s) Buy Item:%d Price:%d Total:%d [Level:%d Option:%d Luck:%d Skill:%d ExcOption:%d]",
				gObj[aIndex].Account, gObj[aIndex].Name, id, Val, Total, lpMsg->mLevel, lpMsg->mOpt, lpMsg->mLuck, lpMsg->mSkill, lpMsg->mExc);
		}
		else{
			gNotice.GCNoticeSend(lpObj->Index, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(892));
		}
	}
	else{
		gNotice.GCNoticeSend(lpObj->Index, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(893));
	}
}