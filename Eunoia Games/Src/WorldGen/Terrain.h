#pragma once

#include "HeightsGenerator.h"
#include "../Rendering/Vertex.h"
#include <vector>

namespace Eunoia { namespace Rendering { 

	class Terrain
	{
	public:
		Terrain(uint32 x, uint32 z, float gap);
	private:
		void GenerateMeshInfo(uint32 x, uint32 z, float gap, std::vector<Vertex>& vertices, std::vector<uint32>& indices);
	private:
		HeightsGenerator m_heightsGenerator;
	};

} }
