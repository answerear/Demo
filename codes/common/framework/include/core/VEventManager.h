/**************************************************************************************************
 * Copyright (C) 2014. Tiny Entertainment Studio.
 * All rights reserved.
 *
 * @file    VEventManager.h
 * @brief   事件管理类定义.
 * @author  aaronwang
 * @date    2014/2/9 23:18:19
 * @version v1.00
 **************************************************************************************************/

#ifndef __VISION_EVENT_MANAGER_H__
#define __VISION_EVENT_MANAGER_H__


#include "VSingleton.h"
#include "VEventMacro.h"
#include "VFramework.h"
#include <vector>
#include <list>
#include <map>
#include <set>


namespace VPlatform
{
	class VMutex;
}


namespace VFramework
{
	class VEventHandler;
	class VEventParam;

	const int32_t V_MAX_EVENT_QUEUE = 2;	/**< 最大事件队列数 */

	/**
	 * @class VEventManager
	 * @brief 事件管理类.
	 * @note 该类是个单例，负责事件的接收和中转派发，可通过全局宏V_EVENT_MANAGER或者VEventManager::GetInstance()来访问.
	 */
	class VFRAMEWORK_API VEventManager : public VSingleton<VEventManager>
	{
		friend class VEventHandler;

		V_DISABLE_COPY(VEventManager);

		/** 事件项 */
		struct VEventItem
		{
			VEventItem(uint32_t unEventID, VEventParam *pEventParam, VINSTANCE receiver, VINSTANCE sender, int32_t nType)
				: m_unEventID(unEventID)
				, m_pEventParam(pEventParam)
				, m_Receiver(receiver)
				, m_Sender(sender)
				, m_nType(nType)
			{}

			uint32_t		m_unEventID;		/**< 事件ID */
			VEventParam		*m_pEventParam;		/**< 事件参数对象 */
			VINSTANCE		m_Receiver;			/**< 事件接收者实例ID */
			VINSTANCE		m_Sender;			/**< 事件发送者实例ID */
			int32_t			m_nType;			/**< 事件对象类型 */
		};

	public:
		/**
		 * @brief Constructor for VEventManager.
		 */
		VEventManager(uint32_t unMaxEvents);

		/**
		 * @brief Destructor for VEventManager.
		 */
		virtual ~VEventManager();

		/**
		 * @brief 发送同步事件 
		 * @note 该接口是同步接口，调用该接口会立刻通知事件接收方，待接收方处理完才返回.
		 * @param [in] unEventID : 事件ID，自定义事件请在QG_EV_USER后扩展
		 * @param [in] pEventParam : 事件参数，继承VEventParam类实现不同事件ID对应的不同参数
		 * @param [in] receiver : 事件接收者实例ID，QG_BROADCAST_INSTANCE_ID为广播对象，凡是关注该事件的对象都能收到通知
		 * @param [in] sender : 事件发送者实例ID
		 * @return 当接收者是广播对象时，则函数调用成功返回true，否则返回false；
		 *		当接收者是固定对象时，则函数返回接收对象处理函数的返回值.
		 */
		bool sendEvent(uint32_t unEventID, VEventParam *pEventParam, const VINSTANCE &receiver, const VINSTANCE &sender, int32_t nType);

		/**
		 * @brief 发送异步事件 
		 * @note 该接口是异步接口，调用该接口，事件会放入事件处理队列，直到程序循环到事件派发时才会派发给相应对象处理.
		 * @param [in] unEventID : 事件ID，自定义事件请在QG_EV_USER后扩展
		 * @param [in] pEventParam : 事件参数，继承VEventParam类实现不同事件ID对应的不同参数
		 * @param [in] receiver : 事件接收者实例ID，QG_BROADCAST_INSTANCE_ID为广播事件，凡是关注该事件的对象都能收到通知
		 * @param [in] sender : 事件发送者实例ID
		 * @return 函数调用成功返回true，返回false时，事件不会触发.  
		 */
		bool postEvent(uint32_t unEventID, VEventParam *pEventParam, const VINSTANCE &receiver, const VINSTANCE &sender, int32_t nType);
	
		/**
		 * @brief 无指定对象的发送同步事件，注册了关注该事件的对象可以收到事件
		 * @param [in] unEventID : 事件ID，自定义事件请在EV_USER后扩展
		 * @param [in] pEventParam : 事件参数，继承VEventParam类实现不同事件ID对应的不同参数
		 * @param [in] sender : 事件发送者实例ID
		 * @return 函数调用成功返回true，返回false时，没有对象关注该事件. 
		 * @note 该接口是同步接口，调用该接口会立刻通知关注该事件的接收方，待接收方处理完才返回.
		 *		事件派发对象的顺序是随机的.
		 * @see VEventManager::RegisterEvent
		 */
		bool sendEvent(uint32_t unEventID, VEventParam *pEventParam, const VINSTANCE &sender);

		/**
		 * @brief 无指定对象的发送异步事件，注册了关注该事件的对象可以收到事件
		 * @param [in] unEventID : 事件ID，自定义事件请在EV_USER后扩展
		 * @param [in] pEventParam : 事件参数，继承VEventParam类实现不同事件ID对应的不同参数
		 * @param [in] sender : 事件发送者实例ID
		 * @return 函数调用成功返回true，返回false时，没有对象关注该事件. 
		 * @note 该接口是异步接口，调用该接口，事件会放入事件处理队列，直到程序循环到事件派发时才会派发给相应对象处理.
		 *		事件派发对象的顺序是随机的.
		 * @see VEventManager::RegisterEvent
		 */
		bool postEvent(uint32_t unEventID, VEventParam *pEventParam, const VINSTANCE &sender);

		/**
		 * @brief 根据实例ID获取事件处理对象.
		 * @param [in] instance : 实例ID
		 * @param [in] &pHandler : 返回实例对象指针
		 * @return 已注册的对象返回对象指针，否则返回空指针.
		 */
		bool getEventHandler(VINSTANCE instance, VEventHandler *&pHandler);

		/**
		 * @brief 判断是否有效的可收发事件对象.
		 * @param [in] pHandler : 事件处理对象指针
		 * @return 已注册对象为有效对象，返回true，否则返回false.  
		 */
		bool isValidHandler(VEventHandler *pHandler);

		/**
		 * @brief 派发事件. 
		 * @note 在QGSystem::Update中调用
		 * @return 调用成功返回true，否则返回false  
		 */
		bool dispatchEvent();

	private:
		/**
		 * @brief 注册事件处理对象. 
		 * @note 通过调用该函数才可以，事件处理对象才可以收发事件.
		 * @param [in] pHandler : 事件处理对象
		 * @return 事件实例ID  
		 */
		VINSTANCE registerHandler(VEventHandler *pHandler);

		/**
		 * @brief 反注册事件处理对象 
		 * @note 调用该接口后，事件处理对象无法再发送和接收处理事件.
		 * @param [in] instances : 事件实例ID
		 * @return 函数调用成功返回true，否则返回false.  
		 */
		bool unregisterHandler(const VINSTANCE &instances);

		/**
		 * @brief 注册事件
		 * @note 注册事件后，可以只接收到关注的事件，不关注的事件无法接收到
		 * @param [in] unEventID : 事件ID
		 * @param [in] instance : 关注该事件ID的处理对象
		 * @return 函数调用成功返回true，否则返回false.
		 */
		bool registerEvent(uint32_t unEventID, const VINSTANCE &instance);

		/**
		 * @brief 反注册事件
		 * @note 反注册事件后，事件处理对象无法收到该事件
		 * @param [in] unEventID : 事件ID
		 * @param [in] instance : 关注该事件ID的处理对象
		 * @return 函数调用成功返回true，否则返回false.
		 */
		bool unregisterEvent(uint32_t unEventID, const VINSTANCE &instance);

		/**
		 * @brief 获取当前待处理事件队列的第一个事件.
		 * @param [in] Item : 事件项
		 * @param [in] bRemovable : 是否移除该事件，默认为移除该事件.
		 * @return 调用成功返回true，否则返回false.  
		 */
		bool peekEvent(VEventItem &Item, bool bRemovable = true);

		/**
		 * @brief 清除所有事件队列中的事件.
		 * @return void  
		 */
		void clearEventQueue();

	private:
		typedef std::vector<VEventHandler*> VHandlerList;
		typedef VHandlerList::iterator VHandlerListItr;

		typedef std::list<VEventItem> VEventList;
		typedef VEventList::iterator VEventListItr;

		typedef std::set<VINSTANCE> VEventInstSet;
		typedef VEventInstSet::iterator VEventInstSetItr;

		typedef std::vector<VEventInstSet> VEventFilterList;
		typedef VEventFilterList::iterator VEventFilterListItr;

		VHandlerList	m_EventHandlers;					/**< 事件处理对象链表 */
		VEventList		m_EventQueue[V_MAX_EVENT_QUEUE];	/**< 待处理事件队列 */

		VEventFilterList	m_EventFilters;					/**< 事件过滤表 */

		int32_t			m_nCurrentQueue;					/**< 当前待处理事件队列 */

		VPlatform::VMutex			*m_pMutex;				/**< 互斥量对象，以支持多线程访问 */
		VPlatform::VMutex			*m_pEventMutex;			/**< 事件注册和反注册，事件派发互斥量，用于事件注册 */
	};

	#define V_EVENT_MANAGER		(VEventManager::GetInstance())
}


#endif	/*__VISION_EVENT_MANAGER_H__*/
