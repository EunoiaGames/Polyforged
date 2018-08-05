#include "RenderStates.h"

namespace Eunoia { namespace Rendering {

	void create_blend_state_no_blend(BlendState* pBlendState)
	{
		pBlendState->enabled = true;
		pBlendState->operation = BLEND_OPERATION_ADD;
		pBlendState->srcFunction = BLEND_FUNCTION_ONE;
		pBlendState->destFunction = BLEND_FUNCTION_ZERO;
	}

	void create_blend_state_additive_blending(BlendState* pBlendState)
	{
		pBlendState->enabled = true;
		pBlendState->operation = BLEND_OPERATION_ADD;
		pBlendState->srcFunction = BLEND_FUNCTION_ONE;
		pBlendState->destFunction = BLEND_FUNCTION_ONE;
	}

	void create_depth_stencil_state_no_depth_stencil(DepthStencilState* pDepthStencilState)
	{
		pDepthStencilState->depthEnabled = false;
		pDepthStencilState->depthWrite = false;
		pDepthStencilState->depthComparison = DEPTH_COMPARISON_LESS;
		pDepthStencilState->stencilEnabled = false;
		pDepthStencilState->backFace.depthFail = STENCIL_OPERATION_KEEP;
		pDepthStencilState->backFace.stencilPass = STENCIL_OPERATION_KEEP;
		pDepthStencilState->backFace.stencilFail = STENCIL_OPERATION_KEEP;
		pDepthStencilState->backFace.comparison = STENCIL_COMPARISON_ALWAYS;
		pDepthStencilState->frontFace = pDepthStencilState->backFace;
		pDepthStencilState->ref = 0;
		pDepthStencilState->mask = 0;
	}

	void create_depth_stencil_state_no_stencil(DepthStencilState* pDepthStencilState)
	{
		pDepthStencilState->depthEnabled = true;
		pDepthStencilState->depthWrite = true;
		pDepthStencilState->depthComparison = DEPTH_COMPARISON_LESS;
		pDepthStencilState->stencilEnabled = false;
		pDepthStencilState->backFace.depthFail = STENCIL_OPERATION_KEEP;
		pDepthStencilState->backFace.stencilPass = STENCIL_OPERATION_KEEP;
		pDepthStencilState->backFace.stencilFail = STENCIL_OPERATION_KEEP;
		pDepthStencilState->backFace.comparison = STENCIL_COMPARISON_ALWAYS;
		pDepthStencilState->frontFace = pDepthStencilState->backFace;
		pDepthStencilState->ref = 0;
		pDepthStencilState->mask = 0;
	}

} }