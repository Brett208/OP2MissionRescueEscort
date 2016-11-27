#include "DisasterHelper.h"

void DisasterHelper::SetMapProperties(int mapWidth, int mapHeight, bool wrapsEastWest)
{
	if (mapWidth <= 0)
	{
		mapWidth = 32;
	}

	if (mapHeight <= 0)
	{
		mapHeight = 32;
	}

	this->mapWidth = mapWidth;
	this->mapHeight = mapHeight;

	if (wrapsEastWest)
	{
		xOffset = -1;
		yOffset = -1;
	}
}

void DisasterHelper::SetDisasterPercents(int noDisasterPercent, int meteorPercent, 
	int earthquakePercent, int stormPercent, int vortexPercent)
{
	if (noDisasterPercent + meteorPercent + earthquakePercent + stormPercent + vortexPercent != 100)
	{
		return;
	}

	if (noDisasterPercent < 0 || meteorPercent < 0 || earthquakePercent < 0 || stormPercent < 0 || vortexPercent < 0)
	{
		return;
	}

	this->noDisasterPercent = noDisasterPercent;
	this->meteorPercent = meteorPercent;
	this->earthquakePercent = earthquakePercent;
	this->stormPercent = stormPercent;
	this->vortexPercent = vortexPercent;
}

void DisasterHelper::SetMeteorSizePercents(int smallMeteorPercent, int mediumMeteorPercent, int largeMeteorPercent)
{
	if (smallMeteorPercent + mediumMeteorPercent + largeMeteorPercent != 100)
	{
		return;
	}

	if (smallMeteorPercent < 0 || mediumMeteorPercent < 0 || largeMeteorPercent < 0)
	{
		return;
	}

	this->smallMeteorPercent = smallMeteorPercent;
	this->mediumMeteorPercent = mediumMeteorPercent;
	this->largeMeteorPercent = largeMeteorPercent;
}

LOCATION DisasterHelper::GetRandMapLoc()
{
	if (!MapPropertiesSet())
	{
		return LOCATION(xOffset, yOffset);
	}

	return LOCATION(TethysGame::GetRand(mapWidth) + xOffset, TethysGame::GetRand(mapHeight) + yOffset);
}

LOCATION DisasterHelper::GetLocOutsideSafeAreas()
{
	if (!MapPropertiesSet())
	{
		return LOCATION(xOffset, yOffset);
	}

	LOCATION loc = GetRandMapLoc();

	bool largeMeteorInSafeArea = true;
	int numberOfLocsChecked = 0;
	while (largeMeteorInSafeArea)
	{
		for (auto& mapRect : SafeRects)
		{
			if (mapRect.Check(loc))
			{
				loc = GetRandMapLoc();

				numberOfLocsChecked++;

				if (numberOfLocsChecked > 100)
				{
					SendDebugMessage("Unable to find a LOCATION outside of safe areas.");
					return LOCATION(xOffset, yOffset);
				}

				continue;
			}
		}

		break;
	}

	return loc;
}

MAP_RECT DisasterHelper::GetRandMapRect(int rectWidth, int rectHeight)
{
	LOCATION firstRectLoc = GetLocOutsideSafeAreas();

	if (firstRectLoc.x + rectWidth > mapWidth)
	{
		firstRectLoc.x = mapWidth - rectWidth;
	}

	if (firstRectLoc.y + rectHeight < mapHeight)
	{
		firstRectLoc.y = mapHeight - rectHeight;
	}

	return MAP_RECT(firstRectLoc, LOCATION(firstRectLoc.x + rectWidth, firstRectLoc.y + rectHeight));
}

double DisasterHelper::DistanceBetweenPoints(LOCATION loc1, LOCATION loc2)
{
	return std::sqrt(std::pow(loc2.x - loc1.x, 2) + std::pow(loc2.y - loc1.y, 2));
}

void DisasterHelper::CreateRandomDisaster()
{
	int maxDisasterNumber = 100;
	if (!allowVortexes)
	{
		maxDisasterNumber = 100 - vortexPercent;
	}
	int randNum = TethysGame::GetRand(maxDisasterNumber);

	if (randNum < noDisasterPercent)
	{
		// No Disaster this cycle
		return;
	}
	else if (randNum < noDisasterPercent + meteorPercent)
	{
		CreateMeteor();
	}
	else if (randNum < noDisasterPercent + meteorPercent + earthquakePercent)
	{
		CreateEarthquake();
	}
	else if (randNum < noDisasterPercent + meteorPercent + earthquakePercent + stormPercent)
	{
		CreateStorm();
	}
	else if (randNum < noDisasterPercent + meteorPercent + earthquakePercent + stormPercent + vortexPercent)
	{
		CreateVortex();
	}
}

void DisasterHelper::CreateStorm()
{
	if (!MapPropertiesSet())
	{
		return;
	}

	LOCATION startLoc = GetRandMapLoc();
	LOCATION endLoc = GetRandMapLoc();

	int stormDuration = minStormDuration + TethysGame::GetRand(maxStormDuration - minStormDuration);

	TethysGame::SetLightning(startLoc.x, startLoc.y, stormDuration, endLoc.x, endLoc.y);
}

void DisasterHelper::CreateEarthquake()
{
	if (!MapPropertiesSet())
	{
		return;
	}

	LOCATION loc = GetRandMapLoc();
	TethysGame::SetEarthquake(loc.x, loc.y, minQuakeStrength + TethysGame::GetRand(maxQuakeStrength - minQuakeStrength));
}

bool DisasterHelper::DoesPathEnterSafeArea(const LOCATION& pathStartLoc, const LOCATION& pathEndLoc)
{
	if (!MapPropertiesSet())
	{
		return false;
	}

	std::vector<LOCATION> locsOnLine = GetLocationsOnLine(pathStartLoc, pathEndLoc);

	//Check last point on line first.
	for (auto& mapRect : SafeRects)
	{
		if (mapRect.Check(locsOnLine[locsOnLine.size() - 1]))
		{
			return true;
		}
	}

	for (size_t i = 0; i < locsOnLine.size(); i = i + 3)
	{
		LOCATION loc = locsOnLine[i];

		for (auto& mapRect : SafeRects)
		{
			if (mapRect.Check(locsOnLine[i]))
			{
				return true;
			}
		}
	}

	return false;
}

void DisasterHelper::CreateVortex()
{
	if (!MapPropertiesSet())
	{
		return;
	}

	LOCATION vortexStartLoc, vortexEndLoc;

	bool insideSafeArea = true;
	int numberOfPathsChecked = 0;
	while (insideSafeArea)
	{
		MAP_RECT vortexArea = GetRandMapRect(22, 22);

		vortexStartLoc = vortexArea.RandPt();
		vortexEndLoc = vortexArea.RandPt();

		if (DoesPathEnterSafeArea(vortexStartLoc, vortexEndLoc))
		{
			numberOfPathsChecked++;

			if (numberOfPathsChecked > 20)
			{
				SendDebugMessage("Unable to find safe vortex path.");
				return;
			}

			continue;
		}

		break;
	}

	TethysGame::SetTornado(
		vortexStartLoc.x,
		vortexStartLoc.y,
		minVortexDuration + TethysGame::GetRand(maxVortexDuration - minVortexDuration),
		vortexEndLoc.x,
		vortexEndLoc.x,
		false);
}

void DisasterHelper::CreateMeteor()
{
	if (!MapPropertiesSet())
	{
		return;
	}

	LOCATION disasterLoc = GetRandMapLoc();

	int maxMeteorNumber = 100;

	if (!allowLargeMeteors)
	{
		maxMeteorNumber = 100 - largeMeteorPercent;
	}

	int randNumber = TethysGame::GetRand(maxMeteorNumber);
	int meteorSize = 0;

	if (randNumber <= smallMeteorPercent)
	{
		meteorSize = 0;
	}
	else if (randNumber <= smallMeteorPercent + mediumMeteorPercent)
	{
		meteorSize = 1;
	}
	else if (randNumber <= smallMeteorPercent + mediumMeteorPercent + largeMeteorPercent)
	{
		meteorSize = 2;
		disasterLoc = GetLocOutsideSafeAreas();
	}

	TethysGame::SetMeteor(disasterLoc.x, disasterLoc.y, meteorSize);
}

double DisasterHelper::FindSlope(const LOCATION& firstLoc, const LOCATION& secondLoc, UniqueLineSlopeCondition& uniqueSlopeCondition)
{
	uniqueSlopeCondition = UniqueLineSlopeCondition::None;
	if (firstLoc.x == secondLoc.x)
	{
		if (secondLoc.y > firstLoc.y)
		{
			uniqueSlopeCondition = UniqueLineSlopeCondition::PositiveInfinity;
			return 0;
		}
		else if (firstLoc.y > secondLoc.y)
		{
			uniqueSlopeCondition = UniqueLineSlopeCondition::NegativeInfinity;
			return 0;
		}
		else
		{
			return 0;
		}
	}

	return (secondLoc.y - firstLoc.y) / (secondLoc.x - firstLoc.x);
}

std::vector<LOCATION> DisasterHelper::GetLocationsOnLine(LOCATION firstLoc, LOCATION secondLoc)
{
	if (!MapPropertiesSet())
	{
		std::vector<LOCATION> emptyVector;
		return emptyVector;
	}

	//Ensure firstLoc has a lower or equal xCoord then secondLoc.
	if (firstLoc.x > secondLoc.x)
	{
		LOCATION tempLoc = firstLoc;
		firstLoc = secondLoc;
		secondLoc = tempLoc;
	}

	UniqueLineSlopeCondition uniqueLineSlope;
	double slope = FindSlope(firstLoc, secondLoc, uniqueLineSlope);

	if (uniqueLineSlope != UniqueLineSlopeCondition::None || slope > 1 || slope < -1)
	{
		return GetLocationsOnHighSlopeLine(firstLoc, secondLoc, slope, uniqueLineSlope);
	}
	else
	{
		return GetLocationsOnLowSlopeLine(firstLoc, secondLoc, slope);
	}
}

//Assumes firstLoc has a lower x coordinate then secondLoc
std::vector<LOCATION> DisasterHelper::GetLocationsOnLowSlopeLine(const LOCATION& firstLoc, const LOCATION& secondLoc, double slope)
{
	std::vector<LOCATION> locs;

	for (int x = firstLoc.x; x != secondLoc.x; x++)
	{
		double y = slope * (x - firstLoc.x) + firstLoc.y;

		double integral;
		double remainder = modf(y, &integral);

		locs.push_back(LOCATION(x, (int)integral));

		if (remainder != 0.0)
		{
			locs.push_back(LOCATION(x, (int)integral + 1));
		}
	}

	locs.push_back(secondLoc);

	return locs;
}

//Assumes firstLoc has a lower x coordinate then secondLoc
std::vector<LOCATION> DisasterHelper::GetLocationsOnHighSlopeLine(const LOCATION& firstLoc, const LOCATION& secondLoc, double slope, UniqueLineSlopeCondition uniqueLineSlope)
{
	std::vector<LOCATION> locs;

	if (uniqueLineSlope == UniqueLineSlopeCondition::PositiveInfinity)
	{
		for (int y = firstLoc.y; y <= secondLoc.y; y++)
		{
			locs.push_back(LOCATION(firstLoc.x, y));
		}

		return locs;
	}
	else if (uniqueLineSlope == UniqueLineSlopeCondition::NegativeInfinity)
	{
		for (int y = firstLoc.y; y >= secondLoc.y; y--)
		{
			locs.push_back(LOCATION(firstLoc.x, y));
		}

		return locs;
	}

	int y = firstLoc.y;
	while (y != secondLoc.y)
	{
		double x = (y - firstLoc.y) / slope + firstLoc.x;

		double integral;
		double remainder = modf(x, &integral);

		locs.push_back(LOCATION((int)integral, y));

		if (remainder != 0.0)
		{
			locs.push_back(LOCATION((int)integral + 1, y));
		}

		if (slope > 0)
		{
			y++;
		}
		else
		{
			y--;
		}
	}

	/*for (int y = firstLoc.y; y != secondLoc.y; y += 1 * slope)
	{
		double x = (y - firstLoc.y) / slope + firstLoc.x;

		double integral;
		double remainder = modf(x, &integral);

		locs.push_back(LOCATION((int)integral, y));

		if (remainder != 0.0)
		{
			locs.push_back(LOCATION((int)integral + 1, y));
		}
	}*/

	locs.push_back(secondLoc);

	return locs;
}

void DisasterHelper::SendDebugMessage(char* message)
{
#if _DEBUG
	Unit unit;
	TethysGame::AddMessage(unit, message, PlayerNum::Player0, SoundID::sndMessage2);
#endif
}