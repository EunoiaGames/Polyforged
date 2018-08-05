#include "RenderContextGL.h"

namespace Eunoia { namespace Rendering {

	RenderContextGL::RenderContextGL()
	{
		m_hdc = GetDC(((Win32Display*)Display::GetDisplay())->GetWindowHandle());
		HGLRC glrc = wglCreateContext(m_hdc);

		if (glrc)
		{
			if (!wglMakeCurrent(m_hdc, glrc))
			{
				std::cerr << "Could not create opengl context" << std::endl;
			}

			std::cout << "Successfully created opengl context" << std::endl;
		}
		else
		{
			std::cerr << "Could not create opengl context" << std::endl;
		}

		if (glewInit() != GLEW_OK)
		{
			std::cerr << "Could not initialize GLEW" << std::endl;
			return;
		}

		std::cout << "Initialized GLEW" << std::endl;

		SetVsync(true);
		glEnable(GL_DEPTH_TEST);
	}

	RenderContextGL::~RenderContextGL()
	{
		
	}

	void RenderContextGL::SetVsync(bool vsync)
	{
		wglSwapIntervalEXT(vsync ? 1 : 0);
	}

	void RenderContextGL::Clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void RenderContextGL::Swap() const
	{
		SwapBuffers(m_hdc);
	}

	void RenderContextGL::SetViewport(float x, float y, float w, float h) const
	{
		glViewport(x, y, w, h);
	}

	void RenderContextGL::SetDisplayAsRenderTarget() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, Display::GetDisplay()->GetWidth(), Display::GetDisplay()->GetHeight());
	}

	void RenderContextGL::SetDepthStencilState(const DepthStencilState & depthStencilState)
	{
		if (depthStencilState.depthEnabled)
			glEnable(GL_DEPTH_TEST);
		else
			glDisable(GL_DEPTH_TEST);

		glDepthMask(depthStencilState.depthWrite);

		switch (depthStencilState.depthComparison)
		{
		case DEPTH_COMPARISON_ALWAYS: glDepthFunc(GL_ALWAYS); break;
		case DEPTH_COMPARISON_NEVER:glDepthFunc(GL_NEVER); break;
		case DEPTH_COMPARISON_LESS: glDepthFunc(GL_LESS); break;
		case DEPTH_COMPARISON_GREATER: glDepthFunc(GL_GREATER); break;
		case DEPTH_COMPARISON_LESS_EQUAL: glDepthFunc(GL_LEQUAL); break;
		case DEPTH_COMPARISON_GREATER_EQUAL: glDepthFunc(GL_GEQUAL); break;
		case DEPTH_COMPARISON_EQUAL: glDepthFunc(GL_EQUAL); break;
		case DEPTH_COMPARISON_NOT_EQUAL: glDepthFunc(GL_NOTEQUAL); break;
		}

		if (depthStencilState.stencilEnabled)
			glEnable(GL_STENCIL_TEST);
		else
			glDisable(GL_STENCIL_TEST);

		GLenum frontComparison = GetStencilComparison(depthStencilState.frontFace.comparison);
		GLenum backComparison = GetStencilComparison(depthStencilState.backFace.comparison);
		glStencilFuncSeparate(frontComparison, backComparison, depthStencilState.ref, depthStencilState.mask);

		GLenum stencilFail = GetStencilOperation(depthStencilState.frontFace.stencilFail);
		GLenum depthFail = GetStencilOperation(depthStencilState.frontFace.depthFail);
		GLenum stencilPass = GetStencilOperation(depthStencilState.frontFace.stencilPass);
		glStencilOpSeparate(GL_FRONT, stencilFail, depthFail, stencilPass);

		stencilFail = GetStencilOperation(depthStencilState.backFace.stencilFail);
		depthFail = GetStencilOperation(depthStencilState.backFace.depthFail);
		stencilPass = GetStencilOperation(depthStencilState.backFace.stencilPass);
		glStencilOpSeparate(GL_BACK, stencilFail, depthFail, stencilPass);
	}

	void RenderContextGL::SetBlendState(const BlendState & blendState)
	{
		if (blendState.enabled)
			glEnable(GL_BLEND);
		else
			glDisable(GL_BLEND);

		switch (blendState.operation)
		{
		case BLEND_OPERATION_ADD: glBlendEquation(GL_FUNC_ADD); break;
		case BLEND_OPERATION_SUB:  glBlendEquation(GL_FUNC_SUBTRACT); break;
		case BLEND_OPERATION_REV_SUB:  glBlendEquation(GL_FUNC_REVERSE_SUBTRACT); break;
		case BLEND_OPERATION_MIN:  glBlendEquation(GL_MIN); break;
		case BLEND_OPERATION_MAX:  glBlendEquation(GL_MAX); break;
		}

		glBlendFunc(GetBlendFunction(blendState.srcFunction), GetBlendFunction(blendState.destFunction));
	}

	GLenum RenderContextGL::GetStencilComparison(StencilComparison stencilComarison) const
	{
		switch (stencilComarison)
		{
		case STENCIL_COMPARISON_ALWAYS: return GL_ALWAYS;
		case STENCIL_COMPARISON_EQUAL: return GL_EQUAL;
		case STENCIL_COMPARISON_GREATER: return GL_GREATER;
		case STENCIL_COMPARISON_GREATER_EQUAL: return GL_GEQUAL;
		case STENCIL_COMPARISON_LESS: return GL_LESS;
		case STENCIL_COMPARISON_LESS_EQUAL: return GL_LEQUAL;
		case STENCIL_COMPARISON_NEVER: return GL_NEVER;
		case STENCIL_COMPARISON_NOT_EQUAL: return GL_NOTEQUAL;
		}
	}

	GLenum RenderContextGL::GetStencilOperation(StencilOperation stencilOperation) const
	{
		switch (stencilOperation)
		{
		case STENCIL_OPERATION_DECR: return GL_DECR;
		case STENCIL_OPERATION_DECR_CLAMP: return GL_DECR_WRAP;
		case STENCIL_OPERATION_INCR: return GL_INCR;
		case STENCIL_OPERATION_INCR_CLAMP: return GL_INCR_WRAP;
		case STENCIL_OPERATION_INVERT: return GL_INVERT;
		case STENCIL_OPERATION_KEEP: return GL_KEEP;
		case STENCIL_OPERATION_REPLACE: return GL_REPLACE;
		case STENCIL_OPERATION_ZERO: return GL_ZERO;
		}
	}

	GLenum RenderContextGL::GetBlendFunction(BlendFunction blendFunction) const
	{
		switch (blendFunction)
		{
		case BLEND_FUNCTION_ZERO: return GL_ZERO;
		case BLEND_FUNCTION_ONE: return GL_ONE;
		case BLEND_FUNCTION_SRC_COLOR: GL_SRC_COLOR;
		case BLEND_FUNCTION_INV_SOURCE_COLOR: GL_ONE_MINUS_SRC_COLOR;
		case BLEND_FUNCTION_DEST_COLOR: return GL_DST_COLOR;
		case BLEND_FUNCTION_INV_DEST_COLOR: return GL_ONE_MINUS_DST_COLOR;
		case BLEND_FUNCTION_SRC_ALPHA: return GL_SRC_ALPHA;
		case BLEND_FUNCTION_SRC_INV_ALPHA: return GL_ONE_MINUS_SRC_ALPHA;
		case BLEND_FUNCTION_DEST_ALPHA: return GL_DST_ALPHA;
		case BLEND_FUNCTION_DEST_INV_ALPHA: return GL_ONE_MINUS_DST_ALPHA;
		}
	}
} }

