#pragma once

#include "LoadedMesh.h"
#include "../DataStructures/String.h"
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

namespace Eunoia { namespace Rendering {

	class ModelLoader
	{
	public:
		static LoadedMesh LoadFromFile(const String& file);
	private:
		inline static Math::Vector3f ToEunoiaVec(const aiVector3D& vec) { return Math::Vector3f(vec.x, vec.y, vec.z); }
		inline static Math::Vector3f ToEunoiaVec(const aiColor4D& color) { return Math::Vector3f(color.r, color.g, color.b); }
	};

} }
