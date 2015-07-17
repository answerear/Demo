

#ifndef __VISION_LOGGER_H__
#define __VISION_LOGGER_H__


#include "VLoggerInterface.h"


#define __OPEN_LOG__


#ifdef __OPEN_LOG__

	#define V_LOG_STARTUP(appid, ver, force)	\
		if (VLoggerSystem::getLoggerServiceInstance() != NULL)	\
		{	\
			VLoggerSystem::getLoggerServiceInstance()->startup(appid, ver, force);	\
		}

	#define V_LOG_ENTER_BACKGROUND()	\
		if (VLoggerSystem::getLoggerServiceInstance() != NULL)	\
		{	\
			VLoggerSystem::getLoggerServiceInstance()->enterBackground();	\
		}

	#define V_LOG_ENTER_FOREGROUND()	\
		if (VLoggerSystem::getLoggerServiceInstance() != NULL)	\
		{	\
			VLoggerSystem::getLoggerServiceInstance()->enterForeground();	\
		}

	#define V_LOG_GET_DATA(stime, etime, content, content_size)	\
		if (VLoggerSystem::getLoggerServiceInstance() != NULL)	\
		{	\
			VLoggerSystem::getLoggerServiceInstance()->getLogData(stime, etime, content, content_size);	\
		}

	#define V_LOG_GET_DATA_EX(etime, content, content_size)	\
		if (VLoggerSystem::getLoggerServiceInstance() != NULL)	\
		{	\
			VLoggerSystem::getLoggerServiceInstance()->getLogData(etime, content, content_size);	\
		}

	// 通用宏
	#define V_LOG_TRACE(level, module, fmt, ...)	\
		if (VLoggerSystem::getLoggerServiceInstance() != NULL)	\
		{	\
			VLoggerSystem::getLoggerServiceInstance()->trace(level, __FILE__, __LINE__, module, fmt, ##__VA_ARGS__);	\
		}

	// Debug级别的日志输出宏
	#define V_LOG_TRACE_DEBUG(module, fmt, ...)	\
		if (VLoggerSystem::getLoggerServiceInstance() != NULL)	\
		{	\
			VLoggerSystem::getLoggerServiceInstance()->trace(VLoggerSystem::E_LOGLEVEL_DEBUG, __FILE__, __LINE__, module, fmt, ##__VA_ARGS__);	\
		}

	// Info级别日志输出宏
	#define V_LOG_TRACE_INFO(module, fmt, ...)	\
		if (VLoggerSystem::getLoggerServiceInstance() != NULL)	\
		{	\
			VLoggerSystem::getLoggerServiceInstance()->trace(VLoggerSystem::E_LOGLEVEL_INFO, __FILE__, __LINE__, module, fmt, ##__VA_ARGS__);	\
		}

	// Event级别日志输出宏
	#define V_LOG_TRACE_EVENT(module, fmt, ...)	\
		if (VLoggerSystem::getLoggerServiceInstance() != NULL)	\
		{	\
			VLoggerSystem::getLoggerServiceInstance()->trace(VLoggerSystem::E_LOGLEVEL_EVENT, __FILE__, __LINE__, module, fmt, ##__VA_ARGS__);	\
		}

#else

	#define V_LOG_STARTUP(appid, ver, force)

	#define V_LOG_ENTER_BACKGROUND()
	#define V_LOG_ENTER_FOREGROUND()

	#define V_LOG_GET_DATA(stime, etime, content, content_size)
	#define V_LOG_GET_DATA(etime, content, content_size)

	// 通用宏
	#define V_LOG_TRACE(level, module, fmt, ...)
	// Debug级别的日志输出宏
	#define V_LOG_TRACE_DEBUG(module, fmt, ...)
	// Info级别日志输出宏
	#define V_LOG_TRACE_INFO(module, fmt, ...)
	// Event级别日志输出宏
	#define V_LOG_TRACE_EVENT(module, fmt, ...)

#endif



#endif	/*__VISION_LOGGER_H__*/
