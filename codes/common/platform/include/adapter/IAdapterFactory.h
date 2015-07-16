/**************************************************************************************************
 * Copyright (C) 2014. Tiny Entertainment Studio.
 * All rights reserved.
 *
 * @file    IAdapterFactory.h
 * @brief   操作系统适配层工厂接口类定义.
 * @author  aaronwang
 * @date    2014/2/8 10:55:41
 * @version v1.00
 **************************************************************************************************/

#ifndef __VISION_ADAPTER_FACTORY_H__
#define __VISION_ADAPTER_FACTORY_H__


#include "VType.h"
#include "VMacro.h"


namespace VPlatform
{
	class IConsoleAdapter;
	class ITimerAdapter;
	class IDirAdapter;
	class IApnAdapter;
	class IAudioAdapter;
	class IDeviceInfoAdapter;

	enum EPlatform
	{
		E_PLATFORM_UNKNOWN = 0,
		E_PLATFORM_WIN32 = 1,
		E_PLATFORM_IOS,
		E_PLATFORM_ANDROID
	};

	/**
	 * @class IAdapterFactory
	 * @brief 操作系统适配层工厂接口.
	 * @note 不同操作系统平台需要实现继承该类实现具体平台接口
	 */
	class IAdapterFactory
	{
		V_DECLARE_INTERFACE(IAdapterFactory);

	public:
		/**
		 * @brief 创建操作系统相关的控制台对象.
		 * @return 返回控制台对象，需要用户调用delete释放资源
		 */
		virtual IConsoleAdapter *createConsoleAdapter() = 0;

		/**
		 * @brief 创建操作系统相关的定时器对象.
		 * @return 返回定时器对象，需要用户调用delete释放资源
		 */
		virtual ITimerAdapter *createTimerAdapter() = 0;

		/**
		 * @brief 创建操作系统相关的搜索路径对象.
		 * @return 返回搜索路径对象，需要用户调用delete释放资源
		 */
		virtual IDirAdapter *createDirAdapter() = 0;

		/**
		 * @brief 创建操作系统相关的接入点对象.
		 * @return 返回接入点操作对象，需要用户调用delete释放资源
		 */
		virtual IApnAdapter *createApnAdapter() = 0;
		
		/**
		 * @brief 创建操作系统相关的设备信息对象.
		 * @return 返回设备信息操作对象，需要用户调用delete释放资源
		 */
		virtual IDeviceInfoAdapter *createDeviceInfoAdapter() = 0;

		/**
		 * @brief 获取当前平台类型.
		 * @return 返回当前平台类型
		 */
		virtual EPlatform getPlatform() = 0;
	};

	/**
	 * @brief 创建操作系统相关的适配层工厂对象.
	 * @note 不同操作系统平台需要实现该接口以返回操作系统适配层工厂对象 
	 * @return 返回适配层工厂对象，需要用户调用delete释放资源
	 */
	IAdapterFactory *createAdapterFactory();
}


#endif	/*__VISION_ADAPTER_FACTORY_H__*/
