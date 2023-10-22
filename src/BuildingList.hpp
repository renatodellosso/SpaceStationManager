#pragma once

#include <string>
#include "Resource.hpp"
#include "StationData.hpp"

class Building : public Resource
{
public:
	int cap; // Set to 0 to disable

	std::pair<ResourceId, float> cost;

	Building(std::string name) :
		Resource(name), cap(0)
	{}

	Building(std::string name, float amount, int cap) :
		Resource(name, true, amount), cap(cap)
	{}

	Building(std::string name, bool unlocked, float amount, int cap) :
		Resource(name, unlocked, amount), cap(cap)
	{}

	virtual void onBuild()
	{}
};

namespace Buildings
{
	class Hydroponics : public Building
	{
	public:
		Hydroponics();

		void onBuild() override;
	};
}