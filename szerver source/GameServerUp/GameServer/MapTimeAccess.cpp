#include "stdafx.h"
#include "MapTimeAccess.h"
#include "MemScript.h"
#include "Util.h"
#include "Gate.h"
#include "GameMain.h"
#include "ObjectManager.h"
#include "Notice.h"
#include "Message.h"
#include <windows.h> // For SYSTEMTIME

CMapTimeAccess gMapTimeAccess;

CMapTimeAccess::CMapTimeAccess() {
	this->m_Rules.clear();
}

CMapTimeAccess::~CMapTimeAccess() {
}

int CMapTimeAccess::CalculateMinutesOfWeek(int dayOfWeek, int hour, int minute) {
	// Assuming Sunday is 0, Saturday is 6
	return (dayOfWeek * 24 * 60) + (hour * 60) + minute;
}

void CMapTimeAccess::Load(char* path) {
	CMemScript* lpMemScript = new CMemScript;

	if (lpMemScript == 0) {
		ErrorMessageBox(MEM_SCRIPT_ALLOC_ERROR, path);
		return;
	}

	if (lpMemScript->SetBuffer(path) == 0) {
		ErrorMessageBox(lpMemScript->GetLastError());
		delete lpMemScript;
		return;
	}

	this->m_Rules.clear();
	int rulesLoaded = 0; // Counter for loaded rules
	try {
		while (true) {
			if (lpMemScript->GetToken() == TOKEN_END) {
				break;
			}

			if (strcmp("end", lpMemScript->GetString()) == 0) {
				break;
			}

			MapTimeAccessRule rule;

			rule.MapID = lpMemScript->GetNumber();

			char szDayOfWeek[10];
			strcpy_s(szDayOfWeek, lpMemScript->GetAsString());
			rule.DayOfWeek = (strcmp(szDayOfWeek, "*") == 0) ? -1 : atoi(szDayOfWeek);

			rule.OpenHour = lpMemScript->GetAsNumber();
			rule.OpenMinute = lpMemScript->GetAsNumber();
			rule.DurationMinutes = lpMemScript->GetAsNumber();

			char szKickGate[10];
			strcpy_s(szKickGate, lpMemScript->GetAsString());
			rule.KickGate = (strcmp(szKickGate, "*") == 0 || strlen(szKickGate) == 0) ? 17 : atoi(szKickGate); // Default 17 (Lorencia)

			// Basic Validation
			if ((rule.DayOfWeek < -1 || rule.DayOfWeek > 6) ||
				(rule.OpenHour < 0 || rule.OpenHour > 23) ||
				(rule.OpenMinute < 0 || rule.OpenMinute > 59) ||
				(rule.DurationMinutes <= 0)) {
				LogAdd(LOG_BLACK, "[MapTimeAccess] Invalid rule format for MapID %d. Skipping.", rule.MapID);
				continue;
			}

			// Calculate helper values (handle day wildcard later during check)
			if(rule.DayOfWeek != -1) {
				rule.OpenTimeMinutesOfWeek = CalculateMinutesOfWeek(rule.DayOfWeek, rule.OpenHour, rule.OpenMinute);
				rule.CloseTimeMinutesOfWeek = rule.OpenTimeMinutesOfWeek + rule.DurationMinutes;
			}
			else {
				// For wildcard day, we'll calculate on the fly during check based on the *current* day.
				rule.OpenTimeMinutesOfWeek = -1; // Indicate wildcard
				rule.CloseTimeMinutesOfWeek = -1;
			}
			

			this->m_Rules[rule.MapID].push_back(rule);
			rulesLoaded++; // Increment counter
		}
	}
	catch (...) {
		ErrorMessageBox(lpMemScript->GetLastError());
		LogAdd(LOG_RED, "[MapTimeAccess] Exception caught while parsing file: %s. Error: %s", path, lpMemScript->GetLastError());
	}

	LogAdd(LOG_BLACK, "[MapTimeAccess] Loaded %d rules from %d map entries.", rulesLoaded, this->m_Rules.size());
	delete lpMemScript;
}

// Check if the *current* time falls within the rule's allowed interval
bool CMapTimeAccess::IsTimeInRange(const MapTimeAccessRule& rule, int currentDayOfWeek, int currentHour, int currentMinute) {
    int ruleDay = rule.DayOfWeek;
    bool result = false; // Initialize result

    // If the rule's day is wildcard, or matches the current day
    if (ruleDay == -1 || ruleDay == currentDayOfWeek) {
		// Calculate open/close times for the *current* day
		int openTimeMinutesCurrentDay = CalculateMinutesOfWeek(currentDayOfWeek, rule.OpenHour, rule.OpenMinute);
			int closeTimeMinutesCurrentDay = openTimeMinutesCurrentDay + rule.DurationMinutes;
		int currentMinutesCurrentWeek = CalculateMinutesOfWeek(currentDayOfWeek, currentHour, currentMinute);

		// Check if current time is within the interval for *this specific day*
        // Note: This handles wrap-around midnight implicitly because we calculate based on the *current* day.
        // Example: Open 22:00, Duration 180 (closes 01:00 next day)
        // If current time is 23:00 (day X), openTime is calculated for day X, closeTime is calculated for day X.
        // currentMinutesCurrentWeek (23:00) >= openTimeMinutesCurrentDay (22:00) -> allowed.
        // If current time is 00:30 (day X+1), openTime/closeTime are calculated for day X+1.
        // currentMinutesCurrentWeek (00:30 day X+1) might be < openTimeMinutesCurrentDay (22:00 day X+1), needs careful check.

        // Simpler approach: Check if current time is >= open time AND current time is < close time.
        // This requires handling the week wrap-around for the close time if duration crosses midnight/week end.

		// Corrected Logic: Calculate absolute start and end minutes in the week for the rule.
		int ruleStartMinutesOfWeek = CalculateMinutesOfWeek((ruleDay == -1 ? currentDayOfWeek : ruleDay), rule.OpenHour, rule.OpenMinute);
		int ruleEndMinutesOfWeek = ruleStartMinutesOfWeek + rule.DurationMinutes;
		int currentMinutesOfWeek = CalculateMinutesOfWeek(currentDayOfWeek, currentHour, currentMinute);
		
		const int totalMinutesInWeek = 7 * 24 * 60;

		if (ruleEndMinutesOfWeek >= totalMinutesInWeek) { // Rule interval crosses the week boundary (e.g., Saturday night to Sunday morning)
			// Check if current time is in the first part (before week end) OR in the second part (after week start)
			result = (currentMinutesOfWeek >= ruleStartMinutesOfWeek || currentMinutesOfWeek < (ruleEndMinutesOfWeek % totalMinutesInWeek));
		}
		else { // Rule interval is within the same week
			result = (currentMinutesOfWeek >= ruleStartMinutesOfWeek && currentMinutesOfWeek < ruleEndMinutesOfWeek);
		}
    }
    //else: Rule day doesn't match current day, result remains false

    return result;
}


bool CMapTimeAccess::IsMoveAllowed(int mapId, int gate /*= -1*/) {
	// LogAdd(LOG_BLUE, "[MapTimeAccess] IsMoveAllowed called for MapID: %d", mapId); // REMOVED
	auto it = this->m_Rules.find(mapId);
	if (it == this->m_Rules.end()) {
		// LogAdd(LOG_BLUE, "[MapTimeAccess] No rules found for MapID: %d. Allowing move.", mapId); // REMOVED
		return true; // No rules for this map, always allowed
	}

	SYSTEMTIME time;
	GetLocalTime(&time);
		int currentDayOfWeek = time.wDayOfWeek;
		int currentHour = time.wHour;
		int currentMinute = time.wMinute;

	// LogAdd(LOG_BLUE, "[MapTimeAccess] Checking rules for MapID: %d. Current Time: Day %d, %02d:%02d", mapId, currentDayOfWeek, currentHour, currentMinute); // REMOVED

	const std::vector<MapTimeAccessRule>& rules = it->second;
	for (std::vector<MapTimeAccessRule>::const_iterator iter = rules.begin(); iter != rules.end(); ++iter) {
		const MapTimeAccessRule& rule = *iter;
		// LogAdd(LOG_BLUE, "[MapTimeAccess]  - Checking Rule: Day %d, %02d:%02d, Duration %d", rule.DayOfWeek, rule.OpenHour, rule.OpenMinute, rule.DurationMinutes); // REMOVED
		if (IsTimeInRange(rule, currentDayOfWeek, currentHour, currentMinute)) {
			// LogAdd(LOG_BLUE, "[MapTimeAccess]  - Rule MATCHED. Allowing move."); // REMOVED
			return true; // Found a matching rule that allows access now
		}
	}

	// LogAdd(LOG_BLUE, "[MapTimeAccess] No matching rule allows access for MapID: %d at current time. Denying move.", mapId); // REMOVED
	return false; // No active rule allows access right now
}

int CMapTimeAccess::GetKickGate(int mapId) {
	auto it = this->m_Rules.find(mapId);
	if (it != this->m_Rules.end() && !it->second.empty()) {
		// In theory, all rules for the same map should have the same kick gate,
		// but for simplicity, we just return the one from the first rule found.
		// If different kick gates per time slot are needed, this logic needs refinement.
		return it->second[0].KickGate;
	}
	return 17; // Default Lorencia gate if no rule or kick gate specified
}

void CMapTimeAccess::CheckAndKickPlayers() {
	// LogAdd(LOG_BLUE, "[MapTimeAccess] CheckAndKickPlayers timer executing..."); // Log timer execution - REMOVED
	SYSTEMTIME time;
	GetLocalTime(&time);
		int currentDayOfWeek = time.wDayOfWeek;
		int currentHour = time.wHour;
		int currentMinute = time.wMinute;

	for (int n = OBJECT_START_USER; n < MAX_OBJECT; ++n) {
		// Check if the object is a user, fully connected and in playing state
		if (gObj[n].Connected != OBJECT_ONLINE || gObj[n].State != OBJECT_PLAYING || gObj[n].Type != OBJECT_USER) {
			continue;
		}

		LPOBJ lpObj = &gObj[n];

		// Find rules for the player's current map
		auto it = this->m_Rules.find(lpObj->Map);
		if (it == this->m_Rules.end()) {
			continue; // No rules for this map, player is fine
		}

		// Check if *any* active rule allows the player to be on this map *right now*
		bool allowed = false;
		const std::vector<MapTimeAccessRule>& rules = it->second;
		for (std::vector<MapTimeAccessRule>::const_iterator iter = rules.begin(); iter != rules.end(); ++iter) {
			const MapTimeAccessRule& rule = *iter;
			if (IsTimeInRange(rule, currentDayOfWeek, currentHour, currentMinute)) {
				allowed = true;
				break; // Found a valid time slot, player can stay
			}
		}

		// If no active rule allows the player to be here
		if (!allowed)
		{
			// Kick the player
			int kickGate = rules[0].KickGate; // Get kick gate from the first rule (assuming they are consistent)

			// Send message (Use the updated index 2008)
			gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(2008)); 

			// Teleport the player
			GATE_INFO GateInfo; // Temporary struct to check gate validity
			if (gGate.GetInfo(kickGate, &GateInfo)) { // Check if the gate is valid by trying to get its info
				int originalMapForKickLog = lpObj->Map; // Store the original map in a variable
				gObjMoveGate(lpObj->Index, kickGate);
			}
		}
	}
} 