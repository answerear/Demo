//
//  IOSAudioEngine.cpp
//  HelloWorkd
//
//  Created by mix on 14-3-10.
//
//

#include "VAudioAdapter.h"
#include "stb_vorbis.h"
#include <stdio.h>
#include "VTimer.h"


namespace VPlatform
{
    VAudioAdapter::VAudioAdapter()
    : m_nChanelState(0)
    , m_nCallbackState(0)
    , m_Sources(0)
    , m_pDevice(0)
    , m_pContext(0)
    , MAX_AUDIO_CHANNEL(16)
    , m_fEffectVol(1.0f)
    , m_fBackgroundMusicVol(1.0f)
    , m_bInit(false)
    {
        init();
		if(m_pTimer){
			m_pTimer->SetObserver(this);
			m_pTimer->Start(3*1000);
		}
    }
    
	VAudioAdapter::~VAudioAdapter()
	{
	}
    
    void VAudioAdapter::init(){
		m_pTimer=new VTimer();
        do{
            m_Sources = new ALuint[MAX_AUDIO_CHANNEL];
            if (0 == m_Sources)	{
                break;
            }
            memset(m_Sources, AL_INVALID, sizeof(ALuint)*MAX_AUDIO_CHANNEL);
            
            //Init OpenAL,store the al context in m_pContext.
		    m_pDevice = alcOpenDevice(NULL);
		    if (0 == m_pDevice)
		    {
                break;
		    }
            
		    m_pContext = alcCreateContext(m_pDevice, NULL);
            if (0 == m_pContext)
            {
                alcCloseDevice(m_pDevice);
                break;
            }
            alcMakeContextCurrent(m_pContext);
            
            alutInitWithoutContext(NULL, NULL);
            
            //generate sources for channels
            alGenSources(MAX_AUDIO_CHANNEL, m_Sources);
            m_bInit=true;
            return ;
        }while(0);
    }
    
    void VAudioAdapter::releaseSound(int chanel){
        int buffID=m_chanel2sound[chanel];
        if(buffID!=0){
            if(alIsSource(m_Sources[chanel])==AL_TRUE){
                alSourceStop(m_Sources[chanel]);
            }
            
            if(alIsBuffer(buffID)==AL_TRUE){
                alDeleteBuffers(1, (ALuint*)&buffID);
            }
            m_chanel2sound.erase(chanel);
            alSourcei(m_Sources[chanel], AL_BUFFER, NULL);
            alSourcei(m_Sources[chanel],AL_LOOPING, AL_FALSE);
            setChanelActiveState(chanel, false);
        }
    }
    
    //     IAudioAdapter* VAudioAdapter::getAudioEngine(){
    //         static QGAudioEngine iosEngie;
    //         return &iosEngie;
    //     }
    
    void VAudioAdapter::onTimer(uint32_t unTimerID){
        for (int i = 0; i < MAX_AUDIO_CHANNEL; i ++) {
            if(isChanelActive(i)){
                bool bIsPlaying = isPlaying(i);
                bool bIsPause = isPause(i);
                if ((!bIsPause) && (!bIsPlaying)) {
                    releaseSound(i);
                }
            }
        }
    }
    
    int VAudioAdapter::playEffect(const char *path)
    {
        if(NULL==path){
            return -1;
        }
        int res=-1;
        int chanel=getFreeChanel();
        if(chanel!=-1){
            res=preparePlaySound(chanel, path, false,m_fEffectVol);
        }else{
            enterQueue(path);
        }
        return res;
    }
    
    void VAudioAdapter::stopEffect(int resID){
        for (int i = 1; i < MAX_AUDIO_CHANNEL; i ++){
            if(isChanelActive(i)){
                releaseSound(i);
            }
        }
    }
    
    int VAudioAdapter::playBackgroundMusic(const char* pBackgroundMusic,bool loop){
        if(pBackgroundMusic==NULL){
            return -1;
        }
        int res=-1;
        int chanel=0;
        if(chanel!=-1){
            res=chanel;
            preparePlaySound(chanel, pBackgroundMusic, true,m_fBackgroundMusicVol);
        }
        return res;
    }
    
    bool VAudioAdapter::isBackgroundMusciPlaying(){
        return isChanelActive(0);
    }
    
    
    void VAudioAdapter::stopBackgroundMusic(){
        if(isChanelActive(0)){
            releaseSound(0);
        }
    }
    
    bool VAudioAdapter::isPlaying(int chanel){
        if(!isChanelValid(chanel)){
            return false;
        }
        if(alIsSource(m_Sources[chanel])){
            ALint nState = -1;
            alGetSourcei(m_Sources[chanel], AL_SOURCE_STATE, &nState);
            return (nState == AL_PLAYING);
        }
        return false;
    }
    
    bool VAudioAdapter::isPause(int chanel){
        if(!isChanelValid(chanel)){
            return false;
        }
        if(alIsSource(m_Sources[chanel])){
            ALint nState = -1;
            alGetSourcei(m_Sources[chanel], AL_SOURCE_STATE, &nState);
            return (nState == AL_PAUSED);
        }
        return false;
    }
    
    void VAudioAdapter::pauseBackgroundMusic(){
        if(isPlaying(0)){
            alSourcePause(m_Sources[0]);
        }
    }
    
    void VAudioAdapter::resumBackgroundMusic(){
        if(isPause(0)){
            alSourcePlay(m_Sources[0]);
        }
    }
    
    void VAudioAdapter::stopAllEffect(){
        
    }
    
    void VAudioAdapter::OnPlayEffectEnd(int nChannel){
        
    }
    
    bool VAudioAdapter::isChanelValid(int chanel){
        return chanel>=0&&chanel<MAX_AUDIO_CHANNEL;
    }
    
    bool VAudioAdapter::isChanelActive(int chanel){
        if(!isChanelValid(chanel)){
            return false;
        }
        return ((m_nChanelState&(1<<chanel)) != 0);
    }
    
    void VAudioAdapter::setChanelActiveState(int chanel,bool active){
        if(!isChanelValid(chanel)){
            return ;
        }
        if(active){
            m_nChanelState|=(1<<chanel);
        }else{
            m_nChanelState&=(~(1<<chanel));
        }
    }
    
    bool VAudioAdapter::isNeedCallback(int chanel){
        if(!isChanelValid(chanel)){
            return false;
        }
        return ((m_nCallbackState&(1<<chanel)) != 0);
    }
    
    void VAudioAdapter::setNeedCallback(int chanel,bool flag){
        if(!isChanelValid(chanel)){
            return ;
        }
        if(flag){
            m_nCallbackState|=(1<<chanel);
        }else{
            m_nCallbackState&=(~(1<<chanel));
        }
    }
    
    int VAudioAdapter::getFreeChanel(){
        for(int i=1;i<MAX_AUDIO_CHANNEL;i++){
            if(!isChanelActive(i)){
                return i;
            }
        }
        return -1;
    }
    
    int VAudioAdapter::preparePlaySound(int chanel,const char* szFilename , bool loop,float vol){
        int soundID=CreateSound(szFilename, loop);
        if(soundID!=AL_INVALID){
            setChanelActiveState(chanel, true);
        }
        unionSoundAndChanel(chanel, soundID);
        if (alIsBuffer(soundID) == AL_FALSE)
		{
			return -1;
		}
        alSourcei(m_Sources[chanel], AL_BUFFER, soundID);
		if(loop){
            alSourcei(m_Sources[chanel],AL_LOOPING, AL_TRUE);
        }
		if (alGetError() != AL_NO_ERROR)
		{
			return -1;
		}
        alSourcef(m_Sources[chanel], AL_GAIN, vol);
        alSourcePlay(m_Sources[chanel]);
        return soundID;
    }
    
    int VAudioAdapter::CreateSound(const char* szFilename , bool bCreateStream){
        ALuint			buff = AL_NONE;
        buff = alutCreateBufferFromFile(szFilename);
		if (buff == AL_NONE)
		{
			buff = loadMediaFile(szFilename);
		}
		if (buff == AL_NONE)
		{
			return AL_INVALID;
		}
		else
		{
			return buff;
		}
    }
    
    int VAudioAdapter::loadMediaFile(const char* pFilename){
        short *decoded;
		int channels, len;
		len = stb_vorbis_decode_filename((char*)(pFilename), &channels, &decoded);
        
		if (len > 0)
		{
            int error;
			stb_vorbis *v = stb_vorbis_open_filename((char*)(pFilename), &error, NULL);
			if (0 == v)
			{
				printf("ogg error:%d\n",error);
			}
            
			stb_vorbis_info info = stb_vorbis_get_info(v);
			stb_vorbis_close(v);
			v = 0;
            
			ALuint buffer;
			alGenBuffers (1, &buffer);
			if (alGetError () != AL_NO_ERROR)
			{
				free(decoded);
				return AL_NONE;
			}
            
			ALenum format = ((info.channels > 1) ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16);
			alBufferData (buffer, format, decoded,
                          (ALsizei) (len*channels*2), (ALsizei) (info.sample_rate));
			ALenum alerro = alGetError();
			if (alerro != AL_NO_ERROR)
			{
				free(decoded);
				return AL_NONE;
			}
            
			free(decoded);
			decoded = 0;
			return buffer;
		}
        
		else
		{
			if (len == -1)
			{
				printf("stb_vorbis_open_filename failed!\n");
			}
			else if (len == -2)
			{
				printf("stb_vorbis memory alloc failed!\n");
			}
			return AL_NONE;
		}
        
		return 0;
    }
    
    void VAudioAdapter::enterQueue(const char* path){
        m_waitingEffect.push_back(path);
    }
    
    std::string VAudioAdapter::getNextOneEffect(){
        return "";
    }
    
    void VAudioAdapter::unionSoundAndChanel(int chanel, int sound){
        m_chanel2sound[chanel]=sound;
    }
    
    void VAudioAdapter::setBackgroundMusicVolume(float vol){
        m_fBackgroundMusicVol=vol;
    }
    
    void VAudioAdapter::setEffectsVolume(float vol){
        m_fEffectVol=vol;
    }
    
    float VAudioAdapter::getBackgroundMusicVolume(){
        return m_fBackgroundMusicVol;
    }
    
    float VAudioAdapter::getEffectVolume(){
        return m_fEffectVol;
    }
    
}

