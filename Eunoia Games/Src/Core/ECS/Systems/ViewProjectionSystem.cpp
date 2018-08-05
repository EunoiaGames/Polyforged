#include "ViewProjectionSystem.h"
#include "../Components/CameraComponent.h"
#include "../Components/TransformComponent.h"

namespace Eunoia { namespace Systems {

	ViewProjectionSystem::ViewProjectionSystem()
	{
		m_requiredComponents.push_back(Components::CameraComponent::ID);
		m_requiredComponents.push_back(Components::TransformComponent::ID);
	}

	void ViewProjectionSystem::Render(Core::Entity * pEntity, Rendering::RenderingEngine * pRenderingEngine)
	{
		const Math::Matrix4f& projection = pEntity->GetComponent<Components::CameraComponent>()->projection;
		const Math::Transform& transform = pEntity->GetComponent<Components::TransformComponent>()->transform;

		Math::Matrix4f view = transform.GetRot().GetConjugate().CreateRotationMatrix() * Math::Matrix4f().InitTranslation(transform.GetPos() * -1.0f);
		pRenderingEngine->SetCamera(view, projection, transform.GetPos());
	}

} }
