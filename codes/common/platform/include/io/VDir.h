/**************************************************************************************************
 * Copyright (C) 2014. Tiny Entertainment Studio.
 * All rights reserved.
 *
 * @file    VDir.h
 * @brief   操作系统平台无关的枚举搜索路径文件类定义.
 * @author  aaronwang
 * @date    2014/2/9 22:41:46
 * @version v1.00
 **************************************************************************************************/

#ifndef __VISION_DIR_H__
#define __VISION_DIR_H__


#include "VType.h"
#include "VMacro.h"
#include "VPlatform.h"


namespace VPlatform
{
	class IDirAdapter;

	/**
	 * @class VDir
	 * @brief 操作系统平台无关的枚举搜索路径文件类.
	 */
	class VPLATFORM_API VDir
	{
		V_DISABLE_COPY(VDir);

	public:
		static char NATIVE_SEPARATOR;

	public:
		/**
		 * @brief Constructor for VDir.
		 */
		VDir();

		/**
		 * @brief Destructor for VDir.
		 */
		~VDir();

		/**
		 * @brief 开始枚举搜索指定目录下的文件.
		 * @param [in] strPath : 指定目录文件格式字符串
		 * @return 调用成功返回true，失败返回false.  
		 */
		bool findFile(const VString &strPath);

		/**
		 * @brief 搜索下一个文件.
		 * @return 枚举没结束返回true，否则返回false表示枚举结束.  
		 */
		bool findNextFile();

		/**
		 * @brief 结束当前枚举搜索.
		 * @return void  
		 */
		void close();

		/**
		 * @brief 获取枚举目录的完整路径.
		 * @return 返回枚举目录的路径，返回类型std::string.
		 */
		VString getRoot() const;

		/**
		 * @brief 获取当前枚举到的完整文件名.
		 * @return 返回当前枚举到的完整文件名，类型std::string.
		 */
		VString getFileName() const;

		/**
		 * @brief 获取当前枚举到的文件的全路径名，包括完整文件名.
		 * @return 返回当前枚举到的文件的全路径名，类型std::string.
		 */
		VString getFilePath() const;

		/**
		 * @brief 获取当前枚举到的文件文件名，不包括扩展名.
		 * @return 返回当前枚举到的文件文件名，类型std::string.  
		 */
		VString getFileTitle() const;

		/**
		 * @brief 获取当前枚举到的文件大小.
		 * @return 返回当前枚举到的文件大小.  
		 */
		uint32_t getFileSize() const;

		/**
		 * @brief 判断当前枚举到的文件是否点目录，包括'.'和'..' .
		 * @return 点目录返回true，否则返回false.  
		 */
		bool isDots() const;

		/**
		 * @brief 判断当前枚举到的文件是否文件夹.
		 * @return 文件返回true，否则返回false.  
		 */
		bool isDirectory() const;

		/**
		 * @brief 获取当前枚举到的文件的创建时间戳.
		 * @return 返回文件创建时间戳，该时间是从1970年1月1日到当前的秒数
		 */
		long_t getCreationTime() const;

		/**
		 * @brief 获取当前枚举到的文件的最后访问时间戳.
		 * @return 返回文件最后访问时间戳，该时间是从1970年1月1日到当前的秒数
		 */
		long_t getLastAccessTime() const;

		/**
		 * @brief 获取当前枚举到的文件的最后修改时间戳.
		 * @return 返回文件最后修改时间戳，该时间是从1970年1月1日到当前的秒数  
		 */
		long_t getLastWriteTime() const;

		/**
		 * @brief 创建文件夹.
		 * @note 该接口不能创建多级文件夹.
		 * @param [in] strDir : 文件夹路径名称
		 * @return 调用成功返回true，否则返回false.  
		 */
		static bool makeDir(const VString &strDir);

		/**
		 * @brief 删除文件夹. 
		 * @note 该接口不能删除多级文件夹.
		 * @param [in] strDir : 文件夹路径名称
		 * @return 调用成功返回true，否则返回false.   
		 */
		static bool removeDir(const VString &strDir);

		/**
		 * @brief 删除文件.
		 * @param [in] strFileName : 需要删除文件的名称.
		 * @return 调用成功返回true，否则返回false.  
		 */
		static bool remove(const VString &strFileName);

		/**
		 * @brief 判断路径对应的文件是否存在.
		 * @param [in] strPath : 完整路径名
		 * @return 文件存在返回true，否则返回false.  
		 */
		static bool exists(const VString &strPath);

		/**
		 * @brief 获取应用程序缓存数据存储路径，不同平台指定对应的路径，以对上层透明处理.
		 * @return 返回应用程序缓存数据存储路径.  
		 */
		static VString getCachePath();

		/**
		 * @brief 获取应用程序路径.
		 * @return 返回应用程序路径.  
		 */
		static VString getAppPath();

		/**
		 * @brief 获取系统相关的路径分隔符
		 */
		static char getNativeSeparator();
		
	protected:
		IDirAdapter	*m_pDirAdpater;

		static IDirAdapter *s_pDirAdapter;
	};
}


#endif	/*__VISION_DIR_H__*/
