#pragma once
#include "../Math/Math.h"

namespace Eunoia { namespace Rendering { 

	struct Material
	{
		Material(const Math::Vector3f& albedoColor = Math::Vector3f(1.0f, 1.0f, 1.0f)) :
			albedoColor(albedoColor)
		{}

		Math::Vector3f albedoColor;
	};

} }
