#pragma once

#include "../System.h"

namespace Eunoia { namespace Systems {

	class MovementSystem : public Core::System
	{
	public:
		MovementSystem();

		void Update(Core::Entity* pEntity, const Core::DisplayInput* pInput, float dt) override;
	};

} }
