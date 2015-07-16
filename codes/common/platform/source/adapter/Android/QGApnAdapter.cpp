#include "QGApnAdapter.h"
#include "QGAndroidApnManager.h"

namespace QGLoggerSystem
{
	QGApnAdapter::QGApnAdapter()
	{
		QGAndroidApnManager::g().AddObserver((IApnAdapterObserver*)(this));
	}

	QGApnAdapter::~QGApnAdapter()
	{
		QGAndroidApnManager::g().RemoveObserver((IApnAdapterObserver*)(this));
	}

	void QGApnAdapter::SetObserver(IApnAdapterObserver *pObserver)
	{
		m_pObserver=pObserver;
	}

	EApnType QGApnAdapter::GetApnType() const
	{
		return  GetApnTypeFromJava();
	}

	ECarrier QGApnAdapter::GetCarrier() const
	{
		return  GetCarrierFromJava();
	}

	bool QGApnAdapter::PingRoutes(const std::string &strHost)
	{
		return true;
	}

	void QGApnAdapter::CancelPingRoutes()
	{

	}

	void QGApnAdapter::OnApnChanged(EApnType eLastApn, EApnType eCurrentApn){
		if(m_pObserver){
			m_pObserver->OnApnChanged(eLastApn,eCurrentApn);
		}
	}

	void QGApnAdapter::OnPingResult(bool bReachable){
		if(m_pObserver){
			m_pObserver->OnPingResult(bReachable);
		}
	}
}

