/**************************************************************************************************
 * Copyright (C) 2014. Tiny Entertainment Studio.
 * All rights reserved.
 *
 * @file    VEventParamT5.h
 * @brief   事件参数基类定义.
 * @author  aaronwang
 * @date    2014/2/9 23:34:03
 * @version v1.00
 **************************************************************************************************/

#ifndef __VISION_EVENT_PARAM_T5_H__
#define __VISION_EVENT_PARAM_T5_H__


#include "VEventParam.h"


namespace VFramework
{	
	/**
	 * @brief 带五个成员的参数类
	 */
	template <typename T1, typename T2, typename T3, typename T4, typename T5>
	class VEventParamT5 : public VEventParam
	{
	public:
		VEventParamT5()
		{
		}

		VEventParamT5(const T1 &value1, const T2 &value2, const T3 &value3, const T4 &value4, const T5 &value5)
			: m_value1(value1)
			, m_value2(value2)
			, m_value3(value3)
			, m_value4(value4)
			, m_value5(value5)
		{
		}

	protected:
		virtual VEventParam *clone()
		{
			VEventParamT5 *pCopy = new VEventParamT5(m_value1, m_value2, m_value3, m_value4, m_value5);
			return pCopy;
		}

	public:
		T1 m_value1;
		T2 m_value2;
		T3 m_value3;
		T4 m_value4;
		T5 m_value5;
	};
}


#endif	/*__VISION_EVENT_PARAM_T5_H__*/
