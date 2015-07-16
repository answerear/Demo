/**************************************************************************************************
 * Copyright (C) 2014. Tiny Entertainment Studio.
 * All rights reserved.
 *
 * @file    VEventParamBuffer.h
 * @brief   事件参数基类定义.
 * @author  aaronwang
 * @date    2014/2/9 23:34:03
 * @version v1.00
 **************************************************************************************************/

#ifndef __VISION_EVENT_PARAM_BUFFER_H__
#define __VISION_EVENT_PARAM_BUFFER_H__


#include "VEventParam.h"


namespace VFramework
{
	/**
	 * @brief 带一个成员的参数类
	 */
	class VFRAMEWORK_API VEventParamBuffer : public VEventParam
	{
	public:
		VEventParamBuffer();
		VEventParamBuffer(char *pBuffer, int32_t nBufSize);

	protected:
		virtual VEventParam *clone();

	public:
		char	*m_pBuffer;
		int32_t	m_nBufSize;
	};
}


#endif	/*__VISION_EVENT_PARAM_BUFFER_H__*/
