#pragma once

#include "Vertex.h"
#include <vector>

namespace Eunoia { namespace Rendering {

	enum MeshUsage
	{
		MESH_USAGE_STATIC,
		MESH_USAGE_DYNAMIC,

		NUM_MESH_USAGES
	};

	class Mesh
	{
	public:
		virtual void Render() const = 0;
		virtual void Map(Vertex* pVertices) const = 0;
		virtual void Unmap() const = 0;

		static Mesh* CreateMesh(const Vertex* pVertices, uint32 numVertices, const uint32* pIndices, uint32 numIndices, MeshUsage usage);
		static Mesh* CreateMesh(const std::vector<Vertex>& vertices, const std::vector<uint32>& indices, MeshUsage usage);
	};
} }
