#pragma once

#include <string>
#include <map>
#include <memory>
#include "Resource.hpp"
#include "JobList.hpp"
#include "ResourceList.hpp"
#include "BuildingList.hpp"
#include "StationData.hpp"

std::string stationName;
int day;

std::map<JobId, std::unique_ptr<Job>> population;
std::map<ResourceId, std::unique_ptr<Resource>> resources;
std::map<BuildingId, std::unique_ptr<Building>> buildings;