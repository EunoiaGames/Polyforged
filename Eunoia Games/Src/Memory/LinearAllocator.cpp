#include "LinearAllocator.h"
#include <cstring>

namespace Eunoia { namespace Core {

	LinearAllocator::LinearAllocator(Allocator & allocator, uint32 size) :
		m_size(size)
	{
		m_pData = (unsigned char*)allocator.Allocate(size);
		m_pCustomAllocator = &allocator;
	}

	LinearAllocator::LinearAllocator(uint32 size) :
		m_size(size)
	{
		m_pData = (unsigned char*)malloc(size);
	}

	LinearAllocator::~LinearAllocator()
	{
		if (m_pCustomAllocator)
			m_pCustomAllocator->Free(m_pData);
		else
			free(m_pData);
	}

	void * LinearAllocator::Allocate(uint32 size)
	{
		void* pNewMem = m_pData + m_offset;
		m_offset += size;
		return pNewMem;
	}

	void LinearAllocator::Free(void * pData)
	{
		//Doesn't make sense to free memory with this allocator
	}

	void LinearAllocator::Reset()
	{
		memset(m_pData, 0, m_size);
		m_offset = 0;
	}

} }
