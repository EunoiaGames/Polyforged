#include "RenderContextD3D11.h"
#include "../Windows/Win32Display.h"

namespace Eunoia { namespace Rendering {

	RenderContextD3D11::RenderContextD3D11()
	{
		m_clearColor[0] = 0.0f;
		m_clearColor[1] = 0.0f;
		m_clearColor[2] = 0.0f;
		m_clearColor[3] = 1.0f;

		CreateDeviceAndSwapChain();
		CreateRenderTarget();
		CreateDefaultDepthStencilState();
		CreateDefaultBlendState();
		CreateDefaultRasterizerState();
	}

	RenderContextD3D11::~RenderContextD3D11()
	{
		m_pSwapChain->Release();
		m_pDevice->Release();
		m_pDeviceContext->Release();
		m_pRenderTargetView->Release();
		m_pDepthStencilState->Release();
		m_pBlendState->Release();
		m_pRasterizerState->Release();
	}

	void RenderContextD3D11::SetVsync(bool vsync)
	{
		m_vsync = vsync ? 1 : 0;
	}

	void RenderContextD3D11::Clear() const
	{
		m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetView, m_clearColor);
	}

	void RenderContextD3D11::Swap() const
	{
		m_pSwapChain->Present(m_vsync, 0);
	}

	void RenderContextD3D11::SetViewport(float x, float y, float w, float h) const
	{
		D3D11_VIEWPORT viewport{};
		viewport.TopLeftX = x;
		viewport.TopLeftY = y;
		viewport.Width = w;
		viewport.Height = h;
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;

		D3D11_RECT rect;
		rect.left = x;
		rect.right = w;
		rect.top = y;
		rect.bottom = h;

		m_pDeviceContext->RSSetViewports(1, &viewport);
		m_pDeviceContext->RSSetScissorRects(1, &rect);
	}

	void RenderContextD3D11::SetDisplayAsRenderTarget() const
	{
		m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, NULL);
	}

	IDXGISwapChain * RenderContextD3D11::GetSwapChain() const
	{
		return m_pSwapChain;
	}

	ID3D11Device * RenderContextD3D11::GetDevice() const
	{
		return m_pDevice;
	}

	ID3D11DeviceContext * RenderContextD3D11::GetDeviceContext() const
	{
		return m_pDeviceContext;
	}

	void RenderContextD3D11::CreateDeviceAndSwapChain()
	{
		DXGI_SWAP_CHAIN_DESC swap_chain_desc{};
		swap_chain_desc.BufferCount = 1;
		swap_chain_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swap_chain_desc.OutputWindow = ((Win32Display*)Display::GetDisplay())->GetWindowHandle();
		swap_chain_desc.SampleDesc.Count = 1;
		swap_chain_desc.Windowed = true;

		HRESULT err = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, NULL, 0, D3D11_SDK_VERSION,
			&swap_chain_desc, &m_pSwapChain, &m_pDevice, NULL, &m_pDeviceContext);

		if (err != S_OK)
		{
			std::cerr << "Error creating d3d11 device and swap chain" << std::endl;
		}
		else
		{
			std::cout << "Created d3d11 device and swap chain" << std::endl;
		}
	}

	void RenderContextD3D11::CreateRenderTarget()
	{
		ID3D11Texture2D* pBackBuffer;
		HRESULT err = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer);

		if (err != S_OK)
		{
			std::cerr << "Could not get back buffer from swap chain" << std::endl;
		}

		err = m_pDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_pRenderTargetView);
		pBackBuffer->Release();
		if (err != S_OK)
		{
			std::cerr << "Error creating d3d11 render target chain" << std::endl;
		}
	}

	void RenderContextD3D11::CreateDefaultDepthStencilState()
	{
		D3D11_DEPTH_STENCIL_DESC depth_stencil_desc{};

		depth_stencil_desc.DepthEnable = true;
		depth_stencil_desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		depth_stencil_desc.DepthFunc = D3D11_COMPARISON_LESS;

		depth_stencil_desc.StencilEnable = false;
		depth_stencil_desc.StencilReadMask = 0xFF;
		depth_stencil_desc.StencilWriteMask = 0xFF;

		depth_stencil_desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		depth_stencil_desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
		depth_stencil_desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		depth_stencil_desc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		depth_stencil_desc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		depth_stencil_desc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
		depth_stencil_desc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		depth_stencil_desc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		HRESULT err = m_pDevice->CreateDepthStencilState(&depth_stencil_desc, &m_pDepthStencilState);

		if (err != S_OK)
		{
			std::cerr << "Error creating d3d11 depth stencil state" << std::endl;
		}

		m_pDeviceContext->OMSetDepthStencilState(m_pDepthStencilState, 1);
	}

	void RenderContextD3D11::CreateDefaultBlendState()
	{
		D3D11_RENDER_TARGET_BLEND_DESC blend_desc;
		blend_desc.BlendEnable = false;
		blend_desc.BlendOp = D3D11_BLEND_OP_ADD;

		blend_desc.SrcBlend = D3D11_BLEND_ONE;
		blend_desc.DestBlend = D3D11_BLEND_ZERO;
		blend_desc.SrcBlendAlpha = D3D11_BLEND_ONE;
		blend_desc.DestBlendAlpha = D3D11_BLEND_ZERO;
		blend_desc.BlendOpAlpha = D3D11_BLEND_OP_ADD;
		blend_desc.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		D3D11_BLEND_DESC blend_desc_;
		blend_desc_.AlphaToCoverageEnable = false;
		blend_desc_.IndependentBlendEnable = false;
		blend_desc_.RenderTarget[0] = blend_desc;

		m_pDevice->CreateBlendState(&blend_desc_, &m_pBlendState);
		m_pDeviceContext->OMSetBlendState(m_pBlendState, NULL, 0xffffffff);
	}

	void RenderContextD3D11::CreateDefaultRasterizerState()
	{
		D3D11_RASTERIZER_DESC rasterizer_desc{};
		rasterizer_desc.CullMode = D3D11_CULL_NONE;
		rasterizer_desc.FillMode = D3D11_FILL_SOLID;
		rasterizer_desc.FrontCounterClockwise = true;
		rasterizer_desc.ScissorEnable = true;

		HRESULT err = m_pDevice->CreateRasterizerState(&rasterizer_desc, &m_pRasterizerState);

		if (err != S_OK)
		{
			std::cerr << "Error creating d3d11 rasterizer state" << std::endl;
		}

		m_pDeviceContext->RSSetState(m_pRasterizerState);
	}

} }
