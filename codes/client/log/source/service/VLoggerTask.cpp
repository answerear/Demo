
#include "VLoggerTask.h"


namespace VLoggerSystem
{
	//----------------------------------------------------------------------------------------------
	// QGLoggerTaskCheckFile
	//----------------------------------------------------------------------------------------------
	ELogTask VLoggerTaskCheckFile::TaskType() const
	{
		return E_LOGTASK_CHECK_FILE;
	}

	//----------------------------------------------------------------------------------------------
	// QGLoggerTaskWriteFile
	//----------------------------------------------------------------------------------------------
	ELogTask VLoggerTaskWriteFile::TaskType() const
	{
		return E_LOGTASK_WRITE_FILE;
	}
}

