#pragma once

#include <string>
#include <vector>
#include "Resource.hpp"
#include "ResourceList.hpp"

enum BuildingId
{
	Hydroponics,
	DataMiner,
	RentalPod
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

	virtual void onBuild(int amount)
	{}

	virtual void onDayEnd()
	{}

	virtual std::string getDescription() override;
};

namespace Buildings
{
	class Hydroponics : public Building
	{
	private:
		float bonus = 0.1f;
	public:
		Hydroponics() : Building("Hydroponics", true, 0, 10, { { Food, 10 }, { Metal, 5 } })
		{}

		void onBuild(int amount) override;
		std::string getDescription() override;
	};

	class DataMiner : public Building
	{
	private:
		float productivity = 10.0f;
	public:
		DataMiner() : Building("Data Miner", true, 0, 0, { { Money, 100 }, { Metal, 5 } })
		{}

		void onDayEnd() override;
		std::string getDescription() override;
	};

	class RentalPod : public Building
	{
	private:
		float productivity = 45.0f, foodConsumption = 1;
	public:
		RentalPod() : Building("Rental Pod", true, 0, 0, { { Money, 300 }, { Metal, 10 } })
		{}

		void onDayEnd() override;
		std::string getDescription() override;
	};
}