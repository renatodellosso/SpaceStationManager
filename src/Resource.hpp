#pragma once

#include <string>

class Resource
{
public:
	float amount = 0;
	bool unlocked = false;

	virtual std::string getName() = 0;

	virtual void onDayEnd()
	{}
};