
#ifndef __QQGAME_LOGGER_JNI_HELPER_ANDROID_H__
#define __QQGAME_LOGGER_JNI_HELPER_ANDROID_H__

#include "QGLoggerType.h"
#include "QGApnType.h"

#ifdef QG_OS_ANDROID
#include <jni.h>
extern "C"{

	
	uint32_t StartAndroidTimer(uint32_t unInterval);
	
	void KillAndroidTimer(uint32_t unTimerID);

	QGLoggerSystem::EApnType GetApnTypeFromJava();
	QGLoggerSystem::ECarrier GetCarrierFromJava();
    
	void CancelPingRoute();
	void PingRoute(const QString& host);
};
#endif

#endif	/*__QQGAME_LOGGER_JNI_HELPER_ANDROID_H__*/