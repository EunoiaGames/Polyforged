#pragma once

#include "../System.h"

namespace Eunoia { namespace Systems {

	class LightSystem : public Core::System
	{
	public:
		LightSystem();

		void Render(Core::Entity* pEntity, Rendering::RenderingEngine* pRenderingEngine) override;
	private:

	};

} }
