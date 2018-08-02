#include "RenderContext.h"
#include "../Platform/Opengl/RenderContextGL.h"
#include "../Platform/D3D11/RenderContextD3D11.h"

namespace Eunoia { namespace Rendering {
	
	RenderContext* RenderContext::s_pRenderContext;
	GraphicsAPI RenderContext::s_graphicsApi;

	RenderContext * RenderContext::GetRenderContext()
	{
		return s_pRenderContext;
	}

	GraphicsAPI RenderContext::GetGraphicsAPI()
	{
		return s_graphicsApi;
	}

	void RenderContext::InitGraphicsAPI(GraphicsAPI api)
	{
		s_graphicsApi = api;

		if (s_pRenderContext)
			delete s_pRenderContext;

		switch (s_graphicsApi)
		{
		case GRAPHICS_API_D3D11: s_pRenderContext = new RenderContextD3D11(); break;
		case GRAPHICS_API_OPENGL: s_pRenderContext = new RenderContextGL(); break;
		}
	}

} }

