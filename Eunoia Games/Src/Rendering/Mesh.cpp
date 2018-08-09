#include "Mesh.h"
#include "../Platform/Opengl/MeshGL.h"
#include "../Platform/D3D11/MeshD3D11.h"
#include "../Rendering/RenderContext.h"

namespace Eunoia { namespace Rendering {

	Mesh * Mesh::CreateMesh(const Vertex* pVertices, uint32 numVertices, const uint32* pIndices, uint32 numIndices, MeshUsage usage)
	{
		switch (RenderContext::GetGraphicsAPI())
		{
		case GRAPHICS_API_D3D11: return new MeshD3D11(pVertices, numVertices, pIndices, numIndices, usage);
		case GRAPHICS_API_OPENGL: return new MeshGL(pVertices, numVertices, pIndices, numIndices, usage);
		}
	}

	Mesh * Mesh::CreateMesh(const std::vector<Vertex>& vertices, const std::vector<uint32>& indices, MeshUsage usage)
	{
		return CreateMesh(&vertices[0], vertices.size(), &indices[0], indices.size(), usage);
	}

	Mesh * Mesh::CreateMesh(const Vertex * pVertices, uint32 numVertices, MeshUsage usage)
	{
		switch (RenderContext::GetGraphicsAPI())
		{
		case GRAPHICS_API_D3D11: return NULL;
		case GRAPHICS_API_OPENGL: return new MeshGL(pVertices, numVertices, usage);
		}
	}

	Mesh * Mesh::CreateMesh(const std::vector<Vertex>& vertices, MeshUsage usage)
	{
		return CreateMesh(&vertices[0], vertices.size(),  usage);
	}

} }
