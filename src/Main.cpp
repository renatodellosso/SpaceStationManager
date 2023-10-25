// SpaceStationManager.cpp : This file contains the 'main' function. Program
// execution begins and ends there.
//
#pragma once

#include <conio.h>
#include <iostream>
#include <map>
#include <sstream>
#include "JobList.hpp"
#include "ResourceList.hpp"
#include "BuildingList.hpp"
#include "PurchaseList.hpp"
#include "StationData.hpp"

void initVars();
void listPopulation(bool withKeybinds = false);
void listResources(bool withKeybinds = false);
void listBuildings(bool withKeybinds = false);
void listPurchases(bool withKeybinds = false);
void mainMenu();
void endDay();
void assignJobs(std::string mode = "");
void build(std::string mode = "");
void purchase(std::string mode = "");
std::vector<std::pair<ResourceId, float>> getTotalCost(std::vector<std::pair<ResourceId, float>> baseCost, int times);
bool hasResources(std::vector<std::pair<ResourceId, float>> cost);
void spendResources(std::vector<std::pair<ResourceId, float>> cost);
std::string listCost(std::vector<std::pair<ResourceId, float>> cost);

char getCharInput()
{
	char input = _getch();
	return input;
}

std::string getStringInput()
{
	std::string input;
	std::getline(std::cin, input);
	return input;
}

std::string keybinds = "1234567890qwertyuiopasdfghjklzxcvbnm";
char indexToKeybind(int index)
{
	return keybinds[index];
}

int keybindToIndex(char keybind)
{
	return keybinds.find(keybind);
}

void pause()
{
	std::cout << "Press any key to continue...";
	(void)_getch();  // Cast to void to show we're ignoring the return value
}

void clearScreen()
{
	system("cls");  // Different for non-Windows OS's
}

int main()
{
	std::cout << "Welcome to Space Station Manager!\n\n";
	pause();
	clearScreen();

	initVars();

	std::cout << "Enter a station name: ";
	stationName = getStringInput();

	clearScreen();
	mainMenu();
}

void initVars()
{
	population[Unassigned] = std::make_unique<Jobs::Unnassigned>();
	population[Farmer] = std::make_unique<Jobs::Farmer>();
	population[Miner] = std::make_unique<Jobs::Miner>();
	population[Scientist] = std::make_unique<Jobs::Scientist>();

	resources[Money] = std::make_unique<Resources::Money>();
	resources[Food] = std::make_unique<Resources::Food>();
	resources[Metal] = std::make_unique<Resources::Metal>();
	resources[Research] = std::make_unique<Resources::Research>();

	buildings[Hydroponics] = std::make_unique<Buildings::Hydroponics>();
	buildings[DataMiner] = std::make_unique<Buildings::DataMiner>();
	buildings[RentalPod] = std::make_unique<Buildings::RentalPod>();

	purchases[NewColonist] = std::make_unique<Purchases::NewColonist>();
	purchases[Lab] = std::make_unique<Purchases::Lab>();
	purchases[Drills] = std::make_unique<Purchases::Drills>();
}

void mainMenu()
{
	std::cout << stationName << " - Day " << day << "\n\n";

	listPopulation();
	listBuildings();
	listResources();

	std::cout << "[1]: Assign jobs\n";
	std::cout << "[2]: Build\n";
	std::cout << "[3]: Purchase\n";
	std::cout << "[ ]: End day\n";

	char input = getCharInput();

	switch (input)
	{
	case ' ':
	{
		clearScreen();
		endDay();
		break;
	}
	case '1':
	{
		clearScreen();
		assignJobs();
		break;
	}
	case '2':
	{
		clearScreen();
		build();
		break;
	}
	case '3':
	{
		clearScreen();
		purchase();
		break;
	}
	default:
	{
		clearScreen();
		std::cout << "Invalid input\n\n";
		mainMenu();
		break;
	}
	}
}

void listResources(bool withKeybinds)
{
	std::cout << "Resources:\n";

	int index = 0;
	for (auto& resource : resources)
	{
		if (resource.second->unlocked)
		{
			if (withKeybinds)
			{
				std::cout << "[" << indexToKeybind(index) << "]: ";
			}

			std::cout << resource.second->name << ": " << resource.second->amount;

			std::string desc = resource.second->getDescription();
			if (!desc.empty())
				std::cout << " - " << desc;

			std::cout << "\n";

			index++;
		}
	}

	std::cout << "\n";
}

void listPopulation(bool withKeybinds)
{
	std::cout << "Population:\n";

	int index = 0;
	for (auto& job : population)
	{
		if (job.second->unlocked)
		{
			if (withKeybinds)
			{
				std::cout << "[" << indexToKeybind(index) << "]: ";
			}

			std::cout << job.second->name << ": " << job.second->amount;

			std::string desc = job.second->getDescription();
			if (!desc.empty())
				std::cout << " - " << desc;

			std::cout << "\n";
		}

		index++;
	}

	std::cout << "\n";
}

void listBuildings(bool withKeybinds)
{
	std::cout << "Buildings:\n";

	int index = 0;
	for (auto& building : buildings)
	{
		if (building.second->unlocked)
		{
			if (withKeybinds)
			{
				std::cout << "[" << indexToKeybind(index) << "]: ";
			}

			std::cout << building.second->name << ": " << building.second->amount;

			if (building.second->cap > 0)
				std::cout << "/" << building.second->cap;

			std::string desc = building.second->getDescription();
			if (!desc.empty())
				std::cout << " - " << desc;

			std::cout << "\n";

			if (withKeybinds)
			{
				std::cout << "\tCost: " << listCost(building.second->costs) << "\n";
			}
		}

		index++;
	}

	std::cout << "\n";
}

void listPurchases(bool withKeybinds)
{
	std::cout << "Purchases:\n";

	int index = 0;
	for (auto& purchase : purchases)
	{
		if (purchase.second->unlocked)
		{
			if (withKeybinds)
			{
				std::cout << "[" << indexToKeybind(index) << "]: ";
			}

			std::cout << purchase.second->name << ": " << purchase.second->amount;

			if (purchase.second->cap > 0)
				std::cout << "/" << purchase.second->cap;

			std::string desc = purchase.second->getDescription();
			if (!desc.empty())
				std::cout << " - " << desc;

			std::cout << "\n";

			if (withKeybinds)
			{
				std::cout << "\tCost: " << listCost(purchase.second->costs) << "\n";
			}
		}

		index++; // We could write some code to keep keybinds sequential
	}

	std::cout << "\n";
}

std::vector<std::pair<ResourceId, float>> getTotalCost(BuildingId building)
{
	return std::vector<std::pair<ResourceId, float>>();
}

void endDay()
{
	day++;

	for (auto& resource : resources)
	{
		resource.second->onDayEnd();
	}

	for (auto& job : population)
	{
		job.second->onDayEnd();
	}

	for (auto& building : buildings)
	{
		building.second->onDayEnd();
	}

	clearScreen();
	mainMenu();
}

void assignJobs(std::string mode)
{
	if (mode._Equal(""))
	{
		listPopulation();

		std::cout << "[a]: Assign\n";
		std::cout << "[u]: Unassign\n";
	}
	else
	{
		listPopulation(true);
	}
	std::cout << "[ ]: Back\n";

	char input = getCharInput();
	if (mode._Equal(""))
	{
		switch (input)
		{
		case ' ':
		{
			clearScreen();
			mainMenu();
			break;
		}
		case 'a':
		{
			clearScreen();
			assignJobs("assign");
			break;
		}
		case 'u':
		{
			clearScreen();
			assignJobs("unassign");
			break;
		}
		default:
		{
			clearScreen();
			std::cout << "Invalid input\n\n";
			assignJobs();
			break;
		}
		}
	}
	else
	{
		if (input == ' ')
		{
			clearScreen();
			assignJobs();
		}
		else
		{
			int index = keybindToIndex(input);
			if (static_cast<JobId>(index) == Unassigned)
			{
				clearScreen();
				std::cout << "Cannot assign/unassign Unassigned\n\n";
				assignJobs(mode);
			}
			if (index < 0 || index >= population.size())
			{
				clearScreen();
				std::cout << "Invalid input\n\n";
				assignJobs(mode);
			}

			JobId jobId = static_cast<JobId>(index);
			std::unique_ptr<Job> job = std::move(population[jobId]); //Move job out of population. NOTE: Make sure to move it back in when we're done!

			if (!job->unlocked)
			{
				clearScreen();
				population[jobId] = std::move(job); //Move job back into population
				std::cout << "Invalid input\n\n";
				assignJobs(mode);
			}

			std::cout << "\n";
			std::cout << (mode._Equal("assign") ? "Assign" : "Unassign"); //Causes issues if not wrapped in parentheses
			std::cout << " how many " << job->name << "? (0 to go back)\n";

			std::string input = getStringInput();
			try
			{
				int amt = std::stoi(input);
				if (amt < 0 || (mode._Equal("assign") && amt > population[Unassigned]->amount) || (mode._Equal("unassign") && amt > job->amount))
				{
					clearScreen();
					population[jobId] = std::move(job); //Move job back into population
					std::cout << "Invalid input\n\n";
					assignJobs(mode);
				}
				else
				{
					if (mode._Equal("assign"))
					{
						population[Unassigned]->amount -= amt;
						job->amount += amt;
					}
					else
					{
						population[Unassigned]->amount += amt;
						job->amount -= amt;
					}

					clearScreen();
					std::cout << (mode._Equal("assign") ? "Assigned " : "Unassigned ");
					std::cout << amt << " " << job->name << "\n\n";
					population[jobId] = std::move(job); //Move job back into population
					assignJobs(mode);
				}
			}
			catch (std::exception ex)
			{
				clearScreen();
				population[jobId] = std::move(job); //Move job back into population
				std::cout << "Invalid input\n\n";
				assignJobs(mode);
			}

		}
	}
}

void build(std::string mode)
{
	listBuildings(true);
	listResources();

	std::cout << "[ ]: Back\n";

	char input = getCharInput();

	if (mode._Equal(""))
	{
		if (input == ' ')
		{
			clearScreen();
			mainMenu();
		}
		else
		{
			int index = keybindToIndex(input);

			if (index < 0 || index >= buildings.size())
			{
				clearScreen();
				std::cout << "Invalid input\n\n";
				build(mode);
			}

			BuildingId buildingId = static_cast<BuildingId>(index);
			std::unique_ptr<Building> building = std::move(buildings[buildingId]);

			if (!building->unlocked)
			{
				clearScreen();
				std::cout << "Invalid input\n\n";
				build(mode);
			}

			std::cout << "\nBuild how many " << building->name << "? (0 to go back)\n";

			std::string input = getStringInput();
			try
			{
				int amt = std::stoi(input);

				std::vector<std::pair<ResourceId, float>> cost = getTotalCost(building->costs, amt);

				if (amt < 0)
				{
					buildings[buildingId] = std::move(building);

					clearScreen();
					std::cout << "Invalid input\n\n";
					build(mode);
				}

				if (building->cap > 0 && building->amount + amt > building->cap)
				{
					buildings[buildingId] = std::move(building);

					clearScreen();
					std::cout << "Cannot build that many\n\n";
					build(mode);
				}

				if (!hasResources(cost))
				{
					buildings[buildingId] = std::move(building);

					clearScreen();
					std::cout << "Cannot afford\n\n";
					build(mode);
				}

				spendResources(cost);
				building->amount += amt;
				building->onBuild(amt);

				clearScreen();
				std::cout << "Built " << amt << " " << building->name << "\n\n";
				buildings[buildingId] = std::move(building);
				build(mode);
			}
			catch (std::exception ex)
			{
				clearScreen();
				buildings[buildingId] = std::move(building);
				std::cout << "Invalid input\n\n";
				build(mode);
			}
		}
	}
}

void purchase(std::string mode)
{
	listPurchases(true);
	listResources();

	std::cout << "[ ]: Back\n";

	char input = getCharInput();

	if (mode._Equal(""))
	{
		if (input == ' ')
		{
			clearScreen();
			mainMenu();
		}
		else
		{
			int index = keybindToIndex(input);

			if (index < 0 || index >= purchases.size())
			{
				clearScreen();
				std::cout << "Invalid input\n\n";
				purchase(mode);
			}

			PurchaseId purchaseId = static_cast<PurchaseId>(index);
			std::unique_ptr<Purchase> selectedPurchase = std::move(purchases[purchaseId]);

			if (!selectedPurchase->unlocked)
			{
				clearScreen();
				std::cout << "Invalid input\n\n";
				build(mode);
			}

			std::cout << "Purchase how many " << selectedPurchase->name << "? (0 to go back)\n";

			std::string input = getStringInput();
			try
			{
				int amt = std::stoi(input);

				std::vector<std::pair<ResourceId, float>> cost = getTotalCost(selectedPurchase->costs, amt);

				if (amt < 0)
				{
					purchases[purchaseId] = std::move(selectedPurchase);

					clearScreen();
					std::cout << "Invalid input\n\n";
					purchase(mode);
				}

				if (selectedPurchase->cap > 0 && selectedPurchase->amount + amt > selectedPurchase->cap)
				{
					purchases[purchaseId] = std::move(selectedPurchase);

					clearScreen();
					std::cout << "Cannot purchase that many\n\n";
					purchase(mode);
				}

				if (!hasResources(cost))
				{
					purchases[purchaseId] = std::move(selectedPurchase);

					clearScreen();
					std::cout << "Cannot afford\n\n";
					purchase(mode);
				}

				spendResources(cost);
				selectedPurchase->amount += amt;
				selectedPurchase->onPurchase(amt);

				clearScreen();
				std::cout << "Purchased " << amt << " " << selectedPurchase->name << "\n\n";
				purchases[purchaseId] = std::move(selectedPurchase);
				purchase(mode);
			}
			catch (std::exception ex)
			{
				clearScreen();
				purchases[purchaseId] = std::move(selectedPurchase);
				std::cout << "Invalid input\n\n";
				purchase(mode);
			}
		}
	}
}

bool hasResources(std::vector<std::pair<ResourceId, float>> costs)
{
	for (std::pair<ResourceId, float> cost : costs)
	{
		if (resources[cost.first]->amount < cost.second)
		{
			return false;
		}
	}

	return true;
}

std::vector<std::pair<ResourceId, float>> getTotalCost(std::vector<std::pair<ResourceId, float>> baseCost, int times)
{
	std::vector<std::pair<ResourceId, float>> costs;

	for (std::pair<ResourceId, float> cost : baseCost)
	{
		cost.second *= times;
		costs.push_back(cost);
	}

	return costs;
}

void spendResources(std::vector<std::pair<ResourceId, float>> cost)
{
	for (std::pair<ResourceId, float> c : cost)
	{
		resources[c.first]->amount -= c.second;
	}
}

std::string listCost(std::vector<std::pair<ResourceId, float>> cost)
{
	std::stringstream ss;

	for (std::pair<ResourceId, float> c : cost)
	{
		ss << c.second << " " << resources[c.first]->name << ", ";
	}

	std::string str = ss.str();
	return str.erase(str.length() - 2);
}