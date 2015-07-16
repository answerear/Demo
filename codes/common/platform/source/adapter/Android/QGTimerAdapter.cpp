

#include "QGTimerAdapter.h"
#include "ITimerObserver.h"
#include "QGConsoleAdapter.h"
#include "QGAndroidJNIHelper.h"

namespace QGLoggerSystem
{
	QGTimerAdapter::QTimerMap QGTimerAdapter::m_sTimerMap;

	QGTimerAdapter::QGTimerAdapter()
		: m_pObserver(NULL)
		, m_unTimerID(QG_INVALID_TIMER_ID)
	{

	}

	QGTimerAdapter::~QGTimerAdapter()
	{
		Stop();
	}

	uint32_t QGTimerAdapter::Start(uint32_t unInterval)
	{
		Stop();
		m_unTimerID=StartAndroidTimer(unInterval);
		m_sTimerMap.insert(QTimerPair(m_unTimerID, this));
		return m_unTimerID;
	}

	void QGTimerAdapter::Stop()
	{
		if (QG_INVALID_TIMER_ID != m_unTimerID)
		{
			m_sTimerMap.erase(m_unTimerID);
			KillAndroidTimer(m_unTimerID);
			m_unTimerID = QG_INVALID_TIMER_ID;
		}
	}

	void QGTimerAdapter::SetObserver(ITimerObserver *pObserver)
	{
		m_pObserver = pObserver;
	}

	uint32_t QGTimerAdapter::GetTimerID() const
	{
		return m_unTimerID;
	}

	void QGTimerAdapter::OnTimer(uint32_t uIDEvent)
	{
		LOGD("QGameLogSDK","OnTimer call id=%u\n",uIDEvent);
		QTimerMap::iterator itr = m_sTimerMap.find(uIDEvent);
		if (itr != m_sTimerMap.end())
		{
			if (itr->second->m_pObserver != NULL)
			{
				itr->second->m_pObserver->OnTimer(itr->first);
			}
		}
	}
}
