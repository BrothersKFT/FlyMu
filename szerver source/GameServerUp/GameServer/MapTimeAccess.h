#pragma once

#include <map>
#include <vector>
#include "User.h" // Include User.h or necessary headers for LPOBJ

struct MapTimeAccessRule {
	int MapID;
	int DayOfWeek; // -1 for wildcard '*'
	int OpenHour;
	int OpenMinute;
	int DurationMinutes;
	int KickGate;  // Default Lorencia gate (e.g., 17) if '*'
	// Calculated helper values
	int OpenTimeMinutesOfWeek;
	int CloseTimeMinutesOfWeek; // Exclusive
};

class CMapTimeAccess {
public:
	CMapTimeAccess();
	virtual ~CMapTimeAccess();

	void Load(char* path);
	bool IsMoveAllowed(int mapId, int gate = -1); // Check if moving to mapId (optionally via a specific gate) is allowed now
	void CheckAndKickPlayers();
	int GetKickGate(int mapId); // Gets the appropriate kick gate for a map (if restricted and closed)

private:
	std::map<int, std::vector<MapTimeAccessRule>> m_Rules;
	bool IsTimeInRange(const MapTimeAccessRule& rule, int currentDayOfWeek, int currentHour, int currentMinute);
	int CalculateMinutesOfWeek(int dayOfWeek, int hour, int minute);

};

extern CMapTimeAccess gMapTimeAccess; 