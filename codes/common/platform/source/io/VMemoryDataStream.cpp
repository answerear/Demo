

#include "VMemoryDataStream.h"


namespace VPlatform
{
	VMemoryDataStream::VMemoryDataStream(uchar_t *pBuffer, size_t unSize)
		: m_pBuffer(NULL)
		, m_lSize(0)
		, m_lCurPos(0)
		, m_bCreated(false)
	{

	}

	VMemoryDataStream::VMemoryDataStream(size_t unSize /* = V_MEMORY_DATA_STREAM_BUFFER_SIZE */)
		: m_pBuffer(NULL)
		, m_lSize(0)
		, m_lCurPos(0)
		, m_bCreated(true)
	{
		m_pBuffer = new uchar_t[unSize];
	}

	VMemoryDataStream::VMemoryDataStream(const VMemoryDataStream &other)
	{
		copy(other);
	}

	VMemoryDataStream::~VMemoryDataStream()
	{
		if (m_bCreated)
		{
			V_SAFE_DELETE_ARRAY(m_pBuffer);
			m_pBuffer = NULL;
		}
	}

	VMemoryDataStream &VMemoryDataStream::operator=(const VMemoryDataStream &other)
	{
		copy(other);
		return *this;
	}

	size_t VMemoryDataStream::read(void *pBuffer, size_t nSize)
	{
		long_t lLeft = m_lSize - m_lCurPos - 1;
		long_t lBytesOfRead = (long_t)nSize > lLeft ? lLeft : (long_t)nSize;
		memcpy(pBuffer, m_pBuffer + m_lCurPos, lBytesOfRead);
		m_lCurPos += lBytesOfRead;
		return lBytesOfRead;
	}

	size_t VMemoryDataStream::write(void *pBuffer, size_t nSize)
	{
		long_t lSpace = m_lSize - m_lCurPos - 1;
		long_t lBytesOfWritten = (long_t)nSize > lSpace ? lSpace : (long_t)nSize;
		memcpy(m_pBuffer + m_lCurPos, pBuffer, lBytesOfWritten);
		m_lCurPos += lBytesOfWritten;
		return lBytesOfWritten;
	}

	void VMemoryDataStream::seek(long_t lPos)
	{
		m_lCurPos = lPos;
	}

	long_t VMemoryDataStream::tell() const
	{
		return m_lCurPos;
	}

	long_t VMemoryDataStream::size() const
	{
		return m_lSize;
	}

	bool VMemoryDataStream::eof() const
	{
		return (m_lCurPos == m_lSize - 1);
	}

	void VMemoryDataStream::copy(const VMemoryDataStream &other)
	{
		V_SAFE_DELETE_ARRAY(m_pBuffer);

		m_pBuffer = new uchar_t[other.m_lSize];
		memcpy(m_pBuffer, other.m_pBuffer, other.m_lSize);

		m_lSize = other.m_lSize;
		m_lCurPos = other.m_lCurPos;

		m_bCreated = true;
	}
}
