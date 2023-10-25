#pragma once

#include <string>

class Resource
{
public:
	const std::string name;
	float amount = 0;
	bool unlocked = false;

	Resource(std::string name)
		: name(name)
	{}

	Resource(std::string name, float amount)
		: name(name), unlocked(true), amount(amount)
	{}

	Resource(std::string name, bool unlocked, float amount)
		: name(name), unlocked(unlocked), amount(amount)
	{}

	virtual void onDayEnd()
	{}

	virtual std::string getDescription();
};