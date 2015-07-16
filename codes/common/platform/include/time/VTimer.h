/**************************************************************************************************
 * Copyright (C) 2014. Tiny Entertainment Studio.
 * All rights reserved.
 *
 * @file    VTimer.h
 * @brief   定时器类定义.
 * @author  aaronwang
 * @date    2014/2/10 0:59:58
 * @version v1.00
 **************************************************************************************************/

#ifndef __VISION_TIMER_H__
#define __VISION_TIMER_H__


#include "VType.h"
#include "VMacro.h"
#include "VPlatform.h"


namespace VPlatform
{
	class ITimerObserver;
	class ITimerAdapter;

	/**
	 * @class VTimer
	 * @brief 定时器类.
	 * @note 该类是操作系统平台无关定时器，对平台适配层的进一步封装.
	 */
	class VPLATFORM_API VTimer
	{
		V_DISABLE_COPY(VTimer);

	public:
		/**
		 * @brief Constructor for VTimer.
		 */
		VTimer();

		/**
		 * @brief Destructor for VTimer.
		 */
		~VTimer();

		/**
		 * @brief 启动定时器.
		 * @param [in] unInterval : 定时毫秒数
		 * @return 定时器ID  
		 */
		uint32_t start(uint32_t unInterval);

		/**
		 * @brief 关闭定时器.
		 * @return void  
		 */
		void stop();

		/**
		 * @brief 设置定时器观察者对象.
		 * @param [in] pObserver : 观察者对象
		 * @return void  
		 */
		void setObserver(ITimerObserver *pObserver);

		/**
		 * @brief 获取定时器ID.
		 * @return 返回定时器ID  
		 */
		uint32_t getTimerID() const;

	protected:
		ITimerAdapter *m_pAdapter;
	};
}


#endif	/*__VISION_TIMER_H__*/
