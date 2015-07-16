/**************************************************************************************************
 * Copyright (C) 2014. Tiny Entertainment Studio.
 * All rights reserved.
 *
 * @file    VEventParam.h
 * @brief   事件参数基类定义.
 * @author  aaronwang
 * @date    2014/2/9 23:34:03
 * @version v1.00
 **************************************************************************************************/

#ifndef __VISION_EVENT_PARAM_H__
#define __VISION_EVENT_PARAM_H__


#include "VType.h"
#include "VMacro.h"
#include "VFramework.h"


namespace VFramework
{
	/**
	 * @class VEventParam
	 * @brief 事件参数基类.
	 * @note 该类用于在发送事件时传递参数用，每个继承者均需要实现Clone接口以支持深拷贝，主要用于异步事件处理
	 * @see VEventManager::PostEvent(uint32_t, VEventParam, VINSTANCE, VINSTANCE)
	 */
	class VFRAMEWORK_API VEventParam
	{
		V_DECLARE_INTERFACE(VEventParam);

	public:
		/**
		 * @brief 克隆接口，需要继承者实现深拷贝
		 * @note 该接口主要用于异步事件发送时做一个深拷贝保存起来防止异步派发事件时，对象内部某些资源已经释放造成程序崩溃；
		 *		该深拷贝出来的对象会在VEventManager::DispatchEvent事件派发后内部释放，继承者无需关该对象释放.
		 * @return 返回一个新的VEventParam对象.
		 */
		virtual VEventParam *clone() = 0;
	};
}


#endif	/*__VISION_EVENT_PARAM_H__*/
