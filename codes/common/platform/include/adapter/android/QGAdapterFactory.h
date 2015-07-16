#ifndef __QQGAME_ADAPTER_FACTORY_ANDROID_H__
#define __QQGAME_ADAPTER_FACTORY_ANDROID_H__

#include "IAdapterFactory.h"

namespace QGLoggerSystem
{
	class QGAdapterFactory : public IAdapterFactory
	{
		QG_DISABLE_COPY(QGAdapterFactory);

	public:
		QGAdapterFactory();

	protected:
		virtual IConsoleAdapter *CreateConsoleAdapter();
		virtual ITimerAdapter *CreateTimerAdapter();
		virtual IDirAdapter *CreateDirAdapter();
		virtual IApnAdapter *CreateApnAdapter();
		virtual EPlatform GetPlatform();
	};
}

#endif	/*__QQGAME_ADAPTER_FACTORY_ANDROID_H__*/