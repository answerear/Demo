

#ifndef __VISION_LOGGER_SERVICE_H__
#define __VISION_LOGGER_SERVICE_H__


#include "VLoggerInterface.h"
#include "VSingleton.h"
#include "VLoggerTask.h"
#include "VThread.h"
#include "ITimerObserver.h"
#include <list>


namespace VPlatform
{
	class VFileDataStream;
	class VTimer;
	class VMutex;
	class VDir;
	class VDateTime;
}

namespace VLoggerSystem
{
	using namespace VPlatform;

	class VLoggerItem;
	
	const int32_t MAX_LOG_CACHE_COUNT = 2;		/**< 日志缓存队列数 */

	class VLoggerService 
		: public ILoggerService
		, public VSingleton<VLoggerService>
		, public VThread
		, public ITimerObserver
	{
		V_DISABLE_COPY(VLoggerService);

	public:
		VLoggerService();
		virtual ~VLoggerService();

	protected:	// from ILoggerService
		/**
		 * @brief 启动日志服务
		 */
		virtual bool startup(int32_t nAppID, const VString &strVersion, bool bForceOutput = false);
		
		/**
		 * @brief 输出日志
		 */
		virtual void trace(ELogLevel eLevel, const char *lpszFileName, int nLine, const char *lpszModule, const char *lpszFmt, ...);
		
		/**
		 * @brief 指定开始时间和结束时间来获取日志文件内容
		 */
		virtual void getLogData(uint32_t unBeginTimestamp, uint32_t unEndTimestamp, char *&pszContent, uint32_t &unContentSize);

		/**
		 * @brief 指定结束结束时间和内容大小获取日志文件内容
		 */
		virtual void getLogData(uint32_t unEndTimestamp, char *&pszContent, uint32_t &unContentSize);

		/**
		 * @brief 程序进入后台调用，主要给终端平台调用，Win32和linux忽略
		 */
		virtual void enterBackground();

		/**
		 * @brief 程序进入前台调用，主要给终端平台调用，Win32和linux忽略
		 */
		virtual void enterForeground();

	protected:	// from QGThread
		virtual int32_t run();

	protected:	// from ITimerObserver
		virtual void onTimer(uint32_t unTimerID);

	protected:
		bool Startup();
		void Shutdown();

		bool OpenLogFile();
		void CloseLogFile();
		void WriteLogFile(int32_t nCacheIndex);
		int ReadLogFile(time_t t, char *pBuffer, int32_t nBufferSize);

		void StartFlushTimer();
		void StopFlushTimer();

		void CheckLogFile(const VDir &rDir, time_t lTimestamp);
		void FlushLog(bool bTerminate = false);

		VString GetLogFilePath() const;
		VString GetFileName(const VString &strFilePath) const;
		VString MakeLogFileName(const VDateTime &rDateTime, const VString &strPath) const;

		void ClearLogCache(int nCacheIndex = -1);

		void SwitchCache();

		void StartAsyncTask();

		void SubmitWriteLogTask();
		void SubmitCheckLogTask();

		void ProcessWriteLogTask(VLoggerTask *pTask);
		void ProcessCheckLogTask(VLoggerTask *pTask);

		ELogLevel GetLogLevelFromString(const VString &strLevel) const;
		VString GetLogLevelString(ELogLevel eLevel) const;

		uint32_t GetCurrentLogFileSize() const;

	protected:
		typedef std::list<VLoggerItem*>	VLoggerCache;
		typedef VLoggerCache::iterator	VLoggerCacheItr;

		typedef std::list<VLoggerTask*>		VAsyncTaskQueue;
		typedef VAsyncTaskQueue::iterator	VAsyncTaskQueueItr;

		VFileDataStream		*m_pFileStream;			/// 日志文件流
		VTimer				*m_pFlushTimer;			/// 写回定时器
		VMutex				*m_pLogMutex;			/// 该锁用于防止外部调用Trace时候的多线程访问
		VMutex				*m_pTaskMutex;			/// 该锁用于异步任务
		VMutex				*m_pWorkingMutex;		/// 该锁用于工作线程

		int32_t				m_nCurrentCache;		/// 当前缓存数据流索引
		int32_t				m_nCacheCurrentCapacity;/// 当前缓存容量，单位：字节
		int32_t				m_nCurrentLogHour;		/// 当前日志文件输出的小时数，用于是否切换文件存放日志
		int32_t				m_nAppID;				/// APP ID

		ELogLevel			m_eLogLevel;			/// 当前日志输出级别
		ELogTask			m_eLogTask;				/// 当前执行的异步任务类型

		bool				m_bStartup;				/// 是否曾经输出过日志
		bool				m_bForceOutput;			/// 是否强制输出，不管后台下发的配置文件
		bool				m_bTerminate;			/// 工作线程被终止标记

		VLoggerCache		m_LogCache[MAX_LOG_CACHE_COUNT];	/// 日志缓存数据
		VAsyncTaskQueue		m_TaskQueue;			/// 异步任务队列

		VString				m_strVersion;			/// 软件版本号
	};
}


#endif	/*__VISION_LOGGER_SERVICE_H__*/
