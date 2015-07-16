

#ifndef __QQGAME_TIMER_ADAPTER_IOS_H__
#define __QQGAME_TIMER_ADAPTER_IOS_H__


#include "ITimerAdapter.h"


namespace VPlatform
{
    class VTimerAdapter : public ITimerAdapter
    {
        V_DISABLE_COPY(VTimerAdapter);
        
    public:
        VTimerAdapter();
        virtual ~VTimerAdapter();
        
    protected:
        virtual uint32_t start(uint32_t unInterval);
		virtual void stop();
		virtual void setObserver(ITimerObserver *pObserver);
		virtual uint32_t getTimerID() const;
        
    public:
        ITimerObserver  *m_pObserver;
        uint32_t        m_unTimerID;
        
    protected:
        void            *m_pTimer;
    };
}


#endif	/*__QQGAME_TIMER_ADAPTER_IOS_H__*/
