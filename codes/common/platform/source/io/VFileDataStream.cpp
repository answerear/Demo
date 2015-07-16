

#include "VFileDataStream.h"


namespace VPlatform
{
	VFileDataStream::VFileDataStream()
		: m_pFileHandle(NULL)
		, m_lSize(0)
	{

	}

	VFileDataStream::~VFileDataStream()
	{
		close();
	}

	bool VFileDataStream::open(const char *szFileName, uint32_t unMode)
	{
		if (unMode == E_MODE_READ_ONLY)
		{
			m_pFileHandle = fopen(szFileName, "rb");
		}
		else if (unMode == E_MODE_WRITE_ONLY)
		{
			m_pFileHandle = fopen(szFileName, "wb");
		}
		else if (unMode == (E_MODE_WRITE_ONLY|E_MODE_APPEND)
			|| unMode == E_MODE_APPEND)
		{
			m_pFileHandle = fopen(szFileName, "ab");
		}
		else if (unMode == E_MODE_READ_WRITE)
		{
			m_pFileHandle = fopen(szFileName, "r+b");
		}
		else if (unMode == (E_MODE_READ_WRITE|E_MODE_TRUNCATE))
		{
			m_pFileHandle = fopen(szFileName, "w+b");
		}
		else if (unMode == (E_MODE_READ_WRITE|E_MODE_APPEND))
		{
			m_pFileHandle = fopen(szFileName, "a+b");
		}
		else if (unMode == (E_MODE_READ_ONLY|E_MODE_TEXT))
		{
			m_pFileHandle = fopen(szFileName, "r+t");
		}
		else if (unMode == (E_MODE_WRITE_ONLY|E_MODE_TEXT))
		{
			m_pFileHandle = fopen(szFileName, "w+t");
		}
		else if (unMode == (E_MODE_WRITE_ONLY|E_MODE_APPEND|E_MODE_TEXT)
			|| unMode == (E_MODE_APPEND|E_MODE_TEXT))
		{
			m_pFileHandle = fopen(szFileName, "a+t");
		}
		else if (unMode == (E_MODE_READ_WRITE|E_MODE_TEXT))
		{
			m_pFileHandle = fopen(szFileName, "r+t");
		}
		else if (unMode == (E_MODE_READ_WRITE|E_MODE_TRUNCATE|E_MODE_TEXT))
		{
			m_pFileHandle = fopen(szFileName, "w+t");
		}
		else if (unMode == (E_MODE_READ_WRITE|E_MODE_APPEND|E_MODE_TEXT))
		{
			m_pFileHandle = fopen(szFileName, "a+t");
		}

		m_lSize = 0;
		return (m_pFileHandle != NULL);
	}

	void VFileDataStream::close()
	{
		if (m_pFileHandle != NULL)
		{
			fflush(m_pFileHandle);
			fclose(m_pFileHandle);
			m_pFileHandle = NULL;
		}

		m_lSize = 0;
	}

	size_t VFileDataStream::read(void *pBuffer, size_t nSize)
	{
		size_t nBytesOfRead = 0;

		if (m_pFileHandle != NULL)
		{
			nBytesOfRead = fread(pBuffer, 1, nSize, m_pFileHandle);
		}

		return nBytesOfRead;
	}

	size_t VFileDataStream::write(void *pBuffer, size_t nSize)
	{
		size_t nBytesOfWritten = 0;

		if (m_pFileHandle != NULL)
		{
			nBytesOfWritten = fwrite(pBuffer, 1, nSize, m_pFileHandle);
		}

		return nBytesOfWritten;
	}

	void VFileDataStream::flush()
	{
		if (m_pFileHandle != NULL)
		{
			fflush(m_pFileHandle);
		}
	}

	void VFileDataStream::seek(long_t lPos)
	{
		if (m_pFileHandle != NULL)
		{
			fseek(m_pFileHandle, lPos, SEEK_SET);
		}
	}

	long_t VFileDataStream::tell() const
	{
		long_t lPos = 0;

		if (m_pFileHandle != NULL)
		{
			lPos = ftell(m_pFileHandle);
		}

		return lPos;
	}

	long_t VFileDataStream::size() const
	{
		if (m_pFileHandle != NULL)
		{
			if (m_lSize == 0)
			{
				long_t lPos = ftell(m_pFileHandle);
				fseek(m_pFileHandle, 0, SEEK_END);
				m_lSize = ftell(m_pFileHandle);
				fseek(m_pFileHandle, lPos, SEEK_SET);
			}
		}

		return m_lSize;
	}

	bool VFileDataStream::eof() const
	{
		bool bEnd = true;

		if (m_pFileHandle != NULL)
		{
			uint32_t unPos = ftell(m_pFileHandle);
			uint32_t unSize = size();
			bEnd = (unPos == unSize - 1);
		}

		return bEnd;
	}
}
