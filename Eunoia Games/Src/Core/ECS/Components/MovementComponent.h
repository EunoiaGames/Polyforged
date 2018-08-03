#pragma once

#include "../Component.h"
#include "../../../Math/Math.h"
#include "../../InputDefs.h"

namespace Eunoia { namespace Components {

	DECLARE_COMPONENT(MovementComponent)
	{
		MovementComponent(float speed, Key forward = INPUT_KEY_W, Key back = INPUT_KEY_S, Key left = INPUT_KEY_A, Key right = INPUT_KEY_D) :
			speed(speed),
			forward(forward),
			back(back),
			left(left),
			right(right)
		{}

		Key forward;
		Key back;
		Key left;
		Key right;
		float speed;
	};

} }
