#pragma once

#include "../Component.h"
#include "../../../Rendering/Mesh.h"
#include <vector>

namespace Eunoia { namespace Components {

	DECLARE_COMPONENT(MaterialComponent)
	{
		MaterialComponent(const Rendering::Material& material) :
			material(material)
		{}

		Rendering::Material material;
	};

} }
