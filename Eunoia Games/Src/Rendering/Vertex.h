#pragma once

#include "../Math/Math.h"

namespace Eunoia { namespace Rendering { 
	
	enum VertexAttribute
	{
		VERTEX_ATTRIBUTE_POS,

		NUM_VERTEX_ATTRIBUTES
	};

	struct Vertex
	{
		Vertex(const Math::Vector3f& pos) :
			pos(pos)
		{}

		Math::Vector3f pos;
	};

} }