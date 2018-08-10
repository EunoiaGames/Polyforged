#pragma once

#include "Allocator.h"
#include <vector>

namespace Eunoia { namespace Core {

	class PoolAllocator : public Allocator
	{
	public:
		PoolAllocator(Allocator& allocator, uint32 elementSize, uint32 maxElements);
		PoolAllocator(uint32 elementSize, uint32 maxElements);
		~PoolAllocator();

		void* Allocate(uint32 size) override;
		void Free(void* pData) override;

		void Reset() override;
	private:
		void InitElementStack();
	private:
		Allocator* m_pAllocator;
		unsigned char* m_pData;

		uint32 m_elementSize;
		uint32 m_maxElements;

		uint32* m_pElementStack;
		uint32 m_elementIndex;
	};

} }
