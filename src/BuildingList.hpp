#pragma once

#include <string>
#include <vector>
#include "Resource.hpp"
#include "ResourceList.hpp"

enum BuildingId
{
	Hydroponics
};

class Building : public Resource
{
public:
	int cap; // Set to 0 to disable

	std::vector<std::pair<ResourceId, float>> costs; // We don't know length at compile-time, so we use a vector

	Building(std::string name) :
		Resource(name), cap(0)
	{}

	Building(std::string name, float amount, int cap, std::vector<std::pair<ResourceId, float>> costs) :
		Resource(name, true, amount), cap(cap), costs(costs)
	{}

	Building(std::string name, bool unlocked, float amount, int cap, std::vector<std::pair<ResourceId, float>> costs) :
		Resource(name, unlocked, amount), cap(cap), costs(costs)
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