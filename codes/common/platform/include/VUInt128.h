
#ifndef __VISION_UINT_128_H__
#define __VISION_UINT_128_H__


class __uint128_t
{
public:
	__uint128_t()
		: low(0)
		, high(0)
	{}

	__uint128_t(uint64_t l, uint64_t h)
		: low(l)
		, high(h)
	{}

	__uint128_t(const __uint128_t &other)
	{
		low = other.low;
		high = other.high;
	}

	bool operator ==(const __uint128_t &other) const
	{
		return (low == other.low && high == other.high);
	}

	bool operator !=(const __uint128_t &other) const
	{
		return (low != other.low || high != other.high);
	}

	bool operator <(const __uint128_t &other) const
	{
		return (high < other.high || (low < other.low && high == other.high));
	}

	uint64_t	low;
	uint64_t	high;
};


#endif	/*__VISION_UINT_128_H__*/
