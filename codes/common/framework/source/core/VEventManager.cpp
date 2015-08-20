

#include "VEventManager.h"
#include "VEventParam.h"
#include "VEventHandler.h"



template<> VFramework::VEventManager *VSingleton<VFramework::VEventManager>::m_pInstance = NULL;


namespace VFramework
{	
	VEventManager::VEventManager(uint32_t unMaxEvents)
		: m_nCurrentQueue(0)
	{
		m_EventHandlers.reserve(128);
		m_EventHandlers.resize(128);
		m_EventFilters.reserve(unMaxEvents);
		m_EventFilters.resize(unMaxEvents);
	}

	VEventManager::~VEventManager()
	{
		m_EventHandlers.clear();
		clearEventQueue();
	}

	bool VEventManager::sendEvent(uint32_t unEventID, VEventParam *pEventParam, const VINSTANCE &receiver, const VINSTANCE &sender, int32_t nType)
	{
		if (V_INVALID_INSTANCE_ID == receiver)
			return false;

		bool bRet = false;

		if (V_BROADCAST_INSTANCE_ID == receiver)
		{
			// 广播
			VAutoLock locker(m_mutex);
			int32_t i = 0;
			for (i = 0; i < (int32_t)m_EventHandlers.size(); ++i)
			{
				VEventHandler *pHandler = m_EventHandlers[i];
				if(NULL != pHandler)
				{
					if (nType == pHandler->handlerType())
					{
						pHandler->processEvent(unEventID, pEventParam, sender);
					}
				}
			}

			bRet = true;
		}
		else
		{
			VAutoLock locker(m_mutex);

			// 发送给指定对象
			VEventHandler *pReceiver = NULL;
			if (getEventHandler(receiver, pReceiver))
			{
				bRet = pReceiver->processEvent(unEventID, pEventParam, sender);
			}
		}

		return bRet;
	}

	bool VEventManager::postEvent(uint32_t unEventID, VEventParam *pEventParam, const VINSTANCE &receiver, const VINSTANCE &sender, int32_t nType)
	{
		if (V_INVALID_INSTANCE_ID == receiver)
			return false;

		bool bRet = false;

// 		if (V_BROADCAST_INSTANCE_ID != receiver)
		{
			VAutoLock locker(m_mutex);
			VEventParam *pCopy = NULL;

			if (pEventParam != NULL)
			{
				pCopy = pEventParam->clone();
			}

			VEventItem item(unEventID, pCopy, receiver, sender, nType);
			m_EventQueue[m_nCurrentQueue].push_back(item);

			bRet = true;
		}
// 		else
// 		{
// 			bRet = postEvent(unEventID, pEventParam, sender);
// 		}

		return bRet;
	}

	bool VEventManager::sendEvent(uint32_t unEventID, VEventParam *pEventParam, const VINSTANCE &sender)
	{
		bool bRet = false;

		VAutoLock handlerLocker(m_mutex);
		VAutoLock eventLocker(m_mutexEvent);

		if (unEventID < m_EventFilters.size())
		{
			VEventInstSet &instSet = m_EventFilters[unEventID];
			VEventInstSetItr itr = instSet.begin();

			// 广播发送给所有关注该事件的对象
			while (itr != instSet.end())
			{
				const VINSTANCE &receiver = *itr;
				VEventHandler *pReceiver = NULL;

				if (getEventHandler(receiver, pReceiver))
				{
					pReceiver->processEvent(unEventID, pEventParam, sender);
					bRet = true;
				}

				++itr;
			}
		}

		return bRet;
	}

	bool VEventManager::postEvent(uint32_t unEventID, VEventParam *pEventParam, const VINSTANCE &sender)
	{
		bool bRet = false;

		VAutoLock handlerLocker(m_mutex);
		VAutoLock eventLocker(m_mutexEvent);

		if (unEventID < m_EventFilters.size())
		{
			VEventInstSet &instSet = m_EventFilters[unEventID];
			VEventInstSetItr itr = instSet.begin();

			// 广播发送给所有关注该事件的对象
			while (itr != instSet.end())
			{
				const VINSTANCE &receiver = *itr;

				if (receiver != V_INVALID_INSTANCE_ID)
				{
					VEventParam *pCopy = NULL;

					if (pEventParam != NULL)
					{
						pCopy = pEventParam->clone();
					}

					VEventItem item(unEventID, pCopy, receiver, sender, 0);
					m_EventQueue[m_nCurrentQueue].push_back(item);

					bRet = true;
				}

				++itr;
			}
		}

		return bRet;
	}

	bool VEventManager::getEventHandler(VINSTANCE instance, VEventHandler *&pHandler)
	{
		bool bRet = false;
		int32_t index = instance.m_nIndex;
		void *address = instance.m_pObject;
		if (index >= 0 && index < m_EventHandlers.size()
			&& m_EventHandlers[index] != NULL && m_EventHandlers[index] == (VEventHandler *)address)
		{
			pHandler = (VEventHandler *)address;
			bRet = true;
		}

		return bRet;
	}

	bool VEventManager::isValidHandler(VEventHandler *pHandler)
	{
		bool bRet = false;
		VINSTANCE instance = pHandler->m_InstanceID;
		int32_t index = instance.m_nIndex;
		void *address = instance.m_pObject;
		if (index >= 0 && index < m_EventHandlers.size()
			&& m_EventHandlers[index] != NULL && m_EventHandlers[index] == (VEventHandler *)address)
		{
			bRet = true;
		}

		return bRet;
	}

	VINSTANCE VEventManager::registerHandler(VEventHandler *pHandler)
	{
		bool bFound = false;
		size_t index = 0;

		VAutoLock locker(m_mutex);

		// 先查找原来数组中是否有空位，如果有空位直接存入数组空位，没有则需要扩展数组大小
		VHandlerListItr itr = m_EventHandlers.begin();
		while (itr != m_EventHandlers.end())
		{
			if (*itr == NULL)
			{
				m_EventHandlers[index] = pHandler;
				bFound = true;
				break;
			}

			++itr;
			++index;
		}

		if (!bFound)
		{
			index = m_EventHandlers.size();
			m_EventHandlers.push_back(pHandler);
		}

		return VINSTANCE(pHandler, (uint32_t)index);
	}

	bool VEventManager::unregisterHandler(const VINSTANCE &instance)
	{
		if (V_INVALID_INSTANCE_ID == instance)
		{
			return false;
		}

		bool bRet = false;

		VAutoLock locker(m_mutex);

		int32_t index = instance.m_nIndex;
		void *address = instance.m_pObject;
		if (m_EventHandlers[index] == (VEventHandler*)address)
		{
			m_EventHandlers[index] = NULL;
			bRet = true;
		}

		return bRet;
	}

	bool VEventManager::registerEvent(uint32_t unEventID, const VINSTANCE &instance)
	{
		if (V_INVALID_INSTANCE_ID == instance)
			return false;

		bool bRet = false;

		VAutoLock locker(m_mutex);
		VAutoLock eventLocker(m_mutexEvent);

		if (unEventID < m_EventFilters.size())
		{
			VEventInstSet &instSet = m_EventFilters[unEventID];
			std::pair<VEventInstSetItr, bool> r = instSet.insert(instance);
			bRet = r.second;
		}

		return bRet;
	}

	bool VEventManager::unregisterEvent(uint32_t unEventID, const VINSTANCE &instance)
	{
		if (V_INVALID_INSTANCE_ID == instance)
			return false;

		bool bRet = false;

		VAutoLock locker(m_mutex);
		VAutoLock eventLocker(m_mutexEvent);

		if (unEventID < m_EventFilters.size())
		{
			VEventInstSet &instSet = m_EventFilters[unEventID];
			instSet.erase(instance);
			bRet = true;
		}

		return bRet;
	}

	bool VEventManager::peekEvent(VEventItem &Item, bool bRemovable /* = true */)
	{
		bool bRet = false;

		VAutoLock locker(m_mutex);
		if (!m_EventQueue[m_nCurrentQueue].empty())
		{
			VEventListItr itr = m_EventQueue[m_nCurrentQueue].begin();
			Item = *itr;
			if (bRemovable)
				m_EventQueue[m_nCurrentQueue].pop_front();
			bRet = true;
		}

		return bRet;
	}

	bool VEventManager::dispatchEvent()
	{
		VAutoLock locker(m_mutex, std::defer_lock);

		locker.lock();
		int32_t index = m_nCurrentQueue;
		m_nCurrentQueue = (++m_nCurrentQueue) % V_MAX_EVENT_QUEUE;
		locker.unlock();

		if (m_EventQueue[index].empty())
		{
			return false;
		}

		while (!m_EventQueue[index].empty())
		{
			VEventItem &item = m_EventQueue[index].front();

			if (V_BROADCAST_INSTANCE_ID == item.m_Receiver)
			{
				// 广播事件通知
				VHandlerListItr itr = m_EventHandlers.begin();
				while (itr != m_EventHandlers.end())
				{
					VEventHandler *&pHandler = *itr;
					if (pHandler != NULL)
					{
						if (item.m_nType == pHandler->handlerType())
						{
							pHandler->processEvent(item.m_unEventID, item.m_pEventParam, item.m_Sender);
						}
					}

					++itr;
				}
			}
			else
			{
				// 单个对象事件通知
				VEventHandler *pHandler = NULL;
				if (getEventHandler(item.m_Receiver, pHandler))
				{
					pHandler->processEvent(item.m_unEventID, item.m_pEventParam, item.m_Sender);
				}
			}

			delete item.m_pEventParam;
			m_EventQueue[index].pop_front();
		}

		return true;
	}

	void VEventManager::clearEventQueue()
	{
		int32_t i = 0;
		for (i = 0; i < V_MAX_EVENT_QUEUE; ++i)
		{
			VEventListItr itr = m_EventQueue[i].begin();
			while (itr != m_EventQueue[i].end())
			{
				VEventItem &item = *itr;
				delete item.m_pEventParam;
				++itr;
			}

			m_EventQueue[i].clear();
		}
	}
}
