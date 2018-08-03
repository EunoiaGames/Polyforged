#pragma once

#include "Mesh.h"
#include "Material.h"

namespace Eunoia { namespace Rendering {

	struct MaterialMesh
	{
		MaterialMesh(Mesh* pMesh, const Material& material = Material()) :
			pMesh(pMesh),
			material(material)
		{}

		Mesh* pMesh;
		Material material;
	};

	typedef std::vector<MaterialMesh> LoadedMesh;

} }
