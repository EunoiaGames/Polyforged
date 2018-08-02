#include "Component.h"

namespace Eunoia { namespace Core {

	std::vector<StaticComponentData> BaseComponent::s_components;

	componentID BaseComponent::RegisterComponentType(uint32 size)
	{
		componentID id = s_components.size();
		s_components.push_back(StaticComponentData(size));
		return id;
	}

	StaticComponentData & BaseComponent::GetStaticComponentData(componentID id)
	{
		return s_components[id];
	}

} }
