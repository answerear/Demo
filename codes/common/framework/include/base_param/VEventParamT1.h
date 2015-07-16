/**************************************************************************************************
 * Copyright (C) 2014. Tiny Entertainment Studio.
 * All rights reserved.
 *
 * @file    VEventParamT1.h
 * @brief   事件参数基类定义.
 * @author  aaronwang
 * @date    2014/2/9 23:34:03
 * @version v1.00
 **************************************************************************************************/

#ifndef __VISION_EVENT_PARAM_T1_H__
#define __VISION_EVENT_PARAM_T1_H__


#include "VEventParam.h"


namespace VFramework
{
	/**
	 * @brief 带一个成员的参数类
	 * @note clone方法会复制一个对象出来用于异步发送事件，当异步事件派发完后，系统会释放该空间
	 */
	template <typename T>
	class VEventParamT1 : public VEventParam
	{
	public:
		VEventParamT1()	
		{
		}

		VEventParamT1(const T &value) 
			: m_value(value)	
		{
		}

	protected:
		virtual VEventParam *clone()
		{
			VEventParamT1 *pCopy = new VEventParamT1(m_value);
			return pCopy;
		}

	public:
		T m_value;
	};	
}


#endif	/*__VISION_EVENT_PARAM_T1_H__*/
