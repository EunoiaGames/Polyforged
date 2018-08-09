#pragma once

#include "../Core/Common.h"

namespace Eunoia { namespace Rendering {

	class NoDataMesh
	{
	public:
		virtual void Render() const = 0;
		
		static NoDataMesh* CreateNoDataMesh(uint32 numVertices);
	};

} }
