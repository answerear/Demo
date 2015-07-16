

#include "VEventHandler.h"
#include "VEventManager.h"


namespace VFramework
{
	VEventHandler::VEventHandler(bool bAutoRegister /* = true */)
	{
		if (bAutoRegister)
		{
			m_InstanceID = V_EVENT_MANAGER.registerHandler(this);
		}
	}

	VEventHandler::~VEventHandler()
	{
		unregisterAllEvent();
		V_EVENT_MANAGER.unregisterHandler(m_InstanceID);
	}

	int32_t VEventHandler::handlerType() const
	{
		return 0;
	}

	bool VEventHandler::sendEvent(uint32_t unEventID, VEventParam *pEventParam, const VINSTANCE &receiver, int32_t nType /* = 0 */)
	{
		return V_EVENT_MANAGER.sendEvent(unEventID, pEventParam, receiver, m_InstanceID, nType);
	}

	bool VEventHandler::postEvent(uint32_t unEventID, VEventParam *pEventParam, const VINSTANCE &receiver, int32_t nType /* = 0 */)
	{
		return V_EVENT_MANAGER.postEvent(unEventID, pEventParam, receiver, m_InstanceID, nType);
	}

	bool VEventHandler::sendEventEx(uint32_t unEventID, VEventParam *pEventParam)
	{
		return V_EVENT_MANAGER.sendEvent(unEventID, pEventParam, m_InstanceID);
	}

	bool VEventHandler::postEventEx(uint32_t unEventID, VEventParam *pEventParam)
	{
		return V_EVENT_MANAGER.postEvent(unEventID, pEventParam, m_InstanceID);
	}

	VINSTANCE VEventHandler::registerHandler()
	{
		V_EVENT_MANAGER.unregisterHandler(m_InstanceID);
		m_InstanceID = V_EVENT_MANAGER.registerHandler(this);
		return m_InstanceID;
	}

	bool VEventHandler::unregisterHandler()
	{
		bool bRet = V_EVENT_MANAGER.unregisterHandler(m_InstanceID);
		m_InstanceID = V_INVALID_INSTANCE_ID;
		return bRet;
	}

	bool VEventHandler::processEvent(uint32_t unEventID, VEventParam *pEventParam, const VINSTANCE &sender)
	{
		return eventProc(unEventID, pEventParam, sender);
	}

	bool VEventHandler::eventProc(uint32_t EventID, VEventParam *pEventParam, const VINSTANCE &sender)
	{
		return true;
	}

	void VEventHandler::setupEventFilter()
	{

	}

	bool VEventHandler::registerEvent(uint32_t unEventID)
	{
		bool bRet = V_EVENT_MANAGER.registerEvent(unEventID, m_InstanceID);
		if (bRet)
		{
			m_EventList.push_back(unEventID);
		}

		return bRet;
	}

	bool VEventHandler::unregisterEvent(uint32_t unEventID)
	{
		bool bRet = V_EVENT_MANAGER.unregisterEvent(unEventID, m_InstanceID);

		if (bRet)
		{
			VEventListItr itr = m_EventList.begin();
			while (itr != m_EventList.end())
			{
				if (*itr == unEventID)
				{
					m_EventList.erase(itr);
					break;
				}

				++itr;
			}
		}

		return bRet;
	}

	void VEventHandler::unregisterAllEvent()
	{
		VEventListItr itr = m_EventList.begin();
		while (itr != m_EventList.end())
		{
			V_EVENT_MANAGER.unregisterEvent(*itr, m_InstanceID);
			++itr;
		}

		m_EventList.clear();
	}
}
