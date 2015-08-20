#ifndef __QQGAME_ANDROID_APN_MANAGER_ANDROID_H__
#define __QQGAME_ANDROID_APN_MANAGER_ANDROID_H__

#include "QGApnType.h"
#include <vector>
#include "IApnAdapterObserver.h"

namespace QGLoggerSystem
{
   class QGAndroidApnManager{
	   QG_DISABLE_COPY(QGAndroidApnManager);
   private:
	    QGAndroidApnManager();
   public:
	   static QGAndroidApnManager& g();
	   void AddObserver(IApnAdapterObserver* pObserver);
	   void RemoveObserver(IApnAdapterObserver* pObserver);
	   void OnApnChanged(EApnType eCurrentApn);
	   void OnPingResult(bool bReachable);
   private:
	   EApnType m_eLastApn; 
	   EApnType m_eCurrentApn;
	   typedef std::vector<IApnAdapterObserver*> APNOBSERVERVEC;
	   APNOBSERVERVEC m_vecApnObser;

	   typedef APNOBSERVERVEC::iterator OBSERITOR;
   }; 
}
#endif