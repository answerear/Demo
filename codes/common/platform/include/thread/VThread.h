/**************************************************************************************************
 * Copyright (C) 2014. Tiny Entertainment Studio.
 * All rights reserved.
 *
 * @file    VThread.h
 * @brief   线程类定义.
 * @author  aaronwang
 * @date    2014/2/10 0:50:43
 * @version v1.00
 **************************************************************************************************/

#ifndef __VISION_THREAD_H__
#define __VISION_THREAD_H__


#include "VType.h"
#include "VMacro.h"
#include "VPlatform.h"
#include <pthread.h>


namespace VPlatform
{
	class VPLATFORM_API VThreadID
	{
	public:
		VThreadID(const pthread_t &tid)
			: m_tid(tid)
		{}

		bool operator ==(const VThreadID &other) const
		{
			return pthread_equal(m_tid, other.m_tid) == 0;
		}

		bool operator !=(const VThreadID &other) const
		{
			return pthread_equal(m_tid, other.m_tid) != 0;
		}

		void *getID() const
		{
#ifdef V_OS_WIN32
			return m_tid.p;
#else
			return (void*)m_tid;
#endif
		}

		const pthread_t &m_tid;
	};
	

	/**
	 * @class VThread
	 * @brief 线程类.
	 * @note 该类提供多线程各种接口.
	 */
	class VPLATFORM_API VThread
	{
		V_DISABLE_COPY(VThread);

	public:
		/**
		 * @brief 线程优先级
		 */
		enum EPriority
		{
			E_PRIORITY_IDLE = 0,		/** 最低优先级，空闲时才执行 */
			E_PRIORITY_LOWEST,
			E_PRIORITY_LOW,
			E_PRIORITY_NORMAL,
			E_PRIORITY_HIGH,
			E_PRIORITY_HIGHEST,
			E_PRIORITY_TIME_CRITICAL,	/** 最高优先级 */
			E_PRIORITY_INHERIT,			/** 继承自创建的线程的优先级 */
			E_MAX_PRIORITY
		};

		/**
		 * @brief Constructor for VThread.
		 */
		VThread();

		/**
		 * @brief Destructor for VThread.
		 */
		virtual ~VThread();

		/**
		 * @brief 启动线程.
		 * @param [in] ePriority : 线程优先级，默认为E_PRIORITY_INHERIT.
		 * @return 调用成功返回true，否则返回false. 
		 * @see EPriority
		 */
		bool start(EPriority ePriority = E_PRIORITY_INHERIT);

		/**
		 * @brief 挂起当前线程，直到Resume()调用唤醒当前线程.
		 * @note 只能在需要的线程内调用，该接口是挂起调用的线程
		 * @return 调用成功返回true，否则返回false.   
		 */
		bool suspend();

		/**
		 * @brief 唤醒线程 
		 * @note 调用Suspend后，在别的线程代用该接口，可以唤醒对应的线程.
		 * @return 调用成功返回true，否则返回false.   
		 */
		bool resume();

		/**
		 * @brief 终止线程.
		 * @return 调用成功返回true，否则返回false.   
		 */
		bool terminate();

		/**
		 * @brief 等待线程执行完成.
		 * @return 调用成功返回true，否则返回false.   
		 */
		bool wait();

		/**
		 * @brief 线程是否在执行
		 * @return 线程正在执行返回true，否则返回false.
		 */
		bool isRunning() const	{ return m_bRunning; }

		/**
		 * @brief 线程是否挂起
		 * @return 线程挂起中则返回true，否则返回false.
		 */
		bool isSuspend() const	{ return m_bSuspend; }

		/**
		 * @brief 线程处理函数，继承者实现该函数以执行线程处理.
		 * @return 返回给系统的返回值  
		 */
		virtual int32_t run() = 0;

		/**
		 * @brief 获取线程对应的ID
		 * @return 返回线程ID
		 */
		VThreadID getThreadID() const	{ return VThreadID(m_thread); }

		/**
		 * @brief 静态接口，获取当前调用线程ID.
		 * @return 线程ID  
		 */
		static VThreadID getCurrentThreadID();

		/**
		 * @brief 静态接口，获取主线程ID.
		 * @return 线程ID  
		 */
		static VThreadID getMainThreadID();

	private:
		void release();

		static void *ThreadRoutine(void *pUser);

	protected:
		pthread_t		m_thread;
		pthread_attr_t	m_attr;
		pthread_cond_t	m_cond;
		pthread_mutex_t	m_mutex;

		bool			m_bRunning;
		bool			m_bSuspend;

		static pthread_t m_mainthread;
	};
}


#endif	/*__VISION_THREAD_H__*/
