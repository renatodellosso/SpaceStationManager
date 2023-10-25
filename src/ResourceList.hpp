#pragma once

#include "Resource.hpp"

enum ResourceId
{
	Money,
	Food,
	Metal
};

namespace Resources
{
	class Money : public Resource
	{
	public:
		Money() :
			Resource("$", true, 1000)
		{}
	};

	class Food : public Resource
	{
	public:
		Food() :
			Resource("Food", true, 30)
		{}
	};

	class Metal : public Resource
	{
	public:
		Metal() :
			Resource("Metal", true, 10)
		{}
	};
}