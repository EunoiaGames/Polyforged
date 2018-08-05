#pragma once

#include "../../Rendering/RenderContext.h"
#include <d3d11.h>

namespace Eunoia { namespace Rendering {

	class RenderContextD3D11 : public RenderContext
	{
	public:
		RenderContextD3D11();
		~RenderContextD3D11();

		void SetVsync(bool vsync) override;

		void Clear() const override;
		void Swap() const override;
		void SetViewport(float x, float y, float w, float h) const override;
		void SetDisplayAsRenderTarget() const override;

		void SetDepthStencilState(const DepthStencilState& depthStencilState) override;
		void SetBlendState(const BlendState& blendState) override;

		IDXGISwapChain* GetSwapChain() const;
		ID3D11Device* GetDevice() const;
		ID3D11DeviceContext* GetDeviceContext() const;
	private:
		void CreateDeviceAndSwapChain();
		void CreateRenderTarget();
		void CreateDepthStencilView();
		void CreateDefaultDepthStencilState();
		void CreateDefaultBlendState();
		void CreateDefaultRasterizerState();

		D3D11_DEPTH_STENCILOP_DESC GetStencilOperationFace(const StencilOperationFace& face);
		D3D11_STENCIL_OP GetStencilOperation(StencilOperation operation);
		D3D11_BLEND GetBlendFunction(BlendFunction blendFunction) const;
	private:
		IDXGISwapChain* m_pSwapChain;
		ID3D11Device* m_pDevice;
		ID3D11DeviceContext* m_pDeviceContext;
		ID3D11RenderTargetView* m_pRenderTargetView;
		ID3D11DepthStencilView* m_pDepthStencilView;

		ID3D11DepthStencilState* m_pDepthStencilState;
		ID3D11BlendState* m_pBlendState;
		ID3D11RasterizerState* m_pRasterizerState;

		float m_clearColor[4];
		UINT m_vsync;
	};

} }
