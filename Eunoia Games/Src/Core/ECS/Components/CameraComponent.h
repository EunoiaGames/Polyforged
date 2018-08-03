#pragma once

#include "../Component.h"
#include "../../../Math/Math.h"
#include "../../InputDefs.h"
#include "../../../Rendering/Display.h"

namespace Eunoia { namespace Components {

	DECLARE_COMPONENT(CameraComponent)
	{
		CameraComponent(const Math::Matrix4f projection) :
			projection(projection)
		{}

		CameraComponent(float fov = 70.0f) 
		{
			projection.InitPerspective(fov, Rendering::Display::GetDisplay()->GetWidth(), Rendering::Display::GetDisplay()->GetHeight(), 0.01f, 1000.0f);
		}

		Math::Matrix4f projection;
	};

} }