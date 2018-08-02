#include "DataBuffer.h"
#include <cstdlib>
#include <cstring>

namespace Eunoia {

	DataBuffer::DataBuffer(unsigned int size)
	{
		m_pData = malloc(size);
	}

	DataBuffer::DataBuffer(void * pData)
	{
		m_pData = pData;
	}

	DataBuffer::DataBuffer()
	{
		m_pData = NULL;
	}

	void DataBuffer::DeleteData() const
	{
		if (m_pData)
		{
			delete m_pData;
		}
	}

	void DataBuffer::SetNewData(void * pData)
	{
		m_pData = pData;
	}

	void * DataBuffer::GetData() const
	{
		return m_pData;
	}

	void DataBuffer::Write(const void* pData, unsigned int offset, unsigned int size)
	{
		memcpy((unsigned char*)m_pData + offset, pData, size);
	}

	void DataBuffer::Read(void * pData, unsigned int offset, unsigned int size)
	{
		memcpy(pData, (unsigned char*)m_pData + offset, size);
	}
}
