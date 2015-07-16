

#include "VConsoleAdapter.h"
#include <windows.h>


namespace VPlatform
{
	VConsoleAdapter::VConsoleAdapter()
	{

	}

	void VConsoleAdapter::print(const char *pText)
	{
		printf(pText);
		OutputDebugString(pText);
	}
}
