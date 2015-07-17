

#ifndef __VISION_PLATFORM_H__
#define __VISION_PLATFORM_H__


// #include "VType.h"

#if defined PLATFORM_EXPORT
#define VPLATFORM_API	VEXPORT_API
#else
#define VPLATFORM_API	VIMPORT_API
#endif


#endif	/*__VISION_PLATFORM_H__*/
