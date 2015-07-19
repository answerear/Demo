
#ifndef __VISION_LOGGER_INTERFACE_H__
#define __VISION_LOGGER_INTERFACE_H__


#include "VType.h"
#include "VMacro.h"


#ifdef LOG_EXPORT
#define VLOG_API				VEXPORT_API
#else
#define VLOG_API				VIMPORT_API
#endif


namespace VLoggerSystem
{
	/**
	 * 日志级别
	 */
	enum ELogLevel
	{
		E_LOGLEVEL_OFF = 0,	/// 关日志
		E_LOGLEVEL_EVENT,	/// 关键日志
		E_LOGLEVEL_INFO,	/// 普通信息日志
		E_LOGLEVEL_DEBUG,	/// 调试日志
		E_LOGLEVEL_MAX
	};
	
	/**
	 * @brief 日志服务类，提供windows、ios、android三个平台的日志输出，日志会输出到文件和对应平台的console上
	 *        windows : console和vs的Output窗口
	 *		  ios : xcode的Output窗口
	 *		  android : logcat
	 */
	class VLOG_API ILoggerService
	{
		V_DECLARE_INTERFACE(ILoggerService);

	public:		
		/**
		 * @brief 启动日志服务
		 * @param nAppID [in]		: 
		 * @param strVersion [in]	: 软件字符串版本号
		 * @param bForceOutput [in]	: 是否强制输出日志，不受后台控制
		 * @return 调用成功返回true，否则返回false
		 * @remarks 只有调用了此接口，才可以输出日志
		 */
		virtual bool startup(int32_t nAppID, const VString &strVersion, bool bForceOutput = false) = 0;
		
		/**
		 * @brief 输出日志
		 * @param eLevel [in]		: 日志级别，该输出级别小于预设的级别，则会输出，否则不输出
		 * @param lpszFileName [in]	: 输出当前日志的源码文件名
		 * @param nLine [in]		: 输出当前日志的源码的行数
		 * @param lpszModule [in]	: 模块名称
		 * @param lpszFmt [in]		: 格式化字符串
		 * @return void
		 * @remarks 一行日志格式是：
		 *			YYYY-MM-DD HH:MM:SS.000 Level|ThreadID|uin|File:Line|Module|Content
		 *			一行日志最大长度是4096字节
		 */
		virtual void trace(ELogLevel eLevel, const char *lpszFileName, int nLine, const char *lpszModule, const char *lpszFmt, ...) = 0;
		
		/**
		 * @brief 指定开始时间和结束时间来获取日志文件内容
		 * @param unBeginTimestamp [in]		: 要获取日志内容的开始时间戳
		 * @param unEndTimestamp [in]		: 要获取日志内容的结束时间戳
		 * @param pszContent [in][out]		: 返回的日志内容
		 * @param unContentSize [in][out]	: 返回的日志内容大小
		 * @note 该接口是线程安全的
		 */
		virtual void getLogData(uint32_t unBeginTimestamp, uint32_t unEndTimestamp, char *&pszContent, uint32_t &unContentSize) = 0;

		/**
		 * @brief 指定结束结束时间和内容大小获取日志文件内容
		 * @param unEndTimestamp [in]		: 要获取日志内容的结束时间戳
		 * @param pszContent [in][out]		: 获取到的日志内容
		 * @param unContentSize [in][out]	: 传入获取的日志内容大小，返回实际获取到的内容大小
		 * @note 该接口是线程安全的
		 */
		virtual void getLogData(uint32_t unEndTimestamp, char *&pszContent, uint32_t &unContentSize) = 0;

		/**
		 * @brief 程序进入后台调用，主要给终端平台调用，Win32和linux忽略
		 */
		virtual void enterBackground() = 0;

		/**
		 * @brief 程序进入前台调用，主要给终端平台调用，Win32和linux忽略
		 */
		virtual void enterForeground() = 0;
	};

	/** 创建日志服务接口对象 */
	VLOG_API ILoggerService *createLoggerServiceInstance();

	VLOG_API ILoggerService *getLoggerServiceInstance();
}


#endif	/*__VISION_LOGGER_INTERFACE_H__*/
