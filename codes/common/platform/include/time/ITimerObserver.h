/**************************************************************************************************
 * Copyright (C) 2014. Tiny Entertainment Studio.
 * All rights reserved.
 *
 * @file    ITimerObserver.h
 * @brief   定时器观察者接口类定义.
 * @author  aaronwang
 * @date    2014/2/9 21:08:57
 * @version v1.00
 **************************************************************************************************/

#ifndef __VISION_TIMER_OBSERVER_H__
#define	__VISION_TIMER_OBSERVER_H__


#include "VType.h"
#include "VMacro.h"
#include "VPlatform.h"


namespace VPlatform
{
	/**
	 * @class ITimerObserver
	 * @brief 定时器观察者接口类.
	 * @note 继承该类实现接口以对定时器事件监听.
	 */
	class VPLATFORM_API ITimerObserver
	{
		V_DECLARE_INTERFACE(ITimerObserver);

	public:
		/**
		 * @brief 定时器时间到达回调.
		 * @param [in] unTimerID : 到达时间的定时器ID
		 * @return void
		 */
		virtual void onTimer(uint32_t unTimerID) = 0;
	};
}


#endif	/*__VISION_TIMER_OBSERVER_H__*/
