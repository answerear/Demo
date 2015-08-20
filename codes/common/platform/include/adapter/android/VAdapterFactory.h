#ifndef __VISION_ADAPTER_FACTORY_ANDROID_H__
#define __VISION_ADAPTER_FACTORY_ANDROID_H__


#include "IAdapterFactory.h"


namespace VPlatform
{
	class VAdapterFactory : public IAdapterFactory
	{
		V_DISABLE_COPY(VAdapterFactory);

	public:
		VAdapterFactory();

	protected:
		virtual IConsoleAdapter *CreateConsoleAdapter();
		virtual ITimerAdapter *CreateTimerAdapter();
		virtual IDirAdapter *CreateDirAdapter();
		virtual IApnAdapter *CreateApnAdapter();
		virtual EPlatform GetPlatform();
	};
}

#endif	/*__VISION_ADAPTER_FACTORY_ANDROID_H__*/