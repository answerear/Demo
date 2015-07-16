/**************************************************************************************************
 * Copyright (C) 2014. Tiny Entertainment Studio.
 * All rights reserved.
 *
 * @file    VEventParamT3.h
 * @brief   事件参数基类定义.
 * @author  aaronwang
 * @date    2014/2/9 23:34:03
 * @version v1.00
 **************************************************************************************************/

#ifndef __VISION_EVENT_PARAM_T3_H__
#define __VISION_EVENT_PARAM_T3_H__


#include "VEventParam.h"


namespace VFramework
{
	/**
	 * @brief 带三个成员的参数类
	 */
	template <typename T1, typename T2, typename T3>
	class VEventParamT3 : public VEventParam
	{
	public:
		VEventParamT3()
		{
		}

		VEventParamT3(const T1 &value1, const T2 &value2, const T3 &value3)
			: m_value1(value1)
			, m_value2(value2)
			, m_value3(value3)
		{
		}

	protected:
		virtual VEventParam *clone()
		{
			VEventParamT3 *pCopy = new VEventParamT3(m_value1, m_value2, m_value3);
			return pCopy;
		}

	public:
		T1 m_value1;
		T2 m_value2;
		T3 m_value3;
	};
}


#endif	/*__VISION_EVENT_PARAM_T3_H__*/
