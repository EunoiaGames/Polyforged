#include "Mesh.h"
#include "../Platform/Opengl/MeshGL.h"
#include "../Rendering/RenderContext.h"

namespace Eunoia { namespace Rendering {

	Mesh * Mesh::CreateMesh(const Vertex* pVertices, uint32 numVertices, const uint32* pIndices, uint32 numIndices, MeshUsage usage)
	{
		switch (RenderContext::GetGraphicsAPI())
		{
		case GRAPHICS_API_D3D11: break;
		case GRAPHICS_API_OPENGL: return new MeshGL(pVertices, numVertices, pIndices, numIndices, usage);
		}
	}

	Mesh * Mesh::CreateMesh(const std::vector<Vertex>& vertices, const std::vector<uint32>& indices, MeshUsage usage)
	{
		return CreateMesh(&vertices[0], vertices.size(), &indices[0], indices.size(), usage);
	}

} }
