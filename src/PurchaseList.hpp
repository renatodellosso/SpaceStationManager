#pragma once

#include <string>
#include <vector>
#include "Resource.hpp"
#include "ResourceList.hpp"

enum PurchaseId
{
	NewColonist,
	Lab,
	Drills
};

class Purchase : public Resource
{
public:
	int cap; // Set to 0 to disable

	std::vector<std::pair<ResourceId, float>> costs; // We don't know length at compile-time, so we use a vector

	Purchase(std::string name) :
		Resource(name), cap(0)
	{}

	Purchase(std::string name, float amount, int cap, std::vector<std::pair<ResourceId, float>> costs) :
		Resource(name, true, amount), cap(cap), costs(costs)
	{}

	Purchase(std::string name, bool unlocked, float amount, int cap, std::vector<std::pair<ResourceId, float>> costs) :
		Resource(name, unlocked, amount), cap(cap), costs(costs)
	{}

	virtual void onPurchase(int amount)
	{}

	virtual std::string getDescription() override;
};

namespace Purchases
{
	class NewColonist : public Purchase
	{
	public:
		NewColonist() : Purchase("New Colonist", true, 0, 0, { { Money, 100 }, { Food, 10 } })
		{}

		void onPurchase(int amount) override;
		std::string getDescription() override;
	};

	class Lab : public Purchase
	{
	public:
		Lab() : Purchase("Lab", true, 0, 1, { { Money, 600 }, { Food, 20 }, { Metal, 5 } })
		{}

		void onPurchase(int amount) override;
		std::string getDescription() override;
	};

	class Drills : public Purchase
	{
	private:
		float bonus = 0.1f;
	public:
		Drills() : Purchase("Drills", false, 0, 5, { { Research, 15 }, { Metal, 25 }, { Money, 250 } })
		{}

		void onPurchase(int amount) override;
		std::string getDescription() override;
	};
}