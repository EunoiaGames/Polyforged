#pragma once

#include "../../Rendering/Shader.h"
#include <GL\glew.h>
#include <map>

namespace Eunoia { namespace Rendering {

	struct ShaderGlobalUniformGL
	{
		ShaderVariableType	Type;
		GLint				Location;
		unsigned int		Count;
	};

	class ShaderGL : public Shader
	{
	public:
		ShaderGL(const String& shaderFile);

		void Bind() const override;

		void SetBuffer(const String& bufferName, ShaderType type) override;
		void SetBufferValue(const String& name, const void* pValue) override;
		void UpdateBuffer() override;

		void SetBuffer(const String& name, const void* pValue, ShaderType type) override;
	private:
		GLuint CreateShader(const String& src, GLenum shaderType);
		void LinkAndValidate();
		void ParseShader(const String& src);

		void SetUniformf(GLint location, const float* pValues, unsigned int count) const;
		void SetUniformi(GLint location, const int* pValues, unsigned int count) const;
		void SetUniformVec2(GLint location, const float* pVec2s, unsigned int count) const;
		void SetUniformVec3(GLint location, const float* pVec3s, unsigned int count) const;
		void SetUniformMat4(GLint location, const float* pVat4s, unsigned int count) const;

		static void CheckForError(GLuint shader, GLuint flag, bool isProgram, const String& errorMessage);
	private:
		GLuint m_program;

		GLuint m_shaders[NUM_SHADER_TYPES];

		std::map<String, ShaderGlobalUniformGL> m_globalUniforms;

		bool m_isGlobalUniformBuffer;
	};

} }
