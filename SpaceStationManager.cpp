// SpaceStationManager.cpp : This file contains the 'main' function. Program
// execution begins and ends there.
//

#include <conio.h>
#include <iostream>
#include <map>

char getCharInput()
{
	char input = _getch();
	return input;
}

std::string getStringInput()
{
	std::string input;
	std::cin >> input;
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

namespace Job
{
	const std::string UNASSIGNED = "Unassigned";
};

namespace Resource
{
	const std::string UNASSIGNED = "Unassigned";
};

std::map<std::string, int> population;
std::map<std::string, int> resources;

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

	while (true)
		mainMenu();
}

void initStation()
{
	day = 0;

	population[Job::UNASSIGNED] = 10; // We can also do Job::Unassigned
	resources[Money] = 100;
	resources[Food] = 100;
}

void mainMenu()
{
	clearScreen();
	std::cout << stationName << " - Day " << day << "\n\n";

	listPopulation();
	listResources();

	pause();
}

void listResources()
{
	std::cout << "Resources:\n";

	// Get an iterator, pointing to the first element
	std::map<Resource, int>::iterator it = resources.begin();
	while (it != resources.end())
	{
		// it->first is the key, it->second is the value
		//std::cout <<  << ": " << it->second << "\n";
		it++;
	}
}

void listPopulation()
{

}