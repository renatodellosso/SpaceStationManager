// SpaceStationManager.cpp : This file contains the 'main' function. Program
// execution begins and ends there.
//
#pragma once

#include <conio.h>
#include <iostream>
#include <map>
#include "JobList.hpp"
#include "ResourceList.hpp"
#include "StationData.hpp"

void initVars();
void listPopulation(bool withKeybinds = false);
void listResources(bool withKeybinds = false);
void mainMenu();
void endDay();
void assignJobs(std::string mode = "");
void build();

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

	resources[Money] = std::make_unique<Resources::Money>();
	resources[Food] = std::make_unique<Resources::Food>();
}

void mainMenu()
{
	std::cout << stationName << " - Day " << day << "\n\n";

	listPopulation();
	listResources();

	std::cout << "[1]: Assign jobs\n";
	std::cout << "[2]: Build\n";
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
			std::cout << resource.second->getName() << ": " << resource.second->amount << "\n";

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
			std::cout << job.second->getName() << ": " << job.second->amount << "\n";

			index++;
		}
	}

	std::cout << "\n";
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
			if (index != -1)
			{
				JobId jobId = static_cast<JobId>(index);
				std::unique_ptr<Resource> job = std::move(population[jobId]); //Move job out of population. NOTE: Make sure to move it back in when we're done!

				std::cout << "\n";
				std::cout << (mode._Equal("assign") ? "Assign" : "Unassign"); //Causes issues if not wrapped in parentheses
				std::cout << " how many " << job->getName() << "? (0 to go back)\n";

				std::string input = getStringInput();
				try
				{
					int amt = std::stoi(input);
					if (amt < 0 || (mode._Equal("assign") && amt > population[Unassigned]->amount) || (mode._Equal("unassign") && amt > job->amount))
					{
						clearScreen();
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
						std::cout << amt << " " << job->getName() << "\n\n";
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
			else
			{
				clearScreen();
				std::cout << "Invalid input\n\n";
				assignJobs(mode);
			}
		}
	}
}

void build()
{

}