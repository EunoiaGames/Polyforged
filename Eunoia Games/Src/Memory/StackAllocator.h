#pragma once

#include "Allocator.h"

#define STACK_ALLOCATOR_ALLOCATION_OFFSET sizeof(Eunoia::uint32)

namespace Eunoia { namespace Core {

	class StackAllocator : public Allocator
	{
	public:
		StackAllocator(Allocator& allocator, uint32 size);
		StackAllocator(uint32 size);

		~StackAllocator();

		void* Allocate(uint32 size) override;
		void Free(void* pData) override;

		void Reset() override;
	private:
		Allocator* m_pAllocator;
		unsigned char* m_pData;
		uint32 m_size;
		uint32 m_current;
	};

} }
