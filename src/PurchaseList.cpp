#pragma once

#include <string>
#include <vector>
#include "JobList.hpp"
#include "StationData.hpp"
#include "PurchaseList.hpp"

std::string Purchase::getDescription()
{
	return __super::getDescription();
}

void Purchases::NewColonist::onPurchase(int amount)
{
	population[Unassigned]->amount += amount;
}

std::string Purchases::NewColonist::getDescription()
{
	return "Recruits a new colonist";
}

void Purchases::Lab::onPurchase(int amount)
{
	//purchases[PurchaseId::Lab]->unlocked = false; // Causes write access violation for some reason
	resources[Research]->unlocked = true;
	population[Scientist]->unlocked = true;

	purchases[PurchaseId::Drills]->unlocked = true;
}

std::string Purchases::Lab::getDescription()
{
	return "Unlocks research";
}

void Purchases::Drills::onPurchase(int amount)
{
	//Cast the unique_ptr
	Jobs::Miner& miner = *(static_cast<Jobs::Miner*>(population[Miner].get()));

	miner.productivity += bonus;

	//Return the farmer to the population
	population[Miner] = std::make_unique<Jobs::Miner>(miner);
}

std::string Purchases::Drills::getDescription()
{
	return "+" + std::to_string(bonus) + " miner productivity";
}