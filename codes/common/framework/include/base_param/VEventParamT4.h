/**************************************************************************************************
 * Copyright (C) 2014. Tiny Entertainment Studio.
 * All rights reserved.
 *
 * @file    VEventParamT4.h
 * @brief   事件参数基类定义.
 * @author  aaronwang
 * @date    2014/2/9 23:34:03
 * @version v1.00
 **************************************************************************************************/

#ifndef __VISION_EVENT_PARAM_T4_H__
#define __VISION_EVENT_PARAM_T4_H__


#include "VType.h"
#include "VMacro.h"
#include "VFramework.h"


namespace VFramework
{	
	/**
	 * @brief 带四个成员的参数类
	 */
	template <typename T1, typename T2, typename T3, typename T4>
	class VEventParamT4 : public VEventParam
	{
	public:
		VEventParamT4()
		{
		}

		VEventParamT4(const T1 &value1, const T2 &value2, const T3 &value3, const T4 &value)
			: m_value1(value1)
			, m_value2(value2)
			, m_value3(value3)
			, m_value4(value4)
		{
		}

	protected:
		virtual VEventParam *clone()
		{
			VEventParamT4 *pCopy = new VEventParamT4(m_value1, m_value2, m_value3, m_value4);
			return pCopy;
		}

	public:
		T1 m_value1;
		T2 m_value2;
		T3 m_value3;
		T4 m_value4;
	};
}


#endif	/*__VISION_EVENT_PARAM_T4_H__*/
