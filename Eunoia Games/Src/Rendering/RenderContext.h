#pragma once

#include "RenderStates\RenderStates.h"

namespace Eunoia { namespace Rendering {

	enum GraphicsAPI
	{
		GRAPHICS_API_NONE,
		GRAPHICS_API_OPENGL,
		GRAPHICS_API_D3D11,

		NUM_GRAPHICS_API_TYPES
	};

	class RenderContext
	{
	public:
		virtual void SetVsync(bool vsync) = 0;
		virtual void Clear() const = 0;
		virtual void Swap() const = 0;
		virtual void SetViewport(float x, float y, float w, float h) const = 0;
		virtual void SetDisplayAsRenderTarget() const = 0;

		virtual void SetDepthStencilState(const DepthStencilState& depthStencilState) = 0;
		virtual void SetBlendState(const BlendState& blendState) = 0;

		static RenderContext* GetRenderContext();
		static GraphicsAPI GetGraphicsAPI();

		static void InitGraphicsAPI(GraphicsAPI api);
	private:
		static RenderContext* s_pRenderContext;
		static GraphicsAPI s_graphicsApi;
	};

} }