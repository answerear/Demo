
#ifndef __VISION_CONSOLE_ADAPTER_WIN32_H__
#define	__VISION_CONSOLE_ADAPTER_WIN32_H__


#include "IConsoleAdapter.h"


namespace VPlatform
{
	class VConsoleAdapter : public IConsoleAdapter
	{
		V_DISABLE_COPY(VConsoleAdapter);

	public:
		VConsoleAdapter();

	protected:
		virtual void print(const char *pText);
	};
}


#endif	/*__VISION_CONSOLE_ADAPTER_WIN32_H__*/
