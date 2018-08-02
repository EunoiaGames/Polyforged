#include "MeshD3D11.h"

namespace Eunoia { namespace Rendering {

	MeshD3D11::MeshD3D11(const Vertex * pVertices, uint32 numVertices, const uint32 * pIndices, uint32 numIndices, MeshUsage usage)
	{
		m_pRenderContext = (RenderContextD3D11*)RenderContext::GetRenderContext();
		m_numIndices = numIndices;

		D3D11_BUFFER_DESC vertex_buffer_desc{};

		vertex_buffer_desc.Usage = D3D11_USAGE_DEFAULT;
		vertex_buffer_desc.ByteWidth = numVertices * sizeof(Vertex);
		vertex_buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertex_buffer_desc.CPUAccessFlags = 0;
		vertex_buffer_desc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA vertex_data{};

		vertex_data.pSysMem = pVertices;
		vertex_data.SysMemPitch = 0;
		vertex_data.SysMemSlicePitch = 0;

		HRESULT err = m_pRenderContext->GetDevice()->CreateBuffer(&vertex_buffer_desc, &vertex_data, &m_pVertexBuffer);

		if (err != S_OK)
		{
			std::cerr << "Error create d3d11 vertex buffer" << std::endl;
			return;
		}

		D3D11_BUFFER_DESC index_buffer_desc{};

		index_buffer_desc.Usage = D3D11_USAGE_DEFAULT;
		index_buffer_desc.ByteWidth = numIndices * sizeof(unsigned int);
		index_buffer_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		index_buffer_desc.CPUAccessFlags = 0;
		index_buffer_desc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA indice_data{};

		indice_data.pSysMem = pIndices;
		indice_data.SysMemPitch = 0;
		indice_data.SysMemSlicePitch = 0;

		err = m_pRenderContext->GetDevice()->CreateBuffer(&index_buffer_desc, &indice_data, &m_pIndexBuffer);

		if (err != S_OK)
		{
			std::cerr << "Error create d3d11 index buffer" << std::endl;
			return;
		}
	}

	MeshD3D11::~MeshD3D11()
	{
		m_pVertexBuffer->Release();
		m_pIndexBuffer->Release();
	}

	void MeshD3D11::Render() const
	{
		UINT stride = sizeof(Vertex);
		UINT offset = 0;

		m_pRenderContext->GetDeviceContext()->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
		m_pRenderContext->GetDeviceContext()->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
		m_pRenderContext->GetDeviceContext()->DrawIndexed(m_numIndices, 0, 0);
	}

	void MeshD3D11::Map(Vertex * pVertices) const
	{
		D3D11_MAPPED_SUBRESOURCE mapped_resource;
		m_pRenderContext->GetDeviceContext()->Map(m_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_resource);
		pVertices = (Vertex*)mapped_resource.pData;
	}

	void MeshD3D11::Unmap() const
	{
		m_pRenderContext->GetDeviceContext()->Unmap(m_pVertexBuffer, 0);
	}

} }
