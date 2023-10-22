#include <string>
#include <iostream>
#include <math.h>
#include "JobList.hpp"
#include "StationData.hpp"

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

Jobs::Unnassigned::Unnassigned()
	: Job("Unnassigned")
{
	unlocked = true;
	amount = 10;
}

Jobs::Farmer::Farmer()
	: Job("Farmer")
{
	unlocked = true;
}

void Jobs::Farmer::onDayEnd()
{
	resources[Food]->amount += 1 * amount * productivity;
	__super::onDayEnd();
}