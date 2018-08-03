#include "MovementSystem.h"
#include "../Components/MovementComponent.h"
#include "../Components/TransformComponent.h"

namespace Eunoia { namespace Systems {

	MovementSystem::MovementSystem()
	{
		m_requiredComponents.push_back(Components::MovementComponent::ID);
		m_requiredComponents.push_back(Components::TransformComponent::ID);
	}

	void MovementSystem::Update(Core::Entity * pEntity, const Core::DisplayInput * pInput, float dt)
	{
		const Components::MovementComponent* pMovement = pEntity->GetComponent<Components::MovementComponent>();
		Components::TransformComponent* pTransform = pEntity->GetComponent<Components::TransformComponent>();

		if (pInput->IsKeyDown(pMovement->forward))
			pTransform->transform.Translate(pTransform->transform.GetRot().GetForward() * pMovement->speed * dt);
		if (pInput->IsKeyDown(pMovement->back))
			pTransform->transform.Translate(pTransform->transform.GetRot().GetBack() * pMovement->speed * dt);
		if (pInput->IsKeyDown(pMovement->left))
			pTransform->transform.Translate(pTransform->transform.GetRot().GetLeft() * pMovement->speed * dt);
		if (pInput->IsKeyDown(pMovement->right))
			pTransform->transform.Translate(pTransform->transform.GetRot().GetRight() * pMovement->speed * dt);
	}

} }
