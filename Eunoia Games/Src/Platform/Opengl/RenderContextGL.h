#pragma once

#include <GL\glew.h>
#include <GL\wglew.h>
#include "../../Rendering/RenderContext.h"
#include "../Windows/Win32Display.h"

namespace Eunoia { namespace Rendering {

	class RenderContextGL : public RenderContext
	{
	public:
		RenderContextGL();
		~RenderContextGL();

		void SetVsync(bool vsync) override;
		void Clear() const override;
		void Swap() const override;
		void SetViewport(float x, float y, float w, float h) const override;
		void SetDisplayAsRenderTarget() const override;
	private:
		HDC m_hdc;
	};

} }
