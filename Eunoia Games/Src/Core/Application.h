#pragma once

#include "ECS\System.h"

namespace Eunoia { namespace Core {

	class Application
	{
	public:
		virtual void Init() {};
		virtual void Shutdown() {};

		void AddEntity(Entity* pEntity);
		void AddSystem(System* pSystem);

		void Update(const DisplayInput* pInput, float dt);
		void Render(Rendering::RenderingEngine* pRenderingEngine);
	private:
		std::vector<Entity*> m_entities;
		std::vector<System*> m_systems;
	};

} }
