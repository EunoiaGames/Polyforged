#pragma once

#include "../../Rendering/NoDataMesh.h"
#include "../../Core/Common.h"
#include <GL\glew.h>

namespace Eunoia { namespace Rendering {

	class NoDataMeshGL : public NoDataMesh
	{
	public:
		NoDataMeshGL(uint32 numVertices);
		void Render() const override;
	private:
		uint32 m_numVertices;
		static GLuint s_emptyVao;
	};

} }
