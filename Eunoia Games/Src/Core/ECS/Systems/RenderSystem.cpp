#include "RenderSystem.h"
#include "../Components/MeshComponent.h"
#include "../Components/TransformComponent.h"

namespace Eunoia { namespace Systems {

	RenderSystem::RenderSystem()
	{
		m_requiredComponents.push_back(Components::MeshComponent::ID);
		m_requiredComponents.push_back(Components::TransformComponent::ID);
	}

	void RenderSystem::Render(Core::Entity * pEntity, Rendering::RenderingEngine * pRenderingEngine)
	{
		Components::MeshComponent* pMeshComponent = pEntity->GetComponent<Components::MeshComponent>();
		Components::TransformComponent* pTransformComonent = pEntity->GetComponent<Components::TransformComponent>();

		Rendering::DrawCommand drawCommand;
		drawCommand.pModel = &pMeshComponent->meshes;
		drawCommand.worldMatrix = pTransformComonent->transform.CreateWorldMatrix();

		pRenderingEngine->Submit(drawCommand);
	}

} }
