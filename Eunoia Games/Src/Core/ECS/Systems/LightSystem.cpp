#include "LightSystem.h"
#include "../Components/LightComponent.h"
#include "../Components/TransformComponent.h"

namespace Eunoia { namespace Systems {

	LightSystem::LightSystem()
	{
		m_requiredComponents.push_back(Components::LightComponent::ID);
		m_requiredComponents.push_back(Components::TransformComponent::ID);
	}

	void LightSystem::Render(Core::Entity * pEntity, Rendering::RenderingEngine * pRenderingEngine)
	{
		Math::Transform& transform = pEntity->GetComponent<Components::TransformComponent>()->transform;
		Components::LightComponent* pLightComponent = pEntity->GetComponent<Components::LightComponent>();


		if (pLightComponent->lightType == Rendering::LIGHT_TYPE_DIRECTIONAL)
		{
			Rendering::DirectionalLight light;
			light.baseLight = pLightComponent->baseLight;
			light.direction = transform.GetRot().GetForward();
			pRenderingEngine->SubmitDirectionalLight(light);
		}
		else if (pLightComponent->lightType == Rendering::LIGHT_TYPE_POINT)
		{
			Rendering::PointLight light;
			light.baseLight = pLightComponent->baseLight;
			light.pointLight = pLightComponent->pointLight;
			light.pos = transform.GetPos();
		}
		else if (pLightComponent->lightType == Rendering::LIGHT_TYPE_SPOT)
		{
			Rendering::PointLight pointLight;
			pointLight.baseLight = pLightComponent->baseLight;
			pointLight.pointLight = pLightComponent->pointLight;
			pointLight.pos = transform.GetPos();

			Rendering::SpotLight light;
			light.pointLight = pointLight;
			light.spotLight = pLightComponent->spotLight;
		}

	}

} }
