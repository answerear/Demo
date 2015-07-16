/**************************************************************************************************
 * Copyright (C) 2014. Tiny Entertainment Studio.
 * All rights reserved.
 *
 * @file    IApnObserver.h
 * @brief   接入点观察者接口类定义.
 * @author  aaronwang
 * @date    2014/2/9 21:06:50
 * @version v1.00
 **************************************************************************************************/

#ifndef __VISION_THREAD_OBSERVER_H__
#define __VISION_THREAD_OBSERVER_H__


#include "VApnType.h"
#include "VPlatform.h"


namespace VPlatform
{
	/**
	 * @class IApnObserver
	 * @brief 接入点观察者接口类.
	 * @note 继承该类实现对接入点事件的监听.
	 */
	class VPLATFORM_API IApnObserver
	{
		V_DECLARE_INTERFACE(IApnObserver);

	public:
		/**
		 * @brief 接入点切换事件通知.
		 * @param [in] eLastApn : 前一个接入点类型
		 * @param [in] eCurrentApn : 当前接入点类型
		 * @return void  
		 */
		virtual void onNetworkChanged(EApnType eLastApn, EApnType eCurrentApn) = 0;
	};
}


#endif	/*__VISION_THREAD_OBSERVER_H__*/
