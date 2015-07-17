

#ifndef __VISION_LOGGER_ITEM_H__
#define __VISION_LOGGER_ITEM_H__


#include "VType.h"
#include "VDateTime.h"


namespace VPlatform
{
	class VFileDataStream;
	class VDateTime;
}

namespace VLoggerSystem
{
	using namespace VPlatform;

	class VLoggerItem
	{
	protected:
		int32_t	m_nHour;
		char	*m_pData;
		int32_t	m_nDataLen;

	public:
		VLoggerItem(const VString &strFileName, int32_t nFileLine, const VString &strLevel, 
			const VString &strModule, const char *lpszContent, int32_t nContentLength);
		~VLoggerItem();

		VLoggerItem(const VLoggerItem &other);
		VLoggerItem &operator =(const VLoggerItem &other);

		int32_t GetHour() const	{ return m_nHour; }

		void OutputConsole() const;
		int32_t OutputFile(VFileDataStream &fs) const;

		int32_t GetItemCapacity() const
		{
			return m_nDataLen;
		}

	protected:
		int32_t CalcCapacity(const VString &strFileName, const VString strLevel, const VString &strModule, int32_t nContentLength) const;
		void FormatBuffer(const VDateTime &rDateTime, const VString &strFileName, int32_t nFileLine, const VString &strLevel,
			const VString &strModule, const char *pContent, int32_t nContentLength);

		void SaveStringCopy(const char *pSrc, char *pDst, int32_t nLength);
		void Copy(const VLoggerItem &other);
	};
}



#endif	/*__VISION_LOGGER_ITEM_H__*/
