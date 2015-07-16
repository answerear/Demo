/**************************************************************************************************
 * Copyright (C) 2014. Tiny Entertainment Studio.
 * All rights reserved.
 *
 * @file    VApnManager.h
 * @brief   接入点管理器类定义.
 * @author  aaronwang
 * @date    2014/2/9 21:10:40
 * @version v1.00
 **************************************************************************************************/

#ifndef __VISION_APN_MANAGER_H__
#define __VISION_APN_MANAGER_H__


#include "IApnAdapterObserver.h"
#include "VSingleton.h"
#include "VPlatform.h"


namespace VPlatform
{
	class IApnAdapter;
	class IApnObserver;

	/**
	 * @class VApnManager
	 * @brief 接入点管理类.
	 * @note 该类是单例，可以通过全局宏V_APN_MANAGER来访问该单例或者直接通过VApnManager::GetInstance()访问.
	 * @see V_APN_MANAGER
	 */
	class VPLATFORM_API VApnManager 
		: public VSingleton<VApnManager>
		, public IApnAdapterObserver
	{
		friend class VSystem;

		V_DISABLE_COPY(VApnManager);

	private:
		/**
		 * @brief Constructor for VApnManager.
		 */
		VApnManager();

		/**
		 * @brief Destructor for VApnManager.
		 */
		~VApnManager();

	public:
		/**
		 * @brief 添加接入点事件观察者.
		 * @param [in] pObserver : 观察者对象
		 * @return void
		 * @see class IApnObserver
		 */
		void addObserver(IApnObserver *pObserver);

		/**
		 * @brief 移除接入点事件观察者. 
		 * @param [in] pObserver : 观察者对象
		 * @return void
		 * @see class IApnObserver
		 */
		void removeObserver(IApnObserver *pObserver);

		/**
		 * @brief 获取当前接入点类型.
		 * @return 返回当前接入点类型
		 * @see EApnType
		 */
		EApnType getApnType() const;

		/**
		 * @brief 获取当前接入点字符串描述.
		 * @return 返回当前接入点字符串  
		 */
		VString getApnTypeString() const;

		/**
		 * @brief 获取当前运营商类型.
		 * @return 返回当前运营商类型.
		 * @see ECarrier
		 */
		ECarrier getCarrier() const;

		/**
		 * @brief 获取当前运营商字符串描述.
		 * @return 返回当前运营商字符串描述.  
		 */
		VString getCarrierString() const;

		/**
		 * @brief 当前接入点是否可达.
		 * @return 可达返回true，否则返回false.  
		 */
		bool isReachable() const;

	protected:	// from IApnAdapterObserver
		virtual void onApnChanged(EApnType eLastApn, EApnType eCurrentApn);
		virtual void onPingResult(bool bReachable);
	};

	#define V_APN_MANAGER	(VApnManager::GetInstance())
}


#endif	/*__VISION_APN_MANAGER_H__*/
