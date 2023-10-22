#include <string>
#include "ResourceList.hpp"

Resources::Money::Money() :
	Resource("$")
{
	unlocked = true;
	amount = 1000;
}

Resources::Food::Food() :
	Resource("Food")
{
	unlocked = true;
	amount = 30;
}