

#ifndef __VISION_TIMER_CONTAINER_WIN32_H__
#define __VISION_TIMER_CONTAINER_WIN32_H__


#include "VSingleton.h"
#include <map>


namespace VPlatform
{
	class VTimerAdapter;

	class VTimerContainer : public VSingleton<VTimerContainer>
	{
		V_DISABLE_COPY(VTimerContainer);

	public:
		VTimerContainer();
		virtual ~VTimerContainer();

		bool insertTimer(uint32_t unTimerID, VTimerAdapter *pTimer);
		void removeTimer(uint32_t unTimerID);
		VTimerAdapter *getTimerAdapter(uint32_t unTimerID);

	protected:
		typedef std::pair<uint32_t, VTimerAdapter*>	VTimerPair;
		typedef std::map<uint32_t, VTimerAdapter*>	VTimerMap;

		VTimerMap	m_TimerMap;
	};
}


#endif	/*__VISION_TIMER_CONTAINER_WIN32_H__*/
