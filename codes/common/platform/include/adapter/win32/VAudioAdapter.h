//
//  IOSAudioEngine.h
//  HelloWorkd
//
//  Created by mix on 14-3-10.
//
//

#ifndef __VISION_AUDIO_ADAPTER_WIN32_H__
#define __VISION_AUDIO_ADAPTER_WIN32_H__

#include "VType.h"
#include <iostream>
#include "IAudioAdapter.h"
#include "ITimerObserver.h"
#include "alut.h"
#include <map>
#include <vector>
#include <string>


namespace VPlatform
{
	class VTimer;

    class VAudioAdapter 
		: public ITimerObserver
		, public IAudioAdapter
		, public IAudioPlayEventCallback
	{
	public:
        VAudioAdapter();
		virtual ~VAudioAdapter();

	protected:	/// from ITimerObserver
		virtual void onTimer(uint32_t unTimerID);
        
	protected:	/// from IAudioAdapter
        virtual int playEffect(const char *pEffectPath);
        virtual void stopEffect(int32_t resID);
        
        virtual int playBackgroundMusic(const char *pBackgroundMusic, bool loop = true);
        virtual void stopBackgroundMusic();
        
        virtual void stopAllEffect();
        
        virtual bool isBackgroundMusciPlaying();
        
        virtual void setBackgroundMusicVolume(float vol);
        
        virtual void setEffectsVolume(float vol);
        
        virtual float getBackgroundMusicVolume();
        
        virtual float getEffectVolume();
        
        virtual void pauseBackgroundMusic();
        virtual void resumBackgroundMusic();
        
	protected:	/// from IAudioPlayEventCallback
        virtual void OnPlayEffectEnd(int32_t nChannel);
        
	protected:	// internal methods
		bool isChanelActive(int chanel);
		void setChanelActiveState(int chanel,bool active);

		bool isNeedCallback(int chanel);
		void setNeedCallback(int chanel,bool flag);

		bool isChanelValid(int chanel);

		void init();

		int preparePlaySound(int chanel,const char* szFilename , bool bCreateStream,float vol);

		int CreateSound(const char* szFilename , bool bCreateStream);

		int getFreeChanel();

		int loadMediaFile(const char* szFilename);

		void enterQueue(const char* path);

		bool isPlaying(int chanel);

		bool isPause(int chanel);

		VString getNextOneEffect();

		void releaseSound(int chanel);

		void unionSoundAndChanel(int chanel,int sound);

    private:
        int m_nChanelState;
        int m_nCallbackState;
        bool m_bInit;
        const int MAX_AUDIO_CHANNEL;
        
        ALuint	*m_Sources;
        
        ALCdevice	*m_pDevice;
		ALCcontext	*m_pContext;
        
        typedef std::map<int,int> CHANEL2SOUND;
        CHANEL2SOUND m_chanel2sound;
        
        typedef std::vector<std::string> WAITINGEFFECT;
        WAITINGEFFECT m_waitingEffect;
        
        float m_fEffectVol;
        float m_fBackgroundMusicVol;
      
		VTimer *m_pTimer;
    };
}

#endif	/*__VISION_AUDIO_ADAPTER_WIN32_H__*/
