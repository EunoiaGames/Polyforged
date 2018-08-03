#pragma once

#include "../Component.h"
#include "../../../Math/Transform.h"

namespace Eunoia { namespace Components {

	DECLARE_COMPONENT(TransformComponent)
	{
		TransformComponent(const Math::Transform& transform = Math::Transform()) :
			transform(transform)
		{}

		Math::Transform transform;
	};

} }
