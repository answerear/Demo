

#include "VAdapterFactory.h"
#include "VConsoleAdapter.h"
#include "VTimerAdapter.h"
#include "VDirAdapter.h"
#include "VApnAdapter.h"
#include "VDeviceInfoAdapter.h"
#include "VTimerContainer.h"


namespace VPlatform
{
	IAdapterFactory *createAdapterFactory()
	{
		return new VAdapterFactory();
	}

	VAdapterFactory::VAdapterFactory()
		: m_pTimerContainer(new VTimerContainer())
	{

	}

	VAdapterFactory::~VAdapterFactory()
	{
		V_SAFE_DELETE(m_pTimerContainer);
	}

	IConsoleAdapter *VAdapterFactory::createConsoleAdapter()
	{
		return new VConsoleAdapter();
	}

	ITimerAdapter *VAdapterFactory::createTimerAdapter()
	{
		return new VTimerAdapter();
	}

	IDirAdapter *VAdapterFactory::createDirAdapter()
	{
		return new VDirAdapter();
	}

	IApnAdapter *VAdapterFactory::createApnAdapter()
	{
		return new VApnAdapter();
	}

	IDeviceInfoAdapter *VAdapterFactory::createDeviceInfoAdapter()
	{
		return new VDeviceInfoAdapter();
	}

	EPlatform VAdapterFactory::getPlatform()
	{
		return E_PLATFORM_WIN32;
	}
}

