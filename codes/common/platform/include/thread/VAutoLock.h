/**************************************************************************************************
 * Copyright (C) 2014. Tiny Entertainment Studio.
 * All rights reserved.
 *
 * @file    VAutoLock.h
 * @brief   智能锁类定义.
 * @author  aaronwang
 * @date    2014/2/9 21:24:07
 * @version v1.00
 **************************************************************************************************/

#ifndef __VISION_AUTO_LOCK_H__
#define __VISION_AUTO_LOCK_H__


#include "VType.h"
#include "VMacro.h"
#include "VPlatform.h"


namespace VPlatform
{
	class VMutex;

	/**
	 * @class VAutoLock
	 * @brief 智能锁类.
	 * @note 智能的锁定临界区资源，在该对象析构时自动解锁临界区
	 */
	class VPLATFORM_API VAutoLock
	{
		V_DISABLE_COPY(VAutoLock);

	public:
		/**
		 * @brief Constructor for VAutoLock.
		 * @note 可以在构造时自动锁定临界资源.
		 * @param [in] pMutex : 互斥量对象
		 * @param [in] bInitLock : 构造时自动锁定临界区资源，默认是自动上锁.
		 */
		VAutoLock(VMutex *pMutex, bool bInitLock = true);

		/**
		 * @brief Destructor for VAutoLock.
		 */
		virtual ~VAutoLock();

		/**
		 * @brief 锁定临界区.
		 * @return void  
		 */
		void lock();

		/**
		 * @brief 解锁临界区.
		 * @return void  
		 */
		void unlock();

		/**
		 * @brief 获取当前智能锁是否上锁.
		 * @return 已经锁定临界区返回true，否则返回false.  
		 */
		bool isLocked() const	{ return m_bLocked; }

	protected:
		VMutex	*m_pMutex;	/**< 互斥量对象 */
		bool	m_bLocked;	/**< 锁定标记 */
	};
}

#endif	/*__VISION_AUTO_LOCK_H__*/
