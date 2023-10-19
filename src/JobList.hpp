#pragma once

#include "Resource.hpp"
#include "Main.hpp"

class Job : public Resource
{
public:
	void onDayEnd() override;
};

namespace Jobs
{
	class Unnassigned : public Resource
	{
	public:
		std::string getName() override;
	};

	class Farmer : public Resource
	{
	public:
		std::string getName() override;
	};
}