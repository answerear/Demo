
#ifndef __QQGAME_ADAPTER_FACTORY_IOS_H__
#define __QQGAME_ADAPTER_FACTORY_IOS_H__


#include "IAdapterFactory.h"


namespace VPlatform
{
    class VAdapterFactory : public IAdapterFactory
    {
        V_DISABLE_COPY(VAdapterFactory);
        
    public:
        VAdapterFactory();
        virtual ~VAdapterFactory();
        
    protected:
        virtual IConsoleAdapter *createConsoleAdapter();
		virtual ITimerAdapter *createTimerAdapter();
		virtual IDirAdapter *createDirAdapter();
		virtual IApnAdapter *createApnAdapter();
        virtual IAudioAdapter *createAudioAdapter();
        
		virtual EPlatform getPlatform();
    };
}


#endif	/*__QQGAME_ADAPTER_FACTORY_IOS_H__*/
