#include "Component.h"

namespace Eunoia { namespace Core {

	uint32 BaseComponent::s_lastComponentID = 0;

	componentID BaseComponent::RegisterComponentType(uint32 size)
	{
		return s_lastComponentID++;
	}

} }
