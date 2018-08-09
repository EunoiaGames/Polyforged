#include "MeshGL.h"

namespace Eunoia { namespace Rendering {

	MeshGL::MeshGL(const Vertex * pVertices, uint32 numVertices, const uint32 * pIndices, uint32 numIndices, MeshUsage usage)
	{
		m_count = numIndices;

		glGenVertexArrays(1, &m_vao);
		glGenBuffers(1, &m_vbo);
		glGenBuffers(1, &m_ibo);

		glBindVertexArray(m_vao);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * numVertices, pVertices, GetUsage(usage));
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32) * numIndices, pIndices, GL_STATIC_DRAW);

		glVertexAttribPointer(VERTEX_ATTRIBUTE_POS, 3, GL_FLOAT, false, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, Vertex::pos));
		glVertexAttribPointer(VERTEX_ATTRIBUTE_COLOR, 3, GL_FLOAT, false, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, Vertex::color));
		glVertexAttribPointer(VERTEX_ATTRIBUTE_NORMAL, 3, GL_FLOAT, false, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, Vertex::normal));

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	MeshGL::MeshGL(const Vertex * pVertices, uint32 numVertices, MeshUsage usage)
	{
		m_count = numVertices;
		m_ibo = 0;

		glGenVertexArrays(1, &m_vao);
		glGenBuffers(1, &m_vbo);

		glBindVertexArray(m_vao);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * numVertices, pVertices, GetUsage(usage));

		glVertexAttribPointer(VERTEX_ATTRIBUTE_POS, 3, GL_FLOAT, false, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, Vertex::pos));
		glVertexAttribPointer(VERTEX_ATTRIBUTE_COLOR, 3, GL_FLOAT, false, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, Vertex::color));
		glVertexAttribPointer(VERTEX_ATTRIBUTE_NORMAL, 3, GL_FLOAT, false, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, Vertex::normal));

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	MeshGL::~MeshGL()
	{
		glDeleteVertexArrays(1, &m_vao);
		glDeleteBuffers(1, &m_vbo);

		if(m_ibo)
			glDeleteBuffers(1, &m_ibo);
	}

	void MeshGL::Render() const
	{
		glBindVertexArray(m_vao);

		for (uint32 i = 0; i < NUM_VERTEX_ATTRIBUTES; i++)
			glEnableVertexAttribArray(i);

		if (m_ibo == 0)
		{
			glDrawArrays(GL_TRIANGLES, 0, m_count);
		}
		else
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
			glDrawElements(GL_TRIANGLES, m_count, GL_UNSIGNED_INT, NULL);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		for (uint32 i = 0; i < NUM_VERTEX_ATTRIBUTES; i++)
			glDisableVertexAttribArray(i);

		glBindVertexArray(0);
	}

	void MeshGL::Map(Vertex * pVertices) const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		pVertices = (Vertex*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}

	void MeshGL::Unmap() const
	{
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	GLenum MeshGL::GetUsage(MeshUsage usage)
	{
		switch (usage)
		{
		case MESH_USAGE_DYNAMIC: return GL_DYNAMIC_DRAW;
		case MESH_USAGE_STATIC: return GL_STATIC_DRAW;
		}
	}

} }
