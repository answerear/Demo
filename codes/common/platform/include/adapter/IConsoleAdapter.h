/**************************************************************************************************
 * Copyright (C) 2014. Tiny Entertainment Studio.
 * All rights reserved.
 *
 * @file    IConsoleAdapter.h
 * @brief   操作系统适配层的控制台接口类定义.
 * @author  aaronwang
 * @date    2014/2/9 20:42:04
 * @version v1.00
 **************************************************************************************************/

#ifndef __VISION_CONSOLE_ADAPTER_H__
#define __VISION_CONSOLE_ADAPTER_H__


#include "VType.h"
#include "VMacro.h"


namespace VPlatform
{
	/**
	 * @class IConsoleAdapter
	 * @brief 操作系统相关控制台接口类.
	 * @note 相关操作系统平台需要继承该接口类实现具体平台相关功能
	 */
	class IConsoleAdapter
	{
		V_DECLARE_INTERFACE(IConsoleAdapter);

	public:
		/**
		 * @brief 输出到控制台.
		 * @param [in] pText : 需要输出的以'\0'结尾字符串，
		 * @return void 
		 */
		virtual void print(const char *pText) = 0;
	};
}


#endif	/*__VISION_CONSOLE_ADAPTER_H__*/
