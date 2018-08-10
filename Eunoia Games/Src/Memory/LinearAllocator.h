#pragma once

#include "Allocator.h"

namespace Eunoia  { namespace Core {

	class LinearAllocator : public Allocator
	{
	public:
		LinearAllocator(Allocator& allocator, uint32 size);
		LinearAllocator(uint32 size);

		~LinearAllocator();

		void* Allocate(uint32 size) override;
		void Free(void* pData) override;

		void Reset() override;
	private:

	private:
		unsigned char* m_pData;
		Allocator* m_pCustomAllocator;
		uint32 m_size;
		uint32 m_offset;
	};

} }
