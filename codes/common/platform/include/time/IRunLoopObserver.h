
#ifndef __VISION_RUNLOOP_OBSERVER_H__
#define __VISION_RUNLOOP_OBSERVER_H__

#include "VType.h"
#include "VMacro.h"
#include "VPlatform.h"

namespace VPlatform
{
	class VPLATFORM_API IRunLoopObserver
	{
		V_DECLARE_INTERFACE(IRunLoopObserver);

	public:
		virtual void onExecute(uint32_t unLoopID, uint64_t dt) = 0;
	};
}

#endif	/*__VISION_RUNLOOP_OBSERVER_H__*/
