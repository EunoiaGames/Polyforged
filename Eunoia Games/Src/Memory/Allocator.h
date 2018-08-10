#pragma once

#include "../Core/Common.h"

namespace Eunoia { namespace Core {

	class Allocator
	{
	public:
		virtual void* Allocate(uint32 size) = 0;
		virtual void Free(void* pData) = 0;

		virtual void Reset() = 0;
	};

} }