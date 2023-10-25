#pragma once

#include <string>
#include <map>
#include <memory>
#include "Resource.hpp"
#include "JobList.hpp"
#include "BuildingList.hpp"
#include "PurchaseList.hpp"

extern std::string stationName;
extern int day;
extern std::map<JobId, std::unique_ptr<Job>> population;
extern std::map<ResourceId, std::unique_ptr<Resource>> resources;
extern std::map<BuildingId, std::unique_ptr<Building>> buildings;
extern std::map<PurchaseId, std::unique_ptr<Purchase>> purchases;