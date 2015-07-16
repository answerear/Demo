/**************************************************************************************************
 * Copyright (C) 2014. Tiny Entertainment Studio.
 * All rights reserved.
 *
 * @file    VDataStream.h
 * @brief   数据流类定义.
 * @author  aaronwang
 * @date    2014/2/9 21:46:43
 * @version v1.00
 **************************************************************************************************/

#ifndef __VISION_DATA_STREAM_H__
#define __VISION_DATA_STREAM_H__


#include "VType.h"
#include "VMacro.h"
#include "VPlatform.h"


namespace VPlatform
{
	/**
	 * @class VDataStream
	 * @brief 数据流类.
	 * @note 该类提供对基本数据类型的流输入和输出接口.
	 */
	class VPLATFORM_API VDataStream
	{
		V_DECLARE_INTERFACE(VDataStream);

	public:
		/**
		 * @brief 从数据流中读数据到缓冲区.
		 * @param [in] pBuffer : 数据缓冲区
		 * @param [in] nSize : 数据缓冲区大小
		 * @return 返回读取到的数据大小.
		 */
		virtual size_t read(void *pBuffer, size_t nSize) = 0;

		/**
		 * @brief 写缓冲区数据到数据流中.
		 * @param [in] pBuffer : 数据缓冲区
		 * @param [in] nSize : 数据缓冲区大小
		 * @return 返回写入的数据大小.  
		 */
		virtual size_t write(void *pBuffer, size_t nSize) = 0;

		/**
		 * @brief 把数据流指针移动到指定位置.
		 * @param [in] llPos : 指定偏移位置
		 * @return void  
		 */
		virtual void seek(long_t lPos) = 0;

		/**
		 * @brief 获取当前数据流读写位置. 
		 * @return 返回当前数据流读写位置.  
		 */
		virtual long_t tell() const = 0;

		/**
		 * @brief 获取数据流的大小.
		 * @return 返回当前数据流的大小  
		 */
		virtual long_t size() const = 0;

		/**
		 * @brief 是否到数据流末尾.
		 * @return 到末尾返回true，否则返回false.  
		 */
		virtual bool eof() const = 0;

		/**
		 * @brief 输出基本类型值到数据流
		 */
		VDataStream &operator<<(bool val);
		VDataStream &operator<<(int8_t val);
		VDataStream &operator<<(uint8_t val);
		VDataStream &operator<<(int16_t val);
		VDataStream &operator<<(uint16_t val);
		VDataStream &operator<<(int32_t val);
		VDataStream &operator<<(uint32_t val);
		VDataStream &operator<<(int64_t val);
		VDataStream &operator<<(uint64_t val);
		VDataStream &operator<<(float val);
		VDataStream &operator<<(double val);
		VDataStream &operator<<(const char *s);
		VDataStream &operator<<(const VString &s);

		/**
		 * @brief 输入数据流到基本类型值
		 */
		VDataStream &operator>>(bool &val);
		VDataStream &operator>>(int8_t &val);
		VDataStream &operator>>(uint8_t &val);
		VDataStream &operator>>(int16_t &val);
		VDataStream &operator>>(uint16_t &val);
		VDataStream &operator>>(int32_t &val);
		VDataStream &operator>>(uint32_t &val);
		VDataStream &operator>>(int64_t &val);
		VDataStream &operator>>(uint64_t &val);
		VDataStream &operator>>(float &val);
		VDataStream &operator>>(double &val);
		VDataStream &operator>>(char *&s);
		VDataStream &operator>>(VString &s);
	};
}


#endif	/*__VISION_DATA_STREAM_H__*/
