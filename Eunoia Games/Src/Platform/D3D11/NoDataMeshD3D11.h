#pragma once

#include "../../Rendering/NoDataMesh.h"
#include "../../Core/Common.h"
#include "RenderContextD3D11.h"

namespace Eunoia { namespace Rendering {

	class NoDataMeshD3D11 : public NoDataMesh
	{
	public:
		NoDataMeshD3D11(uint32 numVertices);
		void Render() const override;
	private:
		uint32 m_numVertices;
	};

} }
