#pragma once

#include "../Component.h"
#include "../../../Rendering/Mesh.h"
#include <vector>

namespace Eunoia { namespace Components {

	DECLARE_COMPONENT(MeshComponent)
	{
		Rendering::Mesh* pMesh;
	};

} }
