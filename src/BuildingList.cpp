#pragma once

#include <vector>
#include "Resource.hpp"
#include "BuildingList.hpp"
#include "ResourceList.hpp"
#include "JobList.hpp"
#include "StationData.hpp"

Buildings::Hydroponics::Hydroponics() : Building("Hydroponics", true, 0, 10, { { Food, 10 } })
{}

void Buildings::Hydroponics::onBuild()
{
	//Cast the unique_ptr
	Jobs::Farmer& farmer = *(static_cast<Jobs::Farmer*>(population[Farmer].get()));

	farmer.productivity += 0.1f;

	//Return the farmer to the population
	population[Farmer] = std::make_unique<Jobs::Farmer>(farmer);
}