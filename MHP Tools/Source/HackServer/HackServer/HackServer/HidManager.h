#ifndef _HIDMANAGER_H_
#define _HIDMANAGER_H_
#pragma once

#include <map>
#include <string>
//#include <mutex> // Eltávolítva
#include <windows.h> // CRITICAL_SECTION miatt
#include <vector> // Visszaállítva vector-ra

#define MAX_HID_INFO 1000 // Ez valószínűleg már nem szükséges a vector miatt

struct HARDWARE_ID_INFO
{
	char HardwareId[36];
	DWORD LastDetectionTime;
};

class CHidManager
{
public:
	CHidManager();
	virtual ~CHidManager();
	bool CheckHardwareId(char HardwareId[36]);
	void InsertHardwareId(char HardwareId[36]);
	void ClearHardwareId();
	void DeleteAllHardwareId();
	void Load(char* path);
	void RemoveHardwareId(char* HardwareId);
	bool CheckHwidConnectionLimit(char* HardwareId);
	void IncrementHwidCount(char* HardwareId);
	void DecrementHwidCount(char* HardwareId);
//private:
	std::vector<HARDWARE_ID_INFO> m_HardwareIdInfo; // Visszaállítva vector-ra
	//int m_count; // Eltávolítva, vector kezeli
	std::map<std::string, int> m_HwidConnectionCount;
	//std::mutex m_HwidCountMutex; // Eltávolítva
	CRITICAL_SECTION m_HwidCountMutex; // Cserélve CRITICAL_SECTION-re
};

extern CHidManager gHidManager;
#endif