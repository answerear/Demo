
#include "VInstance.h"


namespace VFramework
{
    const VInstance VInstance::V_BROADCAST_INSTANCE_ID = VInstance((void*)0xFFFFFFFF, 0);
    
    const VInstance VInstance::V_INVALID_INSTANCE_ID = VInstance(NULL, 0);
}

