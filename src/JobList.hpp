#pragma once

#include "Resource.hpp"

enum JobId
{
	Unassigned,
	Farmer,
	Miner,
	Scientist
};

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
	virtual std::string getDescription() override;
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
		std::string getDescription() override;
	};

	class Miner : public Job
	{
	public:
		float productivity = 0.3f;
		Miner() :
			Job("Miner", true, 0)
		{}
		void onDayEnd() override;
		std::string getDescription() override;
	};

	class Scientist : public Job
	{
	public:
		float productivity = 0.5f;
		Scientist() :
			Job("Scientist", false, 0)
		{}
		void onDayEnd() override;
		std::string getDescription() override;
	};
}