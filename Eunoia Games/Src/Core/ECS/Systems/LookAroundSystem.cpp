#include "LookAroundSystem.h"
#include "../Components/TransformComponent.h"
#include "../Components/LookAroundComponent.h"
#include "../../../Rendering/Display.h"

namespace Eunoia { namespace Systems {

	LookAroundSystem::LookAroundSystem()
	{
		m_requiredComponents.push_back(Components::TransformComponent::ID);
		m_requiredComponents.push_back(Components::LookAroundComponent::ID);
	}

	void LookAroundSystem::Update(Core::Entity * pEntity, const Core::DisplayInput * pInput, float dt)
	{
		Math::Transform& transform = pEntity->GetComponent<Components::TransformComponent>()->transform;
		const Components::LookAroundComponent* pLookAround = pEntity->GetComponent<Components::LookAroundComponent>();

		const Math::Vector2f CENTER_POS = Rendering::Display::GetDisplay()->GetSize() / 2.0f;

		if (pInput->IsKeyPressed(pLookAround->toggleKey))
		{
			pInput->SetCursorVisible(!pInput->IsCursorVisible());
			pInput->SetCursorPosition(CENTER_POS);
		}

		if (pInput->IsCursorVisible())
			return;

		Math::Vector2f deltaPos = pInput->GetCursorPosition() - CENTER_POS;

		bool rotX = deltaPos.GetY() != 0;
		bool rotY = deltaPos.GetX() != 0;

		if (rotX)
		{
			transform.Rotate(transform.GetRot().GetRight(), deltaPos.GetY() * pLookAround->sensitivity * dt);
		}
		if (rotY)
		{
			transform.Rotate(Math::Vector3f(0.0f, 1.0f, 0.0f), deltaPos.GetX() * pLookAround->sensitivity * dt);
		}
		if (rotX || rotY)
		{
			pInput->SetCursorPosition(CENTER_POS);
		}
	}

} }
