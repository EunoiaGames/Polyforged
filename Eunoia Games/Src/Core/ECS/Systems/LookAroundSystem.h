#pragma once

#include "../System.h"

namespace Eunoia { namespace Systems {

	class LookAroundSystem : public Core::System
	{
	public:
		LookAroundSystem();
		void Update(Core::Entity* pEntity, const Core::DisplayInput* pInput, float dt) override;
	};

} }
