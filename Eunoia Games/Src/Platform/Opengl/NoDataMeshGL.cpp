#include "NoDataMeshGL.h"

namespace Eunoia { namespace Rendering {

	GLuint NoDataMeshGL::s_emptyVao = 0;

	NoDataMeshGL::NoDataMeshGL(uint32 numVertices) :
		m_numVertices(numVertices)
	{
		if (!s_emptyVao)
			glGenVertexArrays(1, &s_emptyVao);
	}

	void NoDataMeshGL::Render() const
	{
		glBindVertexArray(s_emptyVao);
		glDrawArrays(GL_TRIANGLES, 0, m_numVertices);
	}

} }
