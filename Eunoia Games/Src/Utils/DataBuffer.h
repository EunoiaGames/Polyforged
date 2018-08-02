#pragma once

namespace Eunoia {

	class DataBuffer
	{
	public:
		DataBuffer(unsigned int size);
		DataBuffer(void* pData);
		DataBuffer();

		void DeleteData() const;
		void SetNewData(void* pData);
		void* GetData() const;

		void Write(const void* pData, unsigned int offset, unsigned int size);
		void Read(void* pData, unsigned int offset, unsigned int size);
	private:
		void* m_pData;
	};

}
