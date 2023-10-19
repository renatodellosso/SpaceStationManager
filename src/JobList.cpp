#include <string>
#include "JobList.hpp"

void Job::onDayEnd()
{
	resources[Food]->amount -= 1;
}

std::string Jobs::Unnassigned::getName()
{
	return "Unnassigned";
}

std::string Jobs::Farmer::getName()
{
	return "Farmer";
}