
#ifndef __VISION_ADAPTER_FACTORY_WIN32_H__
#define __VISION_ADAPTER_FACTORY_WIN32_H__


#include "IAdapterFactory.h"


namespace VPlatform
{
	class VTimerContainer;

	class VAdapterFactory : public IAdapterFactory
	{
		V_DISABLE_COPY(VAdapterFactory);

	public:
		VAdapterFactory();
		virtual ~VAdapterFactory();

	protected:
		virtual IConsoleAdapter *createConsoleAdapter();
		virtual ITimerAdapter *createTimerAdapter();
		virtual IDirAdapter *createDirAdapter();
		virtual IApnAdapter *createApnAdapter();
		virtual IDeviceInfoAdapter *createDeviceInfoAdapter();

		virtual EPlatform getPlatform();

	protected:
		VTimerContainer	*m_pTimerContainer;
	};
}


#endif	/*__VISION_ADAPTER_FACTORY_WIN32_H__*/
