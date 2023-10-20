#include <string>
#include <iostream>
#include "JobList.hpp"
#include "StationData.hpp"

void Job::onDayEnd()
{
	resources[Food]->amount -= 1 * amount;
}

std::string Jobs::Unnassigned::getName()
{
	return "Unnassigned";
}

std::string Jobs::Farmer::getName()
{
	return "Farmer";
}

void Jobs::Farmer::onDayEnd()
{
	__super::onDayEnd();
	resources[Food]->amount += 1 * amount * productivity;
}