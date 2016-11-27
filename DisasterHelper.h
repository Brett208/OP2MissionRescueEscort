#pragma once

#include "OP2Helper\OP2Helper.h"
#include "Outpost2DLL\Outpost2DLL.h"
#include <cmath>
#include <vector>

// Ensure all map coordinates passed into DisasterHelper are pre-corrected for the proper offset.
// East-West wrap maps (x - 1, y - 1). Non wrap maps (x + 31, y - 1).
class DisasterHelper
{
public:
	//Tile width and tile height of map.
	void SetMapProperties(int mapWidth, int mapHeight, bool wrapsEastWest);

	void CreateRandomDisaster();
	void CreateMeteor();
	void CreateEarthquake();
	void CreateStorm();
	void CreateVortex();

	//If percent values do not sum to 100, no changes will be made. 
	//Set percent values as a whole number (ie 10 = 10 percent).
	void SetDisasterPercents(int noDisasterPercent, int meteorPercent,
		int earthquakePercent, int stormPercent, int vortexPercent);

	//If percent values do not sum to 100, no changes will be made. 
	//Set percent values as a whole number (ie 10 = 10 percent).
	void SetMeteorSizePercents(int smallMeteorPercent, int mediumMeteorPercent, int largeMeteorPercent);

	void SetEarthquakeStrength(int minStrength, int maxStrength)
	{
		if (minStrength > maxStrength || minStrength < 0)
		{
			return;
		}

		this->minQuakeStrength = minStrength;
		this->maxQuakeStrength = maxStrength;
	}

	//Duration is represented by number of marks
	void SetVortexDuration(int minDuration, int maxDuration)
	{
		if (minDuration > maxDuration || minDuration < 0)
		{
			return;
		}

		this->minVortexDuration = minDuration;
		this->maxVortexDuration = maxDuration;
	}

	//Duration is represented by number of marks
	void SetStormDuration(int minDuration, int maxDuration)
	{
		if (minDuration > maxDuration || minDuration < 0)
		{
			return;
		}

		this->minStormDuration = minDuration;
		this->maxStormDuration = maxDuration;
	}

	void SetAllowVortexes(bool allowVortexes)
	{
		this->allowVortexes = allowVortexes;
	}

	void SetAllowLargeMeteors(bool allowLargeMeteors)
	{
		this->allowLargeMeteors = allowLargeMeteors;
	}

	void AddSafeRect(const MAP_RECT& safeRect)
	{
		SafeRects.push_back(safeRect);
	}

	void ClearSafeRects()
	{
		SafeRects.clear();
	}

	// Attempts to return a LOCATION that exists outside any declared safe areas. 
	// If unable to find a valid LOCATION, LOCATION (0,0) is returned.
	LOCATION GetLocOutsideSafeAreas();

	std::vector<LOCATION> GetLocationsOnLine(LOCATION firstLoc, LOCATION secondLoc);

	bool DoesPathEnterSafeArea(const LOCATION& startLoc, const LOCATION& endLOC);

	bool MapPropertiesSet()
	{
		return mapWidth != 0;
	}

private:
	int xOffset = 31;
	int yOffset = -1;

	int mapWidth;
	int mapHeight;

	int noDisasterPercent = 15;
	int earthquakePercent = 35;
	int meteorPercent = 20;
	int stormPercent = 20;
	int vortexPercent = 10;

	int smallMeteorPercent = 40;
	int mediumMeteorPercent = 40;
	int largeMeteorPercent = 20;

	bool allowVortexes = true;
	bool allowLargeMeteors = true;

	int minQuakeStrength = 0;
	int maxQuakeStrength = 4;

	int minVortexDuration = 5;
	int maxVortexDuration = 20;

	int minStormDuration = 10;
	int maxStormDuration = 55;

	std::vector<MAP_RECT> SafeRects;

	LOCATION GetRandMapLoc();
	MAP_RECT DisasterHelper::GetRandMapRect(int rectWidth, int rectHeight);
	double DistanceBetweenPoints(LOCATION loc1, LOCATION loc2);	

	enum class UniqueLineSlopeCondition { None, PositiveInfinity, NegativeInfinity };

	std::vector<LOCATION> GetLocationsOnHighSlopeLine(const LOCATION& firstLoc, const LOCATION& secondLoc, double slope, UniqueLineSlopeCondition uniqueLineSlope);
	std::vector<LOCATION> GetLocationsOnLowSlopeLine(const LOCATION& firstLoc, const LOCATION& secondLoc, double slope);

	double FindSlope(const LOCATION& firstLoc, const LOCATION& secondLoc, UniqueLineSlopeCondition& uniqueSlopeCondition);

	void SendDebugMessage(char* message);
};