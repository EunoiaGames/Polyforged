#pragma once

#include "../Component.h"
#include "../../../Math/Math.h"

namespace Eunoia { namespace Rendering {

	enum LightType
	{
		LIGHT_TYPE_DIRECTIONAL,
		LIGHT_TYPE_POINT,
		LIGHT_TYPE_SPOT,

		NUM_LIGHT_TYPES
	};

	struct BaseLightInfo
	{
		Math::Vector3f color;
		float intensity;
	};

	struct PointLightInfo
	{
		Math::Attenuation attenuation;
		float range;
	};
	
	struct SpotLightInfo
	{
		float cutoff;
	};

	struct DirectionalLight
	{
		BaseLightInfo baseLight;
		Math::Vector3f direction;
	};

	struct PointLight
	{
		BaseLightInfo baseLight;
		PointLightInfo pointLight;
		Math::Vector3f pos;
	};

	struct SpotLight
	{
		PointLight pointLight;
		SpotLightInfo spotLight;
	};

} }

namespace Eunoia { namespace Components {

	DECLARE_COMPONENT(LightComponent)
	{
		Rendering::LightType lightType;
		Rendering::BaseLightInfo baseLight;
		Rendering::PointLightInfo pointLight;
		Rendering::SpotLightInfo spotLight;
	};

} }
