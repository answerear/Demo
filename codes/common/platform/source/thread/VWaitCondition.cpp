

#include "VWaitCondition.h"
#include "VMutex.h"
#include "VDateTime.h"


namespace VPlatform
{
	VWaitCondition::VWaitCondition()
	{
		pthread_cond_init(&m_cond, NULL);
	}

	VWaitCondition::~VWaitCondition()
	{
		pthread_cond_destroy(&m_cond);
	}

	bool VWaitCondition::wait(VMutex *pMutex, uint32_t unTimeout /* = -1 */)
	{
		if (NULL == pMutex)
			return false;

		int nResult = 0;

		if (-1 == unTimeout)
		{
			nResult = pthread_cond_wait(&m_cond, &(pMutex->m_mutex));
		}
		else
		{
			uint64_t llTimestamp = VDateTime::currentMSecsSinceEpoch();
			llTimestamp += unTimeout;
			struct timespec ts;
			ts.tv_sec = (long)llTimestamp / 1000;
			ts.tv_nsec = (long)llTimestamp % 1000 * 1000;
			nResult = pthread_cond_timedwait(&m_cond, &(pMutex->m_mutex), &ts);
		}
		
		return (nResult == 0);
	}

	void VWaitCondition::wakeAll()
	{
		pthread_cond_broadcast(&m_cond);
	}

	void VWaitCondition::wakeOne()
	{
		pthread_cond_signal(&m_cond);
	}
}

