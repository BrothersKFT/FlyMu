#include "StdAfx.h"
#include "HidManager.h"
#include "Log.h"
#include "MemScript.h"
//#include "Protect.h" // Eltávolítva
#include "ServerInfo.h"
#include "Util.h"

CHidManager gHidManager;

CHidManager::CHidManager()
{
	InitializeCriticalSection(&this->m_HwidCountMutex); // Inicializálás
}

CHidManager::~CHidManager()
{
	DeleteCriticalSection(&this->m_HwidCountMutex); // Törlés
}

bool CHidManager::CheckHardwareId(char HardwareId[36]) // OK
{
	if(gServerInfo.m_DetectionLockTime == 0)
	{
		return 1;
	}

	this->ClearHardwareId();

	for(DWORD i = 0; i < m_HardwareIdInfo.size(); i++)
	{
		if(memcmp(m_HardwareIdInfo[i].HardwareId, HardwareId,sizeof(m_HardwareIdInfo[i].HardwareId)) == 0)
		{
			return 0;
		}
	}

	return 1;
}

void CHidManager::InsertHardwareId(char HardwareId[36])
{
	HARDWARE_ID_INFO info;

	memcpy(info.HardwareId,HardwareId,sizeof(info.HardwareId));

	info.LastDetectionTime = GetTickCount();

	this->m_HardwareIdInfo.push_back(info);
}

void CHidManager::ClearHardwareId()
{
	for(std::vector<HARDWARE_ID_INFO>::iterator it=this->m_HardwareIdInfo.begin();it != this->m_HardwareIdInfo.end();it++)
	{
		if((GetTickCount()-it->LastDetectionTime) > (DWORD)(gServerInfo.m_DetectionLockTime*1000))
		{
			it = this->m_HardwareIdInfo.erase(it);
			break;
		}
	}
}

void CHidManager::DeleteAllHardwareId()
{
	int count = this->m_HardwareIdInfo.size();
	this->m_HardwareIdInfo.clear();
	LogAdd(LOG_BLACK, "�Las Prohibiciones Temporales De Hardware Se Eliminaron Con Exito! Total %d HwIds Eliminados.", count);
}

void CHidManager::RemoveHardwareId(char* HardwareId)
{
	// ... existing RemoveHardwareId implementation ...
}

bool CHidManager::CheckHwidConnectionLimit(char* HardwareId)
{
	//std::lock_guard<std::mutex> lock(this->m_HwidCountMutex);
	EnterCriticalSection(&this->m_HwidCountMutex); // Zárolás

	bool result = true; // Eredmény változó

	if (gServerInfo.m_MaxHwidConnection <= 0) // Ha a limit 0 vagy negatív, nincs korlátozás
	{
		// result marad true
	}
	else
	{
		std::string hwidStr(HardwareId);
		auto it = this->m_HwidConnectionCount.find(hwidStr);

		if (it == this->m_HwidConnectionCount.end()) // Ha még nincs bejegyzés, akkor biztosan limit alatt van
		{
			// result marad true
		}
		else
		{
			// Ellenőrizzük, hogy a jelenlegi szám kisebb-e a limitnél
			result = (it->second < gServerInfo.m_MaxHwidConnection);
		}
	}

	LeaveCriticalSection(&this->m_HwidCountMutex); // Feloldás
	return result;
}

void CHidManager::IncrementHwidCount(char* HardwareId)
{
	//std::lock_guard<std::mutex> lock(this->m_HwidCountMutex);
	EnterCriticalSection(&this->m_HwidCountMutex); // Zárolás

	std::string hwidStr(HardwareId);
	this->m_HwidConnectionCount[hwidStr]++;
	// LogAdd(LOG_DEBUG, "[HWID Count] Incremented %s to %d", hwidStr.c_str(), this->m_HwidConnectionCount[hwidStr]);

	LeaveCriticalSection(&this->m_HwidCountMutex); // Feloldás
}

void CHidManager::DecrementHwidCount(char* HardwareId)
{
	//std::lock_guard<std::mutex> lock(this->m_HwidCountMutex);
	EnterCriticalSection(&this->m_HwidCountMutex); // Zárolás

	std::string hwidStr(HardwareId);
	auto it = this->m_HwidConnectionCount.find(hwidStr);
	if (it != this->m_HwidConnectionCount.end())
	{
		it->second--;
		// LogAdd(LOG_DEBUG, "[HWID Count] Decremented %s to %d", hwidStr.c_str(), it->second);
		if (it->second <= 0)
		{
			this->m_HwidConnectionCount.erase(it);
			// LogAdd(LOG_DEBUG, "[HWID Count] Removed %s", hwidStr.c_str());
		}
	}

	LeaveCriticalSection(&this->m_HwidCountMutex); // Feloldás
}
