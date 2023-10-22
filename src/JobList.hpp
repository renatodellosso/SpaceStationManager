#pragma once

#include "Resource.hpp"

class Job : public Resource
{
public:
	Job(std::string name) :
		Resource(name)
	{}

	Job(std::string name, float amount) :
		Resource(name, true, amount)
	{}

	Job(std::string name, bool unlocked, float amount) :
		Resource(name, unlocked, amount)
	{}

	virtual void onDayEnd() override;
};

namespace Jobs
{
	class Unnassigned : public Job
	{
	public:
		Unnassigned() :
			Job("Unnassigned", true, 10)
		{}
	};

	class Farmer : public Job
	{
	public:
		float productivity = 1.2f;
		Farmer() :
			Job("Farmer", true, 0)
		{}
		void onDayEnd() override;
	};
}