/*
*VAudioManager.cpp
*
*  Created on: 2014Äê3ÔÂ5ÈÕ
*      Author: mix
*/
#include "VAudioManager.h"
#include "IAudioAdapter.h"
#include "IAdapterFactory.h"
#include "IDirAdapter.h"
#include "VSystem.h"

#include <stdio.h>


INIT_SINGLETON(VPlatform::VAudioManager);


namespace VPlatform 
{
	VAudioManager::VAudioManager()
		: m_bEffectEnable(true)
		, m_bBackgroundMusicEnable(true)
		, m_bkMusicVolume(1.0f)
		, m_effectVolume(1.0f)
		, m_bEffectPlaying(false)
	{
		m_pSimpleAudioEngine = V_ADAPTER_FACTORY.createAudioAdapter();
		m_eMusicType=EMT_MAX_MUSIC_TYPE;
	}

	VAudioManager::~VAudioManager()
	{
		release();
	}


	void VAudioManager::stopBackgroundMusic(){
		if(m_pSimpleAudioEngine->isBackgroundMusciPlaying()){
			m_pSimpleAudioEngine->stopBackgroundMusic();
		}
		m_eMusicType=EMT_MAX_MUSIC_TYPE;
	}

	void VAudioManager::pauseBackgroundMusic(){
		if(m_pSimpleAudioEngine->isBackgroundMusciPlaying()){
			m_pSimpleAudioEngine->pauseBackgroundMusic();
		}
	}

	void VAudioManager::resumeBackgroundMusic(){
		if(m_pSimpleAudioEngine&&m_bBackgroundMusicEnable){
			m_pSimpleAudioEngine->resumBackgroundMusic();
		}
	}

	bool VAudioManager::getBackgroundMusicPathWithType(EMusicType eMusicType,char *name,bool &loop){
		loop=true;
		switch(eMusicType){
		case EMT_PLAYING_WELCOME:{
			snprintf(name,MAX_MEDIA_NAME_LEN-1,"MusicEx_Welcome.ogg");
			return true;
								 }
		case EMT_PLAYING_NORMAL:{
			snprintf(name,MAX_MEDIA_NAME_LEN-1,"MusicEx_Normal.ogg");
			return true;
								}
		case EMT_PLAYING_NORMAL2:{
			snprintf(name,MAX_MEDIA_NAME_LEN-1,"MusicEx_Normal2.ogg");
			return true;
								 }
		case EMT_PLAYING_EXCITING:{
			snprintf(name,MAX_MEDIA_NAME_LEN-1,"MusicEx_Exciting.ogg");
			return true;
								  }
		case EMT_PLAYING_WIN:{
			snprintf(name,MAX_MEDIA_NAME_LEN-1,"MusicEx_Win.ogg");
			loop=false;
			return true;
							 }
		case EMT_PLAYING_LOSE:{
			snprintf(name,MAX_MEDIA_NAME_LEN-1,"MusicEx_Lose.ogg");
			loop=false;
			return true;
							  }
		}
		return false;
	}


	void VAudioManager::playBackgroundMusic(EMusicType eMusicType,bool loop){
		if(eMusicType==m_eMusicType||!m_bBackgroundMusicEnable){
			return ;
		}
		m_eMusicType=eMusicType;
		char mediaName[MAX_MEDIA_NAME_LEN]={0};
		if(!getBackgroundMusicPathWithType(eMusicType,mediaName,loop)){
			return ;
		}
		char *prefix="Data/Sounds";
		char path[MAX_MEDIA_PATH_LEN]={0};
		snprintf(path,MAX_MEDIA_PATH_LEN-1,"%s/%s",prefix,mediaName);

		playBackgroundMusic(path,loop);
	}

	void VAudioManager::playBackgroundMusic(const char *pBackgroundMusic,bool loop){
		if(pBackgroundMusic==NULL||!m_bBackgroundMusicEnable){
			return ;
		}
		playBackgroundMusicInner(pBackgroundMusic,loop);
	}

	void VAudioManager::playBackgroundMusicInner(const char* pBkMusicPath,bool loop){
		if(m_pSimpleAudioEngine){
			if(m_pSimpleAudioEngine->isBackgroundMusciPlaying()){
				m_pSimpleAudioEngine->stopBackgroundMusic();
			}
			if(m_bkMusicVolume<0){
				m_bkMusicVolume=0;
			}
			if(m_bkMusicVolume>1.0f){
				m_bkMusicVolume=1.0f;
			}
			m_pSimpleAudioEngine->setBackgroundMusicVolume(m_bkMusicVolume);
			m_pSimpleAudioEngine->playBackgroundMusic(pBkMusicPath,loop);
		}
	}

	bool VAudioManager::isBackgroundMusicPlaying()
	{
		return m_pSimpleAudioEngine->isBackgroundMusciPlaying();
	}

	void VAudioManager::setSilence(){
		m_bBackgroundMusicEnable=false;
		m_bEffectEnable=false;
		if(m_pSimpleAudioEngine){
			m_pSimpleAudioEngine->stopAllEffect();
			m_pSimpleAudioEngine->stopBackgroundMusic();
		}
		m_listEffect.clear();
	}

	void VAudioManager::disableEffect(){
		m_bEffectEnable=false;
		if(m_pSimpleAudioEngine){
			m_pSimpleAudioEngine->stopAllEffect();
		}
		m_bEffectPlaying=false;
		m_listEffect.clear();
	}

	void VAudioManager::enableEffect(){
		m_bEffectEnable=true;
	}

	void VAudioManager::playEffect(const char *pEffectPath){
		if(NULL==pEffectPath||!m_bEffectEnable){
			return ;
		}
		if(!m_bEffectPlaying){
			playEffectInner(pEffectPath);
		}else{
			m_listEffect.push_back(pEffectPath);
		}
	}

	void VAudioManager::onEffectPlayComplte()
	{
		m_bEffectPlaying=false;
	}

	void VAudioManager::playEffectInner(const char *pEffectPath)
	{
		//m_bEffectPlaying=true;
		/*char *prefix="Data/Sounds";
		char path[MAX_MEDIA_PATH_LEN]={0};
		snprintf(path,MAX_MEDIA_PATH_LEN-1,"%s/%s",prefix,pEffectPath);*/
		if(m_pSimpleAudioEngine){
			m_pSimpleAudioEngine->setEffectsVolume(m_effectVolume);
			m_pSimpleAudioEngine->playEffect(pEffectPath);
		}else{
			m_bEffectPlaying=false;
		}
	}

	void VAudioManager::release(){
		if(m_pSimpleAudioEngine){

		}
	}

}






