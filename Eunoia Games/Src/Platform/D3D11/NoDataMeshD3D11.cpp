#include "NoDataMeshD3D11.h"

namespace Eunoia { namespace Rendering {

	NoDataMeshD3D11::NoDataMeshD3D11(uint32 numVertices) :
		m_numVertices(numVertices)
	{}

	void NoDataMeshD3D11::Render() const
	{
		((RenderContextD3D11*)RenderContext::GetRenderContext())->GetDeviceContext()->Draw(m_numVertices, 0);
	}

} }
