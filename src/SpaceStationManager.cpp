// SpaceStationManager.cpp : This file contains the 'main' function. Program
// execution begins and ends there.
//

#include <conio.h>
#include <iostream>
#include <map>
#include "Resource.h"
#include "JobList.h"
#include "ResourceList.h"

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

void pause()
{
	std::cout << "Press any key to continue...";
	(void)_getch();  // Cast to void to show we're ignoring the return value
}

void clearScreen()
{
	system("cls");  // Different for non-Windows OS's
}

void initStation();
void mainMenu();
void listPopulation();
void listResources();
void endDay();
void assignJobs();
void build();

enum JobId
{
	Unassigned,
};

enum ResourceId
{
	Money,
	Food,
};

std::map<JobId, std::unique_ptr<Resource>> population;
std::map<ResourceId, std::unique_ptr<Resource>> resources;

std::string stationName;
int day;

int main()
{
	std::cout << "Welcome to Space Station Manager!\n\n";
	pause();
	clearScreen();

	std::cout << "Enter a station name: ";
	stationName = getStringInput();

	initStation();

	mainMenu();
}

void initStation()
{
	day = 0;

	//Make a unique pointer to a new Unassigned job
	population[Unassigned] = std::make_unique<Jobs::Unnassigned>(); // We can also do Job::Unassigned
	population[Unassigned]->amount = 10; // We can also do (*population[Unassigned]).amount = 10;

	resources[Money] = std::make_unique<Resources::Money>();
	resources[Money]->amount = 1000;

	resources[Food] = std::make_unique<Resources::Food>();
	resources[Food]->amount = 30;
}

void mainMenu()
{
	std::cout << stationName << " - Day " << day << "\n\n";

	listPopulation();
	listResources();

	std::cout << "[1] Assign jobs\n";
	std::cout << "[2] Build\n";
	std::cout << "[ ] End day\n";

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
		std::cout << "Assign jobs\n";
		clearScreen();
		assignJobs();
		break;
	}
	case '2':
	{
		std::cout << "Build\n";
		clearScreen();
		build();
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

void listResources()
{
	std::cout << "Resources:\n";

	for (auto& resource : resources)
	{
		std::cout << resource.second->GetName() << ": " << resource.second->amount << "\n";
	}

	std::cout << "\n";
}

void listPopulation()
{
	std::cout << "Population:\n";

	for (auto& job : population)
	{
		std::cout << job.second->GetName() << ": " << job.second->amount << "\n";
	}

	std::cout << "\n";
}

void endDay()
{
	day++;

	for (auto& resource : resources)
	{
		resource.second->OnDayEnd();
	}

	for (auto& job : population)
	{
		job.second->OnDayEnd();
	}

	clearScreen();
	mainMenu();
}

void assignJobs()
{

}

void build()
{

}