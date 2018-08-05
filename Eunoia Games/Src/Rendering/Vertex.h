#pragma once

#include "../Math/Math.h"

namespace Eunoia { namespace Rendering { 
	
	enum VertexAttribute
	{
		VERTEX_ATTRIBUTE_POS,
		VERTEX_ATTRIBUTE_COLOR,
		VERTEX_ATTRIBUTE_NORMAL,

		NUM_VERTEX_ATTRIBUTES
	};

	struct Vertex
	{
		Vertex(const Math::Vector3f& pos, const Math::Vector3f& color, const Math::Vector3f& normal = Math::Vector3f(0.0f, 0.0f, 0.0f)) :
			pos(pos),
			color(color),
			normal(normal)
		{}

		Math::Vector3f pos;
		Math::Vector3f color;
		Math::Vector3f normal;
	};

} }