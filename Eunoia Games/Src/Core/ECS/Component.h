#pragma once
#include <vector>
#include "ECSTypes.h"

#define DECLARE_COMPONENT(Name) struct Name : public Eunoia::Core::Component<Name>

namespace Eunoia { namespace Core {

	struct BaseComponent
	{
	public:
		static componentID RegisterComponentType(uint32 size);

		EntityHandle entity = NULL_ENTITY_HANDLE;
	private:
		static uint32 s_lastComponentID;

	};

	template<typename T>
	struct Component : public BaseComponent
	{
		static const componentID ID;
	};

	template<typename T>
	const componentID Component<T>::ID(BaseComponent::RegisterComponentType(sizeof(T)));

} }
