#pragma once

#include "ECSTypes.h"
#include <map>
#include <vector>

namespace Eunoia { namespace Core {

	class Entity
	{
	public:
		virtual ~Entity()
		{
			for (const auto& it : m_components)
			{
				free(it.second);
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
		inline void AddComponent(const Comp& comp)
		{
			m_components[Comp::ID] = (uint8)malloc(Comp::SIZE);
			((Comp*)memcpy(m_components[Comp::ID], &comp, Comp::SIZE))->entity = this;
		}

		template<class Comp>
		inline bool RemoveComponent()
		{
			if (m_components.find(Comp::ID) == m_components.end())
			{
				return false;
			}

			free(m_components[Comp::ID]);
			m_components.erase(Comp::ID);
			return true;
		}

		template<class Comp>
		inline Comp* GetComponent() 
		{ 
			return (Comp*)m_components[Comp::ID];
		}

	private:
		std::map<componentID, uint8*> m_components;
	};

} }
