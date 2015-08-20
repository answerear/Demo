
#ifndef __VISION_CONSOLE_ADAPTER_ANDROID_H__
#define	__VISION_CONSOLE_ADAPTER_ANDROID_H__


#include "IConsoleAdapter.h"


namespace VPlatform
{
	class VConsoleAdapter : public IConsoleAdapter
	{
		V_DISABLE_COPY(VConsoleAdapter);

	public:
		VConsoleAdapter();

	protected:
		virtual void Print(const char *pText);
	};
}


#endif	/*__VISION_CONSOLE_ADAPTER_ANDROID_H__*/
