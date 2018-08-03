#include "Application.h"

namespace Eunoia { namespace Core {

	void Application::AddEntity(Entity * pEntity)
	{
		m_entities.push_back(pEntity);
	}

	void Application::AddSystem(System * pSystem)
	{
		m_systems.push_back(pSystem);
	}

	void Application::Update(const DisplayInput * pInput, float dt)
	{
		for (uint32 i = 0; i < m_systems.size(); i++)
		{
			const std::vector<componentID>& requiredComponents = m_systems[i]->GetRequiredComponents();
			for (uint32 j = 0; j < m_entities.size(); j++)
			{
				if (m_entities[j]->IsValidForSystem(requiredComponents))
					m_systems[i]->Update(m_entities[j], pInput, dt);
			}
		}
	}

	void Application::Render(Rendering::RenderingEngine* pRenderingEngine)
	{
		pRenderingEngine->Begin();
		for (uint32 i = 0; i < m_systems.size(); i++)
		{
			const std::vector<componentID>& requiredComponents = m_systems[i]->GetRequiredComponents();
			for (uint32 j = 0; j < m_entities.size(); j++)
			{
				if (m_entities[j]->IsValidForSystem(requiredComponents))
					m_systems[i]->Render(m_entities[j], pRenderingEngine);
			}
		}
		pRenderingEngine->End();
		pRenderingEngine->Draw();
	}

} }
