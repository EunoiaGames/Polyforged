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
		BaseLightInfo(const Math::Vector3f& color, float intensity) :
			color(color),
			intensity(intensity)
		{}

		BaseLightInfo() {}

		Math::Vector3f color;
		float intensity;
	};

	struct PointLightInfo
	{
		PointLightInfo(const Math::Attenuation& attenuation, float range) :
			attenuation(attenuation),
			range(range)
		{}

		PointLightInfo() {}

		Math::Attenuation attenuation;
		float range;
	};
	
	struct SpotLightInfo
	{
		SpotLightInfo(float cutoff) :
			cutoff(cutoff)
		{}

		SpotLightInfo() {}

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
		LightComponent(Rendering::LightType lightType, const Rendering::BaseLightInfo& baseLight) :
			lightType(lightType),
			baseLight(baseLight)
		{}

		LightComponent(const Rendering::BaseLightInfo& baseLight) :
			lightType(Rendering::LIGHT_TYPE_DIRECTIONAL),
			baseLight(baseLight)
		{}

		LightComponent(const Rendering::BaseLightInfo& baseLight, const Rendering::PointLightInfo& pointLight) :
			lightType(Rendering::LIGHT_TYPE_POINT),
			baseLight(baseLight),
			pointLight(pointLight)
		{}

		LightComponent(const Rendering::BaseLightInfo& baseLight, const Rendering::SpotLightInfo& spotLight) :
			lightType(Rendering::LIGHT_TYPE_SPOT),
			baseLight(baseLight),
			spotLight(spotLight)
		{}

		Rendering::LightType lightType;
		Rendering::BaseLightInfo baseLight;
		Rendering::PointLightInfo pointLight;
		Rendering::SpotLightInfo spotLight;
	};

} }
