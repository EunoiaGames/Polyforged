#pragma once

#include "../DataStructures/String.h"

namespace Eunoia { namespace Rendering { 

	enum ShaderType
	{
		SHADER_TYPE_VERTEX,
		SHADER_TYPE_FRAGMENT,

		NUM_SHADER_TYPES
	};

	enum ShaderVariableType
	{
		SHADER_VARIABLE_FLOAT,
		SHADER_VARIABLE_INT,
		SHADER_VARIABLE_VEC2,
		SHADER_VARIABLE_VEC3,
		SHADER_VARIABLE_MAT4,

		SHADER_VARIABLE_SAMPLER2D,

		NUM_SHADER_VARIABLE_TYPES,
		SHADER_VARIABLE_INVALID_TYPE = -1
	};

	class Shader
	{
	public:
		virtual void Bind() const = 0;

		virtual void SetBuffer(const String& bufferName, ShaderType type) = 0;
		virtual void SetBufferValue(const String& name, const void* pValue) = 0;
		virtual void UpdateBuffer() = 0;

		virtual void SetBuffer(const String& name, const void* pValue, ShaderType type) = 0;

		static Shader* CreateShader(const String& shaderFile);
	};

} }
