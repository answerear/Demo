

#include "VApnManager.h"


template<> VPlatform::VApnManager *VSingleton<VPlatform::VApnManager>::m_pInstance = NULL;


namespace VPlatform
{
	VApnManager::VApnManager()
	{

	}

	VApnManager::~VApnManager()
	{

	}

	void VApnManager::addObserver(IApnObserver *pObserver)
	{

	}

	void VApnManager::removeObserver(IApnObserver *pObserver)
	{

	}

	EApnType VApnManager::getApnType() const
	{
		return E_APN_WIFI;
	}

	VString VApnManager::getApnTypeString() const
	{
		return "Wifi";
	}

	ECarrier VApnManager::getCarrier() const
	{
		return E_CARRIER_CHINA_TELECOM;
	}

	VString VApnManager::getCarrierString() const
	{
		return "Telecom";
	}

	void VApnManager::onApnChanged(EApnType eLastApn, EApnType eCurrentApn)
	{

	}

	void VApnManager::onPingResult(bool bReachable)
	{

	}
}
