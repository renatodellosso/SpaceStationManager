#pragma once

#include <string>
#include <vector>
#include "Resource.hpp"
#include "BuildingList.hpp"
#include "ResourceList.hpp"
#include "JobList.hpp"
#include "StationData.hpp"

std::string Building::getDescription()
{
	return __super::getDescription();
}

void Buildings::Hydroponics::onBuild(int amount)
{
	//Cast the unique_ptr
	Jobs::Farmer& farmer = *(static_cast<Jobs::Farmer*>(population[Farmer].get()));

	farmer.productivity += bonus;

	//Return the farmer to the population
	population[Farmer] = std::make_unique<Jobs::Farmer>(farmer);
}

std::string Buildings::Hydroponics::getDescription()
{
	return "+" + std::to_string(amount * bonus) + " farmer productivity";
}

void Buildings::DataMiner::onDayEnd()
{
	resources[Money]->amount += productivity * amount;
}

std::string Buildings::DataMiner::getDescription()
{
	return "+" + std::to_string(productivity * amount) + " $ per day";
}

void Buildings::RentalPod::onDayEnd()
{
	resources[Money]->amount += productivity * amount;
	resources[Food]->amount -= foodConsumption * amount;
}

std::string Buildings::RentalPod::getDescription()
{
	return "+" + std::to_string(productivity * amount) + " $ per day, -" + std::to_string(foodConsumption * amount) + " food per day";
}
