/**************************************************************************************************
 * Copyright (C) 2014. Tiny Entertainment Studio.
 * All rights reserved.
 *
 * @file    VBufQueue.cpp
 * @brief   收发缓冲区.
 * @author  aaronwang
 * @date    2014/12/26 16:31:22
 * @version v1.00
 **************************************************************************************************/


#include "VBufQueue.h"



namespace VPlatform
{
	VBufQueue::VBufQueue(size_t unCapacity)
	{
		m_Buffer.reserve(unCapacity);
	}

	VBufQueue::~VBufQueue()
	{
	}

	bool VBufQueue::put(uchar_t *pData, size_t nDataLen)
	{
		if (NULL == pData || 0 == nDataLen)
			return false;

		VAutoLock locker(m_mutex);
		m_Buffer.insert(m_Buffer.end(), pData, pData+nDataLen);

		return true;
	}

	void VBufQueue::take(uchar_t *&pData, size_t &nDataLen, bool bErase /* = false */, bool bAlloc /* = true */)
	{
		VAutoLock locker(m_mutex);

		if (bAlloc)
		{
			size_t nTotalSize = size();
			if (-1 == nDataLen || nDataLen > nTotalSize)
			{
				nDataLen = nTotalSize;
			}

			pData = new uchar_t[nDataLen];
		}
		
		if (pData != NULL)
		{
			VByteBufferItr itr = m_Buffer.begin();
			memcpy(pData, (uchar_t*)&(*itr), nDataLen);
		}

		if (bErase)
		{
			VByteBufferItr itrBegin = m_Buffer.begin();
			VByteBufferItr itrLast = itrBegin + nDataLen;
			m_Buffer.erase(itrBegin, itrLast);
		}
	}

	void VBufQueue::take(VByteBuffer &rBuffer, size_t nBufSize, bool bErase /* = false */)
	{
		VAutoLock locker(m_mutex);

		size_t nTotalSize = size();
		if (-1 == nBufSize || nBufSize > nTotalSize)
		{
			nBufSize = nTotalSize;
		}

		VByteBufferItr itrBegin = m_Buffer.begin();
		VByteBufferItr itrLast = itrBegin + nBufSize;
		rBuffer.assign(itrBegin, itrLast);

		if (bErase)
		{
			m_Buffer.erase(itrBegin, itrLast);
		}
	}

	void VBufQueue::erase(size_t nDataLen)
	{
		VAutoLock locker(m_mutex);

		VByteBufferItr itrBegin = m_Buffer.begin();
		VByteBufferItr itrLast = itrBegin + nDataLen;
		m_Buffer.erase(itrBegin, itrLast);
	}
}
