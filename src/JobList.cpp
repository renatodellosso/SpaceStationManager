#include <string>
#include <iostream>
#include <math.h>
#include "JobList.hpp"
#include "ResourceList.hpp"
#include "StationData.hpp"

std::string Job::getDescription()
{
	return __super::getDescription();
}

void Job::onDayEnd()
{
	resources[Food]->amount -= 1 * amount;

	int deficit = resources[Food]->amount < 0 ? -resources[Food]->amount : 0;
	if (deficit > 0)
	{
		amount -= ceil(deficit / 3);
		if (amount < 0)
			amount = 0;
	}
}

void Jobs::Farmer::onDayEnd()
{
	resources[Food]->amount += 1 * amount * productivity;
	__super::onDayEnd();
}

std::string Jobs::Farmer::getDescription()
{
	return "Produces " + std::to_string(amount * productivity) + " food per day";
}

void Jobs::Miner::onDayEnd()
{
	resources[Metal]->amount += 1 * amount * productivity;
	__super::onDayEnd();
}

std::string Jobs::Miner::getDescription()
{
	return "Produces " + std::to_string(amount * productivity) + " metal per day";
}

void Jobs::Scientist::onDayEnd()
{
	resources[Research]->amount += 1 * amount * productivity;
	__super::onDayEnd();
}

std::string Jobs::Scientist::getDescription()
{
	return "Produces " + std::to_string(amount * productivity) + " research per day";
}