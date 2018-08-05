#pragma once

#include "BlendState.h"
#include "DepthStencilState.h"


namespace Eunoia { namespace Rendering {

	void create_blend_state_no_blend(BlendState* pBlendState);
	void create_blend_state_additive_blending(BlendState* pBlendState);

	void create_depth_stencil_state_no_depth_stencil(DepthStencilState* pDepthStencilState);
	void create_depth_stencil_state_no_stencil(DepthStencilState* pDepthStencilState);

} }

