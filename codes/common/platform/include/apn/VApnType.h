/**************************************************************************************************
 * Copyright (C) 2014. Tiny Entertainment Studio.
 * All rights reserved.
 *
 * @file    VApnType.h
 * @brief   接入点相关类型枚举.
 * @author  aaronwang
 * @date    2014/2/9 21:23:44
 * @version v1.00
 **************************************************************************************************/

#ifndef __VISION_APN_TYPE_H__
#define __VISION_APN_TYPE_H__


#include "VType.h"
#include "VMacro.h"


namespace VPlatform
{
	/**
	 * @brief 接入点类型枚举
	 */
	enum EApnType
	{
		E_APN_UNREACHABLE = 0,	/**< 没有可用接入点 */
		E_APN_WIFI,				/**< WIFI */
		E_APN_2G,				/**< 2G */
		E_APN_3G,				/**< 3G */
		E_APN_4G,				/**< 4G */
		E_APN_UNKNOWN,			/**< 未知接入点 */
	};

	/**
	 * @brief 运营商类型枚举
	 */
	enum ECarrier
	{
		E_CARRIER_UNKNOWN = 0,		/**< 未知运营商 */
		E_CARRIER_CHINA_MOBILE,		/**< 中国移动 */
		E_CARRIER_CHINA_UNICOM,		/**< 中国联通 */
		E_CARRIER_CHINA_TELECOM,	/**< 中国电信 */
		E_CARRIER_CHINA_TIETONG,	/**< 中国铁通 */
	};
}


#endif	/*__VISION_APN_TYPE_H__*/
