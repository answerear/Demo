//
//  IAudioEngine.h
//  HelloWorkd
//
//  Created by mix on 14-3-10.
//
//

#ifndef __IAUDIO_ADAPTER_H__
#define __IAUDIO_ADAPTER_H__


#include "VType.h"
#include "VMacro.h"


namespace VPlatform 
{
    class IAudioPlayEventCallback
	{
        virtual void OnPlayEffectEnd(int32_t nChannel) = 0;
    };
    
    class IAudioAdapter
	{
		V_DECLARE_INTERFACE(IAudioAdapter);

    public:
        virtual int playEffect(const char *pEffectPath) = 0;
        virtual void stopEffect(int32_t resID) = 0;
        
        virtual void pauseBackgroundMusic() = 0;
        virtual void resumBackgroundMusic() = 0;
        
        virtual int32_t playBackgroundMusic(const char* pBackgroundMusic, bool loop = true) = 0;
        virtual void stopBackgroundMusic() = 0;
        
        virtual void stopAllEffect() = 0;
        
        virtual bool isBackgroundMusciPlaying() = 0;
        
        virtual void setBackgroundMusicVolume(float vol) = 0;
        
        virtual void setEffectsVolume(float vol) = 0;
        
        virtual float getBackgroundMusicVolume() = 0;
        
        virtual float getEffectVolume() = 0;
    };
}

#endif	/*__IAUDIO_ADAPTER_H__*/
