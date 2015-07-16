
#include "VEventParamBuffer.h"


namespace VFramework
{
	VEventParamBuffer::VEventParamBuffer()
		: m_pBuffer(NULL)
		, m_nBufSize(0)
	{
	}

	VEventParamBuffer::VEventParamBuffer(char *pBuffer, int32_t nBufSize)
		: m_pBuffer(NULL)
		, m_nBufSize(0)
	{
		if (nBufSize > 0)
		{
			m_pBuffer = new char[nBufSize];
			memcpy(m_pBuffer, pBuffer, nBufSize);
			m_nBufSize = nBufSize;
		}
	}

	VEventParam *VEventParamBuffer::clone()
	{
		VEventParamBuffer *pCopy = new VEventParamBuffer(m_pBuffer, m_nBufSize);
		return pCopy;
	}
}

