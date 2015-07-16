

#include "VApnAdapter.h"


namespace VPlatform
{
	VApnAdapter::VApnAdapter()
	{

	}

	VApnAdapter::~VApnAdapter()
	{

	}

	void VApnAdapter::setObserver(IApnAdapterObserver *pObserver)
	{

	}

	EApnType VApnAdapter::getApnType() const
	{
		return E_APN_WIFI;
	}

	ECarrier VApnAdapter::getCarrier() const
	{
		return E_CARRIER_CHINA_TELECOM;
	}

	bool VApnAdapter::pingRoutes(const std::string &strHost)
	{
		return true;
	}

	void VApnAdapter::cancelPingRoutes()
	{

	}
}

