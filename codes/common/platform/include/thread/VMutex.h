/**************************************************************************************************
 * Copyright (C) 2014. Tiny Entertainment Studio.
 * All rights reserved.
 *
 * @file    VMutex.h
 * @brief   互斥量类定义.
 * @author  aaronwang
 * @date    2014/2/10 0:05:48
 * @version v1.00
 **************************************************************************************************/

#ifndef __VISION_MUTEX_H__
#define __VISION_MUTEX_H__


#include "VType.h"
#include "VMacro.h"
#include "VPlatform.h"
#include <pthread.h>


namespace VPlatform
{
	/**
	 * @class VMutex
	 * @brief 互斥量类.
	 * @note pthread_mutex简单封装.
	 */
	class VPLATFORM_API VMutex
	{
		friend class VWaitCondition;

		V_DISABLE_COPY(VMutex);

	public:
		/**
		 * @brief 递归模式
		 */
		enum RecursionMode
		{
			NonRecursive = 0,	/**< 不递归 */
			Recursive,			/**< 递归 */
		};

		/**
		 * @brief Constructor for VMutex.
		 * @param [in] eMode : 是否递归锁，默认不递归.
		 */
		VMutex(RecursionMode eMode = NonRecursive);

		/**
		 * @brief Destructor for VMutex.
		 */
		virtual ~VMutex();

		/**
		 * @brief 是否递归锁  
		 */
		bool isRecursive() const;

		/**
		 * @brief 加锁.
		 * @return void  
		 */
		void lock();

		/**
		 * @brief 尝试加锁.
		 * @param [in] unTimeout : 尝试时间.
		 * @return 调用成功返回true，否则返回false.  
		 */
		bool tryLock(uint32_t unTimeout = 0);

		/**
		 * @brief 解锁  
		 */
		void unlock();

	protected:
		RecursionMode		m_eMode;	/**< 递归模式 */
		pthread_mutex_t		m_mutex;	/**< pthread互斥量对象 */
		pthread_mutexattr_t	m_attr;		/**< pthread互斥量属性对象 */
	};
}


#endif	/*__VISION_MUTEX_H__*/
