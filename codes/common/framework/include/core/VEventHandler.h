/**************************************************************************************************
 * Copyright (C) 2014. Tiny Entertainment Studio.
 * All rights reserved.
 *
 * @file    VEventHandler.h
 * @brief   事件处理基类定义.
 * @author  aaronwang
 * @date    2014/2/9 22:52:46
 * @version v1.00
 **************************************************************************************************/

#ifndef __VISION_EVENT_HANDLER_H__
#define __VISION_EVENT_HANDLER_H__


#include "VEventMacro.h"
#include "VFramework.h"
#include <list>


namespace VFramework
{
	class VEventParam;

	/**
	 * @class VEventHandler
	 * @brief 事件处理基类.
	 * @note 继承该类可以发送事件和接收事件通知，该类提供基本事件发送和接收处理接口，
	 *		只有注册了对象才可以发送和接收事件.
	 * @see V_DECLARE_EVENT_MAP
	 * @see V_BEGIN_EVENT_MAP
	 * @see V_ON_EVENT_REQ
	 * @see V_END_EVENT_MAP
	 * @see class VEventManager
	 */
	class VFRAMEWORK_API VEventHandler
	{
		friend class VEventManager;

	public:
		/**
		 * @brief Constructor for VEventHandler.
		 * @param [in] bAutoRegister : 是否自动注册对象，默认为自动注册.
		 */
		VEventHandler(bool bAutoRegister = true);

		/**
		 * @brief Destructor for VEventHandler.
		 */
		virtual ~VEventHandler();

		/**
		 * @brief 事件处理对象类型，默认都是0，主要用于广播时，固定广播给某一类对象
		 * @return 返回一个整型的事件对象类型
		 */
		virtual int32_t handlerType() const;

		/**
		 * @brief 发送同步事件 
		 * @note 该接口是同步接口，调用该接口会立刻通知事件接收方，待接收方处理完才返回.
		 * @param [in] unEventID : 事件ID，自定义事件请在QG_EV_USER后扩展
		 * @param [in] pEventParam : 事件参数，继承VEventParam类实现不同事件ID对应的不同参数
		 * @param [in] receiver : 事件接收者实例，QG_BROADCAST_INSTANCE_ID为广播对象，凡是关注该事件的对象都能收到通知
		 * @param [in] nType : 用于广播的，广播给某一类对象
		 * @return 当接收者是广播对象时，则函数调用成功返回true，否则返回false；
		 *		当接收者是固定对象时，则函数返回接收对象处理函数的返回值.
		 * @see QGEventManager::SendEvent(uint32_t unEventID, VEventParam *pEventParam, VINSTANCE receiver, VINSTANCE sender)
		 */
		bool sendEvent(uint32_t unEventID, VEventParam *pEventParam, const VINSTANCE &receiver, int32_t nType = 0);

		/**
		 * @brief 发送异步事件 
		 * @note 该接口是异步接口，调用该接口，事件会放入事件处理队列，直到程序循环到事件派发时才会派发给相应对象处理.
		 * @param [in] unEventID : 事件ID，自定义事件请在QG_EV_USER后扩展
		 * @param [in] pEventParam : 事件参数，继承VEventParam类实现不同事件ID对应的不同参数
		 * @param [in] receiver : 事件接收者实例，QG_BROADCAST_INSTANCE_ID为广播事件，凡是关注该事件的对象都能收到通知
		 * @param [in] nType : 用于广播的，广播给某一类对象
		 * @return 函数调用成功返回true，返回false时，事件不会触发. 
		 * @see QGEventManager::PostEvent(uint32_t unEventID, VEventParam *pEventParam, VINSTANCE receiver, VINSTANCE sender)
		 */
		bool postEvent(uint32_t unEventID, VEventParam *pEventParam, const VINSTANCE &receiver, int32_t nType = 0);

		/**
		 * @brief 无指定对象的发送同步事件，注册了关注该事件的对象可以收到事件
		 * @param [in] unEventID : 事件ID，自定义事件请在EV_USER后扩展
		 * @param [in] pEventParam : 事件参数，继承VEventParam类实现不同事件ID对应的不同参数
		 * @return 函数调用成功返回true，返回false时，没有对象关注该事件. 
		 * @note 该接口是同步接口，调用该接口会立刻通知关注该事件的接收方，待接收方处理完才返回.
		 *		事件派发对象的顺序是随机的.
		 */
		bool sendEventEx(uint32_t unEventID, VEventParam *pEventParam);

		/**
		 * @brief 无指定对象的发送异步事件，注册了关注该事件的对象可以收到事件
		 * @param [in] unEventID : 事件ID，自定义事件请在EV_USER后扩展
		 * @param [in] pEventParam : 事件参数，继承VEventParam类实现不同事件ID对应的不同参数
		 * @return 函数调用成功返回true，返回false时，没有对象关注该事件. 
		 * @note 该接口是异步接口，调用该接口，事件会放入事件处理队列，直到程序循环到事件派发时才会派发给相应对象处理.
		 *		事件派发对象的顺序是随机的.
		 */
		bool postEventEx(uint32_t unEventID, VEventParam *pEventParam);

		/**
		 * @brief 获取当前事件处理对象实例ID.
		 * @note 只有注册了事件处理对象才会有有效实例ID返回，没有注册时返回的是QG_INVALID_INSTANCE_ID
		 * @return 返回当前事件处理对象实例ID 
		 */
		VINSTANCE getInstanceID() const { return m_InstanceID; }

	protected:
		/**
		 * @brief 注册事件处理对象，返回对象实例ID 
		 * @note 只有调用了该接口或者直接调用QGEventManager::RegisterHandler()才可以发送事件和接收事件.
		 * @return 返回对象实例ID
		 * @see QGEventManager::RegisterHandler(VEventHandler *pHandler)
		 */
		VINSTANCE registerHandler();

		/**
		 * @brief 反注册事件处理对象 
		 * @note 反注册后，对象不能再发送和接收事件，在析构函数时自动调用该接口.
		 * @return 调用成功返回true，否则返回false. 
		 * @see QGEventManager::UnregisterHandler(VINSTANCE instance)
		 */
		bool unregisterHandler();

		//子类首先用EventProc处理自己的事件，如果发现自己不需要处理就用ProcessEvent把事件交给父类

		/**
		 * @brief 处理事件函数 
		 * @note 继承者不需要直接重写该接口来处理事件，可在类定义中通过QG_DECLARE_EVENT_MAP、
		 *	在类实现文件中通过QG_BEGIN_EVENT_MAP，QG_ON_EVENT_REQ，QG_END_EVENT_MAP这4个辅助宏来实现事件处理函数.
		 *	事件处理函数返回是true时，不会再传递给基类处理，只有返回false时会给父类继续处理，直到事件处理类最顶层为止.
		 * @param [in] unEventID : 事件ID
		 * @param [in] pEventParam : 事件对应的参数对象
		 * @param [in] sender : 发送者对象ID
		 * @return 返回是true时，不会再传递给基类处理，只有返回false时会给父类继续处理，直到事件处理类最顶层为止.  
		 */
		virtual bool processEvent(uint32_t unEventID, VEventParam *pEventParam, const VINSTANCE &sender);

		/**
		 * @brief 基类事件处理函数，类似DefWindowProc.
		 * @note 该函数默认没有任何处理.
		 * @param [in] eventID : 事件ID
		 * @param [in] pEventParam : 事件对应的参数对象
		 * @param [in] sender : 发送者对象ID
		 * @return 永远返回true，因为VEventHandler是所有事件处理类的父类，无法再传递给其基类处理事件.
		 */
		bool eventProc(uint32_t eventID, VEventParam *pEventParam, const VINSTANCE &sender);

		/**
		 * @brief 设置事件过滤
		 * @return void
		 */
		void setupEventFilter();

		bool registerEvent(uint32_t unEventID);
		bool unregisterEvent(uint32_t unEventID);
		void unregisterAllEvent();

	private:
		VINSTANCE	m_InstanceID;

		typedef std::list<uint32_t>		VEventList;
		typedef VEventList::iterator	VEventListItr;

		VEventList	m_EventList;
	};
}

#endif	/*__VISION_EVENT_HANDLER_H__*/
