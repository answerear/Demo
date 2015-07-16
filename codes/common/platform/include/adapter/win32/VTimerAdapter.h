

#ifndef __VISION_TIMER_WIN32_H__
#define __VISION_TIMER_WIN32_H__


#include "ITimerAdapter.h"
#include <map>
#include <windows.h>

namespace VPlatform
{
	class VTimerAdapter : public ITimerAdapter
	{
	public:
		VTimerAdapter();
		virtual ~VTimerAdapter();

		V_DISABLE_COPY(VTimerAdapter);

	protected:
		virtual uint32_t start(uint32_t unInterval);
		virtual void stop();
		virtual void setObserver(ITimerObserver *pObserver);
		virtual uint32_t getTimerID() const;

	private:
		static void CALLBACK onTimer(HWND hWnd, UINT uMsg, UINT_PTR uIDEvent, DWORD dwTime);

	private:
		ITimerObserver		*m_pObserver;
		uint32_t			m_unTimerID;
	};
}


#endif	/*__VISION_TIMER_WIN32_H__*/
