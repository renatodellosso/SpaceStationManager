#pragma once

#include <string>

class Resource
{
private:
	std::string name;
public:
	float amount = 0;
	bool unlocked = false;

	Resource(std::string name)
		: name(name)
	{}

	virtual std::string getName();

	virtual void onDayEnd()
	{}
};