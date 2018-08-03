#pragma once

#include "../Component.h"
#include "../../../Math/Transform.h"

namespace Eunoia { namespace Components {

	DECLARE_COMPONENT(TransformComponent)
	{
		Math::Transform transform;
	};

} }
