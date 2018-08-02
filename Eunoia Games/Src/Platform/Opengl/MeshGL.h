#pragma once

#include "../../Rendering/Mesh.h"
#include <GL\glew.h>

namespace Eunoia { namespace Rendering { 

	class MeshGL : public Mesh
	{
	public:
		MeshGL(const Vertex* pVertices, uint32 numVertices, const uint32* indices, uint32 numIndices, MeshUsage usage);

		void Render() const override;
		void Map(Vertex* pVertices) const override;
		void Unmap() const override;
	private:
		static GLenum GetUsage(MeshUsage usage);
	private:
		GLuint m_vao;
		GLuint m_vbo;
		GLuint m_ibo;

		uint32 m_numIndices;
	};

} }
