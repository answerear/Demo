/**************************************************************************************************
 * Copyright (C) 2014. Tiny Entertainment Studio.
 * All rights reserved.
 *
 * @file    VTimer.h
 * @brief   定时器类定义.
 * @author  aaronwang
 * @date    2014/2/10 0:59:58
 * @version v1.00
 **************************************************************************************************/

#ifndef __VISION_RUN_LOOP_TIMER_H__
#define __VISION_RUN_LOOP_TIMER_H__


#include "VSingleton.h"
#include "VPlatform.h"
#include <map>


namespace VPlatform
{
	#define V_INVALID_LOOP_ID		0

	class IRunLoopObserver;

	/**
	 * @class VRunLoop
	 * @brief 运行循环对象
	 * @note 该类是系统循环，按照系统循环计时
	 */
	class VPLATFORM_API VRunLoop
	{
		V_DISABLE_COPY(VRunLoop);

	public:
		/**
		 * @brief Constructor for VRunLoop.
		 */
		VRunLoop();

		/**
		 * @brief Destructor for VRunLoop.
		 */
		~VRunLoop();

		/**
		 * @brief 启动系统循环计时器.
		 * @param [in] unInterval : 定时毫秒数
		 * @param [in] bRepeat : 是否循环计时器
		 * @return 循环ID
		 */
		uint32_t start(uint32_t unInterval, bool bRepeat, IRunLoopObserver *pObserver);
		
		/**
		 * @brief 简单的启动系统循环，按照循环次数来回调
		 * @param : void
		 * @return 循环ID
		 */
		uint32_t start(IRunLoopObserver *pObserver);

		/**
		 * @brief 关闭循环计时器.
		 * @param [in] unLoopID : 循环ID，调用start接口返回
		 * @return 对应的循环计时器ID有效就返回true，否则返回false
		 */
		bool stop(uint32_t unLoopID);

		/**
		 * @brief 执行计时器，并且派发回调
		 */
		void execute();

	protected:
		struct RunLoopInfo
		{
			uint64_t			ullLastTimestamp;	/// 上次计时时间戳
			uint64_t			ullInterval;		/// 设定的时间间隔
			IRunLoopObserver	*pObserver;			/// 回调对象
			bool				bRepeat;			/// 是否循环计时
		};

		typedef std::map<uint32_t, RunLoopInfo> VRunLoopInfos;
		typedef VRunLoopInfos::iterator			VRunLoopInfosItr;

		typedef std::pair<uint32_t, RunLoopInfo> VRunLoopValue;

		VRunLoopInfos	m_infos;
		static uint32_t m_unLoopID;
	};
}


#endif	/*__VISION_RUN_LOOP_TIMER_H__*/
