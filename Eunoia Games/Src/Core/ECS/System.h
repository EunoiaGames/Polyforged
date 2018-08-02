#pragma once

#include "Entity.h"
#include "../DisplayInput.h"

namespace Eunoia { namespace Core {

	class System
	{
	public:
		virtual void Update(Entity* pEntity, const DisplayInput* pInput, float dt) {}
		virtual void Render(Entity* pEntity) {}

		inline const std::vector<componentID>& GetRequiredComponents() const { return m_requiredComponents; }
	private:
		std::vector<componentID> m_requiredComponents;
	};

} }
