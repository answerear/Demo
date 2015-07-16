/**************************************************************************************************
 * Copyright (C) 2014. Tiny Entertainment Studio.
 * All rights reserved.
 *
 * @file    IApnAdapterObserver.h
 * @brief   适配层接入点事件观察者接口类定义.
 * @author  aaronwang
 * @date    2014/2/9 20:37:13
 * @version v1.00
 **************************************************************************************************/

#ifndef __VISION_APN_ADPATER_OBSERVER_H__
#define __VISION_APN_ADPATER_OBSERVER_H__


#include "VApnType.h"
#include "VPlatform.h"


namespace VPlatform
{
	/**
	 * @class IApnAdapterObserver
	 * @brief 适配层接入点事件观察者接口类.
	 * @note 继承该类实现对平台适配层接入点事件的监听.
	 */
	class VPLATFORM_API IApnAdapterObserver
	{
		V_DECLARE_INTERFACE(IApnAdapterObserver);

	public:
		/**
		 * @brief 接入点切换事件通知.
		 * @param [in] eLastApn : 切换前接入点类型
		 * @param [in] eCurrentApn : 切换后的接入点类型
		 * @return void
		 * @see EApnType
		 */
		virtual void onApnChanged(EApnType eLastApn, EApnType eCurrentApn) = 0;

		/**
		 * @brief 接入点是否可达的ping程序结果通知.
		 * @param [in] bReachable : 是否可达标记
		 * @return void 
		 */
		virtual void onPingResult(bool bReachable) = 0;
	};
}


#endif	/*__VISION_APN_ADPATER_OBSERVER_H__*/
