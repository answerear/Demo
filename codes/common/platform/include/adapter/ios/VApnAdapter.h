

#ifndef __QQGAME_APN_ADAPTER_IOS_H__
#define __QQGAME_APN_ADAPTER_IOS_H__


#include "IApnAdapter.h"
#include "IApnAdapterObserver.h"


namespace VPlatform
{
    class VApnAdapter
        : public IApnAdapter
        , public IApnAdapterObserver
    {
        V_DISABLE_COPY(VApnAdapter);
        
    public:
        VApnAdapter();
        virtual ~VApnAdapter();
        
    protected:  // from IApnAdapter
        virtual void setObserver(IApnAdapterObserver *pObserver);
        
		virtual EApnType getApnType() const;
		virtual ECarrier getCarrier() const;
        
		virtual bool pingRoutes(const VString &strHost);
		virtual void cancelPingRoutes();
        
    protected:  // from IApnAdapterObserver
        virtual void onApnChanged(EApnType eLastApn, EApnType eCurrentApn);
		virtual void onPingResult(bool bReachable);
        
    protected:
        void *m_pOSAdapter;
        IApnAdapterObserver *m_pObserver;
    };
}


#endif	/*__QQGAME_APN_ADAPTER_IOS_H__*/
