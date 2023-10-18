#pragma once
#include <string>

class Resource
{
public:
	int amount = 0;

	virtual std::string GetName() = 0;

	virtual void OnDayEnd()
	{}
};