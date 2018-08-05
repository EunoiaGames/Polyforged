#pragma once

namespace Eunoia { namespace Rendering {

	enum BlendOperation
	{
		BLEND_OPERATION_ADD,
		BLEND_OPERATION_SUB,
		BLEND_OPERATION_REV_SUB,
		BLEND_OPERATION_MIN,
		BLEND_OPERATION_MAX,

		NUM_BLEND_EQUATIONS
	};

	enum BlendFunction
	{
		BLEND_FUNCTION_ZERO,
		BLEND_FUNCTION_ONE,
		BLEND_FUNCTION_SRC_COLOR,
		BLEND_FUNCTION_INV_SOURCE_COLOR,
		BLEND_FUNCTION_DEST_COLOR,
		BLEND_FUNCTION_INV_DEST_COLOR,
		BLEND_FUNCTION_SRC_ALPHA,
		BLEND_FUNCTION_SRC_INV_ALPHA,
		BLEND_FUNCTION_DEST_ALPHA,
		BLEND_FUNCTION_DEST_INV_ALPHA,
	};

	struct BlendState
	{
		BlendState(bool enabled, BlendOperation operation, BlendFunction srcFunction, BlendFunction destFunction) :
			enabled(enabled),
			operation(operation),
			srcFunction(srcFunction),
			destFunction(destFunction)
		{}

		BlendState() {}

		bool enabled;
		BlendOperation operation;
		BlendFunction srcFunction;
		BlendFunction destFunction;
	};

} };