#pragma once

#include "Resource.hpp"
#include "Main.hpp"

class Job : public Resource
{
public:
	virtual void onDayEnd() override;
};

namespace Jobs
{
	class Unnassigned : public Job
	{
	public:
		std::string getName() override;
	};

	class Farmer : public Job
	{
	public:
		float productivity = 1.2f;
		std::string getName() override;
		void onDayEnd() override;
	};
}