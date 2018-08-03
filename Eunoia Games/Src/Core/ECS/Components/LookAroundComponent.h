#pragma once

#include "../Component.h"
#include "../../../Math/Math.h"
#include "../../InputDefs.h"

namespace Eunoia { namespace Components {

	DECLARE_COMPONENT(LookAroundComponent)
	{
		LookAroundComponent(float sensitivity, Key toggleKey) :
			sensitivity(sensitivity),
			toggleKey(toggleKey)
		{}

		float sensitivity;
		Key toggleKey;
	};

} }
