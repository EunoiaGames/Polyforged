#include "RenderContext.h"
#include "../Platform/Opengl/RenderContextGL.h"

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
		case GRAPHICS_API_D3D11:
		case GRAPHICS_API_OPENGL: s_pRenderContext = new RenderContextGL();
		}
	}

} }

