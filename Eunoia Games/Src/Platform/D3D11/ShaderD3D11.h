#pragma once

#include "../../Rendering/Shader.h"
#include "RenderContextD3D11.h"
#include <d3dcompiler.h>
#include <map>
#include "../../Utils/DataBuffer.h"

namespace Eunoia { namespace Rendering {

	struct ShaderCBufferVariableD3D11
	{
		unsigned int	Size;
		unsigned int	Offset;
	};

	struct ShaderCBufferD3D11
	{
		ID3D11Buffer*	pBuffer;
		unsigned int	Size;
		unsigned int	Register;

		std::map<String, ShaderCBufferVariableD3D11> Variables;
	};

	typedef std::map<String, ShaderCBufferD3D11> ShaderCBufferD3D11Map;


	class ShaderD3D11 : public Shader
	{
	public:
		ShaderD3D11(const String& shaderFile);
		~ShaderD3D11();

		void Bind() const override;

		void SetBuffer(const String& bufferName, ShaderType type) override;
		void SetBufferValue(const String& name, const void* pValue) override;
		void UpdateBuffer() override;

		void SetBuffer(const String& name, const void* pValue, ShaderType type) override;
	private:
		ID3DBlob* CompileShader(const String& src, const String& main, const String& target);
		void CreateInputLayout(ID3D11ShaderReflection* pVertexReflection, ID3DBlob* pVertexShader);
		void LoadResources(ID3D11ShaderReflection* pReflection, ShaderType shaderType);
	private:
		RenderContextD3D11* m_pRenderContext;

		ShaderCBufferD3D11Map m_vertexCBufferMap;
		ShaderCBufferD3D11Map m_pixelCBufferMap;

		ShaderCBufferD3D11* m_pCurrentBuffer;
		ShaderType			m_currentShaderType;
		DataBuffer			m_dataBuffer;

		ID3D11VertexShader* m_pVertexShader;
		ID3D11PixelShader* m_pPixelShader;
		ID3D11InputLayout* m_pInputLayout;
	};

} }
