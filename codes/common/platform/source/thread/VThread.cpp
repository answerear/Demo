

#include "VThread.h"


namespace VPlatform
{
	pthread_t VThread::m_mainthread = pthread_self();

	VThreadID VThread::getMainThreadID()
	{
		return VThreadID(m_mainthread);
	}

	VThreadID VThread::getCurrentThreadID()
	{
		return VThreadID(pthread_self());
	}

	VThread::VThread()
		: m_bRunning(false)
		, m_bSuspend(false)
	{
		pthread_attr_init(&m_attr);
		pthread_cond_init(&m_cond, NULL);
		pthread_mutex_init(&m_mutex, NULL);
	}

	VThread::~VThread()
	{
		pthread_mutex_destroy(&m_mutex);
		pthread_cond_destroy(&m_cond);
		pthread_attr_destroy(&m_attr);
	}

	bool VThread::start(EPriority ePriority /* = E_PRIORITY_INHERIT */)
	{
		int nMaxPriority = 0;
		nMaxPriority = sched_get_priority_max(nMaxPriority);	// 获得系统支持的线程优先权的最大值

		sched_param param;
		pthread_attr_getschedparam(&m_attr, &param);

		int nLevel = nMaxPriority / E_MAX_PRIORITY;

		switch (ePriority)
		{
		case E_PRIORITY_IDLE:
			{
				pthread_attr_setschedpolicy(&m_attr, SCHED_RR);	// 设置线程调度策略
				param.sched_priority = 0;
				pthread_attr_setschedparam(&m_attr, &param);
#ifndef V_OS_ANDROID
				pthread_attr_setinheritsched(&m_attr, PTHREAD_EXPLICIT_SCHED);
#endif
			}
			break;
		case E_PRIORITY_LOWEST:
			{
				pthread_attr_setschedpolicy(&m_attr, SCHED_RR);	// 设置线程调度策略
				param.sched_priority = nLevel;
				pthread_attr_setschedparam(&m_attr, &param);
#ifndef V_OS_ANDROID
				pthread_attr_setinheritsched(&m_attr, PTHREAD_EXPLICIT_SCHED);
#endif
			}
			break;
		case E_PRIORITY_LOW:
			{
				pthread_attr_setschedpolicy(&m_attr, SCHED_RR);	// 设置线程调度策略
				param.sched_priority = 2 * nLevel;
				pthread_attr_setschedparam(&m_attr, &param);
#ifndef V_OS_ANDROID
				pthread_attr_setinheritsched(&m_attr, PTHREAD_EXPLICIT_SCHED);
#endif
			}
			break;
		case E_PRIORITY_NORMAL:
			{
				pthread_attr_setschedpolicy(&m_attr, SCHED_RR);	// 设置线程调度策略
				param.sched_priority = 3 * nLevel;
				pthread_attr_setschedparam(&m_attr, &param);
                #ifndef V_OS_ANDROID
				pthread_attr_setinheritsched(&m_attr, PTHREAD_EXPLICIT_SCHED);
                #endif
			}
			break;
		case E_PRIORITY_HIGH:
			{
				pthread_attr_setschedpolicy(&m_attr, SCHED_RR);	// 设置线程调度策略
				param.sched_priority = 4 * nLevel;
				pthread_attr_setschedparam(&m_attr, &param);
#ifndef V_OS_ANDROID
				pthread_attr_setinheritsched(&m_attr, PTHREAD_EXPLICIT_SCHED);
#endif
			}
			break;
		case E_PRIORITY_HIGHEST:
			{
				pthread_attr_setschedpolicy(&m_attr, SCHED_RR);	// 设置线程调度策略
				param.sched_priority = 5 * nLevel;
				pthread_attr_setschedparam(&m_attr, &param);
                #ifndef V_OS_ANDROID
				  pthread_attr_setinheritsched(&m_attr, PTHREAD_EXPLICIT_SCHED);
                #endif
			}
			break;
		case E_PRIORITY_TIME_CRITICAL:
			{
				pthread_attr_setschedpolicy(&m_attr, SCHED_RR);	// 设置线程调度策略
				param.sched_priority = nMaxPriority;
				pthread_attr_setschedparam(&m_attr, &param);
                #ifndef V_OS_ANDROID
				  pthread_attr_setinheritsched(&m_attr, PTHREAD_EXPLICIT_SCHED);
				#endif
			}
			break;
		case E_PRIORITY_INHERIT:
		default:
			{
				 #ifndef V_OS_ANDROID
				pthread_attr_setinheritsched(&m_attr, PTHREAD_INHERIT_SCHED);
				#endif
			}
			break;
		}

		int nResult = pthread_create(&m_thread, &m_attr, VThread::ThreadRoutine, this);

		return (nResult == 0);
	}

	bool VThread::suspend()
	{
		pthread_mutex_lock(&m_mutex);
		m_bSuspend = true;
		while (m_bSuspend)
		{
			pthread_cond_wait(&m_cond, &m_mutex);
		}
		pthread_mutex_unlock(&m_mutex);
		return true;
	}

	bool VThread::resume()
	{
		pthread_mutex_lock(&m_mutex);
		m_bSuspend = false;
		pthread_cond_broadcast(&m_cond);
		pthread_mutex_unlock(&m_mutex);
		return true;
	}

	bool VThread::terminate()
	{
        #ifndef V_OS_ANDROID
		if (pthread_cancel(m_thread))
		{
			return false;
		}
		#endif
		m_bRunning = false;
		m_bSuspend = false;

		return false;
	}

	bool VThread::wait()
	{
		return (pthread_join(m_thread, NULL) == 0);
	}

	void VThread::release()
	{
		pthread_detach(m_thread);
	}

	void *VThread::ThreadRoutine(void *pUser)
	{
		VThread *pThread = (VThread *)pUser;
		
		pThread->m_bRunning = true;
		
		if (pThread != NULL)
		{
			pThread->run();
			pThread->release();
		}

		pThread->m_bRunning = false;

		return NULL;
	}
}
