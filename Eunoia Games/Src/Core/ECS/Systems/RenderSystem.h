#pragma once

#include "../System.h"

namespace Eunoia { namespace Systems { 

	class RenderSystem : public Core::System
	{
	public:
		RenderSystem();

		void Render(Core::Entity* pEntity, Rendering::RenderingEngine* pRenderingEngine) override;
	private:

	};

} }
