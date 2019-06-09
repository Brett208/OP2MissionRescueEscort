#pragma once

#include"Outpost2DLL/Outpost2DLL.h"
#include <vector>

enum class UniqueLineSlopeCondition { None, PositiveInfinity, NegativeInfinity };

double FindSlope(const LOCATION& firstLoc, const LOCATION& secondLoc, UniqueLineSlopeCondition& uniqueSlopeCondition)
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

//Assumes firstLoc has a lower x coordinate then secondLoc
std::vector<LOCATION> GetLocationsOnLowSlopeLine(const LOCATION& firstLoc, const LOCATION& secondLoc, double slope)
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
std::vector<LOCATION> GetLocationsOnHighSlopeLine(const LOCATION& firstLoc, const LOCATION& secondLoc, double slope, UniqueLineSlopeCondition uniqueLineSlope)
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

	locs.push_back(secondLoc);

	return locs;
}

std::vector<LOCATION> GetLocationsOnLine(LOCATION firstLoc, LOCATION secondLoc)
{
	//if (!MapPropertiesSet())
	//{
	//	std::vector<LOCATION> emptyVector;
	//	return emptyVector;
	//}

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

bool DoesPathEnterSafeArea(const LOCATION& pathStartLoc, const LOCATION& pathEndLoc, std::vector<MAP_RECT>& safeRects)
{
	std::vector<LOCATION> locsOnLine = GetLocationsOnLine(pathStartLoc, pathEndLoc);

	//Check last point on line first.
	for (auto& mapRect : safeRects)
	{
		if (mapRect.Check(locsOnLine[locsOnLine.size() - 1]))
		{
			return true;
		}
	}

	for (std::size_t i = 0; i < locsOnLine.size(); i = i + 3)
	{
		LOCATION loc = locsOnLine[i];

		for (auto& mapRect : safeRects)
		{
			if (mapRect.Check(locsOnLine[i]))
			{
				return true;
			}
		}
	}

	return false;
}
