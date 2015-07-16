

#include "VTimerContainer.h"


template<> VPlatform::VTimerContainer *VSingleton<VPlatform::VTimerContainer>::m_pInstance = NULL;


namespace VPlatform
{
	VTimerContainer::VTimerContainer()
	{

	}

	VTimerContainer::~VTimerContainer()
	{

	}

	bool VTimerContainer::insertTimer(uint32_t unTimerID, VTimerAdapter *pTimer)
	{
		std::pair<VTimerMap::iterator, bool> p = m_TimerMap.insert(VTimerPair(unTimerID, pTimer));
		return p.second;
	}

	void VTimerContainer::removeTimer(uint32_t unTimerID)
	{
		VTimerMap::iterator itr = m_TimerMap.find(unTimerID);
		if (itr != m_TimerMap.end())
		{
			m_TimerMap.erase(itr);
		}
	}

	VTimerAdapter *VTimerContainer::getTimerAdapter(uint32_t unTimerID)
	{
		VTimerAdapter *pTimer = NULL;
		VTimerMap::iterator itr = m_TimerMap.find(unTimerID);
		
		if (itr != m_TimerMap.end())
		{
			pTimer = itr->second;
		}

		return pTimer;
	}
}
