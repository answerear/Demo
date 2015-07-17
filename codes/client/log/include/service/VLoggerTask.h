
#ifndef __VISION_LOGGER_TASK_H__
#define __VISION_LOGGER_TASK_H__


#include "VType.h"
#include "VMacro.h"


namespace VLoggerSystem
{
	enum ELogTask
	{
		E_LOGTASK_NONE = 0,
		E_LOGTASK_WRITE_FILE,
		E_LOGTASK_CHECK_FILE,
		E_LOGTASK_UPLOAD_FILE,
		E_LOGTASK_MAX
	};

	class VLoggerTask
	{
		V_DECLARE_INTERFACE(VLoggerTask);

	public:
		virtual ELogTask TaskType() const = 0;
	};

	class VLoggerTaskCheckFile : public VLoggerTask
	{
	public:
		virtual ELogTask TaskType() const;
	};

	class VLoggerTaskWriteFile : public VLoggerTask
	{
	public:
		virtual ELogTask TaskType() const;
	};
}


#endif	/*__VISION_LOGGER_TASK_H__*/
