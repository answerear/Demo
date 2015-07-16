/**************************************************************************************************
 * Copyright (C) 2014. Tiny Entertainment Studio.
 * All rights reserved.
 *
 * @file    VEventMacro.h
 * @brief   事件处理系统辅助宏定义.
 * @author  aaronwang
 * @date    2014/2/9 23:17:16
 * @version v1.00
 **************************************************************************************************/

#ifndef __VISION_EVENT_MACRO_H__
#define __VISION_EVENT_MACRO_H__


#include "VType.h"
#include "VMacro.h"
#include "VInstance.h"


#define V_BROADCAST_INSTANCE_ID        VFramework::VInstance::V_BROADCAST_INSTANCE_ID    /**< 广播事件实例ID */
#define V_INVALID_INSTANCE_ID          VFramework::VInstance::V_INVALID_INSTANCE_ID      /**< 无效事件实例ID */


namespace VFramework
{

/// 声明事件MAP
#define V_DECLARE_EVENT_MAP() \
public: \
	bool eventProc(uint32_t unEventID, VEventParam *pEventParam, VINSTANCE sender); \
protected: \
	virtual bool processEvent(uint32_t unEventID, VEventParam *pEventParam, VINSTANCE sender); 

/// 声明事件处理函数
#define V_DECLARE_EVENT_HANDLE(func)	\
	bool func(VEventParam *pEventParam, VINSTANCE sender);

/// 开始实现事件处理函数
#define V_BEGIN_EVENT_MAP(theClass, classBase) \
	bool theClass::processEvent(uint32_t unEventID, VEventParam *pEventParam, VINSTANCE sender) \
	{ \
		bool bResult = eventProc(unEventID, pEventParam, sender); \
		if (!bResult) \
		{ \
			bResult = classBase::processEvent(unEventID, pEventParam, sender); \
		} \
		return bResult; \
	} \
	\
	bool theClass::eventProc(uint32_t unEventID, VEventParam *pEventParam, VINSTANCE sender) \
	{ \
		bool bResult = false; \

/// 事件处理函数响应调用
#define V_ON_EVENT(eid, func)	\
	if (eid == unEventID)	\
	{	\
		bResult = func(pEventParam, sender);	\
		return bResult;	\
	}
	
/// 结束事件处理函数
#define V_END_EVENT_MAP()	\
		return bResult;	\
	}

/// 开始注册事件过滤
#define V_BEGIN_EVENT_FILTER(theClass, classBase)	\
	void theClass::setupEventFilter()	\
	{	\
		classBase::setupEventFilter();	\

/// 注册事件过滤
#define V_EVENT_FILTER(eid)		registerEvent(eid)

/// 结束事件过滤
#define V_END_EVENT_FILTER()	\
	}
}


#endif	/*__VISION_EVENT_MACRO_H__*/
