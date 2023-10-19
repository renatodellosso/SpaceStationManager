#pragma once

#include <conio.h>
#include <memory>
#include <map>
#include <string>
#include "Resource.hpp"

enum JobId
{
	Unassigned,
	Farmer
};

enum ResourceId
{
	Money,
	Food,
};

std::string stationName;
int day;
std::map<JobId, std::unique_ptr<Resource>> population;
std::map<ResourceId, std::unique_ptr<Resource>> resources;

char getCharInput();
std::string getStringInput();
void clearScreen();
void pause();
void initStation();
void mainMenu();
void listPopulation(bool withKeybinds = false);
void listResources(bool withKeybinds = false);
void endDay();
void assignJobs(std::string mode = "");
void build();