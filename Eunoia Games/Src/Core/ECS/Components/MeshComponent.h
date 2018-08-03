#pragma once

#include "../Component.h"
#include "../../../Rendering/Mesh.h"
#include <vector>

namespace Eunoia { namespace Components {

	DECLARE_COMPONENT(MeshComponent)
	{
		MeshComponent(Rendering::Mesh* pMesh) :
			pMesh(pMesh)
		{}

		Rendering::Mesh* pMesh;
	};

} }
