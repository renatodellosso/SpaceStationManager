#include "Resource.h"

namespace Resources
{

	class Money : public Resource
	{
	public:
		std::string GetName() override
		{
			return "$";
		}
	};;

	class Food : public Resource
	{
	public:
		std::string GetName() override
		{
			return "Food";
		}
	};
}