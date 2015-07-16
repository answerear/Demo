//
//  AndroidAudioEngine.cpp
//  HelloWorkd
//
//  Created by mix on 14-3-10.
//
//

#include "QGAudioEngine.h"
using namespace CocosDenshion;

namespace QGGameMediaEngine {
    QGAudioEngine::QGAudioEngine(){
        m_audioDelegate=SimpleAudioEngine::sharedEngine();
    }
    
    IGameAudioEngine* QGAudioEngine::getAudioEngine(){
        static AudioEngine androidEngine;
        return &androidEngine;
    }
    
    
    int QGAudioEngine::playEffect(const char *pEffectPath){
        if(NULL==pEffectPath){
            return -1;
        }
        if(m_audioDelegate){
            m_audioDelegate->setEffectsVolume(m_fEffectVol);
            return m_audioDelegate->playEffect(pEffectPath);
        }
        return -1;
    }
    
    void QGAudioEngine::stopAllEffect(){
        if(m_audioDelegate){
            m_audioDelegate->stopAllEffects();
        }
    }
    
    void QGAudioEngine::stopEffect(int resID){
        if(m_audioDelegate){
            m_audioDelegate->stopEffect(resID);
        }
    }
    
    int QGAudioEngine::playBackgroundMusic(const char *pBackgroundMusic,bool loop){
        if(m_audioDelegate){
            m_audioDelegate->setBackgroundMusicVolume(m_fBackgroundVol);
            m_audioDelegate->playBackgroundMusic(pBackgroundMusic,loop);
        }
    }
    
    bool QGAudioEngine::isBackgroundMusciPlaying(){
        if(m_audioDelegate){
            return m_audioDelegate->isBackgroundMusicPlaying();
        }
        return true;
    }
    
    void QGAudioEngine::stopBackgroundMusic(){
        if(m_audioDelegate){
            m_audioDelegate->stopBackgroundMusic(true);
        }
    }
    
    void QGAudioEngine::pauseBackgroundMusic(){
        if(m_audioDelegate){
            m_audioDelegate->pauseBackgroundMusic();
        }
    }
    
    void QGAudioEngine::resumBackgroundMusic(){
        if(m_audioDelegate){
            m_audioDelegate->resumeBackgroundMusic();
        }
    }
    
    
    float QGAudioEngine::getEffectVolume(){
        return m_fEffectVol;
    }
    
    float QGAudioEngine::getBackgroundMusicVolume(){
        return m_fBackgroundVol;
    }
    
    void QGAudioEngine::setBackgroundMusicVolume(float vol){
        m_fBackgroundVol=vol;
    }
    
    void QGAudioEngine::setEffectsVolume(float vol){
        m_fEffectVol=vol;
    }
    
}
