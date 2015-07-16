

#include "VSystem.h"
#include "VAdapterFactory.h"
#include "VDir.h"
#include "VTextCodec.h"
#include "VConsole.h"
#include "VApnManager.h"
#include "VRunLoop.h"
#include "IAdapterFactory.h"


template<> VPlatform::VSystem *VSingleton<VPlatform::VSystem>::m_pInstance = NULL;

namespace VPlatform
{
	const uint32_t VSystem::V_PLATFORM_UNKNOWN = E_PLATFORM_UNKNOWN;
	const uint32_t VSystem::V_PLATFORM_WIN32 = E_PLATFORM_WIN32;
	const uint32_t VSystem::V_PLATFORM_IOS = E_PLATFORM_IOS;
	const uint32_t VSystem::V_PLATFORM_ANDROID = E_PLATFORM_ANDROID;
	
	VSystem::VSystem()
		: m_pAdapterFactory(NULL)
		, m_pTextCodec(NULL)
		, m_pConsole(NULL)
		, m_pApnMgr(NULL)
		, m_pMainRunLoop(NULL)
	{
		m_pAdapterFactory = createAdapterFactory();

		VDir::getNativeSeparator();

		m_pTextCodec = new VTextCodec("GB2312.dat");
		m_pConsole = new VConsole();
		m_pApnMgr = new VApnManager();
		m_pMainRunLoop = new VRunLoop();
	}

	VSystem::~VSystem()
	{
		V_SAFE_DELETE(m_pMainRunLoop);
		V_SAFE_DELETE(m_pApnMgr);
		V_SAFE_DELETE(m_pConsole);
		V_SAFE_DELETE(m_pAdapterFactory);
	}

	void VSystem::process()
	{
		if (m_pMainRunLoop != NULL)
		{
			m_pMainRunLoop->execute();
		}
	}
	
	uint32_t VSystem::getPlatform() const
	{
		return (uint32_t)(m_pAdapterFactory != NULL ? m_pAdapterFactory->getPlatform() : E_PLATFORM_UNKNOWN);
	}

	VRunLoop &VSystem::getMainRunLoop()
	{
		return *m_pMainRunLoop;
	}
}
