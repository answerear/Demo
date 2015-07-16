

#include "QGAdapterFactory.h"
#include "QGConsoleAdapter.h"
#include "QGApnAdapter.h"
#include "QGTimerAdapter.h"
#include "QGDirAdapter.h"


namespace QGLoggerSystem
{
	IAdapterFactory *CreateAdapterFactory()
	{
		return new QGAdapterFactory;
	}

	QGAdapterFactory::QGAdapterFactory()
	{

	}

	IConsoleAdapter *QGAdapterFactory::CreateConsoleAdapter()
	{
		 return new QGConsoleAdapter();;
	}

	ITimerAdapter *QGAdapterFactory::CreateTimerAdapter()
	{
		return new QGTimerAdapter();
	}

	IDirAdapter *QGAdapterFactory::CreateDirAdapter()
	{
		return  new QGDirAdapter();
	}

	IApnAdapter *QGAdapterFactory::CreateApnAdapter(){
		return new QGApnAdapter();
	}

	EPlatform QGAdapterFactory::GetPlatform()
	{
		return E_PLATFORM_ANDROID;
	}
}

