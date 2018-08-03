#include "CoreEngine.h"

namespace Eunoia { namespace Core {

	CoreEngine::CoreEngine(Application * pApplication, float maxFPS)
	{
		m_pApplication = pApplication;
		m_running = false;
		m_frameTime = 1.0f / maxFPS;
	}

	void CoreEngine::Init(const String & title, uint32 width, uint32 height, Rendering::GraphicsAPI api)
	{
		String apiTitle = title + " | Graphics API : ";
		switch (api)
		{
		case Rendering::GRAPHICS_API_D3D11: apiTitle += "D3D11"; break;
		case Rendering::GRAPHICS_API_OPENGL: apiTitle += "Opengl"; break;
		}
		m_pDisplay = Rendering::Display::CreateDisplay(title, width, height, api);
		m_pRenderingEngine = new Rendering::RenderingEngine();
	}

	void CoreEngine::Run()
	{
		if (m_running)
			return;

		m_running = true;

		m_pApplication->Init();

		while (m_running)
		{
			if (m_pDisplay->ShouldClose())
			{
				m_running = false;
			}

			Update(m_frameTime);
			Render();
		}

		m_pApplication->Shutdown();
	}

	void CoreEngine::Update(float dt)
	{
		m_pApplication->Update(m_pDisplay->GetInput(), dt);
		m_pDisplay->Update();
		m_pDisplay->GetInput()->Update();
	}

	void CoreEngine::Render()
	{
		Rendering::RenderContext::GetRenderContext()->SetDisplayAsRenderTarget();
		Rendering::RenderContext::GetRenderContext()->Clear();
		m_pApplication->Render(m_pRenderingEngine);
		Rendering::RenderContext::GetRenderContext()->Swap();
	}

} }
