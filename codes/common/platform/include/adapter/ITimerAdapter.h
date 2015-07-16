/**************************************************************************************************
 * Copyright (C) 2014. Tiny Entertainment Studio.
 * All rights reserved.
 *
 * @file    ITimerAdapter.h
 * @brief   操作系统平台相关的定时器接口类定义.
 * @author  aaronwang
 * @date    2014/2/9 21:01:17
 * @version v1.00
 **************************************************************************************************/

#ifndef __VISION_LOGGER_TIMER_ADAPTER_H__
#define __VISION_LOGGER_TIMER_ADAPTER_H__


#include "VType.h"
#include "VMacro.h"


namespace VPlatform
{
	class ITimerObserver;

	const uint32_t V_INVALID_TIMER_ID = 0;		/**< 无效定时器ID */

	/**
	 * @class ITimerAdapter
	 * @brief 操作系统平台相关的定时器接口类.
	 * @note 相关操作系统平台需要继承该接口类实现具体平台相关功能.
	 */
	class ITimerAdapter
	{
		V_DECLARE_INTERFACE(ITimerAdapter);

	public:
		/**
		 * @brief 启动定时器，定时器是循环定时.
		 * @param [in] unInterval : 定时器时间间隔毫秒数
		 * @return 返回定时器对应ID.  
		 */
		virtual uint32_t start(uint32_t unInterval) = 0;

		/**
		 * @brief 关闭定时器.
		 * @return void  
		 */
		virtual void stop() = 0;

		/**
		 * @brief 设置定时器回调观察者对象.
		 * @param [in] pObserver : 观察者对象
		 * @return void
		 * @see class ITimerObserver
		 */
		virtual void setObserver(ITimerObserver *pObserver) = 0;

		/**
		 * @brief 获取定时器对象对应的定时器ID 
		 * @note 当前定时器正在计时，则返回合法的对应的定时器ID，否则返回无效定时器ID.
		 * @return 返回定时器ID  
		 */
		virtual uint32_t getTimerID() const = 0;
	};
}



#endif	/*__VISION_LOGGER_TIMER_ADAPTER_H__*/
