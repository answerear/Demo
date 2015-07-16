

#include "VDeviceInfo.h"
#include "IDeviceInfoAdapter.h"
#include "IAdapterFactory.h"
#include "VSystem.h"


INIT_SINGLETON(VPlatform::VDeviceInfo);


namespace VPlatform
{
	const char* VDeviceInfo::Unknown = "Unknown";
	const char* VDeviceInfo::Windows = "Windows";
	const char* VDeviceInfo::iOS = "iOS";
	const char* VDeviceInfo::Android = "Android";

	VDeviceInfo::VDeviceInfo()
		: m_pDevInfoAdapter(NULL)
	{
		m_pDevInfoAdapter = V_ADAPTER_FACTORY.createDeviceInfoAdapter();
	}

	VDeviceInfo::~VDeviceInfo()
	{
		V_SAFE_DELETE(m_pDevInfoAdapter);
	}

	VDeviceInfo::EPlatform VDeviceInfo::getPlatform() const
	{
		EPlatform ePlatform = E_PLATFORM_UNKNOWN;

		if (m_pDevInfoAdapter != NULL)
		{
			switch (m_pDevInfoAdapter->getPlatform())
			{
			case IDeviceInfoAdapter::E_PLATFORM_WIN32:
				{
					ePlatform = E_PLATFORM_WIN32;
				}
				break;
			case IDeviceInfoAdapter::E_PLATFORM_IOS:
				{
					ePlatform = E_PLATFORM_IOS;
				}
				break;
			case IDeviceInfoAdapter::E_PLATFORM_ANDROID:
				{
					ePlatform = E_PLATFORM_ANDROID;
				}
				break;
			}
		}

		return ePlatform;
	}

	VString VDeviceInfo::getPlatformString() const
	{
		VString strPlatform = Unknown;

		if (m_pDevInfoAdapter != NULL)
		{
			switch (m_pDevInfoAdapter->getPlatform())
			{
			case IDeviceInfoAdapter::E_PLATFORM_WIN32:
				{
					strPlatform = Windows;
				}
				break;
			case IDeviceInfoAdapter::E_PLATFORM_IOS:
				{
					strPlatform = iOS;
				}
				break;
			case IDeviceInfoAdapter::E_PLATFORM_ANDROID:
				{
					strPlatform = Android;
				}
				break;
			}
		}

		return strPlatform;
	}

	VString VDeviceInfo::getSoftwareVersion() const
	{
		if (m_pDevInfoAdapter != NULL)
		{
			return m_pDevInfoAdapter->getSoftwareVersion();
		}
		return "";
	}

	VString VDeviceInfo::getOSVersion() const
	{
		if (m_pDevInfoAdapter != NULL)
		{
			return m_pDevInfoAdapter->getOSVersion();
		}
		return "";
	}

	VString VDeviceInfo::getDeviceVersion() const
	{
		if (m_pDevInfoAdapter != NULL)
		{
			return m_pDevInfoAdapter->getDeviceVersion();
		}
		return "";
	}

	int32_t VDeviceInfo::getScreenWidth() const
	{
		if (m_pDevInfoAdapter != NULL)
		{
			return m_pDevInfoAdapter->getScreenWidth();
		}
		return 0;
	}

	int32_t VDeviceInfo::getScreenHeight() const
	{
		if (m_pDevInfoAdapter != NULL)
		{
			return m_pDevInfoAdapter->getScreenHeight();
		}
		return 0;
	}

	float VDeviceInfo::getScreenDPI() const
	{
		if (m_pDevInfoAdapter != NULL)
		{
			return m_pDevInfoAdapter->getScreenDPI();
		}
		return 0.0f;
	}

	VString VDeviceInfo::getMacAddress() const
	{
		if (m_pDevInfoAdapter != NULL)
		{
			return m_pDevInfoAdapter->getMacAddress();
		}
		return "";
	}

	VString VDeviceInfo::getCPUType() const
	{
		if (m_pDevInfoAdapter != NULL)
		{
			return m_pDevInfoAdapter->getCPUType();
		}
		return "";
	}

	int32_t VDeviceInfo::getNumberOfProcessors() const
	{
		if (m_pDevInfoAdapter != NULL)
		{
			return m_pDevInfoAdapter->getNumberOfProcessors();
		}
		return 1;
	}

	uint32_t VDeviceInfo::getMemoryCapacity() const
	{
		if (m_pDevInfoAdapter != NULL)
		{
			return m_pDevInfoAdapter->getMemoryCapacity();
		}
		return 0;
	}

	VString VDeviceInfo::getDeviceID() const
	{
		if (m_pDevInfoAdapter != NULL)
		{
			return m_pDevInfoAdapter->getDeviceID();
		}
		return "";
	}
}
