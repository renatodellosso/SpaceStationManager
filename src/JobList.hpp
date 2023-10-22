#pragma once

#include "Resource.hpp"

class Job : public Resource
{
public:
	Job(std::string name) :
		Resource(name)
	{}
	virtual void onDayEnd() override;
};

namespace Jobs
{
	class Unnassigned : public Job
	{
	public:
		Unnassigned();
	};

	class Farmer : public Job
	{
	public:
		float productivity = 1.2f;
		Farmer();
		void onDayEnd() override;
	};
}