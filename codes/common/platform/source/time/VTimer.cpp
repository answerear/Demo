

#include "VTimer.h"
#include "VSystem.h"
#include "VAdapterFactory.h"
#include "ITimerAdapter.h"


namespace VPlatform
{
	VTimer::VTimer()
		: m_pAdapter(NULL)
	{
		m_pAdapter = V_ADAPTER_FACTORY.createTimerAdapter();
	}

	VTimer::~VTimer()
	{
		V_SAFE_DELETE(m_pAdapter);
	}

	uint32_t VTimer::start(uint32_t unInterval)
	{
		if (NULL != m_pAdapter)
		{
			m_pAdapter->stop();
			return m_pAdapter->start(unInterval);
		}

		return V_INVALID_TIMER_ID;
	}

	void VTimer::stop()
	{
		if (NULL != m_pAdapter)
		{
			return m_pAdapter->stop();
		}
	}

	void VTimer::setObserver(ITimerObserver *pObserver)
	{
		if (NULL != m_pAdapter)
		{
			m_pAdapter->setObserver(pObserver);
		}
	}

	uint32_t VTimer::getTimerID() const
	{
		if (NULL != m_pAdapter)
		{
			return m_pAdapter->getTimerID();
		}

		return V_INVALID_TIMER_ID;
	}
}
