#include "RenderSystem.h"
#include "../Components/MeshComponent.h"
#include "../Components/MaterialComponent.h"
#include "../Components/TransformComponent.h"

namespace Eunoia { namespace Systems {

	RenderSystem::RenderSystem()
	{
		m_requiredComponents.push_back(Components::MeshComponent::ID);
		m_requiredComponents.push_back(Components::MaterialComponent::ID);
		m_requiredComponents.push_back(Components::TransformComponent::ID);
	}

	void RenderSystem::Render(Core::Entity * pEntity, Rendering::RenderingEngine * pRenderingEngine)
	{
		Components::MeshComponent* pMeshComponent = pEntity->GetComponent<Components::MeshComponent>();
		Components::TransformComponent* pTransformComonent = pEntity->GetComponent<Components::TransformComponent>();
		Components::MaterialComponent* pMaterialComponent = pEntity->GetComponent<Components::MaterialComponent>();

		Rendering::DrawCommand drawCommand;
		drawCommand.pMesh = pMeshComponent->pMesh;
		drawCommand.material = pMaterialComponent->material;
		drawCommand.worldMatrix = pTransformComonent->transform.CreateWorldMatrix();

		pRenderingEngine->Submit(drawCommand);
	}

} }
