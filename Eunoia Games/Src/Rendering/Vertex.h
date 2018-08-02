#pragma once

#include "../Math/Math.h"

namespace Eunoia { namespace Rendering { 
	
	enum VertexAttribute
	{
		VERTEX_ATTRIBUTE_POS,
		VERTEX_ATTRIBUTE_COLOR,

		NUM_VERTEX_ATTRIBUTES
	};

	struct Vertex
	{
		Vertex(const Math::Vector3f& pos, const Math::Vector3f& color) :
			pos(pos),
			color(color)
		{}

		Math::Vector3f pos;
		Math::Vector3f color;
	};

} }