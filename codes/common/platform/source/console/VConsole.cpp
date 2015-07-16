

#include "VConsole.h"
#include "VSystem.h"
#include "IAdapterFactory.h"
#include "IConsoleAdapter.h"
#include <windows.h>


#pragma warning(disable:4996)


template<> VPlatform::VConsole *VSingleton<VPlatform::VConsole>::m_pInstance = NULL;


namespace VPlatform
{
	VConsole::VConsole()
		: m_pAdapter(NULL)
	{
		m_pAdapter = V_ADAPTER_FACTORY.createConsoleAdapter();
	}

	VConsole::~VConsole()
	{
		V_SAFE_DELETE(m_pAdapter);
	}

	void VConsole::print(const char *pszFmt, ...)
	{
		if (NULL != m_pAdapter)
		{
			char *pszBuffer = new char[V_MAX_LOG_BUFFER_SIZE];
			memset(pszBuffer, 0, V_MAX_LOG_BUFFER_SIZE);

			va_list vl;
			va_start(vl, pszFmt);
			vsnprintf(pszBuffer, V_MAX_LOG_BUFFER_SIZE, pszFmt, vl);
			va_end(vl);

			m_pAdapter->print(pszBuffer);

			V_SAFE_DELETE_ARRAY(pszBuffer);
		}
	}
}
