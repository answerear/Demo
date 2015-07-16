

#include "VDeviceInfoAdapter.h"


namespace VPlatform
{
	VDeviceInfoAdapter::VDeviceInfoAdapter()
	{

	}

	VDeviceInfoAdapter::~VDeviceInfoAdapter()
	{

	}

	IDeviceInfoAdapter::EPlatform VDeviceInfoAdapter::getPlatform() const
	{
		return E_PLATFORM_WIN32;
	}

	VString VDeviceInfoAdapter::getSoftwareVersion() const
	{
		return "3.0.0.0";
	}

	VString VDeviceInfoAdapter::getOSVersion() const
	{
		return "Windows 7";
	}

	VString VDeviceInfoAdapter::getDeviceVersion() const
	{
		return "PC";
	}

	int32_t VDeviceInfoAdapter::getScreenWidth() const
	{
		return 0;
	}

	int32_t VDeviceInfoAdapter::getScreenHeight() const
	{
		return 0;
	}

	float VDeviceInfoAdapter::getScreenDPI() const
	{
		return 0.0f;
	}

	VString VDeviceInfoAdapter::getMacAddress() const
	{
		return "12-34-56-78-9A-BC";
	}

	VString VDeviceInfoAdapter::getCPUType() const
	{
		return "Intel Core i5";
	}

	int32_t VDeviceInfoAdapter::getNumberOfProcessors() const
	{
		return 1;
	}

	uint32_t VDeviceInfoAdapter::getMemoryCapacity() const
	{
		return 0x80000000;
	}

	VString VDeviceInfoAdapter::getDeviceID() const
	{
		return "12-34-56-78-9A-BC";
	}
}

