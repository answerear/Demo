/**************************************************************************************************
 * Copyright (C) 2014. Tiny Entertainment Studio.
 * All rights reserved.
 *
 * @file    VBufQueue.h
 * @brief   收发缓冲区.
 * @author  aaronwang
 * @date    2014/12/26 15:31:22
 * @version v1.00
 **************************************************************************************************/

#ifndef __VISION_BUF_QUEUE_H__
#define __VISION_BUF_QUEUE_H__


#include "VType.h"
#include "VMacro.h"
#include "VPlatform.h"
#include <vector>
#include <mutex>


namespace VPlatform
{
	typedef std::vector<uchar_t> VByteBuffer;
	typedef VByteBuffer::iterator VByteBufferItr;


	class VPLATFORM_API VBufQueue
	{
	public:
		/**
		 * @brief Constructor
		 * @param [in] nCapacity : 初始化缓冲区容量，后续不够会自动增长
		 */
		VBufQueue(size_t nCapacity);

		/**
		 * @brief Destructor
		 */
		virtual ~VBufQueue();

		/**
		 * @brief 放入数据，自动放入缓冲区末尾
		 * @param [in] pData : 数据首地址
		 * @param [in] nDataLen : 数据长度
		 */
		bool put(uchar_t *pData, size_t nDataLen);
		
		/**
		 * @brief 从缓冲区首开始取数据
		 * @param [in][out] pData : 如果bAlloc是true，则返回新分配内存数据的首地址，否则是传入的地址
		 * @param [in][out] nDataLen : 如果bAlloc是true，传进去要获取数据的长度，-1为整个缓冲区长度，返回的是返回数据长度，否则是pData的缓冲区的长度
		 * @param [in] bErase : 删除相应数据，默认是不删除
		 * @param [in] bAlloc : 是否内部分配空间，默认内部分配内存
		 */
		void take(uchar_t *&pData, size_t &nDataLen, bool bErase = false, bool bAlloc = true);
		
		/**
		 * @brief 从缓冲区首开始取数据
		 * @param [out] rBuffer : 缓冲区数据
		 * @param [in] nBufSize : 获取缓冲区数据大小
		 * @param [in] bErase : 删除相应数据，默认是不删除
		 */
		void take(VByteBuffer &rBuffer, size_t nBufSize, bool bErase = false);

		/**
		 * @brief 删除缓冲区首开始的指定长度的数据
		 * @param [in] nDataLen : 要删除数据长度
		 */
		void erase(size_t nDataLen);

		/**
		 * @brief 清除整个缓冲区
		 */
		void clear()			{ m_Buffer.clear(); }

		/**
		 * @brief 获取当前缓冲区长度
		 */
		size_t size() const	{ return m_Buffer.size(); }

	protected:
		typedef std::unique_lock<std::recursive_mutex> VAutoLock;

		VByteBuffer	m_Buffer;
		std::recursive_mutex	m_mutex;
	};
}


#endif	/*__VISION_BUF_QUEUE_H__*/
