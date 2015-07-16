/**************************************************************************************************
 * Copyright (C) 2014. Tiny Entertainment Studio.
 * All rights reserved.
 *
 * @file    IApnAdapter.h
 * @brief   操作系统相关接入点接口类定义.
 * @author  aaronwang
 * @date    2014/2/8 11:05:19
 * @version v1.00
 **************************************************************************************************/

#ifndef __VISION_APN_ADPATER_H__
#define __VISION_APN_ADPATER_H__


#include "VApnType.h"


namespace VPlatform
{
	class IApnAdapterObserver;

	/**
	 * @class IApnAdapter
	 * @brief 接入点相关操作接口类.
	 * @note 相关操作系统平台需要继承该接口类实现具体平台相关功能
	 */
	class IApnAdapter
	{
		V_DECLARE_INTERFACE(IApnAdapter);

	public:
		/**
		 * @brief 设置接入点适配层观察者对象.
		 * @param [in] pObserver : 观察者对象
		 * @return void  
		 */
		virtual void setObserver(IApnAdapterObserver *pObserver) = 0;

		/**
		 * @brief 获取接入点类型.
		 * @return 返回接入点类型枚举值
		 * @see EApnType
		 */
		virtual EApnType getApnType() const = 0;

		/**
		 * @brief 获取运营商类型.
		 * @return 返回运营商类型枚举值
		 * @see ECarrier
		 */
		virtual ECarrier getCarrier() const = 0;

		/**
		 * @brief 判断当前接入点是否可达指定域名主机.
		 * @param [in] strHost : 远程主机域名或者ip
		 * @return 调用成功返回true，失败返回false. 可达通过IApnAdapterObserver的OnPingResult回调返回
		 * @see IApnAdapterObserver::OnPingResult(bool bReachable)
		 */
		virtual bool pingRoutes(const VString &strHost) = 0;

		/**
		 * @brief 取消当前Ping程序执行接口.
		 * @return void
		 * @see IApnAdapterObserver::OnPingResult(bool bReachable)
		 */
		virtual void cancelPingRoutes() = 0;
	};
}


#endif	/*__VISION_APN_ADPATER_H__*/
