#pragma once

#include "../System.h"

namespace Eunoia { namespace Systems {

	class ViewProjectionSystem : public Core::System
	{
	public:
		ViewProjectionSystem();
		void Render(Core::Entity* pEntity, Rendering::RenderingEngine* pRenderingEngine) override;
	};

} }
