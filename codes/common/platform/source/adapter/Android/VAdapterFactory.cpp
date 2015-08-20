

#include "VAdapterFactory.h"
// #include "VConsoleAdapter.h"
// #include "VApnAdapter.h"
// #include "VTimerAdapter.h"
// #include "VDirAdapter.h"


namespace VPlatform
{
	IAdapterFactory *CreateAdapterFactory()
	{
		return new VAdapterFactory;
	}

	VAdapterFactory::VAdapterFactory()
	{

	}

	IConsoleAdapter *VAdapterFactory::CreateConsoleAdapter()
	{
		 return new VConsoleAdapter();
	}

	ITimerAdapter *VAdapterFactory::CreateTimerAdapter()
	{
		return new VTimerAdapter();
	}

	IDirAdapter *VAdapterFactory::CreateDirAdapter()
	{
		return new VDirAdapter();
	}

	IApnAdapter *VAdapterFactory::CreateApnAdapter()
	{
		return new VApnAdapter();
	}

	EPlatform VAdapterFactory::GetPlatform()
	{
		return E_PLATFORM_ANDROID;
	}
}

