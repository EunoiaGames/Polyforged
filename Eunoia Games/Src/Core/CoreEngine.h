#pragma once

#include "Application.h"
#include "../Rendering/Display.h"

namespace Eunoia { namespace Core { 

	class CoreEngine
	{
	public:
		CoreEngine(Application* pApplication, float maxFPS = 60.0f);
		void Init(const String& title, uint32 width, uint32 height, Rendering::GraphicsAPI api);

		void Run();
	private:
		void Update(float dt);
		void Render();
	private:
		bool m_running;

		float m_frameTime;

		Application* m_pApplication;
		Rendering::RenderingEngine* m_pRenderingEngine;
		Rendering::Display* m_pDisplay;
	};

} }
