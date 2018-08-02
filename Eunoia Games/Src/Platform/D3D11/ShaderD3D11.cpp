#include "ShaderD3D11.h"
#include "../../Utils/FileReader.h"

namespace Eunoia { namespace Rendering {

	ShaderD3D11::ShaderD3D11(const String & shaderFile)
	{
		m_pRenderContext = (RenderContextD3D11*)RenderContext::GetRenderContext();
		String src = FileReader::ReadFile(String("Res/Shaders/HLSL/") + shaderFile + ".hlsl");

		ID3DBlob* pVertexShader = CompileShader(src, "VSMain", "vs_5_0");
		ID3DBlob* pPixelShader = CompileShader(src, "PSMain", "ps_5_0");

		HRESULT err = m_pRenderContext->GetDevice()->CreateVertexShader(pVertexShader->GetBufferPointer(), pVertexShader->GetBufferSize(), NULL, &m_pVertexShader);

		if (err != S_OK)
		{
			std::cerr << "Could not create d3d11 vertex shader" << std::endl;
			return;
		}

		err = m_pRenderContext->GetDevice()->CreatePixelShader(pPixelShader->GetBufferPointer(), pPixelShader->GetBufferSize(), NULL, &m_pPixelShader);

		ID3D11ShaderReflection* pShaderReflection;
		err = D3DReflect(pVertexShader->GetBufferPointer(), pVertexShader->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)&pShaderReflection);

		if (err != S_OK)
		{
			std::cerr << "Could not create d3d11 vertex shader reflection" << std::endl;
			return;
		}

		CreateInputLayout(pShaderReflection, pVertexShader);
		LoadResources(pShaderReflection, SHADER_TYPE_VERTEX);

		err = D3DReflect(pPixelShader->GetBufferPointer(), pPixelShader->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)&pShaderReflection);

		if (err != S_OK)
		{
			std::cerr << "Could not create d3d11 pixel shader reflection" << std::endl;
			return;
		}

		LoadResources(pShaderReflection, SHADER_TYPE_FRAGMENT);
	}

	ShaderD3D11::~ShaderD3D11()
	{
	}

	void ShaderD3D11::Bind() const
	{
		m_pRenderContext->GetDeviceContext()->IASetInputLayout(m_pInputLayout);
		m_pRenderContext->GetDeviceContext()->VSSetShader(m_pVertexShader, NULL, 0);
		m_pRenderContext->GetDeviceContext()->PSSetShader(m_pPixelShader, NULL, 0);
	}

	void ShaderD3D11::SetBuffer(const String & bufferName, ShaderType type)
	{
		if (type == SHADER_TYPE_VERTEX)
		{
			if (m_vertexCBufferMap.find(bufferName) != m_vertexCBufferMap.end())
			{
				m_pCurrentBuffer = &m_vertexCBufferMap[bufferName];
				m_currentShaderType = SHADER_TYPE_VERTEX;
			}
			else
			{
				return;
			}
		}
		else if (type == SHADER_TYPE_FRAGMENT)
		{
			if (m_pixelCBufferMap.find(bufferName) != m_pixelCBufferMap.end())
			{
				m_pCurrentBuffer = &m_pixelCBufferMap[bufferName];
				m_currentShaderType = SHADER_TYPE_FRAGMENT;
			}
			else
			{
				return;
			}
		}

		D3D11_MAPPED_SUBRESOURCE resource{};

		HRESULT err = m_pRenderContext->GetDeviceContext()->Map(m_pCurrentBuffer->pBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);

		if (err != S_OK)
		{
			std::cerr << "Could not map d3d11 cbuffer" << std::endl;
			return;
		}

		m_dataBuffer.SetNewData(resource.pData);
	}

	void ShaderD3D11::SetBufferValue(const String & name, const void * pValue)
	{
		if (!m_pCurrentBuffer)
		{
			return;
		}

		const auto&& it = m_pCurrentBuffer->Variables.find(name);
		if (it != m_pCurrentBuffer->Variables.end())
		{
			const ShaderCBufferVariableD3D11& variable = it->second;
			m_dataBuffer.Write(pValue, variable.Offset, variable.Size);
		}
	}

	void ShaderD3D11::UpdateBuffer()
	{
		if (!m_pCurrentBuffer)
		{
			return;
		}

		m_pRenderContext->GetDeviceContext()->Unmap(m_pCurrentBuffer->pBuffer, 0);

		if (m_currentShaderType == SHADER_TYPE_VERTEX)
		{
			m_pRenderContext->GetDeviceContext()->VSSetConstantBuffers(m_pCurrentBuffer->Register, 1, &m_pCurrentBuffer->pBuffer);
		}
		else if (m_currentShaderType == SHADER_TYPE_FRAGMENT)
		{
			m_pRenderContext->GetDeviceContext()->PSSetConstantBuffers(m_pCurrentBuffer->Register, 1, &m_pCurrentBuffer->pBuffer);
		}

		m_dataBuffer.SetNewData(NULL);
		m_pCurrentBuffer = NULL;
	}

	void ShaderD3D11::SetBuffer(const String & name, const void * pValue, ShaderType type)
	{
		D3D11_MAPPED_SUBRESOURCE resource{};

		const ShaderCBufferD3D11* pBuffer = NULL;
		if (type == SHADER_TYPE_VERTEX)
		{
			auto index = m_vertexCBufferMap.find(name);
			if (index != m_vertexCBufferMap.end())
			{
				pBuffer = &index->second;
			}
			else
			{
				return;
			}
		}
		else if (type == SHADER_TYPE_FRAGMENT)
		{
			auto index = m_pixelCBufferMap.find(name);
			if (index != m_pixelCBufferMap.end())
			{
				pBuffer = &index->second;
			}
			else
			{
				return;
			}
		}

		HRESULT err = m_pRenderContext->GetDeviceContext()->Map(pBuffer->pBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);

		if (err != S_OK)
		{
			std::cerr << "Error mapping d3d11 cbuffer " << name << std::endl;
			return;
		}

		memcpy(resource.pData, pValue, pBuffer->Size);
		m_pRenderContext->GetDeviceContext()->Unmap(pBuffer->pBuffer, 0);

		if (type == SHADER_TYPE_VERTEX)
		{
			m_pRenderContext->GetDeviceContext()->VSSetConstantBuffers(pBuffer->Register, 1, &pBuffer->pBuffer);
		}
		else if (type == SHADER_TYPE_FRAGMENT)
		{
			m_pRenderContext->GetDeviceContext()->PSSetConstantBuffers(pBuffer->Register, 1, &pBuffer->pBuffer);
		}
	}

	ID3DBlob * ShaderD3D11::CompileShader(const String & src, const String & main, const String & target)
	{
		ID3DBlob* pCode;
		ID3DBlob* pErrMsgs;

		HRESULT err = D3DCompile(src.C_Str(), src.Length(), NULL, NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE,
			main.C_Str(), target.C_Str(), D3DCOMPILE_DEBUG, 0, &pCode, &pErrMsgs);

		if (err != S_OK)
		{
			std::cerr << "Could not compile d3d11 " << target << " shader" << std::endl;
			std::cerr << (char*)pErrMsgs->GetBufferPointer() << std::endl;
			return NULL;
		}

		return pCode;
	}

	void ShaderD3D11::CreateInputLayout(ID3D11ShaderReflection * pVertexReflection, ID3DBlob * pVertexShader)
	{
		D3D11_SHADER_DESC vertex_shader_desc{};

		pVertexReflection->GetDesc(&vertex_shader_desc);

		std::vector<D3D11_INPUT_ELEMENT_DESC> layouts;
		unsigned int byteOffset = 0;
		for (unsigned int i = 0; i < vertex_shader_desc.InputParameters; i++)
		{
			D3D11_SIGNATURE_PARAMETER_DESC param_desc;
			pVertexReflection->GetInputParameterDesc(i, &param_desc);
			unsigned int paramOffset = byteOffset;

			DXGI_FORMAT paramFormat;

			if (param_desc.Mask == 1)
			{
				if (param_desc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) paramFormat = DXGI_FORMAT_R32_FLOAT;
				byteOffset += 4;
			}
			else if (param_desc.Mask <= 3)
			{
				if (param_desc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) paramFormat = DXGI_FORMAT_R32G32_FLOAT;
				byteOffset += 8;
			}
			else if (param_desc.Mask <= 7)
			{
				if (param_desc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) paramFormat = DXGI_FORMAT_R32G32B32_FLOAT;
				byteOffset += 12;
			}
			else if (param_desc.Mask <= 15)
			{
				if (param_desc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) paramFormat = DXGI_FORMAT_R32G32B32A32_FLOAT;
				byteOffset += 16;
			}

			D3D11_INPUT_ELEMENT_DESC layout;

			layout.SemanticName = param_desc.SemanticName;
			layout.SemanticIndex = param_desc.SemanticIndex;
			layout.Format = paramFormat;
			layout.InputSlot = 0;
			layout.AlignedByteOffset = paramOffset;
			layout.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			layout.InstanceDataStepRate = 0;

			layouts.push_back(layout);
		}

		HRESULT err = m_pRenderContext->GetDevice()->CreateInputLayout(&layouts[0], layouts.size(), pVertexShader->GetBufferPointer(),
			pVertexShader->GetBufferSize(), &m_pInputLayout);

		if (err != S_OK)
		{
			std::cerr << "Could not create d3d11 vertex shader layout" << std::endl;
			return;
		}
	}

	void ShaderD3D11::LoadResources(ID3D11ShaderReflection * pReflection, ShaderType shaderType)
	{
		D3D11_SHADER_DESC shader_desc{};
		pReflection->GetDesc(&shader_desc);

		for (unsigned int i = 0; i < shader_desc.BoundResources; i++)
		{
			D3D11_SHADER_INPUT_BIND_DESC bind_desc{};
			pReflection->GetResourceBindingDesc(i, &bind_desc);

			if (bind_desc.Type == D3D_SIT_CBUFFER)
			{
				ID3D11ShaderReflectionConstantBuffer* pCBuffer = pReflection->GetConstantBufferByName(bind_desc.Name);

				D3D11_SHADER_BUFFER_DESC shader_buffer_desc{};
				pCBuffer->GetDesc(&shader_buffer_desc);

				ShaderCBufferD3D11 cbuffer{};
				cbuffer.Size = shader_buffer_desc.Size;
				cbuffer.Register = bind_desc.BindPoint;

				D3D11_BUFFER_DESC cbuffer_desc{};
				cbuffer_desc.ByteWidth = cbuffer.Size;
				cbuffer_desc.Usage = D3D11_USAGE_DYNAMIC;
				cbuffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
				cbuffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
				cbuffer_desc.MiscFlags = 0;
				cbuffer_desc.StructureByteStride = 0;

				D3D11_SUBRESOURCE_DATA init_data;
				init_data.pSysMem = malloc(cbuffer.Size);
				init_data.SysMemPitch = 0;
				init_data.SysMemSlicePitch = 0;

				HRESULT err = m_pRenderContext->GetDevice()->CreateBuffer(&cbuffer_desc, &init_data, &cbuffer.pBuffer);

				if (err != S_OK)
				{
					std::cerr << "Error creating d3d11 cbuffer" << std::endl;
					return;
				}

				for (unsigned int j = 0; j < shader_buffer_desc.Variables; j++)
				{
					ID3D11ShaderReflectionVariable* pVariable = pCBuffer->GetVariableByIndex(j);

					D3D11_SHADER_VARIABLE_DESC variable_desc{};
					pVariable->GetDesc(&variable_desc);

					ShaderCBufferVariableD3D11 variable{};
					variable.Size = variable_desc.Size;
					variable.Offset = variable_desc.StartOffset;

					cbuffer.Variables[String(variable_desc.Name)] = variable;
				}

				if (shaderType == SHADER_TYPE_VERTEX)
				{
					m_vertexCBufferMap[String(shader_buffer_desc.Name)] = cbuffer;
				}
				else if (shaderType == SHADER_TYPE_FRAGMENT)
				{
					m_pixelCBufferMap[String(shader_buffer_desc.Name)] = cbuffer;
				}
			}
			else if (bind_desc.Type = D3D_SIT_TEXTURE)
			{
				if (shaderType == SHADER_TYPE_FRAGMENT)
				{
					//m_pixelTextureUnits[String(bind_desc.Name)] = bind_desc.BindPoint;
				}
			}
		}
	}

} }
