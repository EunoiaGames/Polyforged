#pragma once

#include "../../Core/Common.h"

namespace Eunoia { namespace Rendering {

	enum DepthComparison
	{
		DEPTH_COMPARISON_LESS,
		DEPTH_COMPARISON_GREATER,
		DEPTH_COMPARISON_LESS_EQUAL,
		DEPTH_COMPARISON_GREATER_EQUAL,
		DEPTH_COMPARISON_EQUAL,
		DEPTH_COMPARISON_NOT_EQUAL,
		DEPTH_COMPARISON_NEVER,
		DEPTH_COMPARISON_ALWAYS,

		NUM_DEPTH_COMPARISONS
	};

	enum StencilOperation
	{
		STENCIL_OPERATION_KEEP,
		STENCIL_OPERATION_ZERO,
		STENCIL_OPERATION_REPLACE,
		STENCIL_OPERATION_INCR_CLAMP,
		STENCIL_OPERATION_DECR_CLAMP,
		STENCIL_OPERATION_INVERT,
		STENCIL_OPERATION_INCR,
		STENCIL_OPERATION_DECR,

		NUM_STENCIL_OPERATIONS
	};

	enum StencilComparison
	{
		STENCIL_COMPARISON_NEVER,
		STENCIL_COMPARISON_LESS,
		STENCIL_COMPARISON_LESS_EQUAL,
		STENCIL_COMPARISON_GREATER,
		STENCIL_COMPARISON_GREATER_EQUAL,
		STENCIL_COMPARISON_EQUAL,
		STENCIL_COMPARISON_NOT_EQUAL,
		STENCIL_COMPARISON_ALWAYS,

		NUM_STENCIL_COMPARISONS
	};

	struct StencilOperationFace
	{
		StencilOperationFace(StencilOperation stencilFail, StencilOperation depthFail, StencilOperation stencilPass, StencilComparison comparison) :
			stencilFail(stencilFail),
			depthFail(depthFail),
			stencilPass(stencilPass),
			comparison(comparison)
		{}

		StencilOperationFace() {}

		StencilOperation	stencilFail;
		StencilOperation	depthFail;
		StencilOperation	stencilPass;
		StencilComparison	comparison;
	};

	struct DepthStencilState
	{
		DepthStencilState(bool depthEnabled, bool depthWrite, DepthComparison depthComparison, bool stencilEnabled, const StencilOperationFace& frontFace,
			const StencilOperationFace& backFace, uint32 ref, uint32 mask) :
			depthEnabled(depthEnabled),
			depthWrite(depthWrite),
			depthComparison(depthComparison),
			stencilEnabled(stencilEnabled),
			frontFace(frontFace),
			backFace(backFace),
			ref(ref),
			mask(mask)
		{}

		DepthStencilState() {}

		bool depthEnabled;
		bool depthWrite;
		DepthComparison depthComparison;

		bool stencilEnabled;
		StencilOperationFace frontFace;
		StencilOperationFace backFace;
		uint32 ref;
		uint32 mask;
	};

} }
