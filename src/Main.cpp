// SpaceStationManager.cpp : This file contains the 'main' function. Program
// execution begins and ends there.
//
#pragma once

#include <conio.h>
#include <iostream>
#include <map>
#include "JobList.hpp"
#include "ResourceList.hpp"

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

	std::cout << "Enter a station name: ";
	stationName = getStringInput();

	initStation();

	clearScreen();
	mainMenu();
}

void initStation()
{
	day = 0;

	//Init jobs
	//Make a unique pointer to a new Unassigned job
	population[Unassigned] = std::make_unique<Jobs::Unnassigned>(); // We can also do Job::Unassigned
	population[Farmer] = std::make_unique<Jobs::Farmer>();

	//Set initial values
	population[Unassigned]->unlocked = true;
	population[Unassigned]->amount = 10; // We can also do (*population[Unassigned]).amount = 10;

	population[Farmer]->unlocked = true;
	population[Farmer]->amount = 1;

	//Init resources
	resources[Money] = std::make_unique<Resources::Money>();
	resources[Food] = std::make_unique<Resources::Food>();

	//Set initial values
	resources[Money]->unlocked = true;
	resources[Money]->amount = 1000;

	resources[Food]->unlocked = true;
	resources[Food]->amount = 30;
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
	else if (mode._Equal("assign"))
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
			std::cout << "Assign\n";
			clearScreen();
			assignJobs("assign");
			break;
		}
		case 'u':
		{
			std::cout << "Unassign\n";
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
	else if (mode._Equal("assign"))
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
				std::cout << "Cannot assign to Unassigned\n\n";
				assignJobs("assign");
			}
			if (index != -1)
			{
				JobId jobId = static_cast<JobId>(index);
				std::unique_ptr<Resource> job = std::move(population[jobId]); //Move job out of population. NOTE: Make sure to move it back in when we're done!

				std::cout << "\nAssign how many " << job->getName() << "? (0 to go back)\n";

				std::string input = getStringInput();
				try
				{
					int amt = std::stoi(input);
					if (amt < 0 || amt > population[Unassigned]->amount)
					{
						clearScreen();
						std::cout << "Invalid input\n\n";
						assignJobs("assign");
					}
					else
					{
						population[Unassigned]->amount -= amt;
						job->amount += amt;

						std::cout << job->amount;

						clearScreen();
						std::cout << "Assigned " << amt << " " << job->getName() << "\n\n";
						population[jobId] = std::move(job); //Move job back into population
						assignJobs("assign");
					}
				}
				catch (std::exception ex)
				{
					clearScreen();
					std::cout << "Invalid input\n\n";
					assignJobs("assign");
				}
			}
			else
			{
				clearScreen();
				std::cout << "Invalid input\n\n";
				assignJobs("assign");
			}
		}
	}
}

void build()
{

}