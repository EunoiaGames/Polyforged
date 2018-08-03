#pragma once

#include "../Component.h"
#include "../../../Rendering/LoadedMesh.h"
#include <vector>

namespace Eunoia { namespace Components {

	DECLARE_COMPONENT(MeshComponent)
	{
		MeshComponent(Rendering::Mesh* pMesh)
		{
			mesh.push_back(pMesh);
		}

		MeshComponent(Rendering::LoadedMesh mesh) :
			mesh(mesh)
		{}

		Rendering::LoadedMesh mesh;
	};

} }
