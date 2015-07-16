#include "QGAndroidApnManager.h"
namespace QGLoggerSystem
{
QGAndroidApnManager::QGAndroidApnManager():
    m_eLastApn(E_APN_UNREACHABLE),
	m_eCurrentApn(E_APN_UNREACHABLE)
{

}

QGAndroidApnManager& QGAndroidApnManager::g(){
	static QGAndroidApnManager apnManager;
	return apnManager;
}

void QGAndroidApnManager::AddObserver(IApnAdapterObserver* pObserver){
	if(pObserver){
		OBSERITOR it=std::find(m_vecApnObser.begin(),m_vecApnObser.end(),pObserver);
		if(it==m_vecApnObser.end()){
			m_vecApnObser.push_back(pObserver);
		}
		
	}
}

void QGAndroidApnManager::RemoveObserver(IApnAdapterObserver* pObserver){
	if(pObserver){
		OBSERITOR it=std::find(m_vecApnObser.begin(),m_vecApnObser.end(),pObserver);
	    if(it!=m_vecApnObser.end()){
			m_vecApnObser.erase(it);
		}
	}
}

void QGAndroidApnManager::OnApnChanged(EApnType eCurrentApn){
	OBSERITOR itBegin=m_vecApnObser.begin();
	OBSERITOR itEnd=m_vecApnObser.end();
	m_eLastApn=m_eCurrentApn;
	m_eCurrentApn=eCurrentApn;
	for (; itBegin != itEnd; ++itBegin)
	{
      if(*itBegin){
		(*itBegin)->OnApnChanged(m_eLastApn,m_eCurrentApn);
	  }
	}
}

void QGAndroidApnManager::OnPingResult(bool bReachable){
	OBSERITOR itBegin=m_vecApnObser.begin();
	OBSERITOR itEnd=m_vecApnObser.end();
	for (; itBegin != itEnd; ++itBegin)
	{
		if(*itBegin){
			(*itBegin)->OnPingResult(bReachable);
		}
	}
}
}
