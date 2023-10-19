#pragma once

#include "Resource.hpp"

namespace Resources
{
	class Money : public Resource
	{
	public:
		std::string getName() override;
	};

	class Food : public Resource
	{
	public:
		std::string getName() override;
	};
}