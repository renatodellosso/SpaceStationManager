#pragma once

#include <string>
#include <map>
#include <memory>
#include "Resource.hpp"
#include "StationData.hpp"

std::string stationName;
int day;
std::map<JobId, std::unique_ptr<Resource>> population;
std::map<ResourceId, std::unique_ptr<Resource>> resources;