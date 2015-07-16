/**************************************************************************************************
 * Copyright (C) 2014. Tiny Entertainment Studio.
 * All rights reserved.
 *
 * @file    VWaitCondition.h
 * @brief   条件变量类定义.
 * @author  aaronwang
 * @date    2014/2/10 1:03:30
 * @version v1.00
 **************************************************************************************************/

#ifndef __VISION_WAIT_CONDITION_H__
#define __VISION_WAIT_CONDITION_H__


#include "VType.h"
#include "VMacro.h"
#include "VPlatform.h"
#include <pthread.h>


namespace VPlatform
{
	class VMutex;

	/**
	 * @class VWaitCondition
	 * @brief 条件变量类.
	 * @note 该类是对pthread_cond简单封装.
	 */
	class VPLATFORM_API VWaitCondition
	{
		V_DISABLE_COPY(VWaitCondition);

	public:
		VWaitCondition();
		virtual ~VWaitCondition();

		bool wait(VMutex *pMutex, uint32_t unTimeout = -1);
		void wakeAll();
		void wakeOne();

	protected:
		pthread_cond_t	m_cond;
	};
}


#endif	/*__VISION_WAIT_CONDITION_H__*/
