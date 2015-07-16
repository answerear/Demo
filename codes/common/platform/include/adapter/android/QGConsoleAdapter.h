
#ifndef __QQGAME_CONSOLE_ADAPTER_ANDROID_H__
#define	__QQGAME_CONSOLE_ADAPTER_ANDROID_H__


#include "IConsoleAdapter.h"
#include <android/log.h> 

namespace QGLoggerSystem
{
     #define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,__VA_ARGS__)
     #define LOGI(...)  __android_log_print(ANDROID_LOG_INFO,__VA_ARGS__) 
     #define LOGW(...)  __android_log_print(ANDROID_LOG_WARN,,__VA_ARGS__)
     #define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,__VA_ARGS__) 
	class QGConsoleAdapter : public IConsoleAdapter
	{
		QG_DISABLE_COPY(QGConsoleAdapter);

	public:
		QGConsoleAdapter();

	protected:
		virtual void Print(const char *pText);
	};
}


#endif	/*__QQGAME_CONSOLE_ADAPTER_ANDROID_H__*/
