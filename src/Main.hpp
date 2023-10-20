#pragma once

#include <conio.h>
#include <memory>
#include <map>
#include <string>

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