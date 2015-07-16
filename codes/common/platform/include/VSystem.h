/**************************************************************************************************
 * Copyright (C) 2014. Tiny Entertainment Studio.
 * All rights reserved.
 *
 * @file    VSystem.h
 * @brief   系统类定义.
 * @author  aaronwang
 * @date    2014/2/10 0:31:47
 * @version v1.00
 **************************************************************************************************/

#ifndef __VISION_SYSTEM_H__
#define __VISION_SYSTEM_H__


#include "VSingleton.h"
#include "VPlatform.h"


namespace VPlatform
{
	class IAdapterFactory;
	class VConsole;
	class VApnManager;
	class VTextCodec;
	class VRunLoop;

	/**
	 * @class VSystem
	 * @brief 系统类.
	 * @note 该类对一些全局的单例创建和释放，为上层提供框架层和系统层统一接口.
	 */
	class VPLATFORM_API VSystem : public VSingleton<VSystem>
	{
		V_DISABLE_COPY(VSystem);

	public:
		const static uint32_t V_PLATFORM_UNKNOWN;
		const static uint32_t V_PLATFORM_IOS;
		const static uint32_t V_PLATFORM_WIN32;
		const static uint32_t V_PLATFORM_ANDROID;
		
	public:
		/**
		 * @brief Constructor for VSystem.
		 */
		VSystem();

		/**
		 * @brief Destructor for VSystem.
		 */
		~VSystem();

		/**
		 * @brief 每个程序循环调用处理.
		 * @return void  
		 */
		void process();

		/**
		 * @brief 获取操作系统适配层工厂接口对象 
		 */
		IAdapterFactory &getAdapterFactory()
		{
			return (*m_pAdapterFactory);
		}
		
		uint32_t getPlatform() const;

		VRunLoop &getMainRunLoop();

	private:
		IAdapterFactory		*m_pAdapterFactory;
		VTextCodec			*m_pTextCodec;
		VConsole			*m_pConsole;
		VApnManager			*m_pApnMgr;
		VRunLoop			*m_pMainRunLoop;
	};

	#define V_SYSTEM				(VSystem::GetInstance())
	#define V_ADAPTER_FACTORY		(V_SYSTEM.getAdapterFactory())
	#define V_MAIN_RUNLOOP			(VSystem::GetInstance().getMainRunLoop())
}


#endif	/*__VISION_SYSTEM_H__*/
