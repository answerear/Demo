#include "QGAndroidJNIHelper.h"
#include "QGTimerAdapter.h"
#include "QGConsoleAdapter.h"
#include "QGDirAdapter.h"
#include "QGAndroidApnManager.h"
using namespace QGLoggerSystem;


extern "C"{
	JavaVM *gJavaVM = NULL;

	typedef struct {
		jclass classID;
		jmethodID methodID;
	}JNICallParam;

	//全局保存Timer类信息，提供效率
	static struct timer_offset_t 
	{
		jclass classID;
		jmethodID StartTimermethodID;
		jmethodID KillTimermethodID;
		bool m_bLoaded;

		timer_offset_t(){
			m_bLoaded=false;
		}
	}gTimerOffset;

	//APN类信息
    static struct apn_offset_t
	{
		jclass classID;
		jmethodID GetAPNTypemethodID;
		jmethodID GetCarrierTypemethodID;
		jmethodID PingRouteMethodID;
		jmethodID CacelRouteMethodID;
		bool m_bLoaded;

		apn_offset_t(){
			m_bLoaded=false;
		}
	}gApnOffset;

	//保证JNIEnv的有效性,这样也能克服多线程问题
	static void EnsureJNIEnvSafe(JNIEnv *&pJNIEnv){
		if(gJavaVM){
			if (gJavaVM->AttachCurrentThread(&pJNIEnv, 0)!=JNI_OK) {
			   pJNIEnv=NULL;
			}
		}else{
			pJNIEnv=NULL;
		}
	}

    //获取classID及methodID的工具方法
	static bool GetClassStaticMethodID(JNIEnv *pJNIEnv,JNICallParam &stJNIParam,const char *szClassName,const char *szMethodName,const char*szMethodParam){
		if(pJNIEnv){
			stJNIParam.classID=pJNIEnv->FindClass(szClassName);
			if(!stJNIParam.classID){
				return false;
			}
			stJNIParam.methodID=pJNIEnv->GetStaticMethodID(stJNIParam.classID, szMethodName, szMethodParam);
			if(!stJNIParam.methodID){
				return false;
			}
			return true;
		}else{
			return false;
		}
	}

    //外部不传入ENV,函数内部保证其有效性
	static bool GetClassStaticMethodIDWithoutEnv(JNICallParam &stJNIParam,const char *szClassName,const char *szMethodName,const char*szMethodParam){
		JNIEnv *pJNIENV=NULL;
		EnsureJNIEnvSafe(pJNIENV);
		if(pJNIENV){
           return GetClassStaticMethodID(pJNIENV,stJNIParam,szClassName,szMethodName,szMethodParam);
		}else{
           return false;
		}
	}
	
	//-----------------------------------------------------------------------Timer Start--------------------------------------------
	//初始化JNI调用所需的ID信息
	static void LoadTimerOffset(JNIEnv *pJNIEnv){
		if(pJNIEnv){
			jclass timer=pJNIEnv->FindClass("com/tencent/qgame/timer/QGTimer");
			if(!timer){
				return ;
			}
			gTimerOffset.classID=(jclass)pJNIEnv->NewGlobalRef(timer);
			jmethodID startTimer=pJNIEnv->GetStaticMethodID(gTimerOffset.classID,"setTimer","(I)I");
			if(!startTimer||!gTimerOffset.classID){
				if(gTimerOffset.classID){
				    pJNIEnv->DeleteGlobalRef(gTimerOffset.classID);
			    }
				return ;
			}
			gTimerOffset.StartTimermethodID=startTimer;
			jmethodID killTimer=pJNIEnv->GetStaticMethodID(gTimerOffset.classID,"killTimer","(I)V");
			if(!killTimer){
				pJNIEnv->DeleteGlobalRef(gTimerOffset.classID);
			   return ;
			}
			gTimerOffset.KillTimermethodID=killTimer;
			gTimerOffset.m_bLoaded=true;
		}
	}

	static void UnLoadTimerOffset(JNIEnv *pJNIEnv){
		if(gTimerOffset.m_bLoaded&&pJNIEnv){
			pJNIEnv->DeleteGlobalRef(gTimerOffset.classID);
			gTimerOffset.m_bLoaded=false;
		}
	}

    uint32_t StartAndroidTimer(uint32_t unInterval){
		JNIEnv *pJNIENV=NULL;
		EnsureJNIEnvSafe(pJNIENV);
		if(pJNIENV){
			if(gTimerOffset.m_bLoaded){
				LOGD("QGameLogSDK","use TimerOffset start methodid");
                return pJNIENV->CallStaticIntMethod(gTimerOffset.classID,gTimerOffset.StartTimermethodID,unInterval);
			}else{
				JNICallParam param;
				if(GetClassStaticMethodID(pJNIENV,param,"com/tencent/qgame/timer/QGTimer","setTimer","(I)I")){
					LOGD("QGameLogSDK","no use TimerOffset start methodid");
                    return pJNIENV->CallStaticIntMethod(param.classID,param.methodID,unInterval); 
				}else{
                   return 0;
				}
			}
		}else{
			return 0;
		}
	} 

	void KillAndroidTimer(uint32_t unTimerID){
		JNIEnv *pJNIENV=NULL;
		EnsureJNIEnvSafe(pJNIENV);
		if(pJNIENV){
			if(gTimerOffset.m_bLoaded){
				   LOGD("QGameLogSDK","use TimerOffset kill methodid");
				   pJNIENV->CallStaticVoidMethod(gTimerOffset.classID,gTimerOffset.KillTimermethodID,unTimerID);
			}else{
				JNICallParam param;
				if(GetClassStaticMethodID(pJNIENV,param,"com/tencent/qgame/timer/QGTimer","killTimer","(I)V")){
					 LOGD("QGameLogSDK","no use TimerOffset kill methodid");
					pJNIENV->CallStaticVoidMethod(param.classID,param.methodID,unTimerID); 
				}else{
					
				}
			}
		}
	}

	//-----------------------------------------------------------------------Timer End--------------------------------------------

	//-----------------------------------------------------------------------APN Start--------------------------------------------
	void LoadAPNOffset(JNIEnv *pJNIEnv){
		if(pJNIEnv){
         do{
			jclass apnClass=pJNIEnv->FindClass("com/tencent/qgame/apn/NetworkTypeTranlate");
			if(!apnClass){
				return ;
			}
			gApnOffset.classID=(jclass)pJNIEnv->NewGlobalRef(apnClass);
			jmethodID getAPNType=pJNIEnv->GetStaticMethodID(gApnOffset.classID,"getAPNType","()I");
			if(!getAPNType||!gApnOffset.classID){
				break;
			}
			gApnOffset.GetAPNTypemethodID=getAPNType;
			jmethodID getCarrierType=pJNIEnv->GetStaticMethodID(gApnOffset.classID,"getCarrierType","()I");
			if(!getCarrierType){
				break;
			}
			gApnOffset.GetCarrierTypemethodID=getCarrierType;
			jmethodID pingRoute=pJNIEnv->GetStaticMethodID(gApnOffset.classID,"pingRoute","(Ljava/lang/String;)V");
			if(!pingRoute){
				break;
			}
			gApnOffset.PingRouteMethodID=pingRoute;
			jmethodID cancelRoute=pJNIEnv->GetStaticMethodID(gApnOffset.classID,"cancelRoute","()V");
			if(!cancelRoute){
				break;
			}
			gApnOffset.CacelRouteMethodID=cancelRoute;
			gApnOffset.m_bLoaded=true;
			return ;
		 }while(0);
		  if(gApnOffset.classID){
               pJNIEnv->DeleteGlobalRef(gApnOffset.classID);
		  }
		}
	}

	void UnLoadAPNOffset(JNIEnv *pJNIENV){
		if(gApnOffset.m_bLoaded&&pJNIENV){
			pJNIENV->DeleteGlobalRef(gApnOffset.classID);
			gApnOffset.m_bLoaded=false;
		}
	}

	static QGLoggerSystem::EApnType TranslateApn(jint apn){
		switch(apn){
		 case 0:
		 {
           return E_APN_UNREACHABLE;
	     }
		 case 1:
	     {
           return E_APN_WIFI;

		 }
		 case 2:
	    {
           return E_APN_2G;

	     }
		 case 3:{
           return E_APN_3G;
		 }
		 case 4:{
           return E_APN_4G;
		 }
		 case 5:{
            return E_APN_UNKNOWN;
		  }
		}
		return E_APN_UNKNOWN;
	}

	static ECarrier TranlateCarrier(jint carrier){
		switch(carrier){
		case 0:
			{
				return E_CARRIER_UNKNOWN;
			}
		case 1:
			{
				return E_CARRIER_CHINA_MOBILE;

			}
		case 2:
			{
				return E_CARRIER_CHINA_UNICOM;

			}
		case 3:{
			return E_CARRIER_CHINA_TELECOM;
	     }
		case 4:{
			return E_CARRIER_CHINA_TIETONG;
			   }
		}
		return E_CARRIER_UNKNOWN;
	}

	EApnType GetApnTypeFromJava(){
		JNIEnv *pJNIENV=NULL;
		EnsureJNIEnvSafe(pJNIENV);
		if(pJNIENV){
			if(gApnOffset.m_bLoaded){
				jint apn= pJNIENV->CallStaticIntMethod(gApnOffset.classID,gApnOffset.GetAPNTypemethodID);
				return TranslateApn(apn);
			}else{
				JNICallParam param;
				if(GetClassStaticMethodID(pJNIENV,param,"com/tencent/qgame/apn/NetworkTypeTranlate","getAPNType","()I")){
					jint apn= pJNIENV->CallStaticIntMethod(param.classID,param.methodID); 
					return TranslateApn(apn);
				}else{
                    return QGLoggerSystem::E_APN_UNKNOWN;
				}
			}
		}
	}

	QGLoggerSystem::ECarrier GetCarrierFromJava(){
		JNIEnv *pJNIENV=NULL;
		EnsureJNIEnvSafe(pJNIENV);
		if(pJNIENV){
			if(gApnOffset.m_bLoaded){
				jint carrier=pJNIENV->CallStaticIntMethod(gApnOffset.classID,gApnOffset.GetCarrierTypemethodID);
				return TranlateCarrier(carrier);
			}else{
				JNICallParam param;
				if(GetClassStaticMethodID(pJNIENV,param,"com/tencent/qgame/apn/NetworkTypeTranlate","getCarrierType","()I")){
					jint carrier=pJNIENV->CallStaticIntMethod(param.classID,param.methodID); 
					return TranlateCarrier(carrier);
				}else{
					return QGLoggerSystem::E_CARRIER_UNKNOWN;
				}
			}
		}
	}

	void Java_com_tencent_qgame_apn_NetworkTypeTranlate_onPingResult(JNIEnv* env,jobject thiz,jboolean bReachable){
		LOGD("QGameLogSDK","onPingResult %d",bReachable);
		QGAndroidApnManager::g().OnPingResult(bReachable==JNI_TRUE?true:false);
	}

	void RequestPingHost(const QString& host){
		JNIEnv *pJNIENV=NULL;
		EnsureJNIEnvSafe(pJNIENV);
		if(pJNIENV){
			jstring jniHost=pJNIENV->NewStringUTF(host.c_str());
			if(gApnOffset.PingRouteMethodID){
				LOGD("QGameLogSDK","use ApnOffset pingRoute");
				pJNIENV->CallStaticVoidMethod(gApnOffset.classID,gApnOffset.PingRouteMethodID,jniHost);
			}else{
				JNICallParam param;
				if(GetClassStaticMethodID(pJNIENV,param,"com/tencent/qgame/apn/NetworkTypeTranlate","pingRoute","(Ljava/lang/String;)V")){
					LOGD("QGameLogSDK","no use ApnOffset pingRoute");
					pJNIENV->CallStaticVoidMethod(param.classID,param.methodID,jniHost); 
				}else{

				}
			}
		}else{
			QGAndroidApnManager::g().OnPingResult(false);
		}
	}

	void RequestCancelPingRoute(){
		JNIEnv *pJNIENV=NULL;
		EnsureJNIEnvSafe(pJNIENV);
		if(pJNIENV){
			if(gApnOffset.PingRouteMethodID){
				LOGD("QGameLogSDK","use ApnOffset cancelRoute");
				pJNIENV->CallStaticVoidMethod(gApnOffset.classID,gApnOffset.CacelRouteMethodID);
			}else{
				JNICallParam param;
				if(GetClassStaticMethodID(pJNIENV,param,"com/tencent/qgame/apn/NetworkTypeTranlate","cancelRoute","()V")){
					LOGD("QGameLogSDK","no use ApnOffset cancelRoute");
					pJNIENV->CallStaticVoidMethod(param.classID,param.methodID); 
				}else{

				}
			}
		}
	}
	//-----------------------------------------------------------------------APN End--------------------------------------------

	jint JNI_OnLoad(JavaVM *vm, void *reserved) {
		gJavaVM = vm;
		JNIEnv *pJNIENV=NULL;
		EnsureJNIEnvSafe(pJNIENV);
		if(pJNIENV){
           LoadTimerOffset(pJNIENV);
		   LoadAPNOffset(pJNIENV);
		}
		return JNI_VERSION_1_4;
	}

	void JNI_OnUnload(JavaVM *vm, void *reserved) {
		JNIEnv *pJNIENV=NULL;
		EnsureJNIEnvSafe(pJNIENV);
		if(pJNIENV){
           UnLoadTimerOffset(pJNIENV); 
		   UnLoadAPNOffset(pJNIENV);
		}
	}

	void Java_com_tencent_qgame_timer_QGTimer_testStartTimer(JNIEnv* env,jobject thiz,jint eclispe){
		StartAndroidTimer(eclispe);
	}

	void Java_com_tencent_qgame_timer_QGTimer_testKillTimer(JNIEnv* env,jobject thiz,jint id){
		 KillAndroidTimer(id);
	}

	void Java_com_tencent_qgame_timer_QGTimer_onTimeoutEvent(JNIEnv* env,jobject thiz,jint id){
		QGTimerAdapter::OnTimer(id);
	}

	void Java_com_tencent_qgame_apn_NetworkTypeTranlate_onNetworkInfoChange(JNIEnv* env,jobject thiz,jint apnType,jint carrierType){
		LOGD("QGameLogSDK","apnType=%d,carrierType=%d\n",apnType,carrierType);
		QGAndroidApnManager::g().OnApnChanged(TranslateApn(apnType));
	}

    void PingRoute(const QString& host){
		RequestPingHost(host);
	}

	void CancelPingRoute(){
		RequestCancelPingRoute();
	}

	void  Java_com_tencent_qgame_apn_NetworkTypeTranlate_pingTest(JNIEnv* env,jobject thiz){
		PingRoute(QString("www.baidu.com"));
	}

	void  Java_com_tencent_qgame_apn_NetworkTypeTranlate_cancelPingTest(JNIEnv* env,jobject thiz){
		CancelPingRoute();
	}

	void Java_com_tencent_qgame_dir_QGDir_setAppPath(JNIEnv* env,jobject thiz,jstring path){
		jboolean isCopy;
		const char* strCachePath = env->GetStringUTFChars(path, &isCopy);
		if (isCopy) {
			LOGD("QGameLogSDK","appPath=%s\n",strCachePath);
			QGDirAdapter::SetAppPath(strCachePath);
			env->ReleaseStringUTFChars(path, strCachePath);
		}
	}

	void Java_com_tencent_qgame_dir_QGDir_setSDPath(JNIEnv* env,jobject thiz,jstring path){
		jboolean isCopy;
		const char* strSDPath = env->GetStringUTFChars(path, &isCopy);
		if (isCopy) {
			LOGD("QGameLogSDK","sdPath=%s\n",strSDPath);
			QGDirAdapter::SetExternalStoragePath(strSDPath);
			env->ReleaseStringUTFChars(path, strSDPath);
		}
	}

	void Java_com_tencent_qgame_dir_QGDir_notifySDState(JNIEnv* env,jobject thiz,jboolean ready){
		LOGD("QGameLogSDK","ready=%d\n",ready);
		QGDirAdapter::SetExternalStroageRedy(ready);
	}
};
