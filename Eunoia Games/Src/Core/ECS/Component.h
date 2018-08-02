#pragma once
#include <vector>
#include "ECSTypes.h"

namespace Eunoia { namespace Core {

	struct StaticComponentData
	{
		StaticComponentData(uint32 size) :
			size(size)
		{}

		uint32 size;
	};

	struct BaseComponent
	{
	public:
		static componentID RegisterComponentType(uint32 size);
		static StaticComponentData& GetStaticComponentData(componentID id);

		EntityHandle entity = NULL_ENTITY_HANDLE;
	private:
		static std::vector<StaticComponentData> s_components;
	};

	template<typename T>
	struct Component : public BaseComponent
	{
		static const componentID ID;
		static const uint32 SIZE;
	};

	template<typename T>
	const componentID Component<T>::ID(BaseComponent::RegisterComponentType(sizeof(T)));

	template<typename T>
	const uint32 Component<T>::SIZE(sizeof(T));

} }
