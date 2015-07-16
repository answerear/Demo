/**************************************************************************************************
 * Copyright (C) 2014. Tiny Entertainment Studio.
 * All rights reserved.
 *
 * @file    VConsole.h
 * @brief   操作系统平台无关控制台类定义.
 * @author  aaronwang
 * @date    2014/2/9 21:44:02
 * @version v1.00
 **************************************************************************************************/

#ifndef __VISION_CONSOLE_H__
#define __VISION_CONSOLE_H__


#include "VSingleton.h"
#include "VPlatform.h"


namespace VPlatform
{
	class IConsoleAdapter;

	/**
	 * @class VConsole
	 * @brief 操作系统平台无关控制台类.
	 * @note 该类封装了平台相关处理，实现对平台进一步隔离；该类是单例，可以通过V_CONSOLE全局宏来访问.
	 */
	class VPLATFORM_API VConsole : public VSingleton<VConsole>
	{
		friend class VSystem;

		V_DISABLE_COPY(VConsole);

	private:
		/**
		 * @brief Constructor for VConsole.
		 */
		VConsole();

		/**
		 * @brief Destructor for VConsole.
		 */
		virtual ~VConsole();

	public:
		/**
		 * @brief 输出到平台.
		 * @param [in] pszFmt : 格式化字符串
		 * @param [in] ... : 参数列表
		 * @return void  
		 */
		void print(const char *pszFmt, ...);

	private:
		IConsoleAdapter	*m_pAdapter;	/**< 平台接口对象 */
	};

	#define V_CONSOLE		(VConsole::GetInstance())
}


#endif	/*__VISION_CONSOLE_H__*/
