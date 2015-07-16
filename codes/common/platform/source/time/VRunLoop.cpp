
#include "VRunLoop.h"
#include "VDateTime.h"
#include "IRunLoopObserver.h"


namespace VPlatform
{
	uint32_t VRunLoop::m_unLoopID = 0;

	VRunLoop::VRunLoop()
	{

	}

	VRunLoop::~VRunLoop()
	{

	}

	uint32_t VRunLoop::start(uint32_t unInterval, bool bRepeat, IRunLoopObserver *pObserver)
	{
		if (pObserver == NULL)
			return V_INVALID_LOOP_ID;

		uint32_t unLoopID = m_unLoopID + 1;
		uint64_t unTimestamp = VDateTime::currentMSecsSinceEpoch();
		RunLoopInfo info = {unTimestamp, unInterval, pObserver, bRepeat};
		std::pair<VRunLoopInfosItr, bool> r = m_infos.insert(VRunLoopValue(unLoopID, info));

		if (r.second)
		{
			m_unLoopID++;
		}

		return unLoopID;
	}

	uint32_t VRunLoop::start(IRunLoopObserver *pObserver)
	{
		if (pObserver == NULL)
			return V_INVALID_LOOP_ID;

		uint32_t unLoopID = m_unLoopID + 1;
		uint64_t unTimestamp = VDateTime::currentMSecsSinceEpoch();
		RunLoopInfo info = {unTimestamp, 0, pObserver, true};
		std::pair<VRunLoopInfosItr, bool> r = m_infos.insert(VRunLoopValue(unLoopID, info));

		if (r.second)
		{
			m_unLoopID++;
		}

		return unLoopID;
	}

	bool VRunLoop::stop(uint32_t unLoopID)
	{
		bool bRet = false;
		
		VRunLoopInfosItr itr = m_infos.find(unLoopID);
		
		if (itr != m_infos.end())
		{
			m_infos.erase(itr);
		}

		return bRet;
	}

	void VRunLoop::execute()
	{
		VRunLoopInfosItr itr = m_infos.begin();
		uint64_t ullTimestamp = VDateTime::currentMSecsSinceEpoch();

		while (itr != m_infos.end())
		{
			uint32_t unLoopID = itr->first;
			RunLoopInfo &info = itr->second;
			uint64_t dt = ullTimestamp - info.ullLastTimestamp;
			
			if (dt >= info.ullInterval)
			{
				/// 回调
				info.pObserver->onExecute(unLoopID, dt);
				info.ullLastTimestamp = ullTimestamp;
			}

			if (!info.bRepeat)
			{
				/// 不循环，那么就删掉咯
				m_infos.erase(itr++);
			}
			else
			{
				++itr;
			}			
		}
	}
}
