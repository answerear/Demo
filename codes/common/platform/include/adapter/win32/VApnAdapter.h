
#ifndef __VISION_APN_ADAPTER_WIN32_H__
#define __VISION_APN_ADAPTER_WIN32_H__


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
		virtual void setObserver(IApnAdapterObserver *pObserver);

		virtual EApnType getApnType() const;
		virtual ECarrier getCarrier() const;

		virtual bool pingRoutes(const VString &strHost);
		virtual void cancelPingRoutes();
	};
}


#endif	/*__VISION_APN_ADAPTER_WIN32_H__*/
