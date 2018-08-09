#pragma once

#include "ECSTypes.h"
#include <map>
#include <vector>

namespace Eunoia { namespace Core {

	struct EntityFlags
	{
		EntityFlags():
			updatable(true),
			renderable(true)
		{}

		bool updatable;
		bool renderable;
	};

	class Entity
	{
	public:
		virtual ~Entity()
		{
			for (const auto& it : m_components)
			{
				delete it.second;
			}
		}

		inline bool IsValidForSystem(const std::vector<componentID>& requiredComponents)
		{
			for (uint32 i = 0; i < requiredComponents.size(); i++)
			{
				if (m_components.find(requiredComponents[i]) == m_components.end())
				{
					return false;
				}
			}

			return true;
		}

		template<typename Comp>
		inline void AddComponent(Comp* pComp)
		{
			m_components[Comp::ID] = pComp;
			pComp->entity = this;
		}

		template<class Comp>
		inline bool RemoveComponent()
		{
			if (m_components.find(Comp::ID) == m_components.end())
			{
				return false;
			}

			delete m_components[Comp::ID];
			m_components.erase(Comp::ID);
			return true;
		}

		template<class Comp>
		inline Comp* GetComponent() 
		{ 
			return (Comp*)m_components[Comp::ID];
		}

		EntityFlags flags;

	private:
		std::map<componentID, void*> m_components;
	};

} }
