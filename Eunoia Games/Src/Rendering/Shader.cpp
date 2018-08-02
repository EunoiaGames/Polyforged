#include "Shader.h"
#include "../Platform/Opengl/ShaderGL.h"
#include "../Platform/D3D11/ShaderD3D11.h"
#include "../Rendering/RenderContext.h"

namespace Eunoia { namespace Rendering {

	Shader * Shader::CreateShader(const String& shaderFile)
	{
		switch (RenderContext::GetGraphicsAPI())
		{
		case GRAPHICS_API_D3D11: return new ShaderD3D11(shaderFile);
		case GRAPHICS_API_OPENGL: return new ShaderGL(shaderFile);
		}
	}

} }
