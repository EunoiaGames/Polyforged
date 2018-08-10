#include "StackAllocator.h"
#include <cstring>

namespace Eunoia { namespace Core {

	StackAllocator::StackAllocator(Allocator & allocator, uint32 size) :
		m_size(size)
	{
		m_pData = (unsigned char*)allocator.Allocate(size);
		m_pAllocator = &allocator;
	}

	StackAllocator::StackAllocator(uint32 size) :
		m_size(size)
	{
		m_pData = (unsigned char*)malloc(size);
	}

	StackAllocator::~StackAllocator()
	{
		if (m_pAllocator)
			m_pAllocator->Free(m_pData);
		else
			free(m_pData);
	}

	void * StackAllocator::Allocate(uint32 size)
	{
		unsigned char* pNewMem = m_pData + size + STACK_ALLOCATOR_ALLOCATION_OFFSET;
		memcpy(pNewMem, &m_current, sizeof(uint32));
		m_current += size + STACK_ALLOCATOR_ALLOCATION_OFFSET;
		pNewMem += sizeof(uint32);
		return pNewMem;
	}

	void StackAllocator::Free(void * pData)
	{
		uint32 offset = *(uint32*)((unsigned char*)pData - sizeof(uint32));
		m_current = offset;
	}

	void StackAllocator::Reset()
	{
		memset(m_pData, 0, m_size);
		m_current = 0;
	}

} }
