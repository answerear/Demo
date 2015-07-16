
#ifndef __QQGAME_CONSOLE_ADAPTER_IOS_H__
#define __QQGAME_CONSOLE_ADAPTER_IOS_H__


#include "IConsoleAdapter.h"


namespace VPlatform
{
    class VConsoleAdapter : public IConsoleAdapter
    {
        V_DISABLE_COPY(VConsoleAdapter);
        
    public:
        VConsoleAdapter();
        virtual ~VConsoleAdapter();

    protected:
        virtual void print(const char *pText);
    };
}


#endif	/*__QQGAME_CONSOLE_ADAPTER_IOS_H__*/
