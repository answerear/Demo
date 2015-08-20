

#include "VConsoleAdapter.h"
#include <android/log.h> 


namespace VPlatform
{
	#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,__VA_ARGS__)
	#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO,__VA_ARGS__) 
	#define LOGW(...)  __android_log_print(ANDROID_LOG_WARN,,__VA_ARGS__)
	#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,__VA_ARGS__) 

	VConsoleAdapter::VConsoleAdapter()
	{

	}

	void VConsoleAdapter::Print(const char *pText)
	{
		LOGD("Platform","%s\n", pText);
	}
}
