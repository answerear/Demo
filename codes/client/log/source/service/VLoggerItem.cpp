
#include "VLoggerItem.h"
#include "VConsole.h"
#include "VFileDataStream.h"
#include "VThread.h"


namespace VLoggerSystem
{
	VLoggerItem::VLoggerItem(const VString &strFileName, int32_t nFileLine, const VString &strLevel, const VString &strModule, const char *lpszContent, int32_t nContentLength)
		: m_nHour(0)
		, m_pData(NULL)
		, m_nDataLen(0)
	{
		VDateTime dt = VDateTime::currentDateTime();
		m_nHour = dt.Hour();
		FormatBuffer(dt, strFileName, nFileLine, strLevel, strModule, lpszContent, nContentLength);
	}

	VLoggerItem::VLoggerItem(const VLoggerItem &other)
	{
		Copy(other);
	}

	VLoggerItem::~VLoggerItem()
	{
		V_SAFE_DELETE_ARRAY(m_pData);
	}

	VLoggerItem &VLoggerItem::operator=(const VLoggerItem &other)
	{
		Copy(other);
		return *this;
	}

	void VLoggerItem::OutputConsole() const
	{
		V_CONSOLE.print(m_pData);
	}

	int32_t VLoggerItem::OutputFile(VFileDataStream &fs) const
	{
		int32_t p1 = fs.tell();
		fs<<m_pData;
		// 		fs.Write((unsigned char*)m_pData,m_nDataLen);
		int32_t p2 = fs.tell();
		return p2 - p1;
	}

	int32_t VLoggerItem::CalcCapacity(
		const VString &strFileName, 
		const VString strLevel, 
		const VString &strModule, 
		int32_t nContentLength) const
	{
		const int32_t nDateSize = 10;
		const int32_t nTimeSize = 12;
		int32_t nLevelSize = strLevel.length();
		const int32_t nThreadSize = 8;
		int32_t nFileSize = strFileName.length();
		const int32_t nLineSize = 4;
		int32_t nModuleSize = strModule.length();
		const int32_t nExtraSize = 6;
		const int32_t nEndLineSize = 1;
		return (nDateSize+nTimeSize+nLevelSize+nThreadSize+nFileSize+nLineSize+nModuleSize+nExtraSize+nContentLength+nEndLineSize);
	}

	void VLoggerItem::FormatBuffer(
		const VDateTime &rDateTime, 
		const VString &strFileName, 
		int32_t nFileLine, 
		const VString &strLevel, 
		const VString &strModule, 
		const char *pContent, 
		int32_t nContentLength)
	{
		int32_t nSize = CalcCapacity(strFileName, strLevel, strModule, nContentLength);
		int32_t nBufSize = 4;

		int32_t nDataLen = nSize + nBufSize;

		m_pData = new char[nSize+nBufSize];
		// 		m_nDataLen = nSize+1;

		void *pThreadID = VThread::getCurrentThreadID().getID();

		//#ifdef QG_OS_WIN32
		int nRet = snprintf(m_pData, nDataLen, "%.4d-%.2d-%.2d %.2d:%.2d:%.2d.%.3d %s|%x|%s:%d|%s|%s\n",
			rDateTime.Year(), rDateTime.Month(), rDateTime.Day(),
			rDateTime.Hour(), rDateTime.Minute(), rDateTime.Second(), rDateTime.Millisecond(),
			strLevel.c_str(), pThreadID, strFileName.c_str(), nFileLine,
			strModule.c_str(), pContent);

		m_nDataLen = nRet;
		// 		if (nRet > nSize)
		// 		{
		// 			nRet = nSize;
		// 		}
		// 		else if (nRet < 0)
		// 		{
		// 			nRet = nSize;
		// 			m_pData[nSize-1] = '\n';
		// 		}
		// 
		// 		m_pData[nRet] = 0;
		//#else
		//		m_nDataLen = nSize + 1;
		//		int nRet = snprintf(m_pData, nDataLen, "%.4d-%.2d-%.2d %.2d:%.2d:%.2d.%.3d %s|%x|%s:%d|%s|%s",
		//			rDateTime.Year(), rDateTime.Month(), rDateTime.Day(),
		//			rDateTime.Hour(), rDateTime.Minute(), rDateTime.Second(), rDateTime.Millisecond(),
		//			strLevel.c_str(), pThreadID, strFileName.c_str(), nFileLine,
		//			strModule.c_str(), pContent);
		//        
		//        if (nRet > nSize || nRet < 0)
		//        {
		//            nRet = nSize;
		//        }
		//        
		//        m_pData[nRet] = '\n';
		//        m_pData[nRet+1] = 0;
		//#endif
	}

	void VLoggerItem::SaveStringCopy(const char *pSrc, char *pDst, int32_t nLength) 
	{
		if (pSrc != NULL)
		{
			int nSize = strlen(pSrc);
			nSize = (nLength < nSize ? nLength - 1 : nSize);
			strncpy(pDst, pSrc, nSize);
			pDst[nSize] = 0;
		}
		else
		{
			V_SAFE_DELETE_ARRAY(pDst);
		}
	}

	void VLoggerItem::Copy(const VLoggerItem &other)
	{
		m_nHour = other.m_nHour;
		m_nDataLen = other.m_nDataLen;
		V_SAFE_DELETE_ARRAY(m_pData);
		m_pData = new char[m_nDataLen];

		SaveStringCopy(other.m_pData, m_pData, other.m_nDataLen);
	}
}
