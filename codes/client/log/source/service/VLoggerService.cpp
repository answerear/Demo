

#include "VLoggerService.h"
#include "VFileDataStream.h"
#include "VTimer.h"
#include "VMutex.h"
#include "VDateTime.h"
#include "VDir.h"
#include "VAutoLock.h"
#include "VLoggerItem.h"
#include <stdarg.h>


INIT_SINGLETON(VLoggerSystem::VLoggerService);


namespace VLoggerSystem
{
	const int32_t MAX_OUTPUT_BUFFER_SIZE = 2 * 1024;		/// 输出数据缓冲区大小，单位：字节
	const int32_t MAX_FLUSH_CAPACITY = 10 * 1024;			/// 最大缓存日志大小，超过则写回文件，单位：字节
	const int32_t MAX_FLUSH_INTERVAL = 10 * 1000;			/// 最大写回文件日志的时间间隔，单位：毫秒
	const int32_t MAX_LOG_FILE_OUT_OF_DATE = 7;				/// 日志文件最大缓存时间，单位：天

	const char V_LOG_LEVEL_DEBUG[] = "Debug";
	const char V_LOG_LEVEL_INFO[] = "Info";
	const char V_LOG_LEVEL_EVENT[] = "Event";
	const char V_LOG_LEVEL_OFF[] = "Off";

	ILoggerService *createLoggerServiceInstance()
	{
		return new VLoggerService();
	}

	ILoggerService *getLoggerServiceInstance()
	{
		return VLoggerService::GetInstancePtr();
	}

	VLoggerService::VLoggerService()
		: m_pFileStream(new VFileDataStream())
		, m_pFlushTimer(new VTimer())
		, m_pLogMutex(new VMutex(VMutex::Recursive))
		, m_pTaskMutex(new VMutex(VMutex::Recursive))
		, m_pWorkingMutex(new VMutex(VMutex::Recursive))
		, m_nCurrentCache(0)
		, m_nCacheCurrentCapacity(0)
		, m_nCurrentLogHour(-1)
		, m_eLogLevel(E_LOGLEVEL_DEBUG)
		, m_eLogTask(E_LOGTASK_NONE)
		, m_bStartup(false)
		, m_bForceOutput(false)
		, m_bTerminate(false)
		, m_strVersion("")
	{
		if (m_pFlushTimer != NULL)
		{
			m_pFlushTimer->setObserver(this);
		}
	}

	VLoggerService::~VLoggerService()
	{
		Shutdown();

		V_SAFE_DELETE(m_pFlushTimer);
		V_SAFE_DELETE(m_pWorkingMutex);
		V_SAFE_DELETE(m_pTaskMutex);
		V_SAFE_DELETE(m_pLogMutex);
		V_SAFE_DELETE(m_pFileStream);
	}


	bool VLoggerService::startup(int32_t nAppID, const VString &strVersion, bool bForceOutput /* = false */)
	{
		m_nAppID = nAppID;
		m_strVersion = strVersion;
		m_bForceOutput = bForceOutput;

		bool bRet = false;

		SubmitCheckLogTask();

		if (m_eLogLevel != E_LOGLEVEL_OFF)
		{
			bRet = Startup();
		}
		else
		{
			bRet = true;
		}

		trace(E_LOGLEVEL_EVENT, __FILE__, __LINE__, "Logger", "******************** Begin Log %s *******************", strVersion.c_str());

		return true;
	}

	void VLoggerService::trace(ELogLevel eLevel, const char *lpszFileName, int nLine, const char *lpszModule, const char *lpszFmt, ...)
	{
		if (eLevel <= m_eLogLevel || m_bForceOutput)
		{
			va_list args;
			char szContent[MAX_OUTPUT_BUFFER_SIZE] = {0};

			va_start(args, lpszFmt);
			vsnprintf(szContent, MAX_OUTPUT_BUFFER_SIZE-1, lpszFmt, args);
			va_end(args);

			int32_t nContentLength = strlen(szContent);

			// 简单处理后面多出来的换行符，因为日志SDK内部会自动添加换行符
			if (szContent[nContentLength-1] == '\n')
			{
				szContent[nContentLength-1] = 0;
				nContentLength--;
			}

			// 提取文件名，去掉路径名
			VString strName = GetFileName(lpszFileName);

			// 生成日志项，直接在调试控制台显示日志内容
			VString strLevel = GetLogLevelString(eLevel);
			VString strModule("");
			if (lpszModule != NULL)
				strModule = lpszModule;
			VLoggerItem *pItem = new VLoggerItem(strName, nLine, strLevel, strModule, szContent, nContentLength);
			if (pItem != NULL)
			{
				pItem->OutputConsole();

				// 把日志项添加到缓存中
				m_pLogMutex->lock();

				int32_t nCacheIndex = m_nCurrentCache;
				m_LogCache[nCacheIndex].push_back(pItem);
				m_nCacheCurrentCapacity += pItem->GetItemCapacity();

				// 检查是否需要写文件
				if (m_nCacheCurrentCapacity >= MAX_FLUSH_CAPACITY)
				{
					SubmitWriteLogTask();
				}

				m_pLogMutex->unlock();
			}
		}
	}

	void VLoggerService::getLogData(uint32_t unBeginTimestamp, uint32_t unEndTimestamp, char *&pszContent, uint32_t &unContentSize)
	{
		unContentSize = 0;
	}

	void VLoggerService::getLogData(uint32_t unEndTimestamp, char *&pszContent, uint32_t &unContentSize)
	{
		unContentSize = 0;
	}

	void VLoggerService::enterBackground()
	{
		trace(E_LOGLEVEL_EVENT, __FILE__, __LINE__, "Logger", "Enter Background -------------------------");

		// 强制输出缓存中日志到文件中
		if (m_eLogLevel != E_LOGLEVEL_OFF)
		{
			StopFlushTimer();
			FlushLog();
			CloseLogFile();
		}
	}

	void VLoggerService::enterForeground()
	{
		// 重启写日志定时器
		if (m_eLogLevel != E_LOGLEVEL_OFF)
		{
			OpenLogFile();
			m_nCurrentCache = 0;
			StartFlushTimer();
		}

		trace(E_LOGLEVEL_EVENT, __FILE__, __LINE__, "Logger", "Enter Foreground -------------------------");
	}

	int32_t VLoggerService::run()
	{
		while (1)
		{
			VLoggerTask *pTask = NULL;

			// 获取异步任务队列里面的任务处理
			m_pTaskMutex->lock();

			if (!m_TaskQueue.empty())
			{
				pTask = m_TaskQueue.front();
				m_TaskQueue.pop_front();
			}

			m_pTaskMutex->unlock();

			if (pTask != NULL)
			{
				switch (pTask->TaskType())
				{
				case E_LOGTASK_WRITE_FILE:
					ProcessWriteLogTask(pTask);
					break;
				case E_LOGTASK_CHECK_FILE:
					ProcessCheckLogTask(pTask);
					break;
				default:

					break;
				}
			}

			if (m_bTerminate)
			{
				// 线程被终止
				break;
			}

			// 处理完任务，如果任务队列为空，挂起线程
			m_pTaskMutex->lock();
			bool bEmpty = m_TaskQueue.empty();
			m_pTaskMutex->unlock();

			if (bEmpty)
			{
				suspend();
			}
		}

		return 0;
	}

	void VLoggerService::onTimer(uint32_t unTimerID)
	{
		if (m_pFlushTimer != NULL && m_pFlushTimer->getTimerID() == unTimerID)
		{
			// 提交后台写日志文件任务
			SubmitWriteLogTask();
		}
	}

	bool VLoggerService::Startup()
	{
		m_nCacheCurrentCapacity = 0;
		m_nCurrentCache = 0;

		// 打开日志文件
		OpenLogFile();

		// 启动写回定时器
		StartFlushTimer();

		// 启动写日志线程
		bool bRet = start();

		if (!m_bStartup)
		{
			m_bStartup = true;
		}

		return bRet;
	}

	void VLoggerService::Shutdown()
	{
		// 关定时器
		StopFlushTimer();

		// 杀异步写进程，直接用同步写
		if (isRunning())
		{
			terminate();
		}

		FlushLog(true);
		CloseLogFile();
	}

	bool VLoggerService::OpenLogFile()
	{
		// 先创建文件夹
		VString strLogPath = GetLogFilePath();
		VDir dir;
		dir.makeDir(strLogPath);

		// 构造文件名和保存当前小时，用于跨小时换文件存储
		VDateTime dt = VDateTime::currentDateTime();
		VString strFilePath = MakeLogFileName(dt, strLogPath);
		m_nCurrentLogHour = dt.Hour();
		
		bool bRet = false;
		if (m_pFileStream != NULL)
		{
			bRet = m_pFileStream->open(strFilePath.c_str(), VFileDataStream::E_MODE_APPEND|VFileDataStream::E_MODE_TEXT);
		}
		return bRet;
	}

	void VLoggerService::CloseLogFile()
	{
		if (m_pFileStream != NULL)
		{
			m_pFileStream->flush();
			m_pFileStream->close();
		}
	}

	void VLoggerService::WriteLogFile(int32_t nCacheIndex)
	{
		if (NULL == m_pFileStream)
			return;

		VLoggerCache &cache = m_LogCache[nCacheIndex];

		size_t s = cache.size();
		bool bRet = !cache.empty();
		bRet = bRet && !m_bTerminate;
		while (!cache.empty() && !m_bTerminate)
		{
			VLoggerItem *pItem = cache.front();

			if (pItem->GetHour() != m_nCurrentLogHour)
			{
				// 跨越到下一个小时，所以需要重新写一个新的日志文件
				CloseLogFile();
				OpenLogFile();
			}

			int32_t nBytesOfWritten = pItem->OutputFile(*m_pFileStream);
			cache.pop_front();
			V_SAFE_DELETE(pItem);
		}

		m_pFileStream->flush();
	}

	int32_t VLoggerService::ReadLogFile(time_t t, char *pBuffer, int32_t nBufferSize)
	{
		VString strLogPath = GetLogFilePath();

		VDateTime dt = VDateTime::fromSecsSinceEpoch(t);
		VString strFilePath = MakeLogFileName(dt, strLogPath);

		int32_t nBytesOfRead = 0;
		VFileDataStream fs;

		if (fs.open(strFilePath.c_str(), VFileDataStream::E_MODE_READ_ONLY))
		{
			int32_t nFileSize = fs.size();

			int32_t nSize = nFileSize > nBufferSize ? nBufferSize : nFileSize;
			char *pSrc = pBuffer - nSize;
			nBytesOfRead = fs.read((uint8_t*)pSrc, nSize);
			fs.close();
		}

		return nBytesOfRead;
	}

	void VLoggerService::StartFlushTimer()
	{
		if (m_pFlushTimer != NULL)
		{
			m_pFlushTimer->start(MAX_FLUSH_INTERVAL);
		}
	}

	void VLoggerService::StopFlushTimer()
	{
		if (m_pFlushTimer != NULL)
		{
			m_pFlushTimer->stop();
		}
	}

	void VLoggerService::CheckLogFile(const VDir &rDir, time_t lTimestamp)
	{
		if (rDir.isDots() || rDir.isDirectory())
			return;

		const int nOneDay = 24 * 60 * 60;
		const int nMaxOutdate = MAX_LOG_FILE_OUT_OF_DATE * nOneDay;
		time_t nLastTime = rDir.getLastWriteTime();
		time_t dt = lTimestamp - nLastTime;
		if (dt >= nMaxOutdate)
		{
			VDir::remove(rDir.getFilePath().c_str());
		}
	}

	void VLoggerService::FlushLog(bool bTerminate /* = false */)
	{
		// 关闭后台工作线程，全部日志同步写回文件
		if (isRunning())
		{
			terminate();
		}

		if (bTerminate)
		{
			trace(E_LOGLEVEL_EVENT, __FILE__, __LINE__, "Logger", "******************** END LOG *******************\n");
		}

		// 先暂时关闭日志输出
		ELogLevel level = m_eLogLevel;
		m_eLogLevel = E_LOGLEVEL_OFF;

		int nCacheIndex = (m_nCurrentCache + 1) % MAX_LOG_CACHE_COUNT;
		WriteLogFile(nCacheIndex);
		WriteLogFile(m_nCurrentCache);

		// 恢复原来日志级别
		m_eLogLevel = level;
	}

	VString VLoggerService::GetLogFilePath() const
	{
		VString strCachePath = VDir::getCachePath();
		VString strPath = strCachePath + "Log" + VDir::NATIVE_SEPARATOR;
		return strPath;
	}

	VString VLoggerService::GetFileName(const VString &strFilePath) const
	{
		int32_t pos = strFilePath.rfind(VDir::NATIVE_SEPARATOR) + 1;
		VString strName = strFilePath.substr(pos, strFilePath.length()-pos+1);
		return strName;
	}

	VString VLoggerService::MakeLogFileName(const VDateTime &rDateTime, const VString &strPath) const
	{
		char szName[256] = {0};
		snprintf(szName, sizeof(szName), "%s%u_%.4d-%.2d-%.2d_%.2d.log",
			strPath.c_str(), m_nAppID, rDateTime.Year(), rDateTime.Month(), rDateTime.Day(), rDateTime.Hour());
		return VString(szName);
	}

	void VLoggerService::ClearLogCache(int nCacheIndex /* = -1 */)
	{
		if (nCacheIndex < 0)
		{
			int i = 0;
			for (i = 0; i < MAX_LOG_CACHE_COUNT; ++i)
			{
				while (!m_LogCache[i].empty())
				{
					VLoggerItem *item = m_LogCache[i].back();
					delete item;
					m_LogCache[i].pop_back();
				}
			}

			m_nCacheCurrentCapacity = 0;
		}
		else if (nCacheIndex < MAX_LOG_CACHE_COUNT)
		{
			while (!m_LogCache[nCacheIndex].empty())
			{
				VLoggerItem *item = m_LogCache[nCacheIndex].back();
				delete item;
				m_LogCache[nCacheIndex].pop_back();
			}
		}
	}

	void VLoggerService::SwitchCache()
	{
		VAutoLock locker(m_pWorkingMutex);
		m_nCurrentCache = (++m_nCurrentCache) % MAX_LOG_CACHE_COUNT;
		m_nCacheCurrentCapacity = 0;
	}

	void VLoggerService::StartAsyncTask()
	{
		if (VThread::getCurrentThreadID() == VThread::getMainThreadID())
		{
			if (isRunning() && isSuspend())
			{
				resume();
			}
			else if (!isRunning())
			{
				if (start())
				{
					m_eLogTask = E_LOGTASK_NONE;
				}
			}
		}
	}

	void VLoggerService::SubmitWriteLogTask()
	{
		if (m_eLogTask == E_LOGTASK_NONE)
		{
			// 如果当前异步线程空闲，提交异步线程处理写文件，如果不空闲，等待下次提交再处理
			// 这里可以合并两次写文件任务一次处理，因为这里隔一小段时间就会提交一次写文件任务
			VLoggerTaskWriteFile *pTask = new VLoggerTaskWriteFile();
			m_pTaskMutex->lock();
			m_TaskQueue.push_back(pTask);
			m_pTaskMutex->unlock();

			SwitchCache();
		}

		StartAsyncTask();
	}

	void VLoggerService::SubmitCheckLogTask()
	{
		VLoggerTaskCheckFile *pTask = new VLoggerTaskCheckFile();
		m_pTaskMutex->lock();
		m_TaskQueue.push_back(pTask);
		m_pTaskMutex->unlock();

		StartAsyncTask();
	}

	void VLoggerService::ProcessWriteLogTask(VLoggerTask *pTask)
	{
		m_eLogTask = E_LOGTASK_WRITE_FILE;

		m_pWorkingMutex->lock();
		int nCacheIndex = m_nCurrentCache;
		nCacheIndex = (++nCacheIndex) % MAX_LOG_CACHE_COUNT;

		WriteLogFile(nCacheIndex);
        m_pWorkingMutex->unlock();

		V_SAFE_DELETE(pTask);

		m_eLogTask = E_LOGTASK_NONE;
	}

	void VLoggerService::ProcessCheckLogTask(VLoggerTask *pTask)
	{
		m_eLogTask = E_LOGTASK_CHECK_FILE;

		// 获取当前时间
		uint64_t t = VDateTime::currentSecsSinceEpoch();
		
		VDir dir;
		VString strLogPath = GetLogFilePath();

		// 遍历log目录下文件，删除过期文件
		VString strPath = strLogPath + "/*.log";
		bool bWorking = dir.findFile(strPath);
		while (bWorking)
		{
			bWorking = dir.findNextFile();
            
            if (bWorking)
            {
                std::string strFileName = dir.getFileName();
                CheckLogFile(dir, t);
            }
		}

		dir.close();

		V_SAFE_DELETE(pTask);

		m_eLogTask = E_LOGTASK_NONE;
	}

	ELogLevel VLoggerService::GetLogLevelFromString(const VString &strLevel) const
	{
		ELogLevel level = E_LOGLEVEL_OFF;

		if (strLevel == V_LOG_LEVEL_OFF)
		{
			level = E_LOGLEVEL_OFF;
		}
		else if (strLevel == V_LOG_LEVEL_EVENT)
		{
			level = E_LOGLEVEL_EVENT;
		}
		else if (strLevel == V_LOG_LEVEL_INFO)
		{
			level = E_LOGLEVEL_INFO;
		}
		else if (strLevel == V_LOG_LEVEL_DEBUG)
		{
			level = E_LOGLEVEL_DEBUG;
		}

		return level;
	}

	VString VLoggerService::GetLogLevelString(ELogLevel eLevel) const
	{
		switch (eLevel)
		{
		case E_LOGLEVEL_OFF:
			return V_LOG_LEVEL_OFF;
			break;
		case E_LOGLEVEL_EVENT:
			return V_LOG_LEVEL_EVENT;
			break;
		case E_LOGLEVEL_INFO:
			return V_LOG_LEVEL_INFO;
			break;
		case E_LOGLEVEL_DEBUG:
			return V_LOG_LEVEL_DEBUG;
			break;
		default:
			return V_LOG_LEVEL_OFF;
			break;
		}
	}

	uint32_t VLoggerService::GetCurrentLogFileSize() const
	{
		VString strLogFilePath = GetLogFilePath();
		VDateTime dt = VDateTime::currentDateTime();
		VString strFilePath = MakeLogFileName(dt, strLogFilePath);

		uint32_t unFileSize = 0;
		VFileDataStream fs;
		if (fs.open(strFilePath.c_str(), VFileDataStream::E_MODE_READ_ONLY))
		{
			unFileSize = fs.size();
			fs.close();
		}

		return unFileSize;
	}
}


