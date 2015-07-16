

#include "VDataStream.h"


namespace VPlatform
{
	VDataStream &VDataStream::operator<<(bool val)
	{
		write(&val, sizeof(val));
		return *this;
	}

	VDataStream &VDataStream::operator<<(int8_t val)
	{
		write(&val, sizeof(val));
		return *this;
	}

	VDataStream &VDataStream::operator<<(uint8_t val)
	{
		write(&val, sizeof(val));
		return *this;
	}

	VDataStream &VDataStream::operator<<(int16_t val)
	{
		write(&val, sizeof(val));
		return *this;
	}

	VDataStream &VDataStream::operator<<(uint16_t val)
	{
		write(&val, sizeof(val));
		return *this;
	}

	VDataStream &VDataStream::operator<<(int32_t val)
	{
		write(&val, sizeof(val));
		return *this;
	}

	VDataStream &VDataStream::operator<<(uint32_t val)
	{
		write(&val, sizeof(val));
		return *this;
	}

	VDataStream &VDataStream::operator<<(int64_t val)
	{
		write(&val, sizeof(val));
		return *this;
	}

	VDataStream &VDataStream::operator<<(uint64_t val)
	{
		write(&val, sizeof(val));
		return *this;
	}

	VDataStream &VDataStream::operator<<(float val)
	{
		write(&val, sizeof(val));
		return *this;
	}

	VDataStream &VDataStream::operator<<(double val)
	{
		write(&val, sizeof(val));
		return *this;
	}

	VDataStream &VDataStream::operator<<(const char *s)
	{
		size_t nLen = strlen(s);
		if (nLen > 0)
		{
			write((void*)s, nLen);
		}
		return *this;
	}

	VDataStream &VDataStream::operator<<(const VString &s)
	{
		size_t nLength = s.length();
		if (nLength > 0)
		{
			write((void*)s.c_str(), nLength);
		}
		char c = 0;
		write(&c, sizeof(c));
		return *this;
	}


	VDataStream &VDataStream::operator>>(bool &val)
	{
		read(&val, sizeof(val));
		return *this;
	}

	VDataStream &VDataStream::operator>>(int8_t &val)
	{
		read(&val, sizeof(val));
		return *this;
	}

	VDataStream &VDataStream::operator>>(uint8_t &val)
	{
		read(&val, sizeof(val));
		return *this;
	}

	VDataStream &VDataStream::operator>>(int16_t &val)
	{
		read(&val, sizeof(val));
		return *this;
	}

	VDataStream &VDataStream::operator>>(uint16_t &val)
	{
		read(&val, sizeof(val));
		return *this;
	}

	VDataStream &VDataStream::operator>>(int32_t &val)
	{
		read(&val, sizeof(val));
		return *this;
	}

	VDataStream &VDataStream::operator>>(uint32_t &val)
	{
		read(&val, sizeof(val));
		return *this;
	}

	VDataStream &VDataStream::operator>>(int64_t &val)
	{
		read(&val, sizeof(val));
		return *this;
	}

	VDataStream &VDataStream::operator>>(uint64_t &val)
	{
		read(&val, sizeof(val));
		return *this;
	}

	VDataStream &VDataStream::operator>>(float &val)
	{
		read(&val, sizeof(val));
		return *this;
	}

	VDataStream &VDataStream::operator>>(double &val)
	{
		read(&val, sizeof(val));
		return *this;
	}

	VDataStream &VDataStream::operator>>(char *&s)
	{
		char c;
		VString str;
		size_t nNumberOfRead = 0;
		size_t nSize = 0;

		do 
		{
			size_t nBytes = read(&c, sizeof(c));
			str += c;
			nNumberOfRead += nBytes;
			nSize++;
		} while (!eof() && c != 0);

		s = new char[nSize+1];
		memcpy(s, str.c_str(), nSize);

		return *this;
	}

	VDataStream &VDataStream::operator>>(VString &s)
	{
		char c;
		size_t nNumberOfRead = 0;
		s.clear();

		do 
		{
			size_t nBytes = read(&c, sizeof(c));
			s += c;
			nNumberOfRead += nBytes;
		} while (!eof() && c != 0);

		return *this;
	}
}
