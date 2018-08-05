#pragma once
#include "../Math/Math.h"

namespace Eunoia { namespace Rendering { 

	struct Material
	{
		Material(const Math::Vector3f& specular = Math::Vector3f(0.0f, 0.0f, 0.0f), float shininess = 1.0) :
			specular(specular),
			shininess(shininess)
		{}

		Math::Vector3f specular;
		float shininess;
	};

} }
