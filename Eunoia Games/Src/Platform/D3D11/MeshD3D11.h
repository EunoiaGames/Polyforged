#pragma once

#include "../../Rendering/Mesh.h"
#include "RenderContextD3D11.h"

namespace Eunoia { namespace Rendering { 
	
	class MeshD3D11 : public Mesh
	{
	public:
		MeshD3D11(const Vertex* pVertices, uint32 numVertices, const uint32* pIndices, uint32 numIndices, MeshUsage usage);
		~MeshD3D11();

		void Render() const override;
		void Map(Vertex* pVertices) const override;
		void Unmap() const override;
	private:
		RenderContextD3D11* m_pRenderContext;

		ID3D11Buffer* m_pVertexBuffer;
		ID3D11Buffer* m_pIndexBuffer;

		uint32 m_numIndices;
	};

} }
