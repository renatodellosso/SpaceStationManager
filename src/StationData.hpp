#pragma once

#include <string>
#include <map>
#include <memory>
#include "Resource.hpp"

enum JobId
{
	Unassigned,
	Farmer
};

enum ResourceId
{
	Money,
	Food,
};

extern std::string stationName;
extern int day;
extern std::map<JobId, std::unique_ptr<Resource>> population;
extern std::map<ResourceId, std::unique_ptr<Resource>> resources;