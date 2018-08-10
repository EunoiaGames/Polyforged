#include "PoolAllocator.h"

namespace Eunoia { namespace Core {

	PoolAllocator::PoolAllocator(Allocator & allocator, uint32 elementSize, uint32 maxElements) :
		m_elementSize(),
		m_maxElements(maxElements)
	{
		m_pAllocator = &allocator;
		m_pData = (unsigned char*)m_pAllocator->Allocate(elementSize * maxElements);
		InitElementStack();
	}

	PoolAllocator::PoolAllocator(uint32 elementSize, uint32 maxElements) :
		m_elementSize(elementSize),
		m_maxElements(maxElements)
	{
		m_pData = (unsigned char*)malloc(elementSize * maxElements);
		InitElementStack();
	}

	PoolAllocator::~PoolAllocator()
	{
		if (m_pAllocator)
			m_pAllocator->Free(m_pData);
		else
			free(m_pData);
	}

	void * PoolAllocator::Allocate(uint32 size)
	{
		ASSERT(size == m_elementSize, "Invalid size");
		uint32 elementIndex = m_pElementStack[m_elementIndex--];
		void* pNewMem = m_pData + m_elementSize * elementIndex;
		return pNewMem;
	}

	void PoolAllocator::Free(void * pData)
	{
		m_pElementStack[++m_elementIndex] = ((unsigned char*)pData - m_pData) / m_elementSize;
	}

	void PoolAllocator::Reset()
	{
		InitElementStack();
	}

	void PoolAllocator::InitElementStack()
	{
		m_pElementStack = new uint32[m_maxElements];
		for (uint32 i = 0; i < m_maxElements; i++)
			m_pElementStack[i] = i;
		m_elementIndex = m_maxElements - 1;
	}
} }
