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

} }

