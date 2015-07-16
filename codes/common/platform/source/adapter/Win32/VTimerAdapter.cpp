

#include "VTimerAdapter.h"
#include "ITimerObserver.h"
#include "VTimerContainer.h"


namespace VPlatform
{
	VTimerAdapter::VTimerAdapter()
		: m_pObserver(NULL)
		, m_unTimerID(V_INVALID_TIMER_ID)
	{

	}

	VTimerAdapter::~VTimerAdapter()
	{
		stop();
	}

	UINT VTimerAdapter::start(UINT unInterval)
	{
		m_unTimerID = ::SetTimer(NULL, 1000, unInterval, VTimerAdapter::onTimer);

		if (VTimerContainer::GetInstancePtr() != NULL)
		{
			VTimerContainer::GetInstancePtr()->insertTimer(m_unTimerID, this);
		}

		return m_unTimerID;
	}

	void VTimerAdapter::stop()
	{
		if (V_INVALID_TIMER_ID != m_unTimerID)
		{
			if (VTimerContainer::GetInstancePtr() != NULL)
			{
				VTimerContainer::GetInstancePtr()->removeTimer(m_unTimerID);
			}

			::KillTimer(NULL, m_unTimerID);
			m_unTimerID = V_INVALID_TIMER_ID;
		}
	}

	void VTimerAdapter::setObserver(ITimerObserver *pObserver)
	{
		m_pObserver = pObserver;
	}

	UINT VTimerAdapter::getTimerID() const
	{
		return m_unTimerID;
	}

	void VTimerAdapter::onTimer(HWND hWnd, UINT uMsg, UINT_PTR uIDEvent, DWORD dwTime)
	{
		if (VTimerContainer::GetInstancePtr() != NULL)
		{
			VTimerAdapter *pTimer = VTimerContainer::GetInstancePtr()->getTimerAdapter(uIDEvent);
			if (pTimer != NULL)
			{
				if (pTimer->m_pObserver != NULL)
				{
					pTimer->m_pObserver->onTimer(pTimer->m_unTimerID);
				}
			}
		}
	}
}
