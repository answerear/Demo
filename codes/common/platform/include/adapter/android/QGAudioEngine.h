//
//  AndroidAudioEngine.h
//  HelloWorkd
//
//  Created by mix on 14-3-10.
//
//

#ifndef HelloWorkd_AndroidAudioEngine_h
#define HelloWorkd_AndroidAudioEngine_h
#include "SimpleAudioEngine.h"
#include "IAudioEngine.h"


namespace QGGameMediaEngine {
    
    class QGAudioEngine:public IGameAudioEngine{
    private:
        QGAudioEngine();
    public:
        static IGameAudioEngine* getAudioEngine();
        
        //IGameAudioEngine
        virtual int playEffect(const char *pEffectPath);
        virtual void stopEffect(int resID);
        
        virtual int playBackgroundMusic(const char* pBackgroundMusic,bool loop=true);
        virtual void stopBackgroundMusic();
        
        virtual void pauseBackgroundMusic();
        virtual void resumBackgroundMusic();
        
        virtual void stopAllEffect();
        
        virtual bool isBackgroundMusciPlaying();
        
        virtual void setBackgroundMusicVolume(float vol);
        
        virtual void setEffectsVolume(float vol);
        
        virtual float getBackgroundMusicVolume();
        
        virtual float getEffectVolume();
    private:
        CocosDenshion::SimpleAudioEngine* m_audioDelegate;
        float m_fBackgroundVol;
        float m_fEffectVol;
    };
}
#endif
