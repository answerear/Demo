
#ifndef __QQGAME_APN_ADAPTER_ANDROID_H__
#define __QQGAME_APN_ADAPTER_ANDROID_H__


#include "IApnAdapter.h"
#include "QGAndroidJNIHelper.h"
#include "QGAndroidApnManager.h"

namespace QGLoggerSystem
{
	class QGApnAdapter : public IApnAdapter,public IApnAdapterObserver
	{
		friend class QGAndroidApnManager;
		QG_DISABLE_COPY(QGApnAdapter);

	public:
		QGApnAdapter();
		virtual ~QGApnAdapter();

	protected:
		virtual void SetObserver(IApnAdapterObserver *pObserver);

		virtual EApnType GetApnType() const;
		virtual ECarrier GetCarrier() const;

		virtual bool PingRoutes(const QString &strHost);
		virtual void CancelPingRoutes();
	private:
        IApnAdapterObserver* m_pObserver;

		virtual void OnApnChanged(EApnType eLastApn, EApnType eCurrentApn);
		virtual void OnPingResult(bool bReachable);
	};
}


#endif	/*__QQGAME_APN_ADAPTER_ANDROID_H__*/
