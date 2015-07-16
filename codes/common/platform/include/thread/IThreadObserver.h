
#ifndef __VISION_THREAD_OBSERVER_H__
#define __VISION_THREAD_OBSERVER_H__


#include "VType.h"
#include "VMacro.h"
#include "VPlatform.h"


namespace VPlatform
{
	class VPLATFORM_API IThreadObserver
	{
		V_DECLARE_INTERFACE(IThreadObserver);

	public:
		virtual int run() = 0;
	};
}


#endif	/*__VISION_THREAD_OBSERVER_H__*/
