/**************************************************************************************************
 * Copyright (C) 2014. Tiny Entertainment Studio.
 * All rights reserved.
 *
 * @file    VEventParamT2.h
 * @brief   事件参数基类定义.
 * @author  aaronwang
 * @date    2014/2/9 23:34:03
 * @version v1.00
 **************************************************************************************************/

#ifndef __VISION_EVENT_PARAM_T2_H__
#define __VISION_EVENT_PARAM_T2_H__


#include "VEventParam.h"


namespace VFramework
{	
	/**
	 * @brief 带两个成员的参数类
	 * @note clone方法会复制一个对象出来用于异步发送事件，当异步事件派发完后，系统会释放该空间
	 */
	template <typename T1, typename T2>
	class VEventParamT2 : public VEventParam
	{
	public:
		VEventParamT2()
		{
		}

		VEventParamT2(const T1 &value1, const T2 &value2)
			: m_value1(value1)
			, m_value2(value2)
		{
		}

	protected:
		virtual VEventParam *clone()
		{
			VEventParamT2 *pCopy = new VEventParamT2(m_value1, m_value2);
			return pCopy;
		}

	public:
		T1 m_value1;
		T2 m_value2;
	};
}


#endif	/*__VISION_EVENT_PARAM_T2_H__*/
