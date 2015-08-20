
#ifndef __QQGAME_APN_ADAPTER_ANDROID_H__
#define __QQGAME_APN_ADAPTER_ANDROID_H__


#include "IApnAdapter.h"

namespace VPlatform
{
	class VApnAdapter : public IApnAdapter
	{
		V_DISABLE_COPY(VApnAdapter);

	public:
		VApnAdapter();
		virtual ~VApnAdapter();

	protected:
		virtual void SetObserver(IApnAdapterObserver *pObserver);

		virtual EApnType GetApnType() const;
		virtual ECarrier GetCarrier() const;

		virtual bool PingRoutes(const VString &strHost);
		virtual void CancelPingRoutes();
	private:
        IApnAdapterObserver* m_pObserver;

		virtual void OnApnChanged(EApnType eLastApn, EApnType eCurrentApn);
		virtual void OnPingResult(bool bReachable);
	};
}


#endif	/*__QQGAME_APN_ADAPTER_ANDROID_H__*/
