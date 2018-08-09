#include "NoDataMesh.h"
#include "../Platform/Opengl/NoDataMeshGL.h"
#include "../Platform/D3D11/NoDataMeshD3D11.h"

namespace Eunoia { namespace Rendering {

	NoDataMesh * NoDataMesh::CreateNoDataMesh(uint32 numVertices)
	{
		switch (RenderContext::GetGraphicsAPI())
		{
		case GRAPHICS_API_D3D11: return new NoDataMeshD3D11(numVertices);
		case GRAPHICS_API_OPENGL: return new NoDataMeshGL(numVertices);
		}
		
		return NULL;
	}

} }
