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
		CreateDepthStencilView();
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
		m_pDeviceContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0xff);
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
		m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);
	}

	void RenderContextD3D11::SetDepthStencilState(const DepthStencilState & depthStencilState)
	{
		D3D11_DEPTH_STENCIL_DESC depth_stencil_desc;

		depth_stencil_desc.DepthEnable = depthStencilState.depthEnabled;
		depth_stencil_desc.DepthWriteMask = depthStencilState.depthWrite ? D3D11_DEPTH_WRITE_MASK_ALL : D3D11_DEPTH_WRITE_MASK_ZERO;

		switch (depthStencilState.depthComparison)
		{
		case DEPTH_COMPARISON_ALWAYS: depth_stencil_desc.DepthFunc = D3D11_COMPARISON_ALWAYS; break;
		case DEPTH_COMPARISON_NEVER: depth_stencil_desc.DepthFunc = D3D11_COMPARISON_NEVER; break;
		case DEPTH_COMPARISON_LESS: depth_stencil_desc.DepthFunc = D3D11_COMPARISON_LESS; break;
		case DEPTH_COMPARISON_GREATER: depth_stencil_desc.DepthFunc = D3D11_COMPARISON_GREATER; break;
		case DEPTH_COMPARISON_LESS_EQUAL: depth_stencil_desc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL; break;
		case DEPTH_COMPARISON_GREATER_EQUAL: depth_stencil_desc.DepthFunc = D3D11_COMPARISON_GREATER_EQUAL; break;
		case DEPTH_COMPARISON_EQUAL: depth_stencil_desc.DepthFunc = D3D11_COMPARISON_EQUAL; break;
		case DEPTH_COMPARISON_NOT_EQUAL: depth_stencil_desc.DepthFunc = D3D11_COMPARISON_NOT_EQUAL; break;
		}

		depth_stencil_desc.StencilEnable = depthStencilState.stencilEnabled;
		depth_stencil_desc.StencilReadMask = depthStencilState.mask;
		depth_stencil_desc.StencilWriteMask = depthStencilState.mask;

		depth_stencil_desc.BackFace = GetStencilOperationFace(depthStencilState.backFace);
		depth_stencil_desc.FrontFace = GetStencilOperationFace(depthStencilState.frontFace);

		m_pDepthStencilState->Release();
		m_pDevice->CreateDepthStencilState(&depth_stencil_desc, &m_pDepthStencilState);
		m_pDeviceContext->OMSetDepthStencilState(m_pDepthStencilState, depthStencilState.ref);
	}

	void RenderContextD3D11::SetBlendState(const BlendState & blendState)
	{
		D3D11_RENDER_TARGET_BLEND_DESC blend_desc;
		blend_desc.BlendEnable = blendState.enabled;

		switch (blendState.operation)
		{
		case BLEND_OPERATION_ADD: blend_desc.BlendOp = D3D11_BLEND_OP_ADD; break;
		case BLEND_OPERATION_SUB: blend_desc.BlendOp = D3D11_BLEND_OP_SUBTRACT; break;
		case BLEND_OPERATION_REV_SUB: blend_desc.BlendOp = D3D11_BLEND_OP_REV_SUBTRACT; break;
		case BLEND_OPERATION_MIN: blend_desc.BlendOp = D3D11_BLEND_OP_MIN; break;
		case BLEND_OPERATION_MAX: blend_desc.BlendOp = D3D11_BLEND_OP_MAX; break;
		}

		blend_desc.SrcBlend = GetBlendFunction(blendState.srcFunction);
		blend_desc.DestBlend = GetBlendFunction(blendState.destFunction);
		blend_desc.SrcBlendAlpha = D3D11_BLEND_ONE;
		blend_desc.DestBlendAlpha = D3D11_BLEND_ZERO;
		blend_desc.BlendOpAlpha = D3D11_BLEND_OP_ADD;
		blend_desc.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		D3D11_BLEND_DESC blend_desc_;
		blend_desc_.AlphaToCoverageEnable = false;
		blend_desc_.IndependentBlendEnable = false;
		blend_desc_.RenderTarget[0] = blend_desc;

		m_pBlendState->Release();
		m_pDevice->CreateBlendState(&blend_desc_, &m_pBlendState);
		m_pDeviceContext->OMSetBlendState(m_pBlendState, NULL, 0xffffffff);
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

	void RenderContextD3D11::CreateDepthStencilView()
	{
		DXGI_FORMAT depth_stencil_format = DXGI_FORMAT_D24_UNORM_S8_UINT;//DXGI_FORMAT_D32_FLOAT_S8X24_UINT;
		D3D11_TEXTURE2D_DESC depth_stencil_texture_desc{};

		depth_stencil_texture_desc.Width = Display::GetDisplay()->GetWidth();
		depth_stencil_texture_desc.Height = Display::GetDisplay()->GetHeight();
		depth_stencil_texture_desc.MipLevels = 1;
		depth_stencil_texture_desc.ArraySize = 1;
		depth_stencil_texture_desc.Format = depth_stencil_format;
		depth_stencil_texture_desc.SampleDesc.Count = 1;
		depth_stencil_texture_desc.SampleDesc.Quality = 0;
		depth_stencil_texture_desc.Usage = D3D11_USAGE_DEFAULT;
		depth_stencil_texture_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depth_stencil_texture_desc.CPUAccessFlags = 0;
		depth_stencil_texture_desc.MiscFlags = 0;

		ID3D11Texture2D* pDepthStencilTexture;
		HRESULT err = m_pDevice->CreateTexture2D(&depth_stencil_texture_desc, NULL, &pDepthStencilTexture);
		if (err != S_OK)
		{
			std::cerr << "Error creating d3d11 depth stencil texture" << std::endl;
		}

		D3D11_DEPTH_STENCIL_VIEW_DESC depth_stencil_view_desc;

		depth_stencil_view_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depth_stencil_view_desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		depth_stencil_view_desc.Texture2D.MipSlice = 0;
		depth_stencil_view_desc.Flags = 0;

		err = m_pDevice->CreateDepthStencilView(pDepthStencilTexture, &depth_stencil_view_desc, &m_pDepthStencilView);

		if (err != S_OK)
		{
			std::cerr << "Error creating d3d11 depth stencil view" << std::endl;
		}

		pDepthStencilTexture->Release();
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

	D3D11_DEPTH_STENCILOP_DESC RenderContextD3D11::GetStencilOperationFace(const StencilOperationFace & face)
	{
		D3D11_DEPTH_STENCILOP_DESC stencil_op_desc;
		stencil_op_desc.StencilDepthFailOp = GetStencilOperation(face.depthFail);
		stencil_op_desc.StencilFailOp = GetStencilOperation(face.stencilFail);
		stencil_op_desc.StencilPassOp = GetStencilOperation(face.stencilPass);

		switch (face.comparison)
		{
		case STENCIL_COMPARISON_NEVER: stencil_op_desc.StencilFunc = D3D11_COMPARISON_NEVER; break;
		case STENCIL_COMPARISON_LESS: stencil_op_desc.StencilFunc = D3D11_COMPARISON_LESS; break;
		case STENCIL_COMPARISON_LESS_EQUAL: stencil_op_desc.StencilFunc = D3D11_COMPARISON_LESS_EQUAL; break;
		case STENCIL_COMPARISON_GREATER: stencil_op_desc.StencilFunc = D3D11_COMPARISON_GREATER; break;
		case STENCIL_COMPARISON_GREATER_EQUAL: stencil_op_desc.StencilFunc = D3D11_COMPARISON_GREATER_EQUAL; break;
		case STENCIL_COMPARISON_EQUAL: stencil_op_desc.StencilFunc = D3D11_COMPARISON_EQUAL; break;
		case STENCIL_COMPARISON_NOT_EQUAL: stencil_op_desc.StencilFunc = D3D11_COMPARISON_NOT_EQUAL; break;
		case STENCIL_COMPARISON_ALWAYS: stencil_op_desc.StencilFunc = D3D11_COMPARISON_ALWAYS; break;
		}

		return stencil_op_desc;
	}

	D3D11_STENCIL_OP RenderContextD3D11::GetStencilOperation(StencilOperation operation)
	{
		switch (operation)
		{
		case STENCIL_OPERATION_KEEP: return D3D11_STENCIL_OP_KEEP;
		case STENCIL_OPERATION_ZERO: return D3D11_STENCIL_OP_ZERO;
		case STENCIL_OPERATION_REPLACE: return D3D11_STENCIL_OP_REPLACE;
		case STENCIL_OPERATION_INCR_CLAMP: return D3D11_STENCIL_OP_INCR_SAT;
		case STENCIL_OPERATION_DECR_CLAMP: return D3D11_STENCIL_OP_DECR_SAT;
		case STENCIL_OPERATION_INVERT: return D3D11_STENCIL_OP_INVERT;
		case STENCIL_OPERATION_INCR: return D3D11_STENCIL_OP_INCR;
		case STENCIL_OPERATION_DECR: return D3D11_STENCIL_OP_DECR;
		}
	}

	D3D11_BLEND RenderContextD3D11::GetBlendFunction(BlendFunction blendFunction) const
	{
		switch (blendFunction)
		{
		case BLEND_FUNCTION_ZERO: return D3D11_BLEND_ZERO;
		case BLEND_FUNCTION_ONE: return D3D11_BLEND_ONE;
		case BLEND_FUNCTION_SRC_COLOR: return D3D11_BLEND_SRC_COLOR;
		case BLEND_FUNCTION_INV_SOURCE_COLOR: return D3D11_BLEND_INV_SRC_COLOR;
		case BLEND_FUNCTION_DEST_COLOR: return D3D11_BLEND_DEST_COLOR;
		case BLEND_FUNCTION_INV_DEST_COLOR: return D3D11_BLEND_INV_DEST_COLOR;
		case BLEND_FUNCTION_SRC_ALPHA: return D3D11_BLEND_SRC_ALPHA;
		case BLEND_FUNCTION_SRC_INV_ALPHA: return D3D11_BLEND_INV_SRC_ALPHA;
		case BLEND_FUNCTION_DEST_ALPHA: return D3D11_BLEND_DEST_ALPHA;
		case BLEND_FUNCTION_DEST_INV_ALPHA: return D3D11_BLEND_INV_DEST_ALPHA;
		}
	}

} }
