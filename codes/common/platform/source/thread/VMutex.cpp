

#include "VMutex.h"
#include "VDateTime.h"


namespace VPlatform
{
	VMutex::VMutex(RecursionMode eMode /* = NonRecursive */)
		: m_eMode(eMode)
	{
		pthread_mutexattr_init(&m_attr);
		if (Recursive == eMode)
		{
			pthread_mutexattr_settype(&m_attr, PTHREAD_MUTEX_RECURSIVE);  
		}		
		pthread_mutex_init(&m_mutex, &m_attr);
	}

	VMutex::~VMutex()
	{
		pthread_mutexattr_destroy(&m_attr);
		pthread_mutex_destroy(&m_mutex);
	}

	bool VMutex::isRecursive() const
	{
		return (Recursive == m_eMode);
	}

	void VMutex::lock()
	{
		pthread_mutex_lock(&m_mutex);
	}

	bool VMutex::tryLock(uint32_t unTimeout /* = 0 */)
	{
		int nResult = 0;

		if (0 == unTimeout)
		{
			nResult = pthread_mutex_trylock(&m_mutex);
		}
		else
		{
			uint64_t llTimestamp = VDateTime::currentMSecsSinceEpoch();
			llTimestamp += unTimeout;
			struct timespec ts;
			ts.tv_sec = (long)llTimestamp / 1000;
			ts.tv_nsec = (long)llTimestamp % 1000 * 1000;
#if defined(V_OS_IOS) || defined(V_OS_ANDROID)
			nResult = pthread_mutex_trylock(&m_mutex);
#else
			nResult = pthread_mutex_timedlock(&m_mutex, &ts);
#endif
		}

		return (nResult == 0);
	}

	void VMutex::unlock()
	{
		pthread_mutex_unlock(&m_mutex);
	}
}


