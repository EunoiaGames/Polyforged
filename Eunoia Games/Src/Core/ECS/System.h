#pragma once

#include "Entity.h"
#include "../DisplayInput.h"
#include "../../Rendering/RenderingEngine.h"

namespace Eunoia { namespace Core {

	class System
	{
	public:
		virtual void Update(Entity* pEntity, const DisplayInput* pInput, float dt) {}
		virtual void Render(Entity* pEntity, Rendering::RenderingEngine* pRenderingEngine) {}

		inline const std::vector<componentID>& GetRequiredComponents() const { return m_requiredComponents; }
	protected:
		std::vector<componentID> m_requiredComponents;
	};

} }
