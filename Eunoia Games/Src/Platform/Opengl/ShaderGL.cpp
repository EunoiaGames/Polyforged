#include "ShaderGL.h"
#include "../../Utils/FileReader.h"
#include <sstream>
#include "../../Math/Math.h"

namespace Eunoia { namespace Rendering {

	ShaderGL::ShaderGL(const String& shaderFile)
	{
		m_program = glCreateProgram();
		m_isGlobalUniformBuffer = true;

		memset(m_shaders, 0, sizeof(ShaderType) * NUM_SHADER_TYPES);

		String src = FileReader::ReadFile(String("Res/Shaders/GLSL/") + shaderFile + ".glsl", true);

		int vertex = src.FindFirstOf("#vertex");
		int fragment = src.FindFirstOf("#fragment", vertex);

		if (vertex == -1)
		{
			std::cerr << "Missing opengl vertex shader" << std::endl;
		}

		if (fragment == -1)
		{
			std::cerr << "Missing opengl fragment shader" << std::endl;
		}

		int vertexStart = src.FindFirstOf("#version", vertex);
		int fragmentStart = src.FindFirstOf("#version", fragment);

		String vertexSrc = src.SubString(vertexStart, fragment - 1);
		String fragmentSrc = src.SubString(fragmentStart);

		m_shaders[SHADER_TYPE_VERTEX] = CreateShader(vertexSrc, GL_VERTEX_SHADER);
		m_shaders[SHADER_TYPE_FRAGMENT] = CreateShader(fragmentSrc, GL_FRAGMENT_SHADER);

		LinkAndValidate();

		ParseShader(src);
	}

	void ShaderGL::Bind() const
	{
		glUseProgram(m_program);
	}

	void ShaderGL::SetBuffer(const String & bufferName, ShaderType type)
	{

	}

	void ShaderGL::SetBufferValue(const String & name, const void * pValue)
	{
		if (m_isGlobalUniformBuffer)
		{
			const auto&& it = m_globalUniforms.find(name);

			if (it != m_globalUniforms.end())
			{
				const ShaderGlobalUniformGL& uniform = it->second;

				switch (uniform.Type)
				{
				case SHADER_VARIABLE_FLOAT: SetUniformf(uniform.Location, (float*)pValue, uniform.Count); break;
				case SHADER_VARIABLE_INT: SetUniformi(uniform.Location, (int*)pValue, uniform.Count); break;
				case SHADER_VARIABLE_VEC2: SetUniformVec2(uniform.Location, (float*)pValue, uniform.Count); break;
				case SHADER_VARIABLE_VEC3: SetUniformVec3(uniform.Location, (float*)pValue, uniform.Count); break;
				case SHADER_VARIABLE_MAT4: SetUniformMat4(uniform.Location, (float*)pValue, uniform.Count); break;
				}
			}
		}
	}

	void ShaderGL::UpdateBuffer()
	{

	}

	void ShaderGL::SetBuffer(const String & name, const void * pValue, ShaderType type)
	{
		const auto&& it = m_structUniforms.find(name);

		if (it != m_structUniforms.end())
		{
			unsigned int offset = 0;
			SetStructUniform(name, it->second, pValue, offset);
		}
	}

	GLuint ShaderGL::CreateShader(const String & src, GLenum shaderType)
	{
		GLuint shader = glCreateShader(shaderType);

		if (shader == 0)
		{
			std::cerr << "Failder to create Opengl Vertex Shader" << std::endl;
			return 0;
		}

		const GLchar* shaderSourceStrings[1];
		GLint shaderSourceStringLengths[1];

		shaderSourceStringLengths[0] = src.Length();
		shaderSourceStrings[0] = src.C_Str();

		glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
		glCompileShader(shader);

		CheckForError(shader, GL_COMPILE_STATUS, false, "Error: Failed to compile shader: ");

		glAttachShader(m_program, shader);

		return shader;
	}

	void ShaderGL::LinkAndValidate()
	{
		glLinkProgram(m_program);
		CheckForError(m_program, GL_LINK_STATUS, true, "Error: Failed to link shader program: ");

		glValidateProgram(m_program);
		CheckForError(m_program, GL_VALIDATE_STATUS, true, "Error: Failed to validate program: ");
	}

	void ShaderGL::ParseShader(const String & src)
	{
		int index = src.FindFirstOf("struct ");

		while (index != -1)
		{
			int spaceIndex = index + 6;
			int openBracket = src.FindFirstOf("{", spaceIndex + 1);
			int newLine = src.FindFirstOf("\n", spaceIndex + 1);

			String name = src.SubString(spaceIndex + 1, MATH_MIN(openBracket, newLine));
			int endStructIndex = src.FindFirstOf("};", MATH_MAX(openBracket, newLine)) + 1;

			int semicolonIndex = src.FindFirstOf(";", MATH_MAX(openBracket, newLine));
			newLine = src.FindFirstOf("\n", MATH_MAX(openBracket, newLine));

			ShaderStructDeclarationGL struct_declaration;

			while (semicolonIndex != endStructIndex)
			{
				while (src[newLine + 1] == '\t' || src[newLine + 1] == ' ')
				{
					newLine++;
				}

				int spaceIndex = src.FindFirstOf(" ", newLine + 1);

				ShaderStructMemberGL member{};

				member.Type = src.SubString(newLine + 1, spaceIndex);
				member.Name = src.SubString(spaceIndex + 1, semicolonIndex);

				struct_declaration.Members.push_back(member);

				semicolonIndex = src.FindFirstOf(";", semicolonIndex + 1);
				newLine = src.FindFirstOf("\n", newLine + 1);
			}

			m_structDeclarations[name] = struct_declaration;
			index = src.FindFirstOf("struct ", endStructIndex + 1);
		}

		index = src.FindFirstOf("uniform ");
		while (index != -1)
		{
			int firstSpaceIndex = src.FindFirstOf(" ", index + 7);
			int secondSpaceIndex = src.FindFirstOf(" ", firstSpaceIndex + 1);
			int semicolonIndex = src.FindFirstOf(";", secondSpaceIndex + 1);

			String uniformType = src.SubString(firstSpaceIndex + 1, secondSpaceIndex);
			String uniformName = src.SubString(secondSpaceIndex + 1, semicolonIndex);

			unsigned int arraySize = 1;

			int arrayOpen = uniformName.FindFirstOf("[");
			if (arrayOpen != -1)
			{
				int arrayClose = uniformName.FindLastOf("]");
				String arraySizeStr = uniformName.SubString(arrayOpen + 1, arrayClose);
				uniformName = uniformName.SubString(0, uniformName.FindFirstOf("["));
				std::stringstream stringstream(arraySizeStr.C_Str());
				stringstream >> arraySize;
			}

			auto structDecIndex = m_structDeclarations.find(uniformType);

			if (structDecIndex != m_structDeclarations.end())
			{
				AddStructUniform(structDecIndex->second, uniformName);
				m_structUniforms[uniformName] = uniformType;
				index = src.FindFirstOf("uniform ", semicolonIndex + 1);
				continue;
			}

			GLint location = glGetUniformLocation(m_program, uniformName.C_Str());

			if (location == -1)
			{
				std::cerr << "Could not find opengl uniform " << uniformName << std::endl;
				index = src.FindFirstOf("uniform ", semicolonIndex + 1);
				continue;
			}

			ShaderVariableType type = SHADER_VARIABLE_INVALID_TYPE;

			if (uniformType == "float") type = SHADER_VARIABLE_FLOAT;
			else if (uniformType == "vec2") type = SHADER_VARIABLE_VEC2;
			else if (uniformType == "vec3") type = SHADER_VARIABLE_VEC3;
			else if (uniformType == "mat4") type = SHADER_VARIABLE_MAT4;
			else if (uniformType == "int") type = SHADER_VARIABLE_INT;
			else if (uniformType == "sampler2D")
			{
				type = SHADER_VARIABLE_SAMPLER2D;
				//m_textureUnits[uniformName] = currentTextureUnit;
				//currentTextureUnit++;
			}

			if (type == SHADER_VARIABLE_INVALID_TYPE)
			{
				std::cerr << "Unsupported glsl uniform type : " << uniformType << std::endl;
				return;
			}

			ShaderGlobalUniformGL uniform{};
			uniform.Location = location;
			uniform.Type = type;
			uniform.Count = arraySize;

			m_globalUniforms[uniformName] = uniform;

			index = src.FindFirstOf("uniform ", semicolonIndex + 1);
		}
	}

	void ShaderGL::AddStructUniform(const ShaderStructDeclarationGL & shaderStruct, const String & uniformName)
	{
		for (unsigned int i = 0; i < shaderStruct.Members.size(); i++)
		{
			const ShaderStructMemberGL& member = shaderStruct.Members[i];

			auto structDecIndex = m_structDeclarations.find(member.Type);

			if (structDecIndex != m_structDeclarations.end())
			{
				AddStructUniform(structDecIndex->second, uniformName + "." + member.Name);
				continue;
			}

			String finalName = uniformName + "." + member.Name;

			GLint location = glGetUniformLocation(m_program, finalName.C_Str());

			if (location == -1)
			{
				std::cerr << "Error finging glsl uniform location : " << finalName << std::endl;
			}

			ShaderGlobalUniformGL uniform{};

			if (member.Type == "float") uniform.Type = SHADER_VARIABLE_FLOAT;
			else if (member.Type == "vec2") uniform.Type = SHADER_VARIABLE_VEC2;
			else if (member.Type == "vec3") uniform.Type = SHADER_VARIABLE_VEC3;
			else if (member.Type == "mat4") uniform.Type = SHADER_VARIABLE_MAT4;

			uniform.Location = location;
			uniform.Count = 1;

			m_globalUniforms[finalName] = uniform;
		}
	}

	void ShaderGL::SetStructUniform(const String & uniformName, const String & structName, const void * pData, unsigned int & offset)
	{
		const ShaderStructDeclarationGL& shaderStruct = m_structDeclarations[structName];

		m_isGlobalUniformBuffer = true;

		for (unsigned int i = 0; i < shaderStruct.Members.size(); i++)
		{
			const ShaderStructMemberGL& member = shaderStruct.Members[i];

			auto structTypeIndex = m_structDeclarations.find(member.Type);

			if (structTypeIndex != m_structDeclarations.end())
			{
				SetStructUniform(uniformName + "." + member.Name, member.Type, pData, offset);
				continue;
			}
			
			if (member.Type == "float")
			{
				SetBufferValue(uniformName + "." + member.Name, (unsigned char*)pData + offset);
				offset += sizeof(float);
			}
			else if (member.Type == "vec2")
			{
				SetBufferValue(uniformName + "." + member.Name, (unsigned char*)pData + offset);
				offset += sizeof(Math::Vector2f);
			}
			else if (member.Type == "vec3")
			{
				SetBufferValue(uniformName + "." + member.Name, (unsigned char*)pData + offset);
				offset += sizeof(Math::Vector3f);
			}
			else if (member.Type == "mat4")
			{
				SetBufferValue(uniformName + "." + member.Name, (unsigned char*)pData + offset);
				offset += sizeof(Math::Matrix4f);
			}
		}
	}

	void ShaderGL::SetUniformf(GLint location, const float* pValues, unsigned int count) const { glUniform1fv(location, count, pValues); }
	void ShaderGL::SetUniformi(GLint location, const int* pValues, unsigned int count) const { glUniform1iv(location, count, pValues); }
	void ShaderGL::SetUniformVec2(GLint location, const float * pVec2s, unsigned int count) const { glUniform2fv(location, count, pVec2s); }
	void ShaderGL::SetUniformVec3(GLint location, const float * pVec3s, unsigned int count) const { glUniform3fv(location, count, pVec3s); }
	void ShaderGL::SetUniformMat4(GLint location, const float * pMat4s, unsigned int count) const { glUniformMatrix4fv(location, count, true, pMat4s); }

	void ShaderGL::CheckForError(GLuint shader, GLuint flag, bool isProgram, const String& errorMessage)
	{
		GLint success = 0;
		GLchar error[1024] = { 0 };

		if (isProgram)
		{
			glGetProgramiv(shader, flag, &success);
		}
		else
		{
			glGetShaderiv(shader, flag, &success);
		}

		if (success == GL_FALSE)
		{
			if (isProgram)
			{
				glGetProgramInfoLog(shader, sizeof(error), NULL, error);
			}
			else
			{
				glGetShaderInfoLog(shader, sizeof(error), NULL, error);
			}

			std::cerr << errorMessage << ": '" << error << "'" << std::endl;
		}
	}

} }
