#include "Resource.h"

namespace Jobs
{
	class Unnassigned : public Resource
	{
	public:
		std::string GetName() override
		{
			return "Unassigned";
		}
	};
}